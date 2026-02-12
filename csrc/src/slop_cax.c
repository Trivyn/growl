#include "../runtime/slop_runtime.h"
#include "slop_cax.h"

static const slop_string cax_EX_ALICE = SLOP_STR("http://example.org/alice");
static const slop_string cax_EX_BOB = SLOP_STR("http://example.org/bob");
static const slop_string cax_EX_FIDO = SLOP_STR("http://example.org/fido");
static const slop_string cax_EX_PERSON = SLOP_STR("http://example.org/Person");
static const slop_string cax_EX_AGENT = SLOP_STR("http://example.org/Agent");
static const slop_string cax_EX_HUMAN = SLOP_STR("http://example.org/Human");
static const slop_string cax_EX_CAT = SLOP_STR("http://example.org/Cat");
static const slop_string cax_EX_DOG = SLOP_STR("http://example.org/Dog");
static const slop_string cax_EX_BIRD = SLOP_STR("http://example.org/Bird");

index_IndexedGraph cax_fixture_g_with_subclass(slop_arena* arena);
index_IndexedGraph cax_fixture_g_with_equiv(slop_arena* arena);
index_IndexedGraph cax_fixture_g_disjoint_violation(slop_arena* arena);
index_IndexedGraph cax_fixture_g_consistent(slop_arena* arena);
types_Delta cax_fixture_delta_with_type(slop_arena* arena);
types_Delta cax_fixture_delta_with_human(slop_arena* arena);
types_Delta cax_fixture_delta_with_person(slop_arena* arena);
types_Delta cax_fixture_delta_empty(slop_arena* arena);
types_Delta cax_fixture_delta_fido_cat(slop_arena* arena);
types_Delta cax_fixture_delta_fido_dog(slop_arena* arena);
index_IndexedGraph cax_fixture_g_all_disjoint(slop_arena* arena);
slop_result_types_Delta_types_InconsistencyReport cax_apply_cax_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast);
slop_list_rdf_Triple cax_cax_sco(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cax_cax_eqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cax_cax_eqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport cax_cax_dw(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport cax_cax_adc(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

typedef struct { slop_arena* arena; rdf_Term individual; rdf_Term type_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } cax__lambda_238_env_t;

static void cax__lambda_238(cax__lambda_238_env_t* _env, rdf_Triple sc_triple) { ({ __auto_type class2 = rdf_triple_object(sc_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->individual, _env->type_pred, class2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term type_pred; rdf_Term class2; index_IndexedGraph g; slop_list_rdf_Triple* result; } cax__lambda_240_env_t;

static void cax__lambda_240(cax__lambda_240_env_t* _env, rdf_Triple t_triple) { ({ __auto_type individual = rdf_triple_subject(t_triple); __auto_type inferred = rdf_make_triple(_env->arena, individual, _env->type_pred, _env->class2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term individual; rdf_Term type_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } cax__lambda_242_env_t;

static void cax__lambda_242(cax__lambda_242_env_t* _env, rdf_Triple eq_triple) { ({ __auto_type class2 = rdf_triple_object(eq_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->individual, _env->type_pred, class2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term individual; rdf_Term type_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } cax__lambda_244_env_t;

static void cax__lambda_244(cax__lambda_244_env_t* _env, rdf_Triple eq_triple) { ({ __auto_type class1 = rdf_triple_subject(eq_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->individual, _env->type_pred, class1); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

index_IndexedGraph cax_fixture_g_with_subclass(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type person = rdf_make_iri(arena, cax_EX_PERSON);
        __auto_type agent = rdf_make_iri(arena, cax_EX_AGENT);
        __auto_type alice = rdf_make_iri(arena, cax_EX_ALICE);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, person, subclass_pred, agent));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, person));
        return g;
    }
}

index_IndexedGraph cax_fixture_g_with_equiv(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type human = rdf_make_iri(arena, cax_EX_HUMAN);
        __auto_type person = rdf_make_iri(arena, cax_EX_PERSON);
        __auto_type alice = rdf_make_iri(arena, cax_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, cax_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, human, equiv_pred, person));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, human));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, bob, type_pred, person));
        return g;
    }
}

index_IndexedGraph cax_fixture_g_disjoint_violation(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type disjoint_pred = rdf_make_iri(arena, vocab_OWL_DISJOINT_WITH);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type cat = rdf_make_iri(arena, cax_EX_CAT);
        __auto_type dog = rdf_make_iri(arena, cax_EX_DOG);
        __auto_type fido = rdf_make_iri(arena, cax_EX_FIDO);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, cat, disjoint_pred, dog));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, fido, type_pred, cat));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, fido, type_pred, dog));
        return g;
    }
}

