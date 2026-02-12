#include "../runtime/slop_runtime.h"
#include "slop_ttl.h"

ttl_PrefixMap ttl_make_prefix_map(slop_arena* arena);
ttl_PrefixMap ttl_prefix_map_add(slop_arena* arena, ttl_PrefixMap pm, slop_string prefix, slop_string iri);
slop_option_string ttl_prefix_map_lookup(ttl_PrefixMap pm, slop_string prefix);
slop_option_int ttl_blank_label_lookup(slop_list_ttl_BlankLabelBinding labels, slop_string label);
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

static uint8_t _wrap_ttl_is_pn_chars(void* _env, uint8_t _p0) { return ttl_is_pn_chars(_p0); }

static uint8_t _wrap_ttl_is_pn_chars_base(void* _env, uint8_t _p0) { return ttl_is_pn_chars_base(_p0); }

static uint8_t _wrap_strlib_is_digit(void* _env, strlib_AsciiChar _p0) { return strlib_is_digit(_p0); }

ttl_PrefixMap ttl_make_prefix_map(slop_arena* arena) {
    ttl_PrefixMap _retval;
    _retval = ((ttl_PrefixMap){.bindings = ((slop_list_ttl_PrefixBinding){ .data = (ttl_PrefixBinding*)slop_arena_alloc(arena, 16 * sizeof(ttl_PrefixBinding)), .len = 0, .cap = 16 }), .count = 0});
    SLOP_POST(((_retval.count == 0)), "(== $result.count 0)");
    return _retval;
}

ttl_PrefixMap ttl_prefix_map_add(slop_arena* arena, ttl_PrefixMap pm, slop_string prefix, slop_string iri) {
    ttl_PrefixMap _retval;
    ({ __auto_type _lst_p = &(pm.bindings); __auto_type _item = (((ttl_PrefixBinding){.prefix = prefix, .iri = iri})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
    _retval = ((ttl_PrefixMap){.bindings = pm.bindings, .count = (pm.count + 1)});
    SLOP_POST(((_retval.count >= pm.count)), "(>= $result.count pm.count)");
    return _retval;
}

slop_option_string ttl_prefix_map_lookup(ttl_PrefixMap pm, slop_string prefix) {
    {
        slop_option_string result = (slop_option_string){.has_value = false};
        {
            __auto_type _coll = pm.bindings;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type b = _coll.data[_i];
                if (string_eq(b.prefix, prefix)) {
                    result = (slop_option_string){.has_value = 1, .value = b.iri};
                }
            }
        }
        return result;
    }
}

slop_option_int ttl_blank_label_lookup(slop_list_ttl_BlankLabelBinding labels, slop_string label) {
    {
        slop_option_int result = (slop_option_int){.has_value = false};
        {
            __auto_type _coll = labels;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type b = _coll.data[_i];
                if (string_eq(b.label, label)) {
                    result = (slop_option_int){.has_value = 1, .value = b.id};
                }
            }
        }
        return result;
    }
}

ttl_TtlParseContext ttl_make_ttl_context(slop_arena* arena, slop_string input) {
    ttl_TtlParseContext _retval;
    _retval = ((ttl_TtlParseContext){.prefixes = ttl_make_prefix_map(arena), .base_iri = (slop_option_string){.has_value = false}, .blank_labels = ((slop_list_ttl_BlankLabelBinding){ .data = (ttl_BlankLabelBinding*)slop_arena_alloc(arena, 16 * sizeof(ttl_BlankLabelBinding)), .len = 0, .cap = 16 }), .blank_counter = 0, .state = common_make_parse_state(arena, input)});
    SLOP_POST(((_retval.blank_counter == 0)), "(== $result.blank-counter 0)");
    return _retval;
}

ttl_GenBlankResult ttl_context_gen_blank_id(slop_arena* arena, ttl_TtlParseContext ctx) {
    ttl_GenBlankResult _retval;
    _retval = ((ttl_GenBlankResult){.id = ctx.blank_counter, .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = (ctx.blank_counter + 1), .state = ctx.state})});
    SLOP_POST(((_retval.id == ctx.blank_counter)), "(== $result.id ctx.blank-counter)");
    SLOP_POST(((_retval.ctx.blank_counter == (ctx.blank_counter + 1))), "(== $result.ctx.blank-counter (+ ctx.blank-counter 1))");
    return _retval;
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_iri_ref(slop_arena* arena, ttl_TtlParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.state) == 60)), "(== (state-peek ctx.state) 60)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.state);
        {
            __auto_type r = common_parse_until(arena, s1, 62);
            __auto_type _mv_269 = r;
            if (_mv_269.is_ok) {
                __auto_type res = _mv_269.data.ok;
                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_iri(arena, res.result), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = res.state})}) });
            } else if (!_mv_269.is_ok) {
                __auto_type e = _mv_269.data.err;
                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = e });
            }
        }
    }
}

