#include "../runtime/slop_runtime.h"
#include "slop_growl.h"

types_ReasonerConfig growl_default_config(void);
types_ReasonerResult growl_reason(slop_arena* arena, index_IndexedGraph input);
types_ReasonerResult growl_reason_with_config(slop_arena* arena, index_IndexedGraph input, types_ReasonerConfig config);
uint8_t growl_is_consistent(slop_arena* arena, index_IndexedGraph input);
slop_list_rdf_Term growl_get_types(slop_arena* arena, index_IndexedGraph g, rdf_Term individual);
slop_list_rdf_Term growl_get_same_as(slop_arena* arena, index_IndexedGraph g, rdf_Term individual);
int64_t growl_get_inferred_count(types_ReasonerResult result);

types_ReasonerConfig growl_default_config(void) {
    types_ReasonerConfig _retval = {0};
    _retval = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 1, .fast = 0, .complete = 0, .validate = 0, .validate_ns = SLOP_STR("")});
    SLOP_POST(((_retval.worker_count == 4)), "(== (. $result worker-count) 4)");
    SLOP_POST(((_retval.channel_buffer == 256)), "(== (. $result channel-buffer) 256)");
    SLOP_POST(((_retval.max_iterations == 1000)), "(== (. $result max-iterations) 1000)");
    SLOP_POST(((_retval.verbose == 1)), "(== (. $result verbose) true)");
    SLOP_POST(((_retval.fast == 0)), "(== (. $result fast) false)");
    SLOP_POST(((_retval.complete == 0)), "(== (. $result complete) false)");
    SLOP_POST(((_retval.validate == 0)), "(== (. $result validate) false)");
    return _retval;
}

types_ReasonerResult growl_reason(slop_arena* arena, index_IndexedGraph input) {
    SLOP_PRE(((rdf_indexed_graph_size(input) >= 0)), "(>= (indexed-graph-size input) 0)");
    types_ReasonerResult _retval = {0};
    _retval = growl_reason_with_config(arena, input, growl_default_config());
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr = {0}; switch (_mv.tag) { case types_ReasonerResult_reason_success: { __auto_type s = _mv.data.reason_success; _mr = (s.inferred_count >= 0); break; } case types_ReasonerResult_reason_inconsistent: { __auto_type _ = _mv.data.reason_inconsistent; _mr = 1; break; }  } _mr; })), "(match $result ((reason-success s) (>= (. s inferred-count) 0)) ((reason-inconsistent _) true))");
    return _retval;
}

types_ReasonerResult growl_reason_with_config(slop_arena* arena, index_IndexedGraph input, types_ReasonerConfig config) {
    SLOP_PRE(((rdf_indexed_graph_size(input) >= 0)), "(>= (indexed-graph-size input) 0)");
    SLOP_PRE(((config.worker_count >= 1)), "(>= (. config worker-count) 1)");
    SLOP_PRE(((config.max_iterations >= 1)), "(>= (. config max-iterations) 1)");
    types_ReasonerResult _retval = {0};
    _retval = engine_engine_run(arena, config, input);
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr = {0}; switch (_mv.tag) { case types_ReasonerResult_reason_success: { __auto_type s = _mv.data.reason_success; _mr = (s.iterations <= config.max_iterations); break; } case types_ReasonerResult_reason_inconsistent: { __auto_type _ = _mv.data.reason_inconsistent; _mr = 1; break; }  } _mr; })), "(match $result ((reason-success s) (<= (. s iterations) (. config max-iterations))) ((reason-inconsistent _) true))");
    return _retval;
}

uint8_t growl_is_consistent(slop_arena* arena, index_IndexedGraph input) {
    SLOP_PRE(((rdf_indexed_graph_size(input) >= 0)), "(>= (indexed-graph-size input) 0)");
    __auto_type _mv_337 = growl_reason(arena, input);
    switch (_mv_337.tag) {
        case types_ReasonerResult_reason_success:
        {
            __auto_type _ = _mv_337.data.reason_success;
            return 1;
        }
        case types_ReasonerResult_reason_inconsistent:
        {
            __auto_type _ = _mv_337.data.reason_inconsistent;
            return 0;
        }
    }
}

slop_list_rdf_Term growl_get_types(slop_arena* arena, index_IndexedGraph g, rdf_Term individual) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Term _retval = {0};
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type matches = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = individual}, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, no_term);
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        {
            __auto_type _coll = matches;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                ({ __auto_type _lst_p = &(result); __auto_type _item = (t.object); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Term growl_get_same_as(slop_arena* arena, index_IndexedGraph g, rdf_Term individual) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Term _retval = {0};
    {
        __auto_type same_pred = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type as_subject = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = individual}, (slop_option_rdf_Term){.has_value = 1, .value = same_pred}, no_term);
        __auto_type as_object = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = same_pred}, (slop_option_rdf_Term){.has_value = 1, .value = individual});
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        ({ __auto_type _lst_p = &(result); __auto_type _item = (individual); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type _coll = as_subject;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                ({ __auto_type _lst_p = &(result); __auto_type _item = (t.object); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
            }
        }
        {
            __auto_type _coll = as_object;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                ({ __auto_type _lst_p = &(result); __auto_type _item = (t.subject); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

int64_t growl_get_inferred_count(types_ReasonerResult result) {
    int64_t _retval = {0};
    __auto_type _mv_338 = result;
    switch (_mv_338.tag) {
        case types_ReasonerResult_reason_success:
        {
            __auto_type s = _mv_338.data.reason_success;
            return s.inferred_count;
        }
        case types_ReasonerResult_reason_inconsistent:
        {
            __auto_type _ = _mv_338.data.reason_inconsistent;
            return 0;
        }
    }
    SLOP_POST(((_retval >= 0)), "(>= $result 0)");
    return _retval;
}

