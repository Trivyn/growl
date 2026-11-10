# Changelog

## 0.10.2 — 2026-11-10

Built on slop-rdf 0.6.2. The Rust crate pins slop-rdf-sys =0.6.2 (exact, as before) and
slop-std-sys stays =0.5.0. The CLI and libgrowl.a are regenerated from slop-rdf 0.6.2 with SLOP
0.5.3.

### Fixed

- **Turtle numeric and boolean literals.** `--emit` writes an `xsd:integer`, `xsd:decimal`,
  `xsd:double` or `xsd:boolean` literal in bare shorthand only when its lexical form is valid
  Turtle for that shorthand. Any other value is written as a quoted typed literal, so the output
  always re-parses to the same term.
- The generated C evaluates each `print` argument once; before, the string expression was
  evaluated twice.

No API change: growl.h, the Rust API and the FFI layouts are unchanged.

## 0.10.1 — 2026-10-27

Built on slop-rdf 0.6.1. The Rust crate pins slop-rdf-sys =0.6.1 (exact, as before), so growl
resolves alongside snarl-shacl 0.7.1 and howl-reasoner 0.7.1: slop-rdf-sys carries a `links` key,
so Cargo allows only one version of it per dependency graph. The CLI and libgrowl.a are
regenerated from slop-rdf 0.6.1 too.

### Fixed

- **Turtle prefixed names.** Local parts may now contain `\`-escapes and `%XX`, and a malformed `%`
  or `\` escape is reported as a parse error. `--emit` writes `prefix:local` only when the local
  part is valid Turtle.

No API change: growl.h, the Rust API and the FFI layouts are unchanged.
