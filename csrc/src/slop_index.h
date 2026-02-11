#ifndef SLOP_index_H
#define SLOP_index_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"

typedef struct index_TripleIndex index_TripleIndex;
typedef struct index_IndexedGraph index_IndexedGraph;

typedef slop_map* index_TripleSet;

typedef slop_map* index_TripleMap;

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

#ifndef SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_DEFINED
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

struct index_TripleIndex {
    slop_map* spo;
    slop_map* pso;
    slop_map* osp;
};
typedef struct index_TripleIndex index_TripleIndex;

#ifndef SLOP_OPTION_INDEX_TRIPLEINDEX_DEFINED
#define SLOP_OPTION_INDEX_TRIPLEINDEX_DEFINED
SLOP_OPTION_DEFINE(index_TripleIndex, slop_option_index_TripleIndex)
#endif

struct index_IndexedGraph {
    slop_list_rdf_Triple triples;
    index_TripleIndex index;
    int64_t size;
};
typedef struct index_IndexedGraph index_IndexedGraph;

#ifndef SLOP_OPTION_INDEX_INDEXEDGRAPH_DEFINED
#define SLOP_OPTION_INDEX_INDEXEDGRAPH_DEFINED
SLOP_OPTION_DEFINE(index_IndexedGraph, slop_option_index_IndexedGraph)
#endif


