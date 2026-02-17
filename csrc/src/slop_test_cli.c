#include "../runtime/slop_runtime.h"
#include "slop_test_cli.h"

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
uint8_t test_cli_test_validate_unsat(slop_arena* arena);
uint8_t test_cli_test_validate_clean(slop_arena* arena);
uint8_t test_cli_test_no_validate_unsat_passes(slop_arena* arena);
uint8_t test_cli_test_validate_unsat_prop(slop_arena* arena);
uint8_t test_cli_test_validate_domain_reports_class(slop_arena* arena);
uint8_t test_cli_test_validate_ns_scoping(slop_arena* arena);
uint8_t test_cli_test_validate_ns_filters_tlo(slop_arena* arena);
uint8_t test_cli_test_background_merge(slop_arena* arena);
uint8_t test_cli_test_validate_multiple_unsat(slop_arena* arena);
int main(int argc, char** _c_argv);

index_IndexedGraph test_cli_graph_to_indexed(slop_arena* arena, rdf_Graph g) {
    {
        __auto_type ig = rdf_indexed_graph_create(arena);
        {
            __auto_type _coll = g.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                ig = rdf_indexed_graph_add(arena, ig, t);
            }
        }
        return ig;
    }
}

rdf_Graph test_cli_indexed_to_graph(slop_arena* arena, index_IndexedGraph ig) {
    return ((rdf_Graph){.triples = ig.triples, .size = ((rdf_GraphSize)(rdf_indexed_graph_size(ig)))});
}

uint8_t test_cli_has_type(slop_arena* arena, index_IndexedGraph g, rdf_Term individual, rdf_Term class) {
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type matches = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = individual}, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = class});
        return (((int64_t)((matches).len)) > 0);
    }
}

uint8_t test_cli_has_same_as(slop_arena* arena, index_IndexedGraph g, rdf_Term a, rdf_Term b) {
    {
        __auto_type same_pred = rdf_make_iri(arena, vocab_OWL_SAME_AS);
        __auto_type fwd = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = a}, (slop_option_rdf_Term){.has_value = 1, .value = same_pred}, (slop_option_rdf_Term){.has_value = 1, .value = b});
        __auto_type bwd = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = b}, (slop_option_rdf_Term){.has_value = 1, .value = same_pred}, (slop_option_rdf_Term){.has_value = 1, .value = a});
        return ((((int64_t)((fwd).len)) > 0) || (((int64_t)((bwd).len)) > 0));
    }
}

void test_cli_print_result(slop_string name, uint8_t passed) {
    if (passed) {
        printf("%s", "[PASS] ");
        printf("%.*s\n", (int)(name).len, (name).data);
    } else {
        printf("%s", "[FAIL] ");
        printf("%.*s\n", (int)(name).len, (name).data);
    }
}

slop_option_types_ReasonerResult test_cli_parse_and_reason(slop_arena* arena, slop_string path) {
    __auto_type _mv_356 = ttl_parse_ttl_file(arena, path);
    if (!_mv_356.is_ok) {
        __auto_type _ = _mv_356.data.err;
        return (slop_option_types_ReasonerResult){.has_value = false};
    } else if (_mv_356.is_ok) {
        __auto_type g = _mv_356.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            return (slop_option_types_ReasonerResult){.has_value = 1, .value = growl_reason(arena, ig)};
        }
    }
}

