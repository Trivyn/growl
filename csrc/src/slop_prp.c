#include "../runtime/slop_runtime.h"
#include "slop_prp.h"

static const slop_string prp_EX_ALICE = SLOP_STR("http://example.org/alice");
static const slop_string prp_EX_ALICIA = SLOP_STR("http://example.org/alicia");
static const slop_string prp_EX_BOB = SLOP_STR("http://example.org/bob");
static const slop_string prp_EX_MARY = SLOP_STR("http://example.org/mary");
static const slop_string prp_EX_MARIA = SLOP_STR("http://example.org/maria");
static const slop_string prp_EX_A = SLOP_STR("http://example.org/a");
static const slop_string prp_EX_B = SLOP_STR("http://example.org/b");
static const slop_string prp_EX_C = SLOP_STR("http://example.org/c");
static const slop_string prp_EX_PERSON = SLOP_STR("http://example.org/Person");
static const slop_string prp_EX_HAS_CHILD = SLOP_STR("http://example.org/hasChild");
static const slop_string prp_EX_HAS_PARENT = SLOP_STR("http://example.org/hasParent");
static const slop_string prp_EX_HAS_FATHER = SLOP_STR("http://example.org/hasFather");
static const slop_string prp_EX_HAS_MOTHER = SLOP_STR("http://example.org/hasMother");
static const slop_string prp_EX_ANCESTOR = SLOP_STR("http://example.org/ancestor");
static const slop_string prp_EX_KNOWS = SLOP_STR("http://example.org/knows");
static const slop_string prp_EX_LIKES = SLOP_STR("http://example.org/likes");
static const slop_string prp_EX_HATES = SLOP_STR("http://example.org/hates");
static const slop_string prp_EX_SSN = SLOP_STR("http://example.org/ssn");

