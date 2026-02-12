#include "../runtime/slop_runtime.h"
#include "slop_eq.h"

static const slop_string eq_EX_ALICE = SLOP_STR("http://example.org/alice");
static const slop_string eq_EX_ALICIA = SLOP_STR("http://example.org/alicia");
static const slop_string eq_EX_BOB = SLOP_STR("http://example.org/bob");
static const slop_string eq_EX_ROBERT = SLOP_STR("http://example.org/robert");
static const slop_string eq_EX_CAROL = SLOP_STR("http://example.org/carol");
static const slop_string eq_EX_A = SLOP_STR("http://example.org/a");
static const slop_string eq_EX_B = SLOP_STR("http://example.org/b");
static const slop_string eq_EX_C = SLOP_STR("http://example.org/c");
static const slop_string eq_EX_KNOWS = SLOP_STR("http://example.org/knows");
static const slop_string eq_EX_ACQUAINTED_WITH = SLOP_STR("http://example.org/acquaintedWith");

index_IndexedGraph eq_fixture_g_same_as(slop_arena* arena);
index_IndexedGraph eq_fixture_g_trans(slop_arena* arena);
index_IndexedGraph eq_fixture_g_rep_s(slop_arena* arena);
index_IndexedGraph eq_fixture_g_rep_p(slop_arena* arena);
index_IndexedGraph eq_fixture_g_rep_o(slop_arena* arena);
index_IndexedGraph eq_fixture_g_contradiction(slop_arena* arena);
index_IndexedGraph eq_fixture_g_no_contradiction(slop_arena* arena);
index_IndexedGraph eq_fixture_g_sym_contradiction(slop_arena* arena);
types_Delta eq_fixture_delta_same_as(slop_arena* arena);
types_Delta eq_fixture_delta_trans(slop_arena* arena);
types_Delta eq_fixture_delta_empty(slop_arena* arena);
types_Delta eq_fixture_delta_rep_p(slop_arena* arena);
types_Delta eq_fixture_delta_rep_o(slop_arena* arena);
types_Delta eq_fixture_delta_contradiction(slop_arena* arena);
slop_result_types_Delta_types_InconsistencyReport eq_apply_eq_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast);
slop_list_rdf_Triple eq_eq_sym(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_trans(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_rep_s(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_rep_p(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_rep_o(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport eq_eq_diff1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport eq_eq_diff2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport eq_eq_diff3(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_ref(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

typedef struct { slop_arena* arena; rdf_Term x; rdf_Term same_as; index_IndexedGraph g; slop_list_rdf_Triple* result; } eq__lambda_146_env_t;

static void eq__lambda_146(eq__lambda_146_env_t* _env, rdf_Triple yo_triple) { ({ __auto_type z = rdf_triple_object(yo_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->x, _env->same_as, z); (((!(rdf_term_eq(_env->x, z)) && !(rdf_indexed_graph_contains(_env->g, inferred)))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term same_as; rdf_Term y; index_IndexedGraph g; slop_list_rdf_Triple* result; } eq__lambda_147_env_t;

static void eq__lambda_147(eq__lambda_147_env_t* _env, rdf_Triple xs_triple) { ({ __auto_type w = rdf_triple_subject(xs_triple); __auto_type inferred = rdf_make_triple(_env->arena, w, _env->same_as, _env->y); (((!(rdf_term_eq(w, _env->y)) && !(rdf_indexed_graph_contains(_env->g, inferred)))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { rdf_Term same_as; slop_arena* arena; rdf_Term s_prime; index_IndexedGraph g; slop_list_rdf_Triple* result; } eq__lambda_149_env_t;

static void eq__lambda_149(eq__lambda_149_env_t* _env, rdf_Triple s_triple) { ({ __auto_type p = rdf_triple_predicate(s_triple); __auto_type o = rdf_triple_object(s_triple); ((!(rdf_term_eq(p, _env->same_as))) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->s_prime, p, o); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

typedef struct { rdf_Term s; slop_arena* arena; rdf_Term p; rdf_Term o; index_IndexedGraph g; slop_list_rdf_Triple* result; } eq__lambda_150_env_t;

static void eq__lambda_150(eq__lambda_150_env_t* _env, rdf_Triple same_triple) { ({ __auto_type s_prime = rdf_triple_object(same_triple); ((!(rdf_term_eq(s_prime, _env->s))) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, s_prime, _env->p, _env->o); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p_prime; index_IndexedGraph g; slop_list_rdf_Triple* result; } eq__lambda_152_env_t;

static void eq__lambda_152(eq__lambda_152_env_t* _env, rdf_Triple p_triple) { ({ __auto_type s = rdf_triple_subject(p_triple); __auto_type o = rdf_triple_object(p_triple); __auto_type inferred = rdf_make_triple(_env->arena, s, _env->p_prime, o); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { rdf_Term same_as; slop_arena* arena; rdf_Term o_prime; index_IndexedGraph g; slop_list_rdf_Triple* result; } eq__lambda_154_env_t;

static void eq__lambda_154(eq__lambda_154_env_t* _env, rdf_Triple o_triple) { ({ __auto_type s = rdf_triple_subject(o_triple); __auto_type p = rdf_triple_predicate(o_triple); ((!(rdf_term_eq(p, _env->same_as))) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, s, p, _env->o_prime); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

typedef struct { rdf_Term o; slop_arena* arena; rdf_Term s; rdf_Term p; index_IndexedGraph g; slop_list_rdf_Triple* result; } eq__lambda_155_env_t;

static void eq__lambda_155(eq__lambda_155_env_t* _env, rdf_Triple same_triple) { ({ __auto_type o_prime = rdf_triple_object(same_triple); ((!(rdf_term_eq(o_prime, _env->o))) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->s, _env->p, o_prime); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

index_IndexedGraph eq_fixture_g_same_as(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type alicia = rdf_make_iri(arena, eq_EX_ALICIA);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, same_as, alicia));
        return g;
    }
}

index_IndexedGraph eq_fixture_g_trans(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type a = rdf_make_iri(arena, eq_EX_A);
        __auto_type b = rdf_make_iri(arena, eq_EX_B);
        __auto_type c = rdf_make_iri(arena, eq_EX_C);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, a, same_as, b));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, b, same_as, c));
        return g;
    }
}

index_IndexedGraph eq_fixture_g_rep_s(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type knows = rdf_make_iri(arena, eq_EX_KNOWS);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type alicia = rdf_make_iri(arena, eq_EX_ALICIA);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, same_as, alicia));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, knows, bob));
        return g;
    }
}

index_IndexedGraph eq_fixture_g_rep_p(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type knows = rdf_make_iri(arena, eq_EX_KNOWS);
        __auto_type acquainted = rdf_make_iri(arena, eq_EX_ACQUAINTED_WITH);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, knows, same_as, acquainted));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, knows, bob));
        return g;
    }
}

index_IndexedGraph eq_fixture_g_rep_o(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type knows = rdf_make_iri(arena, eq_EX_KNOWS);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        __auto_type robert = rdf_make_iri(arena, eq_EX_ROBERT);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, bob, same_as, robert));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, knows, bob));
        return g;
    }
}

index_IndexedGraph eq_fixture_g_contradiction(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type diff_from = rdf_make_iri(arena, vocab_OWL_DIFFERENT_FROM);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, same_as, bob));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, diff_from, bob));
        return g;
    }
}

index_IndexedGraph eq_fixture_g_no_contradiction(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type diff_from = rdf_make_iri(arena, vocab_OWL_DIFFERENT_FROM);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        __auto_type carol = rdf_make_iri(arena, eq_EX_CAROL);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, same_as, bob));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, diff_from, carol));
        return g;
    }
}

