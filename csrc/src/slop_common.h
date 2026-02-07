#ifndef SLOP_common_H
#define SLOP_common_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_strlib.h"

typedef struct common_Position common_Position;
typedef struct common_ParseError common_ParseError;
typedef struct common_ParseState common_ParseState;
typedef struct common_ParseWhileResult common_ParseWhileResult;

typedef enum {
    common_ParseErrorKind_unexpected_char,
    common_ParseErrorKind_unexpected_eof,
    common_ParseErrorKind_invalid_iri,
    common_ParseErrorKind_invalid_prefix,
    common_ParseErrorKind_invalid_literal,
    common_ParseErrorKind_invalid_escape,
    common_ParseErrorKind_invalid_blank_node,
    common_ParseErrorKind_unterminated_string,
    common_ParseErrorKind_unterminated_iri,
    common_ParseErrorKind_missing_dot,
    common_ParseErrorKind_missing_semicolon,
    common_ParseErrorKind_duplicate_prefix,
    common_ParseErrorKind_unknown_prefix,
    common_ParseErrorKind_syntax_error
} common_ParseErrorKind;

struct common_Position {
    int64_t line;
    int64_t column;
    int64_t offset;
};
typedef struct common_Position common_Position;

#ifndef SLOP_OPTION_COMMON_POSITION_DEFINED
#define SLOP_OPTION_COMMON_POSITION_DEFINED
SLOP_OPTION_DEFINE(common_Position, slop_option_common_Position)
#endif

struct common_ParseError {
    common_ParseErrorKind kind;
    slop_string message;
    common_Position position;
};
typedef struct common_ParseError common_ParseError;

#ifndef SLOP_OPTION_COMMON_PARSEERROR_DEFINED
#define SLOP_OPTION_COMMON_PARSEERROR_DEFINED
SLOP_OPTION_DEFINE(common_ParseError, slop_option_common_ParseError)
#endif

struct common_ParseState {
    slop_string input;
    int64_t offset;
    int64_t line;
    int64_t column;
};
typedef struct common_ParseState common_ParseState;

#ifndef SLOP_OPTION_COMMON_PARSESTATE_DEFINED
#define SLOP_OPTION_COMMON_PARSESTATE_DEFINED
SLOP_OPTION_DEFINE(common_ParseState, slop_option_common_ParseState)
#endif

struct common_ParseWhileResult {
    slop_string result;
    common_ParseState state;
};
typedef struct common_ParseWhileResult common_ParseWhileResult;

#ifndef SLOP_OPTION_COMMON_PARSEWHILERESULT_DEFINED
#define SLOP_OPTION_COMMON_PARSEWHILERESULT_DEFINED
SLOP_OPTION_DEFINE(common_ParseWhileResult, slop_option_common_ParseWhileResult)
#endif

#ifndef SLOP_RESULT_COMMON_PARSESTATE_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_COMMON_PARSESTATE_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { common_ParseState ok; common_ParseError err; } data; } slop_result_common_ParseState_common_ParseError;
#endif

#ifndef SLOP_RESULT_COMMON_PARSEWHILERESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_COMMON_PARSEWHILERESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { common_ParseWhileResult ok; common_ParseError err; } data; } slop_result_common_ParseWhileResult_common_ParseError;
#endif

common_ParseError common_make_parse_error(slop_arena* arena, common_ParseErrorKind kind, slop_string msg, common_Position pos);
common_ParseState common_make_parse_state(slop_arena* arena, slop_string input);
uint8_t common_state_at_end(common_ParseState state);
uint8_t common_state_peek(common_ParseState state);
uint8_t common_state_peek_n(common_ParseState state, int64_t n);
common_ParseState common_state_advance(slop_arena* arena, common_ParseState state);
common_ParseState common_skip_whitespace(slop_arena* arena, common_ParseState state);
common_ParseState common_skip_line(slop_arena* arena, common_ParseState state);
slop_result_common_ParseState_common_ParseError common_expect_char(slop_arena* arena, common_ParseState state, uint8_t expected);
common_ParseWhileResult common_parse_while(slop_arena* arena, common_ParseState state, slop_closure_t predicate);
slop_result_common_ParseWhileResult_common_ParseError common_parse_until(slop_arena* arena, common_ParseState state, uint8_t terminator);

#ifndef SLOP_OPTION_COMMON_POSITION_DEFINED
#define SLOP_OPTION_COMMON_POSITION_DEFINED
SLOP_OPTION_DEFINE(common_Position, slop_option_common_Position)
#endif

#ifndef SLOP_OPTION_COMMON_PARSEERROR_DEFINED
#define SLOP_OPTION_COMMON_PARSEERROR_DEFINED
SLOP_OPTION_DEFINE(common_ParseError, slop_option_common_ParseError)
#endif

#ifndef SLOP_OPTION_COMMON_PARSESTATE_DEFINED
#define SLOP_OPTION_COMMON_PARSESTATE_DEFINED
SLOP_OPTION_DEFINE(common_ParseState, slop_option_common_ParseState)
#endif

#ifndef SLOP_OPTION_COMMON_PARSEWHILERESULT_DEFINED
#define SLOP_OPTION_COMMON_PARSEWHILERESULT_DEFINED
SLOP_OPTION_DEFINE(common_ParseWhileResult, slop_option_common_ParseWhileResult)
#endif


#endif
