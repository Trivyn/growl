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
    rdf_TermKind_literal
} rdf_TermKind;

typedef int64_t rdf_BlankNodeId;

static inline rdf_BlankNodeId rdf_BlankNodeId_new(int64_t v) {
SLOP_PRE(v >= 0, "rdf_BlankNodeId >= 0");
return (rdf_BlankNodeId)v;
}

typedef int64_t rdf_GraphSize;

static inline rdf_GraphSize rdf_GraphSize_new(int64_t v) {
SLOP_PRE(v >= 0, "rdf_GraphSize >= 0");
return (rdf_GraphSize)v;
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
    rdf_Term_term_literal
} rdf_Term_tag;

struct rdf_Term {
    rdf_Term_tag tag;
    union {
        rdf_IRI term_iri;
        rdf_BlankNode term_blank;
        rdf_Literal term_literal;
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


#endif
