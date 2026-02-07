# Growl

An OWL 2 RL reasoner with formally verified inference rules.

## Overview

Growl implements the [OWL 2 RL profile](https://www.w3.org/TR/owl2-profiles/#OWL_2_RL) inference rules with Z3-verified contracts. Written in SLOP, it compiles to efficient C code while guaranteeing correctness through formal verification.

## Features

- **Formally Verified**: All inference rules have Z3-verified pre/post conditions
- **OWL 2 RL Compliant**: Implements W3C specification tables 4-9
- **Parallel Execution**: Fork-join parallel semi-naive evaluation
- **Inconsistency Detection**: Reports violations with witness triples

## Rule Coverage

| Table | Rules | Description |
|-------|-------|-------------|
| Table 4 | eq-* | Equality semantics (sameAs, differentFrom) |
| Table 5 | prp-* | Property axioms (domain, range, inverse, transitivity) |
| Table 6 | cls-* | Class expressions (intersectionOf, unionOf, oneOf) |
| Table 7 | cax-* | Class axioms (subClassOf, equivalentClass, disjointWith) |
| Table 8 | scm-* | Schema vocabulary (class/property hierarchies) |

## API

```slop
;; Run reasoning with default configuration
(reason arena graph) -> ReasonerResult

;; Run with custom configuration
(reason-with-config arena graph config) -> ReasonerResult

;; Quick consistency check
(is-consistent arena graph) -> Bool

;; Query results
(get-types arena graph individual) -> (List Term)
(get-same-as arena graph individual) -> (List Term)
```

## Configuration

```slop
(record ReasonerConfig
  (worker-count Int)      ;; Number of parallel workers (default: 4)
  (channel-buffer Int)    ;; Message buffer size (default: 256)
  (max-iterations Int)    ;; Iteration limit (default: 1000)
  (verbose Bool)          ;; Print per-iteration timing (default: true)
  (fast Bool))            ;; Skip schema rules & checks (default: false)
```

## CLI Usage

```bash
growl [options] <file.ttl>

Options:
  -h, --help       Show help message
  -q, --quiet      Only print failures and inconsistencies
  -f, --fast       Skip schema rules and consistency checks
  -o, --emit FILE  Write materialized graph to TTL file
```

### Fast Mode

The `--fast` flag skips schema vocabulary rules (scm-\*), consistency checks (cax-dw, cax-adc, prp-asyp, prp-irp, prp-pdw, eq-diff1/2/3, cls-nothing2, cls-com), and cardinality rules (cls-maxc1/2). This matches the inference depth of reasoners like `reasonable` that skip schema closure. Most published ontologies already include explicit subClassOf/subPropertyOf chains, making schema closure unnecessary for practical use.

## Building

```bash
slop build src/growl.slop
```

### Building from C

Pre-transpiled C sources are included in `csrc/`, so you can build with just a C compiler — no SLOP toolchain required.

```bash
make            # build cli → build/growl
make release    # optimized build (-O3, NDEBUG)
make test       # build and run tests
make benchmark  # run benchmarks
```

## Verification

```bash
slop verify src/growl.slop
slop verify src/rules/*.slop
```

## License

Apache License 2.0 - see [LICENSE](LICENSE) for details.
