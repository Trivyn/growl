#ifndef SLOP_cax_H
#define SLOP_cax_H

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

slop_rdf_index_IndexedGraph growl_cax_fixture_g_with_subclass(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cax_fixture_g_with_equiv(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cax_fixture_g_disjoint_violation(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cax_fixture_g_consistent(slop_arena* arena);
growl_types_Delta growl_cax_fixture_delta_with_type(slop_arena* arena);
growl_types_Delta growl_cax_fixture_delta_with_human(slop_arena* arena);
growl_types_Delta growl_cax_fixture_delta_with_person(slop_arena* arena);
growl_types_Delta growl_cax_fixture_delta_empty(slop_arena* arena);
growl_types_Delta growl_cax_fixture_delta_fido_cat(slop_arena* arena);
growl_types_Delta growl_cax_fixture_delta_fido_dog(slop_arena* arena);
slop_rdf_index_IndexedGraph growl_cax_fixture_g_all_disjoint(slop_arena* arena);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_cax_apply_cax_rules(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, uint8_t fast, uint8_t validate);
slop_list_slop_rdf_rdf_Triple growl_cax_cax_sco(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cax_cax_eqc1(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_list_slop_rdf_rdf_Triple growl_cax_cax_eqc2(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_cax_cax_dw(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);
slop_option_growl_types_InconsistencyReport growl_cax_cax_adc(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta);

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
