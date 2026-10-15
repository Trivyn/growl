#ifndef SLOP_eq_H
#define SLOP_eq_H

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

slop_rdf_index_IndexedGraph growl_eq_fixture_g_same_as(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_eq_fixture_g_trans(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_eq_fixture_g_rep_s(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_eq_fixture_g_rep_p(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_eq_fixture_g_rep_o(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_eq_fixture_g_contradiction(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_eq_fixture_g_no_contradiction(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_eq_fixture_g_sym_contradiction(slop_arena* arena);
growl_types_Delta growl_eq_fixture_delta_same_as(slop_arena* arena);
growl_types_Delta growl_eq_fixture_delta_trans(slop_arena* arena);
growl_types_Delta growl_eq_fixture_delta_empty(slop_arena* arena);
growl_types_Delta growl_eq_fixture_delta_rep_p(slop_arena* arena);
growl_types_Delta growl_eq_fixture_delta_rep_o(slop_arena* arena);
growl_types_Delta growl_eq_fixture_delta_contradiction(slop_arena* arena);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_eq_apply_eq_rules(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, uint8_t fast, uint8_t validate);
slop_list_slop_rdf_rdf_Triple growl_eq_eq_sym(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_eq_eq_trans(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_eq_eq_rep_s(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_eq_eq_rep_p(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_eq_eq_rep_o(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_eq_eq_diff1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_eq_eq_diff2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_eq_eq_diff3(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_eq_eq_ref(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);

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
