# Growl

An OWL 2 RL reasoner with Z3-verified inference rules.

## Overview

Growl implements the [OWL 2 RL profile](https://www.w3.org/TR/owl2-profiles/#OWL_2_RL) inference rules with Z3-verified contracts on every inference function. Written in SLOP, it compiles to efficient C code while using SMT solving to prove properties about the inference logic.

## Features

- **Z3-Verified Contracts**: Every inference function has machine-checked pre/postconditions; soundness properties prove each output triple is justified by a delta/graph premise (see [Verification](#verification) for scope)
- **OWL 2 RL Compliant**: Implements W3C specification tables 4-9
- **Parallel Execution**: Fork-join parallel semi-naive evaluation
- **Inconsistency Detection**: Reports violations with witness triples

## Rule Coverage

76 of 78 OWL 2 RL rules implemented (97% coverage). See [detailed coverage table](#owl-2-rl-rule-coverage) below.

| Table | Rules | Implemented | Description |
|-------|-------|-------------|-------------|
| Table 4 | eq-* | 9/9 | Equality semantics (sameAs, differentFrom) |
| Table 5 | prp-* | 20/20 | Property axioms (domain, range, inverse, transitivity, chains, keys) |
| Table 6 | cls-* | 19/19 | Class expressions (intersectionOf, unionOf, oneOf, qualified cardinality) |
| Table 7 | cax-* | 5/5 | Class axioms (subClassOf, equivalentClass, disjointWith) |
| Table 8 | dt-* | 3/5 | Datatype validation |
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
  (fast Bool)             ;; Skip schema rules & checks (default: false)
  (complete Bool))        ;; Enable cls-thing & prp-ap (default: false)
```

## CLI Usage

```bash
growl [options] <file.ttl>

Options:
  -h, --help       Show help message
  -q, --quiet      Only print failures and inconsistencies
  -f, --fast       Skip schema rules and consistency checks
  -c, --complete   Enable cls-thing and prp-ap for spec completeness
  -o, --emit FILE  Write materialized graph to TTL file
```

### Complete Mode

The `--complete` flag enables axiom rules that are skipped by default for performance:

- **cls-thing**: Asserts `owl:Thing rdf:type owl:Class`
- **cls-nothing1**: Asserts `owl:Nothing rdf:type owl:Class`
- **prp-ap**: Asserts standard annotation properties (rdfs:label, rdfs:comment, etc.) as `owl:AnnotationProperty`
- **dt-type2**: Asserts `literal rdf:type datatype` for every typed literal with a supported datatype

These rules are spec-correct but produce triples with zero practical inference value. Use `--complete` for conformance testing against other reasoners like owlrl.

### Fast Mode

The `--fast` flag skips schema vocabulary rules (scm-\*), datatype rules (dt-type1, dt-not-type), equality-difference checks (eq-diff1/2/3), eq-ref, and cardinality rules (cls-maxc1/2, cls-maxqc1-4). Consistency checks (cax-dw, cax-adc, prp-asyp, prp-irp, prp-pdw, prp-adp, prp-npa1/2, cls-nothing2, cls-com) still run in fast mode, matching the coverage of reasoners like [reasonable](https://github.com/gtfierro/reasonable). Most published ontologies already include explicit subClassOf/subPropertyOf chains, making schema closure unnecessary for practical use.

## Building

```bash
slop build src/growl.slop
```

### Building from C

Pre-transpiled C sources are included in `csrc/`, so you can build with just a C compiler — no SLOP toolchain required.

```bash
make            # build cli → build/growl
make lib        # build static library → build/libgrowl.a
make release    # optimized build (-O3, NDEBUG)
make test       # build and run tests
make benchmark  # run benchmarks
```

### Rust Bindings

Safe Rust bindings are available in the [`rust/`](rust/) directory. See [`rust/README.md`](rust/README.md) for usage instructions.

## Verification

```bash
slop verify              # verify all files in [verify].sources
slop verify -v           # verbose — shows per-function results
```

Growl uses `slop verify`, which encodes contracts into Z3 SMT formulas and proves them with weakest-precondition calculus. 101 function-level contracts are verified across the codebase.

**What is proven:**

- **Soundness** (`@property soundness`): For every output triple, there exists a delta triple justifying it — proving the reasoner never fabricates conclusions from nothing. Covers 55 of 77 inference functions, including all high-value rules (cax-sco, prp-dom/rng, eq-ref/sym, cls-hv1/hv2, etc.).
- **Completeness** (`@property completeness`): For certain rules (eq-sym, scm-eqc1/eqc2, prp-symp, scm-eqp1/eqp2), every applicable delta triple produces the expected output — proving the reasoner doesn't miss inferences. 8 functions.
- **Novelty** (`@property novelty`): Every output triple is new — not already present in the graph. Proves the rule engine never wastes work emitting redundant inferences. Covers cls-maxc2, cls-maxqc3, cls-maxqc4 (3 functions).
- **Postconditions** (`@post`): Predicate constraints (e.g. all outputs have `rdf:type` as predicate), witness counts on inconsistency reports, iteration numbering, and result bounds.
- **Preconditions** (`@pre`): Graph size non-negativity, valid input constraints.

**What is not proven:**

- Soundness for deeply nested callback functions (cls-maxc2/maxqc3/4) that only query the full graph — these don't iterate delta, so the standard delta-sourcing property doesn't apply. They have `@property novelty` and `@post` predicate checks instead.
- Full join semantics — soundness contracts prove delta-sourcing (every output links to a delta triple) but don't fully encode the multi-way join conditions of rules like cls-int1 (which requires checking all intersection components).
- Termination of the fixed-point loop is not proven (semi-naive evaluation over finite graphs terminates in practice but isn't formally verified).
- Memory safety of the generated C code is not verified (relies on arena allocation patterns).

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

### Table 5 — Property Axioms (20/20)

| Rule | Status | Notes |
|------|--------|-------|
| prp-ap | ✅ | Annotation property declarations (behind `--complete` flag) |
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

### Table 6 — Class Expressions (19/19)

| Rule | Status | Notes |
|------|--------|-------|
| cls-thing | ✅ | owl:Thing rdf:type owl:Class (behind `--complete` flag) |
| cls-nothing1 | ✅ | owl:Nothing rdf:type owl:Class (behind `--complete` flag) |
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

### Table 8 — Datatypes (3/5)

| Rule | Status | Notes |
|------|--------|-------|
| dt-type1 | ✅ | Assert all OWL 2 datatypes as rdfs:Datatype (36 types) |
| dt-type2 | ✅ | Literal typing — asserts `literal rdf:type datatype` (behind `--complete` flag) |
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
