//! Safe Rust bindings for the Growl OWL 2 RL reasoner.
//!
//! # Example
//! ```no_run
//! use growl::{Arena, IndexedGraph, Term, reason};
//!
//! let arena = Arena::new(1024 * 1024);
//! let mut graph = IndexedGraph::new(&arena);
//!
//! let dog = arena.make_iri("http://example.org/Dog");
//! let animal = arena.make_iri("http://example.org/Animal");
//! let rdf_type = arena.make_iri("http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
//! let rdfs_subclass = arena.make_iri("http://www.w3.org/2000/01/rdf-schema#subClassOf");
//! let owl_class = arena.make_iri("http://www.w3.org/2002/07/owl#Class");
//! let fido = arena.make_iri("http://example.org/fido");
//!
//! graph.add_triple(arena.make_triple(dog, rdfs_subclass, animal));
//! graph.add_triple(arena.make_triple(fido, rdf_type, dog));
//! graph.add_triple(arena.make_triple(dog, rdf_type, owl_class));
//! graph.add_triple(arena.make_triple(animal, rdf_type, owl_class));
//!
//! let result = reason(&arena, &graph);
//! ```

pub mod ffi;

use std::os::raw::c_char;

// ---------------------------------------------------------------------------
// Internal helpers
// ---------------------------------------------------------------------------

/// Convert a `SlopString` to a Rust `&str`.
///
/// # Safety
/// The caller must ensure the `SlopString` data pointer is valid and the bytes
/// are valid UTF-8 (or at least that the resulting str is not used in ways
/// that require valid UTF-8 — interned RDF strings should always be valid).
unsafe fn slop_string_to_str<'a>(s: ffi::SlopString) -> &'a str {
    if s.data.is_null() || s.len == 0 {
        return "";
    }
    let bytes = std::slice::from_raw_parts(s.data as *const u8, s.len);
    std::str::from_utf8_unchecked(bytes)
}

/// Convert a Rust `&str` to a `SlopString` by interning it.
///
/// The returned SlopString points to data in the global intern pool,
/// which lives for the duration of the process. This is necessary because
/// `rdf_make_iri` and `rdf_make_literal` store the SlopString pointer
/// directly without copying.
fn str_to_slop_string(s: &str) -> ffi::SlopString {
    unsafe { ffi::growl_intern_string(s.as_ptr() as *const c_char, s.len()) }
}

/// Convert `Option<&str>` to `SlopOptionString`.
fn option_str_to_slop(opt: Option<&str>) -> ffi::SlopOptionString {
    match opt {
        Some(s) => ffi::SlopOptionString {
            has_value: true,
            value: str_to_slop_string(s),
        },
        None => ffi::SlopOptionString {
            has_value: false,
            value: ffi::SlopString {
                len: 0,
                data: std::ptr::null(),
            },
        },
    }
}

/// Convert a `Term` to its FFI representation, using the arena for allocation.
fn term_to_ffi(arena: &Arena, term: &Term) -> ffi::RdfTerm {
    match term {
        Term::Iri(value) => arena.make_iri(value),
        Term::Blank(id) => arena.make_blank(*id),
        Term::Literal {
            value,
            datatype,
            lang,
        } => arena.make_literal(value, *datatype, *lang),
    }
}

/// Build a `SlopOptionRdfTerm` with `has_value = false`.
fn none_term() -> ffi::SlopOptionRdfTerm {
    ffi::SlopOptionRdfTerm {
        has_value: false,
        value: unsafe { std::mem::zeroed() },
    }
}

/// Build a `SlopOptionRdfTerm` with `has_value = true`.
fn some_term(t: ffi::RdfTerm) -> ffi::SlopOptionRdfTerm {
    ffi::SlopOptionRdfTerm {
        has_value: true,
        value: t,
    }
}

/// Convert a `SlopListRdfTerm` to `Vec<Term>`.
unsafe fn ffi_term_list_to_vec(list: ffi::SlopListRdfTerm) -> Vec<Term<'static>> {
    let mut v = Vec::with_capacity(list.len);
    for i in 0..list.len {
        let raw = *list.data.add(i);
        v.push(Term::from_ffi(raw));
    }
    v
}

/// Convert a `SlopListRdfTriple` to `Vec<Triple>`.
unsafe fn ffi_triple_list_to_vec(list: ffi::SlopListRdfTriple) -> Vec<Triple<'static>> {
    let mut v = Vec::with_capacity(list.len);
    for i in 0..list.len {
        let raw = *list.data.add(i);
        v.push(Triple::from_ffi(raw));
    }
    v
}

// ---------------------------------------------------------------------------
// Arena
// ---------------------------------------------------------------------------

/// RAII wrapper around the C arena allocator.
///
/// All RDF terms and graphs created through this arena borrow from it.
/// The arena is freed when dropped.
pub struct Arena {
    ptr: *mut ffi::SlopArena,
    // *mut SlopArena is already !Send + !Sync because raw pointers don't
    // implement Send/Sync. This is the desired behavior since the C arena
    // is not thread-safe from the caller side.
}

impl Arena {
    /// Create a new arena with the given capacity in bytes.
    pub fn new(capacity: usize) -> Self {
        let ptr = unsafe { ffi::growl_arena_new(capacity) };
        assert!(!ptr.is_null(), "growl_arena_new returned NULL");
        Arena { ptr }
    }

    /// Create a new arena with the default capacity (1 MB).
    pub fn with_default_capacity() -> Self {
        Self::new(1024 * 1024)
    }

    /// Get the raw arena pointer (for FFI calls).
    pub fn as_ptr(&self) -> *mut ffi::SlopArena {
        self.ptr
    }