uint8_t test_cli_test_subclass_chain_file(slop_arena* arena) {
    __auto_type _mv_357 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_357.has_value) {
        printf("%s\n", "  ERROR: failed to parse subclass-chain.ttl");
        return 0;
    } else if (_mv_357.has_value) {
        __auto_type result = _mv_357.value;
        __auto_type _mv_358 = result;
        switch (_mv_358.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_358.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type person = rdf_make_iri(arena, SLOP_STR("http://example.org/Person"));
                    __auto_type agent = rdf_make_iri(arena, SLOP_STR("http://example.org/Agent"));
                    __auto_type g = s.graph;
                    {
                        __auto_type has_person = test_cli_has_type(arena, g, alice, person);
                        __auto_type has_agent = test_cli_has_type(arena, g, alice, agent);
                        __auto_type did_infer = (s.inferred_count > 0);
                        return (has_person && (has_agent && did_infer));
                    }
                }
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_358.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_equivalent_class_file(slop_arena* arena) {
    __auto_type _mv_359 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/equivalent-class.ttl"));
    if (!_mv_359.has_value) {
        printf("%s\n", "  ERROR: failed to parse equivalent-class.ttl");
        return 0;
    } else if (_mv_359.has_value) {
        __auto_type result = _mv_359.value;
        __auto_type _mv_360 = result;
        switch (_mv_360.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_360.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type bob = rdf_make_iri(arena, SLOP_STR("http://example.org/bob"));
                    __auto_type human = rdf_make_iri(arena, SLOP_STR("http://example.org/Human"));
                    __auto_type person = rdf_make_iri(arena, SLOP_STR("http://example.org/Person"));
                    __auto_type g = s.graph;
                    return (test_cli_has_type(arena, g, alice, person) && test_cli_has_type(arena, g, bob, human));
                }
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_360.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_disjoint_violation_file(slop_arena* arena) {
    __auto_type _mv_361 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/disjoint-violation.ttl"));
    if (!_mv_361.has_value) {
        printf("%s\n", "  ERROR: failed to parse disjoint-violation.ttl");
        return 0;
    } else if (_mv_361.has_value) {
        __auto_type result = _mv_361.value;
        __auto_type _mv_362 = result;
        switch (_mv_362.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_362.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_362.data.reason_inconsistent;
                return 1;
            }
        }
    }
}

uint8_t test_cli_test_sameas_differentfrom_file(slop_arena* arena) {
    __auto_type _mv_363 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-differentfrom.ttl"));
    if (!_mv_363.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-differentfrom.ttl");
        return 0;
    } else if (_mv_363.has_value) {
        __auto_type result = _mv_363.value;
        __auto_type _mv_364 = result;
        switch (_mv_364.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_364.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_364.data.reason_inconsistent;
                return 1;
            }
        }
    }
}

uint8_t test_cli_test_sameas_chain_file(slop_arena* arena) {
    __auto_type _mv_365 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-chain.ttl"));
    if (!_mv_365.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-chain.ttl");
        return 0;
    } else if (_mv_365.has_value) {
        __auto_type result = _mv_365.value;
        __auto_type _mv_366 = result;
        switch (_mv_366.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_366.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type charlie = rdf_make_iri(arena, SLOP_STR("http://example.org/charlie"));
                    return test_cli_has_same_as(arena, s.graph, alice, charlie);
                }
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_366.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_empty_file(slop_arena* arena) {
    __auto_type _mv_367 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/empty.ttl"));
    if (!_mv_367.has_value) {
        printf("%s\n", "  ERROR: failed to parse empty.ttl");
        return 0;
    } else if (_mv_367.has_value) {
        __auto_type result = _mv_367.value;
        __auto_type _mv_368 = result;
        switch (_mv_368.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_368.data.reason_success;
                return (s.inferred_count <= 36);
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_368.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency on empty graph");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_bfo_consistent(slop_arena* arena) {
    {
        __auto_type start_time = slop_now_ms();
        printf("%s\n", "  BFO: parsing...");
        __auto_type _mv_369 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/bfo-core.ttl"));
        if (!_mv_369.is_ok) {
            __auto_type _ = _mv_369.data.err;
            printf("%s\n", "  ERROR: failed to parse bfo-core.ttl");
            return 0;
        } else if (_mv_369.is_ok) {
            __auto_type g = _mv_369.data.ok;
            printf("%s", "  BFO: parsed ");
            printf("%.*s", (int)(int_to_string(arena, rdf_graph_size(g))).len, (int_to_string(arena, rdf_graph_size(g))).data);
            printf("%s\n", " triples, indexing...");
            {
                __auto_type ig = test_cli_graph_to_indexed(arena, g);
                printf("%s", "  BFO: indexed ");
                printf("%.*s", (int)(int_to_string(arena, rdf_indexed_graph_size(ig))).len, (int_to_string(arena, rdf_indexed_graph_size(ig))).data);
                printf("%s\n", " triples, reasoning...");
                {
                    __auto_type reason_start = slop_now_ms();
                    __auto_type _mv_370 = growl_reason(arena, ig);
                    switch (_mv_370.tag) {
                        case types_ReasonerResult_reason_success:
                        {
                            __auto_type s = _mv_370.data.reason_success;
                            {
                                __auto_type end_time = slop_now_ms();
                                printf("%s", "  BFO: ");
                                printf("%.*s", (int)(int_to_string(arena, s.inferred_count)).len, (int_to_string(arena, s.inferred_count)).data);
                                printf("%s", " inferred, ");
                                printf("%.*s", (int)(int_to_string(arena, s.iterations)).len, (int_to_string(arena, s.iterations)).data);
                                printf("%s", " iterations, ");
                                printf("%.*s", (int)(int_to_string(arena, (end_time - reason_start))).len, (int_to_string(arena, (end_time - reason_start))).data);
                                printf("%s\n", "ms reasoning");
                                printf("%s", "  BFO: total ");
                                printf("%.*s", (int)(int_to_string(arena, (end_time - start_time))).len, (int_to_string(arena, (end_time - start_time))).data);
                                printf("%s\n", "ms");
                                return 1;
                            }
                        }
                        case types_ReasonerResult_reason_inconsistent:
                        {
                            __auto_type reports = _mv_370.data.reason_inconsistent;
                            printf("%s", "  ERROR: BFO inconsistent: ");
                            __auto_type _mv_371 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_371.has_value) {
                                __auto_type report = _mv_371.value;
                                printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                            } else if (!_mv_371.has_value) {
                                printf("%s\n", "(no details)");
                            }
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

uint8_t test_cli_test_invalid_literal_file(slop_arena* arena) {
    __auto_type _mv_372 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/invalid-literal.ttl"));
    if (!_mv_372.has_value) {
        printf("%s\n", "  ERROR: failed to parse invalid-literal.ttl");
        return 0;
    } else if (_mv_372.has_value) {
        __auto_type result = _mv_372.value;
        __auto_type _mv_373 = result;
        switch (_mv_373.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_373.data.reason_success;
                printf("%s\n", "  ERROR: should have detected invalid literal");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_373.data.reason_inconsistent;
                return 1;
            }
        }
    }
}

uint8_t test_cli_test_valid_literals_file(slop_arena* arena) {
    __auto_type _mv_374 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/valid-literals.ttl"));
    if (!_mv_374.has_value) {
        printf("%s\n", "  ERROR: failed to parse valid-literals.ttl");
        return 0;
    } else if (_mv_374.has_value) {
        __auto_type result = _mv_374.value;
        __auto_type _mv_375 = result;
        switch (_mv_375.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_375.data.reason_success;
                return 1;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type reports = _mv_375.data.reason_inconsistent;
                printf("%s", "  ERROR: unexpected inconsistency: ");
                __auto_type _mv_376 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                if (_mv_376.has_value) {
                    __auto_type report = _mv_376.value;
                    printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                } else if (!_mv_376.has_value) {
                    printf("%s\n", "(no details)");
                }
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_emit_roundtrip(slop_arena* arena) {
    __auto_type _mv_377 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_377.has_value) {
        printf("%s\n", "  ERROR: failed to parse for roundtrip");
        return 0;
    } else if (_mv_377.has_value) {
        __auto_type result = _mv_377.value;
        __auto_type _mv_378 = result;
        switch (_mv_378.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_378.data.reason_success;
                {
                    __auto_type out_graph = test_cli_indexed_to_graph(arena, s.graph);
                    slop_option_string no_base = (slop_option_string){.has_value = false};
                    __auto_type config = ((serialize_ttl_SerializeConfig){.prefixes = ttl_make_prefix_map(arena), .base_iri = no_base, .indent_width = 2});
                    __auto_type emit_path = SLOP_STR("fixtures/roundtrip-out.ttl");
                    __auto_type _mv_379 = serialize_ttl_serialize_ttl_stream(arena, out_graph, config, emit_path);
                    if (!_mv_379.is_ok) {
                        __auto_type _ = _mv_379.data.err;
                        printf("%s\n", "  ERROR: failed to write roundtrip file");
                        return 0;
                    } else if (_mv_379.is_ok) {
                        __auto_type _ = _mv_379.data.ok;
                        __auto_type _mv_380 = ttl_parse_ttl_file(arena, emit_path);
                        if (!_mv_380.is_ok) {
                            __auto_type _ = _mv_380.data.err;
                            printf("%s\n", "  ERROR: failed to re-parse emitted file");
                            return 0;
                        } else if (_mv_380.is_ok) {
                            __auto_type g2 = _mv_380.data.ok;
                            {
                                __auto_type original_size = rdf_indexed_graph_size(s.graph);
                                __auto_type reparsed_size = rdf_graph_size(g2);
                                printf("%s", "  Roundtrip: emitted ");
                                printf("%.*s", (int)(int_to_string(arena, original_size)).len, (int_to_string(arena, original_size)).data);
                                printf("%s", " triples, re-parsed ");
                                printf("%.*s\n", (int)(int_to_string(arena, reparsed_size)).len, (int_to_string(arena, reparsed_size)).data);
                                return (reparsed_size >= 3);
                            }
                        }
                    }
                }
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_378.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency in roundtrip");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_missing_file(slop_arena* arena) {
    __auto_type _mv_381 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/does-not-exist.ttl"));
    if (!_mv_381.has_value) {
        return 1;
    } else if (_mv_381.has_value) {
        __auto_type _ = _mv_381.value;
        printf("%s\n", "  ERROR: should have failed on missing file");
        return 0;
    }
}

uint8_t test_cli_test_validate_unsat(slop_arena* arena) {
    __auto_type _mv_382 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-unsat.ttl"));
    if (!_mv_382.is_ok) {
        __auto_type _ = _mv_382.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-unsat.ttl");
        return 0;
    } else if (_mv_382.is_ok) {
        __auto_type g = _mv_382.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("")});
            __auto_type _mv_383 = growl_reason_with_config(arena, ig, config);
            switch (_mv_383.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_383.data.reason_inconsistent;
                    return 1;
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_383.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable class");
                    return 0;
                }
            }
        }
    }
}

uint8_t test_cli_test_validate_clean(slop_arena* arena) {
    __auto_type _mv_384 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-clean.ttl"));
    if (!_mv_384.is_ok) {
        __auto_type _ = _mv_384.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-clean.ttl");
        return 0;
    } else if (_mv_384.is_ok) {
        __auto_type g = _mv_384.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("")});
            __auto_type _mv_385 = growl_reason_with_config(arena, ig, config);
            switch (_mv_385.tag) {
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_385.data.reason_success;
                    return 1;
                }
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_385.data.reason_inconsistent;
                    printf("%s", "  ERROR: unexpected inconsistency: ");
                    __auto_type _mv_386 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_386.has_value) {
                        __auto_type report = _mv_386.value;
                        printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                    } else if (!_mv_386.has_value) {
                        printf("%s\n", "(no details)");
                    }
                    return 0;
                }
            }
        }
    }
}

uint8_t test_cli_test_no_validate_unsat_passes(slop_arena* arena) {
    __auto_type _mv_387 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/validate-unsat.ttl"));
    if (!_mv_387.has_value) {
        printf("%s\n", "  ERROR: failed to parse validate-unsat.ttl");
        return 0;
    } else if (_mv_387.has_value) {
        __auto_type result = _mv_387.value;
        __auto_type _mv_388 = result;
        switch (_mv_388.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_388.data.reason_success;
                return 1;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_388.data.reason_inconsistent;
                printf("%s\n", "  ERROR: should pass without --validate (TBox only)");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_validate_unsat_prop(slop_arena* arena) {
    __auto_type _mv_389 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-unsat-prop.ttl"));
    if (!_mv_389.is_ok) {
        __auto_type _ = _mv_389.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-unsat-prop.ttl");
        return 0;
    } else if (_mv_389.is_ok) {
        __auto_type g = _mv_389.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("")});
            __auto_type _mv_390 = growl_reason_with_config(arena, ig, config);
            switch (_mv_390.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_390.data.reason_inconsistent;
                    return 1;
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_390.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable property");
                    return 0;
                }
            }
        }
    }
}

uint8_t test_cli_test_validate_domain_reports_class(slop_arena* arena) {
    __auto_type _mv_391 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-domain-unsat.ttl"));
    if (!_mv_391.is_ok) {
        __auto_type _ = _mv_391.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-domain-unsat.ttl");
        return 0;
    } else if (_mv_391.is_ok) {
        __auto_type g = _mv_391.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("")});
            __auto_type _mv_392 = growl_reason_with_config(arena, ig, config);
            switch (_mv_392.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_392.data.reason_inconsistent;
                    __auto_type _mv_393 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_393.has_value) {
                        __auto_type report = _mv_393.value;
                        return strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                    } else if (!_mv_393.has_value) {
                        return 0;
                    }
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_392.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected inconsistency");
                    return 0;
                }
            }
        }
    }
}

