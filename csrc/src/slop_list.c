#include "../runtime/slop_runtime.h"
#include "slop_list.h"

slop_list_rdf_Term rdf_list_elements(slop_arena* arena, rdf_Graph g, rdf_Term head);
slop_list_rdf_Term rdf_list_elements_indexed(slop_arena* arena, index_IndexedGraph g, rdf_Term head);
uint8_t rdf_list_contains(slop_arena* arena, rdf_Graph g, rdf_Term head, rdf_Term element);
int64_t rdf_list_length(slop_arena* arena, rdf_Graph g, rdf_Term head);

slop_list_rdf_Term rdf_list_elements(slop_arena* arena, rdf_Graph g, rdf_Term head) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_list_rdf_Term _retval;
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type first_pred = rdf_make_iri(arena, vocab_RDF_FIRST);
        __auto_type rest_pred = rdf_make_iri(arena, vocab_RDF_REST);
        __auto_type nil_term = rdf_make_iri(arena, vocab_RDF_NIL);
        __auto_type current = head;
        slop_option_rdf_Term no_obj = (slop_option_rdf_Term){.has_value = false};
        while (!(rdf_term_eq(current, nil_term))) {
            {
                __auto_type first_matches = rdf_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = current}, (slop_option_rdf_Term){.has_value = 1, .value = first_pred}, no_obj);
                if ((((int64_t)((first_matches.triples).len)) > 0)) {
                    __auto_type _mv_94 = ({ __auto_type _lst = first_matches.triples; size_t _idx = (size_t)0; slop_option_rdf_Triple _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_94.has_value) {
                        __auto_type first_triple = _mv_94.value;
                        ({ __auto_type _lst_p = &(result); __auto_type _item = (rdf_triple_object(first_triple)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                    } else if (!_mv_94.has_value) {
                    }
                }
            }
            {
                __auto_type rest_matches = rdf_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = current}, (slop_option_rdf_Term){.has_value = 1, .value = rest_pred}, no_obj);
                if ((((int64_t)((rest_matches.triples).len)) > 0)) {
                    __auto_type _mv_95 = ({ __auto_type _lst = rest_matches.triples; size_t _idx = (size_t)0; slop_option_rdf_Triple _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_95.has_value) {
                        __auto_type rest_triple = _mv_95.value;
                        current = rdf_triple_object(rest_triple);
                    } else if (!_mv_95.has_value) {
                        current = nil_term;
                    }
                } else {
                    current = nil_term;
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Term rdf_list_elements_indexed(slop_arena* arena, index_IndexedGraph g, rdf_Term head) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_list_rdf_Term _retval;
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type first_pred = rdf_make_iri(arena, vocab_RDF_FIRST);
        __auto_type rest_pred = rdf_make_iri(arena, vocab_RDF_REST);
        __auto_type nil_term = rdf_make_iri(arena, vocab_RDF_NIL);
        __auto_type current = head;
        slop_option_rdf_Term no_obj = (slop_option_rdf_Term){.has_value = false};
        while (!(rdf_term_eq(current, nil_term))) {
            {
                __auto_type first_matches = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = current}, (slop_option_rdf_Term){.has_value = 1, .value = first_pred}, no_obj);
                if ((((int64_t)((first_matches).len)) > 0)) {
                    __auto_type _mv_96 = ({ __auto_type _lst = first_matches; size_t _idx = (size_t)0; slop_option_rdf_Triple _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_96.has_value) {
                        __auto_type first_triple = _mv_96.value;
                        ({ __auto_type _lst_p = &(result); __auto_type _item = (rdf_triple_object(first_triple)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                    } else if (!_mv_96.has_value) {
                    }
                }
            }
            {
                __auto_type rest_matches = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = current}, (slop_option_rdf_Term){.has_value = 1, .value = rest_pred}, no_obj);
                if ((((int64_t)((rest_matches).len)) > 0)) {
                    __auto_type _mv_97 = ({ __auto_type _lst = rest_matches; size_t _idx = (size_t)0; slop_option_rdf_Triple _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_97.has_value) {
                        __auto_type rest_triple = _mv_97.value;
                        current = rdf_triple_object(rest_triple);
                    } else if (!_mv_97.has_value) {
                        current = nil_term;
                    }
                } else {
                    current = nil_term;
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

uint8_t rdf_list_contains(slop_arena* arena, rdf_Graph g, rdf_Term head, rdf_Term element) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type elements = rdf_list_elements(arena, g, head);
        uint8_t found = 0;
        {
            __auto_type _coll = elements;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type e = _coll.data[_i];
                if (rdf_term_eq(e, element)) {
                    found = 1;
                }
            }
        }
        return found;
    }
}

int64_t rdf_list_length(slop_arena* arena, rdf_Graph g, rdf_Term head) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    int64_t _retval;
    _retval = ((int64_t)((rdf_list_elements(arena, g, head)).len));
    SLOP_POST(((_retval >= 0)), "(>= $result 0)");
    return _retval;
}

