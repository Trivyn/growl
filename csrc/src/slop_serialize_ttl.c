#include "../runtime/slop_runtime.h"
#include "slop_serialize_ttl.h"

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

slop_string serialize_ttl_escape_string_char(slop_arena* arena, uint8_t c) {
    if ((c == 10)) {
        return SLOP_STR("\\n");
    } else if ((c == 13)) {
        return SLOP_STR("\\r");
    } else if ((c == 9)) {
        return SLOP_STR("\\t");
    } else if ((c == 92)) {
        return SLOP_STR("\\\\");
    } else if ((c == 34)) {
        return SLOP_STR("\\\"");
    } else {
        return slop_string_push_char(arena, SLOP_STR(""), c);
    }
}

uint8_t serialize_ttl_needs_escaping(slop_string s) {
    {
        __auto_type len = string_len(s);
        uint8_t found = 0;
        int64_t i = 0;
        while (((i < len) && !(found))) {
            {
                __auto_type c = strlib_char_at(s, i);
                if (((c == 10) || ((c == 13) || ((c == 9) || ((c == 92) || (c == 34)))))) {
                    found = 1;
                }
                i = (i + 1);
            }
        }
        return found;
    }
}

slop_string serialize_ttl_escape_string(slop_arena* arena, slop_string s) {
    slop_string _retval;
    if (!(serialize_ttl_needs_escaping(s))) {
        _retval = s;
    } else {
        {
            __auto_type len = string_len(s);
            __auto_type result = SLOP_STR("");
            {
                int64_t i = 0;
                while ((i < len)) {
                    {
                        __auto_type c = strlib_char_at(s, i);
                        result = string_concat(arena, result, serialize_ttl_escape_string_char(arena, c));
                        i = (i + 1);
                    }
                }
            }
            _retval = result;
        }
    }
    SLOP_POST(((string_len(_retval) >= 0)), "(>= (string-len $result) 0)");
    return _retval;
}

uint8_t serialize_ttl_string_contains_newline(slop_string s) {
    {
        __auto_type len = string_len(s);
        uint8_t found = 0;
        int64_t i = 0;
        while (((i < len) && !(found))) {
            {
                __auto_type c = strlib_char_at(s, i);
                if (((c == 10) || (c == 13))) {
                    found = 1;
                }
                i = (i + 1);
            }
        }
        return found;
    }
}

uint8_t serialize_ttl_valid_pn_local(slop_string s) {
    {
        __auto_type len = string_len(s);
        if ((len == 0)) {
            return 1;
        } else {
            {
                uint8_t ok = 1;
                int64_t i = 0;
                while (((i < len) && ok)) {
                    {
                        __auto_type c = strlib_char_at(s, i);
                        if (!(ttl_is_pn_chars(c))) {
                            ok = 0;
                        }
                        i = (i + 1);
                    }
                }
                return ok;
            }
        }
    }
}

slop_string serialize_ttl_serialize_iri(slop_arena* arena, rdf_IRI iri, ttl_PrefixMap prefixes) {
    SLOP_PRE(((string_len(iri.value) > 0)), "(> (string-len iri.value) 0)");
    slop_string _retval;
    {
        __auto_type iri_val = iri.value;
        slop_option_string compressed = (slop_option_string){.has_value = false};
        {
            __auto_type _coll = prefixes.bindings;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type b = _coll.data[_i];
                __auto_type _mv_312 = compressed;
                if (_mv_312.has_value) {
                    __auto_type _ = _mv_312.value;
                } else if (!_mv_312.has_value) {
                    {
                        __auto_type prefix_iri = b.iri;
                        if (strlib_starts_with(iri_val, prefix_iri)) {
                            {
                                __auto_type local = strlib_substring(arena, iri_val, string_len(prefix_iri), (string_len(iri_val) - string_len(prefix_iri)));
                                if (serialize_ttl_valid_pn_local(local)) {
                                    compressed = (slop_option_string){.has_value = 1, .value = string_concat(arena, string_concat(arena, b.prefix, SLOP_STR(":")), local)};
                                }
                            }
                        }
                    }
                }
            }
        }
        __auto_type _mv_313 = compressed;
        if (_mv_313.has_value) {
            __auto_type s = _mv_313.value;
            return s;
        } else if (!_mv_313.has_value) {
            return string_concat(arena, string_concat(arena, SLOP_STR("<"), iri_val), SLOP_STR(">"));
        }
    }
    SLOP_POST(((string_len(_retval) > 0)), "(> (string-len $result) 0)");
    return _retval;
}