index_IndexedGraph eq_fixture_g_sym_contradiction(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type diff_from = rdf_make_iri(arena, vocab_OWL_DIFFERENT_FROM);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, same_as, bob));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, bob, diff_from, alice));
        return g;
    }
}

types_Delta eq_fixture_delta_same_as(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type alicia = rdf_make_iri(arena, eq_EX_ALICIA);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, same_as, alicia));
        return d;
    }
}

types_Delta eq_fixture_delta_trans(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type b = rdf_make_iri(arena, eq_EX_B);
        __auto_type c = rdf_make_iri(arena, eq_EX_C);
        d = types_delta_add(arena, d, rdf_make_triple(arena, b, same_as, c));
        return d;
    }
}

types_Delta eq_fixture_delta_empty(slop_arena* arena) {
    return types_make_delta(arena, 0);
}

types_Delta eq_fixture_delta_rep_p(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type knows = rdf_make_iri(arena, eq_EX_KNOWS);
        __auto_type acquainted = rdf_make_iri(arena, eq_EX_ACQUAINTED_WITH);
        d = types_delta_add(arena, d, rdf_make_triple(arena, knows, same_as, acquainted));
        return d;
    }
}

types_Delta eq_fixture_delta_rep_o(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        __auto_type robert = rdf_make_iri(arena, eq_EX_ROBERT);
        d = types_delta_add(arena, d, rdf_make_triple(arena, bob, same_as, robert));
        return d;
    }
}

