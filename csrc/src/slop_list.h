#ifndef SLOP_list_H
#define SLOP_list_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_vocab.h"

#ifndef SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_DEFINED
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

#ifndef SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_DEFINED
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif

slop_list_rdf_Term rdf_list_elements(slop_arena* arena, rdf_Graph g, rdf_Term head);
slop_list_rdf_Term rdf_list_elements_indexed(slop_arena* arena, index_IndexedGraph g, rdf_Term head);
uint8_t rdf_list_contains(slop_arena* arena, rdf_Graph g, rdf_Term head, rdf_Term element);
int64_t rdf_list_length(slop_arena* arena, rdf_Graph g, rdf_Term head);

/* Function name aliases for C interop */
#define list_rdf_list_elements rdf_list_elements
#define list_rdf_list_elements_indexed rdf_list_elements_indexed
#define list_rdf_list_contains rdf_list_contains
#define list_rdf_list_length rdf_list_length

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif


#endif
