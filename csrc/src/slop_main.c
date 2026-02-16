#include "../runtime/slop_runtime.h"
#include "slop_main.h"

void main_print_elapsed(slop_arena* arena, int64_t elapsed);
rdf_Term main_remap_blank_term(slop_arena* arena, rdf_Term t, int64_t offset);
int64_t main_max_blank_id_in_graph(index_IndexedGraph ig);
slop_string main_argv_to_string(uint8_t** argv, int64_t index);
main_CliArgs main_parse_args(slop_arena* arena, int64_t argc, uint8_t** argv);
void main_print_usage(void);
int main(int argc, char** _c_argv);

void main_print_elapsed(slop_arena* arena, int64_t elapsed) {
    printf("%.*s", (int)(int_to_string(arena, (elapsed / 1000))).len, (int_to_string(arena, (elapsed / 1000))).data);
    printf("%s", ".");
    {
        __auto_type ms = (elapsed % 1000);
        if ((ms < 100)) {
            printf("%s", "0");
        }
        if ((ms < 10)) {
            printf("%s", "0");
        }
        printf("%.*s", (int)(int_to_string(arena, ms)).len, (int_to_string(arena, ms)).data);
    }
    printf("%s", "s");
}

rdf_Term main_remap_blank_term(slop_arena* arena, rdf_Term t, int64_t offset) {
    __auto_type _mv_353 = t;
    switch (_mv_353.tag) {
        case rdf_Term_term_blank:
        {
            __auto_type b = _mv_353.data.term_blank;
            return rdf_make_blank(arena, (b.id + offset));
        }
        case rdf_Term_term_iri:
        {
            __auto_type _ = _mv_353.data.term_iri;
            return t;
        }
        case rdf_Term_term_literal:
        {
            __auto_type _ = _mv_353.data.term_literal;
            return t;
        }
    }
}

