#ifndef SLOP_test_cli_H
#define SLOP_test_cli_H

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
#include "slop_ttl.h"
#include "slop_serialize_ttl.h"
#include "slop_vocab.h"
#include "slop_growl.h"
#include "slop_strlib.h"

#ifndef SLOP_OPTION_GROWL_TYPES_REASONERRESULT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_REASONERRESULT_DEFINED
SLOP_OPTION_DEFINE(growl_types_ReasonerResult, slop_option_growl_types_ReasonerResult)
#endif

slop_rdf_index_IndexedGraph growl_cli_test_test_cli_graph_to_indexed(slop_arena* arena, slop_rdf_rdf_Graph g);
slop_rdf_rdf_Graph growl_cli_test_test_cli_indexed_to_graph(slop_arena* arena, slop_rdf_index_IndexedGraph ig);
uint8_t growl_cli_test_test_cli_has_type(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term individual, slop_rdf_rdf_Term class);
uint8_t growl_cli_test_test_cli_has_same_as(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term a, slop_rdf_rdf_Term b);
void growl_cli_test_test_cli_print_result(slop_string name, uint8_t passed);
slop_option_growl_types_ReasonerResult growl_cli_test_test_cli_parse_and_reason(slop_arena* arena, slop_string path);
uint8_t growl_cli_test_test_cli_test_subclass_chain_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_equivalent_class_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_disjoint_violation_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_sameas_differentfrom_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_sameas_chain_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_empty_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_bfo_consistent(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_invalid_literal_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_valid_literals_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_emit_roundtrip(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_missing_file(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_validate_unsat(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_validate_clean(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_no_validate_unsat_passes(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_validate_unsat_prop(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_validate_domain_reports_class(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_validate_ns_scoping(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_validate_ns_filters_tlo(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_rdf_star_blank_remapping(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_background_merge(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_validate_multiple_unsat(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_enrich_basic(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_enrich_skips_eq(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_enrich_skips_cls(slop_arena* arena);
uint8_t growl_cli_test_test_cli_test_enrich_checks_consistency(slop_arena* arena);
int main(int argc, char** _c_argv);

#ifndef SLOP_OPTION_GROWL_TYPES_REASONERRESULT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_REASONERRESULT_DEFINED
SLOP_OPTION_DEFINE(growl_types_ReasonerResult, slop_option_growl_types_ReasonerResult)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif


#endif
