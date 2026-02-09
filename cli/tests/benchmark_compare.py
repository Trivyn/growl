#!/usr/bin/env python3
"""Reasoner comparison: OWL-RL (ground truth) vs Reasonable vs Growl.

OWL-RL is the W3C reference implementation for OWL 2 RL/RDF rules.
It serves as ground truth for expected inference counts.
Reasonable is a fast Rust-based OWL 2 RL reasoner for performance comparison.

Usage: cd cli/tests && python benchmark_compare.py
       cd cli/tests && python benchmark_compare.py --diff
  Requires: pip install owlrl rdflib reasonable
  Requires: growl CLI built at ../build/growl
"""

import argparse
import os
import subprocess
import sys
import tempfile
import time
from collections import defaultdict
from statistics import median

import rdflib
from owlrl import DeductiveClosure, OWLRL_Semantics

FIXTURES = "fixtures"
BENCHMARKS = "fixtures/benchmarks"
GROWL = "../build/growl"

FILES = [
    f"{FIXTURES}/bfo-core.ttl",
    f"{BENCHMARKS}/pizza.ttl",
    f"{FIXTURES}/CommonCoreOntologiesMerged.ttl",
    f"{BENCHMARKS}/schemaorg.ttl",
    f"{BENCHMARKS}/Brick.ttl",
]

# OWL-RL is pure Python and very slow on large files.
# Skip it for files above this threshold (triples).
OWLRL_SKIP_THRESHOLD = 20000

RUNS = 3


def run_owlrl(path, return_graph=False):
    """Run OWL-RL (W3C reference) on a TTL file. Returns (input, inferred, time_s[, graph])."""
    g = rdflib.Graph()
    g.parse(path, format="turtle")
    input_count = len(g)

    if input_count > OWLRL_SKIP_THRESHOLD:
        if return_graph:
            return input_count, None, None, None
        return input_count, None, None

    t0 = time.perf_counter()
    DeductiveClosure(OWLRL_Semantics).expand(g)
    elapsed = time.perf_counter() - t0

    total = len(g)
    inferred = total - input_count
    if return_graph:
        return input_count, inferred, elapsed, g
    return input_count, inferred, elapsed


def run_reasonable(path):
    """Run reasonable on a TTL file. Returns (input, output, median_time_s)."""
    import reasonable
    g = rdflib.Graph()
    g.parse(path, format="turtle")
    input_count = len(g)

    times = []
    output_count = None
    for _ in range(RUNS):
        r = reasonable.PyReasoner()
        r.from_graph(g)
        t0 = time.perf_counter()
        triples = r.reason()
        elapsed = time.perf_counter() - t0
        output_count = input_count + len(triples)
        times.append(elapsed)

    return input_count, output_count, median(times)


def parse_growl_output(line):
    """Parse growl --quiet output line. Returns (input, output, reason_time)."""
    if not line:
        return None, None, None
    # Format: "file.ttl: 0.031s parse, 0.030s reason, 1014 -> 1014 triples"
    parts = line.split(",")
    reason_part = parts[1].strip()  # "0.030s reason"
    reason_time = float(reason_part.split("s")[0])

    triple_part = parts[2].strip()  # "1014 -> 1014 triples"
    nums = triple_part.replace("triples", "").strip().split("->")
    input_count = int(nums[0].strip())
    output_count = int(nums[1].strip())
    return input_count, output_count, reason_time


def run_growl(path, fast=False, complete=False, emit=None, count_emitted=False):
    """Run growl on a TTL file. Returns (input, output, median_time_s).

    If count_emitted is True, emits to a temp file and counts triples with
    rdflib for an apples-to-apples comparison with OWL-RL. Timing still comes
    from --quiet output (reasoning only, excludes serialization).
    """
    # Always emit to temp file when counting emitted triples
    emit_path = emit
    if count_emitted and not emit_path:
        emit_path = os.path.join(
            tempfile.gettempdir(),
            f"growl_bench_{os.path.basename(path)}"
        )

    cmd = [GROWL, "--quiet"]
    if fast:
        cmd.append("--fast")
    if complete:
        cmd.append("--complete")
    if emit_path:
        cmd.extend(["--emit", emit_path])
    cmd.append(path)

    times = []
    input_count = None
    output_count = None

    for _ in range(RUNS):
        result = subprocess.run(cmd, capture_output=True, text=True)
        inp, out, t = parse_growl_output(result.stdout.strip())
        if inp is None:
            return None, None, None
        input_count = inp
        output_count = out
        times.append(t)

    if count_emitted and emit_path and os.path.exists(emit_path):
        g = rdflib.Graph()
        g.parse(emit_path, format="turtle")
        output_count = len(g)
        if not emit:
            os.unlink(emit_path)

    return input_count, output_count, median(times)


def fmt_count(n):
    """Format a count, or '-' if None."""
    if n is None:
        return "-"
    return str(n)


def fmt_time(t):
    """Format time in ms, or '-' if None."""
    if t is None:
        return "-"
    return f"{t*1000:.0f}ms"


