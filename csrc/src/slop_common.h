#ifndef SLOP_common_H
#define SLOP_common_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_strlib.h"

typedef struct slop_rdf_common_Position slop_rdf_common_Position;
typedef struct slop_rdf_common_ParseError slop_rdf_common_ParseError;
typedef struct slop_rdf_common_ParseState slop_rdf_common_ParseState;
typedef struct slop_rdf_common_ParseWhileResult slop_rdf_common_ParseWhileResult;

typedef enum {
    slop_rdf_common_ParseErrorKind_unexpected_char,
    slop_rdf_common_ParseErrorKind_unexpected_eof,
    slop_rdf_common_ParseErrorKind_invalid_iri,
    slop_rdf_common_ParseErrorKind_invalid_prefix,
    slop_rdf_common_ParseErrorKind_invalid_literal,
    slop_rdf_common_ParseErrorKind_invalid_escape,
    slop_rdf_common_ParseErrorKind_invalid_blank_node,
    slop_rdf_common_ParseErrorKind_unterminated_string,
    slop_rdf_common_ParseErrorKind_unterminated_iri,
    slop_rdf_common_ParseErrorKind_missing_dot,
    slop_rdf_common_ParseErrorKind_missing_semicolon,
    slop_rdf_common_ParseErrorKind_duplicate_prefix,
    slop_rdf_common_ParseErrorKind_unknown_prefix,
    slop_rdf_common_ParseErrorKind_syntax_error
} slop_rdf_common_ParseErrorKind;

struct slop_rdf_common_Position {
    int64_t line;
    int64_t column;
    int64_t offset;
};
typedef struct slop_rdf_common_Position slop_rdf_common_Position;

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_POSITION_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_POSITION_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_Position, slop_option_slop_rdf_common_Position)
#endif

struct slop_rdf_common_ParseError {
    slop_rdf_common_ParseErrorKind kind;
    slop_string message;
    slop_rdf_common_Position position;
};
typedef struct slop_rdf_common_ParseError slop_rdf_common_ParseError;

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_PARSEERROR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_ParseError, slop_option_slop_rdf_common_ParseError)
#endif

struct slop_rdf_common_ParseState {
    slop_string input;
    int64_t offset;
    int64_t line;
    int64_t column;
};
typedef struct slop_rdf_common_ParseState slop_rdf_common_ParseState;

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_PARSESTATE_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_PARSESTATE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_ParseState, slop_option_slop_rdf_common_ParseState)
#endif

struct slop_rdf_common_ParseWhileResult {
    slop_string result;
    slop_rdf_common_ParseState state;
};
typedef struct slop_rdf_common_ParseWhileResult slop_rdf_common_ParseWhileResult;

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_PARSEWHILERESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_PARSEWHILERESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_ParseWhileResult, slop_option_slop_rdf_common_ParseWhileResult)
#endif

#ifndef SLOP_RESULT_SLOP_RDF_COMMON_PARSESTATE_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_COMMON_PARSESTATE_SLOP_RDF_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_common_ParseState ok; slop_rdf_common_ParseError err; } data; } slop_result_slop_rdf_common_ParseState_slop_rdf_common_ParseError;
#endif

#ifndef SLOP_RESULT_SLOP_RDF_COMMON_PARSEWHILERESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_COMMON_PARSEWHILERESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_common_ParseWhileResult ok; slop_rdf_common_ParseError err; } data; } slop_result_slop_rdf_common_ParseWhileResult_slop_rdf_common_ParseError;
#endif

slop_rdf_common_ParseError slop_rdf_common_make_parse_error(slop_arena* arena, slop_rdf_common_ParseErrorKind kind, slop_string msg, slop_rdf_common_Position pos);
slop_rdf_common_ParseState slop_rdf_common_make_parse_state(slop_arena* arena, slop_string input);
uint8_t slop_rdf_common_state_at_end(slop_rdf_common_ParseState state);
uint8_t slop_rdf_common_state_peek(slop_rdf_common_ParseState state);
uint8_t slop_rdf_common_state_peek_n(slop_rdf_common_ParseState state, int64_t n);
slop_rdf_common_ParseState slop_rdf_common_state_advance(slop_arena* arena, slop_rdf_common_ParseState state);
slop_rdf_common_ParseState slop_rdf_common_state_with_position(slop_rdf_common_ParseState state, int64_t offset, int64_t line, int64_t column);
slop_rdf_common_ParseState slop_rdf_common_skip_whitespace(slop_arena* arena, slop_rdf_common_ParseState state);
slop_rdf_common_ParseState slop_rdf_common_skip_line(slop_arena* arena, slop_rdf_common_ParseState state);
slop_result_slop_rdf_common_ParseState_slop_rdf_common_ParseError slop_rdf_common_expect_char(slop_arena* arena, slop_rdf_common_ParseState state, uint8_t expected);
slop_rdf_common_ParseWhileResult slop_rdf_common_parse_while(slop_arena* arena, slop_rdf_common_ParseState state, slop_closure_t predicate);
slop_result_slop_rdf_common_ParseWhileResult_slop_rdf_common_ParseError slop_rdf_common_parse_until(slop_arena* arena, slop_rdf_common_ParseState state, uint8_t terminator);

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_POSITION_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_POSITION_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_Position, slop_option_slop_rdf_common_Position)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_PARSEERROR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_ParseError, slop_option_slop_rdf_common_ParseError)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_PARSESTATE_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_PARSESTATE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_ParseState, slop_option_slop_rdf_common_ParseState)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_COMMON_PARSEWHILERESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_COMMON_PARSEWHILERESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_common_ParseWhileResult, slop_option_slop_rdf_common_ParseWhileResult)
#endif


#endif
