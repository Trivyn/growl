#ifndef SLOP_prp_H
#define SLOP_prp_H

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

slop_rdf_index_IndexedGraph growl_prp_fixture_g_domain(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_range(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_functional(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_ifp(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_symmetric(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_asym_violation(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_transitive(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_irp_violation(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_subprop(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_inverse(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_prp_fixture_g_pdw_violation(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_usage(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_empty(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_functional(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_ifp(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_symmetric(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_asymmetric(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_transitive(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_irreflexive(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_subprop(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_inverse1(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_inverse2(slop_arena* arena);
growl_types_Delta growl_prp_fixture_delta_pdw(slop_arena* arena);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_prp_apply_prp_rules(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, uint8_t fast, uint8_t validate, uint8_t enrich);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_dom(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_rng(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_fp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_ifp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_symp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_prp_prp_asyp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_trp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_prp_prp_irp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_prp_prp_adp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_prp_prp_npa1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_prp_prp_npa2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_spo2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_key(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_spo1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_inv1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_inv2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_eqp1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_eqp2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_prp_prp_pdw(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_prp_prp_ap(slop_arena* arena, slop_rdf_index_IndexedGraph g);

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(growl_types_InconsistencyReport, slop_option_growl_types_InconsistencyReport)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_MAP_PTR_DEFINED
#define SLOP_OPTION_MAP_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_map*, slop_option_map_ptr)
#endif

#ifndef SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Term, slop_list_slop_rdf_rdf_Term)
#endif


#endif
