//! Raw FFI bindings matching the C types in `growl.h` and `slop_runtime.h`.

use std::os::raw::{c_char, c_void};

/// Opaque arena allocator.
#[repr(C)]
pub struct SlopArena {
    _private: [u8; 0],
}

/// Length-prefixed string (not null-terminated).
#[repr(C)]
#[derive(Copy, Clone)]
pub struct SlopString {
    pub len: usize,
    pub data: *const c_char,
}

/// Optional string.
#[repr(C)]
#[derive(Copy, Clone)]
pub struct SlopOptionString {
    pub has_value: bool,
    pub value: SlopString,
}

// ---------------------------------------------------------------------------
// RDF types
// ---------------------------------------------------------------------------

#[repr(C)]
#[derive(Copy, Clone)]
pub struct RdfIri {
    pub value: SlopString,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub struct RdfBlankNode {
    pub id: i64,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub struct RdfLiteral {
    pub value: SlopString,
    pub datatype: SlopOptionString,
    pub lang: SlopOptionString,
}

/// Tag for the `rdf_Term` tagged union.
#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum RdfTermTag {
    Iri = 0,
    Blank = 1,
    Literal = 2,
}

/// Data payload for `rdf_Term` — a C union.
#[repr(C)]
#[derive(Copy, Clone)]
pub union RdfTermData {
    pub term_iri: RdfIri,
    pub term_blank: RdfBlankNode,
    pub term_literal: RdfLiteral,
}

/// Tagged union representing an RDF term.
#[repr(C)]
#[derive(Copy, Clone)]
pub struct RdfTerm {
    pub tag: RdfTermTag,
    pub data: RdfTermData,
}

/// An RDF triple (subject, predicate, object).
#[repr(C)]
#[derive(Copy, Clone)]
pub struct RdfTriple {
    pub subject: RdfTerm,
    pub predicate: RdfTerm,
    pub object: RdfTerm,
}

// ---------------------------------------------------------------------------
// List types
// ---------------------------------------------------------------------------

#[repr(C)]
#[derive(Copy, Clone)]
pub struct SlopListRdfTerm {
    pub len: usize,
    pub cap: usize,
    pub data: *mut RdfTerm,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub struct SlopListRdfTriple {
    pub len: usize,
    pub cap: usize,
    pub data: *mut RdfTriple,
}

// ---------------------------------------------------------------------------
// Option types
// ---------------------------------------------------------------------------

#[repr(C)]
#[derive(Copy, Clone)]
pub struct SlopOptionRdfTerm {
    pub has_value: bool,
    pub value: RdfTerm,
}

// ---------------------------------------------------------------------------
// Index types
// ---------------------------------------------------------------------------

#[repr(C)]
#[derive(Copy, Clone)]
pub struct TripleIndex {
    pub spo: *mut c_void,
    pub pso: *mut c_void,
    pub osp: *mut c_void,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub struct IndexedGraphFfi {
    pub triples: SlopListRdfTriple,
    pub index: TripleIndex,
    pub size: i64,
}

// ---------------------------------------------------------------------------
// Reasoner types
// ---------------------------------------------------------------------------

#[repr(C)]
#[derive(Copy, Clone)]
pub struct ReasonerConfigFfi {
    pub worker_count: u8,
    pub channel_buffer: u16,
    pub max_iterations: u16,
    pub verbose: u8,
    pub fast: u8,
    pub complete: u8,
    pub validate: u8,
    pub validate_ns: SlopString,
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum ReasonerResultTag {
    Success = 0,
    Inconsistent = 1,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub struct ReasonerSuccessFfi {
    pub graph: IndexedGraphFfi,
    pub inferred_count: i64,
    pub iterations: i64,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub struct InconsistencyReportFfi {
    pub reason: SlopString,
    pub witnesses: SlopListRdfTriple,
}

/// A list of InconsistencyReport structs (mirrors SLOP's `(List InconsistencyReport)`).
#[repr(C)]
#[derive(Copy, Clone)]
pub struct SlopListInconsistencyReport {
    pub len: usize,
    pub cap: usize,
    pub data: *mut InconsistencyReportFfi,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub union ReasonerResultData {
    pub reason_success: ReasonerSuccessFfi,
    pub reason_inconsistent: SlopListInconsistencyReport,
}

#[repr(C)]
#[derive(Copy, Clone)]
pub struct ReasonerResultFfi {
    pub tag: ReasonerResultTag,
    pub data: ReasonerResultData,
}

// ---------------------------------------------------------------------------
// extern "C" declarations
// ---------------------------------------------------------------------------

extern "C" {
    // Arena and interning (from csrc_shim.c)
    pub fn growl_arena_new(capacity: usize) -> *mut SlopArena;
    pub fn growl_arena_free(arena: *mut SlopArena);
    pub fn growl_intern_string(data: *const c_char, len: usize) -> SlopString;

    // Term constructors
    pub fn rdf_make_iri(arena: *mut SlopArena, value: SlopString) -> RdfTerm;
    pub fn rdf_make_blank(arena: *mut SlopArena, id: i64) -> RdfTerm;
    pub fn rdf_make_literal(
        arena: *mut SlopArena,
        value: SlopString,
        datatype: SlopOptionString,
        lang: SlopOptionString,
    ) -> RdfTerm;
    pub fn rdf_make_triple(
        arena: *mut SlopArena,
        subject: RdfTerm,
        predicate: RdfTerm,
        object: RdfTerm,
    ) -> RdfTriple;

    // Term accessors
    pub fn rdf_triple_subject(t: RdfTriple) -> RdfTerm;
    pub fn rdf_triple_predicate(t: RdfTriple) -> RdfTerm;
    pub fn rdf_triple_object(t: RdfTriple) -> RdfTerm;

    // Equality
    pub fn rdf_term_eq(a: RdfTerm, b: RdfTerm) -> u8;
    pub fn rdf_triple_eq(a: RdfTriple, b: RdfTriple) -> u8;

    // IndexedGraph
    pub fn rdf_indexed_graph_create(arena: *mut SlopArena) -> IndexedGraphFfi;
    pub fn rdf_indexed_graph_add(
        arena: *mut SlopArena,
        g: IndexedGraphFfi,
        t: RdfTriple,
    ) -> IndexedGraphFfi;
    pub fn rdf_indexed_graph_contains(g: IndexedGraphFfi, t: RdfTriple) -> u8;
    pub fn rdf_indexed_graph_match(
        arena: *mut SlopArena,
        g: IndexedGraphFfi,
        subj: SlopOptionRdfTerm,
        pred: SlopOptionRdfTerm,
        obj: SlopOptionRdfTerm,
    ) -> SlopListRdfTriple;
    pub fn rdf_indexed_graph_size(g: IndexedGraphFfi) -> i64;
    pub fn rdf_indexed_graph_objects(
        arena: *mut SlopArena,
        g: IndexedGraphFfi,
        subj: RdfTerm,
        pred: RdfTerm,
    ) -> SlopListRdfTerm;
    pub fn rdf_indexed_graph_subjects(
        arena: *mut SlopArena,
        g: IndexedGraphFfi,
        pred: RdfTerm,
        obj: RdfTerm,
    ) -> SlopListRdfTerm;

    // Reasoner
    pub fn growl_default_config() -> ReasonerConfigFfi;
    pub fn growl_reason(arena: *mut SlopArena, input: IndexedGraphFfi) -> ReasonerResultFfi;
    pub fn growl_reason_with_config(
        arena: *mut SlopArena,
        input: IndexedGraphFfi,
        config: ReasonerConfigFfi,
    ) -> ReasonerResultFfi;
    pub fn growl_is_consistent(arena: *mut SlopArena, input: IndexedGraphFfi) -> u8;
    pub fn growl_get_types(
        arena: *mut SlopArena,
        g: IndexedGraphFfi,
        individual: RdfTerm,
    ) -> SlopListRdfTerm;
    pub fn growl_get_same_as(
        arena: *mut SlopArena,
        g: IndexedGraphFfi,
        individual: RdfTerm,
    ) -> SlopListRdfTerm;
    pub fn growl_get_inferred_count(result: ReasonerResultFfi) -> i64;

    // Annotation filtering
    pub fn growl_filter_annotations(
        arena: *mut SlopArena,
        ig: IndexedGraphFfi,
    ) -> IndexedGraphFfi;
}
