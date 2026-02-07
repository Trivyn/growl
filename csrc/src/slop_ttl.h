#ifndef SLOP_ttl_H
#define SLOP_ttl_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_common.h"
#include "slop_file.h"
#include "slop_strlib.h"

typedef struct ttl_PrefixBinding ttl_PrefixBinding;
typedef struct ttl_PrefixMap ttl_PrefixMap;
typedef struct ttl_GenBlankResult ttl_GenBlankResult;
typedef struct ttl_TermResult ttl_TermResult;
typedef struct ttl_StringResult ttl_StringResult;
typedef struct ttl_EscapeResult ttl_EscapeResult;
typedef struct ttl_TripleResult ttl_TripleResult;
typedef struct ttl_TriplesResult ttl_TriplesResult;
typedef struct ttl_TermTriplesResult ttl_TermTriplesResult;
typedef struct ttl_TtlFileError ttl_TtlFileError;
typedef struct ttl_TtlParseContext ttl_TtlParseContext;

typedef int64_t ttl_BlankNodeCounter;

static inline ttl_BlankNodeCounter ttl_BlankNodeCounter_new(int64_t v) {
SLOP_PRE(v >= 0, "ttl_BlankNodeCounter >= 0");
return (ttl_BlankNodeCounter)v;
}

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

struct ttl_PrefixBinding {
    slop_string prefix;
    slop_string iri;
};
typedef struct ttl_PrefixBinding ttl_PrefixBinding;

#ifndef SLOP_OPTION_TTL_PREFIXBINDING_DEFINED
#define SLOP_OPTION_TTL_PREFIXBINDING_DEFINED
SLOP_OPTION_DEFINE(ttl_PrefixBinding, slop_option_ttl_PrefixBinding)
#endif

#ifndef SLOP_LIST_TTL_PREFIXBINDING_DEFINED
#define SLOP_LIST_TTL_PREFIXBINDING_DEFINED
SLOP_LIST_DEFINE(ttl_PrefixBinding, slop_list_ttl_PrefixBinding)
#endif

struct ttl_PrefixMap {
    slop_list_ttl_PrefixBinding bindings;
    int64_t count;
};
typedef struct ttl_PrefixMap ttl_PrefixMap;

#ifndef SLOP_OPTION_TTL_PREFIXMAP_DEFINED
#define SLOP_OPTION_TTL_PREFIXMAP_DEFINED
SLOP_OPTION_DEFINE(ttl_PrefixMap, slop_option_ttl_PrefixMap)
#endif

typedef enum {
    ttl_TtlFileError_parse_error,
    ttl_TtlFileError_file_error
} ttl_TtlFileError_tag;

struct ttl_TtlFileError {
    ttl_TtlFileError_tag tag;
    union {
        common_ParseError parse_error;
        file_FileError file_error;
    } data;
};
typedef struct ttl_TtlFileError ttl_TtlFileError;

#ifndef SLOP_OPTION_TTL_TTLFILEERROR_DEFINED
#define SLOP_OPTION_TTL_TTLFILEERROR_DEFINED
SLOP_OPTION_DEFINE(ttl_TtlFileError, slop_option_ttl_TtlFileError)
#endif

struct ttl_TtlParseContext {
    ttl_PrefixMap prefixes;
    slop_option_string base_iri;
    ttl_BlankNodeCounter blank_counter;
    common_ParseState state;
};
typedef struct ttl_TtlParseContext ttl_TtlParseContext;

#ifndef SLOP_OPTION_TTL_TTLPARSECONTEXT_DEFINED
#define SLOP_OPTION_TTL_TTLPARSECONTEXT_DEFINED
SLOP_OPTION_DEFINE(ttl_TtlParseContext, slop_option_ttl_TtlParseContext)
#endif

struct ttl_GenBlankResult {
    int64_t id;
    ttl_TtlParseContext ctx;
};
typedef struct ttl_GenBlankResult ttl_GenBlankResult;

#ifndef SLOP_OPTION_TTL_GENBLANKRESULT_DEFINED
#define SLOP_OPTION_TTL_GENBLANKRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_GenBlankResult, slop_option_ttl_GenBlankResult)
#endif

struct ttl_TermResult {
    rdf_Term term;
    ttl_TtlParseContext ctx;
};
typedef struct ttl_TermResult ttl_TermResult;