common_ParseWhileResult ttl_parse_pn_local(slop_arena* arena, common_ParseState state) {
    {
        __auto_type result = common_parse_while(arena, state, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type c = common_state_peek(result.state);
                if ((c == 46)) {
                    {
                        __auto_type c2 = common_state_peek_n(result.state, 1);
                        if (ttl_is_pn_chars(c2)) {
                            {
                                __auto_type after_dot = common_state_advance(arena, result.state);
                                {
                                    __auto_type next_seg = common_parse_while(arena, after_dot, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
                                    result = ((common_ParseWhileResult){.result = string_concat(arena, string_concat(arena, result.result, SLOP_STR(".")), next_seg.result), .state = next_seg.state});
                                }
                            }
                        } else {
                            done = 1;
                        }
                    }
                } else {
                    done = 1;
                }
            }
        }
        return result;
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_prefixed_name(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type prefix_result = common_parse_while(arena, ctx.state, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
        {
            __auto_type s1 = common_expect_char(arena, prefix_result.state, 58);
            __auto_type _mv_270 = s1;
            if (_mv_270.is_ok) {
                __auto_type s2 = _mv_270.data.ok;
                {
                    __auto_type local_result = ttl_parse_pn_local(arena, s2);
                    {
                        __auto_type lookup = ttl_prefix_map_lookup(ctx.prefixes, prefix_result.result);
                        __auto_type _mv_271 = lookup;
                        if (_mv_271.has_value) {
                            __auto_type base_iri = _mv_271.value;
                            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_iri(arena, string_concat(arena, base_iri, local_result.result)), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = local_result.state})}) });
                        } else if (!_mv_271.has_value) {
                            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unknown_prefix, SLOP_STR("Unknown prefix"), ((common_Position){.line = prefix_result.state.line, .column = prefix_result.state.column, .offset = prefix_result.state.offset})) });
                        }
                    }
                }
            } else if (!_mv_270.is_ok) {
                __auto_type e = _mv_270.data.err;
                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = e });
            }
        }
    }
}

slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_blank_node_extended(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.state);
        if ((c == 91)) {
            {
                __auto_type s1 = common_state_advance(arena, ctx.state);
                {
                    __auto_type s2 = common_skip_whitespace(arena, s1);
                    if ((common_state_peek(s2) == 93)) {
                        {
                            __auto_type s3 = common_state_advance(arena, s2);
                            {
                                __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
                                return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, gen.id), .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = ((ttl_TtlParseContext){.prefixes = gen.ctx.prefixes, .base_iri = gen.ctx.base_iri, .blank_labels = gen.ctx.blank_labels, .blank_counter = gen.ctx.blank_counter, .state = s3})}) });
                            }
                        }
                    } else {
                        {
                            __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
                            {
                                __auto_type bnode = rdf_make_blank(arena, gen.id);
                                {
                                    __auto_type pol_result = ttl_parse_predicate_object_list(arena, ((ttl_TtlParseContext){.prefixes = gen.ctx.prefixes, .base_iri = gen.ctx.base_iri, .blank_labels = gen.ctx.blank_labels, .blank_counter = gen.ctx.blank_counter, .state = s2}), bnode);
                                    __auto_type _mv_272 = pol_result;
                                    if (_mv_272.is_ok) {
                                        __auto_type polr = _mv_272.data.ok;
                                        {
                                            __auto_type s3 = common_skip_whitespace(arena, polr.ctx.state);
                                            {
                                                __auto_type s4 = common_expect_char(arena, s3, 93);
                                                __auto_type _mv_273 = s4;
                                                if (_mv_273.is_ok) {
                                                    __auto_type s5 = _mv_273.data.ok;
                                                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = bnode, .extra_triples = polr.triples, .ctx = ((ttl_TtlParseContext){.prefixes = polr.ctx.prefixes, .base_iri = polr.ctx.base_iri, .blank_labels = polr.ctx.blank_labels, .blank_counter = polr.ctx.blank_counter, .state = s5})}) });
                                                } else if (!_mv_273.is_ok) {
                                                    __auto_type e = _mv_273.data.err;
                                                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                                                }
                                            }
                                        }
                                    } else if (!_mv_272.is_ok) {
                                        __auto_type e = _mv_272.data.err;
                                        return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            {
                __auto_type s1 = common_state_advance(arena, ctx.state);
                {
                    __auto_type s2 = common_expect_char(arena, s1, 58);
                    __auto_type _mv_274 = s2;
                    if (_mv_274.is_ok) {
                        __auto_type s3 = _mv_274.data.ok;
                        {
                            __auto_type label_result = common_parse_while(arena, s3, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
                            {
                                __auto_type label_str = label_result.result;
                                __auto_type existing = ttl_blank_label_lookup(ctx.blank_labels, label_result.result);
                                __auto_type _mv_275 = existing;
                                if (_mv_275.has_value) {
                                    __auto_type existing_id = _mv_275.value;
                                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, existing_id), .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = label_result.state})}) });
                                } else if (!_mv_275.has_value) {
                                    {
                                        __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
                                        ({ __auto_type _lst_p = &(ctx.blank_labels); __auto_type _item = (((ttl_BlankLabelBinding){.label = label_str, .id = gen.id})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                        return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, gen.id), .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = ((ttl_TtlParseContext){.prefixes = gen.ctx.prefixes, .base_iri = gen.ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = gen.ctx.blank_counter, .state = label_result.state})}) });
                                    }
                                }
                            }
                        }
                    } else if (!_mv_274.is_ok) {
                        __auto_type e = _mv_274.data.err;
                        return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                    }
                }
            }
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_blank_node(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type r = ttl_parse_blank_node_extended(arena, ctx);
        __auto_type _mv_276 = r;
        if (_mv_276.is_ok) {
            __auto_type ttr = _mv_276.data.ok;
            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = ttr.term, .ctx = ttr.ctx}) });
        } else if (!_mv_276.is_ok) {
            __auto_type e = _mv_276.data.err;
            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = e });
        }
    }
}