    /// Create an IRI term.
    pub fn make_iri(&self, value: &str) -> ffi::RdfTerm {
        unsafe { ffi::rdf_make_iri(self.ptr, str_to_slop_string(value)) }
    }

    /// Create a blank node term.
    pub fn make_blank(&self, id: i64) -> ffi::RdfTerm {
        unsafe { ffi::rdf_make_blank(self.ptr, id) }
    }

    /// Create a literal term with optional datatype and language tag.
    pub fn make_literal(
        &self,
        value: &str,
        datatype: Option<&str>,
        lang: Option<&str>,
    ) -> ffi::RdfTerm {
        unsafe {
            ffi::rdf_make_literal(
                self.ptr,
                str_to_slop_string(value),
                option_str_to_slop(datatype),
                option_str_to_slop(lang),
            )
        }
    }

    /// Create a triple from three terms.
    pub fn make_triple(
        &self,
        subject: ffi::RdfTerm,
        predicate: ffi::RdfTerm,
        object: ffi::RdfTerm,
    ) -> ffi::RdfTriple {
        unsafe { ffi::rdf_make_triple(self.ptr, subject, predicate, object) }
    }
}

impl Drop for Arena {
    fn drop(&mut self) {
        unsafe {
            ffi::growl_arena_free(self.ptr);
        }
    }
}

// ---------------------------------------------------------------------------
// Term (read-side, safe)
// ---------------------------------------------------------------------------

/// A safe, read-side view of an RDF term.
///
/// The lifetime `'a` is tied to the arena that owns the string data.
/// In practice, interned strings are globally allocated and outlive all arenas,
/// but we use a lifetime parameter for safety.
#[derive(Debug, Clone, PartialEq)]
pub enum Term<'a> {
    Iri(&'a str),
    Blank(i64),
    Literal {
        value: &'a str,
        datatype: Option<&'a str>,
        lang: Option<&'a str>,
    },
}

impl<'a> Term<'a> {
    /// Convert from FFI representation.
    ///
    /// # Safety
    /// The RdfTerm must contain valid pointers into interned string data.
    /// This is always the case for terms produced by the C library.
    pub fn from_ffi(raw: ffi::RdfTerm) -> Term<'a> {
        unsafe {
            match raw.tag {
                ffi::RdfTermTag::Iri => Term::Iri(slop_string_to_str(raw.data.term_iri.value)),
                ffi::RdfTermTag::Blank => Term::Blank(raw.data.term_blank.id),
                ffi::RdfTermTag::Literal => {
                    let lit = raw.data.term_literal;
                    let dt = if lit.datatype.has_value {
                        Some(slop_string_to_str(lit.datatype.value))
                    } else {
                        None
                    };
                    let lang = if lit.lang.has_value {
                        Some(slop_string_to_str(lit.lang.value))
                    } else {
                        None
                    };
                    Term::Literal {
                        value: slop_string_to_str(lit.value),
                        datatype: dt,
                        lang,
                    }
                }
            }
        }
    }
}

impl<'a> std::fmt::Display for Term<'a> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Term::Iri(v) => write!(f, "<{}>", v),
            Term::Blank(id) => write!(f, "_:b{}", id),
            Term::Literal {
                value,
                datatype,
                lang,
            } => {
                write!(f, "\"{}\"", value)?;
                if let Some(dt) = datatype {
                    write!(f, "^^<{}>", dt)?;
                }
                if let Some(l) = lang {
                    write!(f, "@{}", l)?;
                }
                Ok(())
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Triple (read-side, safe)
// ---------------------------------------------------------------------------

/// A safe, read-side view of an RDF triple.
#[derive(Debug, Clone, PartialEq)]
pub struct Triple<'a> {
    pub subject: Term<'a>,
    pub predicate: Term<'a>,
    pub object: Term<'a>,
}

impl<'a> Triple<'a> {
    /// Convert from FFI representation.
    pub fn from_ffi(raw: ffi::RdfTriple) -> Triple<'a> {
        Triple {
            subject: Term::from_ffi(raw.subject),
            predicate: Term::from_ffi(raw.predicate),
            object: Term::from_ffi(raw.object),
        }
    }
}

impl<'a> std::fmt::Display for Triple<'a> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} {} {} .", self.subject, self.predicate, self.object)
    }
}

// ---------------------------------------------------------------------------
// IndexedGraph
// ---------------------------------------------------------------------------

/// An indexed RDF graph backed by the C library's triple index.
///
/// The graph borrows from the arena that was used to create it.
pub struct IndexedGraph<'a> {
    raw: ffi::IndexedGraphFfi,
    arena: &'a Arena,
}

impl<'a> IndexedGraph<'a> {
    /// Create a new, empty indexed graph.
    pub fn new(arena: &'a Arena) -> Self {
        let raw = unsafe { ffi::rdf_indexed_graph_create(arena.as_ptr()) };
        IndexedGraph { raw, arena }
    }

    /// Add a raw FFI triple to the graph.
    pub fn add_triple(&mut self, triple: ffi::RdfTriple) {
        self.raw = unsafe { ffi::rdf_indexed_graph_add(self.arena.as_ptr(), self.raw, triple) };
    }

    /// Add a triple from safe `Term` values.
    pub fn add(&mut self, subject: &Term, predicate: &Term, object: &Term) {
        let s = term_to_ffi(self.arena, subject);
        let p = term_to_ffi(self.arena, predicate);
        let o = term_to_ffi(self.arena, object);
        let triple = self.arena.make_triple(s, p, o);
        self.add_triple(triple);
    }