slop_string serialize_ttl_serialize_literal(slop_arena* arena, rdf_Literal lit) {
    slop_string _retval;
    {
        __auto_type val = lit.value;
        __auto_type dt = lit.datatype;
        __auto_type lang = lit.lang;
        __auto_type _mv_314 = lang;
        if (_mv_314.has_value) {
            __auto_type l = _mv_314.value;
            return string_concat(arena, string_concat(arena, string_concat(arena, SLOP_STR("\""), serialize_ttl_escape_string(arena, val)), SLOP_STR("\"@")), l);
        } else if (!_mv_314.has_value) {
            __auto_type _mv_315 = dt;
            if (_mv_315.has_value) {
                __auto_type dt_iri = _mv_315.value;
                if (string_eq(dt_iri, vocab_XSD_INTEGER)) {
                    return val;
                } else if (string_eq(dt_iri, vocab_XSD_DECIMAL)) {
                    return val;
                } else if (string_eq(dt_iri, vocab_XSD_DOUBLE)) {
                    return val;
                } else if (string_eq(dt_iri, vocab_XSD_BOOLEAN)) {
                    return val;
                } else if (string_eq(dt_iri, vocab_XSD_STRING)) {
                    if (serialize_ttl_string_contains_newline(val)) {
                        return string_concat(arena, string_concat(arena, SLOP_STR("\"\"\""), serialize_ttl_escape_string(arena, val)), SLOP_STR("\"\"\""));
                    } else {
                        return string_concat(arena, string_concat(arena, SLOP_STR("\""), serialize_ttl_escape_string(arena, val)), SLOP_STR("\""));
                    }
                } else {
                    return string_concat(arena, string_concat(arena, string_concat(arena, string_concat(arena, SLOP_STR("\""), serialize_ttl_escape_string(arena, val)), SLOP_STR("\"^^<")), dt_iri), SLOP_STR(">"));
                }
            } else if (!_mv_315.has_value) {
                if (serialize_ttl_string_contains_newline(val)) {
                    return string_concat(arena, string_concat(arena, SLOP_STR("\"\"\""), serialize_ttl_escape_string(arena, val)), SLOP_STR("\"\"\""));
                } else {
                    return string_concat(arena, string_concat(arena, SLOP_STR("\""), serialize_ttl_escape_string(arena, val)), SLOP_STR("\""));
                }
            }
        }
    }
    SLOP_POST(((string_len(_retval) > 0)), "(> (string-len $result) 0)");
    return _retval;
}

slop_string serialize_ttl_serialize_blank(slop_arena* arena, rdf_BlankNode node) {
    SLOP_PRE(((node.id >= 0)), "(>= node.id 0)");
    slop_string _retval;
    _retval = string_concat(arena, SLOP_STR("_:b"), int_to_string(arena, node.id));
    SLOP_POST((strlib_starts_with(_retval, SLOP_STR("_:"))), "(starts-with $result \"_:\")");
    return _retval;
}

slop_string serialize_ttl_serialize_term(slop_arena* arena, rdf_Term t, ttl_PrefixMap prefixes) {
    slop_string _retval;
    __auto_type _mv_316 = t;
    switch (_mv_316.tag) {
        case rdf_Term_term_iri:
        {
            __auto_type iri = _mv_316.data.term_iri;
            return serialize_ttl_serialize_iri(arena, iri, prefixes);
        }
        case rdf_Term_term_blank:
        {
            __auto_type node = _mv_316.data.term_blank;
            return serialize_ttl_serialize_blank(arena, node);
        }
        case rdf_Term_term_literal:
        {
            __auto_type lit = _mv_316.data.term_literal;
            return serialize_ttl_serialize_literal(arena, lit);
        }
    }
    SLOP_POST(((string_len(_retval) > 0)), "(> (string-len $result) 0)");
    return _retval;
}

slop_string serialize_ttl_serialize_prefixes(slop_arena* arena, ttl_PrefixMap prefixes) {
    slop_string _retval;
    {
        __auto_type result = SLOP_STR("");
        {
            __auto_type _coll = prefixes.bindings;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type b = _coll.data[_i];
                result = string_concat(arena, result, string_concat(arena, string_concat(arena, string_concat(arena, SLOP_STR("@prefix "), b.prefix), SLOP_STR(": <")), string_concat(arena, b.iri, SLOP_STR("> .\n"))));
            }
        }
        _retval = result;
    }
    SLOP_POST(((string_len(_retval) >= 0)), "(>= (string-len $result) 0)");
    return _retval;
}

