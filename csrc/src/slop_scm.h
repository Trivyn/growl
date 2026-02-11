#ifndef SLOP_scm_H
#define SLOP_scm_H

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

#ifndef SLOP_RESULT_TYPES_DELTA_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_TYPES_DELTA_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { types_Delta ok; types_InconsistencyReport err; } data; } slop_result_types_Delta_types_InconsistencyReport;
#endif

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
slop_list_rdf_Triple scm_scm_eqc_mutual(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_op(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dp(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_spo(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_eqp_mutual(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dom1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_dom2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_rng1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_rng2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_int(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_uni(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_svf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_svf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_avf1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_avf2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple scm_scm_hv(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif


#endif
