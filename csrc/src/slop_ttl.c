#include "../runtime/slop_runtime.h"
#include "slop_ttl.h"

ttl_PrefixMap ttl_make_prefix_map(slop_arena* arena);
ttl_PrefixMap ttl_prefix_map_add(slop_arena* arena, ttl_PrefixMap pm, slop_string prefix, slop_string iri);
slop_option_string ttl_prefix_map_lookup(ttl_PrefixMap pm, slop_string prefix);
void ttl_blank_labels_add(slop_arena* arena, slop_map* ids, slop_string label, int64_t id);
ttl_TtlParseContext ttl_make_ttl_context(slop_arena* arena, slop_string input);
ttl_GenBlankResult ttl_context_gen_blank_id(slop_arena* arena, ttl_TtlParseContext ctx);
ttl_TtlParseContext ttl_ctx_with_state(ttl_TtlParseContext ctx, common_ParseState state);
slop_string ttl_iri_string(rdf_Term t);
slop_list_rdf_Triple ttl_list_push_triples(slop_arena* arena, slop_list_rdf_Triple dst, slop_list_rdf_Triple src);
rdf_Graph ttl_graph_add_all(slop_arena* arena, rdf_Graph g, slop_list_rdf_Triple src);
slop_option_string ttl_some_string(slop_string value);
slop_string ttl_input_slice(slop_string input, int64_t start, int64_t len);
common_ParseState ttl_scan_pn_chars(common_ParseState state);
slop_string ttl_concat_base_slice(slop_arena* arena, slop_string base, slop_string input, int64_t start, int64_t len);
slop_result_ttl_TermResult_common_ParseError ttl_parse_iri_ref(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StringResult_common_ParseError ttl_parse_iri_ref_string(slop_arena* arena, ttl_TtlParseContext ctx);
common_ParseState ttl_scan_pn_local(common_ParseState state);
slop_result_ttl_TermResult_common_ParseError ttl_parse_prefixed_name(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StringResult_common_ParseError ttl_parse_prefixed_name_string(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermTriplesResult_common_ParseError ttl_parse_blank_node_extended(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_TermResult_common_ParseError ttl_parse_blank_node(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StringResult_common_ParseError ttl_parse_string_literal(slop_arena* arena, ttl_TtlParseContext ctx);
uint8_t ttl_escape_value(uint8_t c);
slop_result_ttl_StringScan_common_ParseError ttl_scan_string_body(slop_arena* arena, common_ParseState state, uint8_t q, uint8_t slop_long);
slop_string ttl_decode_string_body(slop_arena* arena, slop_string input, int64_t start, int64_t end, int64_t escapes);
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
void ttl_scratch_reset(slop_arena* scratch);
slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_directive_any(slop_arena* arena, ttl_TtlParseContext ctx);
slop_result_ttl_StreamTriplesResult_common_ParseError ttl_parse_statement_for_each_triple(slop_arena* arena, ttl_TtlParseContext ctx, slop_closure_t callback);
slop_result_int_common_ParseError ttl_parse_ttl_string_for_each_triple(slop_arena* arena, slop_string input, slop_closure_t callback);
slop_result_rdf_Graph_ttl_TtlFileError ttl_parse_ttl_file(slop_arena* arena, slop_string path);
slop_result_int_ttl_TtlFileError ttl_parse_ttl_file_for_each_triple(slop_arena* arena, slop_string path, slop_closure_t callback);
uint8_t ttl_is_pn_chars_base(uint8_t c);
uint8_t ttl_is_pn_chars(uint8_t c);

static uint8_t _wrap_ttl_is_pn_chars(void* _env, uint8_t _p0) { return ttl_is_pn_chars(_p0); }

static uint8_t _wrap_ttl_is_pn_chars_base(void* _env, uint8_t _p0) { return ttl_is_pn_chars_base(_p0); }

ttl_PrefixMap ttl_make_prefix_map(slop_arena* arena) {
    ttl_PrefixMap _retval = {0};
    _retval = ((ttl_PrefixMap){.bindings = ((slop_list_ttl_PrefixBinding){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .count = 0});
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval.count == 0)), "(== $result.count 0)");
    return _retval;
}

ttl_PrefixMap ttl_prefix_map_add(slop_arena* arena, ttl_PrefixMap pm, slop_string prefix, slop_string iri) {
    ttl_PrefixMap _retval = {0};
    ({ __auto_type _lst_p = &(pm.bindings); __auto_type _item = (((ttl_PrefixBinding){.prefix = prefix, .iri = iri})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
    _retval = ((ttl_PrefixMap){.bindings = pm.bindings, .count = (pm.count + 1)});
    goto _slop_post;
    _slop_post: ;
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

void ttl_blank_labels_add(slop_arena* arena, slop_map* ids, slop_string label, int64_t id) {
    ({ slop_string _key_442 = (strlib_substring(arena, label, 0, SLOP_RANGE(int64_t, string_len(label), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:170:43"))); int64_t _val = id; slop_map_put(NULL, ids, &_key_442, &_val, sizeof(_val)); });
}

ttl_TtlParseContext ttl_make_ttl_context(slop_arena* arena, slop_string input) {
    ttl_TtlParseContext _retval = {0};
    _retval = ((ttl_TtlParseContext){.prefixes = ttl_make_prefix_map(arena), .base_iri = (slop_option_string){.has_value = false}, .blank_labels = ((ttl_BlankLabelTable){.arena = arena, .ids = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_string, slop_hash_string, slop_eq_string, SLOP_KEY_HASHED, int64_t); slop_map_new_ptr(arena, 0, &_d); })}), .blank_counter = 0, .state = common_make_parse_state(arena, input)});
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval.blank_counter == 0)), "(== $result.blank-counter 0)");
    return _retval;
}

ttl_GenBlankResult ttl_context_gen_blank_id(slop_arena* arena, ttl_TtlParseContext ctx) {
    ttl_GenBlankResult _retval = {0};
    _retval = ((ttl_GenBlankResult){.id = ctx.blank_counter, .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = (ctx.blank_counter + 1), .state = ctx.state})});
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval.id == ctx.blank_counter)), "(== $result.id ctx.blank-counter)");
    SLOP_POST(((_retval.ctx.blank_counter == (ctx.blank_counter + 1))), "(== $result.ctx.blank-counter (+ ctx.blank-counter 1))");
    return _retval;
}

ttl_TtlParseContext ttl_ctx_with_state(ttl_TtlParseContext ctx, common_ParseState state) {
    return ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = state});
}