slop_result_ttl_StringResult_common_ParseError ttl_parse_string_literal(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type q = common_state_peek(ctx.state);
        __auto_type s = common_state_advance(arena, ctx.state);
        __auto_type result = SLOP_STR("");
        if (((common_state_peek(s) == q) && (common_state_peek_n(s, 1) == q))) {
            s = common_state_advance(arena, s);
            s = common_state_advance(arena, s);
            {
                uint8_t done = 0;
                while ((!(done) && !(common_state_at_end(s)))) {
                    {
                        __auto_type c = common_state_peek(s);
                        if ((c == 92)) {
                            {
                                __auto_type esc = ttl_parse_escape_sequence(arena, ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s}));
                                __auto_type _mv_277 = esc;
                                if (_mv_277.is_ok) {
                                    __auto_type er = _mv_277.data.ok;
                                    result = slop_string_push_char(arena, result, er.slop_char);
                                    s = er.ctx.state;
                                } else if (!_mv_277.is_ok) {
                                    __auto_type e = _mv_277.data.err;
                                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = e });
                                    /* empty list */;
                                }
                            }
                        } else if (((c == q) && ((common_state_peek_n(s, 1) == q) && (common_state_peek_n(s, 2) == q)))) {
                            s = common_state_advance(arena, s);
                            s = common_state_advance(arena, s);
                            s = common_state_advance(arena, s);
                            done = 1;
                        } else {
                            result = slop_string_push_char(arena, result, c);
                            s = common_state_advance(arena, s);
                        }
                    }
                }
                if (done) {
                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringResult){.value = result, .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s})}) });
                } else {
                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unterminated_string, SLOP_STR("Unterminated triple-quoted string"), ((common_Position){.line = s.line, .column = s.column, .offset = s.offset})) });
                }
            }
        } else {
            {
                uint8_t done = 0;
                while ((!(done) && !(common_state_at_end(s)))) {
                    {
                        __auto_type c = common_state_peek(s);
                        if ((c == 92)) {
                            {
                                __auto_type esc = ttl_parse_escape_sequence(arena, ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s}));
                                __auto_type _mv_278 = esc;
                                if (_mv_278.is_ok) {
                                    __auto_type er = _mv_278.data.ok;
                                    result = slop_string_push_char(arena, result, er.slop_char);
                                    s = er.ctx.state;
                                } else if (!_mv_278.is_ok) {
                                    __auto_type e = _mv_278.data.err;
                                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = e });
                                    /* empty list */;
                                }
                            }
                        } else if ((c == q)) {
                            s = common_state_advance(arena, s);
                            done = 1;
                        } else {
                            result = slop_string_push_char(arena, result, c);
                            s = common_state_advance(arena, s);
                        }
                    }
                }
                if (done) {
                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringResult){.value = result, .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s})}) });
                } else {
                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unterminated_string, SLOP_STR("Unterminated string"), ((common_Position){.line = s.line, .column = s.column, .offset = s.offset})) });
                }
            }
        }
    }
}

