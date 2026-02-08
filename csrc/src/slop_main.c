#include "../runtime/slop_runtime.h"
#include "slop_main.h"

void main_print_elapsed(slop_arena* arena, int64_t elapsed);
slop_string main_argv_to_string(uint8_t** argv, int64_t index);
main_CliArgs main_parse_args(slop_arena* arena, int64_t argc, uint8_t** argv);
void main_print_usage(void);
index_IndexedGraph main_graph_to_indexed(slop_arena* arena, rdf_Graph g);
rdf_Graph main_indexed_to_graph(slop_arena* arena, index_IndexedGraph ig);
int main(int64_t argc, uint8_t** argv);

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
        uint8_t quiet = 0;
        uint8_t fast = 0;
        uint8_t complete = 0;
        uint8_t help = 0;
        int64_t i = 1;
        while ((i < argc)) {
            {
                __auto_type arg = main_argv_to_string(argv, i);
                if ((string_eq(arg, SLOP_STR("--help")) || string_eq(arg, SLOP_STR("-h")))) {
                    help = 1;
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
        return ((main_CliArgs){.input_file = input, .emit_file = emit, .quiet = quiet, .fast = fast, .complete = complete, .show_help = help});
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
}

index_IndexedGraph main_graph_to_indexed(slop_arena* arena, rdf_Graph g) {
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

rdf_Graph main_indexed_to_graph(slop_arena* arena, index_IndexedGraph ig) {
    return ((rdf_Graph){.triples = ig.triples, .size = ((rdf_GraphSize)(rdf_indexed_graph_size(ig)))});
}

int main(int64_t argc, uint8_t** argv) {
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
            __auto_type _mv_310 = args.input_file;
            if (!_mv_310.has_value) {
                main_print_usage();
                if (args.show_help) {
                    return 0;
                } else {
                    return 1;
                }
            } else if (_mv_310.has_value) {
                __auto_type input_path = _mv_310.value;
                if (args.show_help) {
                    main_print_usage();
                    return 0;
                } else {
                    {
                        __auto_type quiet = args.quiet;
                        __auto_type parse_start = slop_now_ms();
                        __auto_type _mv_311 = ttl_parse_ttl_file(arena, input_path);
                        if (!_mv_311.is_ok) {
                            __auto_type e = _mv_311.data.err;
                            printf("%s", "Error: failed to parse ");
                            printf("%.*s\n", (int)(input_path).len, (input_path).data);
                            __auto_type _mv_312 = e;
                            switch (_mv_312.tag) {
                                case ttl_TtlFileError_parse_error:
                                {
                                    __auto_type pe = _mv_312.data.parse_error;
                                    printf("%s", "  at line ");
                                    printf("%.*s", (int)(int_to_string(arena, pe.position.line)).len, (int_to_string(arena, pe.position.line)).data);
                                    printf("%s", ", column ");
                                    printf("%.*s\n", (int)(int_to_string(arena, pe.position.column)).len, (int_to_string(arena, pe.position.column)).data);
                                    printf("%s", "  ");
                                    return printf("%.*s\n", (int)(pe.message).len, (pe.message).data);
                                }
                                case ttl_TtlFileError_file_error:
                                {
                                    __auto_type _ = _mv_312.data.file_error;
                                    return printf("%s\n", "  (file error)");
                                }
                            }
                            return 1;
                        } else if (_mv_311.is_ok) {
                            __auto_type g = _mv_311.data.ok;
                            {
                                __auto_type ig = main_graph_to_indexed(arena, g);
                                __auto_type input_size = rdf_indexed_graph_size(ig);
                                __auto_type parse_elapsed = (slop_now_ms() - parse_start);
                                if (!(quiet)) {
                                    printf("%s", "Parsed ");
                                    printf("%.*s", (int)(int_to_string(arena, input_size)).len, (int_to_string(arena, input_size)).data);
                                    printf("%s", " triples from ");
                                    printf("%.*s", (int)(input_path).len, (input_path).data);
                                    printf("%s", " (");
                                    main_print_elapsed(arena, parse_elapsed);
                                    printf("%s\n", ")");
                                }
                                {
                                    __auto_type reason_start = slop_now_ms();
                                    __auto_type config = ((types_ReasonerConfig){.worker_count = 4, .channel_buffer = 256, .max_iterations = 1000, .verbose = !(quiet), .fast = args.fast, .complete = args.complete});
                                    __auto_type _mv_313 = growl_reason_with_config(arena, ig, config);
                                    switch (_mv_313.tag) {
                                        case types_ReasonerResult_reason_success:
                                        {
                                            __auto_type s = _mv_313.data.reason_success;
                                            {
                                                __auto_type inferred = s.inferred_count;
                                                __auto_type iters = s.iterations;
                                                __auto_type reason_elapsed = (slop_now_ms() - reason_start);
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
                                                __auto_type _mv_314 = args.emit_file;
                                                if (_mv_314.has_value) {
                                                    __auto_type emit_path = _mv_314.value;
                                                    {
                                                        __auto_type out_graph = main_indexed_to_graph(arena, s.graph);
                                                        slop_option_string no_base = (slop_option_string){.has_value = false};
                                                        __auto_type config = ((serialize_ttl_SerializeConfig){.prefixes = ttl_make_prefix_map(arena), .base_iri = no_base, .indent_width = 2});
                                                        __auto_type _mv_315 = serialize_ttl_serialize_ttl_stream(arena, out_graph, config, emit_path);
                                                        if (_mv_315.is_ok) {
                                                            __auto_type _ = _mv_315.data.ok;
                                                            if (!(quiet)) {
                                                                printf("%s", "Wrote materialized graph to ");
                                                                printf("%.*s\n", (int)(emit_path).len, (emit_path).data);
                                                            }
                                                            return 0;
                                                        } else if (!_mv_315.is_ok) {
                                                            __auto_type _ = _mv_315.data.err;
                                                            printf("%s", "Error: failed to write ");
                                                            printf("%.*s\n", (int)(emit_path).len, (emit_path).data);
                                                            return 1;
                                                        }
                                                    }
                                                } else if (!_mv_314.has_value) {
                                                    return 0;
                                                }
                                            }
                                        }
                                        case types_ReasonerResult_reason_inconsistent:
                                        {
                                            __auto_type report = _mv_313.data.reason_inconsistent;
                                            {
                                                __auto_type reason_elapsed = (slop_now_ms() - reason_start);
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