int64_t main_max_blank_id_in_graph(index_IndexedGraph ig) {
    {
        __auto_type triples = ig.triples;
        int64_t max_id = 0;
        {
            __auto_type _coll = triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                __auto_type _mv_354 = t.subject;
                switch (_mv_354.tag) {
                    case rdf_Term_term_blank:
                    {
                        __auto_type b = _mv_354.data.term_blank;
                        if ((b.id > max_id)) {
                            max_id = b.id;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                __auto_type _mv_355 = t.object;
                switch (_mv_355.tag) {
                    case rdf_Term_term_blank:
                    {
                        __auto_type b = _mv_355.data.term_blank;
                        if ((b.id > max_id)) {
                            max_id = b.id;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }
        return max_id;
    }
}

slop_string main_argv_to_string(uint8_t** argv, int64_t index) {
    {
        __auto_type ptr = argv[index];
        return (slop_string){.len = strlen(ptr), .data = ptr};
    }
}

main_CliArgs main_parse_args(slop_arena* arena, int64_t argc, uint8_t** argv) {
    {
        slop_option_string input = (slop_option_string){.has_value = false};
        slop_option_string emit = (slop_option_string){.has_value = false};
        slop_option_string background = (slop_option_string){.has_value = false};
        slop_option_string validate_ns_opt = (slop_option_string){.has_value = false};
        uint8_t quiet = 0;
        uint8_t fast = 0;
        uint8_t complete = 0;
        uint8_t validate = 0;
        uint8_t help = 0;
        uint8_t version = 0;
        int64_t i = 1;
        while ((i < argc)) {
            {
                __auto_type arg = main_argv_to_string(argv, i);
                if ((string_eq(arg, SLOP_STR("--help")) || string_eq(arg, SLOP_STR("-h")))) {
                    help = 1;
                    i = (i + 1);
                } else if ((string_eq(arg, SLOP_STR("--version")) || string_eq(arg, SLOP_STR("-V")))) {
                    version = 1;
                    i = (i + 1);
                } else if ((string_eq(arg, SLOP_STR("--quiet")) || string_eq(arg, SLOP_STR("-q")))) {
                    quiet = 1;
                    i = (i + 1);
                } else if ((string_eq(arg, SLOP_STR("--fast")) || string_eq(arg, SLOP_STR("-f")))) {
                    fast = 1;
                    i = (i + 1);
                } else if ((string_eq(arg, SLOP_STR("--complete")) || string_eq(arg, SLOP_STR("-c")))) {
                    complete = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--validate"))) {
                    validate = 1;
                    i = (i + 1);
                } else if (string_eq(arg, SLOP_STR("--validate-ns"))) {
                    if (((i + 1) < argc)) {
                        validate_ns_opt = (slop_option_string){.has_value = 1, .value = main_argv_to_string(argv, (i + 1))};
                        i = (i + 2);
                    } else {
                        printf("%s\n", "Error: --validate-ns requires an IRI prefix");
                        help = 1;
                        i = (i + 1);
                    }
                } else if ((string_eq(arg, SLOP_STR("--background")) || string_eq(arg, SLOP_STR("-b")))) {
                    if (((i + 1) < argc)) {
                        background = (slop_option_string){.has_value = 1, .value = main_argv_to_string(argv, (i + 1))};
                        i = (i + 2);
                    } else {
                        printf("%s\n", "Error: --background requires a file path");
                        help = 1;
                        i = (i + 1);
                    }
                } else if ((string_eq(arg, SLOP_STR("--emit")) || string_eq(arg, SLOP_STR("-o")))) {
                    if (((i + 1) < argc)) {
                        emit = (slop_option_string){.has_value = 1, .value = main_argv_to_string(argv, (i + 1))};
                        i = (i + 2);
                    } else {
                        printf("%s\n", "Error: --emit requires a file path");
                        help = 1;
                        i = (i + 1);
                    }
                } else if (1) {
                    input = (slop_option_string){.has_value = 1, .value = arg};
                    i = (i + 1);
                }
            }
        }
        return ((main_CliArgs){.input_file = input, .emit_file = emit, .background_file = background, .validate_ns = validate_ns_opt, .quiet = quiet, .fast = fast, .complete = complete, .validate = validate, .show_help = help, .show_version = version});
    }
}

void main_print_usage(void) {
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
    printf("%s\n", "  --validate       Check TBox satisfiability via synthetic instance injection");
    printf("%s\n", "  --validate-ns NS Only validate entities with IRIs starting with NS");
    printf("%s\n", "  -b, --background FILE  Load background ontology (e.g. TLO) for reasoning context");
    printf("%s\n", "  -V, --version    Show version information");
}

int main(int argc, char** _c_argv) {
    uint8_t** argv = (uint8_t**)_c_argv;
    {
        #ifdef SLOP_DEBUG
        SLOP_PRE((268435456) > 0, "with-arena size must be positive");
        #endif
        slop_arena _arena = slop_arena_new(268435456);
        #ifdef SLOP_DEBUG
        SLOP_PRE(_arena.base != NULL, "arena allocation failed");
        #endif
        slop_arena* arena = &_arena;
        {
            __auto_type args = main_parse_args(arena, argc, argv);
            if (args.show_version) {
                printf("growl %s\n", GROWL_VERSION);
                return 0;
            } else {
                __auto_type _mv_356 = args.input_file;
                if (!_mv_356.has_value) {
                    main_print_usage();
                    if (args.show_help) {
                        return 0;
                    } else {
                        return 1;
                    }
                } else if (_mv_356.has_value) {
                    __auto_type input_path = _mv_356.value;
                    if (args.show_help) {
                        main_print_usage();
                        return 0;
                    } else {
                        {
                            __auto_type quiet = args.quiet;
                            __auto_type parse_start = slop_now_ms();
                            __auto_type _mv_357 = ttl_parse_ttl_file(arena, input_path);
                            if (!_mv_357.is_ok) {
                                __auto_type e = _mv_357.data.err;
                                printf("%s", "Error: failed to parse ");
                                printf("%.*s\n", (int)(input_path).len, (input_path).data);
                                __auto_type _mv_358 = e;
                                switch (_mv_358.tag) {
                                    case ttl_TtlFileError_parse_error:
                                    {
                                        __auto_type pe = _mv_358.data.parse_error;
                                        printf("%s", "  at line ");
                                        printf("%.*s", (int)(int_to_string(arena, pe.position.line)).len, (int_to_string(arena, pe.position.line)).data);
                                        printf("%s", ", column ");
                                        printf("%.*s\n", (int)(int_to_string(arena, pe.position.column)).len, (int_to_string(arena, pe.position.column)).data);
                                        printf("%s", "  ");
                                        printf("%.*s\n", (int)(pe.message).len, (pe.message).data);
                                        break;
                                    }
                                    case ttl_TtlFileError_file_error:
                                    {
                                        __auto_type _ = _mv_358.data.file_error;
                                        printf("%s\n", "  (file error)");
                                        break;
                                    }
                                }
                                return 1;
                            } else if (_mv_357.is_ok) {
                                __auto_type g = _mv_357.data.ok;
                                {
                                    __auto_type annot_set = growl_collect_annotation_properties(arena, g);
                                    __auto_type original_size = rdf_graph_size(g);
                                    __auto_type ig = growl_graph_to_indexed(arena, g, annot_set);
                                    __auto_type input_size = rdf_indexed_graph_size(ig);
                                    __auto_type filtered_count = (original_size - ((rdf_GraphSize)(input_size)));
                                    __auto_type parse_elapsed = (slop_now_ms() - parse_start);
                                    if (!(quiet)) {
                                        printf("%s", "Parsed ");
                                        printf("%.*s", (int)(int_to_string(arena, input_size)).len, (int_to_string(arena, input_size)).data);
                                        printf("%s", " triples from ");
                                        printf("%.*s", (int)(input_path).len, (input_path).data);
                                        if ((filtered_count > 0)) {
                                            printf("%s", " (filtered ");
                                            printf("%.*s", (int)(int_to_string(arena, filtered_count)).len, (int_to_string(arena, filtered_count)).data);
                                            printf("%s", " annotations)");
                                        }
                                        printf("%s", " (");
                                        main_print_elapsed(arena, parse_elapsed);
                                        printf("%s\n", ")");
                                    }
                                    {
                                        __auto_type combined_ig = ig;
                                        __auto_type _mv_359 = args.background_file;
                                        if (_mv_359.has_value) {
                                            __auto_type bg_path = _mv_359.value;
                                            __auto_type _mv_360 = ttl_parse_ttl_file(arena, bg_path);
                                            if (!_mv_360.is_ok) {
                                                __auto_type _ = _mv_360.data.err;
                                                printf("%s", "Error: failed to parse background file ");
                                                printf("%.*s\n", (int)(bg_path).len, (bg_path).data);
                                                return 1;
                                            } else if (_mv_360.is_ok) {
                                                __auto_type bg_graph = _mv_360.data.ok;
                                                {
                                                    __auto_type bg_annot_set = growl_collect_annotation_properties(arena, bg_graph);
                                                    __auto_type bg_ig = growl_graph_to_indexed(arena, bg_graph, bg_annot_set);
                                                    if (!(quiet)) {
                                                        printf("%s", "Loaded ");
                                                        printf("%.*s", (int)(int_to_string(arena, rdf_indexed_graph_size(bg_ig))).len, (int_to_string(arena, rdf_indexed_graph_size(bg_ig))).data);
                                                        printf("%s", " background triples from ");
                                                        printf("%.*s\n", (int)(bg_path).len, (bg_path).data);
                                                    }
                                                    {
                                                        __auto_type bg_triples = bg_ig.triples;
                                                        __auto_type bg_blank_offset = (main_max_blank_id_in_graph(ig) + 1);
                                                        {
                                                            __auto_type _coll = bg_triples;
                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                __auto_type t = _coll.data[_i];
                                                                {
                                                                    __auto_type rs = main_remap_blank_term(arena, t.subject, bg_blank_offset);
                                                                    __auto_type rp = t.predicate;
                                                                    __auto_type ro = main_remap_blank_term(arena, t.object, bg_blank_offset);
                                                                    __auto_type remapped = rdf_make_triple(arena, rs, rp, ro);
                                                                    combined_ig = rdf_indexed_graph_add(arena, combined_ig, remapped);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else if (!_mv_359.has_value) {
                                        }
                                        {
                                            __auto_type validate_mode = args.validate;
                                            __auto_type effective_fast = (args.fast && !(validate_mode));
                                            __auto_type ns_filter = ({ __auto_type _mv = args.validate_ns; _mv.has_value ? ({ __auto_type ns = _mv.value; ns; }) : (SLOP_STR("")); });
                                            if ((args.fast && validate_mode)) {
                                                printf("%s\n", "Warning: --validate overrides --fast (schema materialization required)");
                                            }
                                            if ((validate_mode && ({ __auto_type _mv = args.emit_file; _mv.has_value ? ({ __auto_type _ = _mv.value; 1; }) : (0); }))) {
                                                printf("%s\n", "Warning: --emit is ignored in --validate mode");
                                            }
                                            if (((validate_mode) && (({ __auto_type _mv = args.background_file; _mv.has_value ? ({ __auto_type _ = _mv.value; 1; }) : (0); })) && ((string_len(ns_filter) == 0)))) {
                                                printf("%s\n", "Warning: --validate with --background but no --validate-ns; all classes will be validated (slow for large TLOs)");
                                            }
                                            {
                                                __auto_type reason_start = slop_now_ms();
                                                __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = !(quiet), .fast = effective_fast, .complete = args.complete, .validate = validate_mode, .validate_ns = ns_filter});
                                                __auto_type _mv_361 = growl_reason_with_config(arena, combined_ig, config);
                                                switch (_mv_361.tag) {
                                                    case types_ReasonerResult_reason_success:
                                                    {
                                                        __auto_type s = _mv_361.data.reason_success;
                                                        {
                                                            __auto_type inferred = s.inferred_count;
                                                            __auto_type iters = s.iterations;
                                                            __auto_type reason_elapsed = (slop_now_ms() - reason_start);
                                                            if (validate_mode) {
                                                                printf("%s\n", "[PASS] Validation passed — all classes are satisfiable");
                                                                return 0;
                                                            } else {
                                                                if (!(quiet)) {
                                                                    printf("%s", "Reasoning completed: ");
                                                                    printf("%.*s", (int)(int_to_string(arena, inferred)).len, (int_to_string(arena, inferred)).data);
                                                                    printf("%s", " inferred in ");
                                                                    printf("%.*s", (int)(int_to_string(arena, iters)).len, (int_to_string(arena, iters)).data);
                                                                    printf("%s", " iterations (");
                                                                    main_print_elapsed(arena, reason_elapsed);
                                                                    printf("%s\n", ")");
                                                                    printf("%s", "Total: ");
                                                                    printf("%.*s", (int)(int_to_string(arena, rdf_indexed_graph_size(s.graph))).len, (int_to_string(arena, rdf_indexed_graph_size(s.graph))).data);
                                                                    printf("%s\n", " triples");
                                                                }
                                                                if (quiet) {
                                                                    printf("%.*s", (int)(input_path).len, (input_path).data);
                                                                    printf("%s", ": ");
                                                                    main_print_elapsed(arena, parse_elapsed);
                                                                    printf("%s", " parse, ");
                                                                    main_print_elapsed(arena, reason_elapsed);
                                                                    printf("%s", " reason, ");
                                                                    printf("%.*s", (int)(int_to_string(arena, input_size)).len, (int_to_string(arena, input_size)).data);
                                                                    printf("%s", " -> ");
                                                                    printf("%.*s", (int)(int_to_string(arena, rdf_indexed_graph_size(s.graph))).len, (int_to_string(arena, rdf_indexed_graph_size(s.graph))).data);
                                                                    printf("%s\n", " triples");
                                                                }
                                                                __auto_type _mv_362 = args.emit_file;
                                                                if (_mv_362.has_value) {
                                                                    __auto_type emit_path = _mv_362.value;
                                                                    {
                                                                        __auto_type out_ig = s.graph;
                                                                        {
                                                                            __auto_type _coll = g.triples;
                                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                __auto_type t = _coll.data[_i];
                                                                                {
                                                                                    __auto_type pred = t.predicate;
                                                                                    if ((slop_map_get(annot_set, &(pred)) != NULL)) {
                                                                                        out_ig = rdf_indexed_graph_add(arena, out_ig, t);
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                        {
                                                                            __auto_type out_graph = growl_indexed_to_graph(arena, out_ig);
                                                                            slop_option_string no_base = (slop_option_string){.has_value = false};
                                                                            __auto_type config = ((serialize_ttl_SerializeConfig){.prefixes = ttl_make_prefix_map(arena), .base_iri = no_base, .indent_width = 2});
                                                                            __auto_type _mv_363 = serialize_ttl_serialize_ttl_stream(arena, out_graph, config, emit_path);
                                                                            if (_mv_363.is_ok) {
                                                                                __auto_type _ = _mv_363.data.ok;
                                                                                if (!(quiet)) {
                                                                                    printf("%s", "Wrote materialized graph to ");
                                                                                    printf("%.*s\n", (int)(emit_path).len, (emit_path).data);
                                                                                }
                                                                                return 0;
                                                                            } else if (!_mv_363.is_ok) {
                                                                                __auto_type _ = _mv_363.data.err;
                                                                                printf("%s", "Error: failed to write ");
                                                                                printf("%.*s\n", (int)(emit_path).len, (emit_path).data);
                                                                                return 1;
                                                                            }
                                                                        }
                                                                    }
                                                                } else if (!_mv_362.has_value) {
                                                                    return 0;
                                                                }
                                                            }
                                                        }
                                                    }
                                                    case types_ReasonerResult_reason_inconsistent:
                                                    {
                                                        __auto_type reports = _mv_361.data.reason_inconsistent;
                                                        {
                                                            __auto_type reason_elapsed = (slop_now_ms() - reason_start);
                                                            if (validate_mode) {
                                                                {
                                                                    __auto_type report_count = ((int64_t)((reports).len));
                                                                    printf("%s", "[FAIL] Validation found ");
                                                                    printf("%.*s", (int)(int_to_string(arena, report_count)).len, (int_to_string(arena, report_count)).data);
                                                                    printf("%s\n", " unsatisfiable entities");
                                                                    printf("%s\n", "");
                                                                    {
                                                                        __auto_type idx = 0;
                                                                        {
                                                                            __auto_type _coll = reports;
                                                                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                                                                __auto_type r = _coll.data[_i];
                                                                                idx = (idx + 1);
                                                                                printf("%s", "  ");
                                                                                printf("%.*s", (int)(int_to_string(arena, idx)).len, (int_to_string(arena, idx)).data);
                                                                                printf("%s", ". ");
                                                                                printf("%.*s\n", (int)(r.reason).len, (r.reason).data);
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                return 1;
                                                            } else {
                                                                __auto_type _mv_364 = ({ __auto_type _lst = reports; size_t _idx = (size_t)0; slop_option_types_InconsistencyReport _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                                if (_mv_364.has_value) {
                                                                    __auto_type report = _mv_364.value;
                                                                    if (quiet) {
                                                                        printf("%.*s", (int)(input_path).len, (input_path).data);
                                                                        printf("%s", ": ");
                                                                        main_print_elapsed(arena, parse_elapsed);
                                                                        printf("%s", " parse, ");
                                                                        main_print_elapsed(arena, reason_elapsed);
                                                                        printf("%s", " reason, ");
                                                                        printf("%.*s", (int)(int_to_string(arena, input_size)).len, (int_to_string(arena, input_size)).data);
                                                                        printf("%s\n", " triples [INCONSISTENT]");
                                                                    }
                                                                    printf("%s\n", "[FAIL] Ontology is inconsistent");
                                                                    printf("%s", "  Reason: ");
                                                                    printf("%.*s\n", (int)(report.reason).len, (report.reason).data);
                                                                    return 1;
                                                                } else if (!_mv_364.has_value) {
                                                                    printf("%s\n", "[FAIL] Ontology is inconsistent (no details)");
                                                                    return 1;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        slop_arena_free(arena);
    }
}

