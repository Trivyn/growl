#!/bin/bash
# Growl Benchmark Suite
# Measures: parse time, reasoning time, total time, triple counts
#
# Usage: cd cli/tests && ./benchmark.sh
#   Requires: ./build/growl (run `slop build` first)

set -euo pipefail

GROWL=../build/growl
FIXTURES=fixtures
BENCHMARKS=fixtures/benchmarks

if [ ! -x "$GROWL" ]; then
  echo "Error: $GROWL not found. Run 'slop build' first."
  exit 1
fi

echo "========================================"
echo "  Growl Benchmark Suite"
echo "========================================"
echo ""

# Consistent ontologies — measure performance
for f in \
  "$FIXTURES/empty.ttl" \
  "$FIXTURES/bfo-core.ttl" \
  "$BENCHMARKS/pizza.ttl" \
  "$FIXTURES/CommonCoreOntologiesMerged.ttl" \
  "$BENCHMARKS/Brick.ttl" \
  "$BENCHMARKS/schemaorg.ttl"; do

  if [ ! -f "$f" ]; then
    echo "SKIP: $f not found"
    continue
  fi

  echo "=== $(basename "$f") ==="
  for run in 1 2 3; do
    $GROWL --quiet "$f" 2>&1
  done
  echo ""
done

# Test emit (serialize) on one consistent benchmark
echo "=== Emit test (bfo-core.ttl) ==="
$GROWL --quiet --emit /tmp/bench-out.ttl "$FIXTURES/bfo-core.ttl" 2>&1
echo ""

# Inconsistent ontologies — should detect and report
echo "========================================"
echo "  Inconsistency Detection"
echo "========================================"
echo ""
for f in "$BENCHMARKS"/*-inconsistent.ttl; do
  if [ ! -f "$f" ]; then
    echo "SKIP: no inconsistent files found"
    break
  fi
  echo "--- $(basename "$f") ---"
  $GROWL --quiet "$f" 2>&1 || true
  echo ""
done