index_IndexedGraph prp_fixture_g_domain(slop_arena* arena);
index_IndexedGraph prp_fixture_g_range(slop_arena* arena);
index_IndexedGraph prp_fixture_g_functional(slop_arena* arena);
index_IndexedGraph prp_fixture_g_ifp(slop_arena* arena);
index_IndexedGraph prp_fixture_g_symmetric(slop_arena* arena);
index_IndexedGraph prp_fixture_g_asym_violation(slop_arena* arena);
index_IndexedGraph prp_fixture_g_transitive(slop_arena* arena);
index_IndexedGraph prp_fixture_g_irp_violation(slop_arena* arena);
index_IndexedGraph prp_fixture_g_subprop(slop_arena* arena);
index_IndexedGraph prp_fixture_g_inverse(slop_arena* arena);
index_IndexedGraph prp_fixture_g_pdw_violation(slop_arena* arena);
types_Delta prp_fixture_delta_usage(slop_arena* arena);
types_Delta prp_fixture_delta_empty(slop_arena* arena);
types_Delta prp_fixture_delta_functional(slop_arena* arena);
types_Delta prp_fixture_delta_ifp(slop_arena* arena);
types_Delta prp_fixture_delta_symmetric(slop_arena* arena);
types_Delta prp_fixture_delta_asymmetric(slop_arena* arena);
types_Delta prp_fixture_delta_transitive(slop_arena* arena);
types_Delta prp_fixture_delta_irreflexive(slop_arena* arena);
types_Delta prp_fixture_delta_subprop(slop_arena* arena);
types_Delta prp_fixture_delta_inverse1(slop_arena* arena);
types_Delta prp_fixture_delta_inverse2(slop_arena* arena);
types_Delta prp_fixture_delta_pdw(slop_arena* arena);
slop_result_types_Delta_types_InconsistencyReport prp_apply_prp_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast);
slop_list_rdf_Triple prp_prp_dom(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_rng(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_fp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_ifp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_symp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport prp_prp_asyp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_trp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport prp_prp_irp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport prp_prp_adp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport prp_prp_npa1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport prp_prp_npa2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_spo2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_key(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_spo1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_inv1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_inv2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_eqp1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_eqp2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport prp_prp_pdw(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple prp_prp_ap(slop_arena* arena, index_IndexedGraph g);

typedef struct { slop_arena* arena; rdf_Term x; rdf_Term type_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_163_env_t;

static void prp__lambda_163(prp__lambda_163_env_t* _env, rdf_Triple dom_triple) { ({ __auto_type c = rdf_triple_object(dom_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->x, _env->type_pred, c); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term y; rdf_Term type_pred; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_164_env_t;

static void prp__lambda_164(prp__lambda_164_env_t* _env, rdf_Triple rng_triple) { ({ __auto_type c = rdf_triple_object(rng_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->y, _env->type_pred, c); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { types_Delta delta; index_IndexedGraph g; slop_option_rdf_Term no_term; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } prp__lambda_165_env_t;

typedef struct { rdf_Term y1; slop_arena* arena; rdf_Term same_as; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_166_env_t;

static void prp__lambda_166(prp__lambda_166_env_t* _env, rdf_Triple other_triple) { ({ __auto_type y2 = rdf_triple_object(other_triple); ((!(rdf_term_eq(_env->y1, y2))) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->y1, _env->same_as, y2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

static void prp__lambda_165(prp__lambda_165_env_t* _env, rdf_Triple fp_triple) { ({ __auto_type p = rdf_triple_subject(fp_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x = rdf_triple_subject(dt); __auto_type y1 = rdf_triple_object(dt); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = x}, (slop_option_rdf_Term){.has_value = 1, .value = p}, _env->no_term, ({ prp__lambda_166_env_t* prp__lambda_166_env = (prp__lambda_166_env_t*)slop_arena_alloc(_env->arena, sizeof(prp__lambda_166_env_t)); *prp__lambda_166_env = (prp__lambda_166_env_t){ .y1 = y1, .arena = _env->arena, .same_as = _env->same_as, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)prp__lambda_166, (void*)prp__lambda_166_env }; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { types_Delta delta; index_IndexedGraph g; slop_option_rdf_Term no_term; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } prp__lambda_167_env_t;

typedef struct { rdf_Term x1; slop_arena* arena; rdf_Term same_as; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_168_env_t;

static void prp__lambda_168(prp__lambda_168_env_t* _env, rdf_Triple other_triple) { ({ __auto_type x2 = rdf_triple_subject(other_triple); ((!(rdf_term_eq(_env->x1, x2))) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, _env->x1, _env->same_as, x2); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }

static void prp__lambda_167(prp__lambda_167_env_t* _env, rdf_Triple ifp_triple) { ({ __auto_type p = rdf_triple_subject(ifp_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x1 = rdf_triple_subject(dt); __auto_type y = rdf_triple_object(dt); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = p}, (slop_option_rdf_Term){.has_value = 1, .value = y}, ({ prp__lambda_168_env_t* prp__lambda_168_env = (prp__lambda_168_env_t*)slop_arena_alloc(_env->arena, sizeof(prp__lambda_168_env_t)); *prp__lambda_168_env = (prp__lambda_168_env_t){ .x1 = x1, .arena = _env->arena, .same_as = _env->same_as, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)prp__lambda_168, (void*)prp__lambda_168_env }; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { types_Delta delta; slop_arena* arena; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_169_env_t;

static void prp__lambda_169(prp__lambda_169_env_t* _env, rdf_Triple sym_triple) { ({ __auto_type p = rdf_triple_subject(sym_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x = rdf_triple_subject(dt); __auto_type y = rdf_triple_object(dt); __auto_type inferred = rdf_make_triple(_env->arena, y, p, x); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { types_Delta delta; index_IndexedGraph g; slop_option_rdf_Term no_term; slop_arena* arena; slop_list_rdf_Triple* result; } prp__lambda_171_env_t;

typedef struct { slop_arena* arena; rdf_Term x; rdf_Term p; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_172_env_t;

static void prp__lambda_172(prp__lambda_172_env_t* _env, rdf_Triple next_triple) { ({ __auto_type z = rdf_triple_object(next_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->x, _env->p, z); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { slop_arena* arena; rdf_Term p; rdf_Term y; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_173_env_t;

static void prp__lambda_173(prp__lambda_173_env_t* _env, rdf_Triple prev_triple) { ({ __auto_type w = rdf_triple_subject(prev_triple); __auto_type inferred = rdf_make_triple(_env->arena, w, _env->p, _env->y); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

static void prp__lambda_171(prp__lambda_171_env_t* _env, rdf_Triple trans_triple) { ({ __auto_type p = rdf_triple_subject(trans_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x = rdf_triple_subject(dt); __auto_type y = rdf_triple_object(dt); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = y}, (slop_option_rdf_Term){.has_value = 1, .value = p}, _env->no_term, ({ prp__lambda_172_env_t* prp__lambda_172_env = (prp__lambda_172_env_t*)slop_arena_alloc(_env->arena, sizeof(prp__lambda_172_env_t)); *prp__lambda_172_env = (prp__lambda_172_env_t){ .arena = _env->arena, .x = x, .p = p, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)prp__lambda_172, (void*)prp__lambda_172_env }; })); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = p}, (slop_option_rdf_Term){.has_value = 1, .value = x}, ({ prp__lambda_173_env_t* prp__lambda_173_env = (prp__lambda_173_env_t*)slop_arena_alloc(_env->arena, sizeof(prp__lambda_173_env_t)); *prp__lambda_173_env = (prp__lambda_173_env_t){ .arena = _env->arena, .p = p, .y = y, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)prp__lambda_173, (void*)prp__lambda_173_env }; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { slop_arena* arena; rdf_Term x; rdf_Term y; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_180_env_t;

static void prp__lambda_180(prp__lambda_180_env_t* _env, rdf_Triple super_triple) { ({ __auto_type p2 = rdf_triple_object(super_triple); __auto_type inferred = rdf_make_triple(_env->arena, _env->x, p2, _env->y); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

typedef struct { types_Delta delta; slop_arena* arena; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_181_env_t;

static void prp__lambda_181(prp__lambda_181_env_t* _env, rdf_Triple inv_triple) { ({ __auto_type p1 = rdf_triple_subject(inv_triple); __auto_type p2 = rdf_triple_object(inv_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p1)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x = rdf_triple_subject(dt); __auto_type y = rdf_triple_object(dt); __auto_type inferred = rdf_make_triple(_env->arena, y, p2, x); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { types_Delta delta; slop_arena* arena; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_182_env_t;

static void prp__lambda_182(prp__lambda_182_env_t* _env, rdf_Triple inv_triple) { ({ __auto_type p1 = rdf_triple_subject(inv_triple); __auto_type p2 = rdf_triple_object(inv_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p2)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x = rdf_triple_subject(dt); __auto_type y = rdf_triple_object(dt); __auto_type inferred = rdf_make_triple(_env->arena, y, p1, x); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { types_Delta delta; slop_arena* arena; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_183_env_t;

static void prp__lambda_183(prp__lambda_183_env_t* _env, rdf_Triple equiv_triple) { ({ __auto_type p1 = rdf_triple_subject(equiv_triple); __auto_type p2 = rdf_triple_object(equiv_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p1)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x = rdf_triple_subject(dt); __auto_type y = rdf_triple_object(dt); __auto_type inferred = rdf_make_triple(_env->arena, x, p2, y); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { types_Delta delta; slop_arena* arena; index_IndexedGraph g; slop_list_rdf_Triple* result; } prp__lambda_184_env_t;

static void prp__lambda_184(prp__lambda_184_env_t* _env, rdf_Triple equiv_triple) { ({ __auto_type p1 = rdf_triple_subject(equiv_triple); __auto_type p2 = rdf_triple_object(equiv_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(p2)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type x = rdf_triple_subject(dt); __auto_type y = rdf_triple_object(dt); __auto_type inferred = rdf_make_triple(_env->arena, x, p1, y); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

index_IndexedGraph prp_fixture_g_domain(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
        __auto_type has_child = rdf_make_iri(arena, prp_EX_HAS_CHILD);
        __auto_type person = rdf_make_iri(arena, prp_EX_PERSON);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_child, domain_pred, person));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_child, bob));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_range(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type range_pred = rdf_make_iri(arena, vocab_RDFS_RANGE);
        __auto_type has_child = rdf_make_iri(arena, prp_EX_HAS_CHILD);
        __auto_type person = rdf_make_iri(arena, prp_EX_PERSON);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_child, range_pred, person));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_child, bob));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_functional(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type fp_type = rdf_make_iri(arena, vocab_OWL_FUNCTIONAL_PROPERTY);
        __auto_type has_mother = rdf_make_iri(arena, prp_EX_HAS_MOTHER);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type mary = rdf_make_iri(arena, prp_EX_MARY);
        __auto_type maria = rdf_make_iri(arena, prp_EX_MARIA);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_mother, type_pred, fp_type));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_mother, mary));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_mother, maria));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_ifp(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type ifp_type = rdf_make_iri(arena, vocab_OWL_INVERSE_FUNCTIONAL_PROPERTY);
        __auto_type ssn = rdf_make_iri(arena, prp_EX_SSN);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type alicia = rdf_make_iri(arena, prp_EX_ALICIA);
        __auto_type ssn_val = rdf_make_literal(arena, SLOP_STR("123"), ((slop_option_string){.has_value = false}), ((slop_option_string){.has_value = false}));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, ssn, type_pred, ifp_type));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, ssn, ssn_val));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alicia, ssn, ssn_val));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_symmetric(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type sym_type = rdf_make_iri(arena, vocab_OWL_SYMMETRIC_PROPERTY);
        __auto_type knows = rdf_make_iri(arena, prp_EX_KNOWS);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, knows, type_pred, sym_type));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, knows, bob));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_asym_violation(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type asym_type = rdf_make_iri(arena, vocab_OWL_ASYMMETRIC_PROPERTY);
        __auto_type has_parent = rdf_make_iri(arena, prp_EX_HAS_PARENT);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_parent, type_pred, asym_type));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_parent, bob));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, bob, has_parent, alice));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_transitive(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type trans_type = rdf_make_iri(arena, vocab_OWL_TRANSITIVE_PROPERTY);
        __auto_type ancestor = rdf_make_iri(arena, prp_EX_ANCESTOR);
        __auto_type a = rdf_make_iri(arena, prp_EX_A);
        __auto_type b = rdf_make_iri(arena, prp_EX_B);
        __auto_type c = rdf_make_iri(arena, prp_EX_C);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, ancestor, type_pred, trans_type));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, a, ancestor, b));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, b, ancestor, c));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_irp_violation(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type irp_type = rdf_make_iri(arena, vocab_OWL_IRREFLEXIVE_PROPERTY);
        __auto_type has_parent = rdf_make_iri(arena, prp_EX_HAS_PARENT);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_parent, type_pred, irp_type));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_parent, alice));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_subprop(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        __auto_type has_father = rdf_make_iri(arena, prp_EX_HAS_FATHER);
        __auto_type has_parent = rdf_make_iri(arena, prp_EX_HAS_PARENT);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_father, subprop_pred, has_parent));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_father, bob));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_inverse(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type inverse_pred = rdf_make_iri(arena, vocab_OWL_INVERSE_OF);
        __auto_type has_parent = rdf_make_iri(arena, prp_EX_HAS_PARENT);
        __auto_type has_child = rdf_make_iri(arena, prp_EX_HAS_CHILD);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_parent, inverse_pred, has_child));
        return g;
    }
}

index_IndexedGraph prp_fixture_g_pdw_violation(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type pdw_pred = rdf_make_iri(arena, vocab_OWL_PROPERTY_DISJOINT_WITH);
        __auto_type likes = rdf_make_iri(arena, prp_EX_LIKES);
        __auto_type hates = rdf_make_iri(arena, prp_EX_HATES);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, likes, pdw_pred, hates));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, likes, bob));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, hates, bob));
        return g;
    }
}

types_Delta prp_fixture_delta_usage(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_child = rdf_make_iri(arena, prp_EX_HAS_CHILD);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, has_child, bob));
        return d;
    }
}

types_Delta prp_fixture_delta_empty(slop_arena* arena) {
    return types_make_delta(arena, 0);
}

types_Delta prp_fixture_delta_functional(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_mother = rdf_make_iri(arena, prp_EX_HAS_MOTHER);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type mary = rdf_make_iri(arena, prp_EX_MARY);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, has_mother, mary));
        return d;
    }
}

types_Delta prp_fixture_delta_ifp(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type ssn = rdf_make_iri(arena, prp_EX_SSN);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type ssn_val = rdf_make_literal(arena, SLOP_STR("123"), ((slop_option_string){.has_value = false}), ((slop_option_string){.has_value = false}));
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, ssn, ssn_val));
        return d;
    }
}

types_Delta prp_fixture_delta_symmetric(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type knows = rdf_make_iri(arena, prp_EX_KNOWS);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, knows, bob));
        return d;
    }
}

types_Delta prp_fixture_delta_asymmetric(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_parent = rdf_make_iri(arena, prp_EX_HAS_PARENT);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, has_parent, bob));
        return d;
    }
}

types_Delta prp_fixture_delta_transitive(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type ancestor = rdf_make_iri(arena, prp_EX_ANCESTOR);
        __auto_type a = rdf_make_iri(arena, prp_EX_A);
        __auto_type b = rdf_make_iri(arena, prp_EX_B);
        d = types_delta_add(arena, d, rdf_make_triple(arena, a, ancestor, b));
        return d;
    }
}

