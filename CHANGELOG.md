# Changelog

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
