#ifndef SLOP_cls_H
#define SLOP_cls_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_vocab.h"
#include "slop_list.h"
#include "slop_types.h"

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(types_InconsistencyReport, slop_option_types_InconsistencyReport)
#endif

#ifndef SLOP_RESULT_TYPES_DELTA_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_TYPES_DELTA_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { types_Delta ok; types_InconsistencyReport err; } data; } slop_result_types_Delta_types_InconsistencyReport;
#endif

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

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(types_InconsistencyReport, slop_option_types_InconsistencyReport)
#endif


#endif
