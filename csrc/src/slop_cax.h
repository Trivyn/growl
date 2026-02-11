#ifndef SLOP_cax_H
#define SLOP_cax_H

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

index_IndexedGraph cax_fixture_g_with_subclass(slop_arena* arena);
index_IndexedGraph cax_fixture_g_with_equiv(slop_arena* arena);
index_IndexedGraph cax_fixture_g_disjoint_violation(slop_arena* arena);
index_IndexedGraph cax_fixture_g_consistent(slop_arena* arena);
types_Delta cax_fixture_delta_with_type(slop_arena* arena);
types_Delta cax_fixture_delta_with_human(slop_arena* arena);
types_Delta cax_fixture_delta_with_person(slop_arena* arena);
types_Delta cax_fixture_delta_empty(slop_arena* arena);
types_Delta cax_fixture_delta_fido_cat(slop_arena* arena);
types_Delta cax_fixture_delta_fido_dog(slop_arena* arena);
index_IndexedGraph cax_fixture_g_all_disjoint(slop_arena* arena);
slop_result_types_Delta_types_InconsistencyReport cax_apply_cax_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast);
slop_list_rdf_Triple cax_cax_sco(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cax_cax_eqc1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple cax_cax_eqc2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport cax_cax_dw(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport cax_cax_adc(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(types_InconsistencyReport, slop_option_types_InconsistencyReport)
#endif


#endif