    /// Check whether the graph contains the given triple.
    pub fn contains_triple(&self, triple: ffi::RdfTriple) -> bool {
        unsafe { ffi::rdf_indexed_graph_contains(self.raw, triple) != 0 }
    }

    /// Return the number of triples in the graph.
    pub fn size(&self) -> i64 {
        unsafe { ffi::rdf_indexed_graph_size(self.raw) }
    }

    /// Match triples by optional subject/predicate/object pattern.
    /// Returns matching triples as a `Vec`.
    pub fn match_pattern(
        &self,
        subject: Option<ffi::RdfTerm>,
        predicate: Option<ffi::RdfTerm>,
        object: Option<ffi::RdfTerm>,
    ) -> Vec<Triple<'a>> {
        let subj = subject.map_or_else(none_term, some_term);
        let pred = predicate.map_or_else(none_term, some_term);
        let obj = object.map_or_else(none_term, some_term);
        unsafe {
            let list =
                ffi::rdf_indexed_graph_match(self.arena.as_ptr(), self.raw, subj, pred, obj);
            ffi_triple_list_to_vec(list)
        }
    }

    /// Get all objects for the given subject and predicate.
    pub fn objects(&self, subject: ffi::RdfTerm, predicate: ffi::RdfTerm) -> Vec<Term<'a>> {
        unsafe {
            let list = ffi::rdf_indexed_graph_objects(self.arena.as_ptr(), self.raw, subject, predicate);
            ffi_term_list_to_vec(list)
        }
    }

    /// Get all subjects for the given predicate and object.
    pub fn subjects(&self, predicate: ffi::RdfTerm, object: ffi::RdfTerm) -> Vec<Term<'a>> {
        unsafe {
            let list = ffi::rdf_indexed_graph_subjects(self.arena.as_ptr(), self.raw, predicate, object);
            ffi_term_list_to_vec(list)
        }
    }

    /// Get the raw FFI graph (for passing to reasoner functions).
    pub fn raw(&self) -> ffi::IndexedGraphFfi {
        self.raw
    }
}

// ---------------------------------------------------------------------------
// ReasonerConfig
// ---------------------------------------------------------------------------

/// Configuration for the OWL 2 RL reasoner.
pub struct ReasonerConfig {
    raw: ffi::ReasonerConfigFfi,
    /// Kept alive so the SlopString pointer in raw.validate_ns stays valid.
    _validate_ns: Option<ffi::SlopString>,
}

impl ReasonerConfig {
    /// Create a new config with default values.
    pub fn new() -> Self {
        let raw = unsafe { ffi::growl_default_config() };
        ReasonerConfig { raw, _validate_ns: None }
    }

    pub fn worker_count(mut self, n: u8) -> Self {
        self.raw.worker_count = n;
        self
    }

    pub fn channel_buffer(mut self, n: u16) -> Self {
        self.raw.channel_buffer = n;
        self
    }

    pub fn max_iterations(mut self, n: u16) -> Self {
        self.raw.max_iterations = n;
        self
    }

    pub fn verbose(mut self, v: bool) -> Self {
        self.raw.verbose = v as u8;
        self
    }

    pub fn fast(mut self, v: bool) -> Self {
        self.raw.fast = v as u8;
        self
    }

    pub fn complete(mut self, v: bool) -> Self {
        self.raw.complete = v as u8;
        self
    }

    pub fn validate(mut self, v: bool) -> Self {
        self.raw.validate = v as u8;
        self
    }

    /// Set the namespace prefix filter for validate mode.
    ///
    /// When non-empty, only entities whose IRI starts with this prefix
    /// will have synthetic instances injected during validation.
    /// Empty string (default) means validate all entities.
    pub fn validate_ns(mut self, prefix: &str) -> Self {
        let interned = str_to_slop_string(prefix);
        self.raw.validate_ns = interned;
        self._validate_ns = Some(interned);
        self
    }
}

impl Default for ReasonerConfig {
    fn default() -> Self {
        Self::new()
    }
}

// ---------------------------------------------------------------------------
// ReasonerResult
// ---------------------------------------------------------------------------

/// The result of running the reasoner.
pub enum ReasonerResult<'a> {
    /// Reasoning completed successfully.
    Success {
        graph: IndexedGraph<'a>,
        inferred_count: i64,
        iterations: i64,
    },
    /// The ontology is inconsistent.
    Inconsistent {
        reason: String,
        witnesses: Vec<Triple<'a>>,
    },
}

