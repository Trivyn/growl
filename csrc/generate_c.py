#!/usr/bin/env python3
"""
Generate bootstrap C files using slop's module resolution.

This script uses slop's existing module resolution to determine the correct
build order, then calls the native transpiler and writes the C files to
the output directory.

Usage: python3 generate_c.py [--append] <tool_dir> <output_dir>
  tool_dir:   Directory containing slop.toml (e.g., cli/ or cli/tests/)
  output_dir: Where to write the C files (e.g., csrc/src)
  --append:   Don't clear existing slop_* files before writing (for second pass)
"""

import sys
import os
import json
import subprocess
from pathlib import Path

# Add the slop package to the path
slop_home = os.environ.get("SLOP_HOME")
if slop_home:
    sys.path.insert(0, str(Path(slop_home) / "src"))

from slop.parser import parse_file
from slop.resolver import ModuleResolver
from slop.providers import load_project_config
from slop import paths


def main():
    # Parse args
    append_mode = False
    args = sys.argv[1:]
    if "--append" in args:
        append_mode = True
        args.remove("--append")

    if len(args) != 2:
        print(f"Usage: {sys.argv[0]} [--append] <tool_dir> <output_dir>")
        sys.exit(1)

    tool_dir = Path(args[0]).resolve()
    output_dir = Path(args[1]).resolve()

    # Change to tool directory for config loading
    original_cwd = os.getcwd()
    os.chdir(tool_dir)

    try:
        # Load project config
        project_cfg, build_cfg, _, _ = load_project_config(None)

        if not project_cfg or not project_cfg.entry:
            print(f"Error: No entry point in {tool_dir}/slop.toml")
            sys.exit(1)

        entry_file = Path(project_cfg.entry)

        # Get include paths from config, expanding ${SLOP_HOME}
        include_paths = []
        if build_cfg and build_cfg.include:
            for p in build_cfg.include:
                expanded = p.replace("${SLOP_HOME}", slop_home or "")
                include_paths.append(str(tool_dir / expanded))

        # Add standard library paths
        stdlib_paths = paths.get_stdlib_include_paths()
        for stdlib_path in stdlib_paths:
            if str(stdlib_path) not in include_paths:
                include_paths.append(str(stdlib_path))

        # Parse entry file
        ast = parse_file(str(entry_file))

        # Resolve modules
        search_paths = [Path(p) for p in include_paths]
        resolver = ModuleResolver(search_paths)
        graph = resolver.build_dependency_graph(entry_file)
        order = resolver.topological_sort(graph)

        print(f"  Build order: {', '.join(order)}")

        # Get source files in order
        source_files = [str(graph.modules[name].path) for name in order]

        # Find native compiler
        compiler_bin = Path(slop_home) / "bin" / "slop-compiler" if slop_home else None
        if not compiler_bin or not compiler_bin.exists():
            print(f"Error: Native compiler not found at {compiler_bin}")
            sys.exit(1)

        # Call native compiler
        cmd = [str(compiler_bin), "transpile"] + source_files
        print(f"  Running: slop-compiler transpile ({len(source_files)} files)")
        result = subprocess.run(cmd, capture_output=True, text=True)

        if result.returncode != 0:
            print(f"Transpiler failed:\n{result.stderr}")
            sys.exit(1)

        # Parse JSON output
        try:
            modules = json.loads(result.stdout)
        except json.JSONDecodeError as e:
            print(f"Failed to parse transpiler output: {e}")
            print(f"Output: {result.stdout[:500]}...")
            sys.exit(1)

        # Create output directory
        output_dir.mkdir(parents=True, exist_ok=True)

        # Clear existing files only if not in append mode
        if not append_mode:
            for f in output_dir.glob("slop_*.h"):
                f.unlink()
            for f in output_dir.glob("slop_*.c"):
                f.unlink()

        # Write C files
        written = 0
        skipped = 0
        for mod_name, content in modules.items():
            c_name = mod_name.replace("-", "_").replace("/", "_")
            header_path = output_dir / f"slop_{c_name}.h"
            impl_path = output_dir / f"slop_{c_name}.c"

            # In append mode, skip modules that already exist
            if append_mode and header_path.exists():
                skipped += 1
                continue

            header = content.get("header", "")
            impl = content.get("impl", "")

            # Fix runtime include path
            header = header.replace(
                '#include "slop_runtime.h"',
                '#include "../runtime/slop_runtime.h"',
            )

            # Write header
            with open(header_path, "w") as f:
                f.write(header)

            # Write implementation with includes
            with open(impl_path, "w") as f:
                f.write('#include "../runtime/slop_runtime.h"\n')
                f.write(f'#include "slop_{c_name}.h"\n\n')
                f.write(impl)

            written += 1

        print(f"  Generated {written} modules in {output_dir}")
        if skipped:
            print(f"  Skipped {skipped} modules (already present)")

    finally:
        os.chdir(original_cwd)


if __name__ == "__main__":
    main()
