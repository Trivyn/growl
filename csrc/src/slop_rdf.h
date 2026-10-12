#ifndef SLOP_rdf_H
#define SLOP_rdf_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct rdf_IRI rdf_IRI;
typedef struct rdf_BlankNode rdf_BlankNode;
typedef struct rdf_Literal rdf_Literal;
typedef struct rdf_Term rdf_Term;
typedef struct rdf_Triple rdf_Triple;
typedef struct rdf_Graph rdf_Graph;

typedef enum {
    rdf_TermKind_iri,
    rdf_TermKind_blank,
    rdf_TermKind_literal,
    rdf_TermKind_triple
} rdf_TermKind;

typedef int64_t rdf_BlankNodeId;

static inline rdf_BlankNodeId rdf_BlankNodeId_new(int64_t v) {
return SLOP_RANGE(rdf_BlankNodeId, v, 1, 0, 0, 0, "BlankNodeId (Int 0 ..)");
}

typedef int64_t rdf_GraphSize;

static inline rdf_GraphSize rdf_GraphSize_new(int64_t v) {
return SLOP_RANGE(rdf_GraphSize, v, 1, 0, 0, 0, "GraphSize (Int 0 ..)");
}

struct rdf_IRI {
    slop_string value;
};
typedef struct rdf_IRI rdf_IRI;

#ifndef SLOP_OPTION_RDF_IRI_DEFINED
#define SLOP_OPTION_RDF_IRI_DEFINED
SLOP_OPTION_DEFINE(rdf_IRI, slop_option_rdf_IRI)
#endif

struct rdf_BlankNode {
    rdf_BlankNodeId id;
};
typedef struct rdf_BlankNode rdf_BlankNode;

#ifndef SLOP_OPTION_RDF_BLANKNODE_DEFINED
#define SLOP_OPTION_RDF_BLANKNODE_DEFINED
SLOP_OPTION_DEFINE(rdf_BlankNode, slop_option_rdf_BlankNode)
#endif

struct rdf_Literal {
    slop_string value;
    slop_option_string datatype;
    slop_option_string lang;
};
typedef struct rdf_Literal rdf_Literal;

#ifndef SLOP_OPTION_RDF_LITERAL_DEFINED
#define SLOP_OPTION_RDF_LITERAL_DEFINED
SLOP_OPTION_DEFINE(rdf_Literal, slop_option_rdf_Literal)
#endif

typedef enum {
    rdf_Term_term_iri,
    rdf_Term_term_blank,
    rdf_Term_term_literal,
    rdf_Term_term_triple
} rdf_Term_tag;

struct rdf_Term {
    rdf_Term_tag tag;
    union {
        rdf_IRI term_iri;
        rdf_BlankNode term_blank;
        rdf_Literal term_literal;
        rdf_Triple* term_triple;
    } data;
};
typedef struct rdf_Term rdf_Term;

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

struct rdf_Triple {
    rdf_Term subject;
    rdf_Term predicate;
    rdf_Term object;
};
typedef struct rdf_Triple rdf_Triple;

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_IMPL_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

struct rdf_Graph {
    slop_list_rdf_Triple triples;
    rdf_GraphSize size;
};
typedef struct rdf_Graph rdf_Graph;

#ifndef SLOP_OPTION_RDF_GRAPH_DEFINED
#define SLOP_OPTION_RDF_GRAPH_DEFINED
SLOP_OPTION_DEFINE(rdf_Graph, slop_option_rdf_Graph)
#endif

