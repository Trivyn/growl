#include "../runtime/slop_runtime.h"
#include "slop_cls.h"

static const slop_string cls_EX_ALICE = SLOP_STR("http://example.org/alice");
static const slop_string cls_EX_BOB = SLOP_STR("http://example.org/bob");
static const slop_string cls_EX_FIDO = SLOP_STR("http://example.org/fido");
static const slop_string cls_EX_MARY = SLOP_STR("http://example.org/mary");
static const slop_string cls_EX_MARIA = SLOP_STR("http://example.org/maria");
static const slop_string cls_EX_USA = SLOP_STR("http://example.org/USA");
static const slop_string cls_EX_MONDAY = SLOP_STR("http://example.org/Monday");
static const slop_string cls_EX_TUESDAY = SLOP_STR("http://example.org/Tuesday");
static const slop_string cls_EX_WEDNESDAY = SLOP_STR("http://example.org/Wednesday");
static const slop_string cls_EX_PERSON = SLOP_STR("http://example.org/Person");
static const slop_string cls_EX_FEMALE = SLOP_STR("http://example.org/Female");
static const slop_string cls_EX_PARENT = SLOP_STR("http://example.org/Parent");
static const slop_string cls_EX_FEMALE_PARENT = SLOP_STR("http://example.org/FemaleParent");
static const slop_string cls_EX_MAN = SLOP_STR("http://example.org/Man");
static const slop_string cls_EX_WOMAN = SLOP_STR("http://example.org/Woman");
static const slop_string cls_EX_NOT_PARENT = SLOP_STR("http://example.org/NotParent");
static const slop_string cls_EX_DOG = SLOP_STR("http://example.org/Dog");
static const slop_string cls_EX_DOG_OWNER = SLOP_STR("http://example.org/DogOwner");
static const slop_string cls_EX_PET_OWNER = SLOP_STR("http://example.org/PetOwner");
static const slop_string cls_EX_HUMAN = SLOP_STR("http://example.org/Human");
static const slop_string cls_EX_PERSON_WITH_HUMAN_CHILDREN = SLOP_STR("http://example.org/PersonWithOnlyHumanChildren");
static const slop_string cls_EX_US_CITIZEN = SLOP_STR("http://example.org/USCitizen");
static const slop_string cls_EX_HAS_ONE_MOTHER = SLOP_STR("http://example.org/HasOneMother");
static const slop_string cls_EX_DAYS_OF_WEEK = SLOP_STR("http://example.org/DaysOfWeek");
static const slop_string cls_EX_HAS_PET = SLOP_STR("http://example.org/hasPet");
static const slop_string cls_EX_HAS_CHILD = SLOP_STR("http://example.org/hasChild");
static const slop_string cls_EX_CITIZENSHIP = SLOP_STR("http://example.org/citizenship");
static const slop_string cls_EX_HAS_MOTHER = SLOP_STR("http://example.org/hasMother");

