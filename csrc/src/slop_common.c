#include "../runtime/slop_runtime.h"
#include "slop_common.h"

common_ParseError common_make_parse_error(slop_arena* arena, common_ParseErrorKind kind, slop_string msg, common_Position pos);
common_ParseState common_make_parse_state(slop_arena* arena, slop_string input);
uint8_t common_state_at_end(common_ParseState state);
uint8_t common_state_peek(common_ParseState state);
uint8_t common_state_peek_n(common_ParseState state, int64_t n);
common_ParseState common_state_advance(slop_arena* arena, common_ParseState state);
common_ParseState common_state_with_position(common_ParseState state, int64_t offset, int64_t line, int64_t column);
common_ParseState common_skip_whitespace(slop_arena* arena, common_ParseState state);
common_ParseState common_skip_line(slop_arena* arena, common_ParseState state);
slop_result_common_ParseState_common_ParseError common_expect_char(slop_arena* arena, common_ParseState state, uint8_t expected);
common_ParseWhileResult common_parse_while(slop_arena* arena, common_ParseState state, slop_closure_t predicate);
slop_result_common_ParseWhileResult_common_ParseError common_parse_until(slop_arena* arena, common_ParseState state, uint8_t terminator);

common_ParseError common_make_parse_error(slop_arena* arena, common_ParseErrorKind kind, slop_string msg, common_Position pos) {
    return ((common_ParseError){.kind = kind, .message = msg, .position = pos});
}

common_ParseState common_make_parse_state(slop_arena* arena, slop_string input) {
    common_ParseState _retval = {0};
    _retval = ((common_ParseState){.input = input, .offset = 0, .line = 1, .column = 1});
    SLOP_POST(((_retval.offset == 0)), "(== $result.offset 0)");
    SLOP_POST(((_retval.line == 1)), "(== $result.line 1)");
    SLOP_POST(((_retval.column == 1)), "(== $result.column 1)");
    return _retval;
}

uint8_t common_state_at_end(common_ParseState state) {
    uint8_t _retval = {0};
    _retval = (state.offset >= string_len(state.input));
    SLOP_POST(((_retval == (state.offset >= string_len(state.input)))), "(== $result (>= (. state offset) (string-len (. state input))))");
    return _retval;
}

uint8_t common_state_peek(common_ParseState state) {
    if (common_state_at_end(state)) {
        return 0;
    } else {
        return strlib_char_at(state.input, state.offset);
    }
}

uint8_t common_state_peek_n(common_ParseState state, int64_t n) {
    if ((state.offset + n) >= string_len(state.input)) {
        return 0;
    } else {
        return strlib_char_at(state.input, (state.offset + n));
    }
}

common_ParseState common_state_advance(slop_arena* arena, common_ParseState state) {
    SLOP_PRE((!(common_state_at_end(state))), "(not (state-at-end state))");
    common_ParseState _retval = {0};
    {
        __auto_type c = common_state_peek(state);
        if (c == 10) {
            _retval = ((common_ParseState){.input = state.input, .offset = (state.offset + 1), .line = (state.line + 1), .column = 1});
        } else {
            _retval = ((common_ParseState){.input = state.input, .offset = (state.offset + 1), .line = state.line, .column = (state.column + 1)});
        }
    }
    SLOP_POST(((_retval.offset == (state.offset + 1))), "(== $result.offset (+ state.offset 1))");
    return _retval;
}

common_ParseState common_state_with_position(common_ParseState state, int64_t offset, int64_t line, int64_t column) {
    return ((common_ParseState){.input = state.input, .offset = offset, .line = line, .column = column});
}

common_ParseState common_skip_whitespace(slop_arena* arena, common_ParseState state) {
    common_ParseState _retval = {0};
    {
        __auto_type input = state.input;
        __auto_type len = string_len(state.input);
        int64_t offset = state.offset;
        int64_t line = state.line;
        int64_t column = state.column;
        uint8_t done = 0;
        while (!(done) && (offset < len)) {
            {
                __auto_type c = strlib_char_at(input, offset);
                if (c == 35) {
                    while ((offset < len) && (strlib_char_at(input, offset) != 10)) {
                        offset = (offset + 1);
                        column = (column + 1);
                    }
                    if (offset < len) {
                        offset = (offset + 1);
                        line = (line + 1);
                        column = 1;
                    }
                } else if (strlib_is_space(c)) {
                    offset = (offset + 1);
                    if (c == 10) {
                        line = (line + 1);
                        column = 1;
                    } else {
                        column = (column + 1);
                    }
                } else {
                    done = 1;
                }
            }
        }
        _retval = common_state_with_position(state, offset, line, column);
    }
    SLOP_POST(((common_state_at_end(_retval) || !(strlib_is_space(common_state_peek(_retval))))), "(or (state-at-end $result) (not (is-space (state-peek $result))))");
    return _retval;
}