types_Delta prp_fixture_delta_irreflexive(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_parent = rdf_make_iri(arena, prp_EX_HAS_PARENT);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, has_parent, alice));
        return d;
    }
}

types_Delta prp_fixture_delta_subprop(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_father = rdf_make_iri(arena, prp_EX_HAS_FATHER);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, has_father, bob));
        return d;
    }
}

types_Delta prp_fixture_delta_inverse1(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_parent = rdf_make_iri(arena, prp_EX_HAS_PARENT);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, has_parent, bob));
        return d;
    }
}

types_Delta prp_fixture_delta_inverse2(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_child = rdf_make_iri(arena, prp_EX_HAS_CHILD);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, bob, has_child, alice));
        return d;
    }
}

types_Delta prp_fixture_delta_pdw(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type likes = rdf_make_iri(arena, prp_EX_LIKES);
        __auto_type alice = rdf_make_iri(arena, prp_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, prp_EX_BOB);
        d = types_delta_add(arena, d, rdf_make_triple(arena, alice, likes, bob));
        return d;
    }
}

slop_result_types_Delta_types_InconsistencyReport prp_apply_prp_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type result = types_make_delta(arena, next_iter);
        {
            __auto_type _coll = prp_prp_dom(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_rng(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_fp(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_ifp(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_symp(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_trp(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        __auto_type _mv_157 = prp_prp_asyp(arena, g, delta);
        if (_mv_157.has_value) {
            __auto_type report = _mv_157.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_157.has_value) {
        }
        __auto_type _mv_158 = prp_prp_irp(arena, g, delta);
        if (_mv_158.has_value) {
            __auto_type report = _mv_158.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_158.has_value) {
        }
        __auto_type _mv_159 = prp_prp_pdw(arena, g, delta);
        if (_mv_159.has_value) {
            __auto_type report = _mv_159.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_159.has_value) {
        }
        __auto_type _mv_160 = prp_prp_adp(arena, g, delta);
        if (_mv_160.has_value) {
            __auto_type report = _mv_160.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_160.has_value) {
        }
        __auto_type _mv_161 = prp_prp_npa1(arena, g, delta);
        if (_mv_161.has_value) {
            __auto_type report = _mv_161.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_161.has_value) {
        }
        __auto_type _mv_162 = prp_prp_npa2(arena, g, delta);
        if (_mv_162.has_value) {
            __auto_type report = _mv_162.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_162.has_value) {
        }
        {
            __auto_type _coll = prp_prp_spo1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_eqp1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_eqp2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_inv1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_inv2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_spo2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = prp_prp_key(arena, g, delta);
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

slop_list_rdf_Triple prp_prp_dom(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        {
            __auto_type _coll = delta.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type dt = _coll.data[_i];
                0;
                {
                    __auto_type x = rdf_triple_subject(dt);
                    __auto_type p = rdf_triple_predicate(dt);
                    rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p}, (slop_option_rdf_Term){.has_value = 1, .value = domain_pred}, no_term, ({ prp__lambda_163_env_t* prp__lambda_163_env = (prp__lambda_163_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_163_env_t)); *prp__lambda_163_env = (prp__lambda_163_env_t){ .arena = arena, .x = x, .type_pred = type_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_163, (void*)prp__lambda_163_env }; }));
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_rng(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type range_pred = rdf_make_iri(arena, vocab_RDFS_RANGE);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        {
            __auto_type _coll = delta.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type dt = _coll.data[_i];
                0;
                {
                    __auto_type y = rdf_triple_object(dt);
                    __auto_type p = rdf_triple_predicate(dt);
                    rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p}, (slop_option_rdf_Term){.has_value = 1, .value = range_pred}, no_term, ({ prp__lambda_164_env_t* prp__lambda_164_env = (prp__lambda_164_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_164_env_t)); *prp__lambda_164_env = (prp__lambda_164_env_t){ .arena = arena, .y = y, .type_pred = type_pred, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_164, (void*)prp__lambda_164_env }; }));
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_fp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type fp_type = rdf_make_iri(arena, vocab_OWL_FUNCTIONAL_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = fp_type}, ({ prp__lambda_165_env_t* prp__lambda_165_env = (prp__lambda_165_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_165_env_t)); *prp__lambda_165_env = (prp__lambda_165_env_t){ .delta = delta, .g = g, .no_term = no_term, .arena = arena, .same_as = same_as, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_165, (void*)prp__lambda_165_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_ifp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type ifp_type = rdf_make_iri(arena, vocab_OWL_INVERSE_FUNCTIONAL_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = ifp_type}, ({ prp__lambda_167_env_t* prp__lambda_167_env = (prp__lambda_167_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_167_env_t)); *prp__lambda_167_env = (prp__lambda_167_env_t){ .delta = delta, .g = g, .no_term = no_term, .arena = arena, .same_as = same_as, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_167, (void*)prp__lambda_167_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_symp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type sym_type = rdf_make_iri(arena, vocab_OWL_SYMMETRIC_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = sym_type}, ({ prp__lambda_169_env_t* prp__lambda_169_env = (prp__lambda_169_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_169_env_t)); *prp__lambda_169_env = (prp__lambda_169_env_t){ .delta = delta, .arena = arena, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_169, (void*)prp__lambda_169_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_option_types_InconsistencyReport prp_prp_asyp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type asym_type = rdf_make_iri(arena, vocab_OWL_ASYMMETRIC_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type asym_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = asym_type});
            {
                __auto_type _coll = asym_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type asym_triple = _coll.data[_i];
                    {
                        __auto_type p = rdf_triple_subject(asym_triple);
                        __auto_type _mv_170 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                        if (_mv_170.has_value) {
                            __auto_type pred_triples = _mv_170.value;
                            {
                                slop_map* _coll = (slop_map*)pred_triples;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                                        {
                                            __auto_type x = rdf_triple_subject(dt);
                                            __auto_type y = rdf_triple_object(dt);
                                            __auto_type reverse = rdf_make_triple(arena, y, p, x);
                                            if (rdf_indexed_graph_contains(g, reverse)) {
                                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("prp-asyp: asymmetric property used symmetrically"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = reverse; _ll.data[2] = asym_triple; _ll; })})};
                                            }
                                        }
                                    }
                                }
                            }
                        } else if (!_mv_170.has_value) {
                        }
                    }
                }
            }
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 2); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 2)))");
    return _retval;
}

slop_list_rdf_Triple prp_prp_trp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type trans_type = rdf_make_iri(arena, vocab_OWL_TRANSITIVE_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = trans_type}, ({ prp__lambda_171_env_t* prp__lambda_171_env = (prp__lambda_171_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_171_env_t)); *prp__lambda_171_env = (prp__lambda_171_env_t){ .delta = delta, .g = g, .no_term = no_term, .arena = arena, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_171, (void*)prp__lambda_171_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_option_types_InconsistencyReport prp_prp_irp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type irp_type = rdf_make_iri(arena, vocab_OWL_IRREFLEXIVE_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type irp_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = irp_type});
            {
                __auto_type _coll = irp_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type irp_triple = _coll.data[_i];
                    {
                        __auto_type p = rdf_triple_subject(irp_triple);
                        __auto_type _mv_174 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                        if (_mv_174.has_value) {
                            __auto_type pred_triples = _mv_174.value;
                            {
                                slop_map* _coll = (slop_map*)pred_triples;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                                        {
                                            __auto_type x = rdf_triple_subject(dt);
                                            __auto_type y = rdf_triple_object(dt);
                                            if (rdf_term_eq(x, y)) {
                                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("prp-irp: irreflexive property used reflexively"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 2 * sizeof(rdf_Triple)), .len = 2, .cap = 2 }; _ll.data[0] = dt; _ll.data[1] = irp_triple; _ll; })})};
                                            }
                                        }
                                    }
                                }
                            }
                        } else if (!_mv_174.has_value) {
                        }
                    }
                }
            }
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 1); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 1)))");
    return _retval;
}