rdf_Term cls_fixture_build_list2(slop_arena* arena, index_IndexedGraph g, rdf_Term e1, rdf_Term e2);
rdf_Term cls_fixture_build_list3(slop_arena* arena, index_IndexedGraph g, rdf_Term e1, rdf_Term e2, rdf_Term e3);
index_IndexedGraph cls_fixture_g_nothing(slop_arena* arena);
types_Delta cls_fixture_delta_nothing(slop_arena* arena);
index_IndexedGraph cls_fixture_g_intersection(slop_arena* arena);
types_Delta cls_fixture_delta_intersection(slop_arena* arena);
index_IndexedGraph cls_fixture_g_intersection2(slop_arena* arena);
types_Delta cls_fixture_delta_int2(slop_arena* arena);
index_IndexedGraph cls_fixture_g_union(slop_arena* arena);
types_Delta cls_fixture_delta_union(slop_arena* arena);
index_IndexedGraph cls_fixture_g_complement_violation(slop_arena* arena);
types_Delta cls_fixture_delta_complement(slop_arena* arena);
index_IndexedGraph cls_fixture_g_svf(slop_arena* arena);
types_Delta cls_fixture_delta_svf(slop_arena* arena);
index_IndexedGraph cls_fixture_g_svf1(slop_arena* arena);
types_Delta cls_fixture_delta_svf1(slop_arena* arena);
index_IndexedGraph cls_fixture_g_avf(slop_arena* arena);
types_Delta cls_fixture_delta_avf(slop_arena* arena);
index_IndexedGraph cls_fixture_g_hv(slop_arena* arena);
types_Delta cls_fixture_delta_hv1(slop_arena* arena);
types_Delta cls_fixture_delta_hv2(slop_arena* arena);
index_IndexedGraph cls_fixture_g_maxc1(slop_arena* arena);
types_Delta cls_fixture_delta_maxc(slop_arena* arena);
index_IndexedGraph cls_fixture_g_one_of(slop_arena* arena);
types_Delta cls_fixture_delta_one_of(slop_arena* arena);
slop_result_types_Delta_types_InconsistencyReport cls_apply_cls_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast);
slop_list_rdf_Triple cls_cls_thing(slop_arena* arena, index_IndexedGraph g);
slop_list_rdf_Triple cls_cls_nothing1(slop_arena* arena, index_IndexedGraph g);
slop_option_types_InconsistencyReport cls_cls_nothing2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_int1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_int2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_uni(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport cls_cls_com(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_svf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_svf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_avf(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_hv1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_hv2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_maxc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_maxc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport cls_cls_maxqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport cls_cls_maxqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_maxqc3(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_maxqc4(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cls_cls_oo(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

typedef struct { slop_arena* arena; index_IndexedGraph g; types_Delta delta; rdf_Term type_pred; slop_list_rdf_Triple* result; } cls__lambda_107_env_t;

static void cls__lambda_107(cls__lambda_107_env_t* _env, rdf_Triple int_triple) { ({ __auto_type int_class = rdf_triple_subject(int_triple); __auto_type list_head = rdf_triple_object(int_triple); __auto_type component_classes = rdf_list_elements_indexed(_env->arena, _env->g, list_head); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(_env->type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type individual = rdf_triple_subject(dt); __auto_type asserted_class = rdf_triple_object(dt); ({ __auto_type is_component = 0; ({ __auto_type _coll = component_classes; for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type comp = _coll.data[_i]; ((rdf_term_eq(comp, asserted_class)) ? ({ ({ is_component = 1; (void)0; }); 0; }) : ({ (void)0; })); } 0; }); ((is_component) ? ({ ({ __auto_type all_satisfied = 1; ({ __auto_type _coll = component_classes; for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type comp = _coll.data[_i]; ({ __auto_type type_triple = rdf_make_triple(_env->arena, individual, _env->type_pred, comp); ((!(rdf_indexed_graph_contains(_env->g, type_triple))) ? ({ ({ all_satisfied = 0; (void)0; }); 0; }) : ({ (void)0; })); }); } 0; }); ((all_satisfied) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, individual, _env->type_pred, int_class); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { slop_arena* arena; index_IndexedGraph g; types_Delta delta; rdf_Term type_pred; slop_list_rdf_Triple* result; } cls__lambda_108_env_t;

static void cls__lambda_108(cls__lambda_108_env_t* _env, rdf_Triple int_triple) { ({ __auto_type int_class = rdf_triple_subject(int_triple); __auto_type list_head = rdf_triple_object(int_triple); __auto_type component_classes = rdf_list_elements_indexed(_env->arena, _env->g, list_head); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(_env->type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ((rdf_term_eq(rdf_triple_object(dt), int_class)) ? ({ ({ __auto_type individual = rdf_triple_subject(dt); ({ __auto_type _coll = component_classes; for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type comp = _coll.data[_i]; ({ __auto_type inferred = rdf_make_triple(_env->arena, individual, _env->type_pred, comp); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } 0; }); }); 0; }) : ({ (void)0; })); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { slop_arena* arena; index_IndexedGraph g; types_Delta delta; rdf_Term type_pred; slop_list_rdf_Triple* result; } cls__lambda_109_env_t;

static void cls__lambda_109(cls__lambda_109_env_t* _env, rdf_Triple union_triple) { ({ __auto_type union_class = rdf_triple_subject(union_triple); __auto_type list_head = rdf_triple_object(union_triple); __auto_type component_classes = rdf_list_elements_indexed(_env->arena, _env->g, list_head); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(_env->type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type individual = rdf_triple_subject(dt); __auto_type asserted_class = rdf_triple_object(dt); ({ __auto_type _coll = component_classes; for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type comp = _coll.data[_i]; ((rdf_term_eq(comp, asserted_class)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, individual, _env->type_pred, union_class); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); } 0; }); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; types_Delta delta; slop_arena* arena; rdf_Term type_pred; slop_list_rdf_Triple* result; } cls__lambda_111_env_t;

typedef struct { types_Delta delta; slop_arena* arena; rdf_Term type_pred; rdf_Term restriction; index_IndexedGraph g; slop_list_rdf_Triple* result; } cls__lambda_112_env_t;

static void cls__lambda_112(cls__lambda_112_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(property)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type u = rdf_triple_subject(dt); __auto_type inferred = rdf_make_triple(_env->arena, u, _env->type_pred, _env->restriction); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

static void cls__lambda_111(cls__lambda_111_env_t* _env, rdf_Triple svf_triple) { ({ __auto_type restriction = rdf_triple_subject(svf_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_112_env_t* cls__lambda_112_env = (cls__lambda_112_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_112_env_t)); *cls__lambda_112_env = (cls__lambda_112_env_t){ .delta = _env->delta, .arena = _env->arena, .type_pred = _env->type_pred, .restriction = restriction, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_112, (void*)cls__lambda_112_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; types_Delta delta; rdf_Term type_pred; slop_arena* arena; slop_list_rdf_Triple* result; } cls__lambda_113_env_t;

typedef struct { types_Delta delta; rdf_Term type_pred; rdf_Term value_class; index_IndexedGraph g; slop_option_rdf_Term no_term; slop_arena* arena; rdf_Term restriction; slop_list_rdf_Triple* result; } cls__lambda_114_env_t;

typedef struct { slop_arena* arena; rdf_Term type_pred; rdf_Term restriction; index_IndexedGraph g; slop_list_rdf_Triple* result; } cls__lambda_115_env_t;

static void cls__lambda_115(cls__lambda_115_env_t* _env, rdf_Triple usage_triple) { ({ __auto_type u = rdf_triple_subject(usage_triple); __auto_type inferred = rdf_make_triple(_env->arena, u, _env->type_pred, _env->restriction); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

static void cls__lambda_114(cls__lambda_114_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(_env->type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ((rdf_term_eq(rdf_triple_object(dt), _env->value_class)) ? ({ ({ __auto_type v = rdf_triple_subject(dt); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = property}, (slop_option_rdf_Term){.has_value = 1, .value = v}, ({ cls__lambda_115_env_t* cls__lambda_115_env = (cls__lambda_115_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_115_env_t)); *cls__lambda_115_env = (cls__lambda_115_env_t){ .arena = _env->arena, .type_pred = _env->type_pred, .restriction = _env->restriction, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_115, (void*)cls__lambda_115_env }; })); }); 0; }) : ({ (void)0; })); } } 0; }); } else { ({ (void)0; }); } (void)0; }); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(property)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type u = rdf_triple_subject(dt); __auto_type v = rdf_triple_object(dt); __auto_type v_type = rdf_make_triple(_env->arena, v, _env->type_pred, _env->value_class); ((rdf_indexed_graph_contains(_env->g, v_type)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, u, _env->type_pred, _env->restriction); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

static void cls__lambda_113(cls__lambda_113_env_t* _env, rdf_Triple svf_triple) { ({ __auto_type restriction = rdf_triple_subject(svf_triple); __auto_type value_class = rdf_triple_object(svf_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_114_env_t* cls__lambda_114_env = (cls__lambda_114_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_114_env_t)); *cls__lambda_114_env = (cls__lambda_114_env_t){ .delta = _env->delta, .type_pred = _env->type_pred, .value_class = value_class, .g = _env->g, .no_term = _env->no_term, .arena = _env->arena, .restriction = restriction, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_114, (void*)cls__lambda_114_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; types_Delta delta; rdf_Term type_pred; slop_arena* arena; slop_list_rdf_Triple* result; } cls__lambda_116_env_t;

typedef struct { types_Delta delta; rdf_Term type_pred; rdf_Term restriction; index_IndexedGraph g; slop_option_rdf_Term no_term; slop_arena* arena; rdf_Term value_class; slop_list_rdf_Triple* result; } cls__lambda_117_env_t;

typedef struct { slop_arena* arena; rdf_Term type_pred; rdf_Term value_class; index_IndexedGraph g; slop_list_rdf_Triple* result; } cls__lambda_118_env_t;

static void cls__lambda_118(cls__lambda_118_env_t* _env, rdf_Triple usage_triple) { ({ __auto_type v = rdf_triple_object(usage_triple); __auto_type inferred = rdf_make_triple(_env->arena, v, _env->type_pred, _env->value_class); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); }

static void cls__lambda_117(cls__lambda_117_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(_env->type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ((rdf_term_eq(rdf_triple_object(dt), _env->restriction)) ? ({ ({ __auto_type u = rdf_triple_subject(dt); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = u}, (slop_option_rdf_Term){.has_value = 1, .value = property}, _env->no_term, ({ cls__lambda_118_env_t* cls__lambda_118_env = (cls__lambda_118_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_118_env_t)); *cls__lambda_118_env = (cls__lambda_118_env_t){ .arena = _env->arena, .type_pred = _env->type_pred, .value_class = _env->value_class, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_118, (void*)cls__lambda_118_env }; })); }); 0; }) : ({ (void)0; })); } } 0; }); } else { ({ (void)0; }); } (void)0; }); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(property)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ({ __auto_type u = rdf_triple_subject(dt); __auto_type v = rdf_triple_object(dt); __auto_type u_type = rdf_make_triple(_env->arena, u, _env->type_pred, _env->restriction); ((rdf_indexed_graph_contains(_env->g, u_type)) ? ({ ({ __auto_type inferred = rdf_make_triple(_env->arena, v, _env->type_pred, _env->value_class); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); }); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

static void cls__lambda_116(cls__lambda_116_env_t* _env, rdf_Triple avf_triple) { ({ __auto_type restriction = rdf_triple_subject(avf_triple); __auto_type value_class = rdf_triple_object(avf_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_117_env_t* cls__lambda_117_env = (cls__lambda_117_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_117_env_t)); *cls__lambda_117_env = (cls__lambda_117_env_t){ .delta = _env->delta, .type_pred = _env->type_pred, .restriction = restriction, .g = _env->g, .no_term = _env->no_term, .arena = _env->arena, .value_class = value_class, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_117, (void*)cls__lambda_117_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; types_Delta delta; rdf_Term type_pred; slop_arena* arena; slop_list_rdf_Triple* result; } cls__lambda_119_env_t;

typedef struct { types_Delta delta; rdf_Term type_pred; rdf_Term restriction; slop_arena* arena; rdf_Term value; index_IndexedGraph g; slop_list_rdf_Triple* result; } cls__lambda_120_env_t;

static void cls__lambda_120(cls__lambda_120_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(_env->type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ((rdf_term_eq(rdf_triple_object(dt), _env->restriction)) ? ({ ({ __auto_type u = rdf_triple_subject(dt); __auto_type inferred = rdf_make_triple(_env->arena, u, property, _env->value); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

static void cls__lambda_119(cls__lambda_119_env_t* _env, rdf_Triple hv_triple) { ({ __auto_type restriction = rdf_triple_subject(hv_triple); __auto_type value = rdf_triple_object(hv_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_120_env_t* cls__lambda_120_env = (cls__lambda_120_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_120_env_t)); *cls__lambda_120_env = (cls__lambda_120_env_t){ .delta = _env->delta, .type_pred = _env->type_pred, .restriction = restriction, .arena = _env->arena, .value = value, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_120, (void*)cls__lambda_120_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; types_Delta delta; slop_arena* arena; rdf_Term type_pred; slop_list_rdf_Triple* result; } cls__lambda_121_env_t;

typedef struct { types_Delta delta; rdf_Term value; slop_arena* arena; rdf_Term type_pred; rdf_Term restriction; index_IndexedGraph g; slop_list_rdf_Triple* result; } cls__lambda_122_env_t;

static void cls__lambda_122(cls__lambda_122_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); ({ __auto_type _mv = ({ void* _ptr = slop_map_get(_env->delta.by_predicate, &(property)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; }); if (_mv.has_value) { __auto_type pred_triples = _mv.value; ({ slop_map* _coll = (slop_map*)pred_triples; for (size_t _i = 0; _i < _coll->cap; _i++) { if (_coll->entries[_i].occupied) { rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key; ((rdf_term_eq(rdf_triple_object(dt), _env->value)) ? ({ ({ __auto_type u = rdf_triple_subject(dt); __auto_type inferred = rdf_make_triple(_env->arena, u, _env->type_pred, _env->restriction); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); 0; }) : ({ (void)0; })); } } 0; }); } else { ({ (void)0; }); } (void)0; }); }); }

static void cls__lambda_121(cls__lambda_121_env_t* _env, rdf_Triple hv_triple) { ({ __auto_type restriction = rdf_triple_subject(hv_triple); __auto_type value = rdf_triple_object(hv_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_122_env_t* cls__lambda_122_env = (cls__lambda_122_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_122_env_t)); *cls__lambda_122_env = (cls__lambda_122_env_t){ .delta = _env->delta, .value = value, .arena = _env->arena, .type_pred = _env->type_pred, .restriction = restriction, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_122, (void*)cls__lambda_122_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; rdf_Term type_pred; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_123_env_t;

typedef struct { index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term type_pred; rdf_Term restriction; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_124_env_t;

typedef struct { index_IndexedGraph g; rdf_Term property; slop_option_rdf_Term no_term; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_125_env_t;

typedef struct { slop_option_rdf_Term first_val; slop_arena* arena; rdf_Term same_as; index_IndexedGraph g; slop_list_rdf_Triple* result; } cls__lambda_126_env_t;

static void cls__lambda_126(cls__lambda_126_env_t* _env, rdf_Triple value_triple) { ({ __auto_type val = rdf_triple_object(value_triple); ({ __auto_type _mv = _env->first_val; if (_mv.has_value) { __auto_type fv = _mv.value; ({ __auto_type inferred = rdf_make_triple(_env->arena, fv, _env->same_as, val); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } else { ({ _env->first_val = (slop_option_rdf_Term){.has_value = 1, .value = val}; (void)0; }); } (void)0; }); }); }

static void cls__lambda_125(cls__lambda_125_env_t* _env, rdf_Triple type_triple) { ({ __auto_type individual = rdf_triple_subject(type_triple); slop_option_rdf_Term first_val = (slop_option_rdf_Term){.has_value = false}; rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = individual}, (slop_option_rdf_Term){.has_value = 1, .value = _env->property}, _env->no_term, ({ cls__lambda_126_env_t* cls__lambda_126_env = (cls__lambda_126_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_126_env_t)); *cls__lambda_126_env = (cls__lambda_126_env_t){ .first_val = first_val, .arena = _env->arena, .same_as = _env->same_as, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_126, (void*)cls__lambda_126_env }; })); }); }

static void cls__lambda_124(cls__lambda_124_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->restriction}, ({ cls__lambda_125_env_t* cls__lambda_125_env = (cls__lambda_125_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_125_env_t)); *cls__lambda_125_env = (cls__lambda_125_env_t){ .g = _env->g, .property = property, .no_term = _env->no_term, .arena = _env->arena, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_125, (void*)cls__lambda_125_env }; })); }); }

static void cls__lambda_123(cls__lambda_123_env_t* _env, rdf_Triple maxc_triple) { ({ __auto_type restriction = rdf_triple_subject(maxc_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_124_env_t* cls__lambda_124_env = (cls__lambda_124_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_124_env_t)); *cls__lambda_124_env = (cls__lambda_124_env_t){ .g = _env->g, .no_term = _env->no_term, .type_pred = _env->type_pred, .restriction = restriction, .arena = _env->arena, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_124, (void*)cls__lambda_124_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; rdf_Term on_class_pred; rdf_Term thing; rdf_Term type_pred; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_127_env_t;

typedef struct { index_IndexedGraph g; rdf_Term restriction; rdf_Term on_class_pred; slop_option_rdf_Term no_term; rdf_Term thing; rdf_Term type_pred; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_128_env_t;

typedef struct { rdf_Term thing; index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term type_pred; rdf_Term restriction; rdf_Term property; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_129_env_t;

typedef struct { index_IndexedGraph g; rdf_Term property; slop_option_rdf_Term no_term; slop_arena* arena; rdf_Term type_pred; rdf_Term qual_class; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_130_env_t;

typedef struct { slop_arena* arena; rdf_Term type_pred; rdf_Term qual_class; index_IndexedGraph g; slop_option_rdf_Term first_qualified; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_131_env_t;

static void cls__lambda_131(cls__lambda_131_env_t* _env, rdf_Triple val_triple) { ({ __auto_type y = rdf_triple_object(val_triple); __auto_type y_type = rdf_make_triple(_env->arena, y, _env->type_pred, _env->qual_class); ((rdf_indexed_graph_contains(_env->g, y_type)) ? ({ ({ __auto_type _mv = _env->first_qualified; if (_mv.has_value) { __auto_type fv = _mv.value; ({ __auto_type inferred = rdf_make_triple(_env->arena, fv, _env->same_as, y); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } else { ({ _env->first_qualified = (slop_option_rdf_Term){.has_value = 1, .value = y}; (void)0; }); } (void)0; }); 0; }) : ({ (void)0; })); }); }

static void cls__lambda_130(cls__lambda_130_env_t* _env, rdf_Triple inst_triple) { ({ __auto_type u = rdf_triple_subject(inst_triple); slop_option_rdf_Term first_qualified = (slop_option_rdf_Term){.has_value = false}; rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = u}, (slop_option_rdf_Term){.has_value = 1, .value = _env->property}, _env->no_term, ({ cls__lambda_131_env_t* cls__lambda_131_env = (cls__lambda_131_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_131_env_t)); *cls__lambda_131_env = (cls__lambda_131_env_t){ .arena = _env->arena, .type_pred = _env->type_pred, .qual_class = _env->qual_class, .g = _env->g, .first_qualified = first_qualified, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_131, (void*)cls__lambda_131_env }; })); }); }

static void cls__lambda_129(cls__lambda_129_env_t* _env, rdf_Triple class_triple) { ({ __auto_type qual_class = rdf_triple_object(class_triple); ((!(rdf_term_eq(qual_class, _env->thing))) ? ({ rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->restriction}, ({ cls__lambda_130_env_t* cls__lambda_130_env = (cls__lambda_130_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_130_env_t)); *cls__lambda_130_env = (cls__lambda_130_env_t){ .g = _env->g, .property = _env->property, .no_term = _env->no_term, .arena = _env->arena, .type_pred = _env->type_pred, .qual_class = qual_class, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_130, (void*)cls__lambda_130_env }; })); 0; }) : ({ (void)0; })); }); }

static void cls__lambda_128(cls__lambda_128_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = _env->restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_class_pred}, _env->no_term, ({ cls__lambda_129_env_t* cls__lambda_129_env = (cls__lambda_129_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_129_env_t)); *cls__lambda_129_env = (cls__lambda_129_env_t){ .thing = _env->thing, .g = _env->g, .no_term = _env->no_term, .type_pred = _env->type_pred, .restriction = _env->restriction, .property = property, .arena = _env->arena, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_129, (void*)cls__lambda_129_env }; })); }); }

static void cls__lambda_127(cls__lambda_127_env_t* _env, rdf_Triple mqc_triple) { ({ __auto_type restriction = rdf_triple_subject(mqc_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_128_env_t* cls__lambda_128_env = (cls__lambda_128_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_128_env_t)); *cls__lambda_128_env = (cls__lambda_128_env_t){ .g = _env->g, .restriction = restriction, .on_class_pred = _env->on_class_pred, .no_term = _env->no_term, .thing = _env->thing, .type_pred = _env->type_pred, .arena = _env->arena, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_128, (void*)cls__lambda_128_env }; })); }); }

typedef struct { index_IndexedGraph g; rdf_Term on_prop_pred; slop_option_rdf_Term no_term; rdf_Term on_class_pred; rdf_Term thing; rdf_Term type_pred; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_132_env_t;

typedef struct { index_IndexedGraph g; rdf_Term restriction; rdf_Term on_class_pred; slop_option_rdf_Term no_term; rdf_Term thing; rdf_Term type_pred; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_133_env_t;

typedef struct { rdf_Term thing; index_IndexedGraph g; slop_option_rdf_Term no_term; rdf_Term type_pred; rdf_Term restriction; rdf_Term property; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_134_env_t;

typedef struct { index_IndexedGraph g; rdf_Term property; slop_option_rdf_Term no_term; slop_arena* arena; rdf_Term same_as; slop_list_rdf_Triple* result; } cls__lambda_135_env_t;

typedef struct { slop_option_rdf_Term first_val; slop_arena* arena; rdf_Term same_as; index_IndexedGraph g; slop_list_rdf_Triple* result; } cls__lambda_136_env_t;

static void cls__lambda_136(cls__lambda_136_env_t* _env, rdf_Triple val_triple) { ({ __auto_type y = rdf_triple_object(val_triple); ({ __auto_type _mv = _env->first_val; if (_mv.has_value) { __auto_type fv = _mv.value; ({ __auto_type inferred = rdf_make_triple(_env->arena, fv, _env->same_as, y); ((!(rdf_indexed_graph_contains(_env->g, inferred))) ? ({ ({ __auto_type _lst_p = &((*_env->result)); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(_env->arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); 0; }) : ({ (void)0; })); }); } else { ({ _env->first_val = (slop_option_rdf_Term){.has_value = 1, .value = y}; (void)0; }); } (void)0; }); }); }

static void cls__lambda_135(cls__lambda_135_env_t* _env, rdf_Triple inst_triple) { ({ __auto_type u = rdf_triple_subject(inst_triple); slop_option_rdf_Term first_val = (slop_option_rdf_Term){.has_value = false}; rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = u}, (slop_option_rdf_Term){.has_value = 1, .value = _env->property}, _env->no_term, ({ cls__lambda_136_env_t* cls__lambda_136_env = (cls__lambda_136_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_136_env_t)); *cls__lambda_136_env = (cls__lambda_136_env_t){ .first_val = first_val, .arena = _env->arena, .same_as = _env->same_as, .g = _env->g, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_136, (void*)cls__lambda_136_env }; })); }); }

static void cls__lambda_134(cls__lambda_134_env_t* _env, rdf_Triple class_triple) { ({ __auto_type qual_class = rdf_triple_object(class_triple); ((rdf_term_eq(qual_class, _env->thing)) ? ({ rdf_indexed_graph_for_each(_env->g, _env->no_term, (slop_option_rdf_Term){.has_value = 1, .value = _env->type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = _env->restriction}, ({ cls__lambda_135_env_t* cls__lambda_135_env = (cls__lambda_135_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_135_env_t)); *cls__lambda_135_env = (cls__lambda_135_env_t){ .g = _env->g, .property = _env->property, .no_term = _env->no_term, .arena = _env->arena, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_135, (void*)cls__lambda_135_env }; })); 0; }) : ({ (void)0; })); }); }

static void cls__lambda_133(cls__lambda_133_env_t* _env, rdf_Triple prop_triple) { ({ __auto_type property = rdf_triple_object(prop_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = _env->restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_class_pred}, _env->no_term, ({ cls__lambda_134_env_t* cls__lambda_134_env = (cls__lambda_134_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_134_env_t)); *cls__lambda_134_env = (cls__lambda_134_env_t){ .thing = _env->thing, .g = _env->g, .no_term = _env->no_term, .type_pred = _env->type_pred, .restriction = _env->restriction, .property = property, .arena = _env->arena, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_134, (void*)cls__lambda_134_env }; })); }); }

static void cls__lambda_132(cls__lambda_132_env_t* _env, rdf_Triple mqc_triple) { ({ __auto_type restriction = rdf_triple_subject(mqc_triple); rdf_indexed_graph_for_each(_env->g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = _env->on_prop_pred}, _env->no_term, ({ cls__lambda_133_env_t* cls__lambda_133_env = (cls__lambda_133_env_t*)slop_arena_alloc(_env->arena, sizeof(cls__lambda_133_env_t)); *cls__lambda_133_env = (cls__lambda_133_env_t){ .g = _env->g, .restriction = restriction, .on_class_pred = _env->on_class_pred, .no_term = _env->no_term, .thing = _env->thing, .type_pred = _env->type_pred, .arena = _env->arena, .same_as = _env->same_as, .result = &((*_env->result)) }; (slop_closure_t){ (void*)cls__lambda_133, (void*)cls__lambda_133_env }; })); }); }

rdf_Term cls_fixture_build_list2(slop_arena* arena, index_IndexedGraph g, rdf_Term e1, rdf_Term e2) {
    {
        __auto_type first_pred = rdf_make_iri(arena, vocab_RDF_FIRST);
        __auto_type rest_pred = rdf_make_iri(arena, vocab_RDF_REST);
        __auto_type nil_term = rdf_make_iri(arena, vocab_RDF_NIL);
        __auto_type node1 = rdf_make_blank(arena, 1);
        __auto_type node2 = rdf_make_blank(arena, 2);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node1, first_pred, e1));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node1, rest_pred, node2));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node2, first_pred, e2));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node2, rest_pred, nil_term));
        return node1;
    }
}

rdf_Term cls_fixture_build_list3(slop_arena* arena, index_IndexedGraph g, rdf_Term e1, rdf_Term e2, rdf_Term e3) {
    {
        __auto_type first_pred = rdf_make_iri(arena, vocab_RDF_FIRST);
        __auto_type rest_pred = rdf_make_iri(arena, vocab_RDF_REST);
        __auto_type nil_term = rdf_make_iri(arena, vocab_RDF_NIL);
        __auto_type node1 = rdf_make_blank(arena, 1);
        __auto_type node2 = rdf_make_blank(arena, 2);
        __auto_type node3 = rdf_make_blank(arena, 3);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node1, first_pred, e1));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node1, rest_pred, node2));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node2, first_pred, e2));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node2, rest_pred, node3));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node3, first_pred, e3));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node3, rest_pred, nil_term));
        return node1;
    }
}

index_IndexedGraph cls_fixture_g_nothing(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type nothing = rdf_make_iri(arena, vocab_OWL_NOTHING);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, nothing));
        return g;
    }
}

types_Delta cls_fixture_delta_nothing(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type nothing = rdf_make_iri(arena, vocab_OWL_NOTHING);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, nothing));
    }
}

index_IndexedGraph cls_fixture_g_intersection(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type int_pred = rdf_make_iri(arena, vocab_OWL_INTERSECTION_OF);
        __auto_type female_parent = rdf_make_iri(arena, cls_EX_FEMALE_PARENT);
        __auto_type female = rdf_make_iri(arena, cls_EX_FEMALE);
        __auto_type parent = rdf_make_iri(arena, cls_EX_PARENT);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        {
            __auto_type list_head = cls_fixture_build_list2(arena, g, female, parent);
            rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, female_parent, int_pred, list_head));
        }
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, female));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, parent));
        return g;
    }
}