uint8_t test_cli_test_validate_ns_scoping(slop_arena* arena) {
    __auto_type _mv_394 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-domain.ttl"));
    if (!_mv_394.is_ok) {
        __auto_type _ = _mv_394.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-domain.ttl");
        return 0;
    } else if (_mv_394.is_ok) {
        __auto_type g = _mv_394.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/")});
            __auto_type _mv_395 = growl_reason_with_config(arena, ig, config);
            switch (_mv_395.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_395.data.reason_inconsistent;
                    __auto_type _mv_396 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_396.has_value) {
                        __auto_type report = _mv_396.value;
                        return strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                    } else if (!_mv_396.has_value) {
                        return 0;
                    }
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_395.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable ex:Bad");
                    return 0;
                }
            }
        }
    }
}

uint8_t test_cli_test_validate_ns_filters_tlo(slop_arena* arena) {
    __auto_type _mv_397 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-tlo.ttl"));
    if (!_mv_397.is_ok) {
        __auto_type _ = _mv_397.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-tlo.ttl");
        return 0;
    } else if (_mv_397.is_ok) {
        __auto_type g = _mv_397.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/")});
            __auto_type _mv_398 = growl_reason_with_config(arena, ig, config);
            switch (_mv_398.tag) {
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_398.data.reason_success;
                    return 1;
                }
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_398.data.reason_inconsistent;
                    printf("%s", "  ERROR: unexpected inconsistency: ");
                    __auto_type _mv_399 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_399.has_value) {
                        __auto_type report = _mv_399.value;
                        printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                    } else if (!_mv_399.has_value) {
                        printf("%s\n", "(no details)");
                    }
                    return 0;
                }
            }
        }
    }
}

