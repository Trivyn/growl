#ifndef SLOP_dt_H
#define SLOP_dt_H

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
#include "slop_xsd.h"
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

slop_list_slop_rdf_rdf_Triple growl_dt_dt_type1(slop_arena* arena, slop_rdf_index_IndexedGraph g);
uint8_t growl_dt_is_supported_datatype(slop_string dt_iri);
slop_list_slop_rdf_rdf_Triple growl_dt_dt_type2(slop_arena* arena, slop_rdf_index_IndexedGraph g);
slop_option_growl_types_InconsistencyReport growl_dt_dt_not_type(slop_arena* arena, slop_rdf_index_IndexedGraph g);

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(growl_types_InconsistencyReport, slop_option_growl_types_InconsistencyReport)
#endif


#endif