slop_option_types_InconsistencyReport prp_prp_adp(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type adp_class = rdf_make_iri(arena, vocab_OWL_ALL_DISJOINT_PROPERTIES);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type members_pred = rdf_make_iri(arena, vocab_OWL_MEMBERS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type adp_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = adp_class});
            {
                __auto_type _coll = adp_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type adp_triple = _coll.data[_i];
                    {
                        __auto_type adp_node = rdf_triple_subject(adp_triple);
                        {
                            __auto_type m_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = adp_node}, (slop_option_rdf_Term){.has_value = 1, .value = members_pred}, no_term);
                            {
                                __auto_type _coll = m_triples;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type m_triple = _coll.data[_i];
                                    {
                                        __auto_type list_head = rdf_triple_object(m_triple);
                                        __auto_type props = rdf_list_elements_indexed(arena, g, list_head);
                                        {
                                            __auto_type _coll = props;
                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                __auto_type pi = _coll.data[_i];
                                                {
                                                    __auto_type _coll = props;
                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                        __auto_type pj = _coll.data[_i];
                                                        if (!(rdf_term_eq(pi, pj))) {
                                                            __auto_type _mv_175 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(pi)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                                                            if (_mv_175.has_value) {
                                                                __auto_type pred_triples = _mv_175.value;
                                                                {
                                                                    slop_map* _coll = (slop_map*)pred_triples;
                                                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                                                        if (_coll->entries[_i].occupied) {
                                                                            rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                                                                            {
                                                                                __auto_type a = rdf_triple_subject(dt);
                                                                                __auto_type b = rdf_triple_object(dt);
                                                                                __auto_type conflict = rdf_make_triple(arena, a, pj, b);
                                                                                if (rdf_indexed_graph_contains(g, conflict)) {
                                                                                    return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("prp-adp: same pair asserted via two properties in AllDisjointProperties"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = conflict; _ll.data[2] = adp_triple; _ll; })})};
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            } else if (!_mv_175.has_value) {
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

slop_option_types_InconsistencyReport prp_prp_npa1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type source_pred = rdf_make_iri(arena, vocab_OWL_SOURCE_INDIVIDUAL);
        __auto_type assert_pred = rdf_make_iri(arena, vocab_OWL_ASSERTION_PROPERTY);
        __auto_type target_pred = rdf_make_iri(arena, vocab_OWL_TARGET_INDIVIDUAL);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type npa_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = source_pred}, no_term);
            {
                __auto_type _coll = npa_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type npa_triple = _coll.data[_i];
                    {
                        __auto_type x = rdf_triple_subject(npa_triple);
                        __auto_type s = rdf_triple_object(npa_triple);
                        {
                            __auto_type ap_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = x}, (slop_option_rdf_Term){.has_value = 1, .value = assert_pred}, no_term);
                            {
                                __auto_type _coll = ap_triples;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type ap_triple = _coll.data[_i];
                                    {
                                        __auto_type p = rdf_triple_object(ap_triple);
                                        {
                                            __auto_type ti_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = x}, (slop_option_rdf_Term){.has_value = 1, .value = target_pred}, no_term);
                                            {
                                                __auto_type _coll = ti_triples;
                                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                                    __auto_type ti_triple = _coll.data[_i];
                                                    {
                                                        __auto_type o = rdf_triple_object(ti_triple);
                                                        __auto_type asserted = rdf_make_triple(arena, s, p, o);
                                                        if (rdf_indexed_graph_contains(g, asserted)) {
                                                            return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("prp-npa1: negative property assertion violated (named individual)"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 4 * sizeof(rdf_Triple)), .len = 4, .cap = 4 }; _ll.data[0] = asserted; _ll.data[1] = npa_triple; _ll.data[2] = ap_triple; _ll.data[3] = ti_triple; _ll; })})};
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
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 1); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 1)))");
    return _retval;
}

