#ifndef SLOP_scm_H
#define SLOP_scm_H

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

#ifndef SLOP_RESULT_GROWL_TYPES_DELTA_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_GROWL_TYPES_DELTA_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { growl_types_Delta ok; growl_types_InconsistencyReport err; } data; } slop_result_growl_types_Delta_growl_types_InconsistencyReport;
#endif

slop_rdf_index_IndexedGraph growl_scm_fixture_g_with_class(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_scm_fixture_g_chain(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_scm_fixture_g_equiv(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_scm_fixture_g_prop_chain(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_scm_fixture_g_domain(slop_arena* arena);
growl_types_Delta growl_scm_fixture_delta_new_link(slop_arena* arena);
growl_types_Delta growl_scm_fixture_delta_empty(slop_arena* arena);
growl_types_Delta growl_scm_fixture_delta_with_class(slop_arena* arena);
growl_types_Delta growl_scm_fixture_delta_equiv(slop_arena* arena);
growl_types_Delta growl_scm_fixture_delta_subprop(slop_arena* arena);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_scm_apply_scm_rules(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_cls(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_sco(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_eqc1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_eqc1b(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_eqc2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_op(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_dp(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_spo(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_eqp1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_eqp1b(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_eqp2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_dom2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_dom1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_rng2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_rng1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_int(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_uni(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_svf1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_svf2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_avf1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_avf2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_scm_scm_hv(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
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