#ifndef SLOP_OPTION_TTL_TERMRESULT_DEFINED
#define SLOP_OPTION_TTL_TERMRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TermResult, slop_option_ttl_TermResult)
#endif

struct ttl_StringResult {
    slop_string value;
    ttl_TtlParseContext ctx;
};
typedef struct ttl_StringResult ttl_StringResult;

#ifndef SLOP_OPTION_TTL_STRINGRESULT_DEFINED
#define SLOP_OPTION_TTL_STRINGRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_StringResult, slop_option_ttl_StringResult)
#endif

struct ttl_EscapeResult {
    uint8_t slop_char;
    ttl_TtlParseContext ctx;
};
typedef struct ttl_EscapeResult ttl_EscapeResult;

#ifndef SLOP_OPTION_TTL_ESCAPERESULT_DEFINED
#define SLOP_OPTION_TTL_ESCAPERESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_EscapeResult, slop_option_ttl_EscapeResult)
#endif

struct ttl_TripleResult {
    rdf_Triple triple;
    ttl_TtlParseContext ctx;
};
typedef struct ttl_TripleResult ttl_TripleResult;

#ifndef SLOP_OPTION_TTL_TRIPLERESULT_DEFINED
#define SLOP_OPTION_TTL_TRIPLERESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TripleResult, slop_option_ttl_TripleResult)
#endif

struct ttl_TriplesResult {
    slop_list_rdf_Triple triples;
    ttl_TtlParseContext ctx;
};
typedef struct ttl_TriplesResult ttl_TriplesResult;

#ifndef SLOP_OPTION_TTL_TRIPLESRESULT_DEFINED
#define SLOP_OPTION_TTL_TRIPLESRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TriplesResult, slop_option_ttl_TriplesResult)
#endif

struct ttl_TermTriplesResult {
    rdf_Term term;
    slop_list_rdf_Triple extra_triples;
    ttl_TtlParseContext ctx;
};
typedef struct ttl_TermTriplesResult ttl_TermTriplesResult;

#ifndef SLOP_OPTION_TTL_TERMTRIPLESRESULT_DEFINED
#define SLOP_OPTION_TTL_TERMTRIPLESRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TermTriplesResult, slop_option_ttl_TermTriplesResult)
#endif

#ifndef SLOP_RESULT_TTL_TERMRESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_TTL_TERMRESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { ttl_TermResult ok; common_ParseError err; } data; } slop_result_ttl_TermResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_TTL_TERMTRIPLESRESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_TTL_TERMTRIPLESRESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { ttl_TermTriplesResult ok; common_ParseError err; } data; } slop_result_ttl_TermTriplesResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_TTL_STRINGRESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_TTL_STRINGRESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { ttl_StringResult ok; common_ParseError err; } data; } slop_result_ttl_StringResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_TTL_ESCAPERESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_TTL_ESCAPERESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { ttl_EscapeResult ok; common_ParseError err; } data; } slop_result_ttl_EscapeResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_TTL_TTLPARSECONTEXT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_TTL_TTLPARSECONTEXT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { ttl_TtlParseContext ok; common_ParseError err; } data; } slop_result_ttl_TtlParseContext_common_ParseError;
#endif

#ifndef SLOP_RESULT_TTL_TRIPLERESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_TTL_TRIPLERESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { ttl_TripleResult ok; common_ParseError err; } data; } slop_result_ttl_TripleResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_TTL_TRIPLESRESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_TTL_TRIPLESRESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { ttl_TriplesResult ok; common_ParseError err; } data; } slop_result_ttl_TriplesResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_RDF_GRAPH_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_RDF_GRAPH_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { rdf_Graph ok; common_ParseError err; } data; } slop_result_rdf_Graph_common_ParseError;
#endif

#ifndef SLOP_RESULT_RDF_GRAPH_TTL_TTLFILEERROR_DEFINED
#define SLOP_RESULT_RDF_GRAPH_TTL_TTLFILEERROR_DEFINED
typedef struct { bool is_ok; union { rdf_Graph ok; ttl_TtlFileError err; } data; } slop_result_rdf_Graph_ttl_TtlFileError;
#endif