types_Delta eq_fixture_delta_contradiction(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type alice = rdf_make_iri(arena, eq_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, eq_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, same_as, bob));
        return d;
    }
}

slop_result_types_Delta_types_InconsistencyReport eq_apply_eq_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type result = types_make_delta(arena, next_iter);
        {
            __auto_type _coll = eq_eq_sym(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = eq_eq_trans(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = eq_eq_rep_s(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = eq_eq_rep_p(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = eq_eq_rep_o(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        if (!(fast)) {
            __auto_type _mv_141 = eq_eq_diff1(arena, g, delta);
            if (_mv_141.has_value) {
                __auto_type report = _mv_141.value;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            } else if (!_mv_141.has_value) {
            }
            __auto_type _mv_142 = eq_eq_diff2(arena, g, delta);
            if (_mv_142.has_value) {
                __auto_type report = _mv_142.value;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            } else if (!_mv_142.has_value) {
            }
            __auto_type _mv_143 = eq_eq_diff3(arena, g, delta);
            if (_mv_143.has_value) {
                __auto_type report = _mv_143.value;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            } else if (!_mv_143.has_value) {
            }
        }
        _retval = ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = true, .data.ok = result });
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == (delta.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) (+ (. delta iteration) 1))) ((error _) true))");
    return _retval;
}

