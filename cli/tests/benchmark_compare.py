#!/usr/bin/env python3
"""Reasoner comparison: OWL-RL (ground truth) vs Growl.

OWL-RL is the W3C reference implementation for OWL 2 RL/RDF rules.
It serves as ground truth for expected inference counts.

Usage: cd cli/tests && python benchmark_compare.py
  Requires: pip install owlrl rdflib
  Requires: growl CLI built at ../build/growl
"""

import os
import subprocess
import sys
import time
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


def run_owlrl(path):
    """Run OWL-RL (W3C reference) on a TTL file. Returns (input, inferred, time_s)."""
    g = rdflib.Graph()
    g.parse(path, format="turtle")
    input_count = len(g)

    if input_count > OWLRL_SKIP_THRESHOLD:
        return input_count, None, None

    t0 = time.perf_counter()
    DeductiveClosure(OWLRL_Semantics).expand(g)
    elapsed = time.perf_counter() - t0

    total = len(g)
    inferred = total - input_count
    return input_count, inferred, elapsed


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


def run_growl(path, fast=False):
    """Run growl on a TTL file. Returns (input, output, median_time_s)."""
    cmd = [GROWL, "--quiet"]
    if fast:
        cmd.append("--fast")
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


def main():
    if not os.path.exists(GROWL):
        print(f"Error: growl binary not found at {GROWL}")
        print("Build it first: cd cli && slop build")
        sys.exit(1)

    print("=" * 72)
    print("  Reasoner Comparison: OWL-RL (ground truth) vs Growl")
    print("=" * 72)
    print()

    for path in FILES:
        name = path.split("/")[-1]
        print(f"--- {name} ---")

        # OWL-RL
        print("  Running OWL-RL...", end="", flush=True)
        owlrl_input, owlrl_inferred, owlrl_time = run_owlrl(path)
        if owlrl_inferred is None:
            print(f" SKIPPED (>{OWLRL_SKIP_THRESHOLD} input triples)")
        else:
            print(f" done ({owlrl_time:.1f}s)")

        # Growl (fast)
        print("  Running Growl --fast...", end="", flush=True)
        growl_input, growl_fast_output, growl_fast_time = run_growl(path, fast=True)
        growl_fast_inferred = (growl_fast_output - growl_input) if growl_fast_output is not None else None
        print(f" done ({fmt_time(growl_fast_time)})")

        # Growl (full)
        print("  Running Growl (full)...", end="", flush=True)
        _, growl_full_output, growl_full_time = run_growl(path, fast=False)
        growl_full_inferred = (growl_full_output - growl_input) if growl_full_output is not None else None
        print(f" done ({fmt_time(growl_full_time)})")

        # Summary table
        print()
        print(f"  {'':20s} {'Input':>8s}  {'Inferred':>8s}  {'Total':>8s}  {'Time':>8s}")
        print(f"  {'':20s} {'-----':>8s}  {'--------':>8s}  {'-----':>8s}  {'----':>8s}")

        owlrl_total = (owlrl_input + owlrl_inferred) if owlrl_inferred is not None else None
        print(f"  {'OWL-RL (ref)':20s} {fmt_count(owlrl_input):>8s}  {fmt_count(owlrl_inferred):>8s}  {fmt_count(owlrl_total):>8s}  {fmt_time(owlrl_time):>8s}")

        print(f"  {'Growl (full)':20s} {fmt_count(growl_input):>8s}  {fmt_count(growl_full_inferred):>8s}  {fmt_count(growl_full_output):>8s}  {fmt_time(growl_full_time):>8s}")
        print(f"  {'Growl (fast)':20s} {fmt_count(growl_input):>8s}  {fmt_count(growl_fast_inferred):>8s}  {fmt_count(growl_fast_output):>8s}  {fmt_time(growl_fast_time):>8s}")

        # Deltas
        if owlrl_inferred is not None:
            print()
            if growl_full_inferred is not None and owlrl_inferred > 0:
                diff = growl_full_inferred - owlrl_inferred
                sign = "+" if diff > 0 else ""
                print(f"  Growl full vs OWL-RL: {sign}{diff} inferred ({sign}{diff/owlrl_inferred*100:.1f}%)")
            if growl_fast_inferred is not None and owlrl_inferred > 0:
                diff = growl_fast_inferred - owlrl_inferred
                sign = "+" if diff > 0 else ""
                print(f"  Growl fast vs OWL-RL: {sign}{diff} inferred ({sign}{diff/owlrl_inferred*100:.1f}%)")

        print()


if __name__ == "__main__":
    main()
