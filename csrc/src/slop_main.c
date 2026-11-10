#include "../runtime/slop_runtime.h"
#include "slop_main.h"

void growl_cli_main_print_elapsed(slop_arena* arena, int64_t elapsed);
slop_string growl_cli_main_argv_to_string(uint8_t** argv, int64_t index);
growl_cli_main_CliArgs growl_cli_main_parse_args(slop_arena* arena, int64_t argc, uint8_t** argv);
void growl_cli_main_print_usage(void);
int main(int argc, char** _c_argv);

void growl_cli_main_print_elapsed(slop_arena* arena, int64_t elapsed) {
    (void)(({ slop_string _ps_497 = (int_to_string(arena, (elapsed / 1000))); printf("%.*s", (int)_ps_497.len, _ps_497.data); }));
    printf("%s", ".");
    {
        __auto_type ms = (elapsed % 1000);
        if (ms < 100) {
            printf("%s", "0");
        }
        if (ms < 10) {
            printf("%s", "0");
        }
        (void)(({ slop_string _ps_498 = (int_to_string(arena, ms)); printf("%.*s", (int)_ps_498.len, _ps_498.data); }));
    }
    printf("%s", "s");
}

slop_string growl_cli_main_argv_to_string(uint8_t** argv, int64_t index) {
    {
        __auto_type ptr = argv[index];
        return (slop_string){.len = strlen(ptr), .data = ptr};
    }
}

growl_cli_main_CliArgs growl_cli_main_parse_args(slop_arena* arena, int64_t argc, uint8_t** argv) {
    {
        slop_option_string input = (slop_option_string){.has_value = false};
        slop_option_string emit = (slop_option_string){.has_value = false};
        slop_option_string background = (slop_option_string){.has_value = false};
        slop_option_string validate_ns_opt = (slop_option_string){.has_value = false};
        uint8_t quiet = 0;
        uint8_t fast = 0;
        uint8_t complete = 0;
        uint8_t enrich = 0;
        uint8_t validate = 0;
        uint8_t help = 0;
        uint8_t version = 0;
        int64_t max_tri = 0;
        int64_t i = 1;
        while (i < argc) {
            {
                __auto_type arg = growl_cli_main_argv_to_string(argv, i);
                if (string_eq(arg, SLOP_STR("--help")) || string_eq(arg, SLOP_STR("-h"))) {
                    help = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--version")) || string_eq(arg, SLOP_STR("-V"))) {
                    version = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--quiet")) || string_eq(arg, SLOP_STR("-q"))) {
                    quiet = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--fast")) || string_eq(arg, SLOP_STR("-f"))) {
                    fast = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--complete")) || string_eq(arg, SLOP_STR("-c"))) {
                    complete = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--enrich")) || string_eq(arg, SLOP_STR("-e"))) {
                    enrich = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--validate"))) {
                    validate = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--validate-ns"))) {
                    if ((i + 1) < argc) {
                        validate_ns_opt = (slop_option_string){.has_value = 1, .value = growl_cli_main_argv_to_string(argv, (i + 1))};
                        i = (i + 2);
                    } else {
                        printf("%s\n", "Error: --validate-ns requires an IRI prefix");
                        help = 1;
                        i = (i + 1);
                    }
                } else if (string_eq(arg, SLOP_STR("--background")) || string_eq(arg, SLOP_STR("-b"))) {
                    if ((i + 1) < argc) {
                        background = (slop_option_string){.has_value = 1, .value = growl_cli_main_argv_to_string(argv, (i + 1))};
                        i = (i + 2);
                    } else {
                        printf("%s\n", "Error: --background requires a file path");
                        help = 1;
                        i = (i + 1);
                    }
                } else if (string_eq(arg, SLOP_STR("--emit")) || string_eq(arg, SLOP_STR("-o"))) {
                    if ((i + 1) < argc) {
                        emit = (slop_option_string){.has_value = 1, .value = growl_cli_main_argv_to_string(argv, (i + 1))};
                        i = (i + 2);
                    } else {
                        printf("%s\n", "Error: --emit requires a file path");
                        help = 1;
                        i = (i + 1);
                    }
                } else if (string_eq(arg, SLOP_STR("--max-triples"))) {
                    if ((i + 1) < argc) {
                        __auto_type _mv_499 = std_strlib_parse_int(growl_cli_main_argv_to_string(argv, (i + 1)));
                        if (_mv_499.is_ok) {
                            __auto_type val = _mv_499.data.ok;
                            max_tri = ((int64_t)(val));
                        } else if (!_mv_499.is_ok) {
                            __auto_type _ = _mv_499.data.err;
                            printf("%s\n", "Error: --max-triples requires a valid number");
                            help = 1;
                        }
                        i = (i + 2);
                    } else {
                        printf("%s\n", "Error: --max-triples requires a number");
                        help = 1;
                        i = (i + 1);
                    }
                } else if (1) {
                    input = (slop_option_string){.has_value = 1, .value = arg};
                    i = (i + 1);
                }
            }
        }
        return ((growl_cli_main_CliArgs){.input_file = input, .emit_file = emit, .background_file = background, .validate_ns = validate_ns_opt, .quiet = quiet, .fast = fast, .complete = complete, .enrich = enrich, .validate = validate, .show_help = help, .show_version = version, .max_triples = SLOP_RANGE(int64_t, max_tri, 1, 0, 0, 0, "(Int 0 ..) at main.slop:170:22")});
    }
}

