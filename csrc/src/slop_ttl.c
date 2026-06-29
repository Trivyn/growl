#include "../runtime/slop_runtime.h"
#include "slop_ttl.h"

ttl_PrefixMap ttl_make_prefix_map(slop_arena* arena);
ttl_PrefixMap ttl_prefix_map_add(slop_arena* arena, ttl_PrefixMap pm, slop_string prefix, slop_string iri);
slop_option_string ttl_prefix_map_lookup(ttl_PrefixMap pm, slop_string prefix);
slop_option_int ttl_blank_label_lookup(slop_list_ttl_BlankLabelBinding labels, slop_string label);
ttl_TtlParseContext ttl_make_ttl_context(slop_arena* arena, slop_string input);
ttl_GenBlankResult ttl_context_gen_blank_id(slop_arena* arena, ttl_TtlParseContext ctx);
ttl_TtlParseContext ttl_ctx_with_state(ttl_TtlParseContext ctx, common_ParseState state);
slop_string ttl_iri_string(rdf_Term t);
slop_list_rdf_Triple ttl_list_push_triples(slop_arena* arena, slop_list_rdf_Triple dst, slop_list_rdf_Triple src);
rdf_Graph ttl_graph_add_all(slop_arena* arena, rdf_Graph g, slop_list_rdf_Triple src);
slop_option_string ttl_some_string(slop_string value);
slop_result_ttl_TermResult_common_ParseError ttl_parse_iri_ref(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StringResult_common_ParseError ttl_parse_iri_ref_string(slop_arena* arena, ttl_TtlParseContext ctx);
common_ParseWhileResult ttl_parse_pn_local(slop_arena* arena, common_ParseState state);
slop_result_ttl_TermResult_common_ParseError ttl_parse_prefixed_name(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StringResult_common_ParseError ttl_parse_prefixed_name_string(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_blank_node_extended(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_blank_node(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StringResult_common_ParseError ttl_parse_string_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_EscapeResult_common_ParseError ttl_parse_escape_sequence(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_numeric_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_boolean_literal(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_term(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_collection(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_common_ParseState_common_ParseError ttl_expect_triple_term_close(slop_arena* arena, common_ParseState state);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_triple_term(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_term_extended(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_directive(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_sparql_prefix(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TripleResult_common_ParseError ttl_parse_triple(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TriplesResult_common_ParseError ttl_parse_predicate_object_list(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject);
slop_result_ttl_TriplesResult_common_ParseError ttl_parse_annotation(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Triple base_triple);
slop_result_ttl_TriplesResult_common_ParseError ttl_parse_object_list(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, rdf_Term predicate);
slop_result_ttl_GraphTriplesResult_common_ParseError ttl_parse_object_list_into_graph(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Graph g, rdf_Term subject, rdf_Term predicate);
slop_result_ttl_GraphTriplesResult_common_ParseError ttl_parse_predicate_object_list_into_graph(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Graph g, rdf_Term subject);
int64_t ttl_emit_triples(slop_list_rdf_Triple triples, slop_closure_t callback);
slop_result_ttl_StreamTriplesResult_common_ParseError ttl_parse_object_list_for_each_triple(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, rdf_Term predicate, slop_closure_t callback);
slop_result_ttl_StreamTriplesResult_common_ParseError ttl_parse_predicate_object_list_for_each_triple(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, slop_closure_t callback);
slop_result_rdf_Graph_common_ParseError ttl_parse_ttl_string(slop_arena* arena, slop_string input);
slop_result_int_common_ParseError ttl_parse_ttl_string_for_each_triple(slop_arena* arena, slop_string input, slop_closure_t callback);
slop_result_rdf_Graph_ttl_TtlFileError ttl_parse_ttl_file(slop_arena* arena, slop_string path);
slop_result_int_ttl_TtlFileError ttl_parse_ttl_file_for_each_triple(slop_arena* arena, slop_string path, slop_closure_t callback);
uint8_t ttl_is_pn_chars_base(uint8_t c);
uint8_t ttl_is_pn_chars(uint8_t c);

static uint8_t _wrap_ttl_is_pn_chars(void* _env, uint8_t _p0) { return ttl_is_pn_chars(_p0); }

static uint8_t _wrap_ttl_is_pn_chars_base(void* _env, uint8_t _p0) { return ttl_is_pn_chars_base(_p0); }

ttl_PrefixMap ttl_make_prefix_map(slop_arena* arena) {
    ttl_PrefixMap _retval = {0};
    _retval = ((ttl_PrefixMap){.bindings = ((slop_list_ttl_PrefixBinding){ .data = (ttl_PrefixBinding*)slop_arena_alloc(arena, 16 * sizeof(ttl_PrefixBinding)), .len = 0, .cap = 16 }), .count = 0});
    SLOP_POST(((_retval.count == 0)), "(== $result.count 0)");
    return _retval;
}

ttl_PrefixMap ttl_prefix_map_add(slop_arena* arena, ttl_PrefixMap pm, slop_string prefix, slop_string iri) {
    ttl_PrefixMap _retval = {0};
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
    ttl_TtlParseContext _retval = {0};
    _retval = ((ttl_TtlParseContext){.prefixes = ttl_make_prefix_map(arena), .base_iri = (slop_option_string){.has_value = false}, .blank_labels = ((slop_list_ttl_BlankLabelBinding){ .data = (ttl_BlankLabelBinding*)slop_arena_alloc(arena, 16 * sizeof(ttl_BlankLabelBinding)), .len = 0, .cap = 16 }), .blank_counter = 0, .state = common_make_parse_state(arena, input)});
    SLOP_POST(((_retval.blank_counter == 0)), "(== $result.blank-counter 0)");
    return _retval;
}

ttl_GenBlankResult ttl_context_gen_blank_id(slop_arena* arena, ttl_TtlParseContext ctx) {
    ttl_GenBlankResult _retval = {0};
    _retval = ((ttl_GenBlankResult){.id = ctx.blank_counter, .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = (ctx.blank_counter + 1), .state = ctx.state})});
    SLOP_POST(((_retval.id == ctx.blank_counter)), "(== $result.id ctx.blank-counter)");
    SLOP_POST(((_retval.ctx.blank_counter == (ctx.blank_counter + 1))), "(== $result.ctx.blank-counter (+ ctx.blank-counter 1))");
    return _retval;
}

ttl_TtlParseContext ttl_ctx_with_state(ttl_TtlParseContext ctx, common_ParseState state) {
    return ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = state});
}

slop_string ttl_iri_string(rdf_Term t) {
    __auto_type _mv_302 = t;
    switch (_mv_302.tag) {
        case rdf_Term_term_iri:
        {
            __auto_type iri = _mv_302.data.term_iri;
            return iri.value;
        }
        default: {
            return SLOP_STR("");
        }
    }
}

slop_list_rdf_Triple ttl_list_push_triples(slop_arena* arena, slop_list_rdf_Triple dst, slop_list_rdf_Triple src) {
    {
        __auto_type acc = dst;
        {
            __auto_type _coll = src;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                ({ __auto_type _lst_p = &(acc); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
            }
        }
        return acc;
    }
}

rdf_Graph ttl_graph_add_all(slop_arena* arena, rdf_Graph g, slop_list_rdf_Triple src) {
    {
        __auto_type acc = g;
        {
            __auto_type _coll = src;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                acc = rdf_graph_add_unchecked(arena, acc, t);
            }
        }
        return acc;
    }
}

slop_option_string ttl_some_string(slop_string value) {
    return (slop_option_string){.has_value = 1, .value = value};
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_iri_ref(slop_arena* arena, ttl_TtlParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.state) == 60)), "(== (state-peek ctx.state) 60)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.state);
        {
            __auto_type res = ({ __auto_type _tmp = common_parse_until(arena, s1, 62); if (!_tmp.is_ok) return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_iri(arena, res.result), .ctx = ttl_ctx_with_state(ctx, res.state)}) });
        }
    }
}

slop_result_ttl_StringResult_common_ParseError ttl_parse_iri_ref_string(slop_arena* arena, ttl_TtlParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.state) == 60)), "(== (state-peek ctx.state) 60)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.state);
        {
            __auto_type res = ({ __auto_type _tmp = common_parse_until(arena, s1, 62); if (!_tmp.is_ok) return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
            return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringResult){.value = res.result, .ctx = ttl_ctx_with_state(ctx, res.state)}) });
        }
    }
}