types_Delta cls_fixture_delta_intersection(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type female = rdf_make_iri(arena, cls_EX_FEMALE);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, female));
    }
}

index_IndexedGraph cls_fixture_g_intersection2(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type int_pred = rdf_make_iri(arena, vocab_OWL_INTERSECTION_OF);
        __auto_type female_parent = rdf_make_iri(arena, cls_EX_FEMALE_PARENT);
        __auto_type female = rdf_make_iri(arena, cls_EX_FEMALE);
        __auto_type parent = rdf_make_iri(arena, cls_EX_PARENT);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        {
            __auto_type list_head = cls_fixture_build_list2(arena, g, female, parent);
            rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, female_parent, int_pred, list_head));
        }
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, female_parent));
        return g;
    }
}

types_Delta cls_fixture_delta_int2(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type female_parent = rdf_make_iri(arena, cls_EX_FEMALE_PARENT);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, female_parent));
    }
}

index_IndexedGraph cls_fixture_g_union(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type union_pred = rdf_make_iri(arena, vocab_OWL_UNION_OF);
        __auto_type person = rdf_make_iri(arena, cls_EX_PERSON);
        __auto_type man = rdf_make_iri(arena, cls_EX_MAN);
        __auto_type woman = rdf_make_iri(arena, cls_EX_WOMAN);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        {
            __auto_type list_head = cls_fixture_build_list2(arena, g, man, woman);
            rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, person, union_pred, list_head));
        }
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, woman));
        return g;
    }
}