slop_option_types_InconsistencyReport prp_prp_npa2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type source_pred = rdf_make_iri(arena, vocab_OWL_SOURCE_INDIVIDUAL);
        __auto_type assert_pred = rdf_make_iri(arena, vocab_OWL_ASSERTION_PROPERTY);
        __auto_type target_pred = rdf_make_iri(arena, vocab_OWL_TARGET_VALUE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type npa_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = source_pred}, no_term);
            {
                __auto_type _coll = npa_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type npa_triple = _coll.data[_i];
                    {
                        __auto_type x = rdf_triple_subject(npa_triple);
                        __auto_type s = rdf_triple_object(npa_triple);
                        {
                            __auto_type ap_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = x}, (slop_option_rdf_Term){.has_value = 1, .value = assert_pred}, no_term);
                            {
                                __auto_type _coll = ap_triples;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type ap_triple = _coll.data[_i];
                                    {
                                        __auto_type p = rdf_triple_object(ap_triple);
                                        {
                                            __auto_type tv_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = x}, (slop_option_rdf_Term){.has_value = 1, .value = target_pred}, no_term);
                                            {
                                                __auto_type _coll = tv_triples;
                                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                                    __auto_type tv_triple = _coll.data[_i];
                                                    {
                                                        __auto_type v = rdf_triple_object(tv_triple);
                                                        __auto_type asserted = rdf_make_triple(arena, s, p, v);
                                                        if (rdf_indexed_graph_contains(g, asserted)) {
                                                            return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("prp-npa2: negative property assertion violated (literal)"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 4 * sizeof(rdf_Triple)), .len = 4, .cap = 4 }; _ll.data[0] = asserted; _ll.data[1] = npa_triple; _ll.data[2] = ap_triple; _ll.data[3] = tv_triple; _ll; })})};
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
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 1); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 1)))");
    return _retval;
}