common_ParseWhileResult ttl_parse_pn_local(slop_arena* arena, common_ParseState state) {
    {
        __auto_type start = state.offset;
        __auto_type len = string_len(state.input);
        int64_t offset = state.offset;
        int64_t column = state.column;
        uint8_t done = 0;
        while (!(done)) {
            if (offset >= len) {
                done = 1;
            } else {
                {
                    __auto_type c = strlib_char_at(state.input, offset);
                    if (ttl_is_pn_chars(c)) {
                        offset = (offset + 1);
                        column = (column + 1);
                    } else if ((c == 46) && ((offset + 1) < len)) {
                        {
                            __auto_type c2 = strlib_char_at(state.input, (offset + 1));
                            if (ttl_is_pn_chars(c2)) {
                                offset = (offset + 2);
                                column = (column + 2);
                            } else {
                                done = 1;
                            }
                        }
                    } else {
                        done = 1;
                    }
                }
            }
        }
        return ((common_ParseWhileResult){.result = strlib_substring(arena, state.input, start, (offset - start)), .state = ((common_ParseState){.input = state.input, .offset = offset, .line = state.line, .column = column})});
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_prefixed_name(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type prefix_result = common_parse_while(arena, ctx.state, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
        {
            __auto_type s2 = ({ __auto_type _tmp = common_expect_char(arena, prefix_result.state, 58); if (!_tmp.is_ok) return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
            {
                __auto_type local_result = ttl_parse_pn_local(arena, s2);
                __auto_type lookup = ttl_prefix_map_lookup(ctx.prefixes, prefix_result.result);
                __auto_type _mv_303 = lookup;
                if (_mv_303.has_value) {
                    __auto_type base_iri = _mv_303.value;
                    return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_iri(arena, string_concat(arena, base_iri, local_result.result)), .ctx = ttl_ctx_with_state(ctx, local_result.state)}) });
                } else if (!_mv_303.has_value) {
                    return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unknown_prefix, SLOP_STR("Unknown prefix"), ((common_Position){.line = prefix_result.state.line, .column = prefix_result.state.column, .offset = prefix_result.state.offset})) });
                }
            }
        }
    }
}

slop_result_ttl_StringResult_common_ParseError ttl_parse_prefixed_name_string(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type prefix_result = common_parse_while(arena, ctx.state, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
        {
            __auto_type s2 = ({ __auto_type _tmp = common_expect_char(arena, prefix_result.state, 58); if (!_tmp.is_ok) return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
            {
                __auto_type local_result = ttl_parse_pn_local(arena, s2);
                __auto_type lookup = ttl_prefix_map_lookup(ctx.prefixes, prefix_result.result);
                __auto_type _mv_304 = lookup;
                if (_mv_304.has_value) {
                    __auto_type base_iri = _mv_304.value;
                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringResult){.value = string_concat(arena, base_iri, local_result.result), .ctx = ttl_ctx_with_state(ctx, local_result.state)}) });
                } else if (!_mv_304.has_value) {
                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unknown_prefix, SLOP_STR("Unknown prefix"), ((common_Position){.line = prefix_result.state.line, .column = prefix_result.state.column, .offset = prefix_result.state.offset})) });
                }
            }
        }
    }
}

slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_blank_node_extended(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.state);
        if (c == 91) {
            {
                __auto_type s2 = common_skip_whitespace(arena, common_state_advance(arena, ctx.state));
                if (common_state_peek(s2) == 93) {
                    {
                        __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
                        return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, gen.id), .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = ttl_ctx_with_state(gen.ctx, common_state_advance(arena, s2))}) });
                    }
                } else {
                    {
                        __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
                        {
                            __auto_type bnode = rdf_make_blank(arena, gen.id);
                            {
                                __auto_type polr = ({ __auto_type _tmp = ttl_parse_predicate_object_list(arena, ttl_ctx_with_state(gen.ctx, s2), bnode); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                {
                                    __auto_type s5 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, polr.ctx.state), 93); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = bnode, .extra_triples = polr.triples, .ctx = ttl_ctx_with_state(polr.ctx, s5)}) });
                                }
                            }
                        }
                    }
                }
            }
        } else {
            {
                __auto_type s3 = ({ __auto_type _tmp = common_expect_char(arena, common_state_advance(arena, ctx.state), 58); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                {
                    __auto_type label_result = common_parse_while(arena, s3, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
                    {
                        __auto_type label_str = label_result.result;
                        __auto_type existing = ttl_blank_label_lookup(ctx.blank_labels, label_result.result);
                        __auto_type _mv_305 = existing;
                        if (_mv_305.has_value) {
                            __auto_type existing_id = _mv_305.value;
                            return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, existing_id), .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = ttl_ctx_with_state(ctx, label_result.state)}) });
                        } else if (!_mv_305.has_value) {
                            {
                                __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
                                __auto_type labels = ctx.blank_labels;
                                ({ __auto_type _lst_p = &(labels); __auto_type _item = (((ttl_BlankLabelBinding){.label = label_str, .id = gen.id})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, gen.id), .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = labels, .blank_counter = gen.ctx.blank_counter, .state = label_result.state})}) });
                            }
                        }
                    }
                }
            }
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_blank_node(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type ttr = ({ __auto_type _tmp = ttl_parse_blank_node_extended(arena, ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = ttr.term, .ctx = ttr.ctx}) });
    }
}

