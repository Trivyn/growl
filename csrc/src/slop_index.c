#include "../runtime/slop_runtime.h"
#include "slop_index.h"

index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena);
index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t);
uint8_t rdf_indexed_graph_contains(index_IndexedGraph g, rdf_Triple t);
slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj);
void rdf_indexed_graph_for_each(index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj, slop_closure_t callback);
int64_t rdf_indexed_graph_size(index_IndexedGraph g);
slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj);
slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred);

index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena) {
    index_IndexedGraph _retval = {0};
    _retval = ((index_IndexedGraph){.triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .index = ((index_TripleIndex){.spo = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .pso = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .osp = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .pos = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term)}), .size = 0});
    SLOP_POST(((_retval.size == 0)), "(== (. $result size) 0)");
    return _retval;
}

index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    index_IndexedGraph _retval = {0};
    if (rdf_indexed_graph_contains(g, t)) {
        _retval = g;
    }
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type o = rdf_triple_object(t);
        ({ __auto_type _lst_p = &(g.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type spo_idx = g.index.spo;
            __auto_type _mv_10 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_10.has_value) {
                __auto_type pred_map = _mv_10.value;
                __auto_type _mv_11 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_11.has_value) {
                    __auto_type obj_set = _mv_11.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, obj_set, &(o), &_dummy); });
                } else if (!_mv_11.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pred_map, &(p), _vptr); });
                    }
                }
            } else if (!_mv_10.has_value) {
                {
                    __auto_type pred_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pred_map, &(p), _vptr); });
                    ({ __auto_type _val = pred_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, spo_idx, &(s), _vptr); });
                }
            }
        }
        {
            __auto_type pso_idx = g.index.pso;
            __auto_type _mv_12 = ({ void* _ptr = slop_map_get(pso_idx, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_12.has_value) {
                __auto_type subj_map = _mv_12.value;
                __auto_type _mv_13 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_13.has_value) {
                    __auto_type obj_set = _mv_13.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, obj_set, &(o), &_dummy); });
                } else if (!_mv_13.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    }
                }
            } else if (!_mv_12.has_value) {
                {
                    __auto_type subj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    ({ __auto_type _val = subj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pso_idx, &(p), _vptr); });
                }
            }
        }
        {
            __auto_type osp_idx = g.index.osp;
            __auto_type _mv_14 = ({ void* _ptr = slop_map_get(osp_idx, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_14.has_value) {
                __auto_type subj_map = _mv_14.value;
                __auto_type _mv_15 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_15.has_value) {
                    __auto_type pred_set = _mv_15.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, pred_set, &(p), &_dummy); });
                } else if (!_mv_15.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(p), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    }
                }
            } else if (!_mv_14.has_value) {
                {
                    __auto_type subj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(p), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    ({ __auto_type _val = subj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, osp_idx, &(o), _vptr); });
                }
            }
        }
        {
            __auto_type pos_idx = g.index.pos;
            __auto_type _mv_16 = ({ void* _ptr = slop_map_get(pos_idx, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_16.has_value) {
                __auto_type obj_map = _mv_16.value;
                __auto_type _mv_17 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_17.has_value) {
                    __auto_type subj_set = _mv_17.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, subj_set, &(s), &_dummy); });
                } else if (!_mv_17.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(s), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, obj_map, &(o), _vptr); });
                    }
                }
            } else if (!_mv_16.has_value) {
                {
                    __auto_type obj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(s), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, obj_map, &(o), _vptr); });
                    ({ __auto_type _val = obj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pos_idx, &(p), _vptr); });
                }
            }
        }
        _retval = ((index_IndexedGraph){.triples = g.triples, .index = g.index, .size = (g.size + 1)});
    }
    SLOP_POST(((_retval.size >= g.size)), "(>= (. $result size) (. g size))");
    return _retval;
}

uint8_t rdf_indexed_graph_contains(index_IndexedGraph g, rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    uint8_t _retval = {0};
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type o = rdf_triple_object(t);
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_18 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_18.has_value) {
            __auto_type pred_map = _mv_18.value;
            __auto_type _mv_19 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_19.has_value) {
                __auto_type obj_set = _mv_19.value;
                return (slop_map_get(obj_set, &(o)) != NULL);
            } else if (!_mv_19.has_value) {
                return 0;
            }
        } else if (!_mv_18.has_value) {
            return 0;
        }
    }
    return _retval;
}

slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_20 = subj;
        if (_mv_20.has_value) {
            __auto_type s = _mv_20.value;
            __auto_type _mv_21 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_21.has_value) {
                __auto_type pred_map = _mv_21.value;
                __auto_type _mv_22 = pred;
                if (_mv_22.has_value) {
                    __auto_type p = _mv_22.value;
                    __auto_type _mv_23 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_23.has_value) {
                        __auto_type term_set = _mv_23.value;
                        __auto_type _mv_24 = obj;
                        if (_mv_24.has_value) {
                            __auto_type o = _mv_24.value;
                            if (slop_map_get(term_set, &(o)) != NULL) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        } else if (!_mv_24.has_value) {
                            {
                                slop_map* _coll = (slop_map*)term_set;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    } else if (!_mv_23.has_value) {
                    }
                } else if (!_mv_22.has_value) {
                    {
                        slop_map* _coll = (slop_map*)pred_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                                index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                __auto_type _mv_25 = obj;
                                if (_mv_25.has_value) {
                                    __auto_type o = _mv_25.value;
                                    if (slop_map_get(term_set, &(o)) != NULL) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                } else if (!_mv_25.has_value) {
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (!_mv_21.has_value) {
            }
        } else if (!_mv_20.has_value) {
            __auto_type _mv_26 = pred;
            if (_mv_26.has_value) {
                __auto_type p = _mv_26.value;
                __auto_type _mv_27 = obj;
                if (_mv_27.has_value) {
                    __auto_type o = _mv_27.value;
                    __auto_type _mv_28 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_28.has_value) {
                        __auto_type obj_map = _mv_28.value;
                        __auto_type _mv_29 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                        if (_mv_29.has_value) {
                            __auto_type subj_set = _mv_29.value;
                            {
                                slop_map* _coll = (slop_map*)subj_set;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        } else if (!_mv_29.has_value) {
                        }
                    } else if (!_mv_28.has_value) {
                    }
                } else if (!_mv_27.has_value) {
                    __auto_type _mv_30 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_30.has_value) {
                        __auto_type subj_map = _mv_30.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                    index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_30.has_value) {
                    }
                }
            } else if (!_mv_26.has_value) {
                __auto_type _mv_31 = obj;
                if (_mv_31.has_value) {
                    __auto_type o = _mv_31.value;
                    __auto_type _mv_32 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_32.has_value) {
                        __auto_type subj_map = _mv_32.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                    index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_32.has_value) {
                    }
                } else if (!_mv_31.has_value) {
                    {
                        __auto_type _coll = g.triples;
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

void rdf_indexed_graph_for_each(index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj, slop_closure_t callback) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    __auto_type _mv_33 = subj;
    if (_mv_33.has_value) {
        __auto_type s = _mv_33.value;
        __auto_type _mv_34 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_34.has_value) {
            __auto_type pred_map = _mv_34.value;
            __auto_type _mv_35 = pred;
            if (_mv_35.has_value) {
                __auto_type p = _mv_35.value;
                __auto_type _mv_36 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_36.has_value) {
                    __auto_type term_set = _mv_36.value;
                    __auto_type _mv_37 = obj;
                    if (_mv_37.has_value) {
                        __auto_type o = _mv_37.value;
                        if (slop_map_get(term_set, &(o)) != NULL) {
                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                        }
                    } else if (!_mv_37.has_value) {
                        {
                            slop_map* _coll = (slop_map*)term_set;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    }
                } else if (!_mv_36.has_value) {
                }
            } else if (!_mv_35.has_value) {
                {
                    slop_map* _coll = (slop_map*)pred_map;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                            index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                            __auto_type _mv_38 = obj;
                            if (_mv_38.has_value) {
                                __auto_type o = _mv_38.value;
                                if (slop_map_get(term_set, &(o)) != NULL) {
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            } else if (!_mv_38.has_value) {
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_34.has_value) {
        }
    } else if (!_mv_33.has_value) {
        __auto_type _mv_39 = pred;
        if (_mv_39.has_value) {
            __auto_type p = _mv_39.value;
            __auto_type _mv_40 = obj;
            if (_mv_40.has_value) {
                __auto_type o = _mv_40.value;
                __auto_type _mv_41 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_41.has_value) {
                    __auto_type obj_map = _mv_41.value;
                    __auto_type _mv_42 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_42.has_value) {
                        __auto_type subj_set = _mv_42.value;
                        {
                            slop_map* _coll = (slop_map*)subj_set;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    } else if (!_mv_42.has_value) {
                    }
                } else if (!_mv_41.has_value) {
                }
            } else if (!_mv_40.has_value) {
                __auto_type _mv_43 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_43.has_value) {
                    __auto_type subj_map = _mv_43.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_43.has_value) {
                }
            }
        } else if (!_mv_39.has_value) {
            __auto_type _mv_44 = obj;
            if (_mv_44.has_value) {
                __auto_type o = _mv_44.value;
                __auto_type _mv_45 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_45.has_value) {
                    __auto_type subj_map = _mv_45.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_45.has_value) {
                }
            } else if (!_mv_44.has_value) {
                {
                    __auto_type _coll = g.triples;
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type t = _coll.data[_i];
                        ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                    }
                }
            }
        }
    }
}

int64_t rdf_indexed_graph_size(index_IndexedGraph g) {
    int64_t _retval = {0};
    _retval = g.size;
    SLOP_POST(((_retval == g.size)), "(== $result (. g size))");
    return _retval;
}

slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type pos_idx = g.index.pos;
        __auto_type _mv_46 = ({ void* _ptr = slop_map_get(pos_idx, &(pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_46.has_value) {
            __auto_type obj_map = _mv_46.value;
            __auto_type _mv_47 = ({ void* _ptr = slop_map_get(obj_map, &(obj)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_47.has_value) {
                __auto_type subj_set = _mv_47.value;
                {
                    slop_map* _coll = (slop_map*)subj_set;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (s); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_47.has_value) {
            }
        } else if (!_mv_46.has_value) {
        }
        return result;
    }
}

slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_48 = ({ void* _ptr = slop_map_get(spo_idx, &(subj)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_48.has_value) {
            __auto_type pred_map = _mv_48.value;
            __auto_type _mv_49 = ({ void* _ptr = slop_map_get(pred_map, &(pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_49.has_value) {
                __auto_type obj_set = _mv_49.value;
                {
                    slop_map* _coll = (slop_map*)obj_set;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (o); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_49.has_value) {
            }
        } else if (!_mv_48.has_value) {
        }
        return result;
    }
}