index_IndexedGraph cax_fixture_g_consistent(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type disjoint_pred = rdf_make_iri(arena, vocab_OWL_DISJOINT_WITH);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type cat = rdf_make_iri(arena, cax_EX_CAT);
        __auto_type dog = rdf_make_iri(arena, cax_EX_DOG);
        __auto_type fido = rdf_make_iri(arena, cax_EX_FIDO);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, cat, disjoint_pred, dog));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, fido, type_pred, dog));
        return g;
    }
}

types_Delta cax_fixture_delta_with_type(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type alice = rdf_make_iri(arena, cax_EX_ALICE);
        __auto_type person = rdf_make_iri(arena, cax_EX_PERSON);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, person));
        return d;
    }
}

types_Delta cax_fixture_delta_with_human(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type alice = rdf_make_iri(arena, cax_EX_ALICE);
        __auto_type human = rdf_make_iri(arena, cax_EX_HUMAN);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, human));
        return d;
    }
}

types_Delta cax_fixture_delta_with_person(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type bob = rdf_make_iri(arena, cax_EX_BOB);
        __auto_type person = rdf_make_iri(arena, cax_EX_PERSON);
        d = types_delta_add(arena, d, rdf_make_triple(arena, bob, type_pred, person));
        return d;
    }
}

types_Delta cax_fixture_delta_empty(slop_arena* arena) {
    return types_make_delta(arena, 0);
}

types_Delta cax_fixture_delta_fido_cat(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type fido = rdf_make_iri(arena, cax_EX_FIDO);
        __auto_type cat = rdf_make_iri(arena, cax_EX_CAT);
        d = types_delta_add(arena, d, rdf_make_triple(arena, fido, type_pred, cat));
        return d;
    }
}

types_Delta cax_fixture_delta_fido_dog(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type fido = rdf_make_iri(arena, cax_EX_FIDO);
        __auto_type dog = rdf_make_iri(arena, cax_EX_DOG);
        d = types_delta_add(arena, d, rdf_make_triple(arena, fido, type_pred, dog));
        return d;
    }
}

index_IndexedGraph cax_fixture_g_all_disjoint(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type members_pred = rdf_make_iri(arena, vocab_OWL_MEMBERS);
        __auto_type first_pred = rdf_make_iri(arena, vocab_RDF_FIRST);
        __auto_type rest_pred = rdf_make_iri(arena, vocab_RDF_REST);
        __auto_type nil_term = rdf_make_iri(arena, vocab_RDF_NIL);
        __auto_type adc_class = rdf_make_iri(arena, vocab_OWL_ALL_DISJOINT_CLASSES);
        __auto_type cat = rdf_make_iri(arena, cax_EX_CAT);
        __auto_type dog = rdf_make_iri(arena, cax_EX_DOG);
        __auto_type bird = rdf_make_iri(arena, cax_EX_BIRD);
        __auto_type fido = rdf_make_iri(arena, cax_EX_FIDO);
        __auto_type adc_node = rdf_make_blank(arena, 1);
        __auto_type list1 = rdf_make_blank(arena, 2);
        __auto_type list2 = rdf_make_blank(arena, 3);
        __auto_type list3 = rdf_make_blank(arena, 4);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, adc_node, type_pred, adc_class));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, adc_node, members_pred, list1));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, list1, first_pred, cat));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, list1, rest_pred, list2));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, list2, first_pred, dog));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, list2, rest_pred, list3));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, list3, first_pred, bird));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, list3, rest_pred, nil_term));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, fido, type_pred, cat));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, fido, type_pred, dog));
        return g;
    }
}