slop_string serialize_ttl_serialize_base(slop_arena* arena, slop_option_string base) {
    __auto_type _mv_317 = base;
    if (_mv_317.has_value) {
        __auto_type iri = _mv_317.value;
        return string_concat(arena, string_concat(arena, SLOP_STR("@base <"), iri), SLOP_STR("> .\n"));
    } else if (!_mv_317.has_value) {
        return SLOP_STR("");
    }
}

slop_string serialize_ttl_make_indent(slop_arena* arena, int64_t width) {
    {
        __auto_type result = SLOP_STR("");
        int64_t i = 0;
        while ((i < width)) {
            result = string_concat(arena, result, SLOP_STR(" "));
            i = (i + 1);
        }
        return result;
    }
}

slop_option_int serialize_ttl_find_subject_group(slop_list_serialize_ttl_SubjectGroup groups, rdf_Term subj) {
    {
        slop_option_int found = (slop_option_int){.has_value = false};
        int64_t i = 0;
        {
            __auto_type _coll = groups;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type sg = _coll.data[_i];
                __auto_type _mv_318 = found;
                if (_mv_318.has_value) {
                    __auto_type _ = _mv_318.value;
                } else if (!_mv_318.has_value) {
                    if (rdf_term_eq(sg.subject, subj)) {
                        found = (slop_option_int){.has_value = 1, .value = i};
                    }
                }
                i = (i + 1);
            }
        }
        return found;
    }
}

slop_option_int serialize_ttl_find_pred_group(slop_list_serialize_ttl_ObjectGroup groups, rdf_Term pred) {
    {
        slop_option_int found = (slop_option_int){.has_value = false};
        int64_t i = 0;
        {
            __auto_type _coll = groups;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type og = _coll.data[_i];
                __auto_type _mv_319 = found;
                if (_mv_319.has_value) {
                    __auto_type _ = _mv_319.value;
                } else if (!_mv_319.has_value) {
                    if (rdf_term_eq(og.predicate, pred)) {
                        found = (slop_option_int){.has_value = 1, .value = i};
                    }
                }
                i = (i + 1);
            }
        }
        return found;
    }
}

