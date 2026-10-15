#ifndef SLOP_list_H
#define SLOP_list_H

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

#ifndef SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Term, slop_list_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

slop_list_slop_rdf_rdf_Term rdf_list_elements(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Term head);
slop_list_slop_rdf_rdf_Term rdf_list_elements_indexed(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term head);
uint8_t rdf_list_contains(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Term head, slop_rdf_rdf_Term element);
int64_t rdf_list_length(slop_arena* arena, slop_rdf_rdf_Graph g, slop_rdf_rdf_Term head);

/* Function name aliases for C interop */
#define slop_rdf_list_rdf_list_elements rdf_list_elements
#define slop_rdf_list_rdf_list_elements_indexed rdf_list_elements_indexed
#define slop_rdf_list_rdf_list_contains rdf_list_contains
#define slop_rdf_list_rdf_list_length rdf_list_length

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif


#endif