rdf_Term rdf_make_iri(slop_arena* arena, slop_string value);
rdf_Term rdf_make_blank(slop_arena* arena, rdf_BlankNodeId id);
rdf_Term rdf_make_literal(slop_arena* arena, slop_string value, slop_option_string datatype, slop_option_string lang);
rdf_Term rdf_make_triple_term(slop_arena* arena, rdf_Triple t);
rdf_TermKind rdf_term_kind(rdf_Term t);
uint8_t rdf_iri_eq(rdf_IRI a, rdf_IRI b);
uint8_t rdf_blank_eq(rdf_BlankNode a, rdf_BlankNode b);
uint8_t rdf_option_string_eq(slop_option_string a, slop_option_string b);
uint8_t rdf_literal_eq(rdf_Literal a, rdf_Literal b);
uint8_t rdf_term_eq(rdf_Term a, rdf_Term b);
rdf_Triple rdf_make_triple(slop_arena* arena, rdf_Term subject, rdf_Term predicate, rdf_Term object);
rdf_Term rdf_triple_subject(rdf_Triple t);
rdf_Term rdf_triple_predicate(rdf_Triple t);
rdf_Term rdf_triple_object(rdf_Triple t);
uint8_t rdf_triple_eq(rdf_Triple a, rdf_Triple b);
rdf_Graph rdf_make_graph(slop_arena* arena);
rdf_Graph rdf_graph_add(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_Graph rdf_graph_add_unchecked(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_Graph rdf_graph_remove(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_GraphSize rdf_graph_size(rdf_Graph g);
uint8_t rdf_graph_contains(rdf_Graph g, rdf_Triple t);
rdf_Graph rdf_graph_match(slop_arena* arena, rdf_Graph g, slop_option_rdf_Term subject, slop_option_rdf_Term predicate, slop_option_rdf_Term object);
void rdf_term_free(rdf_Term* t);
void rdf_triple_free(rdf_Triple* t);
void rdf_graph_free(rdf_Graph* g);

#ifndef SLOP_OPTION_RDF_IRI_DEFINED
#define SLOP_OPTION_RDF_IRI_DEFINED
SLOP_OPTION_DEFINE(rdf_IRI, slop_option_rdf_IRI)
#endif

#ifndef SLOP_OPTION_RDF_BLANKNODE_DEFINED
#define SLOP_OPTION_RDF_BLANKNODE_DEFINED
SLOP_OPTION_DEFINE(rdf_BlankNode, slop_option_rdf_BlankNode)
#endif

#ifndef SLOP_OPTION_RDF_LITERAL_DEFINED
#define SLOP_OPTION_RDF_LITERAL_DEFINED
SLOP_OPTION_DEFINE(rdf_Literal, slop_option_rdf_Literal)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_GRAPH_DEFINED
#define SLOP_OPTION_RDF_GRAPH_DEFINED
SLOP_OPTION_DEFINE(rdf_Graph, slop_option_rdf_Graph)
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
        && (slop_eq_string(&_a->value, &_b->value))
    ;
}
#endif
#ifndef RDF_BLANKNODE_HASH_EQ_DEFINED
#define RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_BlankNode(const void* key) {
    const rdf_BlankNode* _k = (const rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_int(&(int64_t){ (int64_t)_k->id }); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_BlankNode(const void* a, const void* b) {
    const rdf_BlankNode* _a = (const rdf_BlankNode*)a;
    const rdf_BlankNode* _b = (const rdf_BlankNode*)b;
    return true
        && (_a->id == _b->id)
    ;
}
#endif
#ifndef RDF_LITERAL_HASH_EQ_DEFINED
#define RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_Literal(const void* key) {
    const rdf_Literal* _k = (const rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    hash ^= ((_k->datatype).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->datatype).value)) : 0); hash *= 1099511628211ULL;
    hash ^= ((_k->lang).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->lang).value)) : 0); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_Literal(const void* a, const void* b) {
    const rdf_Literal* _a = (const rdf_Literal*)a;
    const rdf_Literal* _b = (const rdf_Literal*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
        && ((_a->datatype).has_value == (_b->datatype).has_value && (!(_a->datatype).has_value || ((slop_eq_string(&(_a->datatype).value, &(_b->datatype).value)))))
        && ((_a->lang).has_value == (_b->lang).has_value && (!(_a->lang).has_value || ((slop_eq_string(&(_a->lang).value, &(_b->lang).value)))))
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
        case rdf_Term_term_triple:
            return slop_hash_ptr(&_k->data.term_triple);
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
        case rdf_Term_term_triple:
            return _a->data.term_triple == _b->data.term_triple;
    }
    return false;
}
#ifndef SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_IMPL_DEFINED
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif
#endif


#endif
