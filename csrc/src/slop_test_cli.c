#include "../runtime/slop_runtime.h"
#include "slop_test_cli.h"

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

slop_rdf_index_IndexedGraph growl_cli_test_test_cli_graph_to_indexed(slop_arena* arena, slop_rdf_rdf_Graph g) {
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

slop_rdf_rdf_Graph growl_cli_test_test_cli_indexed_to_graph(slop_arena* arena, slop_rdf_index_IndexedGraph ig) {
    return ((slop_rdf_rdf_Graph){.triples = ig.triples, .size = ((slop_rdf_rdf_GraphSize)(rdf_indexed_graph_size(ig)))});
}

uint8_t growl_cli_test_test_cli_has_type(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term individual, slop_rdf_rdf_Term class) {
    {
        __auto_type type_pred = rdf_make_iri(arena, slop_rdf_vocab_RDF_TYPE);
        __auto_type matches = rdf_indexed_graph_match(arena, g, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = individual}, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = class});
        return (((int64_t)((matches).len)) > 0);
    }
}

uint8_t growl_cli_test_test_cli_has_same_as(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term a, slop_rdf_rdf_Term b) {
    {
        __auto_type same_pred = rdf_make_iri(arena, slop_rdf_vocab_OWL_SAME_AS);
        __auto_type fwd = rdf_indexed_graph_match(arena, g, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = a}, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = same_pred}, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = b});
        __auto_type bwd = rdf_indexed_graph_match(arena, g, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = b}, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = same_pred}, (slop_option_slop_rdf_rdf_Term){.has_value = 1, .value = a});
        return ((((int64_t)((fwd).len)) > 0) || (((int64_t)((bwd).len)) > 0));
    }
}

void growl_cli_test_test_cli_print_result(slop_string name, uint8_t passed) {
    if (passed) {
        printf("%s", "[PASS] ");
        (void)(({ slop_string _ps_497 = (name); printf("%.*s\n", (int)_ps_497.len, _ps_497.data); }));
    } else {
        printf("%s", "[FAIL] ");
        (void)(({ slop_string _ps_498 = (name); printf("%.*s\n", (int)_ps_498.len, _ps_498.data); }));
    }
}

