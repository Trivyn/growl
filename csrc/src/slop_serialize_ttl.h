#ifndef SLOP_serialize_ttl_H
#define SLOP_serialize_ttl_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_ttl.h"
#include "slop_vocab.h"
#include "slop_file.h"
#include "slop_strlib.h"
#include <stdio.h>

typedef struct serialize_ttl_SerializeConfig serialize_ttl_SerializeConfig;
typedef struct serialize_ttl_SerializeError serialize_ttl_SerializeError;
typedef struct serialize_ttl_TtlFileError serialize_ttl_TtlFileError;
typedef struct serialize_ttl_ObjectGroup serialize_ttl_ObjectGroup;
typedef struct serialize_ttl_SubjectGroup serialize_ttl_SubjectGroup;

#ifndef SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_DEFINED
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

struct serialize_ttl_SerializeConfig {
    ttl_PrefixMap prefixes;
    slop_option_string base_iri;
    int64_t indent_width;
};
typedef struct serialize_ttl_SerializeConfig serialize_ttl_SerializeConfig;

#ifndef SLOP_OPTION_SERIALIZE_TTL_SERIALIZECONFIG_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_SERIALIZECONFIG_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_SerializeConfig, slop_option_serialize_ttl_SerializeConfig)
#endif

struct serialize_ttl_SerializeError {
    slop_string message;
};
typedef struct serialize_ttl_SerializeError serialize_ttl_SerializeError;

#ifndef SLOP_OPTION_SERIALIZE_TTL_SERIALIZEERROR_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_SERIALIZEERROR_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_SerializeError, slop_option_serialize_ttl_SerializeError)
#endif

typedef enum {
    serialize_ttl_TtlFileError_serialize_error,
    serialize_ttl_TtlFileError_file_error
} serialize_ttl_TtlFileError_tag;

struct serialize_ttl_TtlFileError {
    serialize_ttl_TtlFileError_tag tag;
    union {
        serialize_ttl_SerializeError serialize_error;
        file_FileError file_error;
    } data;
};
typedef struct serialize_ttl_TtlFileError serialize_ttl_TtlFileError;

#ifndef SLOP_OPTION_SERIALIZE_TTL_TTLFILEERROR_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_TTLFILEERROR_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_TtlFileError, slop_option_serialize_ttl_TtlFileError)
#endif

struct serialize_ttl_ObjectGroup {
    rdf_Term predicate;
    slop_list_rdf_Term objects;
};
typedef struct serialize_ttl_ObjectGroup serialize_ttl_ObjectGroup;

#ifndef SLOP_OPTION_SERIALIZE_TTL_OBJECTGROUP_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_OBJECTGROUP_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_ObjectGroup, slop_option_serialize_ttl_ObjectGroup)
#endif

#ifndef SLOP_LIST_SERIALIZE_TTL_OBJECTGROUP_DEFINED
#define SLOP_LIST_SERIALIZE_TTL_OBJECTGROUP_DEFINED
SLOP_LIST_DEFINE(serialize_ttl_ObjectGroup, slop_list_serialize_ttl_ObjectGroup)
#endif

struct serialize_ttl_SubjectGroup {
    rdf_Term subject;
    slop_list_serialize_ttl_ObjectGroup pred_groups;
};
typedef struct serialize_ttl_SubjectGroup serialize_ttl_SubjectGroup;

#ifndef SLOP_OPTION_SERIALIZE_TTL_SUBJECTGROUP_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_SUBJECTGROUP_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_SubjectGroup, slop_option_serialize_ttl_SubjectGroup)
#endif

#ifndef SLOP_LIST_SERIALIZE_TTL_SUBJECTGROUP_DEFINED
#define SLOP_LIST_SERIALIZE_TTL_SUBJECTGROUP_DEFINED
SLOP_LIST_DEFINE(serialize_ttl_SubjectGroup, slop_list_serialize_ttl_SubjectGroup)
#endif

#ifndef SLOP_RESULT_U8_SERIALIZE_TTL_TTLFILEERROR_DEFINED
#define SLOP_RESULT_U8_SERIALIZE_TTL_TTLFILEERROR_DEFINED
typedef struct { bool is_ok; union { uint8_t ok; serialize_ttl_TtlFileError err; } data; } slop_result_u8_serialize_ttl_TtlFileError;
#endif

slop_string serialize_ttl_escape_string_char(slop_arena* arena, uint8_t c);
uint8_t serialize_ttl_needs_escaping(slop_string s);
slop_string serialize_ttl_escape_string(slop_arena* arena, slop_string s);
uint8_t serialize_ttl_string_contains_newline(slop_string s);
uint8_t serialize_ttl_valid_pn_local(slop_string s);
slop_string serialize_ttl_serialize_iri(slop_arena* arena, rdf_IRI iri, ttl_PrefixMap prefixes);
slop_string serialize_ttl_serialize_literal(slop_arena* arena, rdf_Literal lit);
slop_string serialize_ttl_serialize_blank(slop_arena* arena, rdf_BlankNode node);
slop_string serialize_ttl_serialize_term(slop_arena* arena, rdf_Term t, ttl_PrefixMap prefixes);
slop_string serialize_ttl_serialize_prefixes(slop_arena* arena, ttl_PrefixMap prefixes);
slop_string serialize_ttl_serialize_base(slop_arena* arena, slop_option_string base);
slop_string serialize_ttl_make_indent(slop_arena* arena, int64_t width);
slop_option_int serialize_ttl_find_subject_group(slop_list_serialize_ttl_SubjectGroup groups, rdf_Term subj);
slop_option_int serialize_ttl_find_pred_group(slop_list_serialize_ttl_ObjectGroup groups, rdf_Term pred);
slop_list_serialize_ttl_SubjectGroup serialize_ttl_build_groups(slop_arena* arena, rdf_Graph g);
slop_string serialize_ttl_serialize_ttl_string(slop_arena* arena, rdf_Graph g, serialize_ttl_SerializeConfig config);
slop_result_u8_serialize_ttl_TtlFileError serialize_ttl_serialize_ttl_file(slop_arena* arena, rdf_Graph g, serialize_ttl_SerializeConfig config, slop_string path);
void serialize_ttl_emit_str(void* handle, slop_string s);
slop_result_u8_serialize_ttl_TtlFileError serialize_ttl_serialize_ttl_stream(slop_arena* arena, rdf_Graph g, serialize_ttl_SerializeConfig config, slop_string path);

#ifndef SLOP_OPTION_SERIALIZE_TTL_SERIALIZECONFIG_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_SERIALIZECONFIG_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_SerializeConfig, slop_option_serialize_ttl_SerializeConfig)
#endif

#ifndef SLOP_OPTION_SERIALIZE_TTL_SERIALIZEERROR_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_SERIALIZEERROR_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_SerializeError, slop_option_serialize_ttl_SerializeError)
#endif

#ifndef SLOP_OPTION_SERIALIZE_TTL_TTLFILEERROR_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_TTLFILEERROR_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_TtlFileError, slop_option_serialize_ttl_TtlFileError)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

#ifndef SLOP_OPTION_SERIALIZE_TTL_OBJECTGROUP_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_OBJECTGROUP_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_ObjectGroup, slop_option_serialize_ttl_ObjectGroup)
#endif

#ifndef SLOP_OPTION_SERIALIZE_TTL_SUBJECTGROUP_DEFINED
#define SLOP_OPTION_SERIALIZE_TTL_SUBJECTGROUP_DEFINED
SLOP_OPTION_DEFINE(serialize_ttl_SubjectGroup, slop_option_serialize_ttl_SubjectGroup)
#endif


#endif
