#ifndef SLOP_growl_H
#define SLOP_growl_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_vocab.h"
#include "slop_types.h"
#include "slop_engine.h"
#include "slop_filter.h"

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

types_ReasonerConfig growl_default_config(void);
types_ReasonerResult growl_reason(slop_arena* arena, index_IndexedGraph input);
types_ReasonerResult growl_reason_with_config(slop_arena* arena, index_IndexedGraph input, types_ReasonerConfig config);
uint8_t growl_is_consistent(slop_arena* arena, index_IndexedGraph input);
slop_list_rdf_Term growl_get_types(slop_arena* arena, index_IndexedGraph g, rdf_Term individual);
slop_list_rdf_Term growl_get_same_as(slop_arena* arena, index_IndexedGraph g, rdf_Term individual);
int64_t growl_get_inferred_count(types_ReasonerResult result);

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif


#endif