impl<'a> ReasonerResult<'a> {
    /// Convert from the FFI result, borrowing from the given arena.
    unsafe fn from_ffi(raw: ffi::ReasonerResultFfi, arena: &'a Arena) -> Self {
        match raw.tag {
            ffi::ReasonerResultTag::Success => {
                let s = raw.data.reason_success;
                ReasonerResult::Success {
                    graph: IndexedGraph {
                        raw: s.graph,
                        arena,
                    },
                    inferred_count: s.inferred_count,
                    iterations: s.iterations,
                }
            }
            ffi::ReasonerResultTag::Inconsistent => {
                let r = raw.data.reason_inconsistent;
                ReasonerResult::Inconsistent {
                    reason: slop_string_to_str(r.reason).to_string(),
                    witnesses: ffi_triple_list_to_vec(r.witnesses),
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// ValidateResult
// ---------------------------------------------------------------------------

/// Result of TBox validation — ergonomic wrapper for validate mode.
#[derive(Debug)]
pub enum ValidateResult<'a> {
    /// All classes and properties are satisfiable.
    Satisfiable,
    /// An unsatisfiable class or property was detected.
    Unsatisfiable {
        /// The unsatisfiable entity (class or property, resolved from synthetic blank).
        entity: Term<'a>,
        /// Enriched reason string from the engine.
        reason: String,
        /// Witness triples from the inconsistency check.
        witnesses: Vec<Triple<'a>>,
    },
}

/// Owned validation result — no lifetime dependency.
#[derive(Debug)]
pub enum OwnedValidateResult {
    /// All classes and properties are satisfiable.
    Satisfiable,
    /// An unsatisfiable class or property was detected.
    Unsatisfiable {
        /// The unsatisfiable entity (class or property, resolved from synthetic blank).
        entity: OwnedTerm,
        /// Enriched reason string from the engine.
        reason: String,
        /// Witness triples from the inconsistency check.
        witnesses: Vec<OwnedTriple>,
    },
}


/// The 10 property metaclasses used for synthetic property injection.
const PROPERTY_METACLASSES: [&str; 10] = [
    "http://www.w3.org/2002/07/owl#ObjectProperty",
    "http://www.w3.org/2002/07/owl#DatatypeProperty",
    "http://www.w3.org/1999/02/22-rdf-syntax-ns#Property",
    "http://www.w3.org/2002/07/owl#FunctionalProperty",
    "http://www.w3.org/2002/07/owl#InverseFunctionalProperty",
    "http://www.w3.org/2002/07/owl#TransitiveProperty",
    "http://www.w3.org/2002/07/owl#SymmetricProperty",
    "http://www.w3.org/2002/07/owl#AsymmetricProperty",
    "http://www.w3.org/2002/07/owl#ReflexiveProperty",
    "http://www.w3.org/2002/07/owl#IrreflexiveProperty",
];

/// Collect all unique declared properties across 10 property metaclasses.
/// Mirrors the SLOP `collect-declared-properties` logic.
fn collect_declared_properties<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph<'a>,
) -> Vec<Term<'a>> {
    let rdf_type = arena.make_iri("http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
    let mut seen = std::collections::HashSet::new();
    let mut result = Vec::new();
    for mc in &PROPERTY_METACLASSES {
        let mc_term = arena.make_iri(mc);
        let matches = graph.match_pattern(None, Some(rdf_type), Some(mc_term));
        for t in matches {
            let key = format!("{}", t.subject);
            if seen.insert(key) {
                result.push(t.subject);
            }
        }
    }
    result
}


const RDF_TYPE_IRI: &str = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
const RDFS_DOMAIN_IRI: &str = "http://www.w3.org/2000/01/rdf-schema#domain";
const RDFS_RANGE_IRI: &str = "http://www.w3.org/2000/01/rdf-schema#range";

/// Check if a witness predicate is rdf:type (class-level rule like cax-dw).
fn witness_is_rdf_type(witness: &Triple<'_>) -> bool {
    matches!(&witness.predicate, Term::Iri(v) if *v == RDF_TYPE_IRI)
}

/// Check if a witness predicate is rdf:type (class-level rule) for owned triples.
fn owned_witness_is_rdf_type(witness: &OwnedTriple) -> bool {
    matches!(&witness.predicate, OwnedTerm::Iri(v) if v == RDF_TYPE_IRI)
}


// ---------------------------------------------------------------------------
// Free functions
// ---------------------------------------------------------------------------

/// Run the OWL 2 RL reasoner with default configuration.
pub fn reason<'a>(arena: &'a Arena, graph: &IndexedGraph) -> ReasonerResult<'a> {
    unsafe {
        let raw = ffi::growl_reason(arena.as_ptr(), graph.raw());
        ReasonerResult::from_ffi(raw, arena)
    }
}

/// Run the OWL 2 RL reasoner with a custom configuration.
pub fn reason_with_config<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph,
    config: &ReasonerConfig,
) -> ReasonerResult<'a> {
    unsafe {
        let raw = ffi::growl_reason_with_config(arena.as_ptr(), graph.raw(), config.raw);
        ReasonerResult::from_ffi(raw, arena)
    }
}

/// Check TBox satisfiability via synthetic instance injection.
///
/// Injects a synthetic blank node instance for each declared `owl:Class`
/// and a synthetic property usage for each declared property, then runs
/// normal OWL-RL reasoning. Returns `Unsatisfiable` if any class or property
/// is unsatisfiable, with the offending entity resolved from the synthetic blank.
pub fn validate<'a>(arena: &'a Arena, graph: &IndexedGraph<'a>) -> ValidateResult<'a> {
    validate_with_ns(arena, graph, "")
}

/// Check TBox satisfiability with namespace scoping.
///
/// Only entities whose IRI starts with `ns` will have synthetic instances injected.
/// Pass an empty string to validate all entities.
pub fn validate_with_ns<'a>(arena: &'a Arena, graph: &IndexedGraph<'a>, ns: &str) -> ValidateResult<'a> {
    let config = ReasonerConfig::new().verbose(false).validate(true).validate_ns(ns);
    match reason_with_config(arena, graph, &config) {
        ReasonerResult::Success { .. } => ValidateResult::Satisfiable,
        ReasonerResult::Inconsistent { reason, witnesses } => {
            let entity = extract_entity_from_reason_borrowed(arena, &reason)
                .unwrap_or_else(|| resolve_validate_entity(arena, graph, &witnesses, ns));
            ValidateResult::Unsatisfiable {
                entity,
                reason,
                witnesses,
            }
        }
    }
}

