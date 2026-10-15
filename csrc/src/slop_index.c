#include "../runtime/slop_runtime.h"
#include "slop_index.h"

slop_rdf_index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena);
slop_rdf_index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t);
uint8_t rdf_indexed_graph_contains(slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t);
slop_list_slop_rdf_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj);
void rdf_indexed_graph_for_each(slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj, slop_closure_t callback);
int64_t rdf_indexed_graph_size(slop_rdf_index_IndexedGraph g);
slop_list_slop_rdf_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term pred, slop_rdf_rdf_Term obj);
slop_list_slop_rdf_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term subj, slop_rdf_rdf_Term pred);

slop_rdf_index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena) {
    slop_rdf_index_IndexedGraph _retval = {0};
    _retval = ((slop_rdf_index_IndexedGraph){.triples = ((slop_list_slop_rdf_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .index = ((slop_rdf_index_TripleIndex){.spo = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); }), .pso = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); }), .osp = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); }), .pos = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); })}), .size = 0});
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval.size == 0)), "(== (. $result size) 0)");
    return _retval;
}

slop_rdf_index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_rdf_index_IndexedGraph _retval = {0};
    if (rdf_indexed_graph_contains(g, t)) {
        _retval = g;
        goto _slop_post;
    }
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type o = rdf_triple_object(t);
        (void)(({ __auto_type _lst_p = &(g.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        {
            __auto_type spo_idx = g.index.spo;
            __auto_type _mv_13 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_13.has_value) {
                __auto_type pred_map = _mv_13.value;
                __auto_type _mv_15 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_15.has_value) {
                    __auto_type obj_set = _mv_15.value;
                    ({ slop_map_put(NULL, obj_set, &(o), NULL, 0); });
                } else if (!_mv_15.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, pred_map, &(p), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_13.has_value) {
                {
                    __auto_type pred_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, pred_map, &(p), &_val, sizeof(_val)); });
                    ({ slop_map* _val = pred_map; slop_map_put(NULL, spo_idx, &(s), &_val, sizeof(_val)); });
                }
            }
        }
        {
            __auto_type pso_idx = g.index.pso;
            __auto_type _mv_23 = ({ void* _ptr = slop_map_get(pso_idx, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_23.has_value) {
                __auto_type subj_map = _mv_23.value;
                __auto_type _mv_25 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_25.has_value) {
                    __auto_type obj_set = _mv_25.value;
                    ({ slop_map_put(NULL, obj_set, &(o), NULL, 0); });
                } else if (!_mv_25.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_23.has_value) {
                {
                    __auto_type subj_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    ({ slop_map* _val = subj_map; slop_map_put(NULL, pso_idx, &(p), &_val, sizeof(_val)); });
                }
            }
        }
        {
            __auto_type osp_idx = g.index.osp;
            __auto_type _mv_33 = ({ void* _ptr = slop_map_get(osp_idx, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_33.has_value) {
                __auto_type subj_map = _mv_33.value;
                __auto_type _mv_35 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_35.has_value) {
                    __auto_type pred_set = _mv_35.value;
                    ({ slop_map_put(NULL, pred_set, &(p), NULL, 0); });
                } else if (!_mv_35.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(p), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_33.has_value) {
                {
                    __auto_type subj_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(p), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    ({ slop_map* _val = subj_map; slop_map_put(NULL, osp_idx, &(o), &_val, sizeof(_val)); });
                }
            }
        }
        {
            __auto_type pos_idx = g.index.pos;
            __auto_type _mv_43 = ({ void* _ptr = slop_map_get(pos_idx, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_43.has_value) {
                __auto_type obj_map = _mv_43.value;
                __auto_type _mv_45 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_45.has_value) {
                    __auto_type subj_set = _mv_45.value;
                    ({ slop_map_put(NULL, subj_set, &(s), NULL, 0); });
                } else if (!_mv_45.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(s), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, obj_map, &(o), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_43.has_value) {
                {
                    __auto_type obj_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(s), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, obj_map, &(o), &_val, sizeof(_val)); });
                    ({ slop_map* _val = obj_map; slop_map_put(NULL, pos_idx, &(p), &_val, sizeof(_val)); });
                }
            }
        }
        _retval = ((slop_rdf_index_IndexedGraph){.triples = g.triples, .index = g.index, .size = (g.size + 1)});
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST(((_retval.size >= g.size)), "(>= (. $result size) (. g size))");
    return _retval;
}

uint8_t rdf_indexed_graph_contains(slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    uint8_t _retval = {0};
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type o = rdf_triple_object(t);
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_53 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_53.has_value) {
            __auto_type pred_map = _mv_53.value;
            __auto_type _mv_55 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_55.has_value) {
                __auto_type obj_set = _mv_55.value;
                _retval = slop_map_has(obj_set, &(o));
                goto _slop_post;
            } else if (!_mv_55.has_value) {
                _retval = 0;
                goto _slop_post;
            }
            SLOP_UNREACHABLE();
        } else if (!_mv_53.has_value) {
            _retval = 0;
            goto _slop_post;
        }
        SLOP_UNREACHABLE();
    }
    _slop_post: ;
    return _retval;
}

