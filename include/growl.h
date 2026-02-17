/* growl.h - Auto-generated FFI header. Do not edit. */
#ifndef GROWL_H
#define GROWL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque runtime types */
typedef struct slop_arena slop_arena;
typedef struct slop_map slop_map;

/* Runtime value types */
typedef struct { size_t len; const char* data; } slop_string;
typedef struct { bool has_value; slop_string value; } slop_option_string;
typedef struct { void* fn; void* env; } slop_closure_t;

/* Type definitions */
struct index_TripleIndex {
    slop_map* spo;
    slop_map* pso;
    slop_map* osp;
};
typedef struct index_TripleIndex index_TripleIndex;

typedef int64_t rdf_BlankNodeId;

struct rdf_BlankNode {
    rdf_BlankNodeId id;
};
typedef struct rdf_BlankNode rdf_BlankNode;

typedef int64_t rdf_GraphSize;

struct rdf_IRI {
    slop_string value;
};
typedef struct rdf_IRI rdf_IRI;

struct rdf_Literal {
    slop_string value;
    slop_option_string datatype;
    slop_option_string lang;
};
typedef struct rdf_Literal rdf_Literal;

typedef enum {
    rdf_TermKind_iri,
    rdf_TermKind_blank,
    rdf_TermKind_literal
} rdf_TermKind;

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

struct rdf_Triple {
    rdf_Term subject;
    rdf_Term predicate;
    rdf_Term object;
};
typedef struct rdf_Triple rdf_Triple;

typedef struct { size_t len; size_t cap; rdf_Term* data; } slop_list_rdf_Term;

typedef struct { size_t len; size_t cap; rdf_Triple* data; } slop_list_rdf_Triple;

struct index_IndexedGraph {
    slop_list_rdf_Triple triples;
    index_TripleIndex index;
    int64_t size;
};
typedef struct index_IndexedGraph index_IndexedGraph;

struct rdf_Graph {
    slop_list_rdf_Triple triples;
    rdf_GraphSize size;
};
typedef struct rdf_Graph rdf_Graph;

typedef struct { bool has_value; rdf_Term value; } slop_option_rdf_Term;

struct types_InconsistencyReport {
    slop_string reason;
    slop_list_rdf_Triple witnesses;
};
typedef struct types_InconsistencyReport types_InconsistencyReport;

typedef struct { size_t len; size_t cap; types_InconsistencyReport* data; } slop_list_types_InconsistencyReport;

struct types_ReasonerConfig {
    uint8_t worker_count;
    uint16_t channel_buffer;
    uint16_t max_iterations;
    uint8_t verbose;
    uint8_t fast;
    uint8_t complete;
    uint8_t validate;
    slop_string validate_ns;
};
typedef struct types_ReasonerConfig types_ReasonerConfig;

typedef enum {
    types_ReasonerResult_reason_success,
    types_ReasonerResult_reason_inconsistent
} types_ReasonerResult_tag;

struct types_ReasonerSuccess {
    index_IndexedGraph graph;
    int64_t inferred_count;
    int64_t iterations;
};
typedef struct types_ReasonerSuccess types_ReasonerSuccess;

struct types_ReasonerResult {
    types_ReasonerResult_tag tag;
    union {
        types_ReasonerSuccess reason_success;
        slop_list_types_InconsistencyReport reason_inconsistent;
    } data;
};
typedef struct types_ReasonerResult types_ReasonerResult;

typedef enum {
    xsd_XsdCompareResult_xsd_compare_less,
    xsd_XsdCompareResult_xsd_compare_equal,
    xsd_XsdCompareResult_xsd_compare_greater,
    xsd_XsdCompareResult_xsd_compare_incomparable
} xsd_XsdCompareResult;

typedef enum {
    xsd_XsdType_xsd_string,
    xsd_XsdType_xsd_integer,
    xsd_XsdType_xsd_decimal,
    xsd_XsdType_xsd_float,
    xsd_XsdType_xsd_double,
    xsd_XsdType_xsd_boolean,
    xsd_XsdType_xsd_unknown
} xsd_XsdType;

typedef enum {
    xsd_XsdValue_xsd_string_val,
    xsd_XsdValue_xsd_integer_val,
    xsd_XsdValue_xsd_decimal_val,
    xsd_XsdValue_xsd_float_val,
    xsd_XsdValue_xsd_double_val,
    xsd_XsdValue_xsd_boolean_val,
    xsd_XsdValue_xsd_unknown_val
} xsd_XsdValue_tag;

struct xsd_XsdValue {
    xsd_XsdValue_tag tag;
    union {
        slop_string xsd_string_val;
        int64_t xsd_integer_val;
        double xsd_decimal_val;
        float xsd_float_val;
        double xsd_double_val;
        uint8_t xsd_boolean_val;
        slop_string xsd_unknown_val;
    } data;
};
typedef struct xsd_XsdValue xsd_XsdValue;

