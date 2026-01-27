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
  (max-iterations Int))   ;; Iteration limit (default: 1000)
```

## Building

```bash
slop build src/growl.slop
```

## Verification

```bash
slop verify src/growl.slop
slop verify src/rules/*.slop
```

## License

Apache License 2.0 - see [LICENSE](LICENSE) for details.