/* Hash/eq functions and list types for struct map/set keys */
#ifndef RDF_TERM_HASH_EQ_DEFINED
#define RDF_TERM_HASH_EQ_DEFINED
#ifndef RDF_IRI_HASH_EQ_DEFINED
#define RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_IRI(const void* key) {
    const rdf_IRI* _k = (const rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_IRI(const void* a, const void* b) {
    const rdf_IRI* _a = (const rdf_IRI*)a;
    const rdf_IRI* _b = (const rdf_IRI*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
    ;
}
#endif
#ifndef RDF_BLANKNODE_HASH_EQ_DEFINED
#define RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_BlankNode(const void* key) {
    const rdf_BlankNode* _k = (const rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    { int64_t _tmp = (int64_t)_k->id; hash ^= slop_hash_int(&_tmp); hash *= 1099511628211ULL; }
    return hash;
}
static inline bool slop_eq_rdf_BlankNode(const void* a, const void* b) {
    const rdf_BlankNode* _a = (const rdf_BlankNode*)a;
    const rdf_BlankNode* _b = (const rdf_BlankNode*)b;
    return true
        && _a->id == _b->id
    ;
}
#endif
#ifndef RDF_LITERAL_HASH_EQ_DEFINED
#define RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_Literal(const void* key) {
    const rdf_Literal* _k = (const rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    { const uint8_t* _b = (const uint8_t*)&_k->datatype; for(size_t _i=0; _i<sizeof(_k->datatype); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    { const uint8_t* _b = (const uint8_t*)&_k->lang; for(size_t _i=0; _i<sizeof(_k->lang); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    return hash;
}
static inline bool slop_eq_rdf_Literal(const void* a, const void* b) {
    const rdf_Literal* _a = (const rdf_Literal*)a;
    const rdf_Literal* _b = (const rdf_Literal*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
        && memcmp(&_a->datatype, &_b->datatype, sizeof(_a->datatype)) == 0
        && memcmp(&_a->lang, &_b->lang, sizeof(_a->lang)) == 0
    ;
}
#endif
static inline uint64_t slop_hash_rdf_Term(const void* key) {
    const rdf_Term* _k = (const rdf_Term*)key;
    switch (_k->tag) {
        case rdf_Term_term_iri:
            return slop_hash_rdf_IRI(&_k->data.term_iri);
        case rdf_Term_term_blank:
            return slop_hash_rdf_BlankNode(&_k->data.term_blank);
        case rdf_Term_term_literal:
            return slop_hash_rdf_Literal(&_k->data.term_literal);
    }
    return 0;
}
static inline bool slop_eq_rdf_Term(const void* a, const void* b) {
    const rdf_Term* _a = (const rdf_Term*)a;
    const rdf_Term* _b = (const rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case rdf_Term_term_iri:
            return slop_eq_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case rdf_Term_term_blank:
            return slop_eq_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case rdf_Term_term_literal:
            return slop_eq_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
    }
    return false;
}
#endif

#ifndef RDF_TRIPLE_HASH_EQ_DEFINED
#define RDF_TRIPLE_HASH_EQ_DEFINED
#ifndef RDF_TERM_HASH_EQ_DEFINED
#define RDF_TERM_HASH_EQ_DEFINED
#ifndef RDF_IRI_HASH_EQ_DEFINED
#define RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_IRI(const void* key) {
    const rdf_IRI* _k = (const rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_IRI(const void* a, const void* b) {
    const rdf_IRI* _a = (const rdf_IRI*)a;
    const rdf_IRI* _b = (const rdf_IRI*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
    ;
}
#endif
#ifndef RDF_BLANKNODE_HASH_EQ_DEFINED
#define RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_BlankNode(const void* key) {
    const rdf_BlankNode* _k = (const rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    { int64_t _tmp = (int64_t)_k->id; hash ^= slop_hash_int(&_tmp); hash *= 1099511628211ULL; }
    return hash;
}
static inline bool slop_eq_rdf_BlankNode(const void* a, const void* b) {
    const rdf_BlankNode* _a = (const rdf_BlankNode*)a;
    const rdf_BlankNode* _b = (const rdf_BlankNode*)b;
    return true
        && _a->id == _b->id
    ;
}
#endif
#ifndef RDF_LITERAL_HASH_EQ_DEFINED
#define RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_Literal(const void* key) {
    const rdf_Literal* _k = (const rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    { const uint8_t* _b = (const uint8_t*)&_k->datatype; for(size_t _i=0; _i<sizeof(_k->datatype); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    { const uint8_t* _b = (const uint8_t*)&_k->lang; for(size_t _i=0; _i<sizeof(_k->lang); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    return hash;
}
static inline bool slop_eq_rdf_Literal(const void* a, const void* b) {
    const rdf_Literal* _a = (const rdf_Literal*)a;
    const rdf_Literal* _b = (const rdf_Literal*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
        && memcmp(&_a->datatype, &_b->datatype, sizeof(_a->datatype)) == 0
        && memcmp(&_a->lang, &_b->lang, sizeof(_a->lang)) == 0
    ;
}
#endif
static inline uint64_t slop_hash_rdf_Term(const void* key) {
    const rdf_Term* _k = (const rdf_Term*)key;
    switch (_k->tag) {
        case rdf_Term_term_iri:
            return slop_hash_rdf_IRI(&_k->data.term_iri);
        case rdf_Term_term_blank:
            return slop_hash_rdf_BlankNode(&_k->data.term_blank);
        case rdf_Term_term_literal:
            return slop_hash_rdf_Literal(&_k->data.term_literal);
    }
    return 0;
}
static inline bool slop_eq_rdf_Term(const void* a, const void* b) {
    const rdf_Term* _a = (const rdf_Term*)a;
    const rdf_Term* _b = (const rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case rdf_Term_term_iri:
            return slop_eq_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case rdf_Term_term_blank:
            return slop_eq_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case rdf_Term_term_literal:
            return slop_eq_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
    }
    return false;
}
#endif
#ifndef RDF_TERM_HASH_EQ_DEFINED
#define RDF_TERM_HASH_EQ_DEFINED
#ifndef RDF_IRI_HASH_EQ_DEFINED
#define RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_IRI(const void* key) {
    const rdf_IRI* _k = (const rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_IRI(const void* a, const void* b) {
    const rdf_IRI* _a = (const rdf_IRI*)a;
    const rdf_IRI* _b = (const rdf_IRI*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
    ;
}
#endif
#ifndef RDF_BLANKNODE_HASH_EQ_DEFINED
#define RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_BlankNode(const void* key) {
    const rdf_BlankNode* _k = (const rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    { int64_t _tmp = (int64_t)_k->id; hash ^= slop_hash_int(&_tmp); hash *= 1099511628211ULL; }
    return hash;
}
static inline bool slop_eq_rdf_BlankNode(const void* a, const void* b) {
    const rdf_BlankNode* _a = (const rdf_BlankNode*)a;
    const rdf_BlankNode* _b = (const rdf_BlankNode*)b;
    return true
        && _a->id == _b->id
    ;
}
#endif
#ifndef RDF_LITERAL_HASH_EQ_DEFINED
#define RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_Literal(const void* key) {
    const rdf_Literal* _k = (const rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    { const uint8_t* _b = (const uint8_t*)&_k->datatype; for(size_t _i=0; _i<sizeof(_k->datatype); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    { const uint8_t* _b = (const uint8_t*)&_k->lang; for(size_t _i=0; _i<sizeof(_k->lang); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    return hash;
}
static inline bool slop_eq_rdf_Literal(const void* a, const void* b) {
    const rdf_Literal* _a = (const rdf_Literal*)a;
    const rdf_Literal* _b = (const rdf_Literal*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
        && memcmp(&_a->datatype, &_b->datatype, sizeof(_a->datatype)) == 0
        && memcmp(&_a->lang, &_b->lang, sizeof(_a->lang)) == 0
    ;
}
#endif
static inline uint64_t slop_hash_rdf_Term(const void* key) {
    const rdf_Term* _k = (const rdf_Term*)key;
    switch (_k->tag) {
        case rdf_Term_term_iri:
            return slop_hash_rdf_IRI(&_k->data.term_iri);
        case rdf_Term_term_blank:
            return slop_hash_rdf_BlankNode(&_k->data.term_blank);
        case rdf_Term_term_literal:
            return slop_hash_rdf_Literal(&_k->data.term_literal);
    }
    return 0;
}
static inline bool slop_eq_rdf_Term(const void* a, const void* b) {
    const rdf_Term* _a = (const rdf_Term*)a;
    const rdf_Term* _b = (const rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case rdf_Term_term_iri:
            return slop_eq_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case rdf_Term_term_blank:
            return slop_eq_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case rdf_Term_term_literal:
            return slop_eq_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
    }
    return false;
}
#endif
#ifndef RDF_TERM_HASH_EQ_DEFINED
#define RDF_TERM_HASH_EQ_DEFINED
#ifndef RDF_IRI_HASH_EQ_DEFINED
#define RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_IRI(const void* key) {
    const rdf_IRI* _k = (const rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_IRI(const void* a, const void* b) {
    const rdf_IRI* _a = (const rdf_IRI*)a;
    const rdf_IRI* _b = (const rdf_IRI*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
    ;
}
#endif
#ifndef RDF_BLANKNODE_HASH_EQ_DEFINED
#define RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_BlankNode(const void* key) {
    const rdf_BlankNode* _k = (const rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    { int64_t _tmp = (int64_t)_k->id; hash ^= slop_hash_int(&_tmp); hash *= 1099511628211ULL; }
    return hash;
}
static inline bool slop_eq_rdf_BlankNode(const void* a, const void* b) {
    const rdf_BlankNode* _a = (const rdf_BlankNode*)a;
    const rdf_BlankNode* _b = (const rdf_BlankNode*)b;
    return true
        && _a->id == _b->id
    ;
}
#endif
#ifndef RDF_LITERAL_HASH_EQ_DEFINED
#define RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_Literal(const void* key) {
    const rdf_Literal* _k = (const rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    { const uint8_t* _b = (const uint8_t*)&_k->datatype; for(size_t _i=0; _i<sizeof(_k->datatype); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    { const uint8_t* _b = (const uint8_t*)&_k->lang; for(size_t _i=0; _i<sizeof(_k->lang); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    return hash;
}
static inline bool slop_eq_rdf_Literal(const void* a, const void* b) {
    const rdf_Literal* _a = (const rdf_Literal*)a;
    const rdf_Literal* _b = (const rdf_Literal*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
        && memcmp(&_a->datatype, &_b->datatype, sizeof(_a->datatype)) == 0
        && memcmp(&_a->lang, &_b->lang, sizeof(_a->lang)) == 0
    ;
}
#endif
static inline uint64_t slop_hash_rdf_Term(const void* key) {
    const rdf_Term* _k = (const rdf_Term*)key;
    switch (_k->tag) {
        case rdf_Term_term_iri:
            return slop_hash_rdf_IRI(&_k->data.term_iri);
        case rdf_Term_term_blank:
            return slop_hash_rdf_BlankNode(&_k->data.term_blank);
        case rdf_Term_term_literal:
            return slop_hash_rdf_Literal(&_k->data.term_literal);
    }
    return 0;
}
static inline bool slop_eq_rdf_Term(const void* a, const void* b) {
    const rdf_Term* _a = (const rdf_Term*)a;
    const rdf_Term* _b = (const rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case rdf_Term_term_iri:
            return slop_eq_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case rdf_Term_term_blank:
            return slop_eq_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case rdf_Term_term_literal:
            return slop_eq_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
    }
    return false;
}
#endif
static inline uint64_t slop_hash_rdf_Triple(const void* key) {
    const rdf_Triple* _k = (const rdf_Triple*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_rdf_Term(&_k->subject); hash *= 1099511628211ULL;
    hash ^= slop_hash_rdf_Term(&_k->predicate); hash *= 1099511628211ULL;
    hash ^= slop_hash_rdf_Term(&_k->object); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_Triple(const void* a, const void* b) {
    const rdf_Triple* _a = (const rdf_Triple*)a;
    const rdf_Triple* _b = (const rdf_Triple*)b;
    return true
        && slop_eq_rdf_Term(&_a->subject, &_b->subject)
        && slop_eq_rdf_Term(&_a->predicate, &_b->predicate)
        && slop_eq_rdf_Term(&_a->object, &_b->object)
    ;
}
#endif

index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena);
index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t);
uint8_t rdf_indexed_graph_contains(index_IndexedGraph g, rdf_Triple t);
slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj);
void rdf_indexed_graph_for_each(index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj, slop_closure_t callback);
int64_t rdf_indexed_graph_size(index_IndexedGraph g);
slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj);
slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred);

/* Function name aliases for C interop */
#define index_indexed_graph_create rdf_indexed_graph_create
#define index_indexed_graph_add rdf_indexed_graph_add
#define index_indexed_graph_contains rdf_indexed_graph_contains
#define index_indexed_graph_match rdf_indexed_graph_match
#define index_indexed_graph_for_each rdf_indexed_graph_for_each
#define index_indexed_graph_size rdf_indexed_graph_size
#define index_indexed_graph_subjects rdf_indexed_graph_subjects
#define index_indexed_graph_objects rdf_indexed_graph_objects

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

#ifndef SLOP_OPTION_INDEX_TRIPLESET_DEFINED
#define SLOP_OPTION_INDEX_TRIPLESET_DEFINED
SLOP_OPTION_DEFINE(index_TripleSet, slop_option_index_TripleSet)
#endif

#ifndef SLOP_OPTION_INDEX_TRIPLEMAP_DEFINED
#define SLOP_OPTION_INDEX_TRIPLEMAP_DEFINED
SLOP_OPTION_DEFINE(index_TripleMap, slop_option_index_TripleMap)
#endif

#ifndef SLOP_OPTION_INDEX_TRIPLEINDEX_DEFINED
#define SLOP_OPTION_INDEX_TRIPLEINDEX_DEFINED
SLOP_OPTION_DEFINE(index_TripleIndex, slop_option_index_TripleIndex)
#endif

#ifndef SLOP_OPTION_INDEX_INDEXEDGRAPH_DEFINED
#define SLOP_OPTION_INDEX_INDEXEDGRAPH_DEFINED
SLOP_OPTION_DEFINE(index_IndexedGraph, slop_option_index_IndexedGraph)
#endif


#endif