/* Public API */
slop_map* growl_collect_annotation_properties(slop_arena* arena, rdf_Graph g);
types_ReasonerConfig growl_default_config(void);
index_IndexedGraph growl_filter_annotations(slop_arena* arena, index_IndexedGraph ig);
int64_t growl_get_inferred_count(types_ReasonerResult result);
slop_list_rdf_Term growl_get_same_as(slop_arena* arena, index_IndexedGraph g, rdf_Term individual);
slop_list_rdf_Term growl_get_types(slop_arena* arena, index_IndexedGraph g, rdf_Term individual);
index_IndexedGraph growl_graph_to_indexed(slop_arena* arena, rdf_Graph g, slop_map* annot_set);
rdf_Graph growl_indexed_to_graph(slop_arena* arena, index_IndexedGraph ig);
uint8_t growl_is_consistent(slop_arena* arena, index_IndexedGraph input);
types_ReasonerResult growl_reason(slop_arena* arena, index_IndexedGraph input);
types_ReasonerResult growl_reason_with_config(slop_arena* arena, index_IndexedGraph input, types_ReasonerConfig config);
uint8_t rdf_blank_eq(rdf_BlankNode a, rdf_BlankNode b);
rdf_Graph rdf_graph_add(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_Graph rdf_graph_add_unchecked(slop_arena* arena, rdf_Graph g, rdf_Triple t);
uint8_t rdf_graph_contains(rdf_Graph g, rdf_Triple t);
void rdf_graph_free(rdf_Graph* g);
rdf_Graph rdf_graph_match(slop_arena* arena, rdf_Graph g, slop_option_rdf_Term subject, slop_option_rdf_Term predicate, slop_option_rdf_Term object);
rdf_Graph rdf_graph_remove(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_GraphSize rdf_graph_size(rdf_Graph g);
index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t);
uint8_t rdf_indexed_graph_contains(index_IndexedGraph g, rdf_Triple t);
index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena);
void rdf_indexed_graph_for_each(index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj, slop_closure_t callback);
slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj);
slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred);
int64_t rdf_indexed_graph_size(index_IndexedGraph g);
slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj);
uint8_t rdf_iri_eq(rdf_IRI a, rdf_IRI b);
uint8_t rdf_list_contains(slop_arena* arena, rdf_Graph g, rdf_Term head, rdf_Term element);
slop_list_rdf_Term rdf_list_elements(slop_arena* arena, rdf_Graph g, rdf_Term head);
slop_list_rdf_Term rdf_list_elements_indexed(slop_arena* arena, index_IndexedGraph g, rdf_Term head);
int64_t rdf_list_length(slop_arena* arena, rdf_Graph g, rdf_Term head);
uint8_t rdf_literal_eq(rdf_Literal a, rdf_Literal b);
rdf_Term rdf_make_blank(slop_arena* arena, rdf_BlankNodeId id);
rdf_Graph rdf_make_graph(slop_arena* arena);
rdf_Term rdf_make_iri(slop_arena* arena, slop_string value);
rdf_Term rdf_make_literal(slop_arena* arena, slop_string value, slop_option_string datatype, slop_option_string lang);
rdf_Triple rdf_make_triple(slop_arena* arena, rdf_Term subject, rdf_Term predicate, rdf_Term object);
uint8_t rdf_option_string_eq(slop_option_string a, slop_option_string b);
uint8_t rdf_term_eq(rdf_Term a, rdf_Term b);
void rdf_term_free(rdf_Term* t);
rdf_TermKind rdf_term_kind(rdf_Term t);
uint8_t rdf_triple_eq(rdf_Triple a, rdf_Triple b);
void rdf_triple_free(rdf_Triple* t);
rdf_Term rdf_triple_object(rdf_Triple t);
rdf_Term rdf_triple_predicate(rdf_Triple t);
rdf_Term rdf_triple_subject(rdf_Triple t);
xsd_XsdCompareResult xsd_compare(slop_arena* arena, rdf_Term a, rdf_Term b);
xsd_XsdCompareResult xsd_float_cmp(double a, double b);
slop_result_u8_xsd_XsdError xsd_literal_values_equal(slop_arena* arena, rdf_Literal a, rdf_Literal b);
xsd_XsdType xsd_parse_type(slop_string datatype_iri);
slop_result_xsd_XsdValue_xsd_XsdError xsd_parse_value(slop_arena* arena, slop_string lexical, xsd_XsdType dtype);
uint8_t xsd_types_compatible(xsd_XsdType t1, xsd_XsdType t2);
uint8_t xsd_validate_lexical(slop_string lexical, slop_string datatype_iri);
xsd_XsdCompareResult xsd_values_compare(xsd_XsdValue a, xsd_XsdValue b);
uint8_t xsd_values_equal(xsd_XsdValue a, xsd_XsdValue b);

#define filter_collect_annotation_properties growl_collect_annotation_properties
#define filter_filter_annotations growl_filter_annotations
#define filter_graph_to_indexed growl_graph_to_indexed
#define filter_indexed_to_graph growl_indexed_to_graph
#define index_indexed_graph_add rdf_indexed_graph_add
#define index_indexed_graph_contains rdf_indexed_graph_contains
#define index_indexed_graph_create rdf_indexed_graph_create
#define index_indexed_graph_for_each rdf_indexed_graph_for_each
#define index_indexed_graph_match rdf_indexed_graph_match
#define index_indexed_graph_objects rdf_indexed_graph_objects
#define index_indexed_graph_size rdf_indexed_graph_size
#define index_indexed_graph_subjects rdf_indexed_graph_subjects
#define list_rdf_list_contains rdf_list_contains
#define list_rdf_list_elements rdf_list_elements
#define list_rdf_list_elements_indexed rdf_list_elements_indexed
#define list_rdf_list_length rdf_list_length
#define xsd_xsd_compare xsd_compare
#define xsd_xsd_parse_type xsd_parse_type
#define xsd_xsd_parse_value xsd_parse_value
#define xsd_xsd_types_compatible xsd_types_compatible
#define xsd_xsd_validate_lexical xsd_validate_lexical
#define xsd_xsd_values_compare xsd_values_compare
#define xsd_xsd_values_equal xsd_values_equal

#ifdef __cplusplus
}
#endif

#endif /* GROWL_H */
