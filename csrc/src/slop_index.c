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
    index_IndexedGraph _retval;
    _retval = ((index_IndexedGraph){.triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .index = ((index_TripleIndex){.spo = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .pso = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .osp = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term)}), .size = 0});
    SLOP_POST(((_retval.size == 0)), "(== (. $result size) 0)");
    return _retval;
}

index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    index_IndexedGraph _retval;
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
            __auto_type _mv_9 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_9.has_value) {
                __auto_type pred_map = _mv_9.value;
                __auto_type _mv_10 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_10.has_value) {
                    __auto_type triple_set = _mv_10.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, triple_set, &(t), &_dummy); });
                } else if (!_mv_10.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(t), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pred_map, &(p), _vptr); });
                    }
                }
            } else if (!_mv_9.has_value) {
                {
                    __auto_type pred_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(t), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pred_map, &(p), _vptr); });
                    ({ __auto_type _val = pred_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, spo_idx, &(s), _vptr); });
                }
            }
        }
        {
            __auto_type pso_idx = g.index.pso;
            __auto_type _mv_11 = ({ void* _ptr = slop_map_get(pso_idx, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_11.has_value) {
                __auto_type subj_map = _mv_11.value;
                __auto_type _mv_12 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_12.has_value) {
                    __auto_type triple_set = _mv_12.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, triple_set, &(t), &_dummy); });
                } else if (!_mv_12.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(t), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    }
                }
            } else if (!_mv_11.has_value) {
                {
                    __auto_type subj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(t), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    ({ __auto_type _val = subj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pso_idx, &(p), _vptr); });
                }
            }
        }
        {
            __auto_type osp_idx = g.index.osp;
            __auto_type _mv_13 = ({ void* _ptr = slop_map_get(osp_idx, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_13.has_value) {
                __auto_type subj_map = _mv_13.value;
                __auto_type _mv_14 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_14.has_value) {
                    __auto_type triple_set = _mv_14.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, triple_set, &(t), &_dummy); });
                } else if (!_mv_14.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(t), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    }
                }
            } else if (!_mv_13.has_value) {
                {
                    __auto_type subj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(t), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    ({ __auto_type _val = subj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, osp_idx, &(o), _vptr); });
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
    uint8_t _retval;
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_15 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_15.has_value) {
            __auto_type pred_map = _mv_15.value;
            __auto_type _mv_16 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_16.has_value) {
                __auto_type triple_set = _mv_16.value;
                return (slop_map_get(triple_set, &(t)) != NULL);
            } else if (!_mv_16.has_value) {
                return 0;
            }
        } else if (!_mv_15.has_value) {
            return 0;
        }
    }
    return _retval;
}

slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_17 = subj;
        if (_mv_17.has_value) {
            __auto_type s = _mv_17.value;
            __auto_type _mv_18 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_18.has_value) {
                __auto_type pred_map = _mv_18.value;
                __auto_type _mv_19 = pred;
                if (_mv_19.has_value) {
                    __auto_type p = _mv_19.value;
                    __auto_type _mv_20 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_20.has_value) {
                        __auto_type triple_set = _mv_20.value;
                        __auto_type _mv_21 = obj;
                        if (_mv_21.has_value) {
                            __auto_type o = _mv_21.value;
                            {
                                slop_map* _coll = (slop_map*)triple_set;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                        if (rdf_term_eq(rdf_triple_object(t), o)) {
                                            ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                        }
                                    }
                                }
                            }
                        } else if (!_mv_21.has_value) {
                            {
                                slop_map* _coll = (slop_map*)triple_set;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    } else if (!_mv_20.has_value) {
                    }
                } else if (!_mv_19.has_value) {
                    {
                        slop_map* _coll = (slop_map*)pred_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                                index_TripleSet triple_set = *(index_TripleSet*)_coll->entries[_i].value;
                                __auto_type _mv_22 = obj;
                                if (_mv_22.has_value) {
                                    __auto_type o = _mv_22.value;
                                    {
                                        slop_map* _coll = (slop_map*)triple_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                                if (rdf_term_eq(rdf_triple_object(t), o)) {
                                                    ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                }
                                            }
                                        }
                                    }
                                } else if (!_mv_22.has_value) {
                                    {
                                        slop_map* _coll = (slop_map*)triple_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (!_mv_18.has_value) {
            }
        } else if (!_mv_17.has_value) {
            __auto_type _mv_23 = pred;
            if (_mv_23.has_value) {
                __auto_type p = _mv_23.value;
                __auto_type _mv_24 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_24.has_value) {
                    __auto_type subj_map = _mv_24.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                index_TripleSet triple_set = *(index_TripleSet*)_coll->entries[_i].value;
                                __auto_type _mv_25 = obj;
                                if (_mv_25.has_value) {
                                    __auto_type o = _mv_25.value;
                                    {
                                        slop_map* _coll = (slop_map*)triple_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                                if (rdf_term_eq(rdf_triple_object(t), o)) {
                                                    ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                }
                                            }
                                        }
                                    }
                                } else if (!_mv_25.has_value) {
                                    {
                                        slop_map* _coll = (slop_map*)triple_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_24.has_value) {
                }
            } else if (!_mv_23.has_value) {
                __auto_type _mv_26 = obj;
                if (_mv_26.has_value) {
                    __auto_type o = _mv_26.value;
                    __auto_type _mv_27 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_27.has_value) {
                        __auto_type subj_map = _mv_27.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                    index_TripleSet triple_set = *(index_TripleSet*)_coll->entries[_i].value;
                                    {
                                        slop_map* _coll = (slop_map*)triple_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_27.has_value) {
                    }
                } else if (!_mv_26.has_value) {
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
    __auto_type _mv_28 = subj;
    if (_mv_28.has_value) {
        __auto_type s = _mv_28.value;
        __auto_type _mv_29 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_29.has_value) {
            __auto_type pred_map = _mv_29.value;
            __auto_type _mv_30 = pred;
            if (_mv_30.has_value) {
                __auto_type p = _mv_30.value;
                __auto_type _mv_31 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_31.has_value) {
                    __auto_type triple_set = _mv_31.value;
                    __auto_type _mv_32 = obj;
                    if (_mv_32.has_value) {
                        __auto_type o = _mv_32.value;
                        {
                            slop_map* _coll = (slop_map*)triple_set;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                    if (rdf_term_eq(rdf_triple_object(t), o)) {
                                        ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                                    }
                                }
                            }
                        }
                    } else if (!_mv_32.has_value) {
                        {
                            slop_map* _coll = (slop_map*)triple_set;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                                }
                            }
                        }
                    }
                } else if (!_mv_31.has_value) {
                }
            } else if (!_mv_30.has_value) {
                {
                    slop_map* _coll = (slop_map*)pred_map;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                            index_TripleSet triple_set = *(index_TripleSet*)_coll->entries[_i].value;
                            __auto_type _mv_33 = obj;
                            if (_mv_33.has_value) {
                                __auto_type o = _mv_33.value;
                                {
                                    slop_map* _coll = (slop_map*)triple_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                            if (rdf_term_eq(rdf_triple_object(t), o)) {
                                                ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                                            }
                                        }
                                    }
                                }
                            } else if (!_mv_33.has_value) {
                                {
                                    slop_map* _coll = (slop_map*)triple_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_29.has_value) {
        }
    } else if (!_mv_28.has_value) {
        __auto_type _mv_34 = pred;
        if (_mv_34.has_value) {
            __auto_type p = _mv_34.value;
            __auto_type _mv_35 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_35.has_value) {
                __auto_type subj_map = _mv_35.value;
                {
                    slop_map* _coll = (slop_map*)subj_map;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                            index_TripleSet triple_set = *(index_TripleSet*)_coll->entries[_i].value;
                            __auto_type _mv_36 = obj;
                            if (_mv_36.has_value) {
                                __auto_type o = _mv_36.value;
                                {
                                    slop_map* _coll = (slop_map*)triple_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                            if (rdf_term_eq(rdf_triple_object(t), o)) {
                                                ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                                            }
                                        }
                                    }
                                }
                            } else if (!_mv_36.has_value) {
                                {
                                    slop_map* _coll = (slop_map*)triple_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (!_mv_35.has_value) {
            }
        } else if (!_mv_34.has_value) {
            __auto_type _mv_37 = obj;
            if (_mv_37.has_value) {
                __auto_type o = _mv_37.value;
                __auto_type _mv_38 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_38.has_value) {
                    __auto_type subj_map = _mv_38.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                index_TripleSet triple_set = *(index_TripleSet*)_coll->entries[_i].value;
                                {
                                    slop_map* _coll = (slop_map*)triple_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_38.has_value) {
                }
            } else if (!_mv_37.has_value) {
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
    int64_t _retval;
    _retval = g.size;
    SLOP_POST(((_retval == g.size)), "(== $result (. g size))");
    return _retval;
}

slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type osp_idx = g.index.osp;
        __auto_type _mv_39 = ({ void* _ptr = slop_map_get(osp_idx, &(obj)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_39.has_value) {
            __auto_type subj_map = _mv_39.value;
            {
                slop_map* _coll = (slop_map*)subj_map;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                        index_TripleSet triple_set = *(index_TripleSet*)_coll->entries[_i].value;
                        {
                            __auto_type found = 0;
                            {
                                slop_map* _coll = (slop_map*)triple_set;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                                        if ((!(found) && rdf_term_eq(rdf_triple_predicate(t), pred))) {
                                            ({ __auto_type _lst_p = &(result); __auto_type _item = (s); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            found = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_39.has_value) {
        }
        return result;
    }
}

slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_40 = ({ void* _ptr = slop_map_get(spo_idx, &(subj)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_40.has_value) {
            __auto_type pred_map = _mv_40.value;
            __auto_type _mv_41 = ({ void* _ptr = slop_map_get(pred_map, &(pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_41.has_value) {
                __auto_type triple_set = _mv_41.value;
                {
                    slop_map* _coll = (slop_map*)triple_set;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Triple t = *(rdf_Triple*)_coll->entries[_i].key;
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (rdf_triple_object(t)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_41.has_value) {
            }
        } else if (!_mv_40.has_value) {
        }
        return result;
    }
}