types_Delta cls_fixture_delta_union(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type woman = rdf_make_iri(arena, cls_EX_WOMAN);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, woman));
    }
}

index_IndexedGraph cls_fixture_g_complement_violation(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type comp_pred = rdf_make_iri(arena, vocab_OWL_COMPLEMENT_OF);
        __auto_type parent = rdf_make_iri(arena, cls_EX_PARENT);
        __auto_type not_parent = rdf_make_iri(arena, cls_EX_NOT_PARENT);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, not_parent, comp_pred, parent));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, parent));
        return g;
    }
}

types_Delta cls_fixture_delta_complement(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type not_parent = rdf_make_iri(arena, cls_EX_NOT_PARENT);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, not_parent));
    }
}

index_IndexedGraph cls_fixture_g_svf(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type svf_pred = rdf_make_iri(arena, vocab_OWL_SOME_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type dog_owner = rdf_make_iri(arena, cls_EX_DOG_OWNER);
        __auto_type dog = rdf_make_iri(arena, cls_EX_DOG);
        __auto_type has_pet = rdf_make_iri(arena, cls_EX_HAS_PET);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        __auto_type fido = rdf_make_iri(arena, cls_EX_FIDO);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, dog_owner, svf_pred, dog));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, dog_owner, on_prop_pred, has_pet));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_pet, fido));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, fido, type_pred, dog));
        return g;
    }
}

