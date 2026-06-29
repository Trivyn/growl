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
size_t growl_layout_sizeof_triple_index(void)       { return sizeof(index_TripleIndex); }
size_t growl_layout_sizeof_indexed_graph(void)      { return sizeof(index_IndexedGraph); }
size_t growl_layout_offset_graph_size(void)         { return offsetof(index_IndexedGraph, size); }
size_t growl_layout_sizeof_rdf_term(void)           { return sizeof(rdf_Term); }
size_t growl_layout_sizeof_rdf_triple(void)         { return sizeof(rdf_Triple); }
size_t growl_layout_sizeof_reasoner_config(void)    { return sizeof(types_ReasonerConfig); }
size_t growl_layout_offset_cfg_cancel_ptr(void)     { return offsetof(types_ReasonerConfig, cancel_ptr); }
size_t growl_layout_sizeof_reasoner_success(void)   { return sizeof(types_ReasonerSuccess); }
size_t growl_layout_offset_success_iterations(void) { return offsetof(types_ReasonerSuccess, iterations); }

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