slop_result_ttl_StringResult_common_ParseError ttl_parse_string_literal(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type q = common_state_peek(ctx.state);
        __auto_type s = common_state_advance(arena, ctx.state);
        __auto_type result = SLOP_STR("");
        if ((common_state_peek(s) == q) && (common_state_peek_n(s, 1) == q)) {
            s = common_state_advance(arena, s);
            s = common_state_advance(arena, s);
            {
                uint8_t done = 0;
                while (!(done) && !(common_state_at_end(s))) {
                    {
                        __auto_type c = common_state_peek(s);
                        if (c == 92) {
                            {
                                __auto_type esc = ttl_parse_escape_sequence(arena, ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s}));
                                __auto_type _mv_306 = esc;
                                if (_mv_306.is_ok) {
                                    __auto_type er = _mv_306.data.ok;
                                    result = slop_string_push_char(arena, result, er.slop_char);
                                    s = er.ctx.state;
                                } else if (!_mv_306.is_ok) {
                                    __auto_type e = _mv_306.data.err;
                                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = e });
                                    /* empty list */;
                                }
                            }
                        } else if ((c == q) && ((common_state_peek_n(s, 1) == q) && (common_state_peek_n(s, 2) == q))) {
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
                __auto_type input = s.input;
                __auto_type len = string_len(s.input);
                __auto_type start = s.offset;
                int64_t scan = s.offset;
                uint8_t fast_done = 0;
                while (!(fast_done) && (scan < len)) {
                    {
                        __auto_type c = strlib_char_at(input, scan);
                        if ((c == 92) || (c == 10)) {
                            fast_done = 1;
                        } else if (c == q) {
                            fast_done = 1;
                        } else {
                            scan = (scan + 1);
                        }
                    }
                }
                if ((scan < len) && (strlib_char_at(input, scan) == q)) {
                    return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringResult){.value = strlib_substring(arena, input, start, (scan - start)), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = ((common_ParseState){.input = input, .offset = (scan + 1), .line = s.line, .column = (s.column + ((scan - start) + 1))})})}) });
                } else {
                    {
                        uint8_t done = 0;
                        while (!(done) && !(common_state_at_end(s))) {
                            {
                                __auto_type c = common_state_peek(s);
                                if (c == 92) {
                                    {
                                        __auto_type esc = ttl_parse_escape_sequence(arena, ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s}));
                                        __auto_type _mv_307 = esc;
                                        if (_mv_307.is_ok) {
                                            __auto_type er = _mv_307.data.ok;
                                            result = slop_string_push_char(arena, result, er.slop_char);
                                            s = er.ctx.state;
                                        } else if (!_mv_307.is_ok) {
                                            __auto_type e = _mv_307.data.err;
                                            return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = e });
                                            /* empty list */;
                                        }
                                    }
                                } else if (c == q) {
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
                    if (c == 110) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 10, .ctx = new_ctx}) });
                    } else if (c == 116) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 9, .ctx = new_ctx}) });
                    } else if (c == 114) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 13, .ctx = new_ctx}) });
                    } else if (c == 92) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 92, .ctx = new_ctx}) });
                    } else if (c == 34) {
                        return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = 34, .ctx = new_ctx}) });
                    } else if (c == 39) {
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
        __auto_type sr = ({ __auto_type _tmp = ttl_parse_string_literal(arena, ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        {
            __auto_type s = sr.ctx.state;
            __auto_type val = sr.value;
            if ((common_state_peek(s) == 94) && (common_state_peek_n(s, 1) == 94)) {
                {
                    __auto_type s2 = common_state_advance(arena, common_state_advance(arena, s));
                    {
                        __auto_type dt_ctx = ttl_ctx_with_state(sr.ctx, s2);
                        if (common_state_peek(s2) == 60) {
                            {
                                __auto_type ir = ({ __auto_type _tmp = ttl_parse_iri_ref_string(arena, dt_ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                {
                                    slop_string datatype = ir.value;
                                    __auto_type dt = ttl_some_string(datatype);
                                    return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, dt, ((slop_option_string){.has_value = false})), .ctx = ir.ctx}) });
                                }
                            }
                        } else {
                            {
                                __auto_type pr = ({ __auto_type _tmp = ttl_parse_prefixed_name_string(arena, dt_ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                {
                                    slop_string datatype = pr.value;
                                    __auto_type dt = ttl_some_string(datatype);
                                    return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, dt, ((slop_option_string){.has_value = false})), .ctx = pr.ctx}) });
                                }
                            }
                        }
                    }
                }
            } else if (common_state_peek(s) == 64) {
                {
                    __auto_type s2 = common_state_advance(arena, s);
                    {
                        __auto_type lang_result = common_parse_while(arena, s2, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
                        return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, ((slop_option_string){.has_value = false}), (slop_option_string){.has_value = 1, .value = lang_result.result}), .ctx = ttl_ctx_with_state(sr.ctx, lang_result.state)}) });
                    }
                }
            } else {
                return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, ((slop_option_string){.has_value = false}), ((slop_option_string){.has_value = false})), .ctx = sr.ctx}) });
            }
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_numeric_literal(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type input = ctx.state.input;
        __auto_type len = string_len(ctx.state.input);
        __auto_type start = ctx.state.offset;
        int64_t offset = ctx.state.offset;
        int64_t column = ctx.state.column;
        uint8_t has_dot = 0;
        uint8_t has_e = 0;
        if ((offset < len) && ((strlib_char_at(input, offset) == 43) || (strlib_char_at(input, offset) == 45))) {
            offset = (offset + 1);
            column = (column + 1);
        }
        while ((offset < len) && strlib_is_digit(strlib_char_at(input, offset))) {
            offset = (offset + 1);
            column = (column + 1);
        }
        if ((offset < len) && (strlib_char_at(input, offset) == 46)) {
            has_dot = 1;
            offset = (offset + 1);
            column = (column + 1);
            while ((offset < len) && strlib_is_digit(strlib_char_at(input, offset))) {
                offset = (offset + 1);
                column = (column + 1);
            }
        }
        if ((offset < len) && ((strlib_char_at(input, offset) == 101) || (strlib_char_at(input, offset) == 69))) {
            has_e = 1;
            offset = (offset + 1);
            column = (column + 1);
            if ((offset < len) && ((strlib_char_at(input, offset) == 43) || (strlib_char_at(input, offset) == 45))) {
                offset = (offset + 1);
                column = (column + 1);
            }
            while ((offset < len) && strlib_is_digit(strlib_char_at(input, offset))) {
                offset = (offset + 1);
                column = (column + 1);
            }
        }
        {
            __auto_type val = strlib_substring(arena, input, start, (offset - start));
            __auto_type dt = (has_e ? SLOP_STR("http://www.w3.org/2001/XMLSchema#double") : (has_dot ? SLOP_STR("http://www.w3.org/2001/XMLSchema#decimal") : SLOP_STR("http://www.w3.org/2001/XMLSchema#integer")));
            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, (slop_option_string){.has_value = 1, .value = dt}, ((slop_option_string){.has_value = false})), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = ((common_ParseState){.input = input, .offset = offset, .line = ctx.state.line, .column = column})})}) });
        }
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_boolean_literal(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.state);
        if (c == 116) {
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
        if (c == 60) {
            return ttl_parse_iri_ref(arena, ctx);
        } else if (c == 95) {
            return ttl_parse_blank_node(arena, ctx);
        } else if ((c == 34) || (c == 39)) {
            return ttl_parse_literal(arena, ctx);
        } else if (((c >= 48) && (c <= 57)) || ((c == 43) || (c == 45))) {
            return ttl_parse_numeric_literal(arena, ctx);
        } else if (c == 116) {
            {
                __auto_type c2 = common_state_peek_n(ctx.state, 1);
                __auto_type c3 = common_state_peek_n(ctx.state, 2);
                __auto_type c4 = common_state_peek_n(ctx.state, 3);
                __auto_type c5 = common_state_peek_n(ctx.state, 4);
                if ((c2 == 114) && ((c3 == 117) && ((c4 == 101) && !((strlib_is_alnum(c5) || ((c5 == 58) || ((c5 == 95) || (c5 == 45)))))))) {
                    return ttl_parse_boolean_literal(arena, ctx);
                } else {
                    return ttl_parse_prefixed_name(arena, ctx);
                }
            }
        } else if (c == 102) {
            {
                __auto_type c2 = common_state_peek_n(ctx.state, 1);
                __auto_type c3 = common_state_peek_n(ctx.state, 2);
                __auto_type c4 = common_state_peek_n(ctx.state, 3);
                __auto_type c5 = common_state_peek_n(ctx.state, 4);
                __auto_type c6 = common_state_peek_n(ctx.state, 5);
                if ((c2 == 97) && ((c3 == 108) && ((c4 == 115) && ((c5 == 101) && !((strlib_is_alnum(c6) || ((c6 == 58) || ((c6 == 95) || (c6 == 45))))))))) {
                    return ttl_parse_boolean_literal(arena, ctx);
                } else {
                    return ttl_parse_prefixed_name(arena, ctx);
                }
            }
        } else if (c == 97) {
            {
                __auto_type c2 = common_state_peek_n(ctx.state, 1);
                if ((c2 == 32) || ((c2 == 9) || ((c2 == 10) || (c2 == 13)))) {
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
        __auto_type triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type cur_ctx = ttl_ctx_with_state(ctx, common_skip_whitespace(arena, common_state_advance(arena, ctx.state)));
        __auto_type rdf_first = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#first"));
        __auto_type rdf_rest = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#rest"));
        __auto_type rdf_nil = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#nil"));
        slop_option_rdf_Term prev_node = (slop_option_rdf_Term){.has_value = false};
        slop_option_rdf_Term first_node = (slop_option_rdf_Term){.has_value = false};
        while (!(common_state_at_end(cur_ctx.state)) && (common_state_peek(cur_ctx.state) != 41)) {
            {
                __auto_type er = ({ __auto_type _tmp = ttl_parse_term_extended(arena, cur_ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                triples = ttl_list_push_triples(arena, triples, er.extra_triples);
                {
                    __auto_type gen = ttl_context_gen_blank_id(arena, er.ctx);
                    {
                        __auto_type cell_node = rdf_make_blank(arena, gen.id);
                        ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, cell_node, rdf_first, er.term)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        __auto_type _mv_308 = prev_node;
                        if (_mv_308.has_value) {
                            __auto_type pn = _mv_308.value;
                            ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, pn, rdf_rest, cell_node)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        } else if (!_mv_308.has_value) {
                            /* empty list */;
                        }
                        __auto_type _mv_309 = first_node;
                        if (_mv_309.has_value) {
                            __auto_type _ = _mv_309.value;
                            /* empty list */;
                        } else if (!_mv_309.has_value) {
                            first_node = (slop_option_rdf_Term){.has_value = 1, .value = cell_node};
                        }
                        prev_node = (slop_option_rdf_Term){.has_value = 1, .value = cell_node};
                        cur_ctx = ttl_ctx_with_state(gen.ctx, common_skip_whitespace(arena, gen.ctx.state));
                    }
                }
            }
        }
        __auto_type _mv_310 = prev_node;
        if (_mv_310.has_value) {
            __auto_type pn = _mv_310.value;
            ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, pn, rdf_rest, rdf_nil)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        } else if (!_mv_310.has_value) {
            /* empty list */;
        }
        {
            __auto_type s_after = ({ __auto_type _tmp = common_expect_char(arena, cur_ctx.state, 41); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
            return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = ({ __auto_type _mv = first_node; _mv.has_value ? ({ __auto_type fnode = _mv.value; fnode; }) : (rdf_nil); }), .extra_triples = triples, .ctx = ttl_ctx_with_state(cur_ctx, s_after)}) });
        }
    }
}

