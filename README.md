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

;; Annotation filtering (preprocessing)
(collect-annotation-properties arena graph) -> (Set Term)
(graph-to-indexed arena graph annot-set) -> IndexedGraph
(indexed-to-graph arena indexed-graph) -> Graph
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

## Annotation Filtering

Growl provides annotation filtering as a preprocessing step. Annotation properties have no semantic effect under OWL 2 Direct Semantics — they carry human-readable metadata (labels, comments, descriptions) that cannot trigger any inference rule. Removing them reduces the input graph size without affecting reasoning results.

The following properties are filtered by default:

- **OWL/RDFS** (9): `rdfs:label`, `rdfs:comment`, `rdfs:seeAlso`, `rdfs:isDefinedBy`, `owl:deprecated`, `owl:versionInfo`, `owl:priorVersion`, `owl:backwardCompatibleWith`, `owl:incompatibleWith`
- **SKOS** (10): `skos:prefLabel`, `skos:altLabel`, `skos:hiddenLabel`, `skos:definition`, `skos:note`, `skos:scopeNote`, `skos:example`, `skos:historyNote`, `skos:editorialNote`, `skos:changeNote`
- **Dublin Core** (8): `dc:title`, `dc:creator`, `dc:subject`, `dc:description`, `dcterms:title`, `dcterms:creator`, `dcterms:description`, `dcterms:abstract`

Additionally, any property declared as `owl:AnnotationProperty` in the input graph is filtered. This is significant for large ontologies — for example, CCO drops from ~13.6K to ~6K input triples.

### Library Usage

```slop
;; Build annotation property set from parsed graph
(let ((annot-set (collect-annotation-properties arena g))
      (ig (graph-to-indexed arena g annot-set)))
  ;; Run reasoning on filtered graph
  (match (reason arena ig)
    ((reason-success s)
      ;; Convert back for serialization, re-adding annotations
      (let ((mut out-ig (. s graph)))
        (for-each (t (. g triples))
          (when (set-has annot-set (. t predicate))
            (set! out-ig (indexed-graph-add arena out-ig t))))
        (indexed-to-graph arena out-ig)))
    ((reason-inconsistent _) ...)))
```

### CLI

The CLI applies annotation filtering automatically. When `--emit` is used, filtered annotation triples are re-added to the output so no data is lost in the materialized graph.

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

## Benchmarks

Compared against [OWL-RL](https://github.com/RDFLib/OWL-RL) (Python reference implementation, used as ground truth) and [Reasonable](https://github.com/gtfierro/reasonable) (Rust) on 5 real-world ontologies. Growl filters annotation triples before reasoning (see [Annotation Filtering](#annotation-filtering)), so its effective input is smaller — the "Input" column shows the raw triple count that OWL-RL and Reasonable see.

### Performance

| Ontology | Input | OWL-RL | Reasonable | Growl --complete | Growl | Growl --fast |
|---|---|---|---|---|---|---|
| BFO | 1,014 | 583ms | 35ms | 33ms | 21ms | 3ms |
| Pizza | 1,944 | 2.2s | 114ms | 229ms | 164ms | 52ms |
| CCO | 13,649 | 18.4s | 737ms | 3.1s | 2.8s | 434ms |
| Schema.org | 17,823 | 8.3s | 132ms | 691ms | 566ms | 333ms |
| Brick | 53,960 | 33.9s | 286ms | 4.6s | 4.0s | 2.3s |

### Accuracy (inferred triples vs OWL-RL reference)

| Ontology | OWL-RL (ref) | Reasonable | Growl --complete | Growl | Growl --fast |
|---|---|---|---|---|---|
| BFO | 2,186 | +91.9% | -0.7% | -17.1% | -83.7% |
| Pizza | 8,005 | +29.1% | -1.9% | -30.6% | -95.2% |
| CCO | 52,363 | -11.4% | +2.7% | -1.8% | -76.0% |
| Schema.org | 26,682 | +15.9% | +0.6% | -0.6% | -40.5% |
| Brick | 39,493 | +81.9% | -0.1% | -23.9% | -69.5% |

**Modes**: `--complete` enables all spec rules (cls-thing, prp-ap, dt-type2) for closest OWL-RL parity. Default Growl skips those practically inert rules. `--fast` targets the same rule coverage as Reasonable (skips schema rules, datatypes, eq-ref, cardinality), making Growl --fast vs Reasonable an apples-to-apples comparison.

## Verification

```bash
slop verify              # verify all files in [verify].sources
slop verify -v           # verbose — shows per-function results
```

Growl uses `slop verify`, which encodes contracts into Z3 SMT formulas and proves them with weakest-precondition calculus. 104 function-level contracts are verified across the codebase.

**What is proven:**

- **Soundness** (`@property soundness`): For every output triple, there exists a delta triple justifying it — proving the reasoner never fabricates conclusions from nothing. Covers 56 of 77 inference functions, including all high-value rules (cax-sco, prp-dom/rng, eq-ref/sym, cls-hv1/hv2, etc.).
- **Completeness** (`@property completeness`): For certain rules (eq-sym/trans, prp-symp, scm-cls, scm-eqc1/eqc2, scm-eqc-mutual, scm-eqp1/eqp2, scm-eqp-mutual, scm-op, scm-dp), every applicable delta triple produces the expected output — proving the reasoner doesn't miss inferences. 12 functions.
- **Novelty** (`@property novelty`): Every output triple is new — not already present in the graph. Proves the rule engine never wastes work emitting redundant inferences. Covers cls-maxc2, cls-maxqc3, cls-maxqc4, and transitive-closure (4 functions).
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