slop_result_ttl_EscapeResult_common_ParseError ttl_parse_escape_sequence(slop_arena* arena, ttl_TtlParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.state) == 92)), "(== (state-peek ctx.state) 92)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.state);
        {
            __auto_type c = common_state_peek(s1);
            {
                __auto_type s2 = common_state_advance(arena, s1);
                {
                    __auto_type new_ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s2});
                    if ((c == 110)) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 10, .ctx = new_ctx}) });
                    } else if ((c == 116)) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 9, .ctx = new_ctx}) });
                    } else if ((c == 114)) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 13, .ctx = new_ctx}) });
                    } else if ((c == 92)) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 92, .ctx = new_ctx}) });
                    } else if ((c == 34)) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 34, .ctx = new_ctx}) });
                    } else if ((c == 39)) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 39, .ctx = new_ctx}) });
                    } else {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_invalid_escape, SLOP_STR("Invalid escape sequence"), ((common_Position){.line = s1.line, .column = s1.column, .offset = s1.offset})) });
                    }
                }
            }
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_literal(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type str_result = ttl_parse_string_literal(arena, ctx);
        __auto_type _mv_279 = str_result;
        if (_mv_279.is_ok) {
            __auto_type sr = _mv_279.data.ok;
            {
                __auto_type s = sr.ctx.state;
                __auto_type val = sr.value;
                if (((common_state_peek(s) == 94) && (common_state_peek_n(s, 1) == 94))) {
                    {
                        __auto_type s2 = common_state_advance(arena, common_state_advance(arena, s));
                        {
                            __auto_type dt_ctx = ((ttl_TtlParseContext){.prefixes = sr.ctx.prefixes, .base_iri = sr.ctx.base_iri, .blank_labels = sr.ctx.blank_labels, .blank_counter = sr.ctx.blank_counter, .state = s2});
                            if ((common_state_peek(s2) == 60)) {
                                {
                                    __auto_type iri_result = ttl_parse_iri_ref(arena, dt_ctx);
                                    __auto_type _mv_280 = iri_result;
                                    if (_mv_280.is_ok) {
                                        __auto_type ir = _mv_280.data.ok;
                                        __auto_type _mv_281 = ir.term;
                                        switch (_mv_281.tag) {
                                            case rdf_Term_term_iri:
                                            {
                                                __auto_type iri_val = _mv_281.data.term_iri;
                                                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, (slop_option_string){.has_value = 1, .value = iri_val.value}, ((slop_option_string){.has_value = false})), .ctx = ir.ctx}) });
                                            }
                                            default: {
                                                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_syntax_error, SLOP_STR("Expected IRI for datatype"), ((common_Position){.line = s2.line, .column = s2.column, .offset = s2.offset})) });
                                            }
                                        }
                                    } else if (!_mv_280.is_ok) {
                                        __auto_type e = _mv_280.data.err;
                                        return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = e });
                                    }
                                }
                            } else {
                                {
                                    __auto_type pn_result = ttl_parse_prefixed_name(arena, dt_ctx);
                                    __auto_type _mv_282 = pn_result;
                                    if (_mv_282.is_ok) {
                                        __auto_type pr = _mv_282.data.ok;
                                        __auto_type _mv_283 = pr.term;
                                        switch (_mv_283.tag) {
                                            case rdf_Term_term_iri:
                                            {
                                                __auto_type iri_val = _mv_283.data.term_iri;
                                                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, (slop_option_string){.has_value = 1, .value = iri_val.value}, ((slop_option_string){.has_value = false})), .ctx = pr.ctx}) });
                                            }
                                            default: {
                                                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_syntax_error, SLOP_STR("Expected IRI for datatype"), ((common_Position){.line = s2.line, .column = s2.column, .offset = s2.offset})) });
                                            }
                                        }
                                    } else if (!_mv_282.is_ok) {
                                        __auto_type e = _mv_282.data.err;
                                        return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = e });
                                    }
                                }
                            }
                        }
                    }
                } else if ((common_state_peek(s) == 64)) {
                    {
                        __auto_type s2 = common_state_advance(arena, s);
                        {
                            __auto_type lang_result = common_parse_while(arena, s2, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars_base, NULL});
                            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, ((slop_option_string){.has_value = false}), (slop_option_string){.has_value = 1, .value = lang_result.result}), .ctx = ((ttl_TtlParseContext){.prefixes = sr.ctx.prefixes, .base_iri = sr.ctx.base_iri, .blank_labels = sr.ctx.blank_labels, .blank_counter = sr.ctx.blank_counter, .state = lang_result.state})}) });
                        }
                    }
                } else {
                    return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, ((slop_option_string){.has_value = false}), ((slop_option_string){.has_value = false})), .ctx = sr.ctx}) });
                }
            }
        } else if (!_mv_279.is_ok) {
            __auto_type e = _mv_279.data.err;
            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = e });
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_numeric_literal(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type start = ctx.state.offset;
        __auto_type s = ctx.state;
        uint8_t has_dot = 0;
        uint8_t has_e = 0;
        if (((common_state_peek(s) == 43) || (common_state_peek(s) == 45))) {
            s = common_state_advance(arena, s);
        }
        {
            __auto_type digits = common_parse_while(arena, s, (slop_closure_t){(void*)_wrap_strlib_is_digit, NULL});
            s = digits.state;
        }
        if ((common_state_peek(s) == 46)) {
            has_dot = 1;
            s = common_state_advance(arena, s);
            {
                __auto_type frac = common_parse_while(arena, s, (slop_closure_t){(void*)_wrap_strlib_is_digit, NULL});
                s = frac.state;
            }
        }
        if (((common_state_peek(s) == 101) || (common_state_peek(s) == 69))) {
            has_e = 1;
            s = common_state_advance(arena, s);
            if (((common_state_peek(s) == 43) || (common_state_peek(s) == 45))) {
                s = common_state_advance(arena, s);
            }
            {
                __auto_type exp_digits = common_parse_while(arena, s, (slop_closure_t){(void*)_wrap_strlib_is_digit, NULL});
                s = exp_digits.state;
            }
        }
        {
            __auto_type val = strlib_substring(arena, ctx.state.input, start, (s.offset - start));
            __auto_type dt = (has_e ? SLOP_STR("http://www.w3.org/2001/XMLSchema#double") : (has_dot ? SLOP_STR("http://www.w3.org/2001/XMLSchema#decimal") : SLOP_STR("http://www.w3.org/2001/XMLSchema#integer")));
            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, (slop_option_string){.has_value = 1, .value = dt}, ((slop_option_string){.has_value = false})), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s})}) });
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_boolean_literal(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.state);
        if ((c == 116)) {
            {
                __auto_type s = common_state_advance(arena, common_state_advance(arena, common_state_advance(arena, common_state_advance(arena, ctx.state))));
                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, SLOP_STR("true"), (slop_option_string){.has_value = 1, .value = SLOP_STR("http://www.w3.org/2001/XMLSchema#boolean")}, ((slop_option_string){.has_value = false})), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s})}) });
            }
        } else {
            {
                __auto_type s = common_state_advance(arena, common_state_advance(arena, common_state_advance(arena, common_state_advance(arena, common_state_advance(arena, ctx.state)))));
                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, SLOP_STR("false"), (slop_option_string){.has_value = 1, .value = SLOP_STR("http://www.w3.org/2001/XMLSchema#boolean")}, ((slop_option_string){.has_value = false})), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s})}) });
            }
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_term(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.state);
        if ((c == 60)) {
            return ttl_parse_iri_ref(arena, ctx);
        } else if ((c == 95)) {
            return ttl_parse_blank_node(arena, ctx);
        } else if (((c == 34) || (c == 39))) {
            return ttl_parse_literal(arena, ctx);
        } else if ((((c >= 48) && (c <= 57)) || ((c == 43) || (c == 45)))) {
            return ttl_parse_numeric_literal(arena, ctx);
        } else if ((c == 116)) {
            {
                __auto_type c2 = common_state_peek_n(ctx.state, 1);
                __auto_type c3 = common_state_peek_n(ctx.state, 2);
                __auto_type c4 = common_state_peek_n(ctx.state, 3);
                __auto_type c5 = common_state_peek_n(ctx.state, 4);
                if (((c2 == 114) && ((c3 == 117) && ((c4 == 101) && !((strlib_is_alnum(c5) || ((c5 == 58) || ((c5 == 95) || (c5 == 45))))))))) {
                    return ttl_parse_boolean_literal(arena, ctx);
                } else {
                    return ttl_parse_prefixed_name(arena, ctx);
                }
            }
        } else if ((c == 102)) {
            {
                __auto_type c2 = common_state_peek_n(ctx.state, 1);
                __auto_type c3 = common_state_peek_n(ctx.state, 2);
                __auto_type c4 = common_state_peek_n(ctx.state, 3);
                __auto_type c5 = common_state_peek_n(ctx.state, 4);
                __auto_type c6 = common_state_peek_n(ctx.state, 5);
                if (((c2 == 97) && ((c3 == 108) && ((c4 == 115) && ((c5 == 101) && !((strlib_is_alnum(c6) || ((c6 == 58) || ((c6 == 95) || (c6 == 45)))))))))) {
                    return ttl_parse_boolean_literal(arena, ctx);
                } else {
                    return ttl_parse_prefixed_name(arena, ctx);
                }
            }
        } else if ((c == 97)) {
            {
                __auto_type c2 = common_state_peek_n(ctx.state, 1);
                if (((c2 == 32) || ((c2 == 9) || ((c2 == 10) || (c2 == 13))))) {
                    return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#type")), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = common_state_advance(arena, ctx.state)})}) });
                } else {
                    return ttl_parse_prefixed_name(arena, ctx);
                }
            }
        } else {
            return ttl_parse_prefixed_name(arena, ctx);
        }
    }
}

slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_collection(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type s1 = common_skip_whitespace(arena, common_state_advance(arena, ctx.state));
        __auto_type triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type cur_ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s1});
        __auto_type rdf_first = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#first"));
        __auto_type rdf_rest = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#rest"));
        __auto_type rdf_nil = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#nil"));
        slop_option_rdf_Term prev_node = (slop_option_rdf_Term){.has_value = false};
        slop_option_rdf_Term first_node = (slop_option_rdf_Term){.has_value = false};
        while ((!(common_state_at_end(cur_ctx.state)) && (common_state_peek(cur_ctx.state) != 41))) {
            {
                __auto_type elem_result = ttl_parse_term_extended(arena, cur_ctx);
                __auto_type _mv_284 = elem_result;
                if (_mv_284.is_ok) {
                    __auto_type er = _mv_284.data.ok;
                    {
                        __auto_type _coll = er.extra_triples;
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            ({ __auto_type _lst_p = &(triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                    {
                        __auto_type gen = ttl_context_gen_blank_id(arena, er.ctx);
                        {
                            __auto_type cell_node = rdf_make_blank(arena, gen.id);
                            ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, cell_node, rdf_first, er.term)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            __auto_type _mv_285 = prev_node;
                            if (_mv_285.has_value) {
                                __auto_type pn = _mv_285.value;
                                ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, pn, rdf_rest, cell_node)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            } else if (!_mv_285.has_value) {
                                /* empty list */;
                            }
                            __auto_type _mv_286 = first_node;
                            if (_mv_286.has_value) {
                                __auto_type _ = _mv_286.value;
                                /* empty list */;
                            } else if (!_mv_286.has_value) {
                                first_node = (slop_option_rdf_Term){.has_value = 1, .value = cell_node};
                            }
                            prev_node = (slop_option_rdf_Term){.has_value = 1, .value = cell_node};
                            cur_ctx = ((ttl_TtlParseContext){.prefixes = gen.ctx.prefixes, .base_iri = gen.ctx.base_iri, .blank_labels = gen.ctx.blank_labels, .blank_counter = gen.ctx.blank_counter, .state = common_skip_whitespace(arena, gen.ctx.state)});
                        }
                    }
                } else if (!_mv_284.is_ok) {
                    __auto_type e = _mv_284.data.err;
                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                    /* empty list */;
                }
            }
        }
        __auto_type _mv_287 = prev_node;
        if (_mv_287.has_value) {
            __auto_type pn = _mv_287.value;
            ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, pn, rdf_rest, rdf_nil)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        } else if (!_mv_287.has_value) {
            /* empty list */;
        }
        {
            __auto_type s_end = common_expect_char(arena, cur_ctx.state, 41);
            __auto_type _mv_288 = s_end;
            if (_mv_288.is_ok) {
                __auto_type s_after = _mv_288.data.ok;
                return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = ({ __auto_type _mv = first_node; _mv.has_value ? ({ __auto_type fnode = _mv.value; fnode; }) : (rdf_nil); }), .extra_triples = triples, .ctx = ((ttl_TtlParseContext){.prefixes = cur_ctx.prefixes, .base_iri = cur_ctx.base_iri, .blank_labels = cur_ctx.blank_labels, .blank_counter = cur_ctx.blank_counter, .state = s_after})}) });
            } else if (!_mv_288.is_ok) {
                __auto_type e = _mv_288.data.err;
                return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
            }
        }
    }
}

slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_term_extended(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.state);
        if ((c == 91)) {
            return ttl_parse_blank_node_extended(arena, ctx);
        } else if ((c == 40)) {
            return ttl_parse_collection(arena, ctx);
        } else {
            {
                __auto_type r = ttl_parse_term(arena, ctx);
                __auto_type _mv_289 = r;
                if (_mv_289.is_ok) {
                    __auto_type tr = _mv_289.data.ok;
                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = tr.term, .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = tr.ctx}) });
                } else if (!_mv_289.is_ok) {
                    __auto_type e = _mv_289.data.err;
                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                }
            }
        }
    }
}

slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_directive(slop_arena* arena, ttl_TtlParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.state) == 64)), "(== (state-peek ctx.state) 64)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.state);
        {
            __auto_type kw = common_parse_while(arena, s1, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars_base, NULL});
            {
                __auto_type keyword = kw.result;
                __auto_type s2 = common_skip_whitespace(arena, kw.state);
                if (strlib_starts_with(keyword, SLOP_STR("prefix"))) {
                    {
                        __auto_type prefix_name = common_parse_while(arena, s2, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
                        {
                            __auto_type s3 = common_expect_char(arena, prefix_name.state, 58);
                            __auto_type _mv_290 = s3;
                            if (_mv_290.is_ok) {
                                __auto_type s4 = _mv_290.data.ok;
                                {
                                    __auto_type s5 = common_skip_whitespace(arena, s4);
                                    {
                                        __auto_type iri_result = ttl_parse_iri_ref(arena, ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s5}));
                                        __auto_type _mv_291 = iri_result;
                                        if (_mv_291.is_ok) {
                                            __auto_type ir = _mv_291.data.ok;
                                            {
                                                __auto_type s6 = common_skip_whitespace(arena, ir.ctx.state);
                                                {
                                                    __auto_type s7 = common_expect_char(arena, s6, 46);
                                                    __auto_type _mv_292 = s7;
                                                    if (_mv_292.is_ok) {
                                                        __auto_type s8 = _mv_292.data.ok;
                                                        return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TtlParseContext){.prefixes = ttl_prefix_map_add(arena, ctx.prefixes, prefix_name.result, ({ __auto_type _mv = ir.term; slop_string _mr = {0}; switch (_mv.tag) { case rdf_Term_term_iri: { __auto_type iri = _mv.data.term_iri; _mr = iri.value; break; } default: { _mr = SLOP_STR(""); break; }  } _mr; })), .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s8}) });
                                                    } else if (!_mv_292.is_ok) {
                                                        __auto_type e = _mv_292.data.err;
                                                        return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = e });
                                                    }
                                                }
                                            }
                                        } else if (!_mv_291.is_ok) {
                                            __auto_type e = _mv_291.data.err;
                                            return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = e });
                                        }
                                    }
                                }
                            } else if (!_mv_290.is_ok) {
                                __auto_type e = _mv_290.data.err;
                                return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = e });
                            }
                        }
                    }
                } else {
                    {
                        __auto_type iri_result = ttl_parse_iri_ref(arena, ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s2}));
                        __auto_type _mv_293 = iri_result;
                        if (_mv_293.is_ok) {
                            __auto_type ir = _mv_293.data.ok;
                            {
                                __auto_type s3 = common_skip_whitespace(arena, ir.ctx.state);
                                {
                                    __auto_type s4 = common_expect_char(arena, s3, 46);
                                    __auto_type _mv_294 = s4;
                                    if (_mv_294.is_ok) {
                                        __auto_type s5 = _mv_294.data.ok;
                                        return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ({ __auto_type _mv = ir.term; slop_option_string _mr = {0}; switch (_mv.tag) { case rdf_Term_term_iri: { __auto_type iri = _mv.data.term_iri; _mr = (slop_option_string){.has_value = 1, .value = iri.value}; break; } default: { _mr = ctx.base_iri; break; }  } _mr; }), .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s5}) });
                                    } else if (!_mv_294.is_ok) {
                                        __auto_type e = _mv_294.data.err;
                                        return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = e });
                                    }
                                }
                            }
                        } else if (!_mv_293.is_ok) {
                            __auto_type e = _mv_293.data.err;
                            return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = e });
                        }
                    }
                }
            }
        }
    }
}

slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_sparql_prefix(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type kw = common_parse_while(arena, ctx.state, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars_base, NULL});
        {
            __auto_type s1 = common_skip_whitespace(arena, kw.state);
            {
                __auto_type prefix_name = common_parse_while(arena, s1, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
                {
                    __auto_type s2 = common_expect_char(arena, prefix_name.state, 58);
                    __auto_type _mv_295 = s2;
                    if (_mv_295.is_ok) {
                        __auto_type s3 = _mv_295.data.ok;
                        {
                            __auto_type s4 = common_skip_whitespace(arena, s3);
                            {
                                __auto_type iri_result = ttl_parse_iri_ref(arena, ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s4}));
                                __auto_type _mv_296 = iri_result;
                                if (_mv_296.is_ok) {
                                    __auto_type ir = _mv_296.data.ok;
                                    return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TtlParseContext){.prefixes = ttl_prefix_map_add(arena, ctx.prefixes, prefix_name.result, ({ __auto_type _mv = ir.term; slop_string _mr = {0}; switch (_mv.tag) { case rdf_Term_term_iri: { __auto_type iri = _mv.data.term_iri; _mr = iri.value; break; } default: { _mr = SLOP_STR(""); break; }  } _mr; })), .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = ir.ctx.state}) });
                                } else if (!_mv_296.is_ok) {
                                    __auto_type e = _mv_296.data.err;
                                    return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = e });
                                }
                            }
                        }
                    } else if (!_mv_295.is_ok) {
                        __auto_type e = _mv_295.data.err;
                        return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = e });
                    }
                }
            }
        }
    }
}