slop_result_common_ParseState_common_ParseError ttl_expect_triple_term_close(slop_arena* arena, common_ParseState state) {
    {
        __auto_type s1 = ({ __auto_type _tmp = common_expect_char(arena, state, 41); if (!_tmp.is_ok) return ((slop_result_common_ParseState_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        {
            __auto_type s2 = ({ __auto_type _tmp = common_expect_char(arena, s1, 62); if (!_tmp.is_ok) return ((slop_result_common_ParseState_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
            return common_expect_char(arena, s2, 62);
        }
    }
}

slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_triple_term(slop_arena* arena, ttl_TtlParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.state) == 60)), "(== (state-peek ctx.state) 60)");
    {
        __auto_type s0 = common_skip_whitespace(arena, common_state_advance(arena, common_state_advance(arena, common_state_advance(arena, ctx.state))));
        __auto_type sr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ttl_ctx_with_state(ctx, s0)); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type pr = ({ __auto_type _tmp = ttl_parse_term(arena, ttl_ctx_with_state(sr.ctx, common_skip_whitespace(arena, sr.ctx.state))); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type objr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ttl_ctx_with_state(pr.ctx, common_skip_whitespace(arena, pr.ctx.state))); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s_end = ({ __auto_type _tmp = ttl_expect_triple_term_close(arena, common_skip_whitespace(arena, objr.ctx.state)); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type extras = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        extras = ttl_list_push_triples(arena, extras, sr.extra_triples);
        extras = ttl_list_push_triples(arena, extras, objr.extra_triples);
        return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_triple_term(arena, rdf_make_triple(arena, sr.term, pr.term, objr.term)), .extra_triples = extras, .ctx = ttl_ctx_with_state(objr.ctx, s_end)}) });
    }
}

slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_term_extended(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.state);
        if (c == 91) {
            return ttl_parse_blank_node_extended(arena, ctx);
        } else if (c == 40) {
            return ttl_parse_collection(arena, ctx);
        } else if ((c == 60) && ((common_state_peek_n(ctx.state, 1) == 60) && (common_state_peek_n(ctx.state, 2) == 40))) {
            return ttl_parse_triple_term(arena, ctx);
        } else {
            {
                __auto_type tr = ({ __auto_type _tmp = ttl_parse_term(arena, ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = tr.term, .extra_triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .ctx = tr.ctx}) });
            }
        }
    }
}

slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_directive(slop_arena* arena, ttl_TtlParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.state) == 64)), "(== (state-peek ctx.state) 64)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.state);
        __auto_type kw = common_parse_while(arena, s1, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars_base, NULL});
        __auto_type keyword = kw.result;
        __auto_type s2 = common_skip_whitespace(arena, kw.state);
        if (strlib_starts_with(keyword, SLOP_STR("prefix"))) {
            {
                __auto_type prefix_name = common_parse_while(arena, s2, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
                __auto_type s4 = ({ __auto_type _tmp = common_expect_char(arena, prefix_name.state, 58); if (!_tmp.is_ok) return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                __auto_type ir = ({ __auto_type _tmp = ttl_parse_iri_ref(arena, ttl_ctx_with_state(ctx, common_skip_whitespace(arena, s4))); if (!_tmp.is_ok) return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                __auto_type s8 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, ir.ctx.state), 46); if (!_tmp.is_ok) return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TtlParseContext){.prefixes = ttl_prefix_map_add(arena, ctx.prefixes, prefix_name.result, ttl_iri_string(ir.term)), .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s8}) });
            }
        } else {
            {
                __auto_type ir = ({ __auto_type _tmp = ttl_parse_iri_ref(arena, ttl_ctx_with_state(ctx, s2)); if (!_tmp.is_ok) return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                __auto_type s5 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, ir.ctx.state), 46); if (!_tmp.is_ok) return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = (slop_option_string){.has_value = 1, .value = ttl_iri_string(ir.term)}, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = s5}) });
            }
        }
    }
}

slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_sparql_prefix(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type kw = common_parse_while(arena, ctx.state, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars_base, NULL});
        __auto_type s1 = common_skip_whitespace(arena, kw.state);
        __auto_type prefix_name = common_parse_while(arena, s1, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
        __auto_type s3 = ({ __auto_type _tmp = common_expect_char(arena, prefix_name.state, 58); if (!_tmp.is_ok) return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type ir = ({ __auto_type _tmp = ttl_parse_iri_ref(arena, ttl_ctx_with_state(ctx, common_skip_whitespace(arena, s3))); if (!_tmp.is_ok) return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        return ((slop_result_ttl_TtlParseContext_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TtlParseContext){.prefixes = ttl_prefix_map_add(arena, ctx.prefixes, prefix_name.result, ttl_iri_string(ir.term)), .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = ir.ctx.state}) });
    }
}

slop_result_ttl_TripleResult_common_ParseError ttl_parse_triple(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type sr = ({ __auto_type _tmp = ttl_parse_term(arena, ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type pr = ({ __auto_type _tmp = ttl_parse_term(arena, ttl_ctx_with_state(sr.ctx, common_skip_whitespace(arena, sr.ctx.state))); if (!_tmp.is_ok) return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type objr = ({ __auto_type _tmp = ttl_parse_term(arena, ttl_ctx_with_state(pr.ctx, common_skip_whitespace(arena, pr.ctx.state))); if (!_tmp.is_ok) return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s5 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, objr.ctx.state), 46); if (!_tmp.is_ok) return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        return ((slop_result_ttl_TripleResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TripleResult){.triple = rdf_make_triple(arena, sr.term, pr.term, objr.term), .ctx = ttl_ctx_with_state(objr.ctx, s5)}) });
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
                __auto_type c1 = common_state_peek(s1);
                if ((c1 == 46) || ((c1 == 93) || ((c1 == 0) || (c1 == 124)))) {
                    cur_ctx = ttl_ctx_with_state(cur_ctx, s1);
                    done = 1;
                } else {
                    {
                        __auto_type pr = ({ __auto_type _tmp = ttl_parse_term(arena, ttl_ctx_with_state(cur_ctx, s1)); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                        __auto_type olr = ({ __auto_type _tmp = ttl_parse_object_list(arena, pr.ctx, subject, pr.term); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                        triples = ttl_list_push_triples(arena, triples, olr.triples);
                        cur_ctx = olr.ctx;
                        {
                            __auto_type s3 = common_skip_whitespace(arena, olr.ctx.state);
                            if (common_state_peek(s3) == 59) {
                                cur_ctx = ttl_ctx_with_state(cur_ctx, common_state_advance(arena, s3));
                            } else {
                                done = 1;
                            }
                        }
                    }
                }
            }
        }
        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TriplesResult){.triples = triples, .ctx = cur_ctx}) });
    }
}

slop_result_ttl_TriplesResult_common_ParseError ttl_parse_annotation(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Triple base_triple) {
    SLOP_PRE(((common_state_peek(ctx.state) == 123)), "(== (state-peek ctx.state) 123)");
    {
        __auto_type s1 = common_state_advance(arena, common_state_advance(arena, ctx.state));
        __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
        __auto_type reifier = rdf_make_blank(arena, gen.id);
        __auto_type reifies = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/1999/02/22-rdf-syntax-ns#reifies"));
        __auto_type triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type polr = ({ __auto_type _tmp = ttl_parse_predicate_object_list(arena, ttl_ctx_with_state(gen.ctx, s1), reifier); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s2 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, polr.ctx.state), 124); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s3 = ({ __auto_type _tmp = common_expect_char(arena, s2, 125); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, reifier, reifies, rdf_make_triple_term(arena, base_triple))); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        triples = ttl_list_push_triples(arena, triples, polr.triples);
        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TriplesResult){.triples = triples, .ctx = ttl_ctx_with_state(polr.ctx, s3)}) });
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
                __auto_type objr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ttl_ctx_with_state(cur_ctx, s1)); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                triples = ttl_list_push_triples(arena, triples, objr.extra_triples);
                ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, subject, predicate, objr.term)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                cur_ctx = objr.ctx;
                {
                    uint8_t ann_done = 0;
                    while (!(ann_done)) {
                        {
                            __auto_type sa = common_skip_whitespace(arena, cur_ctx.state);
                            if ((common_state_peek(sa) == 123) && (common_state_peek_n(sa, 1) == 124)) {
                                {
                                    __auto_type ar = ({ __auto_type _tmp = ttl_parse_annotation(arena, ttl_ctx_with_state(cur_ctx, sa), rdf_make_triple(arena, subject, predicate, objr.term)); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                    triples = ttl_list_push_triples(arena, triples, ar.triples);
                                    cur_ctx = ar.ctx;
                                }
                            } else {
                                ann_done = 1;
                            }
                        }
                    }
                }
                {
                    __auto_type s2 = common_skip_whitespace(arena, cur_ctx.state);
                    if (common_state_peek(s2) == 44) {
                        cur_ctx = ttl_ctx_with_state(cur_ctx, common_state_advance(arena, s2));
                    } else {
                        done = 1;
                    }
                }
            }
        }
        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TriplesResult){.triples = triples, .ctx = cur_ctx}) });
    }
}