ttl_PrefixMap ttl_make_prefix_map(slop_arena* arena);
ttl_PrefixMap ttl_prefix_map_add(slop_arena* arena, ttl_PrefixMap pm, slop_string prefix, slop_string iri);
slop_option_string ttl_prefix_map_lookup(ttl_PrefixMap pm, slop_string prefix);
ttl_TtlParseContext ttl_make_ttl_context(slop_arena* arena, slop_string input);
ttl_GenBlankResult ttl_context_gen_blank_id(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_iri_ref(slop_arena* arena, ttl_TtlParseContext ctx);
common_ParseWhileResult ttl_parse_pn_local(slop_arena* arena, common_ParseState state);
slop_result_ttl_TermResult_common_ParseError ttl_parse_prefixed_name(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_blank_node_extended(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_blank_node(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StringResult_common_ParseError ttl_parse_string_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_EscapeResult_common_ParseError ttl_parse_escape_sequence(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_numeric_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_boolean_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_term(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_collection(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_term_extended(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_directive(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_sparql_prefix(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TripleResult_common_ParseError ttl_parse_triple(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TriplesResult_common_ParseError ttl_parse_predicate_object_list(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject);
slop_result_ttl_TriplesResult_common_ParseError ttl_parse_object_list(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, rdf_Term predicate);
slop_result_rdf_Graph_common_ParseError ttl_parse_ttl_string(slop_arena* arena, slop_string input);
slop_result_rdf_Graph_ttl_TtlFileError ttl_parse_ttl_file(slop_arena* arena, slop_string path);
uint8_t ttl_is_pn_chars_base(uint8_t c);
uint8_t ttl_is_pn_chars(uint8_t c);

#ifndef SLOP_OPTION_TTL_PREFIXBINDING_DEFINED
#define SLOP_OPTION_TTL_PREFIXBINDING_DEFINED
SLOP_OPTION_DEFINE(ttl_PrefixBinding, slop_option_ttl_PrefixBinding)
#endif

#ifndef SLOP_OPTION_TTL_PREFIXMAP_DEFINED
#define SLOP_OPTION_TTL_PREFIXMAP_DEFINED
SLOP_OPTION_DEFINE(ttl_PrefixMap, slop_option_ttl_PrefixMap)
#endif

#ifndef SLOP_OPTION_TTL_GENBLANKRESULT_DEFINED
#define SLOP_OPTION_TTL_GENBLANKRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_GenBlankResult, slop_option_ttl_GenBlankResult)
#endif

#ifndef SLOP_OPTION_TTL_TERMRESULT_DEFINED
#define SLOP_OPTION_TTL_TERMRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TermResult, slop_option_ttl_TermResult)
#endif

#ifndef SLOP_OPTION_TTL_STRINGRESULT_DEFINED
#define SLOP_OPTION_TTL_STRINGRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_StringResult, slop_option_ttl_StringResult)
#endif

#ifndef SLOP_OPTION_TTL_ESCAPERESULT_DEFINED
#define SLOP_OPTION_TTL_ESCAPERESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_EscapeResult, slop_option_ttl_EscapeResult)
#endif

#ifndef SLOP_OPTION_TTL_TRIPLERESULT_DEFINED
#define SLOP_OPTION_TTL_TRIPLERESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TripleResult, slop_option_ttl_TripleResult)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_TTL_TRIPLESRESULT_DEFINED
#define SLOP_OPTION_TTL_TRIPLESRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TriplesResult, slop_option_ttl_TriplesResult)
#endif

#ifndef SLOP_OPTION_TTL_TERMTRIPLESRESULT_DEFINED
#define SLOP_OPTION_TTL_TERMTRIPLESRESULT_DEFINED
SLOP_OPTION_DEFINE(ttl_TermTriplesResult, slop_option_ttl_TermTriplesResult)
#endif

#ifndef SLOP_OPTION_TTL_TTLFILEERROR_DEFINED
#define SLOP_OPTION_TTL_TTLFILEERROR_DEFINED
SLOP_OPTION_DEFINE(ttl_TtlFileError, slop_option_ttl_TtlFileError)
#endif

#ifndef SLOP_OPTION_TTL_TTLPARSECONTEXT_DEFINED
#define SLOP_OPTION_TTL_TTLPARSECONTEXT_DEFINED
SLOP_OPTION_DEFINE(ttl_TtlParseContext, slop_option_ttl_TtlParseContext)
#endif


#endif