slop_list_serialize_ttl_SubjectGroup serialize_ttl_build_groups(slop_arena* arena, rdf_Graph g) {
    {
        __auto_type groups = ((slop_list_serialize_ttl_SubjectGroup){ .data = (serialize_ttl_SubjectGroup*)slop_arena_alloc(arena, 16 * sizeof(serialize_ttl_SubjectGroup)), .len = 0, .cap = 16 });
        {
            __auto_type _coll = g.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type triple = _coll.data[_i];
                {
                    __auto_type subj = triple.subject;
                    __auto_type pred = triple.predicate;
                    __auto_type obj = triple.object;
                    {
                        __auto_type sg_idx = serialize_ttl_find_subject_group(groups, subj);
                        __auto_type _mv_320 = sg_idx;
                        if (_mv_320.has_value) {
                            __auto_type idx = _mv_320.value;
                            __auto_type _mv_321 = ({ __auto_type _lst = groups; size_t _idx = (size_t)idx; slop_option_serialize_ttl_SubjectGroup _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_321.has_value) {
                                __auto_type sg = _mv_321.value;
                                {
                                    __auto_type pg_idx = serialize_ttl_find_pred_group(sg.pred_groups, pred);
                                    __auto_type _mv_322 = pg_idx;
                                    if (_mv_322.has_value) {
                                        __auto_type pidx = _mv_322.value;
                                        __auto_type _mv_323 = ({ __auto_type _lst = sg.pred_groups; size_t _idx = (size_t)pidx; slop_option_serialize_ttl_ObjectGroup _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                        if (_mv_323.has_value) {
                                            __auto_type pg = _mv_323.value;
                                            ({ __auto_type _lst_p = &(pg.objects); __auto_type _item = (obj); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                        } else if (!_mv_323.has_value) {
                                        }
                                    } else if (!_mv_322.has_value) {
                                        {
                                            __auto_type new_pg = ((serialize_ttl_ObjectGroup){.predicate = pred, .objects = ({ ({ __auto_type ol = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 }); ({ __auto_type _lst_p = &(ol); __auto_type _item = (obj); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); ol; }); })});
                                            ({ __auto_type _lst_p = &(sg.pred_groups); __auto_type _item = (new_pg); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                        }
                                    }
                                }
                            } else if (!_mv_321.has_value) {
                            }
                        } else if (!_mv_320.has_value) {
                            {
                                __auto_type new_pg = ((serialize_ttl_ObjectGroup){.predicate = pred, .objects = ({ ({ __auto_type ol = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 }); ({ __auto_type _lst_p = &(ol); __auto_type _item = (obj); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); ol; }); })});
                                {
                                    __auto_type new_sg = ((serialize_ttl_SubjectGroup){.subject = subj, .pred_groups = ({ ({ __auto_type pl = ((slop_list_serialize_ttl_ObjectGroup){ .data = (serialize_ttl_ObjectGroup*)slop_arena_alloc(arena, 16 * sizeof(serialize_ttl_ObjectGroup)), .len = 0, .cap = 16 }); ({ __auto_type _lst_p = &(pl); __auto_type _item = (new_pg); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); pl; }); })});
                                    ({ __auto_type _lst_p = &(groups); __auto_type _item = (new_sg); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                }
                            }
                        }
                    }
                }
            }
        }
        return groups;
    }
}

slop_string serialize_ttl_serialize_ttl_string(slop_arena* arena, rdf_Graph g, serialize_ttl_SerializeConfig config) {
    slop_string _retval;
    {
        __auto_type prefixes = config.prefixes;
        __auto_type base = config.base_iri;
        __auto_type indent = serialize_ttl_make_indent(arena, config.indent_width);
        {
            __auto_type result = SLOP_STR("");
            result = string_concat(arena, result, serialize_ttl_serialize_base(arena, base));
            {
                __auto_type prefix_str = serialize_ttl_serialize_prefixes(arena, prefixes);
                if ((string_len(prefix_str) > 0)) {
                    result = string_concat(arena, result, prefix_str);
                    result = string_concat(arena, result, SLOP_STR("\n"));
                }
            }
            {
                __auto_type prev_subj = SLOP_STR("");
                __auto_type prev_pred = SLOP_STR("");
                uint8_t first_triple = 1;
                {
                    __auto_type _coll = g.triples;
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type triple = _coll.data[_i];
                        {
                            __auto_type subj_str = serialize_ttl_serialize_term(arena, triple.subject, prefixes);
                            __auto_type pred_str = serialize_ttl_serialize_term(arena, triple.predicate, prefixes);
                            __auto_type obj_str = serialize_ttl_serialize_term(arena, triple.object, prefixes);
                            if (first_triple) {
                                result = string_concat(arena, result, subj_str);
                                result = string_concat(arena, result, SLOP_STR(" "));
                                result = string_concat(arena, result, pred_str);
                                result = string_concat(arena, result, SLOP_STR(" "));
                                result = string_concat(arena, result, obj_str);
                                first_triple = 0;
                            } else if ((string_eq(subj_str, prev_subj) && string_eq(pred_str, prev_pred))) {
                                result = string_concat(arena, result, SLOP_STR(", "));
                                result = string_concat(arena, result, obj_str);
                            } else if (string_eq(subj_str, prev_subj)) {
                                result = string_concat(arena, result, SLOP_STR(" ;\n"));
                                result = string_concat(arena, result, indent);
                                result = string_concat(arena, result, pred_str);
                                result = string_concat(arena, result, SLOP_STR(" "));
                                result = string_concat(arena, result, obj_str);
                            } else {
                                result = string_concat(arena, result, SLOP_STR(" .\n"));
                                result = string_concat(arena, result, subj_str);
                                result = string_concat(arena, result, SLOP_STR(" "));
                                result = string_concat(arena, result, pred_str);
                                result = string_concat(arena, result, SLOP_STR(" "));
                                result = string_concat(arena, result, obj_str);
                            }
                            prev_subj = subj_str;
                            prev_pred = pred_str;
                        }
                    }
                }
                if (!(first_triple)) {
                    result = string_concat(arena, result, SLOP_STR(" .\n"));
                }
            }
            _retval = result;
        }
    }
    SLOP_POST(((string_len(_retval) >= 0)), "(>= (string-len $result) 0)");
    return _retval;
}

slop_result_u8_serialize_ttl_TtlFileError serialize_ttl_serialize_ttl_file(slop_arena* arena, rdf_Graph g, serialize_ttl_SerializeConfig config, slop_string path) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type content = serialize_ttl_serialize_ttl_string(arena, g, config);
        {
            __auto_type f = file_file_open(path, file_FileMode_write);
            __auto_type _mv_324 = f;
            if (_mv_324.is_ok) {
                __auto_type handle = _mv_324.data.ok;
                file_file_write_line((&handle), content);
                file_file_close((&handle));
                return ((slop_result_u8_serialize_ttl_TtlFileError){ .is_ok = true, .data.ok = 1 });
            } else if (!_mv_324.is_ok) {
                __auto_type e = _mv_324.data.err;
                return ((slop_result_u8_serialize_ttl_TtlFileError){ .is_ok = false, .data.err = ((serialize_ttl_TtlFileError){ .tag = serialize_ttl_TtlFileError_file_error, .data.file_error = e }) });
            }
        }
    }
}

void serialize_ttl_emit_str(void* handle, slop_string s) {
    fwrite(((void*)(s.data)), ((uint64_t)(1)), ((uint64_t)(s.len)), handle);
}

slop_result_u8_serialize_ttl_TtlFileError serialize_ttl_serialize_ttl_stream(slop_arena* arena, rdf_Graph g, serialize_ttl_SerializeConfig config, slop_string path) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type f = file_file_open(path, file_FileMode_write);
        __auto_type _mv_325 = f;
        if (_mv_325.is_ok) {
            __auto_type handle = _mv_325.data.ok;
            {
                __auto_type fp = ((void*)(handle.handle));
                __auto_type prefixes = config.prefixes;
                __auto_type base = config.base_iri;
                __auto_type indent = serialize_ttl_make_indent(arena, config.indent_width);
                {
                    __auto_type base_str = serialize_ttl_serialize_base(arena, base);
                    if ((string_len(base_str) > 0)) {
                        serialize_ttl_emit_str(fp, base_str);
                    }
                }
                {
                    __auto_type prefix_str = serialize_ttl_serialize_prefixes(arena, prefixes);
                    if ((string_len(prefix_str) > 0)) {
                        serialize_ttl_emit_str(fp, prefix_str);
                        serialize_ttl_emit_str(fp, SLOP_STR("\n"));
                    }
                }
                {
                    rdf_Term prev_subj = rdf_make_blank(arena, 2147483647);
                    rdf_Term prev_pred = rdf_make_blank(arena, 2147483647);
                    __auto_type first_triple = 1;
                    {
                        __auto_type _coll = g.triples;
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type triple = _coll.data[_i];
                            {
                                slop_arena _arena = slop_arena_new(4096);
                                slop_arena* arena = &_arena;
                                {
                                    __auto_type subj_str = serialize_ttl_serialize_term(arena, triple.subject, prefixes);
                                    __auto_type pred_str = serialize_ttl_serialize_term(arena, triple.predicate, prefixes);
                                    __auto_type obj_str = serialize_ttl_serialize_term(arena, triple.object, prefixes);
                                    if (first_triple) {
                                        serialize_ttl_emit_str(fp, subj_str);
                                        serialize_ttl_emit_str(fp, SLOP_STR(" "));
                                        serialize_ttl_emit_str(fp, pred_str);
                                        serialize_ttl_emit_str(fp, SLOP_STR(" "));
                                        serialize_ttl_emit_str(fp, obj_str);
                                        first_triple = 0;
                                    } else if ((rdf_term_eq(triple.subject, prev_subj) && rdf_term_eq(triple.predicate, prev_pred))) {
                                        serialize_ttl_emit_str(fp, SLOP_STR(", "));
                                        serialize_ttl_emit_str(fp, obj_str);
                                    } else if (rdf_term_eq(triple.subject, prev_subj)) {
                                        serialize_ttl_emit_str(fp, SLOP_STR(" ;\n"));
                                        serialize_ttl_emit_str(fp, indent);
                                        serialize_ttl_emit_str(fp, pred_str);
                                        serialize_ttl_emit_str(fp, SLOP_STR(" "));
                                        serialize_ttl_emit_str(fp, obj_str);
                                    } else {
                                        serialize_ttl_emit_str(fp, SLOP_STR(" .\n"));
                                        serialize_ttl_emit_str(fp, subj_str);
                                        serialize_ttl_emit_str(fp, SLOP_STR(" "));
                                        serialize_ttl_emit_str(fp, pred_str);
                                        serialize_ttl_emit_str(fp, SLOP_STR(" "));
                                        serialize_ttl_emit_str(fp, obj_str);
                                    }
                                }
                                slop_arena_free(arena);
                            }
                            prev_subj = triple.subject;
                            prev_pred = triple.predicate;
                        }
                    }
                    if (!(first_triple)) {
                        serialize_ttl_emit_str(fp, SLOP_STR(" .\n"));
                    }
                }
                file_file_close((&handle));
                return ((slop_result_u8_serialize_ttl_TtlFileError){ .is_ok = true, .data.ok = 1 });
            }
        } else if (!_mv_325.is_ok) {
            __auto_type e = _mv_325.data.err;
            return ((slop_result_u8_serialize_ttl_TtlFileError){ .is_ok = false, .data.err = ((serialize_ttl_TtlFileError){ .tag = serialize_ttl_TtlFileError_file_error, .data.file_error = e }) });
        }
    }
}

