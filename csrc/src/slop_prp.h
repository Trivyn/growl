#ifndef SLOP_prp_H
#define SLOP_prp_H

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

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(types_InconsistencyReport, slop_option_types_InconsistencyReport)
#endif


#endif