def shorten_uri(uri):
    """Shorten common URIs for display."""
    prefixes = [
        ("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf:"),
        ("http://www.w3.org/2000/01/rdf-schema#", "rdfs:"),
        ("http://www.w3.org/2002/07/owl#", "owl:"),
        ("http://www.w3.org/2001/XMLSchema#", "xsd:"),
    ]
    s = str(uri)
    for full, short in prefixes:
        if s.startswith(full):
            return short + s[len(full):]
    # Shorten long URIs by taking the local name
    if "#" in s:
        return "..." + s[s.rfind("#"):]
    if "/" in s:
        return "..." + s[s.rfind("/"):]
    return s


def diff_mode(files):
    """Run diff analysis between OWL-RL and Growl outputs."""
    if not os.path.exists(GROWL):
        print(f"Error: growl binary not found at {GROWL}")
        print("Build it first: cd cli && slop build")
        sys.exit(1)

    print("=" * 72)
    print("  Triple Diff: OWL-RL (ground truth) vs Growl")
    print("=" * 72)
    print()

    for path in files:
        name = path.split("/")[-1]
        print(f"--- {name} ---")

        # Run OWL-RL and keep graph
        print("  Running OWL-RL...", end="", flush=True)
        owlrl_input, owlrl_inferred, owlrl_time, owlrl_graph = run_owlrl(
            path, return_graph=True
        )
        if owlrl_graph is None:
            print(f" SKIPPED (>{OWLRL_SKIP_THRESHOLD} input triples)")
            print()
            continue
        print(f" done ({owlrl_time:.1f}s, {len(owlrl_graph)} triples)")

        # Run Growl with --complete --emit (complete mode for OWL 2 RL conformance)
        emit_path = os.path.join(
            tempfile.gettempdir(), f"growl_{name}"
        )
        print(f"  Running Growl --complete --emit {emit_path}...", end="", flush=True)
        cmd = [GROWL, "--quiet", "--complete", "--emit", emit_path, path]
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print(f" FAILED: {result.stderr.strip()}")
            print()
            continue
        print(" done")

        # Load Growl output
        print("  Loading Growl output...", end="", flush=True)
        growl_graph = rdflib.Graph()
        growl_graph.parse(emit_path, format="turtle")
        print(f" done ({len(growl_graph)} triples)")

        # Convert to sets of (s, p, o) tuples for comparison
        # Filter out triples with blank nodes (can't compare across systems)
        def is_named(t):
            s, p, o = t
            return not isinstance(s, rdflib.BNode) and not isinstance(o, rdflib.BNode)

        owlrl_all = set(owlrl_graph)
        growl_all = set(growl_graph)
        owlrl_set = {t for t in owlrl_all if is_named(t)}
        growl_set = {t for t in growl_all if is_named(t)}

        missing = owlrl_set - growl_set  # In OWL-RL but not Growl
        extra = growl_set - owlrl_set  # In Growl but not OWL-RL

        owlrl_bnode = len(owlrl_all) - len(owlrl_set)
        growl_bnode = len(growl_all) - len(growl_set)

        print()
        print(f"  OWL-RL total: {len(owlrl_all)} ({len(owlrl_set)} named, {owlrl_bnode} with bnodes)")
        print(f"  Growl total:  {len(growl_all)} ({len(growl_set)} named, {growl_bnode} with bnodes)")
        print(f"  MISSING (in OWL-RL, not Growl): {len(missing)} named triples")
        print(f"  EXTRA   (in Growl, not OWL-RL): {len(extra)} named triples")

        if missing:
            print()
            print("  MISSING triples by predicate:")
            by_pred = defaultdict(list)
            for s, p, o in missing:
                by_pred[str(p)].append((s, p, o))
            for pred in sorted(by_pred, key=lambda p: -len(by_pred[p])):
                triples = by_pred[pred]
                print(f"    {shorten_uri(pred):40s} {len(triples):>6d}")
                # Show up to 3 examples
                for s, p, o in triples[:3]:
                    print(f"      e.g. ({shorten_uri(s)}, {shorten_uri(p)}, {shorten_uri(o)})")

        if extra:
            print()
            print("  EXTRA triples by predicate:")
            by_pred = defaultdict(list)
            for s, p, o in extra:
                by_pred[str(p)].append((s, p, o))
            for pred in sorted(by_pred, key=lambda p: -len(by_pred[p])):
                triples = by_pred[pred]
                print(f"    {shorten_uri(pred):40s} {len(triples):>6d}")
                for s, p, o in triples[:3]:
                    print(f"      e.g. ({shorten_uri(s)}, {shorten_uri(p)}, {shorten_uri(o)})")

        print()