void growl_cli_main_print_usage(void) {
    printf("%s\n", "growl - OWL 2 RL Reasoner");
    printf("%s\n", "");
    printf("%s\n", "Usage: growl [options] <file.ttl>");
    printf("%s\n", "");
    printf("%s\n", "Options:");
    printf("%s\n", "  -h, --help       Show this help message");
    printf("%s\n", "  -q, --quiet      Only print failures and inconsistencies");
    printf("%s\n", "  -o, --emit FILE  Write materialized graph to TTL file");
    printf("%s\n", "  -f, --fast       Skip schema rules and consistency checks");
    printf("%s\n", "  -c, --complete   Enable cls-thing and prp-ap for spec completeness");
    printf("%s\n", "  -e, --enrich    Property/subclass enrichment (skip sameAs, class exprs, schema)");
    printf("%s\n", "  --validate       Check TBox satisfiability via synthetic instance injection");
    printf("%s\n", "  --validate-ns NS Only validate entities with IRIs starting with NS");
    printf("%s\n", "  -b, --background FILE  Load background ontology (e.g. TLO) for reasoning context");
    printf("%s\n", "  --max-triples N  Cancel reasoning if graph exceeds N triples (0=no limit)");
    printf("%s\n", "  -V, --version    Show version information");
}

int main(int argc, char** _c_argv) {
    uint8_t** argv = (uint8_t**)_c_argv;
    (void)argc; (void)argv;
    {
        #ifdef SLOP_DEBUG
        SLOP_PRE((268435456) > 0, "with-arena size must be positive");
        #endif
        slop_arena _arena_10 = slop_arena_new(268435456);
        #ifdef SLOP_DEBUG
        SLOP_PRE(_arena_10.base != NULL, "arena allocation failed");
        #endif
        slop_arena* arena = &_arena_10;
        {
            __auto_type args = growl_cli_main_parse_args(arena, argc, argv);
            if (args.show_version) {
                printf("growl %s\n", GROWL_VERSION);
                {
                    int _wa_ret = 0;
                    slop_arena_free(&_arena_10);
                    return _wa_ret;
                }
            } else {
                __auto_type _mv_500 = args.input_file;
                if (!_mv_500.has_value) {
                    growl_cli_main_print_usage();
                    if (args.show_help) {
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
                } else if (_mv_500.has_value) {
                    __auto_type input_path = _mv_500.value;
                    if (args.show_help) {
                        growl_cli_main_print_usage();
                        {
                            int _wa_ret = 0;
                            slop_arena_free(&_arena_10);
                            return _wa_ret;
                        }
                    } else {
                        {
                            __auto_type quiet = args.quiet;
                            __auto_type parse_start = slop_now_ms();
                            __auto_type _mv_501 = slop_rdf_ttl_parse_ttl_file(arena, input_path);
                            if (!_mv_501.is_ok) {
                                __auto_type e = _mv_501.data.err;
                                printf("%s", "Error: failed to parse ");
                                ({ slop_string _ps_502 = (input_path); printf("%.*s\n", (int)_ps_502.len, _ps_502.data); });
                                __auto_type _mv_503 = e;
                                switch (_mv_503.tag) {
                                    case slop_rdf_ttl_TtlFileError_parse_error:
                                    {
                                        __auto_type pe = _mv_503.data.parse_error;
                                        printf("%s", "  at line ");
                                        ({ slop_string _ps_504 = (int_to_string(arena, pe.position.line)); printf("%.*s", (int)_ps_504.len, _ps_504.data); });
                                        printf("%s", ", column ");
                                        ({ slop_string _ps_505 = (int_to_string(arena, pe.position.column)); printf("%.*s\n", (int)_ps_505.len, _ps_505.data); });
                                        printf("%s", "  ");
                                        ({ slop_string _ps_506 = (pe.message); printf("%.*s\n", (int)_ps_506.len, _ps_506.data); });
                                        break;
                                    }
                                    case slop_rdf_ttl_TtlFileError_file_error:
                                    {
                                        __auto_type _ = _mv_503.data.file_error;
                                        printf("%s\n", "  (file error)");
                                        break;
                                    }
                                }
                                {
                                    int _wa_ret = 1;
                                    slop_arena_free(&_arena_10);
                                    return _wa_ret;
                                }
                            } else if (_mv_501.is_ok) {
                                __auto_type g = _mv_501.data.ok;
                                {
                                    __auto_type annot_set = growl_collect_annotation_properties(arena, g);
                                    __auto_type original_size = rdf_graph_size(g);
                                    __auto_type ig = growl_graph_to_indexed(arena, g, annot_set);
                                    __auto_type input_size = rdf_indexed_graph_size(ig);
                                    __auto_type filtered_count = (original_size - ((slop_rdf_rdf_GraphSize)(SLOP_RANGE(slop_rdf_rdf_GraphSize, input_size, 1, 0, 0, 0, "GraphSize (Int 0 ..) at main.slop:246:72"))));
                                    __auto_type parse_elapsed = (slop_now_ms() - parse_start);
                                    if (!(quiet)) {
                                        printf("%s", "Parsed ");
                                        ({ slop_string _ps_507 = (int_to_string(arena, input_size)); printf("%.*s", (int)_ps_507.len, _ps_507.data); });
                                        printf("%s", " triples from ");
                                        ({ slop_string _ps_508 = (input_path); printf("%.*s", (int)_ps_508.len, _ps_508.data); });
                                        if (filtered_count > 0) {
                                            printf("%s", " (filtered ");
                                            ({ slop_string _ps_509 = (int_to_string(arena, filtered_count)); printf("%.*s", (int)_ps_509.len, _ps_509.data); });
                                            printf("%s", " annotations)");
                                        }
                                        printf("%s", " (");
                                        growl_cli_main_print_elapsed(arena, parse_elapsed);
                                        printf("%s\n", ")");
                                    }
                                    {
                                        __auto_type combined_ig = ig;
                                        __auto_type _mv_510 = args.background_file;
                                        if (_mv_510.has_value) {
                                            __auto_type bg_path = _mv_510.value;
                                            __auto_type _mv_511 = slop_rdf_ttl_parse_ttl_file(arena, bg_path);
                                            if (!_mv_511.is_ok) {
                                                __auto_type _ = _mv_511.data.err;
                                                printf("%s", "Error: failed to parse background file ");
                                                ({ slop_string _ps_512 = (bg_path); printf("%.*s\n", (int)_ps_512.len, _ps_512.data); });
                                                {
                                                    int _wa_ret = 1;
                                                    slop_arena_free(&_arena_10);
                                                    return _wa_ret;
                                                }
                                            } else if (_mv_511.is_ok) {
                                                __auto_type bg_graph = _mv_511.data.ok;
                                                {
                                                    __auto_type bg_annot_set = growl_collect_annotation_properties(arena, bg_graph);
                                                    __auto_type bg_ig = growl_graph_to_indexed(arena, bg_graph, bg_annot_set);
                                                    if (!(quiet)) {
                                                        printf("%s", "Loaded ");
                                                        ({ slop_string _ps_513 = (int_to_string(arena, rdf_indexed_graph_size(bg_ig))); printf("%.*s", (int)_ps_513.len, _ps_513.data); });
                                                        printf("%s", " background triples from ");
                                                        ({ slop_string _ps_514 = (bg_path); printf("%.*s\n", (int)_ps_514.len, _ps_514.data); });
                                                    }
                                                    {
                                                        __auto_type bg_triples = bg_ig.triples;
                                                        __auto_type bg_blank_offset = (growl_max_blank_id_in_graph(ig) + 1);
                                                        {
                                                            __auto_type _coll = bg_triples;
                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                __auto_type t = _coll.data[_i];
                                                                {
                                                                    __auto_type rs = growl_remap_blank_term(arena, t.subject, bg_blank_offset);
                                                                    __auto_type rp = t.predicate;
                                                                    __auto_type ro = growl_remap_blank_term(arena, t.object, bg_blank_offset);
                                                                    __auto_type remapped = rdf_make_triple(arena, rs, rp, ro);
                                                                    combined_ig = rdf_indexed_graph_add(arena, combined_ig, remapped);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else if (!_mv_510.has_value) {
                                        }
                                        {
                                            __auto_type validate_mode = args.validate;
                                            __auto_type effective_fast = (args.fast && !(validate_mode));
                                            __auto_type ns_filter = ({ __auto_type _mv = args.validate_ns; _mv.has_value ? ({ __auto_type ns = _mv.value; ns; }) : (SLOP_STR("")); });
                                            if (args.fast && validate_mode) {
                                                printf("%s\n", "Warning: --validate overrides --fast (schema materialization required)");
                                            }
                                            if (args.enrich && args.fast) {
                                                printf("%s\n", "Warning: --enrich overrides --fast");
                                            }
                                            if (args.enrich && args.complete) {
                                                printf("%s\n", "Warning: --enrich and --complete are conflicting; --enrich skips most rules");
                                            }
                                            if (validate_mode && ({ __auto_type _mv = args.emit_file; _mv.has_value ? ({ __auto_type _ = _mv.value; 1; }) : (0); })) {
                                                printf("%s\n", "Warning: --emit is ignored in --validate mode");
                                            }
                                            if ((validate_mode) && (({ __auto_type _mv = args.background_file; _mv.has_value ? ({ __auto_type _ = _mv.value; 1; }) : (0); })) && ((string_len(ns_filter) == 0))) {
                                                printf("%s\n", "Warning: --validate with --background but no --validate-ns; all classes will be validated (slow for large TLOs)");
                                            }
                                            {
                                                __auto_type reason_start = slop_now_ms();
                                                __auto_type config = ((growl_types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = !(quiet), .fast = effective_fast, .complete = args.complete, .enrich = args.enrich, .validate = validate_mode, .validate_ns = ns_filter, .cancel_ptr = 0, .max_triples = args.max_triples});
                                                __auto_type _mv_515 = growl_reason_with_config(arena, combined_ig, config);
                                                switch (_mv_515.tag) {
                                                    case growl_types_ReasonerResult_reason_success:
                                                    {
                                                        __auto_type s = _mv_515.data.reason_success;
                                                        {
                                                            __auto_type inferred = s.inferred_count;
                                                            __auto_type iters = s.iterations;
                                                            __auto_type reason_elapsed = (slop_now_ms() - reason_start);
                                                            if (validate_mode) {
                                                                printf("%s\n", "[PASS] Validation passed — all classes are satisfiable");
                                                                {
                                                                    int _wa_ret = 0;
                                                                    slop_arena_free(&_arena_10);
                                                                    return _wa_ret;
                                                                }
                                                            } else {
                                                                if (!(quiet)) {
                                                                    printf("%s", "Reasoning completed: ");
                                                                    ({ slop_string _ps_516 = (int_to_string(arena, inferred)); printf("%.*s", (int)_ps_516.len, _ps_516.data); });
                                                                    printf("%s", " inferred in ");
                                                                    ({ slop_string _ps_517 = (int_to_string(arena, iters)); printf("%.*s", (int)_ps_517.len, _ps_517.data); });
                                                                    printf("%s", " iterations (");
                                                                    growl_cli_main_print_elapsed(arena, reason_elapsed);
                                                                    printf("%s\n", ")");
                                                                    printf("%s", "Total: ");
                                                                    ({ slop_string _ps_518 = (int_to_string(arena, rdf_indexed_graph_size(s.graph))); printf("%.*s", (int)_ps_518.len, _ps_518.data); });
                                                                    printf("%s\n", " triples");
                                                                }
                                                                if (quiet) {
                                                                    ({ slop_string _ps_519 = (input_path); printf("%.*s", (int)_ps_519.len, _ps_519.data); });
                                                                    printf("%s", ": ");
                                                                    growl_cli_main_print_elapsed(arena, parse_elapsed);
                                                                    printf("%s", " parse, ");
                                                                    growl_cli_main_print_elapsed(arena, reason_elapsed);
                                                                    printf("%s", " reason, ");
                                                                    ({ slop_string _ps_520 = (int_to_string(arena, input_size)); printf("%.*s", (int)_ps_520.len, _ps_520.data); });
                                                                    printf("%s", " -> ");
                                                                    ({ slop_string _ps_521 = (int_to_string(arena, rdf_indexed_graph_size(s.graph))); printf("%.*s", (int)_ps_521.len, _ps_521.data); });
                                                                    printf("%s\n", " triples");
                                                                }
                                                                __auto_type _mv_522 = args.emit_file;
                                                                if (_mv_522.has_value) {
                                                                    __auto_type emit_path = _mv_522.value;
                                                                    {
                                                                        __auto_type out_ig = s.graph;
                                                                        {
                                                                            __auto_type _coll = g.triples;
                                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                __auto_type t = _coll.data[_i];
                                                                                {
                                                                                    __auto_type pred = t.predicate;
                                                                                    if (slop_map_has(annot_set, &(pred))) {
                                                                                        out_ig = rdf_indexed_graph_add(arena, out_ig, t);
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                        {
                                                                            __auto_type out_graph = growl_indexed_to_graph(arena, out_ig);
                                                                            slop_option_string no_base = (slop_option_string){.has_value = false};
                                                                            __auto_type config = ((slop_rdf_serialize_ttl_SerializeConfig){.prefixes = slop_rdf_ttl_make_prefix_map(arena), .base_iri = no_base, .indent_width = 2});
                                                                            __auto_type _mv_524 = slop_rdf_serialize_ttl_serialize_ttl_stream(arena, out_graph, config, emit_path);
                                                                            if (_mv_524.is_ok) {
                                                                                __auto_type _ = _mv_524.data.ok;
                                                                                if (!(quiet)) {
                                                                                    printf("%s", "Wrote materialized graph to ");
                                                                                    ({ slop_string _ps_525 = (emit_path); printf("%.*s\n", (int)_ps_525.len, _ps_525.data); });
                                                                                }
                                                                                {
                                                                                    int _wa_ret = 0;
                                                                                    slop_arena_free(&_arena_10);
                                                                                    return _wa_ret;
                                                                                }
                                                                            } else if (!_mv_524.is_ok) {
                                                                                __auto_type _ = _mv_524.data.err;
                                                                                printf("%s", "Error: failed to write ");
                                                                                ({ slop_string _ps_526 = (emit_path); printf("%.*s\n", (int)_ps_526.len, _ps_526.data); });
                                                                                {
                                                                                    int _wa_ret = 1;
                                                                                    slop_arena_free(&_arena_10);
                                                                                    return _wa_ret;
                                                                                }
                                                                            }
                                                                            SLOP_UNREACHABLE();
                                                                        }
                                                                    }
                                                                } else if (!_mv_522.has_value) {
                                                                    {
                                                                        int _wa_ret = 0;
                                                                        slop_arena_free(&_arena_10);
                                                                        return _wa_ret;
                                                                    }
                                                                }
                                                                SLOP_UNREACHABLE();
                                                            }
                                                        }
                                                    }
                                                    case growl_types_ReasonerResult_reason_inconsistent:
                                                    {
                                                        __auto_type reports = _mv_515.data.reason_inconsistent;
                                                        {
                                                            __auto_type reason_elapsed = (slop_now_ms() - reason_start);
                                                            if (validate_mode) {
                                                                {
                                                                    __auto_type report_count = ((int64_t)((reports).len));
                                                                    printf("%s", "[FAIL] Validation found ");
                                                                    ({ slop_string _ps_527 = (int_to_string(arena, report_count)); printf("%.*s", (int)_ps_527.len, _ps_527.data); });
                                                                    printf("%s\n", " unsatisfiable entities");
                                                                    printf("%s\n", "");
                                                                    {
                                                                        int64_t idx = 0;
                                                                        {
                                                                            __auto_type _coll = reports;
                                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                __auto_type r = _coll.data[_i];
                                                                                idx = (idx + 1);
                                                                                printf("%s", "  ");
                                                                                ({ slop_string _ps_528 = (int_to_string(arena, idx)); printf("%.*s", (int)_ps_528.len, _ps_528.data); });
                                                                                printf("%s", ". ");
                                                                                ({ slop_string _ps_529 = (r.reason); printf("%.*s\n", (int)_ps_529.len, _ps_529.data); });
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    int _wa_ret = 1;
                                                                    slop_arena_free(&_arena_10);
                                                                    return _wa_ret;
                                                                }
                                                            } else {
                                                                __auto_type _mv_530 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_growl_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                                if (_mv_530.has_value) {
                                                                    __auto_type report = _mv_530.value;
                                                                    if (quiet) {
                                                                        ({ slop_string _ps_531 = (input_path); printf("%.*s", (int)_ps_531.len, _ps_531.data); });
                                                                        printf("%s", ": ");
                                                                        growl_cli_main_print_elapsed(arena, parse_elapsed);
                                                                        printf("%s", " parse, ");
                                                                        growl_cli_main_print_elapsed(arena, reason_elapsed);
                                                                        printf("%s", " reason, ");
                                                                        ({ slop_string _ps_532 = (int_to_string(arena, input_size)); printf("%.*s", (int)_ps_532.len, _ps_532.data); });
                                                                        printf("%s\n", " triples [INCONSISTENT]");
                                                                    }
                                                                    printf("%s\n", "[FAIL] Ontology is inconsistent");
                                                                    printf("%s", "  Reason: ");
                                                                    ({ slop_string _ps_533 = (report.reason); printf("%.*s\n", (int)_ps_533.len, _ps_533.data); });
                                                                    {
                                                                        int _wa_ret = 1;
                                                                        slop_arena_free(&_arena_10);
                                                                        return _wa_ret;
                                                                    }
                                                                } else if (!_mv_530.has_value) {
                                                                    printf("%s\n", "[FAIL] Ontology is inconsistent (no details)");
                                                                    {
                                                                        int _wa_ret = 1;
                                                                        slop_arena_free(&_arena_10);
                                                                        return _wa_ret;
                                                                    }
                                                                }
                                                                SLOP_UNREACHABLE();
                                                            }
                                                        }
                                                    }
                                                    case growl_types_ReasonerResult_reason_cancelled:
                                                    {
                                                        __auto_type s = _mv_515.data.reason_cancelled;
                                                        printf("%s\n", "[CANCELLED] Reasoning was cancelled");
                                                        if (!(quiet)) {
                                                            printf("%s", "Partial result: ");
                                                            ({ slop_string _ps_534 = (int_to_string(arena, s.inferred_count)); printf("%.*s", (int)_ps_534.len, _ps_534.data); });
                                                            printf("%s", " inferred in ");
                                                            ({ slop_string _ps_535 = (int_to_string(arena, s.iterations)); printf("%.*s", (int)_ps_535.len, _ps_535.data); });
                                                            printf("%s\n", " iterations");
                                                        }
                                                        {
                                                            int _wa_ret = 1;
                                                            slop_arena_free(&_arena_10);
                                                            return _wa_ret;
                                                        }
                                                    }
                                                }
                                                SLOP_UNREACHABLE();
                                            }
                                        }
                                    }
                                }
                            }
                            SLOP_UNREACHABLE();
                        }
                    }
                }
                SLOP_UNREACHABLE();
            }
        }
        slop_arena_free(arena);
    }
}