slop_result_ttl_GraphTriplesResult_common_ParseError ttl_parse_object_list_into_graph(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Graph g, rdf_Term subject, rdf_Term predicate) {
    {
        __auto_type acc = g;
        __auto_type cur_ctx = ctx;
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type s1 = common_skip_whitespace(arena, cur_ctx.state);
                __auto_type objr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ttl_ctx_with_state(cur_ctx, s1)); if (!_tmp.is_ok) return ((slop_result_ttl_GraphTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                acc = ttl_graph_add_all(arena, acc, objr.extra_triples);
                acc = rdf_graph_add_unchecked(arena, acc, rdf_make_triple(arena, subject, predicate, objr.term));
                cur_ctx = objr.ctx;
                {
                    uint8_t ann_done = 0;
                    while (!(ann_done)) {
                        {
                            __auto_type sa = common_skip_whitespace(arena, cur_ctx.state);
                            if ((common_state_peek(sa) == 123) && (common_state_peek_n(sa, 1) == 124)) {
                                {
                                    __auto_type ar = ({ __auto_type _tmp = ttl_parse_annotation(arena, ttl_ctx_with_state(cur_ctx, sa), rdf_make_triple(arena, subject, predicate, objr.term)); if (!_tmp.is_ok) return ((slop_result_ttl_GraphTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                    acc = ttl_graph_add_all(arena, acc, ar.triples);
                                    cur_ctx = ar.ctx;
                                }
                            } else {
                                ann_done = 1;
                            }
                        }
                    }
                }
                {
                    __auto_type s2 = common_skip_whitespace(arena, cur_ctx.state);
                    if (common_state_peek(s2) == 44) {
                        cur_ctx = ttl_ctx_with_state(cur_ctx, common_state_advance(arena, s2));
                    } else {
                        done = 1;
                    }
                }
            }
        }
        return ((slop_result_ttl_GraphTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_GraphTriplesResult){.graph = acc, .ctx = cur_ctx}) });
    }
}

slop_result_ttl_GraphTriplesResult_common_ParseError ttl_parse_predicate_object_list_into_graph(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Graph g, rdf_Term subject) {
    {
        __auto_type acc = g;
        __auto_type cur_ctx = ctx;
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type s1 = common_skip_whitespace(arena, cur_ctx.state);
                __auto_type c1 = common_state_peek(s1);
                if ((c1 == 46) || ((c1 == 93) || ((c1 == 0) || (c1 == 124)))) {
                    cur_ctx = ttl_ctx_with_state(cur_ctx, s1);
                    done = 1;
                } else {
                    {
                        __auto_type pr = ({ __auto_type _tmp = ttl_parse_term(arena, ttl_ctx_with_state(cur_ctx, s1)); if (!_tmp.is_ok) return ((slop_result_ttl_GraphTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                        __auto_type olr = ({ __auto_type _tmp = ttl_parse_object_list_into_graph(arena, pr.ctx, acc, subject, pr.term); if (!_tmp.is_ok) return ((slop_result_ttl_GraphTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                        acc = olr.graph;
                        cur_ctx = olr.ctx;
                        {
                            __auto_type s3 = common_skip_whitespace(arena, olr.ctx.state);
                            if (common_state_peek(s3) == 59) {
                                cur_ctx = ttl_ctx_with_state(cur_ctx, common_state_advance(arena, s3));
                            } else {
                                done = 1;
                            }
                        }
                    }
                }
            }
        }
        return ((slop_result_ttl_GraphTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_GraphTriplesResult){.graph = acc, .ctx = cur_ctx}) });
    }
}

int64_t ttl_emit_triples(slop_list_rdf_Triple triples, slop_closure_t callback) {
    {
        int64_t count = 0;
        {
            __auto_type _coll = triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                count = (count + 1);
            }
        }
        return count;
    }
}

slop_result_ttl_StreamTriplesResult_common_ParseError ttl_parse_object_list_for_each_triple(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, rdf_Term predicate, slop_closure_t callback) {
    {
        int64_t count = 0;
        __auto_type cur_ctx = ctx;
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type s1 = common_skip_whitespace(arena, cur_ctx.state);
                __auto_type objr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ttl_ctx_with_state(cur_ctx, s1)); if (!_tmp.is_ok) return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                count = (count + ttl_emit_triples(objr.extra_triples, callback));
                {
                    __auto_type base_triple = rdf_make_triple(arena, subject, predicate, objr.term);
                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, base_triple);
                    count = (count + 1);
                    cur_ctx = objr.ctx;
                    {
                        uint8_t ann_done = 0;
                        while (!(ann_done)) {
                            {
                                __auto_type sa = common_skip_whitespace(arena, cur_ctx.state);
                                if ((common_state_peek(sa) == 123) && (common_state_peek_n(sa, 1) == 124)) {
                                    {
                                        __auto_type ar = ({ __auto_type _tmp = ttl_parse_annotation(arena, ttl_ctx_with_state(cur_ctx, sa), base_triple); if (!_tmp.is_ok) return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                        count = (count + ttl_emit_triples(ar.triples, callback));
                                        cur_ctx = ar.ctx;
                                    }
                                } else {
                                    ann_done = 1;
                                }
                            }
                        }
                    }
                }
                {
                    __auto_type s2 = common_skip_whitespace(arena, cur_ctx.state);
                    if (common_state_peek(s2) == 44) {
                        cur_ctx = ttl_ctx_with_state(cur_ctx, common_state_advance(arena, s2));
                    } else {
                        done = 1;
                    }
                }
            }
        }
        return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StreamTriplesResult){.count = count, .ctx = cur_ctx}) });
    }
}

slop_result_ttl_StreamTriplesResult_common_ParseError ttl_parse_predicate_object_list_for_each_triple(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, slop_closure_t callback) {
    {
        int64_t count = 0;
        __auto_type cur_ctx = ctx;
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type s1 = common_skip_whitespace(arena, cur_ctx.state);
                __auto_type c1 = common_state_peek(s1);
                if ((c1 == 46) || ((c1 == 93) || ((c1 == 0) || (c1 == 124)))) {
                    cur_ctx = ttl_ctx_with_state(cur_ctx, s1);
                    done = 1;
                } else {
                    {
                        __auto_type pr = ({ __auto_type _tmp = ttl_parse_term(arena, ttl_ctx_with_state(cur_ctx, s1)); if (!_tmp.is_ok) return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                        __auto_type olr = ({ __auto_type _tmp = ttl_parse_object_list_for_each_triple(arena, pr.ctx, subject, pr.term, callback); if (!_tmp.is_ok) return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                        count = (count + olr.count);
                        cur_ctx = olr.ctx;
                        {
                            __auto_type s3 = common_skip_whitespace(arena, olr.ctx.state);
                            if (common_state_peek(s3) == 59) {
                                cur_ctx = ttl_ctx_with_state(cur_ctx, common_state_advance(arena, s3));
                            } else {
                                done = 1;
                            }
                        }
                    }
                }
            }
        }
        return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StreamTriplesResult){.count = count, .ctx = cur_ctx}) });
    }
}

