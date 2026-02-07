#include "../runtime/slop_runtime.h"
#include "slop_scm.h"

static const slop_string scm_EX_PERSON = SLOP_STR("http://example.org/Person");
static const slop_string scm_EX_HUMAN = SLOP_STR("http://example.org/Human");
static const slop_string scm_EX_A = SLOP_STR("http://example.org/A");
static const slop_string scm_EX_B = SLOP_STR("http://example.org/B");
static const slop_string scm_EX_C = SLOP_STR("http://example.org/C");
static const slop_string scm_EX_HAS_PARENT = SLOP_STR("http://example.org/hasParent");
static const slop_string scm_EX_HAS_FATHER = SLOP_STR("http://example.org/hasFather");
static const slop_string scm_EX_HAS_ANCESTOR = SLOP_STR("http://example.org/hasAncestor");

index_IndexedGraph scm_fixture_g_with_class(slop_arena* arena);
index_IndexedGraph scm_fixture_g_chain(slop_arena* arena);
index_IndexedGraph scm_fixture_g_equiv(slop_arena* arena);
index_IndexedGraph scm_fixture_g_prop_chain(slop_arena* arena);
index_IndexedGraph scm_fixture_g_domain(slop_arena* arena);
types_Delta scm_fixture_delta_new_link(slop_arena* arena);
types_Delta scm_fixture_delta_empty(slop_arena* arena);
types_Delta scm_fixture_delta_with_class(slop_arena* arena);
types_Delta scm_fixture_delta_equiv(slop_arena* arena);
types_Delta scm_fixture_delta_subprop(slop_arena* arena);
slop_result_types_Delta_types_InconsistencyReport scm_apply_scm_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_cls(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_sco(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_op(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_spo(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dom1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dom2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_rng1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_rng2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

typedef struct { slop_arena* arena; rdf_Term c1; rdf_Term subclass_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_118_env_t;

static void scm__lambda_118(scm__lambda_118_env_t* _env, rdf_Triple super_triple) { ({ __auto_type c3 = rdf_triple_object(super_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->c1, _env->subclass_pred, c3); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term subclass_pred; rdf_Term c2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_119_env_t;

static void scm__lambda_119(scm__lambda_119_env_t* _env, rdf_Triple sub_triple) { ({ __auto_type c0 = rdf_triple_subject(sub_triple); __auto_type inferred = rdf_make_triple(_env->arena, c0, _env->subclass_pred, _env->c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p1; rdf_Term subprop_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_125_env_t;

static void scm__lambda_125(scm__lambda_125_env_t* _env, rdf_Triple super_triple) { ({ __auto_type p3 = rdf_triple_object(super_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->p1, _env->subprop_pred, p3); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term subprop_pred; rdf_Term p2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_126_env_t;

static void scm__lambda_126(scm__lambda_126_env_t* _env, rdf_Triple sub_triple) { ({ __auto_type p0 = rdf_triple_subject(sub_triple); __auto_type inferred = rdf_make_triple(_env->arena, p0, _env->subprop_pred, _env->p2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p1; rdf_Term domain_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_130_env_t;

static void scm__lambda_130(scm__lambda_130_env_t* _env, rdf_Triple dom_triple) { ({ __auto_type c = rdf_triple_object(dom_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->p1, _env->domain_pred, c); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term domain_pred; rdf_Term c2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_132_env_t;

static void scm__lambda_132(scm__lambda_132_env_t* _env, rdf_Triple dom_triple) { ({ __auto_type p = rdf_triple_subject(dom_triple); __auto_type inferred = rdf_make_triple(_env->arena, p, _env->domain_pred, _env->c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p1; rdf_Term range_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_134_env_t;

static void scm__lambda_134(scm__lambda_134_env_t* _env, rdf_Triple rng_triple) { ({ __auto_type c = rdf_triple_object(rng_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->p1, _env->range_pred, c); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term range_pred; rdf_Term c2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_136_env_t;

static void scm__lambda_136(scm__lambda_136_env_t* _env, rdf_Triple rng_triple) { ({ __auto_type p = rdf_triple_subject(rng_triple); __auto_type inferred = rdf_make_triple(_env->arena, p, _env->range_pred, _env->c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

index_IndexedGraph scm_fixture_g_with_class(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type class_type = rdf_make_iri(arena, vocab_OWL_CLASS);
        __auto_type person = rdf_make_iri(arena, scm_EX_PERSON);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, person, type_pred, class_type));
        return g;
    }
}

index_IndexedGraph scm_fixture_g_chain(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type a = rdf_make_iri(arena, scm_EX_A);
        __auto_type b = rdf_make_iri(arena, scm_EX_B);
        __auto_type c = rdf_make_iri(arena, scm_EX_C);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, a, subclass_pred, b));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, b, subclass_pred, c));
        return g;
    }
}

index_IndexedGraph scm_fixture_g_equiv(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type human = rdf_make_iri(arena, scm_EX_HUMAN);
        __auto_type person = rdf_make_iri(arena, scm_EX_PERSON);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, human, equiv_pred, person));
        return g;
    }
}

index_IndexedGraph scm_fixture_g_prop_chain(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type has_father = rdf_make_iri(arena, scm_EX_HAS_FATHER);
        __auto_type has_parent = rdf_make_iri(arena, scm_EX_HAS_PARENT);
        __auto_type has_ancestor = rdf_make_iri(arena, scm_EX_HAS_ANCESTOR);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_father, subprop_pred, has_parent));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_parent, subprop_pred, has_ancestor));
        return g;
    }
}

index_IndexedGraph scm_fixture_g_domain(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type has_parent = rdf_make_iri(arena, scm_EX_HAS_PARENT);
        __auto_type has_father = rdf_make_iri(arena, scm_EX_HAS_FATHER);
        __auto_type person = rdf_make_iri(arena, scm_EX_PERSON);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_parent, domain_pred, person));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_father, subprop_pred, has_parent));
        return g;
    }
}

types_Delta scm_fixture_delta_new_link(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type b = rdf_make_iri(arena, scm_EX_B);
        __auto_type c = rdf_make_iri(arena, scm_EX_C);
        d = types_delta_add(arena, d, rdf_make_triple(arena, b, subclass_pred, c));
        return d;
    }
}

types_Delta scm_fixture_delta_empty(slop_arena* arena) {
    return types_make_delta(arena, 0);
}

types_Delta scm_fixture_delta_with_class(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type class_type = rdf_make_iri(arena, vocab_OWL_CLASS);
        __auto_type person = rdf_make_iri(arena, scm_EX_PERSON);
        d = types_delta_add(arena, d, rdf_make_triple(arena, person, type_pred, class_type));
        return d;
    }
}

types_Delta scm_fixture_delta_equiv(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type human = rdf_make_iri(arena, scm_EX_HUMAN);
        __auto_type person = rdf_make_iri(arena, scm_EX_PERSON);
        d = types_delta_add(arena, d, rdf_make_triple(arena, human, equiv_pred, person));
        return d;
    }
}

types_Delta scm_fixture_delta_subprop(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type has_father = rdf_make_iri(arena, scm_EX_HAS_FATHER);
        __auto_type has_parent = rdf_make_iri(arena, scm_EX_HAS_PARENT);
        d = types_delta_add(arena, d, rdf_make_triple(arena, has_father, subprop_pred, has_parent));
        return d;
    }
}

slop_result_types_Delta_types_InconsistencyReport scm_apply_scm_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type result = types_make_delta(arena, next_iter);
        {
            __auto_type _coll = scm_scm_cls(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_sco(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_eqc1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_eqc2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_op(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_dp(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_spo(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_eqp1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_eqp2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_dom1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_dom2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_rng1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_rng2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        _retval = ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = true, .data.ok = result });
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == (delta.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) (+ (. delta iteration) 1))) ((error _) true))");
    return _retval;
}

slop_list_rdf_Triple scm_scm_cls(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type class_type = rdf_make_iri(arena, vocab_OWL_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_116 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_116.has_value) {
            __auto_type pred_triples = _mv_116.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        if (rdf_term_eq(rdf_triple_object(dt), class_type)) {
                            {
                                __auto_type class = rdf_triple_subject(dt);
                                {
                                    __auto_type reflexive = rdf_make_triple(arena, class, subclass_pred, class);
                                    if (!(rdf_indexed_graph_contains(g, reflexive))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (reflexive); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                                {
                                    __auto_type to_thing = rdf_make_triple(arena, class, subclass_pred, thing);
                                    if (!(rdf_indexed_graph_contains(g, to_thing))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (to_thing); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_116.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_sco(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_117 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_117.has_value) {
            __auto_type pred_triples = _mv_117.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = c2}, (slop_option_rdf_Term){.has_value = 1, .value = subclass_pred}, no_term, ({ scm__lambda_118_env_t* scm__lambda_118_env = (scm__lambda_118_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_118_env_t)); *scm__lambda_118_env = (scm__lambda_118_env_t){ .arena = arena, .c1 = c1, .subclass_pred = subclass_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_118, (void*)scm__lambda_118_env }; }));
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = subclass_pred}, (slop_option_rdf_Term){.has_value = 1, .value = c1}, ({ scm__lambda_119_env_t* scm__lambda_119_env = (scm__lambda_119_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_119_env_t)); *scm__lambda_119_env = (scm__lambda_119_env_t){ .arena = arena, .subclass_pred = subclass_pred, .c2 = c2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_119, (void*)scm__lambda_119_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_117.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_120 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_120.has_value) {
            __auto_type pred_triples = _mv_120.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            __auto_type inferred = rdf_make_triple(arena, c1, subclass_pred, c2);
                            if (!(rdf_indexed_graph_contains(g, inferred))) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        }
                    }
                }
            }
        } else if (!_mv_120.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_121 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_121.has_value) {
            __auto_type pred_triples = _mv_121.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            __auto_type inferred = rdf_make_triple(arena, c2, subclass_pred, c1);
                            if (!(rdf_indexed_graph_contains(g, inferred))) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        }
                    }
                }
            }
        } else if (!_mv_121.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_op(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type op_type = rdf_make_iri(arena, vocab_OWL_OBJECT_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_122 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_122.has_value) {
            __auto_type pred_triples = _mv_122.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        if (rdf_term_eq(rdf_triple_object(dt), op_type)) {
                            {
                                __auto_type prop = rdf_triple_subject(dt);
                                __auto_type reflexive = rdf_make_triple(arena, prop, subprop_pred, prop);
                                if (!(rdf_indexed_graph_contains(g, reflexive))) {
                                    ({ __auto_type _lst_p = &(result); __auto_type _item = (reflexive); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_122.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_dp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type dp_type = rdf_make_iri(arena, vocab_OWL_DATATYPE_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_123 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_123.has_value) {
            __auto_type pred_triples = _mv_123.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        if (rdf_term_eq(rdf_triple_object(dt), dp_type)) {
                            {
                                __auto_type prop = rdf_triple_subject(dt);
                                __auto_type reflexive = rdf_make_triple(arena, prop, subprop_pred, prop);
                                if (!(rdf_indexed_graph_contains(g, reflexive))) {
                                    ({ __auto_type _lst_p = &(result); __auto_type _item = (reflexive); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_123.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_spo(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_124 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_124.has_value) {
            __auto_type pred_triples = _mv_124.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p2}, (slop_option_rdf_Term){.has_value = 1, .value = subprop_pred}, no_term, ({ scm__lambda_125_env_t* scm__lambda_125_env = (scm__lambda_125_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_125_env_t)); *scm__lambda_125_env = (scm__lambda_125_env_t){ .arena = arena, .p1 = p1, .subprop_pred = subprop_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_125, (void*)scm__lambda_125_env }; }));
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = subprop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = p1}, ({ scm__lambda_126_env_t* scm__lambda_126_env = (scm__lambda_126_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_126_env_t)); *scm__lambda_126_env = (scm__lambda_126_env_t){ .arena = arena, .subprop_pred = subprop_pred, .p2 = p2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_126, (void*)scm__lambda_126_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_124.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqp1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_127 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_127.has_value) {
            __auto_type pred_triples = _mv_127.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            __auto_type inferred = rdf_make_triple(arena, p1, subprop_pred, p2);
                            if (!(rdf_indexed_graph_contains(g, inferred))) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        }
                    }
                }
            }
        } else if (!_mv_127.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqp2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_128 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_128.has_value) {
            __auto_type pred_triples = _mv_128.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            __auto_type inferred = rdf_make_triple(arena, p2, subprop_pred, p1);
                            if (!(rdf_indexed_graph_contains(g, inferred))) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        }
                    }
                }
            }
        } else if (!_mv_128.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_dom1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_129 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_129.has_value) {
            __auto_type pred_triples = _mv_129.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p2}, (slop_option_rdf_Term){.has_value = 1, .value = domain_pred}, no_term, ({ scm__lambda_130_env_t* scm__lambda_130_env = (scm__lambda_130_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_130_env_t)); *scm__lambda_130_env = (scm__lambda_130_env_t){ .arena = arena, .p1 = p1, .domain_pred = domain_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_130, (void*)scm__lambda_130_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_129.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_DOMAIN)), "(all-triples-have-predicate $result RDFS_DOMAIN)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_dom2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_131 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_131.has_value) {
            __auto_type pred_triples = _mv_131.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = domain_pred}, (slop_option_rdf_Term){.has_value = 1, .value = c1}, ({ scm__lambda_132_env_t* scm__lambda_132_env = (scm__lambda_132_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_132_env_t)); *scm__lambda_132_env = (scm__lambda_132_env_t){ .arena = arena, .domain_pred = domain_pred, .c2 = c2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_132, (void*)scm__lambda_132_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_131.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_DOMAIN)), "(all-triples-have-predicate $result RDFS_DOMAIN)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_rng1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type range_pred = rdf_make_iri(arena, vocab_RDFS_RANGE);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_133 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_133.has_value) {
            __auto_type pred_triples = _mv_133.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p2}, (slop_option_rdf_Term){.has_value = 1, .value = range_pred}, no_term, ({ scm__lambda_134_env_t* scm__lambda_134_env = (scm__lambda_134_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_134_env_t)); *scm__lambda_134_env = (scm__lambda_134_env_t){ .arena = arena, .p1 = p1, .range_pred = range_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_134, (void*)scm__lambda_134_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_133.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_RANGE)), "(all-triples-have-predicate $result RDFS_RANGE)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_rng2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type range_pred = rdf_make_iri(arena, vocab_RDFS_RANGE);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_135 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_135.has_value) {
            __auto_type pred_triples = _mv_135.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = range_pred}, (slop_option_rdf_Term){.has_value = 1, .value = c1}, ({ scm__lambda_136_env_t* scm__lambda_136_env = (scm__lambda_136_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_136_env_t)); *scm__lambda_136_env = (scm__lambda_136_env_t){ .arena = arena, .range_pred = range_pred, .c2 = c2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_136, (void*)scm__lambda_136_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_135.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_RANGE)), "(all-triples-have-predicate $result RDFS_RANGE)");
    return _retval;
}