types_Delta cls_fixture_delta_svf(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type dog = rdf_make_iri(arena, cls_EX_DOG);
        __auto_type fido = rdf_make_iri(arena, cls_EX_FIDO);
        return types_delta_add(arena, d, rdf_make_triple(arena, fido, type_pred, dog));
    }
}

index_IndexedGraph cls_fixture_g_svf1(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type svf_pred = rdf_make_iri(arena, vocab_OWL_SOME_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        __auto_type pet_owner = rdf_make_iri(arena, cls_EX_PET_OWNER);
        __auto_type has_pet = rdf_make_iri(arena, cls_EX_HAS_PET);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        __auto_type fido = rdf_make_iri(arena, cls_EX_FIDO);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, pet_owner, svf_pred, thing));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, pet_owner, on_prop_pred, has_pet));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_pet, fido));
        return g;
    }
}

types_Delta cls_fixture_delta_svf1(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_pet = rdf_make_iri(arena, cls_EX_HAS_PET);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        __auto_type fido = rdf_make_iri(arena, cls_EX_FIDO);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, has_pet, fido));
    }
}

index_IndexedGraph cls_fixture_g_avf(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type avf_pred = rdf_make_iri(arena, vocab_OWL_ALL_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type person_hc = rdf_make_iri(arena, cls_EX_PERSON_WITH_HUMAN_CHILDREN);
        __auto_type human = rdf_make_iri(arena, cls_EX_HUMAN);
        __auto_type has_child = rdf_make_iri(arena, cls_EX_HAS_CHILD);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, cls_EX_BOB);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, person_hc, avf_pred, human));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, person_hc, on_prop_pred, has_child));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, person_hc));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_child, bob));
        return g;
    }
}

types_Delta cls_fixture_delta_avf(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type person_hc = rdf_make_iri(arena, cls_EX_PERSON_WITH_HUMAN_CHILDREN);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, person_hc));
    }
}

index_IndexedGraph cls_fixture_g_hv(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type hv_pred = rdf_make_iri(arena, vocab_OWL_HAS_VALUE);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type us_citizen = rdf_make_iri(arena, cls_EX_US_CITIZEN);
        __auto_type usa = rdf_make_iri(arena, cls_EX_USA);
        __auto_type citizenship = rdf_make_iri(arena, cls_EX_CITIZENSHIP);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        __auto_type bob = rdf_make_iri(arena, cls_EX_BOB);
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, us_citizen, hv_pred, usa));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, us_citizen, on_prop_pred, citizenship));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, us_citizen));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, bob, citizenship, usa));
        return g;
    }
}