common_ParseState common_skip_line(slop_arena* arena, common_ParseState state) {
    {
        __auto_type input = state.input;
        __auto_type len = string_len(state.input);
        int64_t offset = state.offset;
        int64_t column = state.column;
        while ((offset < len) && (strlib_char_at(input, offset) != 10)) {
            offset = (offset + 1);
            column = (column + 1);
        }
        if (offset < len) {
            return common_state_with_position(state, (offset + 1), (state.line + 1), 1);
        } else {
            return common_state_with_position(state, offset, state.line, column);
        }
    }
}

slop_result_common_ParseState_common_ParseError common_expect_char(slop_arena* arena, common_ParseState state, uint8_t expected) {
    if (common_state_at_end(state)) {
        return ((slop_result_common_ParseState_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unexpected_eof, SLOP_STR("Unexpected end of input"), ((common_Position){.line = state.line, .column = state.column, .offset = state.offset})) });
    } else {
        if (common_state_peek(state) == expected) {
            return ((slop_result_common_ParseState_common_ParseError){ .is_ok = true, .data.ok = common_state_advance(arena, state) });
        } else {
            return ((slop_result_common_ParseState_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unexpected_char, SLOP_STR("Unexpected character"), ((common_Position){.line = state.line, .column = state.column, .offset = state.offset})) });
        }
    }
}

common_ParseWhileResult common_parse_while(slop_arena* arena, common_ParseState state, slop_closure_t predicate) {
    {
        __auto_type input = state.input;
        __auto_type len = string_len(state.input);
        __auto_type start = state.offset;
        int64_t offset = state.offset;
        int64_t line = state.line;
        int64_t column = state.column;
        while ((offset < len) && ((uint8_t(*)(void*, int64_t))predicate.fn)(predicate.env, strlib_char_at(input, offset))) {
            {
                __auto_type c = strlib_char_at(input, offset);
                offset = (offset + 1);
                if (c == 10) {
                    line = (line + 1);
                    column = 1;
                } else {
                    column = (column + 1);
                }
            }
        }
        return ((common_ParseWhileResult){.result = strlib_substring(arena, input, start, (offset - start)), .state = common_state_with_position(state, offset, line, column)});
    }
}

slop_result_common_ParseWhileResult_common_ParseError common_parse_until(slop_arena* arena, common_ParseState state, uint8_t terminator) {
    {
        __auto_type input = state.input;
        __auto_type len = string_len(state.input);
        __auto_type start = state.offset;
        int64_t offset = state.offset;
        int64_t line = state.line;
        int64_t column = state.column;
        while ((offset < len) && (strlib_char_at(input, offset) != terminator)) {
            {
                __auto_type c = strlib_char_at(input, offset);
                offset = (offset + 1);
                if (c == 10) {
                    line = (line + 1);
                    column = 1;
                } else {
                    column = (column + 1);
                }
            }
        }
        if (offset >= len) {
            return ((slop_result_common_ParseWhileResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unexpected_eof, SLOP_STR("Unexpected end of input"), ((common_Position){.line = line, .column = column, .offset = offset})) });
        } else {
            {
                __auto_type end = offset;
                __auto_type c = strlib_char_at(input, offset);
                offset = (offset + 1);
                if (c == 10) {
                    line = (line + 1);
                    column = 1;
                } else {
                    column = (column + 1);
                }
                return ((slop_result_common_ParseWhileResult_common_ParseError){ .is_ok = true, .data.ok = ((common_ParseWhileResult){.result = strlib_substring(arena, input, start, (end - start)), .state = common_state_with_position(state, offset, line, column)}) });
            }
        }
    }
}

