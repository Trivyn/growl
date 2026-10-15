/*
 * Thin C shim for static inline arena functions from slop_runtime.h.
 * These are static inline in the header, so they have no exported symbol.
 * We wrap them here so Rust can link to them.
 */

#include "slop_runtime.h"
#include "slop_growl.h"
#include <stddef.h>

/*
 * FFI layout guards.
 *
 * These expose the REAL C ABI (struct sizes and the offsets of the fields that
 * sit after a by-value embedded struct) so the hand-written Rust mirrors in
 * src/ffi.rs can be asserted against it in tests. A silent drift here is
 * exactly what regressed growl 0.6.0: slop-rdf added a 4th index (`pos`) to
 * `index_TripleIndex`, growing `index_IndexedGraph` by 8 bytes, but the Rust
 * `TripleIndex` mirror was not updated -- so `IndexedGraph.size` (and
 * `ReasonerSuccess.iterations`) were read at the wrong offset across the FFI
 * boundary and `graph.size()` returned a garbage pointer.
 */
size_t growl_layout_sizeof_triple_index(void)       { return sizeof(slop_rdf_index_TripleIndex); }
size_t growl_layout_sizeof_indexed_graph(void)      { return sizeof(slop_rdf_index_IndexedGraph); }
size_t growl_layout_offset_graph_size(void)         { return offsetof(slop_rdf_index_IndexedGraph, size); }
size_t growl_layout_sizeof_rdf_term(void)           { return sizeof(slop_rdf_rdf_Term); }
size_t growl_layout_sizeof_rdf_triple(void)         { return sizeof(slop_rdf_rdf_Triple); }
size_t growl_layout_sizeof_reasoner_config(void)    { return sizeof(growl_types_ReasonerConfig); }
size_t growl_layout_offset_cfg_cancel_ptr(void)     { return offsetof(growl_types_ReasonerConfig, cancel_ptr); }
size_t growl_layout_sizeof_reasoner_success(void)   { return sizeof(growl_types_ReasonerSuccess); }
size_t growl_layout_offset_success_iterations(void) { return offsetof(growl_types_ReasonerSuccess, iterations); }
/* List headers are embedded by value everywhere (IndexedGraph.triples,
 * InconsistencyReport.witnesses, by-value list returns), so a change to the
 * SLOP_LIST_DECLARE header -- e.g. slop#278 adding an `arena` field -- shifts
 * all of them. The InconsistencyReport size is the stride Rust walks
 * `reason_inconsistent.data[i]` with. */
size_t growl_layout_sizeof_list_rdf_term(void)      { return sizeof(slop_list_slop_rdf_rdf_Term); }
size_t growl_layout_sizeof_list_rdf_triple(void)    { return sizeof(slop_list_slop_rdf_rdf_Triple); }
size_t growl_layout_sizeof_list_report(void)        { return sizeof(slop_list_growl_types_InconsistencyReport); }
size_t growl_layout_offset_graph_index(void)        { return offsetof(slop_rdf_index_IndexedGraph, index); }
size_t growl_layout_sizeof_report(void)             { return sizeof(growl_types_InconsistencyReport); }
size_t growl_layout_sizeof_reasoner_result(void)    { return sizeof(growl_types_ReasonerResult); }
size_t growl_layout_offset_result_data(void)        { return offsetof(growl_types_ReasonerResult, data); }

/* slop_rdf_rdf_Term tag values, mirrored by ffi::RdfTermTag. A C tag Rust has no variant
 * for is UB the moment Rust reads the term (issue #24: RDF 1.2 term_triple). */
size_t growl_layout_tag_term_iri(void)              { return slop_rdf_rdf_Term_term_iri; }
size_t growl_layout_tag_term_blank(void)            { return slop_rdf_rdf_Term_term_blank; }
size_t growl_layout_tag_term_literal(void)          { return slop_rdf_rdf_Term_term_literal; }
size_t growl_layout_tag_term_triple(void)           { return slop_rdf_rdf_Term_term_triple; }

/* The variant count. C enums carry no count, so this switch names every tag
 * and -Wswitch is an error here: a tag added in slop-rdf fails the build
 * until it is handled here and in ffi::RdfTermTag. */
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wswitch"
size_t growl_layout_tag_count(void) {
    slop_rdf_rdf_Term_tag tag = slop_rdf_rdf_Term_term_iri;
    switch (tag) {
        case slop_rdf_rdf_Term_term_iri:
        case slop_rdf_rdf_Term_term_blank:
        case slop_rdf_rdf_Term_term_literal:
        case slop_rdf_rdf_Term_term_triple:
            break;
    }
    return 4;
}
#pragma GCC diagnostic pop

slop_arena* growl_arena_new(size_t capacity) {
    slop_arena* a = (slop_arena*)malloc(sizeof(slop_arena));
    if (!a) return NULL;
    *a = slop_arena_new(capacity);
    if (a->base == NULL) {
        free(a);
        return NULL;
    }
    return a;
}

void growl_arena_free(slop_arena* arena) {
    if (!arena) return;
    slop_arena_free(arena);
    free(arena);
}

slop_string growl_intern_string(const char* data, size_t len) {
    return slop_intern_string(data, len);
}