types_Delta cls_fixture_delta_hv1(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type us_citizen = rdf_make_iri(arena, cls_EX_US_CITIZEN);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, type_pred, us_citizen));
    }
}

types_Delta cls_fixture_delta_hv2(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type citizenship = rdf_make_iri(arena, cls_EX_CITIZENSHIP);
        __auto_type usa = rdf_make_iri(arena, cls_EX_USA);
        __auto_type bob = rdf_make_iri(arena, cls_EX_BOB);
        return types_delta_add(arena, d, rdf_make_triple(arena, bob, citizenship, usa));
    }
}

index_IndexedGraph cls_fixture_g_maxc1(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type maxc_pred = rdf_make_iri(arena, vocab_OWL_MAX_CARDINALITY);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type has_one_mother = rdf_make_iri(arena, cls_EX_HAS_ONE_MOTHER);
        __auto_type has_mother = rdf_make_iri(arena, cls_EX_HAS_MOTHER);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        __auto_type mary = rdf_make_iri(arena, cls_EX_MARY);
        __auto_type maria = rdf_make_iri(arena, cls_EX_MARIA);
        __auto_type one = rdf_make_iri(arena, SLOP_STR("http://example.org/1"));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_one_mother, maxc_pred, one));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, has_one_mother, on_prop_pred, has_mother));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, type_pred, has_one_mother));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_mother, mary));
        rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, alice, has_mother, maria));
        return g;
    }
}

types_Delta cls_fixture_delta_maxc(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type has_mother = rdf_make_iri(arena, cls_EX_HAS_MOTHER);
        __auto_type alice = rdf_make_iri(arena, cls_EX_ALICE);
        __auto_type maria = rdf_make_iri(arena, cls_EX_MARIA);
        return types_delta_add(arena, d, rdf_make_triple(arena, alice, has_mother, maria));
    }
}

index_IndexedGraph cls_fixture_g_one_of(slop_arena* arena) {
    {
        __auto_type g = rdf_indexed_graph_create(arena);
        __auto_type one_of_pred = rdf_make_iri(arena, vocab_OWL_ONE_OF);
        __auto_type first_pred = rdf_make_iri(arena, vocab_RDF_FIRST);
        __auto_type rest_pred = rdf_make_iri(arena, vocab_RDF_REST);
        __auto_type nil_term = rdf_make_iri(arena, vocab_RDF_NIL);
        __auto_type days = rdf_make_iri(arena, cls_EX_DAYS_OF_WEEK);
        __auto_type monday = rdf_make_iri(arena, cls_EX_MONDAY);
        __auto_type tuesday = rdf_make_iri(arena, cls_EX_TUESDAY);
        __auto_type wednesday = rdf_make_iri(arena, cls_EX_WEDNESDAY);
        __auto_type node1 = rdf_make_blank(arena, 1);
        __auto_type node2 = rdf_make_blank(arena, 2);
        __auto_type node3 = rdf_make_blank(arena, 3);
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node1, first_pred, monday));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node1, rest_pred, node2));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node2, first_pred, tuesday));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node2, rest_pred, node3));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node3, first_pred, wednesday));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, node3, rest_pred, nil_term));
        g = rdf_indexed_graph_add(arena, g, rdf_make_triple(arena, days, one_of_pred, node1));
        return g;
    }
}

types_Delta cls_fixture_delta_one_of(slop_arena* arena) {
    {
        __auto_type d = types_make_delta(arena, 0);
        __auto_type one_of_pred = rdf_make_iri(arena, vocab_OWL_ONE_OF);
        __auto_type days = rdf_make_iri(arena, cls_EX_DAYS_OF_WEEK);
        __auto_type node1 = rdf_make_blank(arena, 1);
        d = types_delta_add(arena, d, rdf_make_triple(arena, days, one_of_pred, node1));
        return d;
    }
}