slop_list_rdf_Triple eq_eq_sym(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_144 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(same_as)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_144.has_value) {
            __auto_type pred_triples = _mv_144.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type x = rdf_triple_subject(dt);
                            __auto_type y = rdf_triple_object(dt);
                            __auto_type inferred = rdf_make_triple(arena, y, same_as, x);
                            if (!(rdf_indexed_graph_contains(g, inferred))) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        }
                    }
                }
            }
        } else if (!_mv_144.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

slop_list_rdf_Triple eq_eq_trans(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_145 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(same_as)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_145.has_value) {
            __auto_type pred_triples = _mv_145.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type x = rdf_triple_subject(dt);
                            __auto_type y = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = y}, (slop_option_rdf_Term){.has_value = 1, .value = same_as}, no_term, ({ eq__lambda_146_env_t* eq__lambda_146_env = (eq__lambda_146_env_t*)slop_arena_alloc(arena, sizeof(eq__lambda_146_env_t)); *eq__lambda_146_env = (eq__lambda_146_env_t){ .arena = arena, .x = x, .same_as = same_as, .g = g, .result = &(result) }; (slop_closure_t){ (void*)eq__lambda_146, (void*)eq__lambda_146_env }; }));
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = same_as}, (slop_option_rdf_Term){.has_value = 1, .value = x}, ({ eq__lambda_147_env_t* eq__lambda_147_env = (eq__lambda_147_env_t*)slop_arena_alloc(arena, sizeof(eq__lambda_147_env_t)); *eq__lambda_147_env = (eq__lambda_147_env_t){ .arena = arena, .same_as = same_as, .y = y, .g = g, .result = &(result) }; (slop_closure_t){ (void*)eq__lambda_147, (void*)eq__lambda_147_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_145.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

slop_list_rdf_Triple eq_eq_rep_s(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_148 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(same_as)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_148.has_value) {
            __auto_type pred_triples = _mv_148.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type s = rdf_triple_subject(dt);
                            __auto_type s_prime = rdf_triple_object(dt);
                            if (!(rdf_term_eq(s, s_prime))) {
                                rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = s}, no_term, no_term, ({ eq__lambda_149_env_t* eq__lambda_149_env = (eq__lambda_149_env_t*)slop_arena_alloc(arena, sizeof(eq__lambda_149_env_t)); *eq__lambda_149_env = (eq__lambda_149_env_t){ .same_as = same_as, .arena = arena, .s_prime = s_prime, .g = g, .result = &(result) }; (slop_closure_t){ (void*)eq__lambda_149, (void*)eq__lambda_149_env }; }));
                            }
                        }
                    }
                }
            }
        } else if (!_mv_148.has_value) {
        }
        {
            __auto_type _coll = delta.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type dt = _coll.data[_i];
                if (!(rdf_term_eq(rdf_triple_predicate(dt), same_as))) {
                    {
                        __auto_type s = rdf_triple_subject(dt);
                        __auto_type p = rdf_triple_predicate(dt);
                        __auto_type o = rdf_triple_object(dt);
                        rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = s}, (slop_option_rdf_Term){.has_value = 1, .value = same_as}, no_term, ({ eq__lambda_150_env_t* eq__lambda_150_env = (eq__lambda_150_env_t*)slop_arena_alloc(arena, sizeof(eq__lambda_150_env_t)); *eq__lambda_150_env = (eq__lambda_150_env_t){ .s = s, .arena = arena, .p = p, .o = o, .g = g, .result = &(result) }; (slop_closure_t){ (void*)eq__lambda_150, (void*)eq__lambda_150_env }; }));
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple eq_eq_rep_p(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_151 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(same_as)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_151.has_value) {
            __auto_type pred_triples = _mv_151.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p = rdf_triple_subject(dt);
                            __auto_type p_prime = rdf_triple_object(dt);
                            if (!(rdf_term_eq(p, p_prime))) {
                                rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = p}, no_term, ({ eq__lambda_152_env_t* eq__lambda_152_env = (eq__lambda_152_env_t*)slop_arena_alloc(arena, sizeof(eq__lambda_152_env_t)); *eq__lambda_152_env = (eq__lambda_152_env_t){ .arena = arena, .p_prime = p_prime, .g = g, .result = &(result) }; (slop_closure_t){ (void*)eq__lambda_152, (void*)eq__lambda_152_env }; }));
                            }
                        }
                    }
                }
            }
        } else if (!_mv_151.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple eq_eq_rep_o(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_153 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(same_as)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_153.has_value) {
            __auto_type pred_triples = _mv_153.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type o = rdf_triple_subject(dt);
                            __auto_type o_prime = rdf_triple_object(dt);
                            if (!(rdf_term_eq(o, o_prime))) {
                                rdf_indexed_graph_for_each(g, no_term, no_term, (slop_option_rdf_Term){.has_value = 1, .value = o}, ({ eq__lambda_154_env_t* eq__lambda_154_env = (eq__lambda_154_env_t*)slop_arena_alloc(arena, sizeof(eq__lambda_154_env_t)); *eq__lambda_154_env = (eq__lambda_154_env_t){ .same_as = same_as, .arena = arena, .o_prime = o_prime, .g = g, .result = &(result) }; (slop_closure_t){ (void*)eq__lambda_154, (void*)eq__lambda_154_env }; }));
                            }
                        }
                    }
                }
            }
        } else if (!_mv_153.has_value) {
        }
        {
            __auto_type _coll = delta.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type dt = _coll.data[_i];
                if (!(rdf_term_eq(rdf_triple_predicate(dt), same_as))) {
                    {
                        __auto_type s = rdf_triple_subject(dt);
                        __auto_type p = rdf_triple_predicate(dt);
                        __auto_type o = rdf_triple_object(dt);
                        rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = o}, (slop_option_rdf_Term){.has_value = 1, .value = same_as}, no_term, ({ eq__lambda_155_env_t* eq__lambda_155_env = (eq__lambda_155_env_t*)slop_arena_alloc(arena, sizeof(eq__lambda_155_env_t)); *eq__lambda_155_env = (eq__lambda_155_env_t){ .o = o, .arena = arena, .s = s, .p = p, .g = g, .result = &(result) }; (slop_closure_t){ (void*)eq__lambda_155, (void*)eq__lambda_155_env }; }));
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_option_types_InconsistencyReport eq_eq_diff1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type different_from = rdf_make_iri(arena, vocab_OWL_DIFFERENT_FROM);
        __auto_type _mv_156 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(same_as)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_156.has_value) {
            __auto_type pred_triples = _mv_156.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type x = rdf_triple_subject(dt);
                            __auto_type y = rdf_triple_object(dt);
                            __auto_type diff_triple = rdf_make_triple(arena, x, different_from, y);
                            if (rdf_indexed_graph_contains(g, diff_triple)) {
                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("eq-diff1: x sameAs y and x differentFrom y"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 2 * sizeof(rdf_Triple)), .len = 2, .cap = 2 }; _ll.data[0] = dt; _ll.data[1] = diff_triple; _ll; })})};
                            }
                        }
                    }
                }
            }
        } else if (!_mv_156.has_value) {
        }
        __auto_type _mv_157 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(different_from)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_157.has_value) {
            __auto_type pred_triples = _mv_157.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type x = rdf_triple_subject(dt);
                            __auto_type y = rdf_triple_object(dt);
                            __auto_type same_triple = rdf_make_triple(arena, x, same_as, y);
                            if (rdf_indexed_graph_contains(g, same_triple)) {
                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("eq-diff1: x sameAs y and x differentFrom y"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 2 * sizeof(rdf_Triple)), .len = 2, .cap = 2 }; _ll.data[0] = dt; _ll.data[1] = same_triple; _ll; })})};
                            }
                        }
                    }
                }
            }
        } else if (!_mv_157.has_value) {
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (string_len(r.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some r) (> (string-len (. r reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 2); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 2)))");
    return _retval;
}