slop_result_types_Delta_types_InconsistencyReport cax_apply_cax_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type result = types_make_delta(arena, next_iter);
        {
            __auto_type _coll = cax_cax_sco(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cax_cax_eqc1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cax_cax_eqc2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        __auto_type _mv_235 = cax_cax_dw(arena, g, delta);
        if (_mv_235.has_value) {
            __auto_type report = _mv_235.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_235.has_value) {
        }
        __auto_type _mv_236 = cax_cax_adc(arena, g, delta);
        if (_mv_236.has_value) {
            __auto_type report = _mv_236.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_236.has_value) {
        }
        _retval = ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = true, .data.ok = result });
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == (delta.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) (+ (. delta iteration) 1))) ((error _) true))");
    return _retval;
}

slop_list_rdf_Triple cax_cax_sco(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_237 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_237.has_value) {
            __auto_type pred_triples = _mv_237.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type individual = rdf_triple_subject(dt);
                            __auto_type class1 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = class1}, (slop_option_rdf_Term){.has_value = 1, .value = subclass_pred}, no_term, ({ cax__lambda_238_env_t* cax__lambda_238_env = (cax__lambda_238_env_t*)slop_arena_alloc(arena, sizeof(cax__lambda_238_env_t)); *cax__lambda_238_env = (cax__lambda_238_env_t){ .arena = arena, .individual = individual, .type_pred = type_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)cax__lambda_238, (void*)cax__lambda_238_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_237.has_value) {
        }
        __auto_type _mv_239 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_239.has_value) {
            __auto_type pred_triples = _mv_239.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type class1 = rdf_triple_subject(dt);
                            __auto_type class2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = class1}, ({ cax__lambda_240_env_t* cax__lambda_240_env = (cax__lambda_240_env_t*)slop_arena_alloc(arena, sizeof(cax__lambda_240_env_t)); *cax__lambda_240_env = (cax__lambda_240_env_t){ .arena = arena, .type_pred = type_pred, .class2 = class2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)cax__lambda_240, (void*)cax__lambda_240_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_239.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cax_cax_eqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_241 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_241.has_value) {
            __auto_type pred_triples = _mv_241.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type individual = rdf_triple_subject(dt);
                            __auto_type class1 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = class1}, (slop_option_rdf_Term){.has_value = 1, .value = equiv_pred}, no_term, ({ cax__lambda_242_env_t* cax__lambda_242_env = (cax__lambda_242_env_t*)slop_arena_alloc(arena, sizeof(cax__lambda_242_env_t)); *cax__lambda_242_env = (cax__lambda_242_env_t){ .arena = arena, .individual = individual, .type_pred = type_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)cax__lambda_242, (void*)cax__lambda_242_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_241.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cax_cax_eqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_243 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_243.has_value) {
            __auto_type pred_triples = _mv_243.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type individual = rdf_triple_subject(dt);
                            __auto_type class2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = equiv_pred}, (slop_option_rdf_Term){.has_value = 1, .value = class2}, ({ cax__lambda_244_env_t* cax__lambda_244_env = (cax__lambda_244_env_t*)slop_arena_alloc(arena, sizeof(cax__lambda_244_env_t)); *cax__lambda_244_env = (cax__lambda_244_env_t){ .arena = arena, .individual = individual, .type_pred = type_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)cax__lambda_244, (void*)cax__lambda_244_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_243.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_option_types_InconsistencyReport cax_cax_dw(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type disjoint_pred = rdf_make_iri(arena, vocab_OWL_DISJOINT_WITH);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type _mv_245 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_245.has_value) {
            __auto_type type_triples = _mv_245.value;
            {
                slop_map* _coll = (slop_map*)type_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type individual = rdf_triple_subject(dt);
                            __auto_type class1 = rdf_triple_object(dt);
                            {
                                __auto_type dj_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = class1}, (slop_option_rdf_Term){.has_value = 1, .value = disjoint_pred}, no_term);
                                {
                                    __auto_type _coll = dj_triples;
                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                        __auto_type dj_triple = _coll.data[_i];
                                        {
                                            __auto_type class2 = rdf_triple_object(dj_triple);
                                            __auto_type type2_triple = rdf_make_triple(arena, individual, type_pred, class2);
                                            if (rdf_indexed_graph_contains(g, type2_triple)) {
                                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cax-dw: individual is instance of two disjoint classes"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = type2_triple; _ll.data[2] = dj_triple; _ll; })})};
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            {
                slop_map* _coll = (slop_map*)type_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type individual = rdf_triple_subject(dt);
                            __auto_type class2 = rdf_triple_object(dt);
                            {
                                __auto_type dj_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = disjoint_pred}, (slop_option_rdf_Term){.has_value = 1, .value = class2});
                                {
                                    __auto_type _coll = dj_triples;
                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                        __auto_type dj_triple = _coll.data[_i];
                                        {
                                            __auto_type class1 = rdf_triple_subject(dj_triple);
                                            __auto_type type1_triple = rdf_make_triple(arena, individual, type_pred, class1);
                                            if (rdf_indexed_graph_contains(g, type1_triple)) {
                                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cax-dw: individual is instance of two disjoint classes"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = type1_triple; _ll.data[2] = dj_triple; _ll; })})};
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_245.has_value) {
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type report = _mv.value; (string_len(report.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some report) (> (string-len (. report reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 3); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 3)))");
    return _retval;
}

slop_option_types_InconsistencyReport cax_cax_adc(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type adc_class = rdf_make_iri(arena, vocab_OWL_ALL_DISJOINT_CLASSES);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type members_pred = rdf_make_iri(arena, vocab_OWL_MEMBERS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type adc_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = adc_class});
            {
                __auto_type _coll = adc_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type adc_triple = _coll.data[_i];
                    {
                        __auto_type adc_node = rdf_triple_subject(adc_triple);
                        {
                            __auto_type m_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = adc_node}, (slop_option_rdf_Term){.has_value = 1, .value = members_pred}, no_term);
                            {
                                __auto_type _coll = m_triples;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type m_triple = _coll.data[_i];
                                    {
                                        __auto_type list_head = rdf_triple_object(m_triple);
                                        __auto_type classes = rdf_list_elements_indexed(arena, g, list_head);
                                        {
                                            __auto_type _coll = classes;
                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                __auto_type class_a = _coll.data[_i];
                                                {
                                                    __auto_type _coll = classes;
                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                        __auto_type class_b = _coll.data[_i];
                                                        if (!(rdf_term_eq(class_a, class_b))) {
                                                            {
                                                                __auto_type inst_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = class_a});
                                                                {
                                                                    __auto_type _coll = inst_triples;
                                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                        __auto_type inst_triple = _coll.data[_i];
                                                                        {
                                                                            __auto_type individual = rdf_triple_subject(inst_triple);
                                                                            __auto_type class_b_type_triple = rdf_make_triple(arena, individual, type_pred, class_b);
                                                                            if (rdf_indexed_graph_contains(g, class_b_type_triple)) {
                                                                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cax-adc: individual is instance of two classes in AllDisjointClasses"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = inst_triple; _ll.data[1] = class_b_type_triple; _ll.data[2] = adc_triple; _ll; })})};
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
                }
            }
        }
    }
    return (slop_option_types_InconsistencyReport){.has_value = false};
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type report = _mv.value; (string_len(report.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some report) (> (string-len (. report reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 2); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 2)))");
    return _retval;
}