slop_result_types_Delta_types_InconsistencyReport cls_apply_cls_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type result = types_make_delta(arena, next_iter);
        __auto_type _mv_102 = cls_cls_nothing2(arena, g, delta);
        if (_mv_102.has_value) {
            __auto_type report = _mv_102.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_102.has_value) {
        }
        {
            __auto_type _coll = cls_cls_int1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cls_cls_int2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cls_cls_uni(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        __auto_type _mv_103 = cls_cls_com(arena, g, delta);
        if (_mv_103.has_value) {
            __auto_type report = _mv_103.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
        } else if (!_mv_103.has_value) {
        }
        {
            __auto_type _coll = cls_cls_svf1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cls_cls_svf2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cls_cls_avf(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cls_cls_hv1(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        {
            __auto_type _coll = cls_cls_hv2(arena, g, delta);
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = types_delta_add(arena, result, t);
            }
        }
        if (!(fast)) {
            {
                __auto_type _coll = cls_cls_maxc1(arena, g, delta);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    result = types_delta_add(arena, result, t);
                }
            }
            {
                __auto_type _coll = cls_cls_maxc2(arena, g, delta);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    result = types_delta_add(arena, result, t);
                }
            }
            __auto_type _mv_104 = cls_cls_maxqc1(arena, g, delta);
            if (_mv_104.has_value) {
                __auto_type report = _mv_104.value;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            } else if (!_mv_104.has_value) {
            }
            __auto_type _mv_105 = cls_cls_maxqc2(arena, g, delta);
            if (_mv_105.has_value) {
                __auto_type report = _mv_105.value;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            } else if (!_mv_105.has_value) {
            }
            {
                __auto_type _coll = cls_cls_maxqc3(arena, g, delta);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    result = types_delta_add(arena, result, t);
                }
            }
            {
                __auto_type _coll = cls_cls_maxqc4(arena, g, delta);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    result = types_delta_add(arena, result, t);
                }
            }
        }
        {
            __auto_type _coll = cls_cls_oo(arena, g, delta);
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

slop_list_rdf_Triple cls_cls_thing(slop_arena* arena, index_IndexedGraph g) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        __auto_type owl_class = rdf_make_iri(arena, vocab_OWL_CLASS);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type candidates = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        ({ __auto_type _lst_p = &(candidates); __auto_type _item = (rdf_make_triple(arena, thing, type_pred, owl_class)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type _coll = candidates;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type inferred = _coll.data[_i];
                if (!(rdf_indexed_graph_contains(g, inferred))) {
                    ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST(((((int64_t)((_retval).len)) <= 1)), "(<= (list-len $result) 1)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_nothing1(slop_arena* arena, index_IndexedGraph g) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type nothing = rdf_make_iri(arena, vocab_OWL_NOTHING);
        __auto_type owl_class = rdf_make_iri(arena, vocab_OWL_CLASS);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type candidates = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        ({ __auto_type _lst_p = &(candidates); __auto_type _item = (rdf_make_triple(arena, nothing, type_pred, owl_class)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type _coll = candidates;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type inferred = _coll.data[_i];
                if (!(rdf_indexed_graph_contains(g, inferred))) {
                    ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST(((((int64_t)((_retval).len)) <= 1)), "(<= (list-len $result) 1)");
    return _retval;
}

slop_option_types_InconsistencyReport cls_cls_nothing2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type nothing = rdf_make_iri(arena, vocab_OWL_NOTHING);
        __auto_type _mv_106 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_106.has_value) {
            __auto_type type_triples = _mv_106.value;
            {
                slop_map* _coll = (slop_map*)type_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        if (rdf_term_eq(rdf_triple_object(dt), nothing)) {
                            return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cls-nothing2: individual is instance of owl:Nothing"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 1 * sizeof(rdf_Triple)), .len = 1, .cap = 1 }; _ll.data[0] = dt; _ll; })})};
                        }
                    }
                }
            }
        } else if (!_mv_106.has_value) {
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (string_len(r.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some r) (> (string-len (. r reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 1); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 1)))");
    return _retval;
}

slop_list_rdf_Triple cls_cls_int1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type intersection_pred = rdf_make_iri(arena, vocab_OWL_INTERSECTION_OF);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = intersection_pred}, no_term, ({ cls__lambda_107_env_t* cls__lambda_107_env = (cls__lambda_107_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_107_env_t)); *cls__lambda_107_env = (cls__lambda_107_env_t){ .arena = arena, .g = g, .delta = delta, .type_pred = type_pred, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_107, (void*)cls__lambda_107_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_int2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type intersection_pred = rdf_make_iri(arena, vocab_OWL_INTERSECTION_OF);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = intersection_pred}, no_term, ({ cls__lambda_108_env_t* cls__lambda_108_env = (cls__lambda_108_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_108_env_t)); *cls__lambda_108_env = (cls__lambda_108_env_t){ .arena = arena, .g = g, .delta = delta, .type_pred = type_pred, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_108, (void*)cls__lambda_108_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_uni(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type union_pred = rdf_make_iri(arena, vocab_OWL_UNION_OF);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = union_pred}, no_term, ({ cls__lambda_109_env_t* cls__lambda_109_env = (cls__lambda_109_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_109_env_t)); *cls__lambda_109_env = (cls__lambda_109_env_t){ .arena = arena, .g = g, .delta = delta, .type_pred = type_pred, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_109, (void*)cls__lambda_109_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_option_types_InconsistencyReport cls_cls_com(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type complement_pred = rdf_make_iri(arena, vocab_OWL_COMPLEMENT_OF);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type comp_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = complement_pred}, no_term);
            {
                __auto_type _coll = comp_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type comp_triple = _coll.data[_i];
                    {
                        __auto_type c1 = rdf_triple_subject(comp_triple);
                        __auto_type c2 = rdf_triple_object(comp_triple);
                        __auto_type _mv_110 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(type_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                        if (_mv_110.has_value) {
                            __auto_type type_triples = _mv_110.value;
                            {
                                slop_map* _coll = (slop_map*)type_triples;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                                        {
                                            __auto_type individual = rdf_triple_subject(dt);
                                            __auto_type asserted_class = rdf_triple_object(dt);
                                            if (rdf_term_eq(asserted_class, c1)) {
                                                {
                                                    __auto_type c2_type = rdf_make_triple(arena, individual, type_pred, c2);
                                                    if (rdf_indexed_graph_contains(g, c2_type)) {
                                                        return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cls-com: individual in both class and its complement"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = c2_type; _ll.data[2] = comp_triple; _ll; })})};
                                                    }
                                                }
                                            }
                                            if (rdf_term_eq(asserted_class, c2)) {
                                                {
                                                    __auto_type c1_type = rdf_make_triple(arena, individual, type_pred, c1);
                                                    if (rdf_indexed_graph_contains(g, c1_type)) {
                                                        return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cls-com: individual in both class and its complement"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = dt; _ll.data[1] = c1_type; _ll.data[2] = comp_triple; _ll; })})};
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } else if (!_mv_110.has_value) {
                        }
                    }
                }
            }
        }
        return (slop_option_types_InconsistencyReport){.has_value = false};
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (string_len(r.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some r) (> (string-len (. r reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 3); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 3)))");
    return _retval;
}

slop_list_rdf_Triple cls_cls_svf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type svf_pred = rdf_make_iri(arena, vocab_OWL_SOME_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = svf_pred}, (slop_option_rdf_Term){.has_value = 1, .value = thing}, ({ cls__lambda_111_env_t* cls__lambda_111_env = (cls__lambda_111_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_111_env_t)); *cls__lambda_111_env = (cls__lambda_111_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .delta = delta, .arena = arena, .type_pred = type_pred, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_111, (void*)cls__lambda_111_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_svf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type svf_pred = rdf_make_iri(arena, vocab_OWL_SOME_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = svf_pred}, no_term, ({ cls__lambda_113_env_t* cls__lambda_113_env = (cls__lambda_113_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_113_env_t)); *cls__lambda_113_env = (cls__lambda_113_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .delta = delta, .type_pred = type_pred, .arena = arena, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_113, (void*)cls__lambda_113_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_avf(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type avf_pred = rdf_make_iri(arena, vocab_OWL_ALL_VALUES_FROM);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = avf_pred}, no_term, ({ cls__lambda_116_env_t* cls__lambda_116_env = (cls__lambda_116_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_116_env_t)); *cls__lambda_116_env = (cls__lambda_116_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .delta = delta, .type_pred = type_pred, .arena = arena, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_116, (void*)cls__lambda_116_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_hv1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type hv_pred = rdf_make_iri(arena, vocab_OWL_HAS_VALUE);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = hv_pred}, no_term, ({ cls__lambda_119_env_t* cls__lambda_119_env = (cls__lambda_119_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_119_env_t)); *cls__lambda_119_env = (cls__lambda_119_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .delta = delta, .type_pred = type_pred, .arena = arena, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_119, (void*)cls__lambda_119_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_hv2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type hv_pred = rdf_make_iri(arena, vocab_OWL_HAS_VALUE);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = hv_pred}, no_term, ({ cls__lambda_121_env_t* cls__lambda_121_env = (cls__lambda_121_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_121_env_t)); *cls__lambda_121_env = (cls__lambda_121_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .delta = delta, .arena = arena, .type_pred = type_pred, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_121, (void*)cls__lambda_121_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_maxc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    _retval = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_maxc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type maxc_pred = rdf_make_iri(arena, vocab_OWL_MAX_CARDINALITY);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = maxc_pred}, no_term, ({ cls__lambda_123_env_t* cls__lambda_123_env = (cls__lambda_123_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_123_env_t)); *cls__lambda_123_env = (cls__lambda_123_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .type_pred = type_pred, .arena = arena, .same_as = same_as, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_123, (void*)cls__lambda_123_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

slop_option_types_InconsistencyReport cls_cls_maxqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type mqc_pred = rdf_make_iri(arena, vocab_OWL_MAX_QUALIFIED_CARDINALITY);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type on_class_pred = rdf_make_iri(arena, vocab_OWL_ON_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type mqc_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = mqc_pred}, no_term);
            {
                __auto_type _coll = mqc_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type mqc_triple = _coll.data[_i];
                    {
                        __auto_type restriction = rdf_triple_subject(mqc_triple);
                        __auto_type prop_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = on_prop_pred}, no_term);
                        {
                            __auto_type _coll = prop_triples;
                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                __auto_type prop_triple = _coll.data[_i];
                                {
                                    __auto_type property = rdf_triple_object(prop_triple);
                                    __auto_type class_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = on_class_pred}, no_term);
                                    {
                                        __auto_type _coll = class_triples;
                                        for (size_t _i = 0; _i < _coll.len; _i++) {
                                            __auto_type class_triple = _coll.data[_i];
                                            {
                                                __auto_type qual_class = rdf_triple_object(class_triple);
                                                if (!(rdf_term_eq(qual_class, thing))) {
                                                    {
                                                        __auto_type inst_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = restriction});
                                                        {
                                                            __auto_type _coll = inst_triples;
                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                __auto_type inst_triple = _coll.data[_i];
                                                                {
                                                                    __auto_type u = rdf_triple_subject(inst_triple);
                                                                    __auto_type val_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = u}, (slop_option_rdf_Term){.has_value = 1, .value = property}, no_term);
                                                                    {
                                                                        __auto_type _coll = val_triples;
                                                                        for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                            __auto_type val_triple = _coll.data[_i];
                                                                            {
                                                                                __auto_type y = rdf_triple_object(val_triple);
                                                                                __auto_type y_type = rdf_make_triple(arena, y, type_pred, qual_class);
                                                                                if (rdf_indexed_graph_contains(g, y_type)) {
                                                                                    return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cls-maxqc1: maxQualifiedCardinality 0 violated"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 4 * sizeof(rdf_Triple)), .len = 4, .cap = 4 }; _ll.data[0] = inst_triple; _ll.data[1] = val_triple; _ll.data[2] = y_type; _ll.data[3] = mqc_triple; _ll; })})};
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
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (string_len(r.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some r) (> (string-len (. r reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 2); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 2)))");
    return _retval;
}

slop_option_types_InconsistencyReport cls_cls_maxqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_option_types_InconsistencyReport _retval;
    {
        __auto_type mqc_pred = rdf_make_iri(arena, vocab_OWL_MAX_QUALIFIED_CARDINALITY);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type on_class_pred = rdf_make_iri(arena, vocab_OWL_ON_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            __auto_type mqc_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = mqc_pred}, no_term);
            {
                __auto_type _coll = mqc_triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type mqc_triple = _coll.data[_i];
                    {
                        __auto_type restriction = rdf_triple_subject(mqc_triple);
                        __auto_type prop_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = on_prop_pred}, no_term);
                        {
                            __auto_type _coll = prop_triples;
                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                __auto_type prop_triple = _coll.data[_i];
                                {
                                    __auto_type property = rdf_triple_object(prop_triple);
                                    __auto_type class_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = restriction}, (slop_option_rdf_Term){.has_value = 1, .value = on_class_pred}, no_term);
                                    {
                                        __auto_type _coll = class_triples;
                                        for (size_t _i = 0; _i < _coll.len; _i++) {
                                            __auto_type class_triple = _coll.data[_i];
                                            {
                                                __auto_type qual_class = rdf_triple_object(class_triple);
                                                if (rdf_term_eq(qual_class, thing)) {
                                                    {
                                                        __auto_type inst_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = restriction});
                                                        {
                                                            __auto_type _coll = inst_triples;
                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                __auto_type inst_triple = _coll.data[_i];
                                                                {
                                                                    __auto_type u = rdf_triple_subject(inst_triple);
                                                                    __auto_type val_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = u}, (slop_option_rdf_Term){.has_value = 1, .value = property}, no_term);
                                                                    {
                                                                        __auto_type _coll = val_triples;
                                                                        for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                            __auto_type val_triple = _coll.data[_i];
                                                                            return (slop_option_types_InconsistencyReport){.has_value = 1, .value = ((types_InconsistencyReport){.reason = SLOP_STR("cls-maxqc2: maxQualifiedCardinality 0 (owl:Thing) violated"), .witnesses = ({ slop_list_rdf_Triple _ll = (slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 3 * sizeof(rdf_Triple)), .len = 3, .cap = 3 }; _ll.data[0] = inst_triple; _ll.data[1] = val_triple; _ll.data[2] = mqc_triple; _ll; })})};
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
    }
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (string_len(r.reason) > 0); }) : (1); })), "(match $result ((none) true) ((some r) (> (string-len (. r reason)) 0)))");
    SLOP_POST((({ __auto_type _mv = _retval; _mv.has_value ? ({ __auto_type r = _mv.value; (((int64_t)((r.witnesses).len)) >= 2); }) : (1); })), "(match $result ((none) true) ((some r) (>= (list-len (. r witnesses)) 2)))");
    return _retval;
}

slop_list_rdf_Triple cls_cls_maxqc3(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type mqc_pred = rdf_make_iri(arena, vocab_OWL_MAX_QUALIFIED_CARDINALITY);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type on_class_pred = rdf_make_iri(arena, vocab_OWL_ON_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = mqc_pred}, no_term, ({ cls__lambda_127_env_t* cls__lambda_127_env = (cls__lambda_127_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_127_env_t)); *cls__lambda_127_env = (cls__lambda_127_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .on_class_pred = on_class_pred, .thing = thing, .type_pred = type_pred, .arena = arena, .same_as = same_as, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_127, (void*)cls__lambda_127_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_maxqc4(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type mqc_pred = rdf_make_iri(arena, vocab_OWL_MAX_QUALIFIED_CARDINALITY);
        __auto_type on_prop_pred = rdf_make_iri(arena, vocab_OWL_ON_PROPERTY);
        __auto_type on_class_pred = rdf_make_iri(arena, vocab_OWL_ON_CLASS);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        rdf_indexed_graph_for_each(g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = mqc_pred}, no_term, ({ cls__lambda_132_env_t* cls__lambda_132_env = (cls__lambda_132_env_t*)slop_arena_alloc(arena, sizeof(cls__lambda_132_env_t)); *cls__lambda_132_env = (cls__lambda_132_env_t){ .g = g, .on_prop_pred = on_prop_pred, .no_term = no_term, .on_class_pred = on_class_pred, .thing = thing, .type_pred = type_pred, .arena = arena, .same_as = same_as, .result = &(result) }; (slop_closure_t){ (void*)cls__lambda_132, (void*)cls__lambda_132_env }; }));
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_OWL_SAME_AS)), "(all-triples-have-predicate $result OWL_SAME_AS)");
    return _retval;
}

slop_list_rdf_Triple cls_cls_oo(slop_arena* arena, index_IndexedGraph g, types_Delta delta) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval;
    {
        __auto_type one_of_pred = rdf_make_iri(arena, vocab_OWL_ONE_OF);
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_137 = ({ void* _ptr = slop_map_get(delta.by_predicate, &(one_of_pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_137.has_value) {
            __auto_type pred_triples = _mv_137.value;
            {
                slop_map* _coll = (slop_map*)pred_triples;
                for (size_t _i = 0; _i < _coll->cap; _i++) {
                    if (_coll->entries[_i].occupied) {
                        rdf_Triple dt = *(rdf_Triple*)_coll->entries[_i].key;
                        {
                            __auto_type enum_class = rdf_triple_subject(dt);
                            __auto_type list_head = rdf_triple_object(dt);
                            __auto_type members = rdf_list_elements_indexed(arena, g, list_head);
                            {
                                __auto_type _coll = members;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type member = _coll.data[_i];
                                    {
                                        __auto_type inferred = rdf_make_triple(arena, member, type_pred, enum_class);
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
        } else if (!_mv_137.has_value) {
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    SLOP_POST((types_all_triples_have_predicate(_retval, vocab_RDF_TYPE)), "(all-triples-have-predicate $result RDF_TYPE)");
    return _retval;
}