slop_list_rdf_Triple prp_prp_spo2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type chain_pred = rdf_make_iri(arena, vocab_OWL_PROPERTY_CHAIN_AXIOM);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        {
            __auto_type chain_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = chain_pred}, no_term);
            {
                __auto_type _coll = chain_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type chain_triple = _coll.data[_i];
                    {
                        __auto_type target_prop = rdf_triple_subject(chain_triple);
                        __auto_type list_head = rdf_triple_object(chain_triple);
                        __auto_type chain_props = rdf_list_elements_indexed(arena, g, list_head);
                        __auto_type chain_len = ((int64_t)((chain_props).len));
                        if ((chain_len >= 2)) {
                            {
                                __auto_type _coll = delta.triples;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type dt = _coll.data[_i];
                                    {
                                        __auto_type dt_pred = rdf_triple_predicate(dt);
                                        {
                                            int64_t ci = 0;
                                            while ((ci < chain_len)) {
                                                __auto_type _mv_176 = ({ __auto_type _lst = chain_props; size_t _idx = (size_t)ci; slop_option_rdf_Term _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                if (_mv_176.has_value) {
                                                    __auto_type chain_p = _mv_176.value;
                                                    if (rdf_term_eq(dt_pred, chain_p)) {
                                                        {
                                                            __auto_type starts = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
                                                            ({ __auto_type _lst_p = &(starts); __auto_type _item = (rdf_triple_subject(dt)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                            {
                                                                __auto_type bi = (ci - 1);
                                                                while ((bi >= 0)) {
                                                                    __auto_type _mv_177 = ({ __auto_type _lst = chain_props; size_t _idx = (size_t)bi; slop_option_rdf_Term _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                                    if (_mv_177.has_value) {
                                                                        __auto_type prev_p = _mv_177.value;
                                                                        {
                                                                            __auto_type new_starts = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
                                                                            {
                                                                                __auto_type _coll = starts;
                                                                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                    __auto_type s = _coll.data[_i];
                                                                                    {
                                                                                        __auto_type back_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = prev_p}, (slop_option_rdf_Term){.has_value = 1, .value = s});
                                                                                        {
                                                                                            __auto_type _coll = back_triples;
                                                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                                __auto_type bt = _coll.data[_i];
                                                                                                ({ __auto_type _lst_p = &(new_starts); __auto_type _item = (rdf_triple_subject(bt)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                            starts = new_starts;
                                                                        }
                                                                    } else if (!_mv_177.has_value) {
                                                                    }
                                                                    bi = (bi - 1);
                                                                }
                                                            }
                                                            {
                                                                __auto_type ends = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
                                                                ({ __auto_type _lst_p = &(ends); __auto_type _item = (rdf_triple_object(dt)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                {
                                                                    __auto_type fi = (ci + 1);
                                                                    while ((fi < chain_len)) {
                                                                        __auto_type _mv_178 = ({ __auto_type _lst = chain_props; size_t _idx = (size_t)fi; slop_option_rdf_Term _r; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                                        if (_mv_178.has_value) {
                                                                            __auto_type next_p = _mv_178.value;
                                                                            {
                                                                                __auto_type new_ends = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
                                                                                {
                                                                                    __auto_type _coll = ends;
                                                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                        __auto_type e = _coll.data[_i];
                                                                                        {
                                                                                            __auto_type fwd_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = e}, (slop_option_rdf_Term){.has_value = 1, .value = next_p}, no_term);
                                                                                            {
                                                                                                __auto_type _coll = fwd_triples;
                                                                                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                                    __auto_type ft = _coll.data[_i];
                                                                                                    ({ __auto_type _lst_p = &(new_ends); __auto_type _item = (rdf_triple_object(ft)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                ends = new_ends;
                                                                            }
                                                                        } else if (!_mv_178.has_value) {
                                                                        }
                                                                        fi = (fi + 1);
                                                                    }
                                                                }
                                                                {
                                                                    __auto_type _coll = starts;
                                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                        __auto_type s = _coll.data[_i];
                                                                        {
                                                                            __auto_type _coll = ends;
                                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                __auto_type e = _coll.data[_i];
                                                                                {
                                                                                    __auto_type inferred = rdf_make_triple(arena, s, target_prop, e);
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
                                                } else if (!_mv_176.has_value) {
                                                }
                                                ci = (ci + 1);
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
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_key(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type key_pred = rdf_make_iri(arena, vocab_OWL_HAS_KEY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        {
            __auto_type key_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = key_pred}, no_term);
            {
                __auto_type _coll = key_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type key_triple = _coll.data[_i];
                    {
                        __auto_type key_class = rdf_triple_subject(key_triple);
                        __auto_type list_head = rdf_triple_object(key_triple);
                        __auto_type key_props = rdf_list_elements_indexed(arena, g, list_head);
                        __auto_type num_keys = ((int64_t)((key_props).len));
                        if ((num_keys > 0)) {
                            __auto_type _mv_179 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                            if (_mv_179.has_value) {
                                __auto_type type_triples = _mv_179.value;
                                {
                                    slop_map* _coll = (slop_map*)type_triples;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                                            if (rdf_term_eq(rdf_triple_object(dt), key_class)) {
                                                {
                                                    __auto_type x = rdf_triple_subject(dt);
                                                    {
                                                        __auto_type x_has_all_keys = 1;
                                                        {
                                                            __auto_type _coll = key_props;
                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                __auto_type kp = _coll.data[_i];
                                                                {
                                                                    __auto_type x_vals = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = x}, (slop_option_rdf_Term){.has_value = 1, .value = kp}, no_term);
                                                                    if ((((int64_t)((x_vals).len)) == 0)) {
                                                                        x_has_all_keys = 0;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        if (x_has_all_keys) {
                                                            {
                                                                __auto_type y_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = key_class});
                                                                {
                                                                    __auto_type _coll = y_triples;
                                                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                        __auto_type yt = _coll.data[_i];
                                                                        {
                                                                            __auto_type y = rdf_triple_subject(yt);
                                                                            if (!(rdf_term_eq(x, y))) {
                                                                                {
                                                                                    __auto_type all_match = 1;
                                                                                    {
                                                                                        __auto_type _coll = key_props;
                                                                                        for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                            __auto_type kp = _coll.data[_i];
                                                                                            if (all_match) {
                                                                                                {
                                                                                                    __auto_type x_vals = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = x}, (slop_option_rdf_Term){.has_value = 1, .value = kp}, no_term);
                                                                                                    __auto_type found_match = 0;
                                                                                                    {
                                                                                                        __auto_type _coll = x_vals;
                                                                                                        for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                                            __auto_type xvt = _coll.data[_i];
                                                                                                            {
                                                                                                                __auto_type y_has = rdf_make_triple(arena, y, kp, rdf_triple_object(xvt));
                                                                                                                if (rdf_indexed_graph_contains(g, y_has)) {
                                                                                                                    found_match = 1;
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                    if (!(found_match)) {
                                                                                                        all_match = 0;
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    if (all_match) {
                                                                                        {
                                                                                            __auto_type inferred = rdf_make_triple(arena, x, same_as, y);
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
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else if (!_mv_179.has_value) {
                            }
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

slop_list_rdf_Triple prp_prp_spo1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        {
            __auto_type _coll = delta.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type dt = _coll.data[_i];
                {
                    __auto_type x = rdf_triple_subject(dt);
                    __auto_type p1 = rdf_triple_predicate(dt);
                    __auto_type y = rdf_triple_object(dt);
                    rdf_indexed_graph_for_each(g, (slop_option_rdf_Term){.has_value = 1, .value = p1}, (slop_option_rdf_Term){.has_value = 1, .value = subprop_pred}, no_term, ({ prp__lambda_180_env_t* prp__lambda_180_env = (prp__lambda_180_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_180_env_t)); *prp__lambda_180_env = (prp__lambda_180_env_t){ .arena = arena, .x = x, .y = y, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_180, (void*)prp__lambda_180_env }; }));
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_inv1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type inverse_pred = rdf_make_iri(arena, vocab_OWL_INVERSE_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = inverse_pred}, no_term, ({ prp__lambda_181_env_t* prp__lambda_181_env = (prp__lambda_181_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_181_env_t)); *prp__lambda_181_env = (prp__lambda_181_env_t){ .delta = delta, .arena = arena, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_181, (void*)prp__lambda_181_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_inv2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type inverse_pred = rdf_make_iri(arena, vocab_OWL_INVERSE_OF);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = inverse_pred}, no_term, ({ prp__lambda_182_env_t* prp__lambda_182_env = (prp__lambda_182_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_182_env_t)); *prp__lambda_182_env = (prp__lambda_182_env_t){ .delta = delta, .arena = arena, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_182, (void*)prp__lambda_182_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_eqp1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = equiv_pred}, no_term, ({ prp__lambda_183_env_t* prp__lambda_183_env = (prp__lambda_183_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_183_env_t)); *prp__lambda_183_env = (prp__lambda_183_env_t){ .delta = delta, .arena = arena, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_183, (void*)prp__lambda_183_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple prp_prp_eqp2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_PROPERTY);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = equiv_pred}, no_term, ({ prp__lambda_184_env_t* prp__lambda_184_env = (prp__lambda_184_env_t*)slop_arena_alloc(arena, sizeof(prp__lambda_184_env_t)); *prp__lambda_184_env = (prp__lambda_184_env_t){ .delta = delta, .arena = arena, .g = g, .result = &(result) }; (slop_closure_t){ (void*)prp__lambda_184, (void*)prp__lambda_184_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_option_types_InconsistencyReport prp_prp_pdw(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type pdw_pred = rdf_make_iri(arena, vocab_OWL_PROPERTY_DISJOINT_WITH);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type pdw_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = pdw_pred}, no_term);
            {
                __auto_type _coll = pdw_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type pdw_triple = _coll.data[_i];
                    {
                        __auto_type p1 = rdf_triple_subject(pdw_triple);
                        __auto_type p2 = rdf_triple_object(pdw_triple);
                        __auto_type _mv_185 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(p1)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                        if (_mv_185.has_value) {
                            __auto_type pred_triples = _mv_185.value;
                            {
                                slop_map* _coll = (slop_map*)pred_triples;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                                        {
                                            __auto_type x = rdf_triple_subject(dt);
                                            __auto_type y = rdf_triple_object(dt);
                                            __auto_type conflict = rdf_make_triple(arena, x, p2, y);
                                            if (rdf_indexed_graph_contains(g, conflict)) {
                                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("prp-pdw: disjoint properties both asserted"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = conflict; _ll.data[2] = pdw_triple; _ll; })})};
                                            }
                                        }
                                    }
                                }
                            }
                        } else if (!_mv_185.has_value) {
                        }
                        __auto_type _mv_186 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(p2)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                        if (_mv_186.has_value) {
                            __auto_type pred_triples = _mv_186.value;
                            {
                                slop_map* _coll = (slop_map*)pred_triples;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                                        {
                                            __auto_type x = rdf_triple_subject(dt);
                                            __auto_type y = rdf_triple_object(dt);
                                            __auto_type conflict = rdf_make_triple(arena, x, p1, y);
                                            if (rdf_indexed_graph_contains(g, conflict)) {
                                                return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("prp-pdw: disjoint properties both asserted"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = conflict; _ll.data[2] = pdw_triple; _ll; })})};
                                            }
                                        }
                                    }
                                }
                            }
                        } else if (!_mv_186.has_value) {
                        }
                    }
                }
            }
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 3); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 3)))");
    return _retval;
}

slop_list_rdf_Triple prp_prp_ap(slop_arena* arena, index_IndexedGraph g) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type annot_class = rdf_make_iri(arena, vocab_OWL_ANNOTATION_PROPERTY);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type props = ((slop_list_string){ .data = (slop_string*)slop_arena_alloc(arena, 16 * sizeof(slop_string)), .len = 0, .cap = 16 });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_RDFS_LABEL); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_RDFS_COMMENT); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_RDFS_SEE_ALSO); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_RDFS_IS_DEFINED_BY); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_OWL_DEPRECATED); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_OWL_VERSION_INFO); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_OWL_PRIOR_VERSION); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_OWL_BACKWARD_COMPATIBLE_WITH); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(props); __auto_type _item = (vocab_OWL_INCOMPATIBLE_WITH); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type _coll = props;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type p_iri = _coll.data[_i];
                {
                    __auto_type p_term = rdf_make_iri(arena, p_iri);
                    __auto_type inferred = rdf_make_triple(arena, p_term, type_pred, annot_class);
                    if (!(rdf_indexed_graph_contains(g, inferred))) {
                        ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

