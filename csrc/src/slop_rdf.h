#ifndef SLOP_rdf_H
#define SLOP_rdf_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>

typedef struct slop_rdf_rdf_IRI slop_rdf_rdf_IRI;
typedef struct slop_rdf_rdf_BlankNode slop_rdf_rdf_BlankNode;
typedef struct slop_rdf_rdf_Literal slop_rdf_rdf_Literal;
typedef struct slop_rdf_rdf_Term slop_rdf_rdf_Term;
typedef struct slop_rdf_rdf_Triple slop_rdf_rdf_Triple;
typedef struct slop_rdf_rdf_Graph slop_rdf_rdf_Graph;

typedef enum {
    slop_rdf_rdf_TermKind_iri,
    slop_rdf_rdf_TermKind_blank,
    slop_rdf_rdf_TermKind_literal,
    slop_rdf_rdf_TermKind_triple
} slop_rdf_rdf_TermKind;

typedef int64_t slop_rdf_rdf_BlankNodeId;

static inline slop_rdf_rdf_BlankNodeId slop_rdf_rdf_BlankNodeId_new(int64_t v) {
return SLOP_RANGE(slop_rdf_rdf_BlankNodeId, v, 1, 0, 0, 0, "BlankNodeId (Int 0 ..)");
}

typedef int64_t slop_rdf_rdf_GraphSize;

static inline slop_rdf_rdf_GraphSize slop_rdf_rdf_GraphSize_new(int64_t v) {
return SLOP_RANGE(slop_rdf_rdf_GraphSize, v, 1, 0, 0, 0, "GraphSize (Int 0 ..)");
}

struct slop_rdf_rdf_IRI {
    slop_string value;
};
typedef struct slop_rdf_rdf_IRI slop_rdf_rdf_IRI;

#ifndef SLOP_OPTION_SLOP_RDF_RDF_IRI_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_IRI_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_IRI, slop_option_slop_rdf_rdf_IRI)
#endif

struct slop_rdf_rdf_BlankNode {
    slop_rdf_rdf_BlankNodeId id;
};
typedef struct slop_rdf_rdf_BlankNode slop_rdf_rdf_BlankNode;

#ifndef SLOP_OPTION_SLOP_RDF_RDF_BLANKNODE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_BLANKNODE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_BlankNode, slop_option_slop_rdf_rdf_BlankNode)
#endif

struct slop_rdf_rdf_Literal {
    slop_string value;
    slop_option_string datatype;
    slop_option_string lang;
};
typedef struct slop_rdf_rdf_Literal slop_rdf_rdf_Literal;

#ifndef SLOP_OPTION_SLOP_RDF_RDF_LITERAL_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_LITERAL_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Literal, slop_option_slop_rdf_rdf_Literal)
#endif

typedef enum {
    slop_rdf_rdf_Term_term_iri,
    slop_rdf_rdf_Term_term_blank,
    slop_rdf_rdf_Term_term_literal,
    slop_rdf_rdf_Term_term_triple
} slop_rdf_rdf_Term_tag;

struct slop_rdf_rdf_Term {
    slop_rdf_rdf_Term_tag tag;
    union {
        slop_rdf_rdf_IRI term_iri;
        slop_rdf_rdf_BlankNode term_blank;
        slop_rdf_rdf_Literal term_literal;
        slop_rdf_rdf_Triple* term_triple;
    } data;
};
typedef struct slop_rdf_rdf_Term slop_rdf_rdf_Term;

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

struct slop_rdf_rdf_Triple {
    slop_rdf_rdf_Term subject;
    slop_rdf_rdf_Term predicate;
    slop_rdf_rdf_Term object;
};
typedef struct slop_rdf_rdf_Triple slop_rdf_rdf_Triple;

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Triple, slop_list_slop_rdf_rdf_Triple)
#endif

struct slop_rdf_rdf_Graph {
    slop_list_slop_rdf_rdf_Triple triples;
    slop_rdf_rdf_GraphSize size;
};
typedef struct slop_rdf_rdf_Graph slop_rdf_rdf_Graph;

#ifndef SLOP_OPTION_SLOP_RDF_RDF_GRAPH_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_GRAPH_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Graph, slop_option_slop_rdf_rdf_Graph)
#endif