slop_result_rdf_Graph_common_ParseError ttl_parse_ttl_string(slop_arena* arena, slop_string input) {
    SLOP_PRE(((string_len(input) > 0)), "(> (string-len input) 0)");
    {
        __auto_type ctx = ttl_make_ttl_context(arena, input);
        __auto_type g = rdf_make_graph(arena);
        {
            __auto_type s = common_skip_whitespace(arena, ctx.state);
            ctx = ttl_ctx_with_state(ctx, s);
            while (!(common_state_at_end(ctx.state))) {
                {
                    __auto_type c = common_state_peek(ctx.state);
                    if (c == 64) {
                        ctx = ({ __auto_type _tmp = ttl_parse_directive(arena, ctx); if (!_tmp.is_ok) return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                    } else if ((c == 80) || (c == 66)) {
                        ctx = ({ __auto_type _tmp = ttl_parse_sparql_prefix(arena, ctx); if (!_tmp.is_ok) return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                    } else {
                        {
                            __auto_type sr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ctx); if (!_tmp.is_ok) return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                            g = ttl_graph_add_all(arena, g, sr.extra_triples);
                            {
                                __auto_type polr = ({ __auto_type _tmp = ttl_parse_predicate_object_list_into_graph(arena, sr.ctx, g, sr.term); if (!_tmp.is_ok) return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                __auto_type s5 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, polr.ctx.state), 46); if (!_tmp.is_ok) return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                g = polr.graph;
                                ctx = ttl_ctx_with_state(polr.ctx, s5);
                            }
                        }
                    }
                }
                ctx = ttl_ctx_with_state(ctx, common_skip_whitespace(arena, ctx.state));
            }
        }
        return ((slop_result_rdf_Graph_common_ParseError){ .is_ok = true, .data.ok = g });
    }
}

slop_result_int_common_ParseError ttl_parse_ttl_string_for_each_triple(slop_arena* arena, slop_string input, slop_closure_t callback) {
    SLOP_PRE(((string_len(input) > 0)), "(> (string-len input) 0)");
    {
        __auto_type ctx = ttl_make_ttl_context(arena, input);
        int64_t count = 0;
        {
            __auto_type s = common_skip_whitespace(arena, ctx.state);
            ctx = ttl_ctx_with_state(ctx, s);
            while (!(common_state_at_end(ctx.state))) {
                {
                    __auto_type c = common_state_peek(ctx.state);
                    if (c == 64) {
                        ctx = ({ __auto_type _tmp = ttl_parse_directive(arena, ctx); if (!_tmp.is_ok) return ((slop_result_int_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                    } else if ((c == 80) || (c == 66)) {
                        ctx = ({ __auto_type _tmp = ttl_parse_sparql_prefix(arena, ctx); if (!_tmp.is_ok) return ((slop_result_int_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                    } else {
                        {
                            __auto_type sr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ctx); if (!_tmp.is_ok) return ((slop_result_int_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                            count = (count + ttl_emit_triples(sr.extra_triples, callback));
                            {
                                __auto_type polr = ({ __auto_type _tmp = ttl_parse_predicate_object_list_for_each_triple(arena, sr.ctx, sr.term, callback); if (!_tmp.is_ok) return ((slop_result_int_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                __auto_type s5 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, polr.ctx.state), 46); if (!_tmp.is_ok) return ((slop_result_int_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                count = (count + polr.count);
                                ctx = ttl_ctx_with_state(polr.ctx, s5);
                            }
                        }
                    }
                }
                ctx = ttl_ctx_with_state(ctx, common_skip_whitespace(arena, ctx.state));
            }
        }
        return ((slop_result_int_common_ParseError){ .is_ok = true, .data.ok = count });
    }
}

slop_result_rdf_Graph_ttl_TtlFileError ttl_parse_ttl_file(slop_arena* arena, slop_string path) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type f = file_file_open(path, file_FileMode_read);
        __auto_type _mv_311 = f;
        if (_mv_311.is_ok) {
            __auto_type handle = _mv_311.data.ok;
            {
                __auto_type content = file_file_read_all(arena, (&handle));
                __auto_type _mv_312 = content;
                if (_mv_312.is_ok) {
                    __auto_type text = _mv_312.data.ok;
                    file_file_close((&handle));
                    __auto_type _mv_313 = ttl_parse_ttl_string(arena, text);
                    if (_mv_313.is_ok) {
                        __auto_type g = _mv_313.data.ok;
                        return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = true, .data.ok = g });
                    } else if (!_mv_313.is_ok) {
                        __auto_type e = _mv_313.data.err;
                        return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_parse_error, .data.parse_error = e }) });
                    }
                } else if (!_mv_312.is_ok) {
                    __auto_type e = _mv_312.data.err;
                    file_file_close((&handle));
                    return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
                }
            }
        } else if (!_mv_311.is_ok) {
            __auto_type e = _mv_311.data.err;
            return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
        }
    }
}

slop_result_int_ttl_TtlFileError ttl_parse_ttl_file_for_each_triple(slop_arena* arena, slop_string path, slop_closure_t callback) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type f = file_file_open(path, file_FileMode_read);
        __auto_type _mv_314 = f;
        if (_mv_314.is_ok) {
            __auto_type handle = _mv_314.data.ok;
            {
                __auto_type content = file_file_read_all(arena, (&handle));
                __auto_type _mv_315 = content;
                if (_mv_315.is_ok) {
                    __auto_type text = _mv_315.data.ok;
                    file_file_close((&handle));
                    __auto_type _mv_316 = ttl_parse_ttl_string_for_each_triple(arena, text, callback);
                    if (_mv_316.is_ok) {
                        __auto_type count = _mv_316.data.ok;
                        return ((slop_result_int_ttl_TtlFileError){ .is_ok = true, .data.ok = count });
                    } else if (!_mv_316.is_ok) {
                        __auto_type e = _mv_316.data.err;
                        return ((slop_result_int_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_parse_error, .data.parse_error = e }) });
                    }
                } else if (!_mv_315.is_ok) {
                    __auto_type e = _mv_315.data.err;
                    file_file_close((&handle));
                    return ((slop_result_int_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
                }
            }
        } else if (!_mv_314.is_ok) {
            __auto_type e = _mv_314.data.err;
            return ((slop_result_int_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
        }
    }
}

uint8_t ttl_is_pn_chars_base(uint8_t c) {
    return strlib_is_alpha(c);
}

uint8_t ttl_is_pn_chars(uint8_t c) {
    return (ttl_is_pn_chars_base(c) || (strlib_is_digit(c) || ((c == 95) || (c == 45))));
}

