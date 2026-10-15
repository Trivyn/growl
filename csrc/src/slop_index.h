#ifndef SLOP_index_H
#define SLOP_index_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"

typedef struct slop_rdf_index_TripleIndex slop_rdf_index_TripleIndex;
typedef struct slop_rdf_index_IndexedGraph slop_rdf_index_IndexedGraph;

typedef slop_map* slop_rdf_index_TermSet;

typedef slop_map* slop_rdf_index_TermSetMap;

#ifndef SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Term, slop_list_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Triple, slop_list_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

struct slop_rdf_index_TripleIndex {
    slop_map* spo;
    slop_map* pso;
    slop_map* osp;
    slop_map* pos;
};
typedef struct slop_rdf_index_TripleIndex slop_rdf_index_TripleIndex;

#ifndef SLOP_OPTION_SLOP_RDF_INDEX_TRIPLEINDEX_DEFINED
#define SLOP_OPTION_SLOP_RDF_INDEX_TRIPLEINDEX_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_index_TripleIndex, slop_option_slop_rdf_index_TripleIndex)
#endif

struct slop_rdf_index_IndexedGraph {
    slop_list_slop_rdf_rdf_Triple triples;
    slop_rdf_index_TripleIndex index;
    int64_t size;
};
typedef struct slop_rdf_index_IndexedGraph slop_rdf_index_IndexedGraph;

#ifndef SLOP_OPTION_SLOP_RDF_INDEX_INDEXEDGRAPH_DEFINED
#define SLOP_OPTION_SLOP_RDF_INDEX_INDEXEDGRAPH_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_index_IndexedGraph, slop_option_slop_rdf_index_IndexedGraph)
#endif


/* Hash/eq functions and list types for struct map/set keys */
#ifndef SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#ifndef SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_IRI(const void* key) {
    const slop_rdf_rdf_IRI* _k = (const slop_rdf_rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_IRI(const void* a, const void* b) {
    const slop_rdf_rdf_IRI* _a = (const slop_rdf_rdf_IRI*)a;
    const slop_rdf_rdf_IRI* _b = (const slop_rdf_rdf_IRI*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
    ;
}
#endif
#ifndef SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_BlankNode(const void* key) {
    const slop_rdf_rdf_BlankNode* _k = (const slop_rdf_rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_int(&(int64_t){ (int64_t)_k->id }); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_BlankNode(const void* a, const void* b) {
    const slop_rdf_rdf_BlankNode* _a = (const slop_rdf_rdf_BlankNode*)a;
    const slop_rdf_rdf_BlankNode* _b = (const slop_rdf_rdf_BlankNode*)b;
    return true
        && (_a->id == _b->id)
    ;
}
#endif
#ifndef SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_Literal(const void* key) {
    const slop_rdf_rdf_Literal* _k = (const slop_rdf_rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    hash ^= ((_k->datatype).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->datatype).value)) : 0); hash *= 1099511628211ULL;
    hash ^= ((_k->lang).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->lang).value)) : 0); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_Literal(const void* a, const void* b) {
    const slop_rdf_rdf_Literal* _a = (const slop_rdf_rdf_Literal*)a;
    const slop_rdf_rdf_Literal* _b = (const slop_rdf_rdf_Literal*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
        && ((_a->datatype).has_value == (_b->datatype).has_value && (!(_a->datatype).has_value || ((slop_eq_string(&(_a->datatype).value, &(_b->datatype).value)))))
        && ((_a->lang).has_value == (_b->lang).has_value && (!(_a->lang).has_value || ((slop_eq_string(&(_a->lang).value, &(_b->lang).value)))))
    ;
}
#endif
static inline uint64_t slop_hash_slop_rdf_rdf_Term(const void* key) {
    const slop_rdf_rdf_Term* _k = (const slop_rdf_rdf_Term*)key;
    switch (_k->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_hash_slop_rdf_rdf_IRI(&_k->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_hash_slop_rdf_rdf_BlankNode(&_k->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_hash_slop_rdf_rdf_Literal(&_k->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return slop_hash_ptr(&_k->data.term_triple);
    }
    return 0;
}
static inline bool slop_eq_slop_rdf_rdf_Term(const void* a, const void* b) {
    const slop_rdf_rdf_Term* _a = (const slop_rdf_rdf_Term*)a;
    const slop_rdf_rdf_Term* _b = (const slop_rdf_rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_eq_slop_rdf_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_eq_slop_rdf_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_eq_slop_rdf_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return _a->data.term_triple == _b->data.term_triple;
    }
    return false;
}
#endif

slop_rdf_index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena);
slop_rdf_index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t);
uint8_t rdf_indexed_graph_contains(slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t);
slop_list_slop_rdf_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj);
void rdf_indexed_graph_for_each(slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj, slop_closure_t callback);
int64_t rdf_indexed_graph_size(slop_rdf_index_IndexedGraph g);
slop_list_slop_rdf_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term pred, slop_rdf_rdf_Term obj);
slop_list_slop_rdf_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term subj, slop_rdf_rdf_Term pred);

/* Function name aliases for C interop */
#define slop_rdf_index_indexed_graph_create rdf_indexed_graph_create
#define slop_rdf_index_indexed_graph_add rdf_indexed_graph_add
#define slop_rdf_index_indexed_graph_contains rdf_indexed_graph_contains
#define slop_rdf_index_indexed_graph_match rdf_indexed_graph_match
#define slop_rdf_index_indexed_graph_for_each rdf_indexed_graph_for_each
#define slop_rdf_index_indexed_graph_size rdf_indexed_graph_size
#define slop_rdf_index_indexed_graph_subjects rdf_indexed_graph_subjects
#define slop_rdf_index_indexed_graph_objects rdf_indexed_graph_objects

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_INDEX_TERMSET_DEFINED
#define SLOP_OPTION_SLOP_RDF_INDEX_TERMSET_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_index_TermSet, slop_option_slop_rdf_index_TermSet)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_INDEX_TERMSETMAP_DEFINED
#define SLOP_OPTION_SLOP_RDF_INDEX_TERMSETMAP_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_index_TermSetMap, slop_option_slop_rdf_index_TermSetMap)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_INDEX_TRIPLEINDEX_DEFINED
#define SLOP_OPTION_SLOP_RDF_INDEX_TRIPLEINDEX_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_index_TripleIndex, slop_option_slop_rdf_index_TripleIndex)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_INDEX_INDEXEDGRAPH_DEFINED
#define SLOP_OPTION_SLOP_RDF_INDEX_INDEXEDGRAPH_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_index_IndexedGraph, slop_option_slop_rdf_index_IndexedGraph)
#endif

#ifndef SLOP_OPTION_MAP_PTR_DEFINED
#define SLOP_OPTION_MAP_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_map*, slop_option_map_ptr)
#endif


#endif
