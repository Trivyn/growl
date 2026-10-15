#ifndef SLOP_growl_H
#define SLOP_growl_H

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
#include "slop_types.h"
#include "slop_engine.h"
#include "slop_filter.h"

#ifndef SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Term, slop_list_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

slop_rdf_rdf_Term growl_remap_blank_term(slop_arena* arena, slop_rdf_rdf_Term t, int64_t offset);
int64_t growl_max_blank_id_in_term(slop_rdf_rdf_Term t);
int64_t growl_max_blank_id_in_graph(slop_rdf_index_IndexedGraph ig);
growl_types_ReasonerConfig growl_default_config(void);
growl_types_ReasonerResult growl_reason(slop_arena* arena, slop_rdf_index_IndexedGraph input);
growl_types_ReasonerResult growl_reason_with_config(slop_arena* arena, slop_rdf_index_IndexedGraph input, growl_types_ReasonerConfig config);
uint8_t growl_is_consistent(slop_arena* arena, slop_rdf_index_IndexedGraph input);
slop_list_slop_rdf_rdf_Term growl_get_types(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term individual);
slop_list_slop_rdf_rdf_Term growl_get_same_as(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term individual);
int64_t growl_get_inferred_count(growl_types_ReasonerResult result);

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif


#endif