slop_rdf_rdf_Term rdf_make_iri(slop_arena* arena, slop_string value);
slop_rdf_rdf_Term rdf_make_blank(slop_arena* arena, slop_rdf_rdf_BlankNodeId id);
slop_rdf_rdf_Term rdf_make_literal(slop_arena* arena, slop_string value, slop_option_string datatype, slop_option_string lang);
slop_rdf_rdf_Term rdf_make_triple_term(slop_arena* arena, slop_rdf_rdf_Triple t);
slop_rdf_rdf_TermKind rdf_term_kind(slop_rdf_rdf_Term t);
uint8_t rdf_iri_eq(slop_rdf_rdf_IRI a, slop_rdf_rdf_IRI b);
uint8_t rdf_blank_eq(slop_rdf_rdf_BlankNode a, slop_rdf_rdf_BlankNode b);
uint8_t rdf_option_string_eq(slop_option_string a, slop_option_string b);
uint8_t rdf_literal_eq(slop_rdf_rdf_Literal a, slop_rdf_rdf_Literal b);
uint8_t rdf_term_eq(slop_rdf_rdf_Term a, slop_rdf_rdf_Term b);
slop_rdf_rdf_Triple rdf_make_triple(slop_arena* arena, slop_rdf_rdf_Term subject, slop_rdf_rdf_Term predicate, slop_rdf_rdf_Term object);
slop_rdf_rdf_Term rdf_triple_subject(slop_rdf_rdf_Triple t);
slop_rdf_rdf_Term rdf_triple_predicate(slop_rdf_rdf_Triple t);
slop_rdf_rdf_Term rdf_triple_object(slop_rdf_rdf_Triple t);
uint8_t rdf_triple_eq(slop_rdf_rdf_Triple a, slop_rdf_rdf_Triple b);
slop_rdf_rdf_Graph rdf_make_graph(slop_arena* arena);
slop_rdf_rdf_Graph rdf_graph_add(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
slop_rdf_rdf_Graph rdf_graph_add_unchecked(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
slop_rdf_rdf_Graph rdf_graph_remove(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
slop_rdf_rdf_GraphSize rdf_graph_size(slop_rdf_rdf_Graph g);
uint8_t rdf_graph_contains(slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
slop_rdf_rdf_Graph rdf_graph_match(slop_arena* arena, slop_rdf_rdf_Graph g, slop_option_slop_rdf_rdf_Term subject, slop_option_slop_rdf_rdf_Term predicate, slop_option_slop_rdf_rdf_Term object);
void rdf_term_free(slop_rdf_rdf_Term* t);
void rdf_triple_free(slop_rdf_rdf_Triple* t);
void rdf_graph_free(slop_rdf_rdf_Graph* g);

/* Function name aliases for C interop */
#define slop_rdf_rdf_make_iri rdf_make_iri
#define slop_rdf_rdf_make_blank rdf_make_blank
#define slop_rdf_rdf_make_literal rdf_make_literal
#define slop_rdf_rdf_make_triple_term rdf_make_triple_term
#define slop_rdf_rdf_term_kind rdf_term_kind
#define slop_rdf_rdf_iri_eq rdf_iri_eq
#define slop_rdf_rdf_blank_eq rdf_blank_eq
#define slop_rdf_rdf_option_string_eq rdf_option_string_eq
#define slop_rdf_rdf_literal_eq rdf_literal_eq
#define slop_rdf_rdf_term_eq rdf_term_eq
#define slop_rdf_rdf_make_triple rdf_make_triple
#define slop_rdf_rdf_triple_subject rdf_triple_subject
#define slop_rdf_rdf_triple_predicate rdf_triple_predicate
#define slop_rdf_rdf_triple_object rdf_triple_object
#define slop_rdf_rdf_triple_eq rdf_triple_eq
#define slop_rdf_rdf_make_graph rdf_make_graph
#define slop_rdf_rdf_graph_add rdf_graph_add
#define slop_rdf_rdf_graph_add_unchecked rdf_graph_add_unchecked
#define slop_rdf_rdf_graph_remove rdf_graph_remove
#define slop_rdf_rdf_graph_size rdf_graph_size
#define slop_rdf_rdf_graph_contains rdf_graph_contains
#define slop_rdf_rdf_graph_match rdf_graph_match
#define slop_rdf_rdf_term_free rdf_term_free
#define slop_rdf_rdf_triple_free rdf_triple_free
#define slop_rdf_rdf_graph_free rdf_graph_free

#ifndef SLOP_OPTION_SLOP_RDF_RDF_IRI_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_IRI_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_IRI, slop_option_slop_rdf_rdf_IRI)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_BLANKNODE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_BLANKNODE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_BlankNode, slop_option_slop_rdf_rdf_BlankNode)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_LITERAL_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_LITERAL_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Literal, slop_option_slop_rdf_rdf_Literal)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_GRAPH_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_GRAPH_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Graph, slop_option_slop_rdf_rdf_Graph)
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
#ifndef SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Term, slop_list_slop_rdf_rdf_Term)
#endif
#endif


#endif