slop_option_types_InconsistencyReport eq_eq_diff2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type ad_class = rdf_make_iri(arena, vocab_OWL_ALL_DIFFERENT);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type members_pred = rdf_make_iri(arena, vocab_OWL_MEMBERS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type ad_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = ad_class});
            {
                __auto_type _coll = ad_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type ad_triple = _coll.data[_i];
                    {
                        __auto_type ad_node = rdf_triple_subject(ad_triple);
                        {
                            __auto_type m_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = ad_node}, (slop_option_rdf_Term){.has_value = 1, .value = members_pred}, no_term);
                            {
                                __auto_type _coll = m_triples;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type m_triple = _coll.data[_i];
                                    {
                                        __auto_type list_head = rdf_triple_object(m_triple);
                                        __auto_type members = rdf_list_elements_indexed(arena, g, list_head);
                                        {
                                            __auto_type _coll = members;
                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                __auto_type zi = _coll.data[_i];
                                                {
                                                    __auto_type _coll = members;
                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                        __auto_type zj = _coll.data[_i];
                                                        if (!(rdf_term_eq(zi, zj))) {
                                                            {
                                                                __auto_type same_triple = rdf_make_triple(arena, zi, same_as, zj);
                                                                if (rdf_indexed_graph_contains(g, same_triple)) {
                                                                    return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("eq-diff2: members of AllDifferent are sameAs"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 2 * sizeof(rdf_Triple)), .len = 2, .cap = 2 }; _ll.data[0] = same_triple; _ll.data[1] = ad_triple; _ll; })})};
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (string_len(r.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some r) (> (string-len (. r reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 2); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 2)))");
    return _retval;
}

slop_option_types_InconsistencyReport eq_eq_diff3(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type ad_class = rdf_make_iri(arena, vocab_OWL_ALL_DIFFERENT);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type distinct_pred = rdf_make_iri(arena, vocab_OWL_DISTINCT_MEMBERS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type ad_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = ad_class});
            {
                __auto_type _coll = ad_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type ad_triple = _coll.data[_i];
                    {
                        __auto_type ad_node = rdf_triple_subject(ad_triple);
                        {
                            __auto_type d_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = ad_node}, (slop_option_rdf_Term){.has_value = 1, .value = distinct_pred}, no_term);
                            {
                                __auto_type _coll = d_triples;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type d_triple = _coll.data[_i];
                                    {
                                        __auto_type list_head = rdf_triple_object(d_triple);
                                        __auto_type members = rdf_list_elements_indexed(arena, g, list_head);
                                        {
                                            __auto_type _coll = members;
                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                __auto_type zi = _coll.data[_i];
                                                {
                                                    __auto_type _coll = members;
                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                        __auto_type zj = _coll.data[_i];
                                                        if (!(rdf_term_eq(zi, zj))) {
                                                            {
                                                                __auto_type same_triple = rdf_make_triple(arena, zi, same_as, zj);
                                                                if (rdf_indexed_graph_contains(g, same_triple)) {
                                                                    return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("eq-diff3: distinctMembers of AllDifferent are sameAs"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 2 * sizeof(rdf_Triple)), .len = 2, .cap = 2 }; _ll.data[0] = same_triple; _ll.data[1] = ad_triple; _ll; })})};
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (string_len(r.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some r) (> (string-len (. r reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 2); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 2)))");
    return _retval;
}

slop_list_rdf_Triple eq_eq_ref(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        {
            __auto_type _coll = delta.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type dt = _coll.data[_i];
                {
                    __auto_type s = rdf_triple_subject(dt);
                    __auto_type p = rdf_triple_predicate(dt);
                    __auto_type o = rdf_triple_object(dt);
                    {
                        __auto_type s_self = rdf_make_triple(arena, s, same_as, s);
                        if (!(rdf_indexed_graph_contains(g, s_self))) {
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (s_self); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                    {
                        __auto_type p_self = rdf_make_triple(arena, p, same_as, p);
                        if (!(rdf_indexed_graph_contains(g, p_self))) {
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (p_self); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                    {
                        __auto_type o_self = rdf_make_triple(arena, o, same_as, o);
                        if (!(rdf_indexed_graph_contains(g, o_self))) {
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (o_self); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