def compare_mode(files):
    """Run the standard comparison benchmark."""
    if not os.path.exists(GROWL):
        print(f"Error: growl binary not found at {GROWL}")
        print("Build it first: cd cli && slop build")
        sys.exit(1)

    print("=" * 72)
    print("  Reasoner Comparison: OWL-RL (ground truth) vs Reasonable vs Growl")
    print("=" * 72)
    print()

    for path in files:
        name = path.split("/")[-1]
        print(f"--- {name} ---")

        # OWL-RL
        print("  Running OWL-RL...", end="", flush=True)
        owlrl_input, owlrl_inferred, owlrl_time = run_owlrl(path)
        if owlrl_inferred is None:
            print(f" SKIPPED (>{OWLRL_SKIP_THRESHOLD} input triples)")
        else:
            print(f" done ({owlrl_time:.1f}s)")

        # Reasonable
        print("  Running Reasonable...", end="", flush=True)
        _, reasonable_output, reasonable_time = run_reasonable(path)
        reasonable_inferred = (reasonable_output - owlrl_input) if reasonable_output is not None else None
        print(f" done ({fmt_time(reasonable_time)})")

        # Growl (fast)
        print("  Running Growl --fast...", end="", flush=True)
        growl_input, growl_fast_output, growl_fast_time = run_growl(path, fast=True, count_emitted=True)
        growl_fast_inferred = (growl_fast_output - growl_input) if growl_fast_output is not None else None
        print(f" done ({fmt_time(growl_fast_time)})")

        # Growl (full)
        print("  Running Growl (full)...", end="", flush=True)
        _, growl_full_output, growl_full_time = run_growl(path, fast=False, count_emitted=True)
        growl_full_inferred = (growl_full_output - growl_input) if growl_full_output is not None else None
        print(f" done ({fmt_time(growl_full_time)})")

        # Growl (complete)
        print("  Running Growl (complete)...", end="", flush=True)
        _, growl_complete_output, growl_complete_time = run_growl(path, complete=True, count_emitted=True)
        growl_complete_inferred = (growl_complete_output - growl_input) if growl_complete_output is not None else None
        print(f" done ({fmt_time(growl_complete_time)})")

        # Summary table
        print()
        print(f"  {'':20s} {'Input':>8s}  {'Inferred':>8s}  {'Total':>8s}  {'Time':>8s}")
        print(f"  {'':20s} {'-----':>8s}  {'--------':>8s}  {'-----':>8s}  {'----':>8s}")

        owlrl_total = (owlrl_input + owlrl_inferred) if owlrl_inferred is not None else None
        print(f"  {'OWL-RL (ref)':20s} {fmt_count(owlrl_input):>8s}  {fmt_count(owlrl_inferred):>8s}  {fmt_count(owlrl_total):>8s}  {fmt_time(owlrl_time):>8s}")
        print(f"  {'Reasonable':20s} {fmt_count(owlrl_input):>8s}  {fmt_count(reasonable_inferred):>8s}  {fmt_count(reasonable_output):>8s}  {fmt_time(reasonable_time):>8s}")

        print(f"  {'Growl (complete)':20s} {fmt_count(growl_input):>8s}  {fmt_count(growl_complete_inferred):>8s}  {fmt_count(growl_complete_output):>8s}  {fmt_time(growl_complete_time):>8s}")
        print(f"  {'Growl (full)':20s} {fmt_count(growl_input):>8s}  {fmt_count(growl_full_inferred):>8s}  {fmt_count(growl_full_output):>8s}  {fmt_time(growl_full_time):>8s}")
        print(f"  {'Growl (fast)':20s} {fmt_count(growl_input):>8s}  {fmt_count(growl_fast_inferred):>8s}  {fmt_count(growl_fast_output):>8s}  {fmt_time(growl_fast_time):>8s}")

        # Deltas
        if owlrl_inferred is not None:
            print()
            if growl_complete_inferred is not None and owlrl_inferred > 0:
                diff = growl_complete_inferred - owlrl_inferred
                sign = "+" if diff > 0 else ""
                print(f"  Growl complete vs OWL-RL: {sign}{diff} inferred ({sign}{diff/owlrl_inferred*100:.1f}%)")
            if growl_full_inferred is not None and owlrl_inferred > 0:
                diff = growl_full_inferred - owlrl_inferred
                sign = "+" if diff > 0 else ""
                print(f"  Growl full vs OWL-RL: {sign}{diff} inferred ({sign}{diff/owlrl_inferred*100:.1f}%)")
            if growl_fast_inferred is not None and owlrl_inferred > 0:
                diff = growl_fast_inferred - owlrl_inferred
                sign = "+" if diff > 0 else ""
                print(f"  Growl fast vs OWL-RL: {sign}{diff} inferred ({sign}{diff/owlrl_inferred*100:.1f}%)")

        if reasonable_inferred is not None and growl_fast_inferred is not None:
            diff = growl_fast_inferred - reasonable_inferred
            sign = "+" if diff > 0 else ""
            print(f"  Growl fast vs Reasonable: {sign}{diff} inferred")

        print()


def main():
    parser = argparse.ArgumentParser(description="Reasoner comparison: OWL-RL vs Growl")
    parser.add_argument("--diff", action="store_true",
                        help="Run triple-level diff analysis between OWL-RL and Growl")
    parser.add_argument("files", nargs="*",
                        help="Specific TTL files to test (default: all)")
    args = parser.parse_args()

    files = args.files if args.files else FILES

    if args.diff:
        diff_mode(files)
    else:
        compare_mode(files)


if __name__ == "__main__":
    main()
