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
struct growl_types_ReasonerConfig {
    uint8_t worker_count;
    uint16_t channel_buffer;
    uint16_t max_iterations;
    uint8_t verbose;
    uint8_t fast;
    uint8_t complete;
    uint8_t enrich;
    uint8_t validate;
    slop_string validate_ns;
    int64_t cancel_ptr;
    int64_t max_triples;
};
typedef struct growl_types_ReasonerConfig growl_types_ReasonerConfig;

typedef enum {
    growl_types_ReasonerResult_reason_success,
    growl_types_ReasonerResult_reason_inconsistent,
    growl_types_ReasonerResult_reason_cancelled
} growl_types_ReasonerResult_tag;

struct slop_rdf_index_TripleIndex {
    slop_map* spo;
    slop_map* pso;
    slop_map* osp;
    slop_map* pos;
};
typedef struct slop_rdf_index_TripleIndex slop_rdf_index_TripleIndex;

typedef int64_t slop_rdf_rdf_BlankNodeId;

struct slop_rdf_rdf_BlankNode {
    slop_rdf_rdf_BlankNodeId id;
};
typedef struct slop_rdf_rdf_BlankNode slop_rdf_rdf_BlankNode;

typedef int64_t slop_rdf_rdf_GraphSize;

struct slop_rdf_rdf_IRI {
    slop_string value;
};
typedef struct slop_rdf_rdf_IRI slop_rdf_rdf_IRI;

struct slop_rdf_rdf_Literal {
    slop_string value;
    slop_option_string datatype;
    slop_option_string lang;
};
typedef struct slop_rdf_rdf_Literal slop_rdf_rdf_Literal;

typedef enum {
    slop_rdf_rdf_TermKind_iri,
    slop_rdf_rdf_TermKind_blank,
    slop_rdf_rdf_TermKind_literal,
    slop_rdf_rdf_TermKind_triple
} slop_rdf_rdf_TermKind;

typedef enum {
    slop_rdf_rdf_Term_term_iri,
    slop_rdf_rdf_Term_term_blank,
    slop_rdf_rdf_Term_term_literal,
    slop_rdf_rdf_Term_term_triple
} slop_rdf_rdf_Term_tag;

typedef enum {
    slop_rdf_xsd_XsdCompareResult_xsd_compare_less,
    slop_rdf_xsd_XsdCompareResult_xsd_compare_equal,
    slop_rdf_xsd_XsdCompareResult_xsd_compare_greater,
    slop_rdf_xsd_XsdCompareResult_xsd_compare_incomparable
} slop_rdf_xsd_XsdCompareResult;

typedef enum {
    slop_rdf_xsd_XsdType_xsd_string,
    slop_rdf_xsd_XsdType_xsd_integer,
    slop_rdf_xsd_XsdType_xsd_decimal,
    slop_rdf_xsd_XsdType_xsd_float,
    slop_rdf_xsd_XsdType_xsd_double,
    slop_rdf_xsd_XsdType_xsd_boolean,
    slop_rdf_xsd_XsdType_xsd_unknown
} slop_rdf_xsd_XsdType;

typedef enum {
    slop_rdf_xsd_XsdValue_xsd_string_val,
    slop_rdf_xsd_XsdValue_xsd_integer_val,
    slop_rdf_xsd_XsdValue_xsd_decimal_val,
    slop_rdf_xsd_XsdValue_xsd_float_val,
    slop_rdf_xsd_XsdValue_xsd_double_val,
    slop_rdf_xsd_XsdValue_xsd_boolean_val,
    slop_rdf_xsd_XsdValue_xsd_unknown_val
} slop_rdf_xsd_XsdValue_tag;