uint8_t test_cli_test_background_merge(slop_arena* arena) {
    __auto_type _mv_400 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-tlo.ttl"));
    if (!_mv_400.is_ok) {
        __auto_type _ = _mv_400.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-tlo.ttl");
        return 0;
    } else if (_mv_400.is_ok) {
        __auto_type bg_graph = _mv_400.data.ok;
        __auto_type _mv_401 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-domain-only.ttl"));
        if (!_mv_401.is_ok) {
            __auto_type _ = _mv_401.data.err;
            printf("%s\n", "  ERROR: failed to parse validate-domain-only.ttl");
            return 0;
        } else if (_mv_401.is_ok) {
            __auto_type domain_graph = _mv_401.data.ok;
            {
                __auto_type ig = test_cli_graph_to_indexed(arena, domain_graph);
                __auto_type bg_blank_offset = (growl_max_blank_id_in_graph(ig) + 1);
                {
                    __auto_type _coll = bg_graph.triples;
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type t = _coll.data[_i];
                        {
                            __auto_type rs = growl_remap_blank_term(arena, t.subject, bg_blank_offset);
                            __auto_type rp = t.predicate;
                            __auto_type ro = growl_remap_blank_term(arena, t.object, bg_blank_offset);
                            __auto_type remapped = rdf_make_triple(arena, rs, rp, ro);
                            ig = rdf_indexed_graph_add(arena, ig, remapped);
                        }
                    }
                }
                {
                    __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/")});
                    __auto_type _mv_402 = growl_reason_with_config(arena, ig, config);
                    switch (_mv_402.tag) {
                        case types_ReasonerResult_reason_inconsistent:
                        {
                            __auto_type reports = _mv_402.data.reason_inconsistent;
                            __auto_type _mv_403 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_403.has_value) {
                                __auto_type report = _mv_403.value;
                                return strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                            } else if (!_mv_403.has_value) {
                                return 0;
                            }
                        }
                        case types_ReasonerResult_reason_success:
                        {
                            __auto_type _ = _mv_402.data.reason_success;
                            printf("%s\n", "  ERROR: should have detected unsatisfiable ex:Bad via background merge");
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

uint8_t test_cli_test_validate_multiple_unsat(slop_arena* arena) {
    __auto_type _mv_404 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-multi-unsat.ttl"));
    if (!_mv_404.is_ok) {
        __auto_type _ = _mv_404.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-multi-unsat.ttl");
        return 0;
    } else if (_mv_404.is_ok) {
        __auto_type g = _mv_404.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .validate = 1, .validate_ns = SLOP_STR("")});
            __auto_type _mv_405 = growl_reason_with_config(arena, ig, config);
            switch (_mv_405.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_405.data.reason_inconsistent;
                    {
                        __auto_type count = ((int64_t)((reports).len));
                        if ((count == 2)) {
                            {
                                __auto_type all_class = 1;
                                {
                                    __auto_type _coll = reports;
                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                        __auto_type r = _coll.data[_i];
                                        if (!(strlib_starts_with(r.reason, SLOP_STR("Unsatisfiable class:")))) {
                                            printf("%s", "  ERROR: unexpected report: ");
                                            printf("%.*s\n", (int)(r.reason).len, (r.reason).data);
                                            all_class = 0;
                                        }
                                    }
                                }
                                return all_class;
                            }
                        } else {
                            printf("%s", "  ERROR: expected 2 reports, got ");
                            printf("%.*s\n", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                            {
                                __auto_type _coll = reports;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type r = _coll.data[_i];
                                    printf("%s", "    ");
                                    printf("%.*s\n", (int)(r.reason).len, (r.reason).data);
                                }
                            }
                            return 0;
                        }
                    }
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_405.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable classes");
                    return 0;
                }
            }
        }
    }
}