slop_option_growl_types_ReasonerResult growl_cli_test_test_cli_parse_and_reason(slop_arena* arena, slop_string path) {
    __auto_type _mv_499 = slop_rdf_ttl_parse_ttl_file(arena, path);
    if (!_mv_499.is_ok) {
        __auto_type _ = _mv_499.data.err;
        return (slop_option_growl_types_ReasonerResult){.has_value = false};
    } else if (_mv_499.is_ok) {
        __auto_type g = _mv_499.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            return (slop_option_growl_types_ReasonerResult){.has_value = 1, .value = growl_reason(arena, ig)};
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_subclass_chain_file(slop_arena* arena) {
    __auto_type _mv_500 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_500.has_value) {
        printf("%s\n", "  ERROR: failed to parse subclass-chain.ttl");
        return 0;
    } else if (_mv_500.has_value) {
        __auto_type result = _mv_500.value;
        __auto_type _mv_501 = result;
        switch (_mv_501.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_501.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type person = rdf_make_iri(arena, SLOP_STR("http://example.org/Person"));
                    __auto_type agent = rdf_make_iri(arena, SLOP_STR("http://example.org/Agent"));
                    __auto_type g = s.graph;
                    {
                        __auto_type has_person = growl_cli_test_test_cli_has_type(arena, g, alice, person);
                        __auto_type has_agent = growl_cli_test_test_cli_has_type(arena, g, alice, agent);
                        __auto_type did_infer = (s.inferred_count > 0);
                        return (has_person && (has_agent && did_infer));
                    }
                }
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_501.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_equivalent_class_file(slop_arena* arena) {
    __auto_type _mv_502 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/equivalent-class.ttl"));
    if (!_mv_502.has_value) {
        printf("%s\n", "  ERROR: failed to parse equivalent-class.ttl");
        return 0;
    } else if (_mv_502.has_value) {
        __auto_type result = _mv_502.value;
        __auto_type _mv_503 = result;
        switch (_mv_503.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_503.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type bob = rdf_make_iri(arena, SLOP_STR("http://example.org/bob"));
                    __auto_type human = rdf_make_iri(arena, SLOP_STR("http://example.org/Human"));
                    __auto_type person = rdf_make_iri(arena, SLOP_STR("http://example.org/Person"));
                    __auto_type g = s.graph;
                    return (growl_cli_test_test_cli_has_type(arena, g, alice, person) && growl_cli_test_test_cli_has_type(arena, g, bob, human));
                }
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_503.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_disjoint_violation_file(slop_arena* arena) {
    __auto_type _mv_504 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/disjoint-violation.ttl"));
    if (!_mv_504.has_value) {
        printf("%s\n", "  ERROR: failed to parse disjoint-violation.ttl");
        return 0;
    } else if (_mv_504.has_value) {
        __auto_type result = _mv_504.value;
        __auto_type _mv_505 = result;
        switch (_mv_505.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_505.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_505.data.reason_inconsistent;
                return 1;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_sameas_differentfrom_file(slop_arena* arena) {
    __auto_type _mv_506 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-differentfrom.ttl"));
    if (!_mv_506.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-differentfrom.ttl");
        return 0;
    } else if (_mv_506.has_value) {
        __auto_type result = _mv_506.value;
        __auto_type _mv_507 = result;
        switch (_mv_507.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_507.data.reason_success;
                printf("%s\n", "  ERROR: should have detected inconsistency");
                return 0;
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_507.data.reason_inconsistent;
                return 1;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_sameas_chain_file(slop_arena* arena) {
    __auto_type _mv_508 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/sameas-chain.ttl"));
    if (!_mv_508.has_value) {
        printf("%s\n", "  ERROR: failed to parse sameas-chain.ttl");
        return 0;
    } else if (_mv_508.has_value) {
        __auto_type result = _mv_508.value;
        __auto_type _mv_509 = result;
        switch (_mv_509.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_509.data.reason_success;
                {
                    __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                    __auto_type charlie = rdf_make_iri(arena, SLOP_STR("http://example.org/charlie"));
                    return growl_cli_test_test_cli_has_same_as(arena, s.graph, alice, charlie);
                }
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_509.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_empty_file(slop_arena* arena) {
    __auto_type _mv_510 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/empty.ttl"));
    if (!_mv_510.has_value) {
        printf("%s\n", "  ERROR: failed to parse empty.ttl");
        return 0;
    } else if (_mv_510.has_value) {
        __auto_type result = _mv_510.value;
        __auto_type _mv_511 = result;
        switch (_mv_511.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_511.data.reason_success;
                return (s.inferred_count <= 36);
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_511.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency on empty graph");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_bfo_consistent(slop_arena* arena) {
    {
        __auto_type start_time = slop_now_ms();
        printf("%s\n", "  BFO: parsing...");
        __auto_type _mv_512 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/bfo-core.ttl"));
        if (!_mv_512.is_ok) {
            __auto_type _ = _mv_512.data.err;
            printf("%s\n", "  ERROR: failed to parse bfo-core.ttl");
            return 0;
        } else if (_mv_512.is_ok) {
            __auto_type g = _mv_512.data.ok;
            printf("%s", "  BFO: parsed ");
            ({ slop_string _ps_513 = (int_to_string(arena, rdf_graph_size(g))); printf("%.*s", (int)_ps_513.len, _ps_513.data); });
            printf("%s\n", " triples, indexing...");
            {
                __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
                printf("%s", "  BFO: indexed ");
                ({ slop_string _ps_514 = (int_to_string(arena, rdf_indexed_graph_size(ig))); printf("%.*s", (int)_ps_514.len, _ps_514.data); });
                printf("%s\n", " triples, reasoning...");
                {
                    __auto_type reason_start = slop_now_ms();
                    __auto_type _mv_515 = growl_reason(arena, ig);
                    switch (_mv_515.tag) {
                        case growl_types_ReasonerResult_reason_success:
                        {
                            __auto_type s = _mv_515.data.reason_success;
                            {
                                __auto_type end_time = slop_now_ms();
                                printf("%s", "  BFO: ");
                                ({ slop_string _ps_516 = (int_to_string(arena, s.inferred_count)); printf("%.*s", (int)_ps_516.len, _ps_516.data); });
                                printf("%s", " inferred, ");
                                ({ slop_string _ps_517 = (int_to_string(arena, s.iterations)); printf("%.*s", (int)_ps_517.len, _ps_517.data); });
                                printf("%s", " iterations, ");
                                ({ slop_string _ps_518 = (int_to_string(arena, (end_time - reason_start))); printf("%.*s", (int)_ps_518.len, _ps_518.data); });
                                printf("%s\n", "ms reasoning");
                                printf("%s", "  BFO: total ");
                                ({ slop_string _ps_519 = (int_to_string(arena, (end_time - start_time))); printf("%.*s", (int)_ps_519.len, _ps_519.data); });
                                printf("%s\n", "ms");
                                return 1;
                            }
                        }
                        case growl_types_ReasonerResult_reason_inconsistent:
                        {
                            __auto_type reports = _mv_515.data.reason_inconsistent;
                            printf("%s", "  ERROR: BFO inconsistent: ");
                            __auto_type _mv_520 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_520.has_value) {
                                __auto_type report = _mv_520.value;
                                ({ slop_string _ps_521 = (report.reason); printf("%.*s\n", (int)_ps_521.len, _ps_521.data); });
                            } else if (!_mv_520.has_value) {
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

uint8_t growl_cli_test_test_cli_test_invalid_literal_file(slop_arena* arena) {
    __auto_type _mv_522 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/invalid-literal.ttl"));
    if (!_mv_522.has_value) {
        printf("%s\n", "  ERROR: failed to parse invalid-literal.ttl");
        return 0;
    } else if (_mv_522.has_value) {
        __auto_type result = _mv_522.value;
        __auto_type _mv_523 = result;
        switch (_mv_523.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_523.data.reason_success;
                printf("%s\n", "  ERROR: should have detected invalid literal");
                return 0;
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_523.data.reason_inconsistent;
                return 1;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_valid_literals_file(slop_arena* arena) {
    __auto_type _mv_524 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/valid-literals.ttl"));
    if (!_mv_524.has_value) {
        printf("%s\n", "  ERROR: failed to parse valid-literals.ttl");
        return 0;
    } else if (_mv_524.has_value) {
        __auto_type result = _mv_524.value;
        __auto_type _mv_525 = result;
        switch (_mv_525.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_525.data.reason_success;
                return 1;
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type reports = _mv_525.data.reason_inconsistent;
                printf("%s", "  ERROR: unexpected inconsistency: ");
                __auto_type _mv_526 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                if (_mv_526.has_value) {
                    __auto_type report = _mv_526.value;
                    ({ slop_string _ps_527 = (report.reason); printf("%.*s\n", (int)_ps_527.len, _ps_527.data); });
                } else if (!_mv_526.has_value) {
                    printf("%s\n", "(no details)");
                }
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_emit_roundtrip(slop_arena* arena) {
    __auto_type _mv_528 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_528.has_value) {
        printf("%s\n", "  ERROR: failed to parse for roundtrip");
        return 0;
    } else if (_mv_528.has_value) {
        __auto_type result = _mv_528.value;
        __auto_type _mv_529 = result;
        switch (_mv_529.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type s = _mv_529.data.reason_success;
                {
                    __auto_type out_graph = growl_cli_test_test_cli_indexed_to_graph(arena, s.graph);
                    slop_option_string no_base = (slop_option_string){.has_value = false};
                    __auto_type config = ((slop_rdf_serialize_ttl_SerializeConfig){.prefixes = slop_rdf_ttl_make_prefix_map(arena), .base_iri = no_base, .indent_width = 2});
                    __auto_type emit_path = SLOP_STR("fixtures/roundtrip-out.ttl");
                    __auto_type _mv_530 = slop_rdf_serialize_ttl_serialize_ttl_stream(arena, out_graph, config, emit_path);
                    if (!_mv_530.is_ok) {
                        __auto_type _ = _mv_530.data.err;
                        printf("%s\n", "  ERROR: failed to write roundtrip file");
                        return 0;
                    } else if (_mv_530.is_ok) {
                        __auto_type _ = _mv_530.data.ok;
                        __auto_type _mv_531 = slop_rdf_ttl_parse_ttl_file(arena, emit_path);
                        if (!_mv_531.is_ok) {
                            __auto_type _ = _mv_531.data.err;
                            printf("%s\n", "  ERROR: failed to re-parse emitted file");
                            return 0;
                        } else if (_mv_531.is_ok) {
                            __auto_type g2 = _mv_531.data.ok;
                            {
                                __auto_type original_size = rdf_indexed_graph_size(s.graph);
                                __auto_type reparsed_size = rdf_graph_size(g2);
                                printf("%s", "  Roundtrip: emitted ");
                                ({ slop_string _ps_532 = (int_to_string(arena, original_size)); printf("%.*s", (int)_ps_532.len, _ps_532.data); });
                                printf("%s", " triples, re-parsed ");
                                ({ slop_string _ps_533 = (int_to_string(arena, reparsed_size)); printf("%.*s\n", (int)_ps_533.len, _ps_533.data); });
                                return (reparsed_size >= 3);
                            }
                        }
                        SLOP_UNREACHABLE();
                    }
                    SLOP_UNREACHABLE();
                }
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_529.data.reason_inconsistent;
                printf("%s\n", "  ERROR: unexpected inconsistency in roundtrip");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_missing_file(slop_arena* arena) {
    __auto_type _mv_534 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/does-not-exist.ttl"));
    if (!_mv_534.has_value) {
        return 1;
    } else if (_mv_534.has_value) {
        __auto_type _ = _mv_534.value;
        printf("%s\n", "  ERROR: should have failed on missing file");
        return 0;
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_validate_unsat(slop_arena* arena) {
    __auto_type _mv_535 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-unsat.ttl"));
    if (!_mv_535.is_ok) {
        __auto_type _ = _mv_535.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-unsat.ttl");
        return 0;
    } else if (_mv_535.is_ok) {
        __auto_type g = _mv_535.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_536 = growl_reason_with_config(arena, ig, config);
            switch (_mv_536.tag) {
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_536.data.reason_inconsistent;
                    return 1;
                }
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_536.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable class");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_validate_clean(slop_arena* arena) {
    __auto_type _mv_537 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-clean.ttl"));
    if (!_mv_537.is_ok) {
        __auto_type _ = _mv_537.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-clean.ttl");
        return 0;
    } else if (_mv_537.is_ok) {
        __auto_type g = _mv_537.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_538 = growl_reason_with_config(arena, ig, config);
            switch (_mv_538.tag) {
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_538.data.reason_success;
                    return 1;
                }
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_538.data.reason_inconsistent;
                    printf("%s", "  ERROR: unexpected inconsistency: ");
                    __auto_type _mv_539 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_539.has_value) {
                        __auto_type report = _mv_539.value;
                        ({ slop_string _ps_540 = (report.reason); printf("%.*s\n", (int)_ps_540.len, _ps_540.data); });
                    } else if (!_mv_539.has_value) {
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

uint8_t growl_cli_test_test_cli_test_no_validate_unsat_passes(slop_arena* arena) {
    __auto_type _mv_541 = growl_cli_test_test_cli_parse_and_reason(arena, SLOP_STR("fixtures/validate-unsat.ttl"));
    if (!_mv_541.has_value) {
        printf("%s\n", "  ERROR: failed to parse validate-unsat.ttl");
        return 0;
    } else if (_mv_541.has_value) {
        __auto_type result = _mv_541.value;
        __auto_type _mv_542 = result;
        switch (_mv_542.tag) {
            case growl_types_ReasonerResult_reason_success:
            {
                __auto_type _ = _mv_542.data.reason_success;
                return 1;
            }
            case growl_types_ReasonerResult_reason_inconsistent:
            {
                __auto_type _ = _mv_542.data.reason_inconsistent;
                printf("%s\n", "  ERROR: should pass without --validate (TBox only)");
                return 0;
            }
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_validate_unsat_prop(slop_arena* arena) {
    __auto_type _mv_543 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-unsat-prop.ttl"));
    if (!_mv_543.is_ok) {
        __auto_type _ = _mv_543.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-unsat-prop.ttl");
        return 0;
    } else if (_mv_543.is_ok) {
        __auto_type g = _mv_543.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_544 = growl_reason_with_config(arena, ig, config);
            switch (_mv_544.tag) {
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_544.data.reason_inconsistent;
                    return 1;
                }
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_544.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable property");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_validate_domain_reports_class(slop_arena* arena) {
    __auto_type _mv_545 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-domain-unsat.ttl"));
    if (!_mv_545.is_ok) {
        __auto_type _ = _mv_545.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-domain-unsat.ttl");
        return 0;
    } else if (_mv_545.is_ok) {
        __auto_type g = _mv_545.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_546 = growl_reason_with_config(arena, ig, config);
            switch (_mv_546.tag) {
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_546.data.reason_inconsistent;
                    __auto_type _mv_547 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_547.has_value) {
                        __auto_type report = _mv_547.value;
                        return std_strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                    } else if (!_mv_547.has_value) {
                        return 0;
                    }
                    SLOP_UNREACHABLE();
                }
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_546.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_validate_ns_scoping(slop_arena* arena) {
    __auto_type _mv_548 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-domain.ttl"));
    if (!_mv_548.is_ok) {
        __auto_type _ = _mv_548.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-domain.ttl");
        return 0;
    } else if (_mv_548.is_ok) {
        __auto_type g = _mv_548.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/"), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_549 = growl_reason_with_config(arena, ig, config);
            switch (_mv_549.tag) {
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_549.data.reason_inconsistent;
                    __auto_type _mv_550 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_550.has_value) {
                        __auto_type report = _mv_550.value;
                        return std_strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                    } else if (!_mv_550.has_value) {
                        return 0;
                    }
                    SLOP_UNREACHABLE();
                }
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_549.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable ex:Bad");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_validate_ns_filters_tlo(slop_arena* arena) {
    __auto_type _mv_551 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-tlo.ttl"));
    if (!_mv_551.is_ok) {
        __auto_type _ = _mv_551.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-tlo.ttl");
        return 0;
    } else if (_mv_551.is_ok) {
        __auto_type g = _mv_551.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/"), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_552 = growl_reason_with_config(arena, ig, config);
            switch (_mv_552.tag) {
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_552.data.reason_success;
                    return 1;
                }
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_552.data.reason_inconsistent;
                    printf("%s", "  ERROR: unexpected inconsistency: ");
                    __auto_type _mv_553 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_553.has_value) {
                        __auto_type report = _mv_553.value;
                        ({ slop_string _ps_554 = (report.reason); printf("%.*s\n", (int)_ps_554.len, _ps_554.data); });
                    } else if (!_mv_553.has_value) {
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

uint8_t growl_cli_test_test_cli_test_rdf_star_blank_remapping(slop_arena* arena) {
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

uint8_t growl_cli_test_test_cli_test_background_merge(slop_arena* arena) {
    __auto_type _mv_555 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-bg-tlo.ttl"));
    if (!_mv_555.is_ok) {
        __auto_type _ = _mv_555.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-bg-tlo.ttl");
        return 0;
    } else if (_mv_555.is_ok) {
        __auto_type bg_graph = _mv_555.data.ok;
        __auto_type _mv_556 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-domain-only.ttl"));
        if (!_mv_556.is_ok) {
            __auto_type _ = _mv_556.data.err;
            printf("%s\n", "  ERROR: failed to parse validate-domain-only.ttl");
            return 0;
        } else if (_mv_556.is_ok) {
            __auto_type domain_graph = _mv_556.data.ok;
            {
                __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, domain_graph);
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
                    __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR("http://example.org/"), .cancel_ptr = 0, .max_triples = 0});
                    __auto_type _mv_557 = growl_reason_with_config(arena, ig, config);
                    switch (_mv_557.tag) {
                        case growl_types_ReasonerResult_reason_inconsistent:
                        {
                            __auto_type reports = _mv_557.data.reason_inconsistent;
                            __auto_type _mv_558 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_558.has_value) {
                                __auto_type report = _mv_558.value;
                                return std_strlib_starts_with(report.reason, SLOP_STR("Unsatisfiable class:"));
                            } else if (!_mv_558.has_value) {
                                return 0;
                            }
                            SLOP_UNREACHABLE();
                        }
                        case growl_types_ReasonerResult_reason_success:
                        {
                            __auto_type _ = _mv_557.data.reason_success;
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

uint8_t growl_cli_test_test_cli_test_validate_multiple_unsat(slop_arena* arena) {
    __auto_type _mv_559 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/validate-multi-unsat.ttl"));
    if (!_mv_559.is_ok) {
        __auto_type _ = _mv_559.data.err;
        printf("%s\n", "  ERROR: failed to parse validate-multi-unsat.ttl");
        return 0;
    } else if (_mv_559.is_ok) {
        __auto_type g = _mv_559.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 0, .validate = 1, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_560 = growl_reason_with_config(arena, ig, config);
            switch (_mv_560.tag) {
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type reports = _mv_560.data.reason_inconsistent;
                    {
                        __auto_type count = ((int64_t)((reports).len));
                        if (count == 2) {
                            {
                                uint8_t all_class = 1;
                                {
                                    __auto_type _coll = reports;
                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                        __auto_type r = _coll.data[_i];
                                        if (!(std_strlib_starts_with(r.reason, SLOP_STR("Unsatisfiable class:")))) {
                                            printf("%s", "  ERROR: unexpected report: ");
                                            ({ slop_string _ps_561 = (r.reason); printf("%.*s\n", (int)_ps_561.len, _ps_561.data); });
                                            all_class = 0;
                                        }
                                    }
                                }
                                return all_class;
                            }
                        } else {
                            printf("%s", "  ERROR: expected 2 reports, got ");
                            ({ slop_string _ps_562 = (int_to_string(arena, count)); printf("%.*s\n", (int)_ps_562.len, _ps_562.data); });
                            {
                                __auto_type _coll = reports;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type r = _coll.data[_i];
                                    printf("%s", "    ");
                                    ({ slop_string _ps_563 = (r.reason); printf("%.*s\n", (int)_ps_563.len, _ps_563.data); });
                                }
                            }
                            return 0;
                        }
                    }
                }
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_560.data.reason_success;
                    printf("%s\n", "  ERROR: should have detected unsatisfiable classes");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_enrich_basic(slop_arena* arena) {
    __auto_type _mv_564 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/subclass-chain.ttl"));
    if (!_mv_564.is_ok) {
        __auto_type _ = _mv_564.data.err;
        printf("%s\n", "  ERROR: failed to parse subclass-chain.ttl");
        return 0;
    } else if (_mv_564.is_ok) {
        __auto_type g = _mv_564.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_565 = growl_reason_with_config(arena, ig, config);
            switch (_mv_565.tag) {
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type s = _mv_565.data.reason_success;
                    {
                        __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                        __auto_type person = rdf_make_iri(arena, SLOP_STR("http://example.org/Person"));
                        __auto_type agent = rdf_make_iri(arena, SLOP_STR("http://example.org/Agent"));
                        __auto_type g = s.graph;
                        return (growl_cli_test_test_cli_has_type(arena, g, alice, person) && growl_cli_test_test_cli_has_type(arena, g, alice, agent));
                    }
                }
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_565.data.reason_inconsistent;
                    printf("%s\n", "  ERROR: unexpected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_enrich_skips_eq(slop_arena* arena) {
    __auto_type _mv_566 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/sameas-chain.ttl"));
    if (!_mv_566.is_ok) {
        __auto_type _ = _mv_566.data.err;
        printf("%s\n", "  ERROR: failed to parse sameas-chain.ttl");
        return 0;
    } else if (_mv_566.is_ok) {
        __auto_type g = _mv_566.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_567 = growl_reason_with_config(arena, ig, config);
            switch (_mv_567.tag) {
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type s = _mv_567.data.reason_success;
                    {
                        __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                        __auto_type charlie = rdf_make_iri(arena, SLOP_STR("http://example.org/charlie"));
                        return !(growl_cli_test_test_cli_has_same_as(arena, s.graph, alice, charlie));
                    }
                }
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_567.data.reason_inconsistent;
                    printf("%s\n", "  ERROR: unexpected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_enrich_skips_cls(slop_arena* arena) {
    __auto_type _mv_568 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/enrich-cls-test.ttl"));
    if (!_mv_568.is_ok) {
        __auto_type _ = _mv_568.data.err;
        printf("%s\n", "  ERROR: failed to parse enrich-cls-test.ttl");
        return 0;
    } else if (_mv_568.is_ok) {
        __auto_type g = _mv_568.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_569 = growl_reason_with_config(arena, ig, config);
            switch (_mv_569.tag) {
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type s = _mv_569.data.reason_success;
                    {
                        __auto_type alice = rdf_make_iri(arena, SLOP_STR("http://example.org/alice"));
                        __auto_type p = rdf_make_iri(arena, SLOP_STR("http://example.org/p"));
                        __auto_type v = rdf_make_iri(arena, SLOP_STR("http://example.org/v"));
                        __auto_type expected = rdf_make_triple(arena, alice, p, v);
                        return !(rdf_indexed_graph_contains(s.graph, expected));
                    }
                }
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_569.data.reason_inconsistent;
                    printf("%s\n", "  ERROR: unexpected inconsistency");
                    return 0;
                }
            }
            SLOP_UNREACHABLE();
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t growl_cli_test_test_cli_test_enrich_checks_consistency(slop_arena* arena) {
    __auto_type _mv_570 = slop_rdf_ttl_parse_ttl_file(arena, SLOP_STR("fixtures/disjoint-violation.ttl"));
    if (!_mv_570.is_ok) {
        __auto_type _ = _mv_570.data.err;
        printf("%s\n", "  ERROR: failed to parse disjoint-violation.ttl");
        return 0;
    } else if (_mv_570.is_ok) {
        __auto_type g = _mv_570.data.ok;
        {
            __auto_type ig = growl_cli_test_test_cli_graph_to_indexed(arena, g);
            __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = 0, .fast = 0, .complete = 0, .enrich = 1, .validate = 0, .validate_ns = SLOP_STR(""), .cancel_ptr = 0, .max_triples = 0});
            __auto_type _mv_571 = growl_reason_with_config(arena, ig, config);
            switch (_mv_571.tag) {
                case growl_types_ReasonerResult_reason_inconsistent:
                {
                    __auto_type _ = _mv_571.data.reason_inconsistent;
                    return 1;
                }
                case growl_types_ReasonerResult_reason_success:
                {
                    __auto_type _ = _mv_571.data.reason_success;
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
    (void)argc; (void)argv;
    {
        #ifdef SLOP_DEBUG
        SLOP_PRE((536870912) > 0, "with-arena size must be positive");
        #endif
        slop_arena _arena_10 = slop_arena_new(536870912);
        #ifdef SLOP_DEBUG
        SLOP_PRE(_arena_10.base != NULL, "arena allocation failed");
        #endif
        slop_arena* arena = &_arena_10;
        {
            int64_t passed = 0;
            int64_t failed = 0;
            printf("%s\n", "========================================");
            printf("%s\n", "Growl CLI Integration Tests");
            printf("%s\n", "========================================");
            printf("%s\n", "");
            {
                __auto_type r = growl_cli_test_test_cli_test_bfo_consistent(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("BFO ontology consistent"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_subclass_chain_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("subclass chain from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_equivalent_class_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("equivalent class from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_sameas_chain_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("sameAs transitivity from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_empty_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("empty graph from TTL"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_disjoint_violation_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("disjoint violation detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_sameas_differentfrom_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("sameAs/differentFrom violation detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_invalid_literal_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("dt-not-type: invalid literal detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_valid_literals_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("dt-not-type: valid literals pass"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_emit_roundtrip(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("emit roundtrip (serialize + re-parse)"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_validate_unsat(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate: unsatisfiable class detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_validate_clean(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate: clean TBox passes"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_no_validate_unsat_passes(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate: unsat TBox passes without --validate"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_validate_unsat_prop(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate: unsatisfiable property detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_validate_domain_reports_class(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate: domain-mediated reports class"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_validate_ns_scoping(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate-ns: scoped to domain namespace"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_validate_ns_filters_tlo(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate-ns: TLO entities filtered out"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_rdf_star_blank_remapping(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("background merge: remaps RDF-star blank nodes"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_background_merge(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("background merge: detects unsatisfiable class"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_validate_multiple_unsat(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("validate: multiple unsatisfiable classes"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_enrich_basic(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("enrich: subclass types inferred"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_enrich_skips_eq(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("enrich: sameAs transitivity skipped"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_enrich_skips_cls(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("enrich: cls-hv1 skipped"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_enrich_checks_consistency(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("enrich: disjoint violation still detected"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            {
                __auto_type r = growl_cli_test_test_cli_test_missing_file(arena);
                growl_cli_test_test_cli_print_result(SLOP_STR("missing file handled gracefully"), r);
                if (r) {
                    passed = (passed + 1);
                } else {
                    failed = (failed + 1);
                }
            }
            printf("%s\n", "");
            printf("%s\n", "========================================");
            printf("%s", "Passed: ");
            (void)(({ slop_string _ps_572 = (int_to_string(arena, passed)); printf("%.*s\n", (int)_ps_572.len, _ps_572.data); }));
            printf("%s", "Failed: ");
            (void)(({ slop_string _ps_573 = (int_to_string(arena, failed)); printf("%.*s\n", (int)_ps_573.len, _ps_573.data); }));
            printf("%s\n", "========================================");
            if (failed == 0) {
                {
                    int _wa_ret = 0;
                    slop_arena_free(&_arena_10);
                    return _wa_ret;
                }
            } else {
                {
                    int _wa_ret = 1;
                    slop_arena_free(&_arena_10);
                    return _wa_ret;
                }
            }
        }
        slop_arena_free(arena);
    }
}

