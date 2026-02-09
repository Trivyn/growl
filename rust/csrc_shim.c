/*
 * Thin C shim for static inline arena functions from slop_runtime.h.
 * These are static inline in the header, so they have no exported symbol.
 * We wrap them here so Rust can link to them.
 */

#include "slop_runtime.h"

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
