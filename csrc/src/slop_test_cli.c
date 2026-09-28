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
uint8_t test_cli_test_rdf_star_blank_remapping(slop_arena* arena);
uint8_t test_cli_test_background_merge(slop_arena* arena);
uint8_t test_cli_test_validate_multiple_unsat(slop_arena* arena);
uint8_t test_cli_test_enrich_basic(slop_arena* arena);
uint8_t test_cli_test_enrich_skips_eq(slop_arena* arena);
uint8_t test_cli_test_enrich_skips_cls(slop_arena* arena);
uint8_t test_cli_test_enrich_checks_consistency(slop_arena* arena);
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
    __auto_type _mv_475 = ttl_parse_ttl_file(arena, path);
    if (!_mv_475.is_ok) {
        __auto_type _ = _mv_475.data.err;
        return (slop_option_types_ReasonerResult){.has_value = false};
    } else if (_mv_475.is_ok) {
        __auto_type g = _mv_475.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            return (slop_option_types_ReasonerResult){.has_value = 1, .value = growl_reason(arena, ig)};
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_subclass_chain_file(slop_arena* arena) {
    __auto_type _mv_476 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_476.has_value) {
        printf("%s\n", "  ERROR: failed to parse subclass-chain.ttl");
        return 0;
    } else if (_mv_476.has_value) {
        __auto_type result = _mv_476.value;
        __auto_type _mv_477 = result;
        switch (_mv_477.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_477.data.reason_success;
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
                __auto_type _ = _mv_477.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_equivalent_class_file(slop_arena* arena) {
    __auto_type _mv_478 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/equivalent-class.ttl"));
    if (!_mv_478.has_value) {
        printf("%s\n", "  ERROR: failed to parse equivalent-class.ttl");
        return 0;
    } else if (_mv_478.has_value) {
        __auto_type result = _mv_478.value;
        __auto_type _mv_479 = result;
        switch (_mv_479.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_479.data.reason_success;
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
                __auto_type _ = _mv_479.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_disjoint_violation_file(slop_arena* arena) {
    __auto_type _mv_480 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/disjoint-violation.ttl"));
    if (!_mv_480.has_value) {
        printf("%s\n", "  ERROR: failed to parse disjoint-violation.ttl");
        return 0;
    } else if (_mv_480.has_value) {
        __auto_type result = _mv_480.value;
        __auto_type _mv_481 = result;
        switch (_mv_481.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_481.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_481.data.reason_inconsistent;
                return 1;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_sameas_differentfrom_file(slop_arena* arena) {
    __auto_type _mv_482 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-differentfrom.ttl"));
    if (!_mv_482.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-differentfrom.ttl");
        return 0;
    } else if (_mv_482.has_value) {
        __auto_type result = _mv_482.value;
        __auto_type _mv_483 = result;
        switch (_mv_483.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_483.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_483.data.reason_inconsistent;
                return 1;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_sameas_chain_file(slop_arena* arena) {
    __auto_type _mv_484 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-chain.ttl"));
    if (!_mv_484.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-chain.ttl");
        return 0;
    } else if (_mv_484.has_value) {
        __auto_type result = _mv_484.value;
        __auto_type _mv_485 = result;
        switch (_mv_485.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_485.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type charlie = rdf_make_iri(arena, SLOP_STR("http://example.org/charlie"));
                    return test_cli_has_same_as(arena, s.graph, alice, charlie);
                }
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_485.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_empty_file(slop_arena* arena) {
    __auto_type _mv_486 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/empty.ttl"));
    if (!_mv_486.has_value) {
        printf("%s\n", "  ERROR: failed to parse empty.ttl");
        return 0;
    } else if (_mv_486.has_value) {
        __auto_type result = _mv_486.value;
        __auto_type _mv_487 = result;
        switch (_mv_487.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_487.data.reason_success;
                return (s.inferred_count <= 36);
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_487.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency on empty graph");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_bfo_consistent(slop_arena* arena) {
    {
        __auto_type start_time = slop_now_ms();
        printf("%s\n", "  BFO: parsing...");
        __auto_type _mv_488 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/bfo-core.ttl"));
        if (!_mv_488.is_ok) {
            __auto_type _ = _mv_488.data.err;
            printf("%s\n", "  ERROR: failed to parse bfo-core.ttl");
            return 0;
        } else if (_mv_488.is_ok) {
            __auto_type g = _mv_488.data.ok;
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
                    __auto_type _mv_489 = growl_reason(arena, ig);
                    switch (_mv_489.tag) {
                        case types_ReasonerResult_reason_success:
                        {
                            __auto_type s = _mv_489.data.reason_success;
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
                            __auto_type reports = _mv_489.data.reason_inconsistent;
                            printf("%s", "  ERROR: BFO inconsistent: ");
                            __auto_type _mv_490 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_490.has_value) {
                                __auto_type report = _mv_490.value;
                                printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                            } else if (!_mv_490.has_value) {
                                printf("%s\n", "(no details)");
                            }
                            return 0;
                        }
                    }
                    SLOP_UNREACHABLE();
                }
            }
        }
        SLOP_UNREACHABLE();
    }
}

uint8_t test_cli_test_invalid_literal_file(slop_arena* arena) {
    __auto_type _mv_491 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/invalid-literal.ttl"));
    if (!_mv_491.has_value) {
        printf("%s\n", "  ERROR: failed to parse invalid-literal.ttl");
        return 0;
    } else if (_mv_491.has_value) {
        __auto_type result = _mv_491.value;
        __auto_type _mv_492 = result;
        switch (_mv_492.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_492.data.reason_success;
                printf("%s\n", "  ERROR: should have detected invalid literal");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_492.data.reason_inconsistent;
                return 1;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_valid_literals_file(slop_arena* arena) {
    __auto_type _mv_493 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/valid-literals.ttl"));
    if (!_mv_493.has_value) {
        printf("%s\n", "  ERROR: failed to parse valid-literals.ttl");
        return 0;
    } else if (_mv_493.has_value) {
        __auto_type result = _mv_493.value;
        __auto_type _mv_494 = result;
        switch (_mv_494.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_494.data.reason_success;
                return 1;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type reports = _mv_494.data.reason_inconsistent;
                printf("%s", "  ERROR: unexpected inconsistency: ");
                __auto_type _mv_495 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                if (_mv_495.has_value) {
                    __auto_type report = _mv_495.value;
                    printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                } else if (!_mv_495.has_value) {
                    printf("%s\n", "(no details)");
                }
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_emit_roundtrip(slop_arena* arena) {
    __auto_type _mv_496 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_496.has_value) {
        printf("%s\n", "  ERROR: failed to parse for roundtrip");
        return 0;
    } else if (_mv_496.has_value) {
        __auto_type result = _mv_496.value;
        __auto_type _mv_497 = result;
        switch (_mv_497.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_497.data.reason_success;
                {
                    __auto_type out_graph = test_cli_indexed_to_graph(arena, s.graph);
                    slop_option_string no_base = (slop_option_string){.has_value = false};
                    __auto_type config = ((serialize_ttl_SerializeConfig){.prefixes = ttl_make_prefix_map(arena), .base_iri = no_base, .indent_width = 2});
                    __auto_type emit_path = SLOP_STR("fixtures/roundtrip-out.ttl");
                    __auto_type _mv_498 = serialize_ttl_serialize_ttl_stream(arena, out_graph, config, emit_path);
                    if (!_mv_498.is_ok) {
                        __auto_type _ = _mv_498.data.err;
                        printf("%s\n", "  ERROR: failed to write roundtrip file");
                        return 0;
                    } else if (_mv_498.is_ok) {
                        __auto_type _ = _mv_498.data.ok;
                        __auto_type _mv_499 = ttl_parse_ttl_file(arena, emit_path);
                        if (!_mv_499.is_ok) {
                            __auto_type _ = _mv_499.data.err;
                            printf("%s\n", "  ERROR: failed to re-parse emitted file");
                            return 0;
                        } else if (_mv_499.is_ok) {
                            __auto_type g2 = _mv_499.data.ok;
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
                        SLOP_UNREACHABLE();
                    }
                    SLOP_UNREACHABLE();
                }
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_497.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency in roundtrip");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_missing_file(slop_arena* arena) {
    __auto_type _mv_500 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/does-not-exist.ttl"));
    if (!_mv_500.has_value) {
        return 1;
    } else if (_mv_500.has_value) {
        __auto_type _ = _mv_500.value;
        printf("%s\n", "  ERROR: should have failed on missing file");
        return 0;
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_validate_unsat(slop_arena* arena) {
    __auto_type _mv_501 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-unsat.ttl"));
    if (!_mv_501.is_ok) {
        __auto_type _ = _mv_501.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-unsat.ttl");
        return 0;
    } else if (_mv_501.is_ok) {
        __auto_type g = _mv_501.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_502 = growl_reason_with_config(arena, ig, config);
            switch (_mv_502.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_502.data.reason_inconsistent;
                    return 1;
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_502.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable class");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_validate_clean(slop_arena* arena) {
    __auto_type _mv_503 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-clean.ttl"));
    if (!_mv_503.is_ok) {
        __auto_type _ = _mv_503.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-clean.ttl");
        return 0;
    } else if (_mv_503.is_ok) {
        __auto_type g = _mv_503.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_504 = growl_reason_with_config(arena, ig, config);
            switch (_mv_504.tag) {
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_504.data.reason_success;
                    return 1;
                }
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_504.data.reason_inconsistent;
                    printf("%s", "  ERROR: unexpected inconsistency: ");
                    __auto_type _mv_505 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_505.has_value) {
                        __auto_type report = _mv_505.value;
                        printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                    } else if (!_mv_505.has_value) {
                        printf("%s\n", "(no details)");
                    }
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_no_validate_unsat_passes(slop_arena* arena) {
    __auto_type _mv_506 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/validate-unsat.ttl"));
    if (!_mv_506.has_value) {
        printf("%s\n", "  ERROR: failed to parse validate-unsat.ttl");
        return 0;
    } else if (_mv_506.has_value) {
        __auto_type result = _mv_506.value;
        __auto_type _mv_507 = result;
        switch (_mv_507.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_507.data.reason_success;
                return 1;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_507.data.reason_inconsistent;
                printf("%s\n", "  ERROR: should pass without --validate (TBox only)");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_validate_unsat_prop(slop_arena* arena) {
    __auto_type _mv_508 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-unsat-prop.ttl"));
    if (!_mv_508.is_ok) {
        __auto_type _ = _mv_508.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-unsat-prop.ttl");
        return 0;
    } else if (_mv_508.is_ok) {
        __auto_type g = _mv_508.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_509 = growl_reason_with_config(arena, ig, config);
            switch (_mv_509.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_509.data.reason_inconsistent;
                    return 1;
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_509.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable property");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_validate_domain_reports_class(slop_arena* arena) {
    __auto_type _mv_510 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-domain-unsat.ttl"));
    if (!_mv_510.is_ok) {
        __auto_type _ = _mv_510.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-domain-unsat.ttl");
        return 0;
    } else if (_mv_510.is_ok) {
        __auto_type g = _mv_510.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_511 = growl_reason_with_config(arena, ig, config);
            switch (_mv_511.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_511.data.reason_inconsistent;
                    __auto_type _mv_512 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_512.has_value) {
                        __auto_type report = _mv_512.value;
                        return strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                    } else if (!_mv_512.has_value) {
                        return 0;
                    }
                    SLOP_UNREACHABLE();
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_511.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_validate_ns_scoping(slop_arena* arena) {
    __auto_type _mv_513 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-domain.ttl"));
    if (!_mv_513.is_ok) {
        __auto_type _ = _mv_513.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-domain.ttl");
        return 0;
    } else if (_mv_513.is_ok) {
        __auto_type g = _mv_513.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/"), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_514 = growl_reason_with_config(arena, ig, config);
            switch (_mv_514.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_514.data.reason_inconsistent;
                    __auto_type _mv_515 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_515.has_value) {
                        __auto_type report = _mv_515.value;
                        return strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                    } else if (!_mv_515.has_value) {
                        return 0;
                    }
                    SLOP_UNREACHABLE();
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_514.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable ex:Bad");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_validate_ns_filters_tlo(slop_arena* arena) {
    __auto_type _mv_516 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-tlo.ttl"));
    if (!_mv_516.is_ok) {
        __auto_type _ = _mv_516.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-tlo.ttl");
        return 0;
    } else if (_mv_516.is_ok) {
        __auto_type g = _mv_516.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/"), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_517 = growl_reason_with_config(arena, ig, config);
            switch (_mv_517.tag) {
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_517.data.reason_success;
                    return 1;
                }
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_517.data.reason_inconsistent;
                    printf("%s", "  ERROR: unexpected inconsistency: ");
                    __auto_type _mv_518 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_518.has_value) {
                        __auto_type report = _mv_518.value;
                        printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                    } else if (!_mv_518.has_value) {
                        printf("%s\n", "(no details)");
                    }
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_rdf_star_blank_remapping(slop_arena* arena) {
    {
        __auto_type predicate = rdf_make_iri(arena, SLOP_STR("http://example.org/p"));
        __auto_type value = rdf_make_iri(arena, SLOP_STR("http://example.org/value"));
        __auto_type inner = rdf_make_triple(arena, rdf_make_blank(arena, 2), predicate, value);
        __auto_type inner_term = rdf_make_triple_term(arena, inner);
        __auto_type outer = rdf_make_triple(arena, rdf_make_blank(arena, 7), predicate, inner_term);
        __auto_type quoted = rdf_make_triple_term(arena, outer);
        __auto_type expected_inner = rdf_make_triple(arena, rdf_make_blank(arena, 12), predicate, value);
        __auto_type expected_inner_term = rdf_make_triple_term(arena, expected_inner);
        __auto_type expected_outer = rdf_make_triple(arena, rdf_make_blank(arena, 17), predicate, expected_inner_term);
        __auto_type expected = rdf_make_triple_term(arena, expected_outer);
        __auto_type remapped = growl_remap_blank_term(arena, quoted, 10);
        __auto_type ig = rdf_indexed_graph_create(arena);
        ig = rdf_indexed_graph_add(arena, ig, rdf_make_triple(arena, value, predicate, quoted));
        return ((growl_max_blank_id_in_graph(ig) == 7) && rdf_term_eq(remapped, expected));
    }
}

uint8_t test_cli_test_background_merge(slop_arena* arena) {
    __auto_type _mv_519 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-tlo.ttl"));
    if (!_mv_519.is_ok) {
        __auto_type _ = _mv_519.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-tlo.ttl");
        return 0;
    } else if (_mv_519.is_ok) {
        __auto_type bg_graph = _mv_519.data.ok;
        __auto_type _mv_520 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-domain-only.ttl"));
        if (!_mv_520.is_ok) {
            __auto_type _ = _mv_520.data.err;
            printf("%s\n", "  ERROR: failed to parse validate-domain-only.ttl");
            return 0;
        } else if (_mv_520.is_ok) {
            __auto_type domain_graph = _mv_520.data.ok;
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
                    __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/"), .cancel_ptr = 0, .max_triples = 0});
                    __auto_type _mv_521 = growl_reason_with_config(arena, ig, config);
                    switch (_mv_521.tag) {
                        case types_ReasonerResult_reason_inconsistent:
                        {
                            __auto_type reports = _mv_521.data.reason_inconsistent;
                            __auto_type _mv_522 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_522.has_value) {
                                __auto_type report = _mv_522.value;
                                return strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                            } else if (!_mv_522.has_value) {
                                return 0;
                            }
                            SLOP_UNREACHABLE();
                        }
                        case types_ReasonerResult_reason_success:
                        {
                            __auto_type _ = _mv_521.data.reason_success;
                            printf("%s\n", "  ERROR: should have detected unsatisfiable ex:Bad via background merge");
                            return 0;
                        }
                    }
                    SLOP_UNREACHABLE();
                }
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_validate_multiple_unsat(slop_arena* arena) {
    __auto_type _mv_523 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-multi-unsat.ttl"));
    if (!_mv_523.is_ok) {
        __auto_type _ = _mv_523.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-multi-unsat.ttl");
        return 0;
    } else if (_mv_523.is_ok) {
        __auto_type g = _mv_523.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_524 = growl_reason_with_config(arena, ig, config);
            switch (_mv_524.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_524.data.reason_inconsistent;
                    {
                        __auto_type count = ((int64_t)((reports).len));
                        if (count == 2) {
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
                    __auto_type _ = _mv_524.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable classes");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_enrich_basic(slop_arena* arena) {
    __auto_type _mv_525 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_525.is_ok) {
        __auto_type _ = _mv_525.data.err;
        printf("%s\n", "  ERROR: failed to parse subclass-chain.ttl");
        return 0;
    } else if (_mv_525.is_ok) {
        __auto_type g = _mv_525.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_526 = growl_reason_with_config(arena, ig, config);
            switch (_mv_526.tag) {
                case types_ReasonerResult_reason_success:
                {
                    __auto_type s = _mv_526.data.reason_success;
                    {
                        __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                        __auto_type person = rdf_make_iri(arena, SLOP_STR("http://example.org/Person"));
                        __auto_type agent = rdf_make_iri(arena, SLOP_STR("http://example.org/Agent"));
                        __auto_type g = s.graph;
                        return (test_cli_has_type(arena, g, alice, person) && test_cli_has_type(arena, g, alice, agent));
                    }
                }
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_526.data.reason_inconsistent;
                    printf("%s\n", "  ERROR: unexpected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_enrich_skips_eq(slop_arena* arena) {
    __auto_type _mv_527 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/sameas-chain.ttl"));
    if (!_mv_527.is_ok) {
        __auto_type _ = _mv_527.data.err;
        printf("%s\n", "  ERROR: failed to parse sameas-chain.ttl");
        return 0;
    } else if (_mv_527.is_ok) {
        __auto_type g = _mv_527.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_528 = growl_reason_with_config(arena, ig, config);
            switch (_mv_528.tag) {
                case types_ReasonerResult_reason_success:
                {
                    __auto_type s = _mv_528.data.reason_success;
                    {
                        __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                        __auto_type charlie = rdf_make_iri(arena, SLOP_STR("http://example.org/charlie"));
                        return !(test_cli_has_same_as(arena, s.graph, alice, charlie));
                    }
                }
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_528.data.reason_inconsistent;
                    printf("%s\n", "  ERROR: unexpected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_enrich_skips_cls(slop_arena* arena) {
    __auto_type _mv_529 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/enrich-cls-test.ttl"));
    if (!_mv_529.is_ok) {
        __auto_type _ = _mv_529.data.err;
        printf("%s\n", "  ERROR: failed to parse enrich-cls-test.ttl");
        return 0;
    } else if (_mv_529.is_ok) {
        __auto_type g = _mv_529.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_530 = growl_reason_with_config(arena, ig, config);
            switch (_mv_530.tag) {
                case types_ReasonerResult_reason_success:
                {
                    __auto_type s = _mv_530.data.reason_success;
                    {
                        __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                        __auto_type p = rdf_make_iri(arena, SLOP_STR("http://example.org/p"));
                        __auto_type v = rdf_make_iri(arena, SLOP_STR("http://example.org/v"));
                        __auto_type expected = rdf_make_triple(arena, alice, p, v);
                        return !(rdf_indexed_graph_contains(s.graph, expected));
                    }
                }
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_530.data.reason_inconsistent;
                    printf("%s\n", "  ERROR: unexpected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t test_cli_test_enrich_checks_consistency(slop_arena* arena) {
    __auto_type _mv_531 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/disjoint-violation.ttl"));
    if (!_mv_531.is_ok) {
        __auto_type _ = _mv_531.data.err;
        printf("%s\n", "  ERROR: failed to parse disjoint-violation.ttl");
        return 0;
    } else if (_mv_531.is_ok) {
        __auto_type g = _mv_531.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_532 = growl_reason_with_config(arena, ig, config);
            switch (_mv_532.tag) {
                case types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_532.data.reason_inconsistent;
                    return 1;
                }
                case types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_532.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected disjoint violation in enrich mode");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
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
                __auto_type r = test_cli_test_rdf_star_blank_remapping(arena);
                test_cli_print_result(SLOP_STR("background merge: remaps RDF-star blank nodes"), r);
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
                __auto_type r = test_cli_test_enrich_basic(arena);
                test_cli_print_result(SLOP_STR("enrich: subclass types inferred"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_enrich_skips_eq(arena);
                test_cli_print_result(SLOP_STR("enrich: sameAs transitivity skipped"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_enrich_skips_cls(arena);
                test_cli_print_result(SLOP_STR("enrich: cls-hv1 skipped"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = test_cli_test_enrich_checks_consistency(arena);
                test_cli_print_result(SLOP_STR("enrich: disjoint violation still detected"), r);
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
            if (failed == 0) {
                return 0;
            } else {
                return 1;
            }
        }
        slop_arena_free(arena);
    }
}

