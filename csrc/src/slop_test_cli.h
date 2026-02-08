#ifndef SLOP_test_cli_H
#define SLOP_test_cli_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_ttl.h"
#include "slop_serialize_ttl.h"
#include "slop_vocab.h"
#include "slop_growl.h"

#ifndef SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
#define SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerResult, slop_option_types_ReasonerResult)
#endif

index_IndexedGraph test_cli_graph_to_indexed(slop_arena* arena, rdf_Graph g);
rdf_Graph test_cli_indexed_to_graph(slop_arena* arena, index_IndexedGraph ig);
uint8_t test_cli_has_type(slop_arena* arena, index_IndexedGraph g, rdf_Term individual, rdf_Term class);
uint8_t test_cli_has_same_as(slop_arena* arena, index_IndexedGraph g, rdf_Term a, rdf_Term b);
void test_cli_print_result(slop_string name, uint8_t passed);
slop_option_types_ReasonerResult test_cli_parse_and_reason(slop_arena* arena, slop_string path);
uint8_t test_cli_test_subclass_chain_file(slop_arena* arena);
uint8_t test_cli_test_equivalent_class_file(slop_arena* arena);
uint8_t test_cli_test_disjoint_violation_file(slop_arena* arena);
uint8_t test_cli_test_sameas_differentfrom_file(slop_arena* arena);
uint8_t test_cli_test_sameas_chain_file(slop_arena* arena);
uint8_t test_cli_test_empty_file(slop_arena* arena);
uint8_t test_cli_test_bfo_consistent(slop_arena* arena);
uint8_t test_cli_test_invalid_literal_file(slop_arena* arena);
uint8_t test_cli_test_valid_literals_file(slop_arena* arena);
uint8_t test_cli_test_emit_roundtrip(slop_arena* arena);
uint8_t test_cli_test_missing_file(slop_arena* arena);
int main(void);

#ifndef SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
#define SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerResult, slop_option_types_ReasonerResult)
#endif


#endif
