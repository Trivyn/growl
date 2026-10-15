#ifndef SLOP_cls_H
#define SLOP_cls_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_vocab.h"
#include "slop_list.h"
#include "slop_types.h"

#ifndef SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Triple, slop_list_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(growl_types_InconsistencyReport, slop_option_growl_types_InconsistencyReport)
#endif

#ifndef SLOP_RESULT_GROWL_TYPES_DELTA_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_GROWL_TYPES_DELTA_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { growl_types_Delta ok; growl_types_InconsistencyReport err; } data; } slop_result_growl_types_Delta_growl_types_InconsistencyReport;
#endif

slop_rdf_rdf_Term growl_cls_fixture_build_list2(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term e1, slop_rdf_rdf_Term e2);
slop_rdf_rdf_Term growl_cls_fixture_build_list3(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term e1, slop_rdf_rdf_Term e2, slop_rdf_rdf_Term e3);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_nothing(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_nothing(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_intersection(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_intersection(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_intersection2(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_int2(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_union(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_union(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_complement_violation(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_complement(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_svf(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_svf(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_svf1(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_svf1(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_avf(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_avf(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_hv(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_hv1(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_hv2(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_maxc1(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_maxc(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cls_fixture_g_one_of(slop_arena* arena);
growl_types_Delta growl_cls_fixture_delta_one_of(slop_arena* arena);
uint8_t growl_cls_term_is_int_value(slop_rdf_rdf_Term t, slop_string expected);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_cls_apply_cls_rules(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, uint8_t fast, uint8_t validate);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_thing(slop_arena* arena, slop_rdf_index_IndexedGraph g);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_nothing1(slop_arena* arena, slop_rdf_index_IndexedGraph g);
slop_option_growl_types_InconsistencyReport growl_cls_cls_nothing2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_int1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_int2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_uni(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_cls_cls_com(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_svf2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_svf1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_avf(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_hv1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_hv2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_cls_cls_maxc1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_maxc2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_cls_cls_maxqc1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_cls_cls_maxqc2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_maxqc3(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_maxqc4(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cls_cls_oo(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(growl_types_InconsistencyReport, slop_option_growl_types_InconsistencyReport)
#endif

#ifndef SLOP_OPTION_MAP_PTR_DEFINED
#define SLOP_OPTION_MAP_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_map*, slop_option_map_ptr)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif


#endif