/// Extract entity IRI from the enriched reason string produced by the C engine.
///
/// The C engine's `enrich-validate-report` uses class-map/prop-map for O(1) lookup,
/// producing deterministic format: "Unsatisfiable class: <IRI> (...)" or
/// "Unsatisfiable property usage: <IRI> (...)". Prefer this over re-deriving from
/// graph queries, which can return wrong results due to hash-map iteration order.
fn extract_entity_from_reason(reason: &str) -> Option<OwnedTerm> {
    let iri_str = reason
        .strip_prefix("Unsatisfiable class: ")
        .or_else(|| reason.strip_prefix("Unsatisfiable property usage: "))?;
    let iri = iri_str.split(" (").next()?;
    if iri.is_empty() {
        return None;
    }
    Some(OwnedTerm::Iri(iri.to_string()))
}

/// Extract entity IRI from the enriched reason string, returning a borrowed Term.
fn extract_entity_from_reason_borrowed<'a>(arena: &'a Arena, reason: &str) -> Option<Term<'a>> {
    let iri_str = reason
        .strip_prefix("Unsatisfiable class: ")
        .or_else(|| reason.strip_prefix("Unsatisfiable property usage: "))?;
    let iri = iri_str.split(" (").next()?;
    if iri.is_empty() {
        return None;
    }
    Some(Term::from_ffi(arena.make_iri(iri)))
}

/// Resolve the unsatisfiable entity from witness triples, applying namespace filter.
fn resolve_validate_entity<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph<'a>,
    witnesses: &[Triple<'a>],
    ns: &str,
) -> Term<'a> {
    witnesses
        .first()
        .and_then(|w| match &w.subject {
            Term::Blank(id) if *id >= 10_000_000 && *id < 20_000_000 => {
                resolve_unsatisfiable_class_ns(arena, graph, *id, ns)
            }
            Term::Blank(id) if *id >= 20_000_000 && *id < 40_000_000 => {
                if witness_is_rdf_type(w) {
                    resolve_domain_range_class_ns(arena, graph, *id, ns)
                        .or_else(|| resolve_unsatisfiable_property_ns(arena, graph, *id, ns))
                } else {
                    resolve_unsatisfiable_property_ns(arena, graph, *id, ns)
                }
            }
            _ => None,
        })
        .unwrap_or(Term::Blank(-1))
}

/// Filter entities by namespace prefix (empty = no filter).
fn matches_ns(term: &Term<'_>, ns: &str) -> bool {
    match term {
        Term::Iri(v) => ns.is_empty() || v.starts_with(ns),
        _ => false,
    }
}

/// Resolve synthetic blank to class, with namespace filtering.
fn resolve_unsatisfiable_class_ns<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph<'a>,
    blank_id: i64,
    ns: &str,
) -> Option<Term<'a>> {
    let rdf_type = arena.make_iri(RDF_TYPE_IRI);
    let owl_class = arena.make_iri("http://www.w3.org/2002/07/owl#Class");
    let classes = graph.match_pattern(None, Some(rdf_type), Some(owl_class));
    let filtered: Vec<_> = classes.into_iter().filter(|t| matches_ns(&t.subject, ns)).collect();
    let idx = (blank_id - 10_000_000) as usize;
    filtered.into_iter().nth(idx).map(|t| t.subject)
}

/// Resolve synthetic blank to property, with namespace filtering.
fn resolve_unsatisfiable_property_ns<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph<'a>,
    blank_id: i64,
    ns: &str,
) -> Option<Term<'a>> {
    let prop_index = if blank_id < 30_000_000 {
        (blank_id - 20_000_000) as usize
    } else {
        (blank_id - 30_000_000) as usize
    };
    let props = collect_declared_properties(arena, graph);
    let filtered: Vec<_> = props.into_iter().filter(|t| matches_ns(t, ns)).collect();
    filtered.into_iter().nth(prop_index)
}

/// Trace back from a property blank to the domain/range class, with ns filtering.
fn resolve_domain_range_class_ns<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph<'a>,
    blank_id: i64,
    ns: &str,
) -> Option<Term<'a>> {
    let prop = resolve_unsatisfiable_property_ns(arena, graph, blank_id, ns)?;
    let prop_ffi = term_to_ffi(arena, &prop);
    let dr_iri = if blank_id < 30_000_000 {
        RDFS_DOMAIN_IRI
    } else {
        RDFS_RANGE_IRI
    };
    let dr_pred = arena.make_iri(dr_iri);
    let classes = graph.objects(prop_ffi, dr_pred);
    classes.into_iter().next()
}

/// Resolve the unsatisfiable entity from owned witness triples, with namespace filter.
fn owned_resolve_validate_entity(
    arena: &Arena,
    graph: &IndexedGraph<'_>,
    witnesses: &[OwnedTriple],
    ns: &str,
) -> OwnedTerm {
    witnesses
        .first()
        .and_then(|w| match &w.subject {
            OwnedTerm::Blank(id) if *id >= 10_000_000 && *id < 20_000_000 => {
                resolve_unsatisfiable_class_ns(arena, graph, *id, ns).map(OwnedTerm::from)
            }
            OwnedTerm::Blank(id) if *id >= 20_000_000 && *id < 40_000_000 => {
                if owned_witness_is_rdf_type(w) {
                    resolve_domain_range_class_ns(arena, graph, *id, ns)
                        .map(OwnedTerm::from)
                        .or_else(|| {
                            resolve_unsatisfiable_property_ns(arena, graph, *id, ns)
                                .map(OwnedTerm::from)
                        })
                } else {
                    resolve_unsatisfiable_property_ns(arena, graph, *id, ns)
                        .map(OwnedTerm::from)
                }
            }
            _ => None,
        })
        .unwrap_or(OwnedTerm::Blank(-1))
}