slop_result_ttl_TripleResult_common_ParseError ttl_parse_triple(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type sub_result = ttl_parse_term(arena, ctx);
        __auto_type _mv_297 = sub_result;
        if (_mv_297.is_ok) {
            __auto_type sr = _mv_297.data.ok;
            {
                __auto_type s1 = common_skip_whitespace(arena, sr.ctx.state);
                {
                    __auto_type pred_result = ttl_parse_term(arena, ((ttl_TtlParseContext){.prefixes = sr.ctx.prefixes, .base_iri = sr.ctx.base_iri, .blank_labels = sr.ctx.blank_labels, .blank_counter = sr.ctx.blank_counter, .state = s1}));
                    __auto_type _mv_298 = pred_result;
                    if (_mv_298.is_ok) {
                        __auto_type pr = _mv_298.data.ok;
                        {
                            __auto_type s2 = common_skip_whitespace(arena, pr.ctx.state);
                            {
                                __auto_type obj_result = ttl_parse_term(arena, ((ttl_TtlParseContext){.prefixes = pr.ctx.prefixes, .base_iri = pr.ctx.base_iri, .blank_labels = pr.ctx.blank_labels, .blank_counter = pr.ctx.blank_counter, .state = s2}));
                                __auto_type _mv_299 = obj_result;
                                if (_mv_299.is_ok) {
                                    __auto_type objr = _mv_299.data.ok;
                                    {
                                        __auto_type s3 = common_skip_whitespace(arena, objr.ctx.state);
                                        {
                                            __auto_type s4 = common_expect_char(arena, s3, 46);
                                            __auto_type _mv_300 = s4;
                                            if (_mv_300.is_ok) {
                                                __auto_type s5 = _mv_300.data.ok;
                                                return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TripleResult){.triple = rdf_make_triple(arena, sr.term, pr.term, objr.term), .ctx = ((ttl_TtlParseContext){.prefixes = objr.ctx.prefixes, .base_iri = objr.ctx.base_iri, .blank_labels = objr.ctx.blank_labels, .blank_counter = objr.ctx.blank_counter, .state = s5})}) });
                                            } else if (!_mv_300.is_ok) {
                                                __auto_type e = _mv_300.data.err;
                                                return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                                            }
                                        }
                                    }
                                } else if (!_mv_299.is_ok) {
                                    __auto_type e = _mv_299.data.err;
                                    return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                                }
                            }
                        }
                    } else if (!_mv_298.is_ok) {
                        __auto_type e = _mv_298.data.err;
                        return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                    }
                }
            }
        } else if (!_mv_297.is_ok) {
            __auto_type e = _mv_297.data.err;
            return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
        }
    }
}

slop_result_ttl_TriplesResult_common_ParseError ttl_parse_predicate_object_list(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject) {
    {
        __auto_type triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type cur_ctx = ctx;
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type s1 = common_skip_whitespace(arena, cur_ctx.state);
                {
                    __auto_type c1 = common_state_peek(s1);
                    if (((c1 == 46) || ((c1 == 93) || (c1 == 0)))) {
                        cur_ctx = ((ttl_TtlParseContext){.prefixes = cur_ctx.prefixes, .base_iri = cur_ctx.base_iri, .blank_labels = cur_ctx.blank_labels, .blank_counter = cur_ctx.blank_counter, .state = s1});
                        done = 1;
                    } else {
                        {
                            __auto_type pred_result = ttl_parse_term(arena, ((ttl_TtlParseContext){.prefixes = cur_ctx.prefixes, .base_iri = cur_ctx.base_iri, .blank_labels = cur_ctx.blank_labels, .blank_counter = cur_ctx.blank_counter, .state = s1}));
                            __auto_type _mv_301 = pred_result;
                            if (_mv_301.is_ok) {
                                __auto_type pr = _mv_301.data.ok;
                                {
                                    __auto_type obj_list_result = ttl_parse_object_list(arena, pr.ctx, subject, pr.term);
                                    __auto_type _mv_302 = obj_list_result;
                                    if (_mv_302.is_ok) {
                                        __auto_type olr = _mv_302.data.ok;
                                        {
                                            __auto_type _coll = olr.triples;
                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                __auto_type t = _coll.data[_i];
                                                ({ __auto_type _lst_p = &(triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                        cur_ctx = olr.ctx;
                                        {
                                            __auto_type s3 = common_skip_whitespace(arena, olr.ctx.state);
                                            if ((common_state_peek(s3) == 59)) {
                                                cur_ctx = ((ttl_TtlParseContext){.prefixes = cur_ctx.prefixes, .base_iri = cur_ctx.base_iri, .blank_labels = cur_ctx.blank_labels, .blank_counter = cur_ctx.blank_counter, .state = common_state_advance(arena, s3)});
                                            } else {
                                                done = 1;
                                            }
                                        }
                                    } else if (!_mv_302.is_ok) {
                                        __auto_type e = _mv_302.data.err;
                                        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                                        /* empty list */;
                                    }
                                }
                            } else if (!_mv_301.is_ok) {
                                __auto_type e = _mv_301.data.err;
                                return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                                /* empty list */;
                            }
                        }
                    }
                }
            }
        }
        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TriplesResult){.triples = triples, .ctx = cur_ctx}) });
    }
}

slop_result_ttl_TriplesResult_common_ParseError ttl_parse_object_list(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, rdf_Term predicate) {
    {
        __auto_type triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type cur_ctx = ctx;
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type s1 = common_skip_whitespace(arena, cur_ctx.state);
                {
                    __auto_type obj_result = ttl_parse_term_extended(arena, ((ttl_TtlParseContext){.prefixes = cur_ctx.prefixes, .base_iri = cur_ctx.base_iri, .blank_labels = cur_ctx.blank_labels, .blank_counter = cur_ctx.blank_counter, .state = s1}));
                    __auto_type _mv_303 = obj_result;
                    if (_mv_303.is_ok) {
                        __auto_type objr = _mv_303.data.ok;
                        {
                            __auto_type _coll = objr.extra_triples;
                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                __auto_type t = _coll.data[_i];
                                ({ __auto_type _lst_p = &(triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        }
                        ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, subject, predicate, objr.term)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        cur_ctx = objr.ctx;
                        {
                            __auto_type s2 = common_skip_whitespace(arena, objr.ctx.state);
                            if ((common_state_peek(s2) == 44)) {
                                cur_ctx = ((ttl_TtlParseContext){.prefixes = cur_ctx.prefixes, .base_iri = cur_ctx.base_iri, .blank_labels = cur_ctx.blank_labels, .blank_counter = cur_ctx.blank_counter, .state = common_state_advance(arena, s2)});
                            } else {
                                done = 1;
                            }
                        }
                    } else if (!_mv_303.is_ok) {
                        __auto_type e = _mv_303.data.err;
                        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = e });
                        /* empty list */;
                    }
                }
            }
        }
        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TriplesResult){.triples = triples, .ctx = cur_ctx}) });
    }
}

