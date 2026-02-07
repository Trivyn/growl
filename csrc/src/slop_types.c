#include "../runtime/slop_runtime.h"
#include "slop_types.h"

types_Delta types_make_delta(slop_arena* arena, int64_t iteration);
types_Delta types_delta_add(slop_arena* arena, types_Delta d, rdf_Triple t);
types_Delta types_delta_merge(slop_arena* arena, types_Delta d1, types_Delta d2);
uint8_t types_delta_is_empty(types_Delta d);
uint8_t types_all_triples_have_predicate(slop_list_rdf_Triple triples, slop_string pred_iri);

types_Delta types_make_delta(slop_arena* arena, int64_t iteration) {
    SLOP_PRE(((iteration >= 0)), "(>= iteration 0)");
    types_Delta _retval;
    _retval = ((types_Delta){.triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .seen = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple), .by_predicate = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .iteration = iteration});
    SLOP_POST(((_retval.iteration == iteration)), "(== (. $result iteration) iteration)");
    SLOP_POST(((((int64_t)((_retval.triples).len)) == 0)), "(== (list-len (. $result triples)) 0)");
    return _retval;
}

types_Delta types_delta_add(slop_arena* arena, types_Delta d, rdf_Triple t) {
    SLOP_PRE(((d.iteration >= 0)), "(>= (. d iteration) 0)");
    types_Delta _retval;
    if ((slop_map_get(d.seen, &(t)) != NULL)) {
        _retval = d;
    } else {
        ({ uint8_t _dummy = 1; slop_map_put(arena, d.seen, &(t), &_dummy); });
        ({ __auto_type _lst_p = &(d.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type pred = rdf_triple_predicate(t);
            __auto_type pred_map = d.by_predicate;
            __auto_type _mv_42 = ({ void* _ptr = slop_map_get(pred_map, &(pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_42.has_value) {
                __auto_type pred_set = _mv_42.value;
                ({ uint8_t _dummy = 1; slop_map_put(arena, pred_set, &(t), &_dummy); });
            } else if (!_mv_42.has_value) {
                {
                    __auto_type new_set = slop_map_new_ptr(arena, 16, sizeof(rdf_Triple), slop_hash_rdf_Triple, slop_eq_rdf_Triple);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, new_set, &(t), &_dummy); });
                    ({ __auto_type _val = new_set; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pred_map, &(pred), _vptr); });
                }
            }
        }
        _retval = d;
    }
    SLOP_POST(((_retval.iteration == d.iteration)), "(== (. $result iteration) (. d iteration))");
    return _retval;
}

types_Delta types_delta_merge(slop_arena* arena, types_Delta d1, types_Delta d2) {
    SLOP_PRE(((d1.iteration == d2.iteration)), "(== (. d1 iteration) (. d2 iteration))");
    types_Delta _retval;
    {
        __auto_type result = d1;
        {
            __auto_type _coll = d2.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        _retval = result;
    }
    SLOP_POST(((_retval.iteration == d1.iteration)), "(== (. $result iteration) (. d1 iteration))");
    return _retval;
}

uint8_t types_delta_is_empty(types_Delta d) {
    uint8_t _retval;
    _retval = (((int64_t)((d.triples).len)) == 0);
    SLOP_POST(((_retval == ((int64_t)((d.triples).len))(==, 0))), "(== $result ((list-len (. d triples)) == 0))");
    return _retval;
}

uint8_t types_all_triples_have_predicate(slop_list_rdf_Triple triples, slop_string pred_iri) {
    uint8_t _retval;
    {
        uint8_t result = 1;
        {
            __auto_type _coll = triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                {
                    __auto_type pred = rdf_triple_predicate(t);
                    __auto_type _mv_43 = pred;
                    switch (_mv_43.tag) {
                        case rdf_Term_term_iri:
                        {
                            __auto_type iri = _mv_43.data.term_iri;
                            if (!(string_eq(iri.value, pred_iri))) {
                                result = 0;
                            }
                            break;
                        }
                        default: {
                            result = 0;
                            break;
                        }
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST((((((int64_t)((triples).len)) > 0) || _retval)), "(or (> (list-len triples) 0) $result)");
    return _retval;
}