struct slop_rdf_xsd_XsdValue {
    slop_rdf_xsd_XsdValue_tag tag;
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
typedef struct slop_rdf_xsd_XsdValue slop_rdf_xsd_XsdValue;

struct growl_types_InconsistencyReport {
    slop_string reason;
    slop_list_slop_rdf_rdf_Triple witnesses;
};
typedef struct growl_types_InconsistencyReport growl_types_InconsistencyReport;

struct growl_types_ReasonerResult {
    growl_types_ReasonerResult_tag tag;
    union {
        growl_types_ReasonerSuccess reason_success;
        slop_list_growl_types_InconsistencyReport reason_inconsistent;
        growl_types_ReasonerSuccess reason_cancelled;
    } data;
};
typedef struct growl_types_ReasonerResult growl_types_ReasonerResult;

struct growl_types_ReasonerSuccess {
    slop_rdf_index_IndexedGraph graph;
    int64_t inferred_count;
    int64_t iterations;
};
typedef struct growl_types_ReasonerSuccess growl_types_ReasonerSuccess;

typedef struct { size_t len; size_t cap; growl_types_InconsistencyReport* data; slop_arena* arena; } slop_list_growl_types_InconsistencyReport;

typedef struct { size_t len; size_t cap; slop_rdf_rdf_Term* data; slop_arena* arena; } slop_list_slop_rdf_rdf_Term;

typedef struct { size_t len; size_t cap; slop_rdf_rdf_Triple* data; slop_arena* arena; } slop_list_slop_rdf_rdf_Triple;

typedef struct { bool has_value; slop_rdf_rdf_Term value; } slop_option_slop_rdf_rdf_Term;

struct slop_rdf_index_IndexedGraph {
    slop_list_slop_rdf_rdf_Triple triples;
    slop_rdf_index_TripleIndex index;
    int64_t size;
};
typedef struct slop_rdf_index_IndexedGraph slop_rdf_index_IndexedGraph;

struct slop_rdf_rdf_Graph {
    slop_list_slop_rdf_rdf_Triple triples;
    slop_rdf_rdf_GraphSize size;
};
typedef struct slop_rdf_rdf_Graph slop_rdf_rdf_Graph;

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

struct slop_rdf_rdf_Triple {
    slop_rdf_rdf_Term subject;
    slop_rdf_rdf_Term predicate;
    slop_rdf_rdf_Term object;
};
typedef struct slop_rdf_rdf_Triple slop_rdf_rdf_Triple;

/* Public API */
slop_map* growl_collect_annotation_properties(slop_arena* arena, slop_rdf_rdf_Graph g);
growl_types_ReasonerConfig growl_default_config(void);
slop_rdf_index_IndexedGraph growl_filter_annotations(slop_arena* arena, slop_rdf_index_IndexedGraph ig);
int64_t growl_get_inferred_count(growl_types_ReasonerResult result);
slop_list_slop_rdf_rdf_Term growl_get_same_as(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term individual);
slop_list_slop_rdf_rdf_Term growl_get_types(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term individual);
slop_rdf_index_IndexedGraph growl_graph_to_indexed(slop_arena* arena, slop_rdf_rdf_Graph g, slop_map* annot_set);
slop_rdf_rdf_Graph growl_indexed_to_graph(slop_arena* arena, slop_rdf_index_IndexedGraph ig);
uint8_t growl_is_consistent(slop_arena* arena, slop_rdf_index_IndexedGraph input);
growl_types_ReasonerResult growl_reason(slop_arena* arena, slop_rdf_index_IndexedGraph input);
growl_types_ReasonerResult growl_reason_with_config(slop_arena* arena, slop_rdf_index_IndexedGraph input, growl_types_ReasonerConfig config);
uint8_t rdf_blank_eq(slop_rdf_rdf_BlankNode a, slop_rdf_rdf_BlankNode b);
slop_rdf_rdf_Graph rdf_graph_add(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
slop_rdf_rdf_Graph rdf_graph_add_unchecked(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
uint8_t rdf_graph_contains(slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
void rdf_graph_free(slop_rdf_rdf_Graph* g);
slop_rdf_rdf_Graph rdf_graph_match(slop_arena* arena, slop_rdf_rdf_Graph g, slop_option_slop_rdf_rdf_Term subject, slop_option_slop_rdf_rdf_Term predicate, slop_option_slop_rdf_rdf_Term object);
slop_rdf_rdf_Graph rdf_graph_remove(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Triple t);
slop_rdf_rdf_GraphSize rdf_graph_size(slop_rdf_rdf_Graph g);
slop_rdf_index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t);
uint8_t rdf_indexed_graph_contains(slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t);
slop_rdf_index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena);
void rdf_indexed_graph_for_each(slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj, slop_closure_t callback);
slop_list_slop_rdf_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj);
slop_list_slop_rdf_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term subj, slop_rdf_rdf_Term pred);
int64_t rdf_indexed_graph_size(slop_rdf_index_IndexedGraph g);
slop_list_slop_rdf_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term pred, slop_rdf_rdf_Term obj);
uint8_t rdf_iri_eq(slop_rdf_rdf_IRI a, slop_rdf_rdf_IRI b);
uint8_t rdf_list_contains(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Term head, slop_rdf_rdf_Term element);
slop_list_slop_rdf_rdf_Term rdf_list_elements(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Term head);
slop_list_slop_rdf_rdf_Term rdf_list_elements_indexed(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term head);
int64_t rdf_list_length(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Term head);
uint8_t rdf_literal_eq(slop_rdf_rdf_Literal a, slop_rdf_rdf_Literal b);
slop_rdf_rdf_Term rdf_make_blank(slop_arena* arena, slop_rdf_rdf_BlankNodeId id);
slop_rdf_rdf_Graph rdf_make_graph(slop_arena* arena);
slop_rdf_rdf_Term rdf_make_iri(slop_arena* arena, slop_string value);
slop_rdf_rdf_Term rdf_make_literal(slop_arena* arena, slop_string value, slop_option_string datatype, slop_option_string lang);
slop_rdf_rdf_Triple rdf_make_triple(slop_arena* arena, slop_rdf_rdf_Term subject, slop_rdf_rdf_Term predicate, slop_rdf_rdf_Term object);
slop_rdf_rdf_Term rdf_make_triple_term(slop_arena* arena, slop_rdf_rdf_Triple t);
uint8_t rdf_option_string_eq(slop_option_string a, slop_option_string b);
uint8_t rdf_term_eq(slop_rdf_rdf_Term a, slop_rdf_rdf_Term b);
void rdf_term_free(slop_rdf_rdf_Term* t);
slop_rdf_rdf_TermKind rdf_term_kind(slop_rdf_rdf_Term t);
uint8_t rdf_triple_eq(slop_rdf_rdf_Triple a, slop_rdf_rdf_Triple b);
void rdf_triple_free(slop_rdf_rdf_Triple* t);
slop_rdf_rdf_Term rdf_triple_object(slop_rdf_rdf_Triple t);
slop_rdf_rdf_Term rdf_triple_predicate(slop_rdf_rdf_Triple t);
slop_rdf_rdf_Term rdf_triple_subject(slop_rdf_rdf_Triple t);
slop_rdf_xsd_XsdCompareResult xsd_compare(slop_arena* arena, slop_rdf_rdf_Term a, slop_rdf_rdf_Term b);
slop_rdf_xsd_XsdCompareResult xsd_float_cmp(double a, double b);
slop_result_u8_slop_rdf_xsd_XsdError xsd_literal_values_equal(slop_arena* arena, slop_rdf_rdf_Literal a, slop_rdf_rdf_Literal b);
slop_rdf_xsd_XsdType xsd_parse_type(slop_string datatype_iri);
slop_result_slop_rdf_xsd_XsdValue_slop_rdf_xsd_XsdError xsd_parse_value(slop_arena* arena, slop_string lexical, slop_rdf_xsd_XsdType dtype);
uint8_t xsd_types_compatible(slop_rdf_xsd_XsdType t1, slop_rdf_xsd_XsdType t2);
uint8_t xsd_validate_lexical(slop_string lexical, slop_string datatype_iri);
slop_rdf_xsd_XsdCompareResult xsd_values_compare(slop_rdf_xsd_XsdValue a, slop_rdf_xsd_XsdValue b);
uint8_t xsd_values_equal(slop_rdf_xsd_XsdValue a, slop_rdf_xsd_XsdValue b);

