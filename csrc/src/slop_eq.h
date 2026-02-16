#ifndef SLOP_eq_H
#define SLOP_eq_H

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

index_IndexedGraph eq_fixture_g_same_as(slop_arena* arena);
index_IndexedGraph eq_fixture_g_trans(slop_arena* arena);
index_IndexedGraph eq_fixture_g_rep_s(slop_arena* arena);
index_IndexedGraph eq_fixture_g_rep_p(slop_arena* arena);
index_IndexedGraph eq_fixture_g_rep_o(slop_arena* arena);
index_IndexedGraph eq_fixture_g_contradiction(slop_arena* arena);
index_IndexedGraph eq_fixture_g_no_contradiction(slop_arena* arena);
index_IndexedGraph eq_fixture_g_sym_contradiction(slop_arena* arena);
types_Delta eq_fixture_delta_same_as(slop_arena* arena);
types_Delta eq_fixture_delta_trans(slop_arena* arena);
types_Delta eq_fixture_delta_empty(slop_arena* arena);
types_Delta eq_fixture_delta_rep_p(slop_arena* arena);
types_Delta eq_fixture_delta_rep_o(slop_arena* arena);
types_Delta eq_fixture_delta_contradiction(slop_arena* arena);
slop_result_types_Delta_types_InconsistencyReport eq_apply_eq_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, uint8_t fast, uint8_t validate);
slop_list_rdf_Triple eq_eq_sym(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_trans(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_rep_s(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_rep_p(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_rep_o(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport eq_eq_diff1(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport eq_eq_diff2(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_option_types_InconsistencyReport eq_eq_diff3(slop_arena* arena, index_IndexedGraph g, types_Delta delta);
slop_list_rdf_Triple eq_eq_ref(slop_arena* arena, index_IndexedGraph g, types_Delta delta);

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(types_InconsistencyReport, slop_option_types_InconsistencyReport)
#endif


#endif
