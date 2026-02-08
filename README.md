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

72 of 78 OWL 2 RL rules implemented (92% coverage). See [detailed coverage table](#owl-2-rl-rule-coverage) below.

| Table | Rules | Implemented | Description |
|-------|-------|-------------|-------------|
| Table 4 | eq-* | 9/9 | Equality semantics (sameAs, differentFrom) |
| Table 5 | prp-* | 19/20 | Property axioms (domain, range, inverse, transitivity, chains, keys) |
| Table 6 | cls-* | 17/19 | Class expressions (intersectionOf, unionOf, oneOf, qualified cardinality) |
| Table 7 | cax-* | 5/5 | Class axioms (subClassOf, equivalentClass, disjointWith) |
| Table 8 | dt-* | 2/5 | Datatype validation |
| Table 9 | scm-* | 20/20 | Schema vocabulary (class/property hierarchies) |

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

The `--fast` flag skips schema vocabulary rules (scm-\*), datatype rules (dt-type1, dt-not-type), consistency checks (cax-dw, cax-adc, prp-asyp, prp-irp, prp-pdw, prp-adp, prp-npa1, prp-npa2, eq-diff1/2/3, cls-nothing2, cls-com, cls-maxqc1/2), and cardinality rules (cls-maxc1/2, cls-maxqc3/4). This matches the inference depth of reasoners like `reasonable` that skip schema closure. Most published ontologies already include explicit subClassOf/subPropertyOf chains, making schema closure unnecessary for practical use.

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

## OWL 2 RL Rule Coverage

Detailed per-rule coverage against the [W3C OWL 2 RL specification](https://www.w3.org/TR/owl2-profiles/#Reasoning_in_OWL_2_RL_and_RDF_Graphs_using_Rules).

### Table 4 — Equality (9/9)

| Rule | Status | Notes |
|------|--------|-------|
| eq-ref | ✅ | Reflexivity of equality |
| eq-sym | ✅ | Symmetry of owl:sameAs |
| eq-trans | ✅ | Transitivity of owl:sameAs |
| eq-rep-s | ✅ | Replace subject via owl:sameAs |
| eq-rep-p | ✅ | Replace predicate via owl:sameAs |
| eq-rep-o | ✅ | Replace object via owl:sameAs |
| eq-diff1 | ✅ | owl:differentFrom is symmetric |
| eq-diff2 | ✅ | Inconsistency: sameAs and differentFrom |
| eq-diff3 | ✅ | Inconsistency: members of AllDifferent are sameAs |

### Table 5 — Property Axioms (19/20)

| Rule | Status | Notes |
|------|--------|-------|
| prp-ap | ❌ | Annotation properties — no useful inference |
| prp-dom | ✅ | rdfs:domain inference |
| prp-rng | ✅ | rdfs:range inference |
| prp-fp | ✅ | Functional property → owl:sameAs |
| prp-ifp | ✅ | Inverse functional property → owl:sameAs |
| prp-irp | ✅ | Irreflexive property inconsistency |
| prp-symp | ✅ | Symmetric property inference |
| prp-asyp | ✅ | Asymmetric property inconsistency |
| prp-trp | ✅ | Transitive property inference |
| prp-spo1 | ✅ | SubPropertyOf inference |
| prp-spo2 | ✅ | Property chain axiom inference |
| prp-eqp1 | ✅ | EquivalentProperty forward |
| prp-eqp2 | ✅ | EquivalentProperty reverse |
| prp-pdw | ✅ | PropertyDisjointWith inconsistency |
| prp-adp | ✅ | AllDisjointProperties inconsistency |
| prp-inv1 | ✅ | InverseOf forward |
| prp-inv2 | ✅ | InverseOf reverse |
| prp-key | ✅ | hasKey → owl:sameAs inference |
| prp-npa1 | ✅ | Negative property assertion (named individual) inconsistency |
| prp-npa2 | ✅ | Negative property assertion (literal) inconsistency |

### Table 6 — Class Expressions (17/19)

| Rule | Status | Notes |
|------|--------|-------|
| cls-thing | ❌ | Skipped — triple explosion (every resource gets type owl:Thing) |
| cls-nothing1 | ❌ | Skipped — scm-cls already handles |
| cls-nothing2 | ✅ | Inconsistency: member of owl:Nothing |
| cls-int1 | ✅ | IntersectionOf: member of all → member of intersection |
| cls-int2 | ✅ | IntersectionOf: member of intersection → member of all |
| cls-uni | ✅ | UnionOf: member of component → member of union |
| cls-com | ✅ | ComplementOf inconsistency |
| cls-svf1 | ✅ | SomeValuesFrom (stub — existential, limited in RL) |
| cls-svf2 | ✅ | SomeValuesFrom with owl:Thing |
| cls-avf | ✅ | AllValuesFrom inference |
| cls-hv1 | ✅ | HasValue → type inference |
| cls-hv2 | ✅ | HasValue → property inference |
| cls-maxc1 | ✅ | MaxCardinality 0 (constraint only) |
| cls-maxc2 | ✅ | MaxCardinality 1 → owl:sameAs |
| cls-maxqc1 | ✅ | MaxQualifiedCardinality 0 inconsistency (with onClass) |
| cls-maxqc2 | ✅ | MaxQualifiedCardinality 0 inconsistency (owl:Thing) |
| cls-maxqc3 | ✅ | MaxQualifiedCardinality 1 → owl:sameAs (with onClass) |
| cls-maxqc4 | ✅ | MaxQualifiedCardinality 1 → owl:sameAs (owl:Thing) |
| cls-oo | ✅ | OneOf enumeration |

### Table 7 — Class Axioms (5/5)

| Rule | Status | Notes |
|------|--------|-------|
| cax-sco | ✅ | SubClassOf inference |
| cax-eqc1 | ✅ | EquivalentClass forward |
| cax-eqc2 | ✅ | EquivalentClass reverse |
| cax-dw | ✅ | DisjointWith inconsistency |
| cax-adc | ✅ | AllDisjointClasses inconsistency |

### Table 8 — Datatypes (2/5)

| Rule | Status | Notes |
|------|--------|-------|
| dt-type1 | ✅ | Assert recognized datatypes as rdfs:Datatype |
| dt-type2 | ❌ | Literal typing — non-standard literal-as-subject triples |
| dt-eq | ❌ | Datatype equality — even owlrl skips |
| dt-diff | ❌ | Datatype inequality — even owlrl skips |
| dt-not-type | ✅ | Detect invalid lexical forms (e.g. "abc"^^xsd:integer) |

### Table 9 — Schema Vocabulary (20/20)

| Rule | Status | Notes |
|------|--------|-------|
| scm-cls | ✅ | Class is subclass of itself, owl:Thing; superclass of owl:Nothing |
| scm-sco | ✅ | SubClassOf transitivity |
| scm-eqc1 | ✅ | EquivalentClass → mutual subClassOf |
| scm-eqc2 | ✅ | Mutual subClassOf → equivalentClass |
| scm-op | ✅ | ObjectProperty schema axioms |
| scm-dp | ✅ | DatatypeProperty schema axioms |
| scm-spo | ✅ | SubPropertyOf transitivity |
| scm-eqp1 | ✅ | EquivalentProperty → mutual subPropertyOf |
| scm-eqp2 | ✅ | Mutual subPropertyOf → equivalentProperty |
| scm-dom1 | ✅ | Domain propagation through subClassOf |
| scm-dom2 | ✅ | Domain propagation through subPropertyOf |
| scm-rng1 | ✅ | Range propagation through subClassOf |
| scm-rng2 | ✅ | Range propagation through subPropertyOf |
| scm-hv | ✅ | HasValue + subClassOf interaction |
| scm-svf1 | ✅ | SomeValuesFrom + subClassOf interaction |
| scm-svf2 | ✅ | SomeValuesFrom + subPropertyOf interaction |
| scm-avf1 | ✅ | AllValuesFrom + subClassOf interaction |
| scm-avf2 | ✅ | AllValuesFrom + subPropertyOf interaction |
| scm-int | ✅ | IntersectionOf → subClassOf components |
| scm-uni | ✅ | UnionOf → components subClassOf union |

## License

Apache License 2.0 - see [LICENSE](LICENSE) for details.
