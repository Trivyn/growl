# Rust Bindings for Growl

Safe Rust wrapper over the [Growl](../) OWL 2 RL reasoner. Provides RAII arena management, typed RDF terms, and a high-level API for ontology reasoning.

## Prerequisites

A C compiler is required. The `cc` crate handles compilation automatically — no SLOP toolchain is needed since pre-transpiled C sources are included in `csrc/`.

## Installation

The crate is not yet published on crates.io. Add it as a path dependency:

```toml
[dependencies]
growl = { path = "rust" }
```

## Quick Start

```rust
use growl::{Arena, IndexedGraph, ReasonerResult, Term, reason};

let arena = Arena::new(4 * 1024 * 1024);
let mut graph = IndexedGraph::new(&arena);

// Create terms
let dog = arena.make_iri("http://example.org/Dog");
let animal = arena.make_iri("http://example.org/Animal");
let fido = arena.make_iri("http://example.org/fido");
let rdf_type = arena.make_iri("http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
let rdfs_subclass = arena.make_iri("http://www.w3.org/2000/01/rdf-schema#subClassOf");
let owl_class = arena.make_iri("http://www.w3.org/2002/07/owl#Class");

// Build graph
graph.add_triple(arena.make_triple(dog, rdfs_subclass, animal));
graph.add_triple(arena.make_triple(fido, rdf_type, dog));
graph.add_triple(arena.make_triple(dog, rdf_type, owl_class));
graph.add_triple(arena.make_triple(animal, rdf_type, owl_class));

// Run the reasoner
let result = reason(&arena, &graph);
match result {
    ReasonerResult::Success { graph: result_graph, inferred_count, .. } => {
        println!("Inferred {} triples", inferred_count);

        // Check what fido was inferred to be
        let types = growl::get_types(&arena, &result_graph, fido);
        for t in &types {
            println!("fido rdf:type {}", t);
        }
    }
    ReasonerResult::Inconsistent { reason, witnesses } => {
        println!("Inconsistent: {}", reason);
        for w in &witnesses {
            println!("  witness: {}", w);
        }
    }
}
```

## API Reference

### `Arena`

RAII wrapper around the C arena allocator. All terms and graphs are allocated from an arena.

```rust
let arena = Arena::new(4 * 1024 * 1024);    // 4 MB
let arena = Arena::with_default_capacity();  // 1 MB

// Create RDF terms
let iri = arena.make_iri("http://example.org/x");
let blank = arena.make_blank(1);
let lit = arena.make_literal("hello", None, Some("en"));
let triple = arena.make_triple(iri, iri, lit);
```

### `IndexedGraph`

An indexed RDF graph with SPO/PSO/OSP lookups.

```rust
let mut graph = IndexedGraph::new(&arena);

// Add triples (raw FFI terms)
graph.add_triple(arena.make_triple(s, p, o));

// Add triples (safe Term values)
graph.add(&Term::Iri("http://example.org/s"),
          &Term::Iri("http://example.org/p"),
          &Term::Iri("http://example.org/o"));

graph.size();                          // number of triples
graph.contains_triple(triple);         // exact lookup

// Pattern matching — None means wildcard
graph.match_pattern(None, Some(p), Some(o));  // all triples with given p and o

// Convenience accessors
graph.objects(subject, predicate);     // Vec<Term>
graph.subjects(predicate, object);     // Vec<Term>
```

### `Term`

Safe, read-side view of an RDF term. Lifetime-tied to the arena's string data.

```rust
enum Term<'a> {
    Iri(&'a str),
    Blank(i64),
    Literal { value: &'a str, datatype: Option<&'a str>, lang: Option<&'a str> },
}

// Convert from FFI
let term = Term::from_ffi(raw_term);

// Display formats: <http://...>, _:b42, "hello"@en
println!("{}", term);
```

### `Triple`

Safe, read-side view of an RDF triple.

```rust
struct Triple<'a> {
    pub subject: Term<'a>,
    pub predicate: Term<'a>,
    pub object: Term<'a>,
}

let triple = Triple::from_ffi(raw_triple);
println!("{}", triple);  // <s> <p> <o> .
```

### `ReasonerConfig`

Builder-pattern configuration for the reasoner.

```rust
let config = ReasonerConfig::new()
    .worker_count(4)      // parallel workers (default: 4)
    .channel_buffer(256)  // message buffer size (default: 256)
    .max_iterations(1000) // iteration limit (default: 1000)
    .verbose(false)       // per-iteration timing (default: true)
    .fast(true)           // skip schema rules (default: false)
    .complete(false);     // enable cls-thing & prp-ap (default: false)
```

### `ReasonerResult`

```rust
enum ReasonerResult<'a> {
    Success { graph: IndexedGraph<'a>, inferred_count: i64, iterations: i64 },
    Inconsistent { reason: String, witnesses: Vec<Triple<'a>> },
}
```

### Free Functions

```rust
// Run with default config
reason(&arena, &graph) -> ReasonerResult

// Run with custom config
reason_with_config(&arena, &graph, &config) -> ReasonerResult

// Quick consistency check (no graph returned)
is_consistent(&arena, &graph) -> bool

// Query helpers
get_types(&arena, &graph, individual) -> Vec<Term>
get_same_as(&arena, &graph, individual) -> Vec<Term>
```

## Thread Safety

The C runtime uses a global intern pool (`slop_global_intern_pool`) that is **not thread-safe**. The `Arena` type is `!Send + !Sync` to prevent accidental cross-thread usage.

If you need to call into Growl from multiple threads (e.g., in tests), serialize access with a `Mutex`:

```rust
use std::sync::Mutex;

static C_LOCK: Mutex<()> = Mutex::new(());

fn do_reasoning() {
    let _lock = C_LOCK.lock().unwrap();
    let arena = Arena::new(1024 * 1024);
    // ... use arena, graph, reason() ...
}
```

## Running Tests

```bash
cd rust && cargo test
```

The build script (`build.rs`) compiles all C sources automatically via the `cc` crate.

## License

Apache License 2.0 — see [LICENSE](../LICENSE).
