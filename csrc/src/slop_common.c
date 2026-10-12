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
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval.offset == 0)), "(== $result.offset 0)");
    SLOP_POST(((_retval.line == 1)), "(== $result.line 1)");
    SLOP_POST(((_retval.column == 1)), "(== $result.column 1)");
    return _retval;
}

uint8_t common_state_at_end(common_ParseState state) {
    uint8_t _retval = {0};
    _retval = (state.offset >= string_len(state.input));
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval == (state.offset >= string_len(state.input)))), "(== $result (>= (. state offset) (string-len (. state input))))");
    return _retval;
}

uint8_t common_state_peek(common_ParseState state) {
    uint8_t _retval = {0};
    if (common_state_at_end(state)) {
        _retval = 0;
        goto _slop_post;
    } else {
        _retval = strlib_char_at(state.input, state.offset);
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST(((common_state_at_end(state) || (_retval == strlib_char_at(state.input, state.offset)))), "(or (state-at-end state) (== $result (char-at (. state input) (. state offset))))");
    SLOP_POST(((!(common_state_at_end(state)) || (_retval == 0))), "(or (not (state-at-end state)) (== $result 0))");
    return _retval;
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
            goto _slop_post;
        } else {
            _retval = ((common_ParseState){.input = state.input, .offset = (state.offset + 1), .line = state.line, .column = (state.column + 1)});
            goto _slop_post;
        }
    }
    _slop_post: ;
    SLOP_POST(((_retval.offset == (state.offset + 1))), "(== $result.offset (+ state.offset 1))");
    return _retval;
}

common_ParseState common_state_with_position(common_ParseState state, int64_t offset, int64_t line, int64_t column) {
    common_ParseState _retval = {0};
    _retval = ((common_ParseState){.input = state.input, .offset = offset, .line = line, .column = column});
    goto _slop_post;
    _slop_post: ;
    SLOP_POST((slop_string_eq(_retval.input, state.input)), "(== $result.input state.input)");
    SLOP_POST(((_retval.offset == offset)), "(== $result.offset offset)");
    SLOP_POST(((_retval.line == line)), "(== $result.line line)");
    SLOP_POST(((_retval.column == column)), "(== $result.column column)");
    return _retval;
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
                __auto_type c = strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:174:33"));
                if (c == 35) {
                    while ((offset < len) && (strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:178:63")) != 10)) {
                        offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:180:34");
                        column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:181:34");
                    }
                    if (offset < len) {
                        offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:184:34");
                        line = SLOP_RANGE(int64_t, (line + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:185:32");
                        column = 1;
                    }
                } else if (strlib_is_space(c)) {
                    offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:189:30");
                    if (c == 10) {
                        line = SLOP_RANGE(int64_t, (line + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:192:32");
                        column = 1;
                    } else {
                        column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:194:32");
                    }
                } else {
                    done = 1;
                }
            }
        }
        _retval = common_state_with_position(state, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:196:34"), SLOP_RANGE(int64_t, line, 1, 0, 1, 0, "(Int 1 ..) at common.slop:196:41"), SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at common.slop:196:46"));
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST(((common_state_at_end(_retval) || !(strlib_is_space(common_state_peek(_retval))))), "(or (state-at-end $result) (not (is-space (state-peek $result))))");
    return _retval;
}

common_ParseState common_skip_line(slop_arena* arena, common_ParseState state) {
    {
        __auto_type input = state.input;
        __auto_type len = string_len(state.input);
        int64_t offset = state.offset;
        int64_t column = state.column;
        while ((offset < len) && (strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:206:53")) != 10)) {
            offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:208:24");
            column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:209:24");
        }
        if (offset < len) {
            return common_state_with_position(state, SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:211:36"), (state.line + 1), 1);
        } else {
            return common_state_with_position(state, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:212:36"), state.line, SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at common.slop:212:58"));
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
        while ((offset < len) && ((uint8_t(*)(void*, uint8_t))predicate.fn)(predicate.env, strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:245:60")))) {
            {
                __auto_type c = strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:246:33"));
                offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:248:26");
                if (c == 10) {
                    line = SLOP_RANGE(int64_t, (line + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:251:28");
                    column = 1;
                } else {
                    column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:253:28");
                }
            }
        }
        return ((common_ParseWhileResult){.result = strlib_substring(arena, input, SLOP_RANGE(int64_t, start, 1, 0, 0, 0, "(Int 0 ..) at common.slop:255:40"), SLOP_RANGE(int64_t, (offset - start), 1, 0, 0, 0, "(Int 0 ..) at common.slop:255:46")), .state = common_state_with_position(state, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:256:43"), SLOP_RANGE(int64_t, line, 1, 0, 1, 0, "(Int 1 ..) at common.slop:256:50"), SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at common.slop:256:55"))});
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
        while ((offset < len) && (strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:268:53")) != terminator)) {
            {
                __auto_type c = strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:269:33"));
                offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:271:26");
                if (c == 10) {
                    line = SLOP_RANGE(int64_t, (line + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:274:28");
                    column = 1;
                } else {
                    column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:276:28");
                }
            }
        }
        if (offset >= len) {
            return ((slop_result_common_ParseWhileResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unexpected_eof, SLOP_STR("Unexpected end of input"), ((common_Position){.line = SLOP_RANGE(int64_t, line, 1, 0, 1, 0, "(Int 1 ..) at common.slop:279:38"), .column = SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at common.slop:279:52"), .offset = SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:279:68")})) });
        } else {
            {
                __auto_type end = offset;
                __auto_type c = strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:281:33"));
                offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at common.slop:283:26");
                if (c == 10) {
                    line = SLOP_RANGE(int64_t, (line + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:286:28");
                    column = 1;
                } else {
                    column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at common.slop:288:28");
                }
                return ((slop_result_common_ParseWhileResult_common_ParseError){ .is_ok = true, .data.ok = ((common_ParseWhileResult){.result = strlib_substring(arena, input, SLOP_RANGE(int64_t, start, 1, 0, 0, 0, "(Int 0 ..) at common.slop:290:46"), SLOP_RANGE(int64_t, (end - start), 1, 0, 0, 0, "(Int 0 ..) at common.slop:290:52")), .state = common_state_with_position(state, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at common.slop:291:49"), SLOP_RANGE(int64_t, line, 1, 0, 1, 0, "(Int 1 ..) at common.slop:291:56"), SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at common.slop:291:61"))}) });
            }
        }
    }
}

