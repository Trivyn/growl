#include "../runtime/slop_runtime.h"
#include "slop_common.h"

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

common_ParseError common_make_parse_error(slop_arena* arena, common_ParseErrorKind kind, slop_string msg, common_Position pos) {
    return ((common_ParseError){.kind = kind, .message = msg, .position = pos});
}

common_ParseState common_make_parse_state(slop_arena* arena, slop_string input) {
    common_ParseState _retval;
    _retval = ((common_ParseState){.input = input, .offset = 0, .line = 1, .column = 1});
    SLOP_POST(((_retval.offset == 0)), "(== $result.offset 0)");
    SLOP_POST(((_retval.line == 1)), "(== $result.line 1)");
    SLOP_POST(((_retval.column == 1)), "(== $result.column 1)");
    return _retval;
}

uint8_t common_state_at_end(common_ParseState state) {
    uint8_t _retval;
    _retval = (state.offset >= string_len(state.input));
    SLOP_POST(((_retval == state.offset(>=, string_len(state.input)))), "(== $result ((. state offset) >= (string-len (. state input))))");
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
    if (((state.offset + n) >= string_len(state.input))) {
        return 0;
    } else {
        return strlib_char_at(state.input, (state.offset + n));
    }
}

common_ParseState common_state_advance(slop_arena* arena, common_ParseState state) {
    SLOP_PRE((!(common_state_at_end(state))), "(not (state-at-end state))");
    common_ParseState _retval;
    {
        __auto_type c = common_state_peek(state);
        if ((c == 10)) {
            _retval = ((common_ParseState){.input = state.input, .offset = (state.offset + 1), .line = (state.line + 1), .column = 1});
        } else {
            _retval = ((common_ParseState){.input = state.input, .offset = (state.offset + 1), .line = state.line, .column = (state.column + 1)});
        }
    }
    SLOP_POST(((_retval.offset == (state.offset + 1))), "(== $result.offset (+ state.offset 1))");
    return _retval;
}

common_ParseState common_skip_whitespace(slop_arena* arena, common_ParseState state) {
    common_ParseState _retval;
    {
        __auto_type s = state;
        while ((!(common_state_at_end(s)) && (strlib_is_space(common_state_peek(s)) || (common_state_peek(s) == 35)))) {
            if ((common_state_peek(s) == 35)) {
                s = common_skip_line(arena, s);
            } else {
                s = common_state_advance(arena, s);
            }
        }
        _retval = s;
    }
    SLOP_POST(((common_state_at_end(_retval) || !(strlib_is_space(common_state_peek(_retval))))), "(or (state-at-end $result) (not (is-space (state-peek $result))))");
    return _retval;
}

common_ParseState common_skip_line(slop_arena* arena, common_ParseState state) {
    {
        __auto_type s = state;
        while ((!(common_state_at_end(s)) && (common_state_peek(s) != 10))) {
            s = common_state_advance(arena, s);
        }
        if (!(common_state_at_end(s))) {
            return common_state_advance(arena, s);
        } else {
            return s;
        }
    }
}

slop_result_common_ParseState_common_ParseError common_expect_char(slop_arena* arena, common_ParseState state, uint8_t expected) {
    if (common_state_at_end(state)) {
        return ((slop_result_common_ParseState_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unexpected_eof, SLOP_STR("Unexpected end of input"), ((common_Position){.line = state.line, .column = state.column, .offset = state.offset})) });
    } else {
        if ((common_state_peek(state) == expected)) {
            return ((slop_result_common_ParseState_common_ParseError){ .is_ok = true, .data.ok = common_state_advance(arena, state) });
        } else {
            return ((slop_result_common_ParseState_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unexpected_char, SLOP_STR("Unexpected character"), ((common_Position){.line = state.line, .column = state.column, .offset = state.offset})) });
        }
    }
}

common_ParseWhileResult common_parse_while(slop_arena* arena, common_ParseState state, slop_closure_t predicate) {
    {
        __auto_type start = state.offset;
        __auto_type s = state;
        while ((!(common_state_at_end(s)) && ((uint8_t(*)(void*, int64_t))predicate.fn)(predicate.env, common_state_peek(s)))) {
            s = common_state_advance(arena, s);
        }
        return ((common_ParseWhileResult){.result = strlib_substring(arena, state.input, start, (s.offset - start)), .state = s});
    }
}

slop_result_common_ParseWhileResult_common_ParseError common_parse_until(slop_arena* arena, common_ParseState state, uint8_t terminator) {
    {
        __auto_type start = state.offset;
        __auto_type s = state;
        while ((!(common_state_at_end(s)) && (common_state_peek(s) != terminator))) {
            s = common_state_advance(arena, s);
        }
        if (common_state_at_end(s)) {
            return ((slop_result_common_ParseWhileResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unexpected_eof, SLOP_STR("Unexpected end of input"), ((common_Position){.line = s.line, .column = s.column, .offset = s.offset})) });
        } else {
            return ((slop_result_common_ParseWhileResult_common_ParseError){ .is_ok = true, .data.ok = ((common_ParseWhileResult){.result = strlib_substring(arena, state.input, start, (s.offset - start)), .state = common_state_advance(arena, s)}) });
        }
    }
}