int main(int argc, char** _c_argv) {
    uint8_t** argv = (uint8_t**)_c_argv;
    {
        #ifdef SLOP_DEBUG
        SLOP_PRE((536870912) > 0, "with-arena size must be positive");
        #endif
        slop_arena _arena = slop_arena_new(536870912);
        #ifdef SLOP_DEBUG
        SLOP_PRE(_arena.base != NULL, "arena allocation failed");
        #endif
        slop_arena* arena = &_arena;
        {
            int64_t passed = 0;
            int64_t failed = 0;
            printf("%s\n", "========================================");
            printf("%s\n", "Growl CLI Integration Tests");
            printf("%s\n", "========================================");
            printf("%s\n", "");
            {
                __auto_type r = test_cli_test_bfo_consistent(arena);
                test_cli_print_result(SLOP_STR("BFO ontology consistent"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_subclass_chain_file(arena);
                test_cli_print_result(SLOP_STR("subclass chain from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_equivalent_class_file(arena);
                test_cli_print_result(SLOP_STR("equivalent class from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_sameas_chain_file(arena);
                test_cli_print_result(SLOP_STR("sameAs transitivity from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_empty_file(arena);
                test_cli_print_result(SLOP_STR("empty graph from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_disjoint_violation_file(arena);
                test_cli_print_result(SLOP_STR("disjoint violation detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_sameas_differentfrom_file(arena);
                test_cli_print_result(SLOP_STR("sameAs/differentFrom violation detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_invalid_literal_file(arena);
                test_cli_print_result(SLOP_STR("dt-not-type: invalid literal detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_valid_literals_file(arena);
                test_cli_print_result(SLOP_STR("dt-not-type: valid literals pass"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_emit_roundtrip(arena);
                test_cli_print_result(SLOP_STR("emit roundtrip (serialize + re-parse)"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_validate_unsat(arena);
                test_cli_print_result(SLOP_STR("validate: unsatisfiable class detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_validate_clean(arena);
                test_cli_print_result(SLOP_STR("validate: clean TBox passes"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_no_validate_unsat_passes(arena);
                test_cli_print_result(SLOP_STR("validate: unsat TBox passes without --validate"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_validate_unsat_prop(arena);
                test_cli_print_result(SLOP_STR("validate: unsatisfiable property detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_validate_domain_reports_class(arena);
                test_cli_print_result(SLOP_STR("validate: domain-mediated reports class"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_validate_ns_scoping(arena);
                test_cli_print_result(SLOP_STR("validate-ns: scoped to domain namespace"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_validate_ns_filters_tlo(arena);
                test_cli_print_result(SLOP_STR("validate-ns: TLO entities filtered out"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_background_merge(arena);
                test_cli_print_result(SLOP_STR("background merge: detects unsatisfiable class"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_validate_multiple_unsat(arena);
                test_cli_print_result(SLOP_STR("validate: multiple unsatisfiable classes"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_missing_file(arena);
                test_cli_print_result(SLOP_STR("missing file handled gracefully"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            printf("%s\n", "");
            printf("%s\n", "========================================");
            printf("%s", "Passed: ");
            printf("%.*s\n", (int)(int_to_string(arena, passed)).len, (int_to_string(arena, passed)).data);
            printf("%s", "Failed: ");
            printf("%.*s\n", (int)(int_to_string(arena, failed)).len, (int_to_string(arena, failed)).data);
            printf("%s\n", "========================================");
            if ((failed == 0)) {
                return 0;
            } else {
                return 1;
            }
        }
        slop_arena_free(arena);
    }
}

