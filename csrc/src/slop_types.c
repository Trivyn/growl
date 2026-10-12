#include "../runtime/slop_runtime.h"
#include "slop_types.h"

types_Delta types_make_delta(slop_arena* arena, int64_t iteration);
types_Delta types_delta_add(slop_arena* arena, types_Delta d, rdf_Triple t);
types_Delta types_delta_merge(slop_arena* arena, types_Delta d1, types_Delta d2);
uint8_t types_delta_is_empty(types_Delta d);
uint8_t types_all_triples_have_predicate(slop_list_rdf_Triple triples, slop_string pred_iri);

types_Delta types_make_delta(slop_arena* arena, int64_t iteration) {
    SLOP_PRE(((iteration >= 0)), "(>= iteration 0)");
    types_Delta _retval = {0};
    _retval = ((types_Delta){.triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .seen = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Triple, slop_hash_rdf_Triple, slop_eq_rdf_Triple, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); }), .by_predicate = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); }), .iteration = iteration});
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval.iteration == iteration)), "(== (. $result iteration) iteration)");
    SLOP_POST(((((int64_t)((_retval.triples).len)) == 0)), "(== (list-len (. $result triples)) 0)");
    return _retval;
}

types_Delta types_delta_add(slop_arena* arena, types_Delta d, rdf_Triple t) {
    SLOP_PRE(((d.iteration >= 0)), "(>= (. d iteration) 0)");
    types_Delta _retval = {0};
    if (slop_map_has(d.seen, &(t))) {
        _retval = d;
        goto _slop_post;
    } else {
        ({ slop_map_put(NULL, d.seen, &(t), NULL, 0); });
        ({ __auto_type _lst_p = &(d.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type pred = rdf_triple_predicate(t);
            __auto_type pred_map = d.by_predicate;
            __auto_type _mv_115 = ({ void* _ptr = slop_map_get(pred_map, &(pred)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_115.has_value) {
                __auto_type pred_set = _mv_115.value;
                ({ slop_map_put(NULL, pred_set, &(t), NULL, 0); });
            } else if (!_mv_115.has_value) {
                {
                    __auto_type new_set = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Triple, slop_hash_rdf_Triple, slop_eq_rdf_Triple, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, new_set, &(t), NULL, 0); });
                    ({ slop_map* _val = new_set; slop_map_put(NULL, pred_map, &(pred), &_val, sizeof(_val)); });
                }
            }
        }
        _retval = d;
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST(((_retval.iteration == d.iteration)), "(== (. $result iteration) (. d iteration))");
    return _retval;
}

types_Delta types_delta_merge(slop_arena* arena, types_Delta d1, types_Delta d2) {
    SLOP_PRE(((d1.iteration == d2.iteration)), "(== (. d1 iteration) (. d2 iteration))");
    types_Delta _retval = {0};
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
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST(((_retval.iteration == d1.iteration)), "(== (. $result iteration) (. d1 iteration))");
    return _retval;
}

uint8_t types_delta_is_empty(types_Delta d) {
    uint8_t _retval = {0};
    _retval = (((int64_t)((d.triples).len)) == 0);
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval == (((int64_t)((d.triples).len)) == 0))), "(== $result (== (list-len (. d triples)) 0))");
    return _retval;
}

uint8_t types_all_triples_have_predicate(slop_list_rdf_Triple triples, slop_string pred_iri) {
    uint8_t _retval = {0};
    {
        uint8_t result = 1;
        {
            __auto_type _coll = triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                {
                    __auto_type pred = rdf_triple_predicate(t);
                    __auto_type _mv_119 = pred;
                    switch (_mv_119.tag) {
                        case rdf_Term_term_iri:
                        {
                            __auto_type iri = _mv_119.data.term_iri;
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
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST((((((int64_t)((triples).len)) > 0) || _retval)), "(or (> (list-len triples) 0) $result)");
    return _retval;
}