slop_string ttl_iri_string(rdf_Term t) {
    __auto_type _mv_443 = t;
    switch (_mv_443.tag) {
        case rdf_Term_term_iri:
        {
            __auto_type iri = _mv_443.data.term_iri;
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
                ({ __auto_type _lst_p = &(acc); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
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

slop_string ttl_input_slice(slop_string input, int64_t start, int64_t len) {
    return (slop_string){.len = ((uint64_t)(len)), .data = (input.data + start)};
}

common_ParseState ttl_scan_pn_chars(common_ParseState state) {
    {
        __auto_type input = state.input;
        __auto_type len = string_len(state.input);
        int64_t offset = state.offset;
        while ((offset < len) && ttl_is_pn_chars(strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:265:62")))) {
            offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:266:22");
        }
        return ((common_ParseState){.input = input, .offset = SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:269:17"), .line = state.line, .column = SLOP_RANGE(int64_t, (state.column + (offset - state.offset)), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:271:17")});
    }
}

slop_string ttl_concat_base_slice(slop_arena* arena, slop_string base, slop_string input, int64_t start, int64_t len) {
    {
        __auto_type blen = ((int64_t)(base.len));
        __auto_type total = (blen + len);
        __auto_type buf = ({ __auto_type _alloc = (uint8_t*)slop_arena_alloc(arena, (total + 1)); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; });
        if (blen > 0) {
            memcpy(((void*)(buf)), ((void*)(base.data)), ((uint64_t)(blen)));
        }
        if (len > 0) {
            memcpy(((void*)((buf + blen))), ((void*)((input.data + start))), ((uint64_t)(len)));
        }
        return (slop_string){.len = ((uint64_t)(total)), .data = ((uint8_t*)(buf))};
    }
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

common_ParseState ttl_scan_pn_local(common_ParseState state) {
    {
        __auto_type len = string_len(state.input);
        int64_t offset = state.offset;
        int64_t column = state.column;
        uint8_t done = 0;
        while (!(done)) {
            if (offset >= len) {
                done = 1;
            } else {
                {
                    __auto_type c = strlib_char_at(state.input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:328:45"));
                    if (ttl_is_pn_chars(c)) {
                        offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:332:32");
                        column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:333:32");
                    } else if ((c == 46) && ((offset + 1) < len)) {
                        {
                            __auto_type c2 = strlib_char_at(state.input, SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:335:52"));
                            if (ttl_is_pn_chars(c2)) {
                                offset = SLOP_RANGE(int64_t, (offset + 2), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:338:36");
                                column = SLOP_RANGE(int64_t, (column + 2), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:339:36");
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
        return ((common_ParseState){.input = state.input, .offset = SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:344:17"), .line = state.line, .column = SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:346:17")});
    }
}

slop_result_ttl_TermResult_common_ParseError ttl_parse_prefixed_name(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type pr = ({ __auto_type _tmp = ttl_parse_prefixed_name_string(arena, ctx); if (!_tmp.is_ok) return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_iri(arena, pr.value), .ctx = pr.ctx}) });
    }
}

slop_result_ttl_StringResult_common_ParseError ttl_parse_prefixed_name_string(slop_arena* arena, ttl_TtlParseContext ctx) {
    {
        __auto_type s0 = ctx.state;
        __auto_type s1 = ttl_scan_pn_chars(s0);
        __auto_type s2 = ({ __auto_type _tmp = common_expect_char(arena, s1, 58); if (!_tmp.is_ok) return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s3 = ttl_scan_pn_local(s2);
        __auto_type input = s0.input;
        __auto_type lookup = ttl_prefix_map_lookup(ctx.prefixes, ttl_input_slice(input, s0.offset, SLOP_RANGE(int64_t, (s1.offset - s0.offset), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:373:54")));
        __auto_type _mv_444 = lookup;
        if (_mv_444.has_value) {
            __auto_type base_iri = _mv_444.value;
            return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringResult){.value = ttl_concat_base_slice(arena, base_iri, input, SLOP_RANGE(int64_t, s2.offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:377:60"), SLOP_RANGE(int64_t, (s3.offset - s2.offset), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:377:74")), .ctx = ttl_ctx_with_state(ctx, s3)}) });
        } else if (!_mv_444.has_value) {
            return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unknown_prefix, SLOP_STR("Unknown prefix"), ((common_Position){.line = s1.line, .column = s1.column, .offset = s1.offset})) });
        }
        SLOP_UNREACHABLE();
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
                        return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, gen.id), .extra_triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .ctx = ttl_ctx_with_state(gen.ctx, common_state_advance(arena, s2))}) });
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
                __auto_type s4 = ttl_scan_pn_chars(s3);
                __auto_type label = ttl_input_slice(s3.input, SLOP_RANGE(int64_t, s3.offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:418:48"), SLOP_RANGE(int64_t, (s4.offset - s3.offset), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:418:62"));
                __auto_type tbl = ctx.blank_labels;
                __auto_type _mv_446 = ({ void* _ptr = slop_map_get(tbl.ids, &(label)); _ptr ? (slop_option_int){ .has_value = true, .value = *(int64_t*)_ptr } : (slop_option_int){ .has_value = false }; });
                if (_mv_446.has_value) {
                    __auto_type existing_id = _mv_446.value;
                    return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, existing_id), .extra_triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .ctx = ttl_ctx_with_state(ctx, s4)}) });
                } else if (!_mv_446.has_value) {
                    {
                        __auto_type gen = ttl_context_gen_blank_id(arena, ctx);
                        ttl_blank_labels_add(tbl.arena, tbl.ids, label, gen.id);
                        return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = rdf_make_blank(arena, gen.id), .extra_triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .ctx = ttl_ctx_with_state(gen.ctx, s4)}) });
                    }
                }
                SLOP_UNREACHABLE();
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
        __auto_type s0 = ctx.state;
        __auto_type q = common_state_peek(s0);
        __auto_type slop_long = ((common_state_peek_n(s0, 1) == q) && (common_state_peek_n(s0, 2) == q));
        __auto_type skip = ((slop_long) ? 3 : 1);
        __auto_type start = (s0.offset + skip);
        __auto_type scan = ({ __auto_type _tmp = ttl_scan_string_body(arena, ((common_ParseState){.input = s0.input, .offset = SLOP_RANGE(int64_t, start, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:470:32"), .line = s0.line, .column = SLOP_RANGE(int64_t, (s0.column + skip), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:472:32")}), SLOP_RANGE(uint8_t, q, 1, 1, 0, 255, "(Int 0 .. 255) at ttl.slop:473:22"), slop_long); if (!_tmp.is_ok) return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        return ((slop_result_ttl_StringResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringResult){.value = ttl_decode_string_body(arena, s0.input, SLOP_RANGE(int64_t, start, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:475:55"), SLOP_RANGE(int64_t, scan.end, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:475:61"), SLOP_RANGE(int64_t, scan.escapes, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:475:74")), .ctx = ttl_ctx_with_state(ctx, scan.state)}) });
    }
}

uint8_t ttl_escape_value(uint8_t c) {
    if (c == 110) {
        return 10;
    } else if (c == 116) {
        return 9;
    } else if (c == 114) {
        return 13;
    } else if (c == 92) {
        return 92;
    } else if (c == 34) {
        return 34;
    } else if (c == 39) {
        return 39;
    } else {
        return 0;
    }
}

slop_result_ttl_StringScan_common_ParseError ttl_scan_string_body(slop_arena* arena, common_ParseState state, uint8_t q, uint8_t slop_long) {
    {
        __auto_type input = state.input;
        __auto_type len = string_len(state.input);
        int64_t offset = state.offset;
        int64_t line = state.line;
        int64_t column = state.column;
        int64_t escapes = 0;
        int64_t end = 0;
        uint8_t done = 0;
        while (!(done) && (offset < len)) {
            {
                __auto_type c = strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:510:33"));
                if (c == 92) {
                    if (ttl_escape_value(strlib_char_at(input, SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:513:52"))) == 0) {
                        return ((slop_result_ttl_StringScan_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_invalid_escape, SLOP_STR("Invalid escape sequence"), ((common_Position){.line = SLOP_RANGE(int64_t, line, 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:515:46"), .column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:515:60"), .offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:515:82")})) });
                    } else {
                        escapes = (escapes + 1);
                        offset = SLOP_RANGE(int64_t, (offset + 2), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:518:32");
                        column = SLOP_RANGE(int64_t, (column + 2), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:519:32");
                    }
                } else if ((c == q) && (!(slop_long) || ((strlib_char_at(input, SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:521:56")) == q) && (strlib_char_at(input, SLOP_RANGE(int64_t, (offset + 2), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:521:92")) == q)))) {
                    end = offset;
                    offset = SLOP_RANGE(int64_t, (offset + ((slop_long) ? 3 : 1)), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:524:30");
                    column = SLOP_RANGE(int64_t, (column + ((slop_long) ? 3 : 1)), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:525:30");
                    done = 1;
                } else if (c == 10) {
                    offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:529:30");
                    line = SLOP_RANGE(int64_t, (line + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:530:28");
                    column = 1;
                } else {
                    offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:534:30");
                    column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:535:30");
                }
            }
        }
        if (done) {
            return ((slop_result_ttl_StringScan_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StringScan){.end = SLOP_RANGE(int64_t, end, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:538:16"), .escapes = SLOP_RANGE(int64_t, escapes, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:539:20"), .state = ((common_ParseState){.input = input, .offset = SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:540:63"), .line = SLOP_RANGE(int64_t, line, 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:540:77"), .column = SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:540:91")})}) });
        } else {
            return ((slop_result_ttl_StringScan_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_unterminated_string, ((slop_long) ? SLOP_STR("Unterminated triple-quoted string") : SLOP_STR("Unterminated string")), ((common_Position){.line = SLOP_RANGE(int64_t, line, 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:543:38"), .column = SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:543:52"), .offset = SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:543:68")})) });
        }
    }
}

slop_string ttl_decode_string_body(slop_arena* arena, slop_string input, int64_t start, int64_t end, int64_t escapes) {
    SLOP_PRE(((end >= start)), "(>= end start)");
    if (escapes == 0) {
        return strlib_substring(arena, input, start, SLOP_RANGE(int64_t, (end - start), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:551:36"));
    } else {
        {
            __auto_type out_len = ((end - start) - escapes);
            __auto_type buf = ({ __auto_type _alloc = (uint8_t*)slop_arena_alloc(arena, (out_len + 1)); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; });
            int64_t i = start;
            int64_t j = 0;
            while (i < end) {
                {
                    __auto_type c = strlib_char_at(input, SLOP_RANGE(int64_t, i, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:558:37"));
                    if (c == 92) {
                        buf[j] = ((uint8_t)(ttl_escape_value(strlib_char_at(input, SLOP_RANGE(int64_t, (i + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:562:75")))));
                        i = SLOP_RANGE(int64_t, (i + 2), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:563:29");
                    } else {
                        buf[j] = input.data[i];
                        i = SLOP_RANGE(int64_t, (i + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:566:29");
                    }
                    j = (j + 1);
                }
            }
            return (slop_string){.len = ((uint64_t)(out_len)), .data = ((uint8_t*)(buf))};
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
                    {
                        __auto_type v = ttl_escape_value(SLOP_RANGE(uint8_t, c, 1, 1, 0, 255, "(Int 0 .. 255) at ttl.slop:592:36"));
                        if (v == 0) {
                            return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = false, .data.err = common_make_parse_error(arena, common_ParseErrorKind_invalid_escape, SLOP_STR("Invalid escape sequence"), ((common_Position){.line = s1.line, .column = s1.column, .offset = s1.offset})) });
                        } else {
                            return ((slop_result_ttl_EscapeResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_EscapeResult){.slop_char = SLOP_RANGE(uint8_t, v, 1, 1, 0, 255, "(Int 0 .. 255) at ttl.slop:599:52"), .ctx = new_ctx}) });
                        }
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
        if ((offset < len) && ((strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:671:56")) == 43) || (strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:671:87")) == 45))) {
            offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:673:24");
            column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:674:24");
        }
        while ((offset < len) && strlib_is_digit(strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:676:59")))) {
            offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:678:24");
            column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:679:24");
        }
        if ((offset < len) && (strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:681:52")) == 46)) {
            has_dot = 1;
            offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:683:22");
            column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:684:22");
            while ((offset < len) && strlib_is_digit(strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:685:61")))) {
                offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:687:26");
                column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:688:26");
            }
        }
        if ((offset < len) && ((strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:690:56")) == 101) || (strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:690:88")) == 69))) {
            has_e = 1;
            offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:692:22");
            column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:693:22");
            if ((offset < len) && ((strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:694:58")) == 43) || (strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:694:89")) == 45))) {
                offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:696:26");
                column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:697:26");
            }
            while ((offset < len) && strlib_is_digit(strlib_char_at(input, SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:698:61")))) {
                offset = SLOP_RANGE(int64_t, (offset + 1), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:700:26");
                column = SLOP_RANGE(int64_t, (column + 1), 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:701:26");
            }
        }
        {
            __auto_type val = strlib_substring(arena, input, SLOP_RANGE(int64_t, start, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:702:41"), SLOP_RANGE(int64_t, (offset - start), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:702:47"));
            __auto_type dt = (has_e ? SLOP_STR("http://www.w3.org/2001/XMLSchema#double") : (has_dot ? SLOP_STR("http://www.w3.org/2001/XMLSchema#decimal") : SLOP_STR("http://www.w3.org/2001/XMLSchema#integer")));
            return ((slop_result_ttl_TermResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermResult){.term = rdf_make_literal(arena, val, (slop_option_string){.has_value = 1, .value = dt}, ((slop_option_string){.has_value = false})), .ctx = ((ttl_TtlParseContext){.prefixes = ctx.prefixes, .base_iri = ctx.base_iri, .blank_labels = ctx.blank_labels, .blank_counter = ctx.blank_counter, .state = ((common_ParseState){.input = input, .offset = SLOP_RANGE(int64_t, offset, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:716:23"), .line = ctx.state.line, .column = SLOP_RANGE(int64_t, column, 1, 0, 1, 0, "(Int 1 ..) at ttl.slop:718:23")})})}) });
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
                if ((c2 == 114) && ((c3 == 117) && ((c4 == 101) && !((strlib_is_alnum(SLOP_RANGE(strlib_Byte, c5, 1, 1, 0, 255, "Byte (Int 0 .. 255) at ttl.slop:778:38")) || ((c5 == 58) || ((c5 == 95) || (c5 == 45)))))))) {
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
                if ((c2 == 97) && ((c3 == 108) && ((c4 == 115) && ((c5 == 101) && !((strlib_is_alnum(SLOP_RANGE(strlib_Byte, c6, 1, 1, 0, 255, "Byte (Int 0 .. 255) at ttl.slop:791:38")) || ((c6 == 58) || ((c6 == 95) || (c6 == 45))))))))) {
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
        __auto_type triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
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
                        ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, cell_node, rdf_first, er.term)); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        __auto_type _mv_447 = prev_node;
                        if (_mv_447.has_value) {
                            __auto_type pn = _mv_447.value;
                            ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, pn, rdf_rest, cell_node)); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        } else if (!_mv_447.has_value) {
                            /* empty list */;
                        }
                        __auto_type _mv_448 = first_node;
                        if (_mv_448.has_value) {
                            __auto_type _ = _mv_448.value;
                            /* empty list */;
                        } else if (!_mv_448.has_value) {
                            first_node = (slop_option_rdf_Term){.has_value = 1, .value = cell_node};
                        }
                        prev_node = (slop_option_rdf_Term){.has_value = 1, .value = cell_node};
                        cur_ctx = ttl_ctx_with_state(gen.ctx, common_skip_whitespace(arena, gen.ctx.state));
                    }
                }
            }
        }
        __auto_type _mv_449 = prev_node;
        if (_mv_449.has_value) {
            __auto_type pn = _mv_449.value;
            ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, pn, rdf_rest, rdf_nil)); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        } else if (!_mv_449.has_value) {
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
        __auto_type extras = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
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
                return ((slop_result_ttl_TermTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TermTriplesResult){.term = tr.term, .extra_triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .ctx = tr.ctx}) });
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
        __auto_type triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
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
        __auto_type triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type polr = ({ __auto_type _tmp = ttl_parse_predicate_object_list(arena, ttl_ctx_with_state(gen.ctx, s1), reifier); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s2 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, polr.ctx.state), 124); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s3 = ({ __auto_type _tmp = common_expect_char(arena, s2, 125); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, reifier, reifies, rdf_make_triple_term(arena, base_triple))); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        triples = ttl_list_push_triples(arena, triples, polr.triples);
        return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_TriplesResult){.triples = triples, .ctx = ttl_ctx_with_state(polr.ctx, s3)}) });
    }
}

slop_result_ttl_TriplesResult_common_ParseError ttl_parse_object_list(slop_arena* arena, ttl_TtlParseContext ctx, rdf_Term subject, rdf_Term predicate) {
    {
        __auto_type triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type cur_ctx = ctx;
        uint8_t done = 0;
        while (!(done)) {
            {
                __auto_type s1 = common_skip_whitespace(arena, cur_ctx.state);
                __auto_type objr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ttl_ctx_with_state(cur_ctx, s1)); if (!_tmp.is_ok) return ((slop_result_ttl_TriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                triples = ttl_list_push_triples(arena, triples, objr.extra_triples);
                ({ __auto_type _lst_p = &(triples); __auto_type _item = (rdf_make_triple(arena, subject, predicate, objr.term)); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
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
        return SLOP_RANGE(int64_t, count, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:1117:7");
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
        return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StreamTriplesResult){.count = SLOP_RANGE(int64_t, count, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:1150:50"), .ctx = cur_ctx}) });
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
        return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StreamTriplesResult){.count = SLOP_RANGE(int64_t, count, 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:1177:50"), .ctx = cur_ctx}) });
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

void ttl_scratch_reset(slop_arena* scratch) {
    slop_arena_reset(scratch);;
}

slop_result_ttl_TtlParseContext_common_ParseError ttl_parse_directive_any(slop_arena* arena, ttl_TtlParseContext ctx) {
    if (common_state_peek(ctx.state) == 64) {
        return ttl_parse_directive(arena, ctx);
    } else {
        return ttl_parse_sparql_prefix(arena, ctx);
    }
}

slop_result_ttl_StreamTriplesResult_common_ParseError ttl_parse_statement_for_each_triple(slop_arena* arena, ttl_TtlParseContext ctx, slop_closure_t callback) {
    {
        __auto_type sr = ({ __auto_type _tmp = ttl_parse_term_extended(arena, ctx); if (!_tmp.is_ok) return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type n_extra = ttl_emit_triples(sr.extra_triples, callback);
        __auto_type polr = ({ __auto_type _tmp = ttl_parse_predicate_object_list_for_each_triple(arena, sr.ctx, sr.term, callback); if (!_tmp.is_ok) return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        __auto_type s5 = ({ __auto_type _tmp = common_expect_char(arena, common_skip_whitespace(arena, polr.ctx.state), 46); if (!_tmp.is_ok) return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
        return ((slop_result_ttl_StreamTriplesResult_common_ParseError){ .is_ok = true, .data.ok = ((ttl_StreamTriplesResult){.count = SLOP_RANGE(int64_t, (n_extra + polr.count), 1, 0, 0, 0, "(Int 0 ..) at ttl.slop:1241:16"), .ctx = ttl_ctx_with_state(polr.ctx, s5)}) });
    }
}

slop_result_int_common_ParseError ttl_parse_ttl_string_for_each_triple(slop_arena* arena, slop_string input, slop_closure_t callback) {
    SLOP_PRE(((string_len(input) > 0)), "(> (string-len input) 0)");
    {
        __auto_type scratch = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type ctx = ttl_make_ttl_context(arena, input);
        int64_t count = 0;
        ctx = ttl_ctx_with_state(ctx, common_skip_whitespace(arena, ctx.state));
        while (!(common_state_at_end(ctx.state))) {
            {
                __auto_type c = common_state_peek(ctx.state);
                if ((c == 64) || ((c == 80) || (c == 66))) {
                    __auto_type _mv_450 = ttl_parse_directive_any(arena, ctx);
                    if (_mv_450.is_ok) {
                        __auto_type next = _mv_450.data.ok;
                        ctx = next;
                    } else if (!_mv_450.is_ok) {
                        __auto_type e = _mv_450.data.err;
                        ({ slop_arena_free(scratch); free(scratch); });
                        return ((slop_result_int_common_ParseError){ .is_ok = false, .data.err = e });
                    }
                } else {
                    __auto_type _mv_451 = ttl_parse_statement_for_each_triple(scratch, ctx, callback);
                    if (_mv_451.is_ok) {
                        __auto_type r = _mv_451.data.ok;
                        count = (count + r.count);
                        ctx = r.ctx;
                        ttl_scratch_reset(scratch);
                    } else if (!_mv_451.is_ok) {
                        __auto_type e = _mv_451.data.err;
                        ({ slop_arena_free(scratch); free(scratch); });
                        return ((slop_result_int_common_ParseError){ .is_ok = false, .data.err = e });
                    }
                }
            }
            ctx = ttl_ctx_with_state(ctx, common_skip_whitespace(arena, ctx.state));
        }
        ({ slop_arena_free(scratch); free(scratch); });
        return ((slop_result_int_common_ParseError){ .is_ok = true, .data.ok = count });
    }
}

slop_result_rdf_Graph_ttl_TtlFileError ttl_parse_ttl_file(slop_arena* arena, slop_string path) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type f = file_file_open(path, file_FileMode_read);
        __auto_type _mv_452 = f;
        if (_mv_452.is_ok) {
            __auto_type handle = _mv_452.data.ok;
            {
                __auto_type content = file_file_read_all(arena, (&handle));
                __auto_type _mv_453 = content;
                if (_mv_453.is_ok) {
                    __auto_type text = _mv_453.data.ok;
                    file_file_close((&handle));
                    __auto_type _mv_454 = ttl_parse_ttl_string(arena, text);
                    if (_mv_454.is_ok) {
                        __auto_type g = _mv_454.data.ok;
                        return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = true, .data.ok = g });
                    } else if (!_mv_454.is_ok) {
                        __auto_type e = _mv_454.data.err;
                        return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_parse_error, .data.parse_error = e }) });
                    }
                    SLOP_UNREACHABLE();
                } else if (!_mv_453.is_ok) {
                    __auto_type e = _mv_453.data.err;
                    file_file_close((&handle));
                    return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
                }
                SLOP_UNREACHABLE();
            }
        } else if (!_mv_452.is_ok) {
            __auto_type e = _mv_452.data.err;
            return ((slop_result_rdf_Graph_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
        }
        SLOP_UNREACHABLE();
    }
}

slop_result_int_ttl_TtlFileError ttl_parse_ttl_file_for_each_triple(slop_arena* arena, slop_string path, slop_closure_t callback) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type f = file_file_open(path, file_FileMode_read);
        __auto_type _mv_455 = f;
        if (_mv_455.is_ok) {
            __auto_type handle = _mv_455.data.ok;
            {
                __auto_type content = file_file_read_all(arena, (&handle));
                __auto_type _mv_456 = content;
                if (_mv_456.is_ok) {
                    __auto_type text = _mv_456.data.ok;
                    file_file_close((&handle));
                    __auto_type _mv_457 = ttl_parse_ttl_string_for_each_triple(arena, text, callback);
                    if (_mv_457.is_ok) {
                        __auto_type count = _mv_457.data.ok;
                        return ((slop_result_int_ttl_TtlFileError){ .is_ok = true, .data.ok = count });
                    } else if (!_mv_457.is_ok) {
                        __auto_type e = _mv_457.data.err;
                        return ((slop_result_int_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_parse_error, .data.parse_error = e }) });
                    }
                    SLOP_UNREACHABLE();
                } else if (!_mv_456.is_ok) {
                    __auto_type e = _mv_456.data.err;
                    file_file_close((&handle));
                    return ((slop_result_int_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
                }
                SLOP_UNREACHABLE();
            }
        } else if (!_mv_455.is_ok) {
            __auto_type e = _mv_455.data.err;
            return ((slop_result_int_ttl_TtlFileError){ .is_ok = false, .data.err = ((ttl_TtlFileError){ .tag = ttl_TtlFileError_file_error, .data.file_error = e }) });
        }
        SLOP_UNREACHABLE();
    }
}

uint8_t ttl_is_pn_chars_base(uint8_t c) {
    return strlib_is_alpha(c);
}

uint8_t ttl_is_pn_chars(uint8_t c) {
    return (ttl_is_pn_chars_base(c) || (strlib_is_digit(c) || ((c == 95) || (c == 45))));
}

