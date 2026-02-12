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
slop_list_rdf_Triple scm_scm_eqc1b(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_op(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_spo(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp1b(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dom2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dom1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_rng2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_rng1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_int(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_uni(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_svf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_svf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_avf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_avf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_hv(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

typedef struct { slop_arena* arena; rdf_Term c1; rdf_Term subclass_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_190_env_t;

static void scm__lambda_190(scm__lambda_190_env_t* _env, rdf_Triple super_triple) { ({ __auto_type c3 = rdf_triple_object(super_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->c1, _env->subclass_pred, c3); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term subclass_pred; rdf_Term c2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_191_env_t;

static void scm__lambda_191(scm__lambda_191_env_t* _env, rdf_Triple sub_triple) { ({ __auto_type c0 = rdf_triple_subject(sub_triple); __auto_type inferred = rdf_make_triple(_env->arena, c0, _env->subclass_pred, _env->c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p1; rdf_Term subprop_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_198_env_t;

static void scm__lambda_198(scm__lambda_198_env_t* _env, rdf_Triple super_triple) { ({ __auto_type p3 = rdf_triple_object(super_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->p1, _env->subprop_pred, p3); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term subprop_pred; rdf_Term p2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_199_env_t;

static void scm__lambda_199(scm__lambda_199_env_t* _env, rdf_Triple sub_triple) { ({ __auto_type p0 = rdf_triple_subject(sub_triple); __auto_type inferred = rdf_make_triple(_env->arena, p0, _env->subprop_pred, _env->p2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p1; rdf_Term domain_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_204_env_t;

static void scm__lambda_204(scm__lambda_204_env_t* _env, rdf_Triple dom_triple) { ({ __auto_type c = rdf_triple_object(dom_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->p1, _env->domain_pred, c); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term domain_pred; rdf_Term c2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_206_env_t;

static void scm__lambda_206(scm__lambda_206_env_t* _env, rdf_Triple dom_triple) { ({ __auto_type p = rdf_triple_subject(dom_triple); __auto_type inferred = rdf_make_triple(_env->arena, p, _env->domain_pred, _env->c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p1; rdf_Term range_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_208_env_t;

static void scm__lambda_208(scm__lambda_208_env_t* _env, rdf_Triple rng_triple) { ({ __auto_type c = rdf_triple_object(rng_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->p1, _env->range_pred, c); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term range_pred; rdf_Term c2; index_IndexedGraph g; slop_list_rdf_Triple* result; } scm__lambda_210_env_t;

static void scm__lambda_210(scm__lambda_210_env_t* _env, rdf_Triple rng_triple) { ({ __auto_type p = rdf_triple_subject(rng_triple); __auto_type inferred = rdf_make_triple(_env->arena, p, _env->range_pred, _env->c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; index_IndexedGraph g; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_212_env_t;

static void scm__lambda_212(scm__lambda_212_env_t* _env, rdf_Triple int_triple) { ({ __auto_type int_class = rdf_triple_subject(int_triple); __auto_type list_head = rdf_triple_object(int_triple); __auto_type components = rdf_list_elements_indexed(_env->arena, _env->g, list_head); ({ __auto_type _coll = components; for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type comp = _coll.data[_i]; ({ __auto_type inferred = rdf_make_triple(_env->arena, int_class, _env->subclass_pred, comp); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } 0; }); }); }

typedef struct { slop_arena* arena; index_IndexedGraph g; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_214_env_t;

static void scm__lambda_214(scm__lambda_214_env_t* _env, rdf_Triple union_triple) { ({ __auto_type union_class = rdf_triple_subject(union_triple); __auto_type list_head = rdf_triple_object(union_triple); __auto_type components = rdf_list_elements_indexed(_env->arena, _env->g, list_head); ({ __auto_type _coll = components; for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type comp = _coll.data[_i]; ({ __auto_type inferred = rdf_make_triple(_env->arena, comp, _env->subclass_pred, union_class); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } 0; }); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; rdf_Term svf_pred; rdf_Term y2; slop_arena* arena; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_216_env_t;

typedef struct { index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term svf_pred; rdf_Term y2; slop_arena* arena; rdf_Term on_prop_pred; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_217_env_t;

typedef struct { slop_arena* arena; rdf_Term on_prop_pred; rdf_Term p; index_IndexedGraph g; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_218_env_t;

static void scm__lambda_218(scm__lambda_218_env_t* _env, rdf_Triple svf2_triple) { ({ __auto_type c2 = rdf_triple_subject(svf2_triple); ({ __auto_type c2_on_p = rdf_make_triple(_env->arena, c2, _env->on_prop_pred, _env->p); ((rdf_indexed_graph_contains(_env->g, c2_on_p)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->c1, _env->subclass_pred, c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }); }

static void scm__lambda_217(scm__lambda_217_env_t* _env, rdf_Triple prop1_triple) { ({ __auto_type p = rdf_triple_object(prop1_triple); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->svf_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->y2}, ({ scm__lambda_218_env_t* scm__lambda_218_env = (scm__lambda_218_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_218_env_t)); *scm__lambda_218_env = (scm__lambda_218_env_t){ .arena = _env->arena, .on_prop_pred = _env->on_prop_pred, .p = p, .g = _env->g, .c1 = _env->c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_218, (void*)scm__lambda_218_env }; })); }); }

static void scm__lambda_216(scm__lambda_216_env_t* _env, rdf_Triple svf1_triple) { ({ __auto_type c1 = rdf_triple_subject(svf1_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = c1}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ scm__lambda_217_env_t* scm__lambda_217_env = (scm__lambda_217_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_217_env_t)); *scm__lambda_217_env = (scm__lambda_217_env_t){ .g = _env->g, .no_term = _env->no_term, .svf_pred = _env->svf_pred, .y2 = _env->y2, .arena = _env->arena, .on_prop_pred = _env->on_prop_pred, .c1 = c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_217, (void*)scm__lambda_217_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term svf_pred; slop_option_rdf_Term no_term; rdf_Term on_prop_pred; rdf_Term p2; slop_arena* arena; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_220_env_t;

typedef struct { index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term on_prop_pred; rdf_Term p2; slop_arena* arena; rdf_Term svf_pred; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_221_env_t;

typedef struct { slop_arena* arena; rdf_Term svf_pred; rdf_Term y; index_IndexedGraph g; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_222_env_t;

static void scm__lambda_222(scm__lambda_222_env_t* _env, rdf_Triple prop2_triple) { ({ __auto_type c2 = rdf_triple_subject(prop2_triple); __auto_type c2_svf_y = rdf_make_triple(_env->arena, c2, _env->svf_pred, _env->y); ((rdf_indexed_graph_contains(_env->g, c2_svf_y)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->c1, _env->subclass_pred, c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

static void scm__lambda_221(scm__lambda_221_env_t* _env, rdf_Triple svf1_triple) { ({ __auto_type y = rdf_triple_object(svf1_triple); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->p2}, ({ scm__lambda_222_env_t* scm__lambda_222_env = (scm__lambda_222_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_222_env_t)); *scm__lambda_222_env = (scm__lambda_222_env_t){ .arena = _env->arena, .svf_pred = _env->svf_pred, .y = y, .g = _env->g, .c1 = _env->c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_222, (void*)scm__lambda_222_env }; })); }); }

static void scm__lambda_220(scm__lambda_220_env_t* _env, rdf_Triple prop1_triple) { ({ __auto_type c1 = rdf_triple_subject(prop1_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = c1}, (slop_option_rdf_Term){.has_value = 1, .value = _env->svf_pred}, _env->no_term, ({ scm__lambda_221_env_t* scm__lambda_221_env = (scm__lambda_221_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_221_env_t)); *scm__lambda_221_env = (scm__lambda_221_env_t){ .g = _env->g, .no_term = _env->no_term, .on_prop_pred = _env->on_prop_pred, .p2 = _env->p2, .arena = _env->arena, .svf_pred = _env->svf_pred, .c1 = c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_221, (void*)scm__lambda_221_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; rdf_Term avf_pred; rdf_Term y2; slop_arena* arena; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_224_env_t;

typedef struct { index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term avf_pred; rdf_Term y2; slop_arena* arena; rdf_Term on_prop_pred; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_225_env_t;

typedef struct { slop_arena* arena; rdf_Term on_prop_pred; rdf_Term p; index_IndexedGraph g; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_226_env_t;

static void scm__lambda_226(scm__lambda_226_env_t* _env, rdf_Triple avf2_triple) { ({ __auto_type c2 = rdf_triple_subject(avf2_triple); ({ __auto_type c2_on_p = rdf_make_triple(_env->arena, c2, _env->on_prop_pred, _env->p); ((rdf_indexed_graph_contains(_env->g, c2_on_p)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->c1, _env->subclass_pred, c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }); }

static void scm__lambda_225(scm__lambda_225_env_t* _env, rdf_Triple prop1_triple) { ({ __auto_type p = rdf_triple_object(prop1_triple); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->avf_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->y2}, ({ scm__lambda_226_env_t* scm__lambda_226_env = (scm__lambda_226_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_226_env_t)); *scm__lambda_226_env = (scm__lambda_226_env_t){ .arena = _env->arena, .on_prop_pred = _env->on_prop_pred, .p = p, .g = _env->g, .c1 = _env->c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_226, (void*)scm__lambda_226_env }; })); }); }

static void scm__lambda_224(scm__lambda_224_env_t* _env, rdf_Triple avf1_triple) { ({ __auto_type c1 = rdf_triple_subject(avf1_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = c1}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ scm__lambda_225_env_t* scm__lambda_225_env = (scm__lambda_225_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_225_env_t)); *scm__lambda_225_env = (scm__lambda_225_env_t){ .g = _env->g, .no_term = _env->no_term, .avf_pred = _env->avf_pred, .y2 = _env->y2, .arena = _env->arena, .on_prop_pred = _env->on_prop_pred, .c1 = c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_225, (void*)scm__lambda_225_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term avf_pred; slop_option_rdf_Term no_term; rdf_Term on_prop_pred; rdf_Term p2; slop_arena* arena; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_228_env_t;

typedef struct { index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term on_prop_pred; rdf_Term p2; slop_arena* arena; rdf_Term avf_pred; rdf_Term subclass_pred; rdf_Term c1; slop_list_rdf_Triple* result; } scm__lambda_229_env_t;

typedef struct { slop_arena* arena; rdf_Term avf_pred; rdf_Term y; index_IndexedGraph g; rdf_Term subclass_pred; rdf_Term c1; slop_list_rdf_Triple* result; } scm__lambda_230_env_t;

static void scm__lambda_230(scm__lambda_230_env_t* _env, rdf_Triple prop2_triple) { ({ __auto_type c2 = rdf_triple_subject(prop2_triple); __auto_type c2_avf_y = rdf_make_triple(_env->arena, c2, _env->avf_pred, _env->y); ((rdf_indexed_graph_contains(_env->g, c2_avf_y)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, c2, _env->subclass_pred, _env->c1); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

static void scm__lambda_229(scm__lambda_229_env_t* _env, rdf_Triple avf1_triple) { ({ __auto_type y = rdf_triple_object(avf1_triple); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->p2}, ({ scm__lambda_230_env_t* scm__lambda_230_env = (scm__lambda_230_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_230_env_t)); *scm__lambda_230_env = (scm__lambda_230_env_t){ .arena = _env->arena, .avf_pred = _env->avf_pred, .y = y, .g = _env->g, .subclass_pred = _env->subclass_pred, .c1 = _env->c1, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_230, (void*)scm__lambda_230_env }; })); }); }

static void scm__lambda_228(scm__lambda_228_env_t* _env, rdf_Triple prop1_triple) { ({ __auto_type c1 = rdf_triple_subject(prop1_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = c1}, (slop_option_rdf_Term){.has_value = 1, .value = _env->avf_pred}, _env->no_term, ({ scm__lambda_229_env_t* scm__lambda_229_env = (scm__lambda_229_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_229_env_t)); *scm__lambda_229_env = (scm__lambda_229_env_t){ .g = _env->g, .no_term = _env->no_term, .on_prop_pred = _env->on_prop_pred, .p2 = _env->p2, .arena = _env->arena, .avf_pred = _env->avf_pred, .subclass_pred = _env->subclass_pred, .c1 = c1, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_229, (void*)scm__lambda_229_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term hv_pred; slop_option_rdf_Term no_term; rdf_Term on_prop_pred; rdf_Term p2; slop_arena* arena; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_232_env_t;

typedef struct { index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term on_prop_pred; rdf_Term p2; slop_arena* arena; rdf_Term hv_pred; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_233_env_t;

typedef struct { slop_arena* arena; rdf_Term hv_pred; rdf_Term i; index_IndexedGraph g; rdf_Term c1; rdf_Term subclass_pred; slop_list_rdf_Triple* result; } scm__lambda_234_env_t;

static void scm__lambda_234(scm__lambda_234_env_t* _env, rdf_Triple prop2_triple) { ({ __auto_type c2 = rdf_triple_subject(prop2_triple); __auto_type c2_hv_i = rdf_make_triple(_env->arena, c2, _env->hv_pred, _env->i); ((rdf_indexed_graph_contains(_env->g, c2_hv_i)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->c1, _env->subclass_pred, c2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

static void scm__lambda_233(scm__lambda_233_env_t* _env, rdf_Triple hv1_triple) { ({ __auto_type i = rdf_triple_object(hv1_triple); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->p2}, ({ scm__lambda_234_env_t* scm__lambda_234_env = (scm__lambda_234_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_234_env_t)); *scm__lambda_234_env = (scm__lambda_234_env_t){ .arena = _env->arena, .hv_pred = _env->hv_pred, .i = i, .g = _env->g, .c1 = _env->c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_234, (void*)scm__lambda_234_env }; })); }); }

static void scm__lambda_232(scm__lambda_232_env_t* _env, rdf_Triple prop1_triple) { ({ __auto_type c1 = rdf_triple_subject(prop1_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = c1}, (slop_option_rdf_Term){.has_value = 1, .value = _env->hv_pred}, _env->no_term, ({ scm__lambda_233_env_t* scm__lambda_233_env = (scm__lambda_233_env_t*)slop_arena_alloc(_env->arena, sizeof(scm__lambda_233_env_t)); *scm__lambda_233_env = (scm__lambda_233_env_t){ .g = _env->g, .no_term = _env->no_term, .on_prop_pred = _env->on_prop_pred, .p2 = _env->p2, .arena = _env->arena, .hv_pred = _env->hv_pred, .c1 = c1, .subclass_pred = _env->subclass_pred, .result = &((*_env->result)) }; (slop_closure_t){ (void*)scm__lambda_233, (void*)scm__lambda_233_env }; })); }); }

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
    slop_result_types_Delta_types_InconsistencyReport _retval = {0};
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
            __auto_type _coll = scm_scm_eqc1b(arena, g, delta);
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
            __auto_type _coll = scm_scm_int(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_uni(arena, g, delta);
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
            __auto_type _coll = scm_scm_eqp1b(arena, g, delta);
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
            __auto_type _coll = scm_scm_dom2(arena, g, delta);
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
            __auto_type _coll = scm_scm_rng2(arena, g, delta);
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
            __auto_type _coll = scm_scm_svf1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_svf2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_avf1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_avf2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = scm_scm_hv(arena, g, delta);
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
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type class_type = rdf_make_iri(arena, vocab_OWL_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        __auto_type nothing = rdf_make_iri(arena, vocab_OWL_NOTHING);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_188 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_188.has_value) {
            __auto_type pred_triples = _mv_188.value;
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
                                {
                                    __auto_type nothing_sub = rdf_make_triple(arena, nothing, subclass_pred, class);
                                    if (!(rdf_indexed_graph_contains(g, nothing_sub))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (nothing_sub); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                                {
                                    __auto_type refl_equiv = rdf_make_triple(arena, class, equiv_pred, class);
                                    if (!(rdf_indexed_graph_contains(g, refl_equiv))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (refl_equiv); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_188.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_sco(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_189 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_189.has_value) {
            __auto_type pred_triples = _mv_189.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = c2}, (slop_option_rdf_Term){.has_value = 1, .value = subclass_pred}, no_term, ({ scm__lambda_190_env_t* scm__lambda_190_env = (scm__lambda_190_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_190_env_t)); *scm__lambda_190_env = (scm__lambda_190_env_t){ .arena = arena, .c1 = c1, .subclass_pred = subclass_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_190, (void*)scm__lambda_190_env }; }));
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = subclass_pred}, (slop_option_rdf_Term){.has_value = 1, .value = c1}, ({ scm__lambda_191_env_t* scm__lambda_191_env = (scm__lambda_191_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_191_env_t)); *scm__lambda_191_env = (scm__lambda_191_env_t){ .arena = arena, .subclass_pred = subclass_pred, .c2 = c2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_191, (void*)scm__lambda_191_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_189.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_192 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_192.has_value) {
            __auto_type pred_triples = _mv_192.value;
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
        } else if (!_mv_192.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqc1b(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_193 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_193.has_value) {
            __auto_type pred_triples = _mv_193.value;
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
        } else if (!_mv_193.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_194 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_194.has_value) {
            __auto_type pred_triples = _mv_194.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            if (!(rdf_term_eq(c1, c2))) {
                                {
                                    __auto_type reverse = rdf_make_triple(arena, c2, subclass_pred, c1);
                                    if (rdf_indexed_graph_contains(g, reverse)) {
                                        {
                                            __auto_type inferred = rdf_make_triple(arena, c1, equiv_pred, c2);
                                            if (!(rdf_indexed_graph_contains(g, inferred))) {
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_194.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_op(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type op_type = rdf_make_iri(arena, vocab_OWL_OBJECT_PROPERTY);
        __auto_type rdf_prop_type = rdf_make_iri(arena, vocab_RDF_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_195 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_195.has_value) {
            __auto_type pred_triples = _mv_195.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        if ((rdf_term_eq(rdf_triple_object(dt), op_type) || rdf_term_eq(rdf_triple_object(dt), rdf_prop_type))) {
                            {
                                __auto_type prop = rdf_triple_subject(dt);
                                {
                                    __auto_type reflexive = rdf_make_triple(arena, prop, subprop_pred, prop);
                                    if (!(rdf_indexed_graph_contains(g, reflexive))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (reflexive); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                                {
                                    __auto_type refl_equiv = rdf_make_triple(arena, prop, equiv_pred, prop);
                                    if (!(rdf_indexed_graph_contains(g, refl_equiv))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (refl_equiv); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_195.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_dp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type dp_type = rdf_make_iri(arena, vocab_OWL_DATATYPE_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_196 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_196.has_value) {
            __auto_type pred_triples = _mv_196.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        if (rdf_term_eq(rdf_triple_object(dt), dp_type)) {
                            {
                                __auto_type prop = rdf_triple_subject(dt);
                                {
                                    __auto_type reflexive = rdf_make_triple(arena, prop, subprop_pred, prop);
                                    if (!(rdf_indexed_graph_contains(g, reflexive))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (reflexive); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                                {
                                    __auto_type refl_equiv = rdf_make_triple(arena, prop, equiv_pred, prop);
                                    if (!(rdf_indexed_graph_contains(g, refl_equiv))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (refl_equiv); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_196.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_spo(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_197 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_197.has_value) {
            __auto_type pred_triples = _mv_197.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p2}, (slop_option_rdf_Term){.has_value = 1, .value = subprop_pred}, no_term, ({ scm__lambda_198_env_t* scm__lambda_198_env = (scm__lambda_198_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_198_env_t)); *scm__lambda_198_env = (scm__lambda_198_env_t){ .arena = arena, .p1 = p1, .subprop_pred = subprop_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_198, (void*)scm__lambda_198_env }; }));
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = subprop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = p1}, ({ scm__lambda_199_env_t* scm__lambda_199_env = (scm__lambda_199_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_199_env_t)); *scm__lambda_199_env = (scm__lambda_199_env_t){ .arena = arena, .subprop_pred = subprop_pred, .p2 = p2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_199, (void*)scm__lambda_199_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_197.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqp1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_200 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_200.has_value) {
            __auto_type pred_triples = _mv_200.value;
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
        } else if (!_mv_200.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqp1b(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_201 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(equiv_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_201.has_value) {
            __auto_type pred_triples = _mv_201.value;
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
        } else if (!_mv_201.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBPROPERTY_OF)), "(all-triples-have-predicate $result RDFS_SUBPROPERTY_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_eqp2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_202 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_202.has_value) {
            __auto_type pred_triples = _mv_202.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            if (!(rdf_term_eq(p1, p2))) {
                                {
                                    __auto_type reverse = rdf_make_triple(arena, p2, subprop_pred, p1);
                                    if (rdf_indexed_graph_contains(g, reverse)) {
                                        {
                                            __auto_type inferred = rdf_make_triple(arena, p1, equiv_pred, p2);
                                            if (!(rdf_indexed_graph_contains(g, inferred))) {
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_202.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_dom2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_203 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_203.has_value) {
            __auto_type pred_triples = _mv_203.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p2}, (slop_option_rdf_Term){.has_value = 1, .value = domain_pred}, no_term, ({ scm__lambda_204_env_t* scm__lambda_204_env = (scm__lambda_204_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_204_env_t)); *scm__lambda_204_env = (scm__lambda_204_env_t){ .arena = arena, .p1 = p1, .domain_pred = domain_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_204, (void*)scm__lambda_204_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_203.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_DOMAIN)), "(all-triples-have-predicate $result RDFS_DOMAIN)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_dom1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_205 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_205.has_value) {
            __auto_type pred_triples = _mv_205.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = domain_pred}, (slop_option_rdf_Term){.has_value = 1, .value = c1}, ({ scm__lambda_206_env_t* scm__lambda_206_env = (scm__lambda_206_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_206_env_t)); *scm__lambda_206_env = (scm__lambda_206_env_t){ .arena = arena, .domain_pred = domain_pred, .c2 = c2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_206, (void*)scm__lambda_206_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_205.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_DOMAIN)), "(all-triples-have-predicate $result RDFS_DOMAIN)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_rng2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type range_pred = rdf_make_iri(arena, vocab_RDFS_RANGE);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_207 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_207.has_value) {
            __auto_type pred_triples = _mv_207.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p2}, (slop_option_rdf_Term){.has_value = 1, .value = range_pred}, no_term, ({ scm__lambda_208_env_t* scm__lambda_208_env = (scm__lambda_208_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_208_env_t)); *scm__lambda_208_env = (scm__lambda_208_env_t){ .arena = arena, .p1 = p1, .range_pred = range_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_208, (void*)scm__lambda_208_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_207.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_RANGE)), "(all-triples-have-predicate $result RDFS_RANGE)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_rng1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type range_pred = rdf_make_iri(arena, vocab_RDFS_RANGE);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_209 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_209.has_value) {
            __auto_type pred_triples = _mv_209.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type c1 = rdf_triple_subject(dt);
                            __auto_type c2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = range_pred}, (slop_option_rdf_Term){.has_value = 1, .value = c1}, ({ scm__lambda_210_env_t* scm__lambda_210_env = (scm__lambda_210_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_210_env_t)); *scm__lambda_210_env = (scm__lambda_210_env_t){ .arena = arena, .range_pred = range_pred, .c2 = c2, .g = g, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_210, (void*)scm__lambda_210_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_209.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_RANGE)), "(all-triples-have-predicate $result RDFS_RANGE)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_int(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type intersection_pred = rdf_make_iri(arena, vocab_OWL_INTERSECTION_OF);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_211 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(intersection_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_211.has_value) {
            __auto_type pred_triples = _mv_211.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type int_class = rdf_triple_subject(dt);
                            __auto_type list_head = rdf_triple_object(dt);
                            __auto_type components = rdf_list_elements_indexed(arena, g, list_head);
                            {
                                __auto_type _coll = components;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type comp = _coll.data[_i];
                                    {
                                        __auto_type inferred = rdf_make_triple(arena, int_class, subclass_pred, comp);
                                        if (!(rdf_indexed_graph_contains(g, inferred))) {
                                            ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_211.has_value) {
        }
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = intersection_pred}, no_term, ({ scm__lambda_212_env_t* scm__lambda_212_env = (scm__lambda_212_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_212_env_t)); *scm__lambda_212_env = (scm__lambda_212_env_t){ .arena = arena, .g = g, .subclass_pred = subclass_pred, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_212, (void*)scm__lambda_212_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_uni(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type union_pred = rdf_make_iri(arena, vocab_OWL_UNION_OF);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_213 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(union_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_213.has_value) {
            __auto_type pred_triples = _mv_213.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type union_class = rdf_triple_subject(dt);
                            __auto_type list_head = rdf_triple_object(dt);
                            __auto_type components = rdf_list_elements_indexed(arena, g, list_head);
                            {
                                __auto_type _coll = components;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type comp = _coll.data[_i];
                                    {
                                        __auto_type inferred = rdf_make_triple(arena, comp, subclass_pred, union_class);
                                        if (!(rdf_indexed_graph_contains(g, inferred))) {
                                            ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_213.has_value) {
        }
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = union_pred}, no_term, ({ scm__lambda_214_env_t* scm__lambda_214_env = (scm__lambda_214_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_214_env_t)); *scm__lambda_214_env = (scm__lambda_214_env_t){ .arena = arena, .g = g, .subclass_pred = subclass_pred, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_214, (void*)scm__lambda_214_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_svf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type svf_pred = rdf_make_iri(arena, vocab_OWL_SOME_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_215 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_215.has_value) {
            __auto_type pred_triples = _mv_215.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type y1 = rdf_triple_subject(dt);
                            __auto_type y2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = svf_pred}, (slop_option_rdf_Term){.has_value = 1, .value = y1}, ({ scm__lambda_216_env_t* scm__lambda_216_env = (scm__lambda_216_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_216_env_t)); *scm__lambda_216_env = (scm__lambda_216_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .svf_pred = svf_pred, .y2 = y2, .arena = arena, .subclass_pred = subclass_pred, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_216, (void*)scm__lambda_216_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_215.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_svf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type svf_pred = rdf_make_iri(arena, vocab_OWL_SOME_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_219 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_219.has_value) {
            __auto_type pred_triples = _mv_219.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = on_prop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = p1}, ({ scm__lambda_220_env_t* scm__lambda_220_env = (scm__lambda_220_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_220_env_t)); *scm__lambda_220_env = (scm__lambda_220_env_t){ .g = g, .svf_pred = svf_pred, .no_term = no_term, .on_prop_pred = on_prop_pred, .p2 = p2, .arena = arena, .subclass_pred = subclass_pred, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_220, (void*)scm__lambda_220_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_219.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_avf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type avf_pred = rdf_make_iri(arena, vocab_OWL_ALL_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_223 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subclass_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_223.has_value) {
            __auto_type pred_triples = _mv_223.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type y1 = rdf_triple_subject(dt);
                            __auto_type y2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = avf_pred}, (slop_option_rdf_Term){.has_value = 1, .value = y1}, ({ scm__lambda_224_env_t* scm__lambda_224_env = (scm__lambda_224_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_224_env_t)); *scm__lambda_224_env = (scm__lambda_224_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .avf_pred = avf_pred, .y2 = y2, .arena = arena, .subclass_pred = subclass_pred, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_224, (void*)scm__lambda_224_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_223.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_avf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type avf_pred = rdf_make_iri(arena, vocab_OWL_ALL_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_227 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_227.has_value) {
            __auto_type pred_triples = _mv_227.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = on_prop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = p1}, ({ scm__lambda_228_env_t* scm__lambda_228_env = (scm__lambda_228_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_228_env_t)); *scm__lambda_228_env = (scm__lambda_228_env_t){ .g = g, .avf_pred = avf_pred, .no_term = no_term, .on_prop_pred = on_prop_pred, .p2 = p2, .arena = arena, .subclass_pred = subclass_pred, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_228, (void*)scm__lambda_228_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_227.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

slop_list_rdf_Triple scm_scm_hv(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type hv_pred = rdf_make_iri(arena, vocab_OWL_HAS_VALUE);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_231 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(subprop_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_231.has_value) {
            __auto_type pred_triples = _mv_231.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type p1 = rdf_triple_subject(dt);
                            __auto_type p2 = rdf_triple_object(dt);
                            rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = on_prop_pred}, (slop_option_rdf_Term){.has_value = 1, .value = p1}, ({ scm__lambda_232_env_t* scm__lambda_232_env = (scm__lambda_232_env_t*)slop_arena_alloc(arena, sizeof(scm__lambda_232_env_t)); *scm__lambda_232_env = (scm__lambda_232_env_t){ .g = g, .hv_pred = hv_pred, .no_term = no_term, .on_prop_pred = on_prop_pred, .p2 = p2, .arena = arena, .subclass_pred = subclass_pred, .result = &(result) }; (slop_closure_t){ (void*)scm__lambda_232, (void*)scm__lambda_232_env }; }));
                        }
                    }
                }
            }
        } else if (!_mv_231.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDFS_SUBCLASS_OF)), "(all-triples-have-predicate $result RDFS_SUBCLASS_OF)");
    return _retval;
}