/// Check whether the graph is consistent under OWL 2 RL rules.
pub fn is_consistent(arena: &Arena, graph: &IndexedGraph) -> bool {
    unsafe { ffi::growl_is_consistent(arena.as_ptr(), graph.raw()) != 0 }
}

/// Get the `rdf:type` values inferred for an individual.
pub fn get_types<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph,
    individual: ffi::RdfTerm,
) -> Vec<Term<'a>> {
    unsafe {
        let list = ffi::growl_get_types(arena.as_ptr(), graph.raw(), individual);
        ffi_term_list_to_vec(list)
    }
}

/// Get the `owl:sameAs` terms inferred for an individual.
pub fn get_same_as<'a>(
    arena: &'a Arena,
    graph: &IndexedGraph,
    individual: ffi::RdfTerm,
) -> Vec<Term<'a>> {
    unsafe {
        let list = ffi::growl_get_same_as(arena.as_ptr(), graph.raw(), individual);
        ffi_term_list_to_vec(list)
    }
}

/// Get the number of inferred triples from a reasoner result.
pub fn get_inferred_count(result: &ffi::ReasonerResultFfi) -> i64 {
    unsafe { ffi::growl_get_inferred_count(*result) }
}

/// The 27 standard/well-known annotation property IRIs that are always filtered.
///
/// In addition to these, `filter_annotations` also removes triples whose predicate
/// is declared as `owl:AnnotationProperty` in the input graph.
pub const STANDARD_ANNOTATION_PROPERTIES: [&str; 27] = [
    // OWL/RDFS (9)
    "http://www.w3.org/2000/01/rdf-schema#label",
    "http://www.w3.org/2000/01/rdf-schema#comment",
    "http://www.w3.org/2000/01/rdf-schema#seeAlso",
    "http://www.w3.org/2000/01/rdf-schema#isDefinedBy",
    "http://www.w3.org/2002/07/owl#deprecated",
    "http://www.w3.org/2002/07/owl#versionInfo",
    "http://www.w3.org/2002/07/owl#priorVersion",
    "http://www.w3.org/2002/07/owl#backwardCompatibleWith",
    "http://www.w3.org/2002/07/owl#incompatibleWith",
    // SKOS (10)
    "http://www.w3.org/2004/02/skos/core#prefLabel",
    "http://www.w3.org/2004/02/skos/core#altLabel",
    "http://www.w3.org/2004/02/skos/core#hiddenLabel",
    "http://www.w3.org/2004/02/skos/core#definition",
    "http://www.w3.org/2004/02/skos/core#note",
    "http://www.w3.org/2004/02/skos/core#scopeNote",
    "http://www.w3.org/2004/02/skos/core#example",
    "http://www.w3.org/2004/02/skos/core#historyNote",
    "http://www.w3.org/2004/02/skos/core#editorialNote",
    "http://www.w3.org/2004/02/skos/core#changeNote",
    // Dublin Core (8)
    "http://purl.org/dc/elements/1.1/title",
    "http://purl.org/dc/elements/1.1/creator",
    "http://purl.org/dc/elements/1.1/subject",
    "http://purl.org/dc/elements/1.1/description",
    "http://purl.org/dc/terms/title",
    "http://purl.org/dc/terms/creator",
    "http://purl.org/dc/terms/description",
    "http://purl.org/dc/terms/abstract",
];

/// Filter annotation triples from an indexed graph.
///
/// Returns a new `IndexedGraph` with all triples removed whose predicate is a
/// standard annotation property or declared as `owl:AnnotationProperty` in the graph.
pub fn filter_annotations<'a>(arena: &'a Arena, graph: &IndexedGraph) -> IndexedGraph<'a> {
    let raw = unsafe { ffi::growl_filter_annotations(arena.as_ptr(), graph.raw()) };
    IndexedGraph { raw, arena }
}

// ---------------------------------------------------------------------------
// Owned types (no lifetimes, safe to send across threads)
// ---------------------------------------------------------------------------

/// Owned RDF term — uses String, no lifetime dependency on arena.
#[derive(Debug, Clone, PartialEq)]
pub enum OwnedTerm {
    Iri(String),
    Blank(i64),
    Literal {
        value: String,
        datatype: Option<String>,
        lang: Option<String>,
    },
}

impl<'a> From<Term<'a>> for OwnedTerm {
    fn from(t: Term<'a>) -> Self {
        match t {
            Term::Iri(v) => OwnedTerm::Iri(v.to_string()),
            Term::Blank(id) => OwnedTerm::Blank(id),
            Term::Literal {
                value,
                datatype,
                lang,
            } => OwnedTerm::Literal {
                value: value.to_string(),
                datatype: datatype.map(|s| s.to_string()),
                lang: lang.map(|s| s.to_string()),
            },
        }
    }
}

impl std::fmt::Display for OwnedTerm {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            OwnedTerm::Iri(v) => write!(f, "<{}>", v),
            OwnedTerm::Blank(id) => write!(f, "_:b{}", id),
            OwnedTerm::Literal {
                value,
                datatype,
                lang,
            } => {
                write!(f, "\"{}\"", value)?;
                if let Some(dt) = datatype {
                    write!(f, "^^<{}>", dt)?;
                }
                if let Some(l) = lang {
                    write!(f, "@{}", l)?;
                }
                Ok(())
            }
        }
    }
}

/// Owned RDF triple.
#[derive(Debug, Clone, PartialEq)]
pub struct OwnedTriple {
    pub subject: OwnedTerm,
    pub predicate: OwnedTerm,
    pub object: OwnedTerm,
}