#define growl_filter_collect_annotation_properties growl_collect_annotation_properties
#define growl_filter_filter_annotations growl_filter_annotations
#define growl_filter_graph_to_indexed growl_graph_to_indexed
#define growl_filter_indexed_to_graph growl_indexed_to_graph
#define slop_rdf_index_indexed_graph_add rdf_indexed_graph_add
#define slop_rdf_index_indexed_graph_contains rdf_indexed_graph_contains
#define slop_rdf_index_indexed_graph_create rdf_indexed_graph_create
#define slop_rdf_index_indexed_graph_for_each rdf_indexed_graph_for_each
#define slop_rdf_index_indexed_graph_match rdf_indexed_graph_match
#define slop_rdf_index_indexed_graph_objects rdf_indexed_graph_objects
#define slop_rdf_index_indexed_graph_size rdf_indexed_graph_size
#define slop_rdf_index_indexed_graph_subjects rdf_indexed_graph_subjects
#define slop_rdf_list_rdf_list_contains rdf_list_contains
#define slop_rdf_list_rdf_list_elements rdf_list_elements
#define slop_rdf_list_rdf_list_elements_indexed rdf_list_elements_indexed
#define slop_rdf_list_rdf_list_length rdf_list_length
#define slop_rdf_rdf_blank_eq rdf_blank_eq
#define slop_rdf_rdf_graph_add rdf_graph_add
#define slop_rdf_rdf_graph_add_unchecked rdf_graph_add_unchecked
#define slop_rdf_rdf_graph_contains rdf_graph_contains
#define slop_rdf_rdf_graph_free rdf_graph_free
#define slop_rdf_rdf_graph_match rdf_graph_match
#define slop_rdf_rdf_graph_remove rdf_graph_remove
#define slop_rdf_rdf_graph_size rdf_graph_size
#define slop_rdf_rdf_iri_eq rdf_iri_eq
#define slop_rdf_rdf_literal_eq rdf_literal_eq
#define slop_rdf_rdf_make_blank rdf_make_blank
#define slop_rdf_rdf_make_graph rdf_make_graph
#define slop_rdf_rdf_make_iri rdf_make_iri
#define slop_rdf_rdf_make_literal rdf_make_literal
#define slop_rdf_rdf_make_triple rdf_make_triple
#define slop_rdf_rdf_make_triple_term rdf_make_triple_term
#define slop_rdf_rdf_option_string_eq rdf_option_string_eq
#define slop_rdf_rdf_term_eq rdf_term_eq
#define slop_rdf_rdf_term_free rdf_term_free
#define slop_rdf_rdf_term_kind rdf_term_kind
#define slop_rdf_rdf_triple_eq rdf_triple_eq
#define slop_rdf_rdf_triple_free rdf_triple_free
#define slop_rdf_rdf_triple_object rdf_triple_object
#define slop_rdf_rdf_triple_predicate rdf_triple_predicate
#define slop_rdf_rdf_triple_subject rdf_triple_subject
#define slop_rdf_xsd_float_cmp xsd_float_cmp
#define slop_rdf_xsd_literal_values_equal xsd_literal_values_equal
#define slop_rdf_xsd_xsd_compare xsd_compare
#define slop_rdf_xsd_xsd_parse_type xsd_parse_type
#define slop_rdf_xsd_xsd_parse_value xsd_parse_value
#define slop_rdf_xsd_xsd_types_compatible xsd_types_compatible
#define slop_rdf_xsd_xsd_validate_lexical xsd_validate_lexical
#define slop_rdf_xsd_xsd_values_compare xsd_values_compare
#define slop_rdf_xsd_xsd_values_equal xsd_values_equal

#ifdef __cplusplus
}
#endif

#endif /* GROWL_H */