slop_result_rdf_Graph_common_ParseError ttl_parse_ttl_string(slop_arena* arena, slop_string input) {
    SLOP_PRE(((string_len(input) > 0)), "(> (string-len input) 0)");
    {
        __auto_type ctx = ttl_make_ttl_context(arena, input);
        __auto_type g = rdf_make_graph(arena);
        {
            __auto_type s = common_skip_whitespace(arena, ctx.state);
            ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s});
            while (!(common_state_at_end(ctx.state))) {
                {
                    __auto_type c = common_state_peek(ctx.state);
                    if ((c == 64)) {
                        {
                            __auto_type dir_result = ttl_parse_directive(arena, ctx);
                            __auto_type _mv_304 = dir_result;
                            if (_mv_304.is_ok) {
                                __auto_type new_ctx = _mv_304.data.ok;
                                ctx = new_ctx;
                            } else if (!_mv_304.is_ok) {
                                __auto_type e = _mv_304.data.err;
                                return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                /* empty list */;
                            }
                        }
                    } else if (((c == 80) || (c == 66))) {
                        {
                            __auto_type dir_result = ttl_parse_sparql_prefix(arena, ctx);
                            __auto_type _mv_305 = dir_result;
                            if (_mv_305.is_ok) {
                                __auto_type new_ctx = _mv_305.data.ok;
                                ctx = new_ctx;
                            } else if (!_mv_305.is_ok) {
                                __auto_type e = _mv_305.data.err;
                                return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                /* empty list */;
                            }
                        }
                    } else {
                        {
                            __auto_type sub_result = ttl_parse_term_extended(arena, ctx);
                            __auto_type _mv_306 = sub_result;
                            if (_mv_306.is_ok) {
                                __auto_type sr = _mv_306.data.ok;
                                {
                                    __auto_type _coll = sr.extra_triples;
                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                        __auto_type t = _coll.data[_i];
                                        g = rdf_graph_add_unchecked(arena, g, t);
                                    }
                                }
                                {
                                    __auto_type pol_result = ttl_parse_predicate_object_list(arena, sr.ctx, sr.term);
                                    __auto_type _mv_307 = pol_result;
                                    if (_mv_307.is_ok) {
                                        __auto_type polr = _mv_307.data.ok;
                                        {
                                            __auto_type _coll = polr.triples;
                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                __auto_type t = _coll.data[_i];
                                                g = rdf_graph_add_unchecked(arena, g, t);
                                            }
                                        }
                                        {
                                            __auto_type s3 = common_skip_whitespace(arena, polr.ctx.state);
                                            {
                                                __auto_type s4 = common_expect_char(arena, s3, 46);
                                                __auto_type _mv_308 = s4;
                                                if (_mv_308.is_ok) {
                                                    __auto_type s5 = _mv_308.data.ok;
                                                    ctx = ((ttl_TtlParseContext){.prefixes = polr.ctx.prefixes, .base_iri = polr.ctx.base_iri, .blank_labels = polr.ctx.blank_labels, .blank_counter = polr.ctx.blank_counter, .state = s5});
                                                } else if (!_mv_308.is_ok) {
                                                    __auto_type e = _mv_308.data.err;
                                                    return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                                    /* empty list */;
                                                }
                                            }
                                        }
                                    } else if (!_mv_307.is_ok) {
                                        __auto_type e = _mv_307.data.err;
                                        return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                        /* empty list */;
                                    }
                                }
                            } else if (!_mv_306.is_ok) {
                                __auto_type e = _mv_306.data.err;
                                return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                /* empty list */;
                            }
                        }
                    }
                }
                {
                    __auto_type s2 = common_skip_whitespace(arena, ctx.state);
                    ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s2});
                }
            }
        }
        return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = true, .data.ok = g });
    }
}

slop_result_rdf_Graph_ttl_TtlFileError ttl_parse_ttl_file(slop_arena* arena, slop_string path) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type f = file_file_open(path, file_FileMode_read);
        __auto_type _mv_309 = f;
        if (_mv_309.is_ok) {
            __auto_type handle = _mv_309.data.ok;
            {
                __auto_type content = file_file_read_all(arena, (&handle));
                __auto_type _mv_310 = content;
                if (_mv_310.is_ok) {
                    __auto_type text = _mv_310.data.ok;
                    file_file_close((&handle));
                    __auto_type _mv_311 = ttl_parse_ttl_string(arena, text);
                    if (_mv_311.is_ok) {
                        __auto_type g = _mv_311.data.ok;
                        return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = true, .data.ok = g });
                    } else if (!_mv_311.is_ok) {
                        __auto_type e = _mv_311.data.err;
                        return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_parse_error, .data.parse_error = e }) });
                    }
                } else if (!_mv_310.is_ok) {
                    __auto_type e = _mv_310.data.err;
                    file_file_close((&handle));
                    return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
                }
            }
        } else if (!_mv_309.is_ok) {
            __auto_type e = _mv_309.data.err;
            return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
        }
    }
}

uint8_t ttl_is_pn_chars_base(uint8_t c) {
    return strlib_is_alpha(c);
}

uint8_t ttl_is_pn_chars(uint8_t c) {
    return (ttl_is_pn_chars_base(c) || (strlib_is_digit(c) || ((c == 95) || (c == 45))));
}