impl<'a> From<Triple<'a>> for OwnedTriple {
    fn from(t: Triple<'a>) -> Self {
        OwnedTriple {
            subject: OwnedTerm::from(t.subject),
            predicate: OwnedTerm::from(t.predicate),
            object: OwnedTerm::from(t.object),
        }
    }
}

impl std::fmt::Display for OwnedTriple {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} {} {} .", self.subject, self.predicate, self.object)
    }
}

/// Owned reasoning result — no lifetime dependency.
pub enum OwnedReasonerResult {
    /// Reasoning completed successfully.
    Success {
        triples: Vec<OwnedTriple>,
        inferred_count: i64,
        iterations: i64,
    },
    /// The ontology is inconsistent.
    Inconsistent {
        reason: String,
        witnesses: Vec<OwnedTriple>,
    },
}

// ---------------------------------------------------------------------------
// Reasoner (high-level, owns its Arena)
// ---------------------------------------------------------------------------

/// High-level OWL 2 RL reasoner that owns its arena and graph.
///
/// This struct hides the arena/FFI details and provides a simple API
/// for loading triples and running reasoning. The `OwnedReasonerResult`
/// contains owned data that can be freely sent across threads.
///
/// # Example
/// ```no_run
/// use growl::{Reasoner, OwnedTerm, OwnedReasonerResult};
///
/// let mut reasoner = Reasoner::new();
/// reasoner.add_iri_triple(
///     "http://example.org/Dog",
///     "http://www.w3.org/2000/01/rdf-schema#subClassOf",
///     "http://example.org/Animal",
/// );
/// reasoner.add_iri_triple(
///     "http://example.org/fido",
///     "http://www.w3.org/1999/02/22-rdf-syntax-ns#type",
///     "http://example.org/Dog",
/// );
///
/// match reasoner.reason() {
///     OwnedReasonerResult::Success { triples, inferred_count, .. } => {
///         println!("Inferred {} triples", inferred_count);
///     }
///     OwnedReasonerResult::Inconsistent { reason, .. } => {
///         println!("Inconsistent: {}", reason);
///     }
/// }
/// ```
pub struct Reasoner {
    arena: Arena,
    graph_raw: ffi::IndexedGraphFfi,
    triple_count: usize,
    filter_annotations: bool,
    complete: bool,
}

impl Reasoner {
    /// Create a new reasoner with 32 MB arena.
    pub fn new() -> Self {
        Self::with_capacity(32 * 1024 * 1024)
    }

    /// Create a new reasoner with the given arena capacity in bytes.
    pub fn with_capacity(bytes: usize) -> Self {
        let arena = Arena::new(bytes);
        let graph_raw = unsafe { ffi::rdf_indexed_graph_create(arena.as_ptr()) };
        Reasoner {
            arena,
            graph_raw,
            triple_count: 0,
            filter_annotations: false,
            complete: false,
        }
    }

    /// Enable or disable annotation filtering before reasoning.
    ///
    /// When enabled, annotation triples (e.g. `rdfs:label`, `rdfs:comment`, SKOS labels,
    /// Dublin Core metadata) are removed before reasoning and restored afterward.
    /// This can significantly improve performance on annotation-heavy ontologies.
    pub fn filter_annotations(mut self, enable: bool) -> Self {
        self.filter_annotations = enable;
        self
    }

    /// Enable or disable complete mode for reasoning.
    ///
    /// When enabled, additional OWL axioms (owl:Thing, owl:Nothing, annotation
    /// properties, datatype assertions) are materialized before reasoning.
    /// This setting is inherited by `validate()` and `validate_ns()`.
    pub fn complete(mut self, enable: bool) -> Self {
        self.complete = enable;
        self
    }

    /// Add a triple from owned terms.
    pub fn add_triple(&mut self, s: &OwnedTerm, p: &OwnedTerm, o: &OwnedTerm) {
        let sf = self.owned_term_to_ffi(s);
        let pf = self.owned_term_to_ffi(p);
        let of = self.owned_term_to_ffi(o);
        let triple = self.arena.make_triple(sf, pf, of);
        self.graph_raw =
            unsafe { ffi::rdf_indexed_graph_add(self.arena.as_ptr(), self.graph_raw, triple) };
        self.triple_count += 1;
    }

    /// Add a triple from borrowed terms (zero heap allocations).
    ///
    /// This is the preferred method when converting from external RDF stores
    /// where string data can be borrowed directly as `&str`.
    pub fn add_triple_ref(&mut self, s: &Term, p: &Term, o: &Term) {
        let sf = term_to_ffi(&self.arena, s);
        let pf = term_to_ffi(&self.arena, p);
        let of = term_to_ffi(&self.arena, o);
        let triple = self.arena.make_triple(sf, pf, of);
        self.graph_raw =
            unsafe { ffi::rdf_indexed_graph_add(self.arena.as_ptr(), self.graph_raw, triple) };
        self.triple_count += 1;
    }

    /// Convenience: add a triple where all three terms are IRIs.
    pub fn add_iri_triple(&mut self, s: &str, p: &str, o: &str) {
        let sf = self.arena.make_iri(s);
        let pf = self.arena.make_iri(p);
        let of = self.arena.make_iri(o);
        let triple = self.arena.make_triple(sf, pf, of);
        self.graph_raw =
            unsafe { ffi::rdf_indexed_graph_add(self.arena.as_ptr(), self.graph_raw, triple) };
        self.triple_count += 1;
    }

    /// Return the number of triples loaded into the reasoner.
    pub fn triple_count(&self) -> usize {
        self.triple_count
    }