slop_list_slop_rdf_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_list_slop_rdf_rdf_Triple _retval = {0};
    {
        __auto_type result = ((slop_list_slop_rdf_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type _mv_57 = subj;
        if (_mv_57.has_value) {
            __auto_type s = _mv_57.value;
            __auto_type _mv_59 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_59.has_value) {
                __auto_type pred_map = _mv_59.value;
                __auto_type _mv_60 = pred;
                if (_mv_60.has_value) {
                    __auto_type p = _mv_60.value;
                    __auto_type _mv_62 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_62.has_value) {
                        __auto_type term_set = _mv_62.value;
                        __auto_type _mv_63 = obj;
                        if (_mv_63.has_value) {
                            __auto_type o = _mv_63.value;
                            if (slop_map_has(term_set, &(o))) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        } else if (!_mv_63.has_value) {
                            {
                                slop_map* _coll = (slop_map*)term_set;
                                for (size_t _i = 0; _i < _coll->len; _i++) {
                                    {
                                        slop_rdf_rdf_Term o = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    } else if (!_mv_62.has_value) {
                    }
                } else if (!_mv_60.has_value) {
                    {
                        slop_map* _coll = (slop_map*)pred_map;
                        for (size_t _i = 0; _i < _coll->len; _i++) {
                            {
                                slop_rdf_rdf_Term p = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                slop_rdf_index_TermSet term_set = *(slop_rdf_index_TermSet*)slop_map_value_at(_coll, _i);
                                __auto_type _mv_65 = obj;
                                if (_mv_65.has_value) {
                                    __auto_type o = _mv_65.value;
                                    if (slop_map_has(term_set, &(o))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                } else if (!_mv_65.has_value) {
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->len; _i++) {
                                            {
                                                slop_rdf_rdf_Term o = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (!_mv_59.has_value) {
            }
        } else if (!_mv_57.has_value) {
            __auto_type _mv_67 = pred;
            if (_mv_67.has_value) {
                __auto_type p = _mv_67.value;
                __auto_type _mv_68 = obj;
                if (_mv_68.has_value) {
                    __auto_type o = _mv_68.value;
                    __auto_type _mv_70 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_70.has_value) {
                        __auto_type obj_map = _mv_70.value;
                        __auto_type _mv_72 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                        if (_mv_72.has_value) {
                            __auto_type subj_set = _mv_72.value;
                            {
                                slop_map* _coll = (slop_map*)subj_set;
                                for (size_t _i = 0; _i < _coll->len; _i++) {
                                    {
                                        slop_rdf_rdf_Term s = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        } else if (!_mv_72.has_value) {
                        }
                    } else if (!_mv_70.has_value) {
                    }
                } else if (!_mv_68.has_value) {
                    __auto_type _mv_74 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_74.has_value) {
                        __auto_type subj_map = _mv_74.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    slop_rdf_rdf_Term s = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                    slop_rdf_index_TermSet term_set = *(slop_rdf_index_TermSet*)slop_map_value_at(_coll, _i);
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->len; _i++) {
                                            {
                                                slop_rdf_rdf_Term o = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_74.has_value) {
                    }
                }
            } else if (!_mv_67.has_value) {
                __auto_type _mv_75 = obj;
                if (_mv_75.has_value) {
                    __auto_type o = _mv_75.value;
                    __auto_type _mv_77 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_77.has_value) {
                        __auto_type subj_map = _mv_77.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    slop_rdf_rdf_Term s = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                    slop_rdf_index_TermSet term_set = *(slop_rdf_index_TermSet*)slop_map_value_at(_coll, _i);
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->len; _i++) {
                                            {
                                                slop_rdf_rdf_Term p = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_77.has_value) {
                    }
                } else if (!_mv_75.has_value) {
                    {
                        __auto_type _coll = g.triples;
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            }
        }
        _retval = result;
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

void rdf_indexed_graph_for_each(slop_rdf_index_IndexedGraph g, slop_option_slop_rdf_rdf_Term subj, slop_option_slop_rdf_rdf_Term pred, slop_option_slop_rdf_rdf_Term obj, slop_closure_t callback) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    __auto_type _mv_78 = subj;
    if (_mv_78.has_value) {
        __auto_type s = _mv_78.value;
        __auto_type _mv_80 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_80.has_value) {
            __auto_type pred_map = _mv_80.value;
            __auto_type _mv_81 = pred;
            if (_mv_81.has_value) {
                __auto_type p = _mv_81.value;
                __auto_type _mv_83 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_83.has_value) {
                    __auto_type term_set = _mv_83.value;
                    __auto_type _mv_84 = obj;
                    if (_mv_84.has_value) {
                        __auto_type o = _mv_84.value;
                        if (slop_map_has(term_set, &(o))) {
                            ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, ((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o}));
                        }
                    } else if (!_mv_84.has_value) {
                        {
                            slop_map* _coll = (slop_map*)term_set;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    slop_rdf_rdf_Term o = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                    ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, ((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    }
                } else if (!_mv_83.has_value) {
                }
            } else if (!_mv_81.has_value) {
                {
                    slop_map* _coll = (slop_map*)pred_map;
                    for (size_t _i = 0; _i < _coll->len; _i++) {
                        {
                            slop_rdf_rdf_Term p = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                            slop_rdf_index_TermSet term_set = *(slop_rdf_index_TermSet*)slop_map_value_at(_coll, _i);
                            __auto_type _mv_86 = obj;
                            if (_mv_86.has_value) {
                                __auto_type o = _mv_86.value;
                                if (slop_map_has(term_set, &(o))) {
                                    ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, ((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            } else if (!_mv_86.has_value) {
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->len; _i++) {
                                        {
                                            slop_rdf_rdf_Term o = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                            ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, ((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_80.has_value) {
        }
    } else if (!_mv_78.has_value) {
        __auto_type _mv_88 = pred;
        if (_mv_88.has_value) {
            __auto_type p = _mv_88.value;
            __auto_type _mv_89 = obj;
            if (_mv_89.has_value) {
                __auto_type o = _mv_89.value;
                __auto_type _mv_91 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_91.has_value) {
                    __auto_type obj_map = _mv_91.value;
                    __auto_type _mv_93 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_93.has_value) {
                        __auto_type subj_set = _mv_93.value;
                        {
                            slop_map* _coll = (slop_map*)subj_set;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    slop_rdf_rdf_Term s = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                    ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, ((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    } else if (!_mv_93.has_value) {
                    }
                } else if (!_mv_91.has_value) {
                }
            } else if (!_mv_89.has_value) {
                __auto_type _mv_95 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_95.has_value) {
                    __auto_type subj_map = _mv_95.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->len; _i++) {
                            {
                                slop_rdf_rdf_Term s = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                slop_rdf_index_TermSet term_set = *(slop_rdf_index_TermSet*)slop_map_value_at(_coll, _i);
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->len; _i++) {
                                        {
                                            slop_rdf_rdf_Term o = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                            ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, ((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_95.has_value) {
                }
            }
        } else if (!_mv_88.has_value) {
            __auto_type _mv_96 = obj;
            if (_mv_96.has_value) {
                __auto_type o = _mv_96.value;
                __auto_type _mv_98 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_98.has_value) {
                    __auto_type subj_map = _mv_98.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->len; _i++) {
                            {
                                slop_rdf_rdf_Term s = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                slop_rdf_index_TermSet term_set = *(slop_rdf_index_TermSet*)slop_map_value_at(_coll, _i);
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->len; _i++) {
                                        {
                                            slop_rdf_rdf_Term p = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                                            ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, ((slop_rdf_rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_98.has_value) {
                }
            } else if (!_mv_96.has_value) {
                {
                    __auto_type _coll = g.triples;
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type t = _coll.data[_i];
                        ((void(*)(void*, slop_rdf_rdf_Triple))callback.fn)(callback.env, t);
                    }
                }
            }
        }
    }
}

int64_t rdf_indexed_graph_size(slop_rdf_index_IndexedGraph g) {
    int64_t _retval = {0};
    _retval = g.size;
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval == g.size)), "(== $result (. g size))");
    return _retval;
}

slop_list_slop_rdf_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term pred, slop_rdf_rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_slop_rdf_rdf_Term){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type pos_idx = g.index.pos;
        __auto_type _mv_100 = ({ void* _ptr = slop_map_get(pos_idx, &(pred)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_100.has_value) {
            __auto_type obj_map = _mv_100.value;
            __auto_type _mv_102 = ({ void* _ptr = slop_map_get(obj_map, &(obj)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_102.has_value) {
                __auto_type subj_set = _mv_102.value;
                {
                    slop_map* _coll = (slop_map*)subj_set;
                    for (size_t _i = 0; _i < _coll->len; _i++) {
                        {
                            slop_rdf_rdf_Term s = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (s); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_102.has_value) {
            }
        } else if (!_mv_100.has_value) {
        }
        return result;
    }
}

slop_list_slop_rdf_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term subj, slop_rdf_rdf_Term pred) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_slop_rdf_rdf_Term){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_104 = ({ void* _ptr = slop_map_get(spo_idx, &(subj)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_104.has_value) {
            __auto_type pred_map = _mv_104.value;
            __auto_type _mv_106 = ({ void* _ptr = slop_map_get(pred_map, &(pred)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_106.has_value) {
                __auto_type obj_set = _mv_106.value;
                {
                    slop_map* _coll = (slop_map*)obj_set;
                    for (size_t _i = 0; _i < _coll->len; _i++) {
                        {
                            slop_rdf_rdf_Term o = *(slop_rdf_rdf_Term*)slop_map_key_at(_coll, _i);
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (o); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_106.has_value) {
            }
        } else if (!_mv_104.has_value) {
        }
        return result;
    }
}

