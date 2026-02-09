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
int main(void);

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
    __auto_type _mv_315 = ttl_parse_ttl_file(arena, path);
    if (!_mv_315.is_ok) {
        __auto_type _ = _mv_315.data.err;
        return (slop_option_types_ReasonerResult){.has_value = false};
    } else if (_mv_315.is_ok) {
        __auto_type g = _mv_315.data.ok;
        {
            __auto_type ig = test_cli_graph_to_indexed(arena, g);
            return (slop_option_types_ReasonerResult){.has_value = 1, .value = growl_reason(arena, ig)};
        }
    }
}

uint8_t test_cli_test_subclass_chain_file(slop_arena* arena) {
    __auto_type _mv_316 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_316.has_value) {
        printf("%s\n", "  ERROR: failed to parse subclass-chain.ttl");
        return 0;
    } else if (_mv_316.has_value) {
        __auto_type result = _mv_316.value;
        __auto_type _mv_317 = result;
        switch (_mv_317.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_317.data.reason_success;
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
                __auto_type _ = _mv_317.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_equivalent_class_file(slop_arena* arena) {
    __auto_type _mv_318 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/equivalent-class.ttl"));
    if (!_mv_318.has_value) {
        printf("%s\n", "  ERROR: failed to parse equivalent-class.ttl");
        return 0;
    } else if (_mv_318.has_value) {
        __auto_type result = _mv_318.value;
        __auto_type _mv_319 = result;
        switch (_mv_319.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_319.data.reason_success;
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
                __auto_type _ = _mv_319.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_disjoint_violation_file(slop_arena* arena) {
    __auto_type _mv_320 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/disjoint-violation.ttl"));
    if (!_mv_320.has_value) {
        printf("%s\n", "  ERROR: failed to parse disjoint-violation.ttl");
        return 0;
    } else if (_mv_320.has_value) {
        __auto_type result = _mv_320.value;
        __auto_type _mv_321 = result;
        switch (_mv_321.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_321.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_321.data.reason_inconsistent;
                return 1;
            }
        }
    }
}

uint8_t test_cli_test_sameas_differentfrom_file(slop_arena* arena) {
    __auto_type _mv_322 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-differentfrom.ttl"));
    if (!_mv_322.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-differentfrom.ttl");
        return 0;
    } else if (_mv_322.has_value) {
        __auto_type result = _mv_322.value;
        __auto_type _mv_323 = result;
        switch (_mv_323.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_323.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_323.data.reason_inconsistent;
                return 1;
            }
        }
    }
}

uint8_t test_cli_test_sameas_chain_file(slop_arena* arena) {
    __auto_type _mv_324 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-chain.ttl"));
    if (!_mv_324.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-chain.ttl");
        return 0;
    } else if (_mv_324.has_value) {
        __auto_type result = _mv_324.value;
        __auto_type _mv_325 = result;
        switch (_mv_325.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_325.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type charlie = rdf_make_iri(arena, SLOP_STR("http://example.org/charlie"));
                    return test_cli_has_same_as(arena, s.graph, alice, charlie);
                }
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_325.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_empty_file(slop_arena* arena) {
    __auto_type _mv_326 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/empty.ttl"));
    if (!_mv_326.has_value) {
        printf("%s\n", "  ERROR: failed to parse empty.ttl");
        return 0;
    } else if (_mv_326.has_value) {
        __auto_type result = _mv_326.value;
        __auto_type _mv_327 = result;
        switch (_mv_327.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_327.data.reason_success;
                return (s.inferred_count <= 36);
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_327.data.reason_inconsistent;
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
        __auto_type _mv_328 = ttl_parse_ttl_file(arena, SLOP_STR("fixtures/bfo-core.ttl"));
        if (!_mv_328.is_ok) {
            __auto_type _ = _mv_328.data.err;
            printf("%s\n", "  ERROR: failed to parse bfo-core.ttl");
            return 0;
        } else if (_mv_328.is_ok) {
            __auto_type g = _mv_328.data.ok;
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
                    __auto_type _mv_329 = growl_reason(arena, ig);
                    switch (_mv_329.tag) {
                        case types_ReasonerResult_reason_success:
                        {
                            __auto_type s = _mv_329.data.reason_success;
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
                            __auto_type report = _mv_329.data.reason_inconsistent;
                            printf("%s", "  ERROR: BFO inconsistent: ");
                            printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

uint8_t test_cli_test_invalid_literal_file(slop_arena* arena) {
    __auto_type _mv_330 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/invalid-literal.ttl"));
    if (!_mv_330.has_value) {
        printf("%s\n", "  ERROR: failed to parse invalid-literal.ttl");
        return 0;
    } else if (_mv_330.has_value) {
        __auto_type result = _mv_330.value;
        __auto_type _mv_331 = result;
        switch (_mv_331.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_331.data.reason_success;
                printf("%s\n", "  ERROR: should have detected invalid literal");
                return 0;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_331.data.reason_inconsistent;
                return 1;
            }
        }
    }
}

uint8_t test_cli_test_valid_literals_file(slop_arena* arena) {
    __auto_type _mv_332 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/valid-literals.ttl"));
    if (!_mv_332.has_value) {
        printf("%s\n", "  ERROR: failed to parse valid-literals.ttl");
        return 0;
    } else if (_mv_332.has_value) {
        __auto_type result = _mv_332.value;
        __auto_type _mv_333 = result;
        switch (_mv_333.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_333.data.reason_success;
                return 1;
            }
            case types_ReasonerResult_reason_inconsistent:
            {
                __auto_type report = _mv_333.data.reason_inconsistent;
                printf("%s", "  ERROR: unexpected inconsistency: ");
                printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_emit_roundtrip(slop_arena* arena) {
    __auto_type _mv_334 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_334.has_value) {
        printf("%s\n", "  ERROR: failed to parse for roundtrip");
        return 0;
    } else if (_mv_334.has_value) {
        __auto_type result = _mv_334.value;
        __auto_type _mv_335 = result;
        switch (_mv_335.tag) {
            case types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_335.data.reason_success;
                {
                    __auto_type out_graph = test_cli_indexed_to_graph(arena, s.graph);
                    slop_option_string no_base = (slop_option_string){.has_value = false};
                    __auto_type config = ((serialize_ttl_SerializeConfig){.prefixes = ttl_make_prefix_map(arena), .base_iri = no_base, .indent_width = 2});
                    __auto_type emit_path = SLOP_STR("fixtures/roundtrip-out.ttl");
                    __auto_type _mv_336 = serialize_ttl_serialize_ttl_stream(arena, out_graph, config, emit_path);
                    if (!_mv_336.is_ok) {
                        __auto_type _ = _mv_336.data.err;
                        printf("%s\n", "  ERROR: failed to write roundtrip file");
                        return 0;
                    } else if (_mv_336.is_ok) {
                        __auto_type _ = _mv_336.data.ok;
                        __auto_type _mv_337 = ttl_parse_ttl_file(arena, emit_path);
                        if (!_mv_337.is_ok) {
                            __auto_type _ = _mv_337.data.err;
                            printf("%s\n", "  ERROR: failed to re-parse emitted file");
                            return 0;
                        } else if (_mv_337.is_ok) {
                            __auto_type g2 = _mv_337.data.ok;
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
                __auto_type _ = _mv_335.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency in roundtrip");
                return 0;
            }
        }
    }
}

uint8_t test_cli_test_missing_file(slop_arena* arena) {
    __auto_type _mv_338 = test_cli_parse_and_reason(arena, SLOP_STR("fixtures/does-not-exist.ttl"));
    if (!_mv_338.has_value) {
        return 1;
    } else if (_mv_338.has_value) {
        __auto_type _ = _mv_338.value;
        printf("%s\n", "  ERROR: should have failed on missing file");
        return 0;
    }
}

int main(void) {
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