    /// Run OWL 2 RL reasoning with default configuration.
    ///
    /// Returns an `OwnedReasonerResult` with all data copied out of the
    /// arena's interned pool, so it can be freely used after this call.
    pub fn reason(&self) -> OwnedReasonerResult {
        self.reason_with_config(&ReasonerConfig::new())
    }

    /// Run OWL 2 RL reasoning with custom configuration.
    pub fn reason_with_config(&self, config: &ReasonerConfig) -> OwnedReasonerResult {
        if self.filter_annotations {
            self.reason_with_filtering(config)
        } else {
            let raw_result = unsafe {
                ffi::growl_reason_with_config(self.arena.as_ptr(), self.graph_raw, config.raw)
            };
            unsafe { self.convert_result(raw_result) }
        }
    }

    fn reason_with_filtering(&self, config: &ReasonerConfig) -> OwnedReasonerResult {
        unsafe {
            // Filter annotation triples
            let filtered = ffi::growl_filter_annotations(self.arena.as_ptr(), self.graph_raw);
            // Reason on filtered graph
            let raw_result =
                ffi::growl_reason_with_config(self.arena.as_ptr(), filtered, config.raw);
            match raw_result.tag {
                ffi::ReasonerResultTag::Success => {
                    let s = raw_result.data.reason_success;
                    // Re-add all original triples to the result graph
                    let mut result_graph = s.graph;
                    let orig = self.graph_raw;
                    for i in 0..orig.triples.len {
                        let triple = *orig.triples.data.add(i);
                        result_graph =
                            ffi::rdf_indexed_graph_add(self.arena.as_ptr(), result_graph, triple);
                    }
                    let restored_result = ffi::ReasonerResultFfi {
                        tag: ffi::ReasonerResultTag::Success,
                        data: ffi::ReasonerResultData {
                            reason_success: ffi::ReasonerSuccessFfi {
                                graph: result_graph,
                                inferred_count: s.inferred_count,
                                iterations: s.iterations,
                            },
                        },
                    };
                    self.convert_result(restored_result)
                }
                ffi::ReasonerResultTag::Inconsistent => self.convert_result(raw_result),
            }
        }
    }

    /// Check TBox satisfiability via synthetic instance injection.
    ///
    /// For each declared `owl:Class`, injects a synthetic blank node instance,
    /// and for each declared property, injects a synthetic usage triple.
    /// Returns `Unsatisfiable` with the offending entity if any class or
    /// property is unsatisfiable.
    ///
    /// Note: `--validate` overrides `--fast` since schema materialization is required.
    pub fn validate(&self) -> OwnedValidateResult {
        self.validate_ns("")
    }

    /// Check TBox satisfiability with namespace scoping.
    ///
    /// Only entities whose IRI starts with `ns` will have synthetic instances injected.
    /// Pass an empty string to validate all entities.
    pub fn validate_ns(&self, ns: &str) -> OwnedValidateResult {
        let config = ReasonerConfig::new().verbose(false).validate(true).validate_ns(ns).complete(self.complete);
        match self.reason_with_config(&config) {
            OwnedReasonerResult::Success { .. } => OwnedValidateResult::Satisfiable,
            OwnedReasonerResult::Inconsistent { reason, witnesses } => {
                let ig = IndexedGraph {
                    raw: self.graph_raw,
                    arena: &self.arena,
                };
                let entity = extract_entity_from_reason(&reason)
                    .unwrap_or_else(|| owned_resolve_validate_entity(&self.arena, &ig, &witnesses, ns));
                OwnedValidateResult::Unsatisfiable {
                    entity,
                    reason,
                    witnesses,
                }
            }
        }
    }

    /// Quick consistency check (no inferred triples returned).
    pub fn is_consistent(&self) -> bool {
        unsafe { ffi::growl_is_consistent(self.arena.as_ptr(), self.graph_raw) != 0 }
    }

    // -- private helpers --

    fn owned_term_to_ffi(&self, term: &OwnedTerm) -> ffi::RdfTerm {
        match term {
            OwnedTerm::Iri(v) => self.arena.make_iri(v),
            OwnedTerm::Blank(id) => self.arena.make_blank(*id),
            OwnedTerm::Literal {
                value,
                datatype,
                lang,
            } => self.arena.make_literal(
                value,
                datatype.as_deref(),
                lang.as_deref(),
            ),
        }
    }

    unsafe fn convert_result(&self, raw: ffi::ReasonerResultFfi) -> OwnedReasonerResult {
        match raw.tag {
            ffi::ReasonerResultTag::Success => {
                let s = raw.data.reason_success;
                // Convert all inferred triples to owned
                let triples_list = s.graph.triples;
                let mut triples = Vec::with_capacity(triples_list.len);
                for i in 0..triples_list.len {
                    let raw_triple = *triples_list.data.add(i);
                    let t = Triple::from_ffi(raw_triple);
                    triples.push(OwnedTriple::from(t));
                }
                OwnedReasonerResult::Success {
                    triples,
                    inferred_count: s.inferred_count,
                    iterations: s.iterations,
                }
            }
            ffi::ReasonerResultTag::Inconsistent => {
                let r = raw.data.reason_inconsistent;
                let reason = slop_string_to_str(r.reason).to_string();
                let mut witnesses = Vec::with_capacity(r.witnesses.len);
                for i in 0..r.witnesses.len {
                    let raw_triple = *r.witnesses.data.add(i);
                    let t = Triple::from_ffi(raw_triple);
                    witnesses.push(OwnedTriple::from(t));
                }
                OwnedReasonerResult::Inconsistent { reason, witnesses }
            }
        }
    }
}

impl Default for Reasoner {
    fn default() -> Self {
        Self::new()
    }
}
