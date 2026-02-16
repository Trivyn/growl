#include "../runtime/slop_runtime.h"
#include "slop_engine.h"

void engine_print_ms(slop_arena* arena, int64_t ms);
slop_list_rdf_Term engine_collect_declared_properties(slop_arena* arena, index_IndexedGraph g);
uint8_t engine_iri_matches_ns(rdf_Term term, slop_string ns);
engine_ValidateInjection engine_inject_validate_instances(slop_arena* arena, index_IndexedGraph g, uint8_t verbose, slop_string validate_ns);
slop_string engine_resolve_blank_class(slop_arena* arena, int64_t blank_id, slop_list_rdf_Term class_map);
slop_string engine_resolve_blank_prop(slop_arena* arena, int64_t blank_id, slop_list_rdf_Term prop_map);
slop_string engine_build_enriched_reason(slop_arena* arena, slop_string class_name, slop_string prop_name, slop_string original_reason, slop_string detail);
types_InconsistencyReport engine_enrich_validate_report(slop_arena* arena, types_InconsistencyReport report, index_IndexedGraph pre_inject_graph, slop_string validate_ns, slop_list_rdf_Term class_map, slop_list_rdf_Term prop_map);
slop_list_types_InconsistencyReport engine_validate_check_all(slop_arena* arena, index_IndexedGraph g, index_IndexedGraph pre_inject_graph, slop_string validate_ns, slop_list_rdf_Term class_map, slop_list_rdf_Term prop_map);
types_ReasonerResult engine_engine_run(slop_arena* arena, types_ReasonerConfig config, index_IndexedGraph initial);
types_Delta engine_make_initial_delta(slop_arena* arena, index_IndexedGraph g);
slop_list_rdf_Triple engine_compute_tc(slop_arena* arena, index_IndexedGraph g, rdf_Term pred);
index_IndexedGraph engine_schema_materialize(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_EngineState_types_InconsistencyReport engine_engine_run_iteration(slop_arena* arena, types_EngineState state);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_sequential(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_parallel(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
index_IndexedGraph engine_merge_into_graph(slop_arena* arena, index_IndexedGraph g, types_Delta d);
slop_list_thread_int_ptr engine_spawn_rule_workers(slop_arena* arena, index_IndexedGraph g, types_Delta delta, slop_chan_engine_WorkerMessage* result_chan, slop_arena* arena_cax_infer, slop_arena* arena_cax_check, slop_arena* arena_prp_char, slop_arena* arena_prp_chain, slop_arena* arena_prp_check, slop_arena* arena_eq_infer, slop_arena* arena_eq_check, slop_arena* arena_cls_set, slop_arena* arena_cls_ind, uint8_t verbose, uint8_t fast, uint8_t validate);
slop_result_types_Delta_types_InconsistencyReport engine_collect_worker_results(slop_arena* arena, slop_chan_engine_WorkerMessage* result_chan, slop_list_thread_int_ptr workers, int64_t next_iter);

typedef struct { types_Delta* d; slop_arena* arena; } engine__lambda_274_env_t;

static void engine__lambda_274(engine__lambda_274_env_t* _env, rdf_Triple t) { ({ (*_env->d) = types_delta_add(_env->arena, (*_env->d), t); (void)0; }); }

typedef struct { slop_arena* arena_cax_infer; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_282_env_t;

static slop_result_void_thread_ChanError engine__lambda_282(engine__lambda_282_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_cax_infer, _env->next_iter); ({ __auto_type _coll = cax_cax_sco(_env->arena_cax_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cax_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cax_cax_eqc1(_env->arena_cax_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cax_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cax_cax_eqc2(_env->arena_cax_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cax_infer, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  cax-infer: "); engine_print_ms(_env->arena_cax_infer, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_cax_check; index_IndexedGraph g; types_Delta delta; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_283_env_t;

static slop_result_void_thread_ChanError engine__lambda_283(engine__lambda_283_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); ({ __auto_type _mv = cax_cax_dw(_env->arena_cax_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = cax_cax_adc(_env->arena_cax_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ (void)0; }); } (void)0; }); } (void)0; }); ((_env->verbose) ? ({ ({ printf("%s", "  cax-check: "); engine_print_ms(_env->arena_cax_check, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_prp_char; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_284_env_t;

static slop_result_void_thread_ChanError engine__lambda_284(engine__lambda_284_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_prp_char, _env->next_iter); ({ __auto_type _coll = prp_prp_dom(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_rng(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_fp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_ifp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_symp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_trp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  prp-char: "); engine_print_ms(_env->arena_prp_char, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_prp_chain; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_285_env_t;

static slop_result_void_thread_ChanError engine__lambda_285(engine__lambda_285_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_prp_chain, _env->next_iter); ({ __auto_type _coll = prp_prp_spo1(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_spo2(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_eqp1(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_eqp2(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_inv1(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_inv2(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_key(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  prp-chain: "); engine_print_ms(_env->arena_prp_chain, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_prp_check; index_IndexedGraph g; types_Delta delta; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_286_env_t;

static slop_result_void_thread_ChanError engine__lambda_286(engine__lambda_286_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); ({ __auto_type _mv = prp_prp_asyp(_env->arena_prp_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = prp_prp_irp(_env->arena_prp_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = prp_prp_pdw(_env->arena_prp_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = prp_prp_adp(_env->arena_prp_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = prp_prp_npa1(_env->arena_prp_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = prp_prp_npa2(_env->arena_prp_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ (void)0; }); } (void)0; }); } (void)0; }); } (void)0; }); } (void)0; }); } (void)0; }); } (void)0; }); ((_env->verbose) ? ({ ({ printf("%s", "  prp-check: "); engine_print_ms(_env->arena_prp_check, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_eq_infer; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_287_env_t;

static slop_result_void_thread_ChanError engine__lambda_287(engine__lambda_287_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_eq_infer, _env->next_iter); ({ __auto_type _coll = eq_eq_sym(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_trans(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_rep_s(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_rep_p(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_rep_o(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  eq-infer: "); engine_print_ms(_env->arena_eq_infer, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_eq_check; index_IndexedGraph g; types_Delta delta; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_288_env_t;

static slop_result_void_thread_ChanError engine__lambda_288(engine__lambda_288_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); ({ __auto_type _mv = eq_eq_diff1(_env->arena_eq_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = eq_eq_diff2(_env->arena_eq_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = eq_eq_diff3(_env->arena_eq_check, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ (void)0; }); } (void)0; }); } (void)0; }); } (void)0; }); ((_env->verbose) ? ({ ({ printf("%s", "  eq-check: "); engine_print_ms(_env->arena_eq_check, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_cls_set; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_289_env_t;

static slop_result_void_thread_ChanError engine__lambda_289(engine__lambda_289_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_cls_set, _env->next_iter); ({ __auto_type _coll = cls_cls_int1(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_int2(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_uni(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_svf1(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_svf2(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_avf(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  cls-set: "); engine_print_ms(_env->arena_cls_set, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_cls_ind; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t fast; uint8_t validate; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_290_env_t;

static slop_result_void_thread_ChanError engine__lambda_290(engine__lambda_290_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_cls_ind, _env->next_iter); ({ __auto_type _coll = cls_cls_hv1(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_hv2(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ((!(_env->fast)) ? ({ ({ ((!(_env->validate)) ? ({ ({ ({ __auto_type _mv = cls_cls_maxc1(_env->arena_cls_ind, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ (void)0; }); } (void)0; }); }); 0; }) : ({ (void)0; })); ({ __auto_type _coll = cls_cls_maxc2(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ((!(_env->validate)) ? ({ ({ ({ __auto_type _mv = cls_cls_maxqc1(_env->arena_cls_ind, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = cls_cls_maxqc2(_env->arena_cls_ind, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ (void)0; }); } (void)0; }); } (void)0; }); }); 0; }) : ({ (void)0; })); ({ __auto_type _coll = cls_cls_maxqc3(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_maxqc4(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); }); 0; }) : ({ (void)0; })); ({ __auto_type _coll = cls_cls_oo(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ((!(_env->validate)) ? ({ ({ ({ __auto_type _mv = cls_cls_nothing2(_env->arena_cls_ind, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ __auto_type _mv = cls_cls_com(_env->arena_cls_ind, _env->g, _env->delta); if (_mv.has_value) { __auto_type report = _mv.value; ({ thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); ({ (void)0; }); }); } else { ({ (void)0; }); } (void)0; }); } (void)0; }); }); 0; }) : ({ (void)0; })); ((_env->verbose) ? ({ ({ printf("%s", "  cls-ind: "); engine_print_ms(_env->arena_cls_ind, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

void engine_print_ms(slop_arena* arena, int64_t ms) {
    printf("%.*s", (int)(int_to_string(arena, ms)).len, (int_to_string(arena, ms)).data);
    printf("%s", "ms");
}

slop_list_rdf_Term engine_collect_declared_properties(slop_arena* arena, index_IndexedGraph g) {
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type seen = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type meta_types = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_OBJECT_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_DATATYPE_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_RDF_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_FUNCTIONAL_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_INVERSE_FUNCTIONAL_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_TRANSITIVE_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_SYMMETRIC_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_ASYMMETRIC_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_REFLEXIVE_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(meta_types); __auto_type _item = (rdf_make_iri(arena, vocab_OWL_IRREFLEXIVE_PROPERTY)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type _coll = meta_types;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type mt = _coll.data[_i];
                {
                    __auto_type matches = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = mt});
                    {
                        __auto_type _coll = matches;
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            {
                                __auto_type prop = rdf_triple_subject(t);
                                if (!((slop_map_get(seen, &(prop)) != NULL))) {
                                    ({ uint8_t _dummy = 1; slop_map_put(arena, seen, &(prop), &_dummy); });
                                    ({ __auto_type _lst_p = &(result); __auto_type _item = (prop); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                }
                            }
                        }
                    }
                }
            }
        }
        return result;
    }
}

uint8_t engine_iri_matches_ns(rdf_Term term, slop_string ns) {
    __auto_type _mv_246 = term;
    switch (_mv_246.tag) {
        case rdf_Term_term_iri:
        {
            __auto_type iri = _mv_246.data.term_iri;
            if ((ns.len == 0)) {
                return 1;
            } else {
                return strlib_starts_with(iri.value, ns);
            }
        }
        default: {
            return 0;
        }
    }
}

engine_ValidateInjection engine_inject_validate_instances(slop_arena* arena, index_IndexedGraph g, uint8_t verbose, slop_string validate_ns) {
    {
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type class_type = rdf_make_iri(arena, vocab_OWL_CLASS);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type class_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, (slop_option_rdf_Term){.has_value = 1, .value = class_type});
        __auto_type result = g;
        int64_t count = 0;
        __auto_type class_map = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        {
            __auto_type _coll = class_triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                {
                    __auto_type cls = rdf_triple_subject(t);
                    if (engine_iri_matches_ns(cls, validate_ns)) {
                        {
                            __auto_type synthetic = rdf_make_blank(arena, (10000000 + count));
                            __auto_type type_triple = rdf_make_triple(arena, synthetic, type_pred, cls);
                            result = rdf_indexed_graph_add(arena, result, type_triple);
                            ({ __auto_type _lst_p = &(class_map); __auto_type _item = (cls); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            count = (count + 1);
                        }
                    }
                }
            }
        }
        if (verbose) {
            printf("%s", "[validate] injected ");
            printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
            printf("%s\n", " synthetic class instances");
        }
        {
            __auto_type props = engine_collect_declared_properties(arena, g);
            int64_t prop_count = 0;
            __auto_type prop_map = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
            {
                __auto_type _coll = props;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type p = _coll.data[_i];
                    if (engine_iri_matches_ns(p, validate_ns)) {
                        {
                            __auto_type subj_blank = rdf_make_blank(arena, (20000000 + prop_count));
                            __auto_type obj_blank = rdf_make_blank(arena, (30000000 + prop_count));
                            __auto_type prop_triple = rdf_make_triple(arena, subj_blank, p, obj_blank);
                            result = rdf_indexed_graph_add(arena, result, prop_triple);
                            ({ __auto_type _lst_p = &(prop_map); __auto_type _item = (p); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            prop_count = (prop_count + 1);
                        }
                    }
                }
            }
            if (verbose) {
                printf("%s", "[validate] injected ");
                printf("%.*s", (int)(int_to_string(arena, prop_count)).len, (int_to_string(arena, prop_count)).data);
                printf("%s\n", " synthetic property usages");
            }
            return ((engine_ValidateInjection){.graph = result, .class_map = class_map, .prop_map = prop_map});
        }
    }
}

slop_string engine_resolve_blank_class(slop_arena* arena, int64_t blank_id, slop_list_rdf_Term class_map) {
    if (((blank_id >= 10000000) && (blank_id < 20000000))) {
        {
            __auto_type class_index = (blank_id - 10000000);
            __auto_type _mv_247 = ({ __auto_type _lst = class_map; size_t _idx = (size_t)class_index; slop_option_rdf_Term _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
            if (_mv_247.has_value) {
                __auto_type cls = _mv_247.value;
                __auto_type _mv_248 = cls;
                switch (_mv_248.tag) {
                    case rdf_Term_term_iri:
                    {
                        __auto_type iri = _mv_248.data.term_iri;
                        return iri.value;
                    }
                    default: {
                        return SLOP_STR("");
                    }
                }
            } else if (!_mv_247.has_value) {
                return SLOP_STR("");
            }
        }
    } else {
        return SLOP_STR("");
    }
}

slop_string engine_resolve_blank_prop(slop_arena* arena, int64_t blank_id, slop_list_rdf_Term prop_map) {
    if (((blank_id >= 20000000) && (blank_id < 40000000))) {
        {
            __auto_type prop_index = (((blank_id < 30000000)) ? (blank_id - 20000000) : (blank_id - 30000000));
            __auto_type _mv_249 = ({ __auto_type _lst = prop_map; size_t _idx = (size_t)prop_index; slop_option_rdf_Term _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
            if (_mv_249.has_value) {
                __auto_type prop = _mv_249.value;
                __auto_type _mv_250 = prop;
                switch (_mv_250.tag) {
                    case rdf_Term_term_iri:
                    {
                        __auto_type iri = _mv_250.data.term_iri;
                        return iri.value;
                    }
                    default: {
                        return SLOP_STR("");
                    }
                }
            } else if (!_mv_249.has_value) {
                return SLOP_STR("");
            }
        }
    } else {
        return SLOP_STR("");
    }
}

slop_string engine_build_enriched_reason(slop_arena* arena, slop_string class_name, slop_string prop_name, slop_string original_reason, slop_string detail) {
    {
        __auto_type reason_suffix = (((string_len(detail) > 0)) ? string_concat(arena, original_reason, string_concat(arena, SLOP_STR(": "), detail)) : original_reason);
        if ((string_len(class_name) > 0)) {
            return string_concat(arena, string_concat(arena, SLOP_STR("Unsatisfiable class: "), class_name), string_concat(arena, SLOP_STR(" ("), string_concat(arena, reason_suffix, SLOP_STR(")"))));
        } else {
            if ((string_len(prop_name) > 0)) {
                return string_concat(arena, string_concat(arena, SLOP_STR("Unsatisfiable property usage: "), prop_name), string_concat(arena, SLOP_STR(" ("), string_concat(arena, reason_suffix, SLOP_STR(")"))));
            } else {
                return reason_suffix;
            }
        }
    }
}

types_InconsistencyReport engine_enrich_validate_report(slop_arena* arena, types_InconsistencyReport report, index_IndexedGraph pre_inject_graph, slop_string validate_ns, slop_list_rdf_Term class_map, slop_list_rdf_Term prop_map) {
    {
        __auto_type witnesses = report.witnesses;
        __auto_type original_reason = report.reason;
        if (strlib_starts_with(original_reason, SLOP_STR("cax-dw"))) {
            __auto_type _mv_251 = ({ __auto_type _lst = witnesses; size_t _idx = (size_t)2; slop_option_rdf_Triple _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
            if (_mv_251.has_value) {
                __auto_type dj_witness = _mv_251.value;
                {
                    __auto_type class_a = rdf_triple_subject(dj_witness);
                    __auto_type class_b = rdf_triple_object(dj_witness);
                    __auto_type _mv_252 = class_a;
                    switch (_mv_252.tag) {
                        case rdf_Term_term_iri:
                        {
                            __auto_type iri_a = _mv_252.data.term_iri;
                            __auto_type _mv_253 = class_b;
                            switch (_mv_253.tag) {
                                case rdf_Term_term_iri:
                                {
                                    __auto_type iri_b = _mv_253.data.term_iri;
                                    {
                                        __auto_type detail = string_concat(arena, iri_a.value, string_concat(arena, SLOP_STR(" disjointWith "), iri_b.value));
                                        __auto_type _mv_254 = ({ __auto_type _lst = witnesses; size_t _idx = (size_t)0; slop_option_rdf_Triple _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                        if (_mv_254.has_value) {
                                            __auto_type first_witness = _mv_254.value;
                                            {
                                                __auto_type subj = rdf_triple_subject(first_witness);
                                                __auto_type _mv_255 = subj;
                                                switch (_mv_255.tag) {
                                                    case rdf_Term_term_blank:
                                                    {
                                                        __auto_type bnode = _mv_255.data.term_blank;
                                                        {
                                                            __auto_type class_name = engine_resolve_blank_class(arena, bnode.id, class_map);
                                                            __auto_type prop_name = engine_resolve_blank_prop(arena, bnode.id, prop_map);
                                                            __auto_type enriched = engine_build_enriched_reason(arena, class_name, prop_name, original_reason, detail);
                                                            if ((string_len(prop_name) > 0)) {
                                                                {
                                                                    __auto_type blank_id = bnode.id;
                                                                    __auto_type prop_index = (((blank_id < 30000000)) ? (blank_id - 20000000) : (blank_id - 30000000));
                                                                    int64_t domain_count = 0;
                                                                    __auto_type _mv_256 = ({ __auto_type _lst = prop_map; size_t _idx = (size_t)prop_index; slop_option_rdf_Term _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                                    if (_mv_256.has_value) {
                                                                        __auto_type prop_term = _mv_256.value;
                                                                        {
                                                                            __auto_type domain_pred = rdf_make_iri(arena, vocab_RDFS_DOMAIN);
                                                                            slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
                                                                            __auto_type domains = rdf_indexed_graph_match(arena, pre_inject_graph, (slop_option_rdf_Term){.has_value = 1, .value = prop_term}, (slop_option_rdf_Term){.has_value = 1, .value = domain_pred}, no_term);
                                                                            domain_count = ((int64_t)((domains).len));
                                                                        }
                                                                    } else if (!_mv_256.has_value) {
                                                                    }
                                                                    {
                                                                        __auto_type final_reason = (((domain_count > 1)) ? string_concat(arena, enriched, string_concat(arena, SLOP_STR("\n  Note: "), string_concat(arena, prop_name, string_concat(arena, SLOP_STR(" has "), string_concat(arena, int_to_string(arena, domain_count), SLOP_STR(" rdfs:domain declarations (OWL treats multiple domains as intersection, not union).\n  Consider using owl:unionOf if union semantics were intended.")))))) : enriched);
                                                                        return ((types_InconsistencyReport){.reason = final_reason, .witnesses = witnesses});
                                                                    }
                                                                }
                                                            } else {
                                                                return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                            }
                                                        }
                                                    }
                                                    default: {
                                                        {
                                                            __auto_type enriched = engine_build_enriched_reason(arena, SLOP_STR(""), SLOP_STR(""), original_reason, detail);
                                                            return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                        }
                                                    }
                                                }
                                            }
                                        } else if (!_mv_254.has_value) {
                                            {
                                                __auto_type enriched = engine_build_enriched_reason(arena, SLOP_STR(""), SLOP_STR(""), original_reason, detail);
                                                return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                            }
                                        }
                                    }
                                }
                                default: {
                                    return report;
                                }
                            }
                        }
                        default: {
                            return report;
                        }
                    }
                }
            } else if (!_mv_251.has_value) {
                return report;
            }
        } else {
            if (strlib_starts_with(original_reason, SLOP_STR("cax-adc"))) {
                __auto_type _mv_257 = ({ __auto_type _lst = witnesses; size_t _idx = (size_t)0; slop_option_rdf_Triple _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                if (_mv_257.has_value) {
                    __auto_type w0 = _mv_257.value;
                    __auto_type _mv_258 = ({ __auto_type _lst = witnesses; size_t _idx = (size_t)1; slop_option_rdf_Triple _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                    if (_mv_258.has_value) {
                        __auto_type w1 = _mv_258.value;
                        {
                            __auto_type class_a = rdf_triple_object(w0);
                            __auto_type class_b = rdf_triple_object(w1);
                            __auto_type subj = rdf_triple_subject(w0);
                            __auto_type _mv_259 = class_a;
                            switch (_mv_259.tag) {
                                case rdf_Term_term_iri:
                                {
                                    __auto_type iri_a = _mv_259.data.term_iri;
                                    __auto_type _mv_260 = class_b;
                                    switch (_mv_260.tag) {
                                        case rdf_Term_term_iri:
                                        {
                                            __auto_type iri_b = _mv_260.data.term_iri;
                                            {
                                                __auto_type detail = string_concat(arena, iri_a.value, string_concat(arena, SLOP_STR(" disjointWith "), string_concat(arena, iri_b.value, SLOP_STR(" (via AllDisjointClasses)"))));
                                                __auto_type _mv_261 = subj;
                                                switch (_mv_261.tag) {
                                                    case rdf_Term_term_blank:
                                                    {
                                                        __auto_type bnode = _mv_261.data.term_blank;
                                                        {
                                                            __auto_type class_name = engine_resolve_blank_class(arena, bnode.id, class_map);
                                                            __auto_type prop_name = engine_resolve_blank_prop(arena, bnode.id, prop_map);
                                                            __auto_type enriched = engine_build_enriched_reason(arena, class_name, prop_name, original_reason, detail);
                                                            return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                        }
                                                    }
                                                    default: {
                                                        {
                                                            __auto_type enriched = engine_build_enriched_reason(arena, SLOP_STR(""), SLOP_STR(""), original_reason, detail);
                                                            return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        default: {
                                            return report;
                                        }
                                    }
                                }
                                default: {
                                    return report;
                                }
                            }
                        }
                    } else if (!_mv_258.has_value) {
                        return report;
                    }
                } else if (!_mv_257.has_value) {
                    return report;
                }
            } else {
                __auto_type _mv_262 = ({ __auto_type _lst = witnesses; size_t _idx = (size_t)0; slop_option_rdf_Triple _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                if (_mv_262.has_value) {
                    __auto_type first_witness = _mv_262.value;
                    {
                        __auto_type subj = rdf_triple_subject(first_witness);
                        __auto_type _mv_263 = subj;
                        switch (_mv_263.tag) {
                            case rdf_Term_term_blank:
                            {
                                __auto_type bnode = _mv_263.data.term_blank;
                                {
                                    __auto_type class_name = engine_resolve_blank_class(arena, bnode.id, class_map);
                                    __auto_type prop_name = engine_resolve_blank_prop(arena, bnode.id, prop_map);
                                    if ((string_len(class_name) > 0)) {
                                        {
                                            __auto_type enriched = engine_build_enriched_reason(arena, class_name, SLOP_STR(""), original_reason, SLOP_STR(""));
                                            return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                        }
                                    } else {
                                        if ((string_len(prop_name) > 0)) {
                                            {
                                                __auto_type witness_pred = rdf_triple_predicate(first_witness);
                                                __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
                                                if (rdf_term_eq(witness_pred, type_pred)) {
                                                    {
                                                        __auto_type blank_id = bnode.id;
                                                        __auto_type prop_index = (((blank_id < 30000000)) ? (blank_id - 20000000) : (blank_id - 30000000));
                                                        __auto_type _mv_264 = ({ __auto_type _lst = prop_map; size_t _idx = (size_t)prop_index; slop_option_rdf_Term _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                        if (_mv_264.has_value) {
                                                            __auto_type prop = _mv_264.value;
                                                            {
                                                                __auto_type domain_or_range_pred = rdf_make_iri(arena, (((blank_id < 30000000)) ? vocab_RDFS_DOMAIN : vocab_RDFS_RANGE));
                                                                slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
                                                                __auto_type class_triples = rdf_indexed_graph_match(arena, pre_inject_graph, (slop_option_rdf_Term){.has_value = 1, .value = prop}, (slop_option_rdf_Term){.has_value = 1, .value = domain_or_range_pred}, no_term);
                                                                __auto_type _mv_265 = ({ __auto_type _lst = class_triples; size_t _idx = (size_t)0; slop_option_rdf_Triple _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                                                                if (_mv_265.has_value) {
                                                                    __auto_type class_triple = _mv_265.value;
                                                                    {
                                                                        __auto_type cls = rdf_triple_object(class_triple);
                                                                        if (engine_iri_matches_ns(cls, validate_ns)) {
                                                                            __auto_type _mv_266 = cls;
                                                                            switch (_mv_266.tag) {
                                                                                case rdf_Term_term_iri:
                                                                                {
                                                                                    __auto_type iri = _mv_266.data.term_iri;
                                                                                    {
                                                                                        __auto_type enriched = engine_build_enriched_reason(arena, iri.value, SLOP_STR(""), original_reason, SLOP_STR(""));
                                                                                        return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                                                    }
                                                                                }
                                                                                default: {
                                                                                    return report;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            {
                                                                                __auto_type enriched = engine_build_enriched_reason(arena, SLOP_STR(""), prop_name, original_reason, SLOP_STR(""));
                                                                                return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                                            }
                                                                        }
                                                                    }
                                                                } else if (!_mv_265.has_value) {
                                                                    {
                                                                        __auto_type enriched = engine_build_enriched_reason(arena, SLOP_STR(""), prop_name, original_reason, SLOP_STR(""));
                                                                        return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                                    }
                                                                }
                                                            }
                                                        } else if (!_mv_264.has_value) {
                                                            return report;
                                                        }
                                                    }
                                                } else {
                                                    {
                                                        __auto_type enriched = engine_build_enriched_reason(arena, SLOP_STR(""), prop_name, original_reason, SLOP_STR(""));
                                                        return ((types_InconsistencyReport){.reason = enriched, .witnesses = witnesses});
                                                    }
                                                }
                                            }
                                        } else {
                                            return report;
                                        }
                                    }
                                }
                            }
                            default: {
                                return report;
                            }
                        }
                    }
                } else if (!_mv_262.has_value) {
                    return report;
                }
            }
        }
    }
}

slop_list_types_InconsistencyReport engine_validate_check_all(slop_arena* arena, index_IndexedGraph g, index_IndexedGraph pre_inject_graph, slop_string validate_ns, slop_list_rdf_Term class_map, slop_list_rdf_Term prop_map) {
    {
        __auto_type reports = ((slop_list_types_InconsistencyReport){ .data = (types_InconsistencyReport*)slop_arena_alloc(arena, 16 * sizeof(types_InconsistencyReport)), .len = 0, .cap = 16 });
        __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE);
        __auto_type nothing_class = rdf_make_iri(arena, vocab_OWL_NOTHING);
        __auto_type disjoint_pred = rdf_make_iri(arena, vocab_OWL_DISJOINT_WITH);
        __auto_type complement_pred = rdf_make_iri(arena, vocab_OWL_COMPLEMENT_OF);
        __auto_type asymm_type = rdf_make_iri(arena, vocab_OWL_ASYMMETRIC_PROPERTY);
        __auto_type pdw_pred = rdf_make_iri(arena, vocab_OWL_PROPERTY_DISJOINT_WITH);
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        {
            int64_t i = 0;
            __auto_type class_count = ((int64_t)((class_map).len));
            while ((i < class_count)) {
                __auto_type _mv_267 = ({ __auto_type _lst = class_map; size_t _idx = (size_t)i; slop_option_rdf_Term _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                if (_mv_267.has_value) {
                    __auto_type cls = _mv_267.value;
                    {
                        __auto_type blank_id = (10000000 + i);
                        __auto_type blank = rdf_make_blank(arena, blank_id);
                        __auto_type types = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = blank}, (slop_option_rdf_Term){.has_value = 1, .value = type_pred}, no_term);
                        uint8_t found = 0;
                        if (!(found)) {
                            {
                                __auto_type _coll = types;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type tt = _coll.data[_i];
                                    if ((!(found) && rdf_term_eq(tt.object, nothing_class))) {
                                        found = 1;
                                        {
                                            __auto_type raw_report = ((types_InconsistencyReport){.reason = SLOP_STR("cls-nothing2: individual is member of owl:Nothing"), .witnesses = ({ __auto_type wl = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }); ({ __auto_type _lst_p = &(wl); __auto_type _item = (tt); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); wl; })});
                                            ({ __auto_type _lst_p = &(reports); __auto_type _item = (engine_enrich_validate_report(arena, raw_report, pre_inject_graph, validate_ns, class_map, prop_map)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                        }
                                    }
                                }
                            }
                        }
                        if (!(found)) {
                            {
                                __auto_type _coll = types;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type tt = _coll.data[_i];
                                    if (!(found)) {
                                        {
                                            __auto_type cls_type = tt.object;
                                            __auto_type dj_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = cls_type}, (slop_option_rdf_Term){.has_value = 1, .value = disjoint_pred}, no_term);
                                            {
                                                __auto_type _coll = dj_triples;
                                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                                    __auto_type dj = _coll.data[_i];
                                                    if (!(found)) {
                                                        {
                                                            __auto_type other_cls = dj.object;
                                                            __auto_type type_check_triple = rdf_make_triple(arena, blank, type_pred, other_cls);
                                                            if (rdf_indexed_graph_contains(g, type_check_triple)) {
                                                                found = 1;
                                                                {
                                                                    __auto_type witness_type_other = rdf_make_triple(arena, blank, type_pred, other_cls);
                                                                    __auto_type wl = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
                                                                    ({ __auto_type _lst_p = &(wl); __auto_type _item = (tt); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                    ({ __auto_type _lst_p = &(wl); __auto_type _item = (witness_type_other); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                    ({ __auto_type _lst_p = &(wl); __auto_type _item = (dj); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                    {
                                                                        __auto_type raw_report = ((types_InconsistencyReport){.reason = SLOP_STR("cax-dw: disjoint classes have common individual"), .witnesses = wl});
                                                                        ({ __auto_type _lst_p = &(reports); __auto_type _item = (engine_enrich_validate_report(arena, raw_report, pre_inject_graph, validate_ns, class_map, prop_map)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
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
                        if (!(found)) {
                            {
                                __auto_type _coll = types;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type tt = _coll.data[_i];
                                    if (!(found)) {
                                        {
                                            __auto_type cls_type = tt.object;
                                            __auto_type comp_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = cls_type}, (slop_option_rdf_Term){.has_value = 1, .value = complement_pred}, no_term);
                                            {
                                                __auto_type _coll = comp_triples;
                                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                                    __auto_type ct = _coll.data[_i];
                                                    if (!(found)) {
                                                        {
                                                            __auto_type comp_cls = ct.object;
                                                            __auto_type type_check_triple = rdf_make_triple(arena, blank, type_pred, comp_cls);
                                                            if (rdf_indexed_graph_contains(g, type_check_triple)) {
                                                                found = 1;
                                                                {
                                                                    __auto_type wl = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
                                                                    ({ __auto_type _lst_p = &(wl); __auto_type _item = (tt); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                    ({ __auto_type _lst_p = &(wl); __auto_type _item = (rdf_make_triple(arena, blank, type_pred, comp_cls)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                                    {
                                                                        __auto_type raw_report = ((types_InconsistencyReport){.reason = SLOP_STR("cls-com: individual is member of class and its complement"), .witnesses = wl});
                                                                        ({ __auto_type _lst_p = &(reports); __auto_type _item = (engine_enrich_validate_report(arena, raw_report, pre_inject_graph, validate_ns, class_map, prop_map)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
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
                } else if (!_mv_267.has_value) {
                }
                i = (i + 1);
            }
        }
        {
            int64_t j = 0;
            __auto_type prop_count = ((int64_t)((prop_map).len));
            while ((j < prop_count)) {
                __auto_type _mv_268 = ({ __auto_type _lst = prop_map; size_t _idx = (size_t)j; slop_option_rdf_Term _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                if (_mv_268.has_value) {
                    __auto_type prop = _mv_268.value;
                    {
                        __auto_type subj_blank = rdf_make_blank(arena, (20000000 + j));
                        __auto_type obj_blank = rdf_make_blank(arena, (30000000 + j));
                        uint8_t found = 0;
                        if (!(found)) {
                            {
                                __auto_type asymm_check = rdf_make_triple(arena, prop, type_pred, asymm_type);
                                if (rdf_indexed_graph_contains(g, asymm_check)) {
                                    {
                                        __auto_type reverse_triple = rdf_make_triple(arena, obj_blank, prop, subj_blank);
                                        if (rdf_indexed_graph_contains(g, reverse_triple)) {
                                            found = 1;
                                            {
                                                __auto_type wl = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
                                                ({ __auto_type _lst_p = &(wl); __auto_type _item = (rdf_make_triple(arena, subj_blank, prop, obj_blank)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                ({ __auto_type _lst_p = &(wl); __auto_type _item = (reverse_triple); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                {
                                                    __auto_type raw_report = ((types_InconsistencyReport){.reason = SLOP_STR("prp-asyp: asymmetric property used symmetrically"), .witnesses = wl});
                                                    ({ __auto_type _lst_p = &(reports); __auto_type _item = (engine_enrich_validate_report(arena, raw_report, pre_inject_graph, validate_ns, class_map, prop_map)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (!(found)) {
                            {
                                __auto_type pdw_triples = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = prop}, (slop_option_rdf_Term){.has_value = 1, .value = pdw_pred}, no_term);
                                {
                                    __auto_type _coll = pdw_triples;
                                    for (size_t _i = 0; _i < _coll.len; _i++) {
                                        __auto_type pdw = _coll.data[_i];
                                        if (!(found)) {
                                            {
                                                __auto_type other_prop = pdw.object;
                                                __auto_type other_triple = rdf_make_triple(arena, subj_blank, other_prop, obj_blank);
                                                if (rdf_indexed_graph_contains(g, other_triple)) {
                                                    found = 1;
                                                    {
                                                        __auto_type wl = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
                                                        ({ __auto_type _lst_p = &(wl); __auto_type _item = (rdf_make_triple(arena, subj_blank, prop, obj_blank)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                        ({ __auto_type _lst_p = &(wl); __auto_type _item = (other_triple); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                        ({ __auto_type _lst_p = &(wl); __auto_type _item = (pdw); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                        {
                                                            __auto_type raw_report = ((types_InconsistencyReport){.reason = SLOP_STR("prp-pdw: property disjoint with another property used on same individuals"), .witnesses = wl});
                                                            ({ __auto_type _lst_p = &(reports); __auto_type _item = (engine_enrich_validate_report(arena, raw_report, pre_inject_graph, validate_ns, class_map, prop_map)); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
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
                } else if (!_mv_268.has_value) {
                }
                j = (j + 1);
            }
        }
        return reports;
    }
}

types_ReasonerResult engine_engine_run(slop_arena* arena, types_ReasonerConfig config, index_IndexedGraph initial) {
    SLOP_PRE(((config.worker_count >= 1)), "(>= (. config worker-count) 1)");
    SLOP_PRE(((config.max_iterations >= 1)), "(>= (. config max-iterations) 1)");
    SLOP_PRE(((rdf_indexed_graph_size(initial) >= 0)), "(>= (indexed-graph-size initial) 0)");
    types_ReasonerResult _retval = {0};
    {
        __auto_type initial_size = rdf_indexed_graph_size(initial);
        __auto_type initial_delta = engine_make_initial_delta(arena, initial);
        __auto_type materialized_graph = ((config.fast) ? initial : engine_schema_materialize(arena, initial, engine_make_initial_delta(arena, initial), config));
        __auto_type dt_graph = ((config.fast) ? materialized_graph : ({ __auto_type mg = materialized_graph; ({ __auto_type _coll = dt_dt_type1(arena, mg); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ mg = rdf_indexed_graph_add(arena, mg, t); (void)0; }); } 0; }); mg; }));
        __auto_type complete_graph = (((!(config.fast) && config.complete)) ? ({ __auto_type cg = dt_graph; ({ __auto_type _coll = prp_prp_ap(arena, cg); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ cg = rdf_indexed_graph_add(arena, cg, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_thing(arena, cg); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ cg = rdf_indexed_graph_add(arena, cg, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_nothing1(arena, cg); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ cg = rdf_indexed_graph_add(arena, cg, t); (void)0; }); } 0; }); ({ __auto_type _coll = dt_dt_type2(arena, cg); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ cg = rdf_indexed_graph_add(arena, cg, t); (void)0; }); } 0; }); ({ __auto_type thing = rdf_make_iri(arena, vocab_OWL_THING); __auto_type nothing = rdf_make_iri(arena, vocab_OWL_NOTHING); __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF); __auto_type equiv_pred = rdf_make_iri(arena, vocab_OWL_EQUIVALENT_CLASS); ({ cg = rdf_indexed_graph_add(arena, cg, rdf_make_triple(arena, thing, subclass_pred, thing)); (void)0; }); ({ cg = rdf_indexed_graph_add(arena, cg, rdf_make_triple(arena, thing, equiv_pred, thing)); (void)0; }); ({ cg = rdf_indexed_graph_add(arena, cg, rdf_make_triple(arena, nothing, subclass_pred, nothing)); (void)0; }); ({ cg = rdf_indexed_graph_add(arena, cg, rdf_make_triple(arena, nothing, equiv_pred, nothing)); (void)0; }); ({ cg = rdf_indexed_graph_add(arena, cg, rdf_make_triple(arena, nothing, subclass_pred, thing)); (void)0; }); }); ({ __auto_type same_as = rdf_make_iri(arena, vocab_OWL_SAME_AS); ({ cg = rdf_indexed_graph_add(arena, cg, rdf_make_triple(arena, same_as, same_as, same_as)); (void)0; }); }); ({ __auto_type type_pred = rdf_make_iri(arena, vocab_RDF_TYPE); ({ cg = rdf_indexed_graph_add(arena, cg, rdf_make_triple(arena, rdf_make_iri(arena, vocab_OWL_DIFFERENT_FROM), type_pred, rdf_make_iri(arena, vocab_OWL_SYMMETRIC_PROPERTY))); (void)0; }); }); cg; }) : dt_graph);
        __auto_type validate_injection = ((config.validate) ? engine_inject_validate_instances(arena, complete_graph, config.verbose, config.validate_ns) : ((engine_ValidateInjection){.graph = complete_graph, .class_map = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 }), .prop_map = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 })}));
        __auto_type validate_graph = validate_injection.graph;
        __auto_type validate_class_map = validate_injection.class_map;
        __auto_type validate_prop_map = validate_injection.prop_map;
        __auto_type fixpoint_delta = ((config.validate) ? engine_make_initial_delta(arena, validate_graph) : initial_delta);
        __auto_type state = ((types_EngineState){.graph = validate_graph, .delta = fixpoint_delta, .iteration = 0, .config = config});
        uint8_t done = 0;
        slop_option_types_InconsistencyReport inconsistency = (slop_option_types_InconsistencyReport){.has_value = false};
        slop_option_types_InconsistencyReport dt_report = (slop_option_types_InconsistencyReport){.has_value = false};
        if (!(config.fast)) {
            __auto_type _mv_269 = dt_dt_not_type(arena, state.graph);
            if (_mv_269.has_value) {
                __auto_type report = _mv_269.value;
                if (config.validate) {
                    dt_report = (slop_option_types_InconsistencyReport){.has_value = 1, .value = report};
                } else {
                    {
                        __auto_type reports = ((slop_list_types_InconsistencyReport){ .data = (types_InconsistencyReport*)slop_arena_alloc(arena, 16 * sizeof(types_InconsistencyReport)), .len = 0, .cap = 16 });
                        ({ __auto_type _lst_p = &(reports); __auto_type _item = (report); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_inconsistent, .data.reason_inconsistent = reports });
                    }
                }
            } else if (!_mv_269.has_value) {
            }
        }
        while ((!(done) && (state.iteration < config.max_iterations))) {
            if (config.verbose) {
                printf("%s", "[iter ");
                printf("%.*s", (int)(int_to_string(arena, state.iteration)).len, (int_to_string(arena, state.iteration)).data);
                printf("%s", "] graph=");
                printf("%.*s", (int)(int_to_string(arena, rdf_indexed_graph_size(state.graph))).len, (int_to_string(arena, rdf_indexed_graph_size(state.graph))).data);
                printf("%s\n", "");
            }
            __auto_type _mv_270 = engine_engine_run_iteration(arena, state);
            if (_mv_270.is_ok) {
                __auto_type new_state = _mv_270.data.ok;
                state = new_state;
                if (types_delta_is_empty(new_state.delta)) {
                    done = 1;
                }
            } else if (!_mv_270.is_ok) {
                __auto_type report = _mv_270.data.err;
                done = 1;
                inconsistency = (slop_option_types_InconsistencyReport){.has_value = 1, .value = report};
            }
        }
        if (config.validate) {
            __auto_type _mv_271 = inconsistency;
            if (_mv_271.has_value) {
                __auto_type report = _mv_271.value;
                {
                    __auto_type reports = ((slop_list_types_InconsistencyReport){ .data = (types_InconsistencyReport*)slop_arena_alloc(arena, 16 * sizeof(types_InconsistencyReport)), .len = 0, .cap = 16 });
                    __auto_type enriched = engine_enrich_validate_report(arena, report, complete_graph, config.validate_ns, validate_class_map, validate_prop_map);
                    ({ __auto_type _lst_p = &(reports); __auto_type _item = (enriched); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                    return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_inconsistent, .data.reason_inconsistent = reports });
                }
            } else if (!_mv_271.has_value) {
                {
                    __auto_type all_reports = engine_validate_check_all(arena, state.graph, complete_graph, config.validate_ns, validate_class_map, validate_prop_map);
                    __auto_type _mv_272 = dt_report;
                    if (_mv_272.has_value) {
                        __auto_type dt_r = _mv_272.value;
                        {
                            __auto_type combined = ((slop_list_types_InconsistencyReport){ .data = (types_InconsistencyReport*)slop_arena_alloc(arena, 16 * sizeof(types_InconsistencyReport)), .len = 0, .cap = 16 });
                            ({ __auto_type _lst_p = &(combined); __auto_type _item = (dt_r); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            {
                                __auto_type _coll = all_reports;
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type r = _coll.data[_i];
                                    ({ __auto_type _lst_p = &(combined); __auto_type _item = (r); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                }
                            }
                            if ((((int64_t)((combined).len)) > 0)) {
                                return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_inconsistent, .data.reason_inconsistent = combined });
                            } else {
                                return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_success, .data.reason_success = ((types_ReasonerSuccess){.graph = state.graph, .inferred_count = (rdf_indexed_graph_size(state.graph) - initial_size), .iterations = state.iteration}) });
                            }
                        }
                    } else if (!_mv_272.has_value) {
                        if ((((int64_t)((all_reports).len)) > 0)) {
                            return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_inconsistent, .data.reason_inconsistent = all_reports });
                        } else {
                            return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_success, .data.reason_success = ((types_ReasonerSuccess){.graph = state.graph, .inferred_count = (rdf_indexed_graph_size(state.graph) - initial_size), .iterations = state.iteration}) });
                        }
                    }
                }
            }
        } else {
            __auto_type _mv_273 = inconsistency;
            if (_mv_273.has_value) {
                __auto_type report = _mv_273.value;
                {
                    __auto_type reports = ((slop_list_types_InconsistencyReport){ .data = (types_InconsistencyReport*)slop_arena_alloc(arena, 16 * sizeof(types_InconsistencyReport)), .len = 0, .cap = 16 });
                    ({ __auto_type _lst_p = &(reports); __auto_type _item = (report); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                    return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_inconsistent, .data.reason_inconsistent = reports });
                }
            } else if (!_mv_273.has_value) {
                {
                    __auto_type final_graph = state.graph;
                    if (config.complete) {
                        {
                            __auto_type full_delta = engine_make_initial_delta(arena, final_graph);
                            {
                                __auto_type _coll = eq_eq_ref(arena, final_graph, full_delta);
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type t = _coll.data[_i];
                                    final_graph = rdf_indexed_graph_add(arena, final_graph, t);
                                }
                            }
                        }
                    }
                    return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_success, .data.reason_success = ((types_ReasonerSuccess){.graph = final_graph, .inferred_count = (rdf_indexed_graph_size(final_graph) - initial_size), .iterations = state.iteration}) });
                }
            }
        }
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr = {0}; switch (_mv.tag) { case types_ReasonerResult_reason_success: { __auto_type s = _mv.data.reason_success; _mr = (s.iterations <= config.max_iterations); break; } case types_ReasonerResult_reason_inconsistent: { __auto_type _ = _mv.data.reason_inconsistent; _mr = 1; break; }  } _mr; })), "(match $result ((reason-success s) (<= (. s iterations) (. config max-iterations))) ((reason-inconsistent _) true))");
    return _retval;
}

types_Delta engine_make_initial_delta(slop_arena* arena, index_IndexedGraph g) {
    types_Delta _retval = {0};
    {
        __auto_type d = types_make_delta(arena, 0);
        rdf_indexed_graph_for_each(g, ((slop_option_rdf_Term){.has_value = false}), ((slop_option_rdf_Term){.has_value = false}), ((slop_option_rdf_Term){.has_value = false}), ({ engine__lambda_274_env_t* engine__lambda_274_env = (engine__lambda_274_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_274_env_t)); *engine__lambda_274_env = (engine__lambda_274_env_t){ .d = &(d), .arena = arena }; (slop_closure_t){ (void*)engine__lambda_274, (void*)engine__lambda_274_env }; }));
        _retval = d;
    }
    SLOP_POST(((_retval.iteration == 0)), "(== (. $result iteration) 0)");
    return _retval;
}

slop_list_rdf_Triple engine_compute_tc(slop_arena* arena, index_IndexedGraph g, rdf_Term pred) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        slop_option_rdf_Term no_term = (slop_option_rdf_Term){.has_value = false};
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type all_pred_triples = rdf_indexed_graph_match(arena, g, no_term, (slop_option_rdf_Term){.has_value = 1, .value = pred}, no_term);
        __auto_type all_subjects = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type seen_subjects = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
        {
            __auto_type _coll = all_pred_triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                {
                    __auto_type s = rdf_triple_subject(t);
                    if (!((slop_map_get(seen_subjects, &(s)) != NULL))) {
                        ({ uint8_t _dummy = 1; slop_map_put(arena, seen_subjects, &(s), &_dummy); });
                        ({ __auto_type _lst_p = &(all_subjects); __auto_type _item = (s); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                    }
                }
            }
        }
        {
            __auto_type _coll = all_subjects;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type start = _coll.data[_i];
                {
                    __auto_type bfs_visited = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type bfs_queue = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
                    {
                        __auto_type direct_parents = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = start}, (slop_option_rdf_Term){.has_value = 1, .value = pred}, no_term);
                        {
                            __auto_type _coll = direct_parents;
                            for (size_t _i = 0; _i < _coll.len; _i++) {
                                __auto_type t = _coll.data[_i];
                                {
                                    __auto_type parent = rdf_triple_object(t);
                                    if (!((slop_map_get(bfs_visited, &(parent)) != NULL))) {
                                        ({ uint8_t _dummy = 1; slop_map_put(arena, bfs_visited, &(parent), &_dummy); });
                                        ({ __auto_type _lst_p = &(bfs_queue); __auto_type _item = (parent); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    }
                    {
                        int64_t qi = 0;
                        while ((qi < ((int64_t)((bfs_queue).len)))) {
                            __auto_type _mv_275 = ({ __auto_type _lst = bfs_queue; size_t _idx = (size_t)qi; slop_option_rdf_Term _r = {0}; if (_idx < _lst.len) { _r.has_value = true; _r.value = _lst.data[_idx]; } else { _r.has_value = false; } _r; });
                            if (_mv_275.has_value) {
                                __auto_type current = _mv_275.value;
                                {
                                    __auto_type inferred = rdf_make_triple(arena, start, pred, current);
                                    if (!(rdf_indexed_graph_contains(g, inferred))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (inferred); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                                {
                                    __auto_type parents = rdf_indexed_graph_match(arena, g, (slop_option_rdf_Term){.has_value = 1, .value = current}, (slop_option_rdf_Term){.has_value = 1, .value = pred}, no_term);
                                    {
                                        __auto_type _coll = parents;
                                        for (size_t _i = 0; _i < _coll.len; _i++) {
                                            __auto_type t = _coll.data[_i];
                                            {
                                                __auto_type parent = rdf_triple_object(t);
                                                if (!((slop_map_get(bfs_visited, &(parent)) != NULL))) {
                                                    ({ uint8_t _dummy = 1; slop_map_put(arena, bfs_visited, &(parent), &_dummy); });
                                                    ({ __auto_type _lst_p = &(bfs_queue); __auto_type _item = (parent); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                                }
                                            }
                                        }
                                    }
                                }
                            } else if (!_mv_275.has_value) {
                            }
                            qi = (qi + 1);
                        }
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

index_IndexedGraph engine_schema_materialize(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config) {
    {
        __auto_type graph = g;
        __auto_type verbose = config.verbose;
        __auto_type subclass_pred = rdf_make_iri(arena, vocab_RDFS_SUBCLASS_OF);
        __auto_type subprop_pred = rdf_make_iri(arena, vocab_RDFS_SUBPROPERTY_OF);
        if (verbose) {
            printf("%s\n", "[schema] phased materialization");
        }
        {
            __auto_type t0 = slop_now_ms();
            int64_t count = 0;
            {
                __auto_type _coll = scm_scm_cls(arena, graph, delta);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_op(arena, graph, delta);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_dp(arena, graph, delta);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            if (verbose) {
                printf("%s", "[schema] phase 1 (bootstrap): +");
                printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                printf("%s", " triples (");
                engine_print_ms(arena, (slop_now_ms() - t0));
                printf("%s\n", ")");
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type full_d = engine_make_initial_delta(arena, graph);
            int64_t count = 0;
            {
                __auto_type _coll = scm_scm_eqc1(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_eqc1b(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_eqp1(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_eqp1b(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_int(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_uni(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            if (verbose) {
                printf("%s", "[schema] phase 2 (edges): +");
                printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                printf("%s", " triples (");
                engine_print_ms(arena, (slop_now_ms() - t0));
                printf("%s\n", ")");
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            int64_t count = 0;
            {
                __auto_type _coll = engine_compute_tc(arena, graph, subclass_pred);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = engine_compute_tc(arena, graph, subprop_pred);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            if (verbose) {
                printf("%s", "[schema] phase 3 (TC): +");
                printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                printf("%s", " triples (");
                engine_print_ms(arena, (slop_now_ms() - t0));
                printf("%s\n", ")");
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type full_d = engine_make_initial_delta(arena, graph);
            int64_t count = 0;
            {
                __auto_type _coll = scm_scm_eqc2(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_eqp2(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            if (verbose) {
                printf("%s", "[schema] phase 3b (mutual-eq): +");
                printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                printf("%s", " triples (");
                engine_print_ms(arena, (slop_now_ms() - t0));
                printf("%s\n", ")");
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type full_d = engine_make_initial_delta(arena, graph);
            int64_t count = 0;
            {
                __auto_type _coll = scm_scm_dom1(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_dom2(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_rng1(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            {
                __auto_type _coll = scm_scm_rng2(arena, graph, full_d);
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    graph = rdf_indexed_graph_add(arena, graph, t);
                    count = (count + 1);
                }
            }
            if (verbose) {
                printf("%s", "[schema] phase 4 (dom/rng): +");
                printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                printf("%s", " triples (");
                engine_print_ms(arena, (slop_now_ms() - t0));
                printf("%s\n", ")");
            }
        }
        {
            uint8_t phase_done = 0;
            int64_t phase_iter = 0;
            __auto_type struct_delta = engine_make_initial_delta(arena, graph);
            while ((!(phase_done) && (phase_iter < config.max_iterations))) {
                {
                    __auto_type t0 = slop_now_ms();
                    int64_t count = 0;
                    __auto_type new_delta = types_make_delta(arena, 0);
                    {
                        __auto_type _coll = scm_scm_svf1(arena, graph, struct_delta);
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            graph = rdf_indexed_graph_add(arena, graph, t);
                            new_delta = types_delta_add(arena, new_delta, t);
                            count = (count + 1);
                        }
                    }
                    {
                        __auto_type _coll = scm_scm_svf2(arena, graph, struct_delta);
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            graph = rdf_indexed_graph_add(arena, graph, t);
                            new_delta = types_delta_add(arena, new_delta, t);
                            count = (count + 1);
                        }
                    }
                    {
                        __auto_type _coll = scm_scm_avf1(arena, graph, struct_delta);
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            graph = rdf_indexed_graph_add(arena, graph, t);
                            new_delta = types_delta_add(arena, new_delta, t);
                            count = (count + 1);
                        }
                    }
                    {
                        __auto_type _coll = scm_scm_avf2(arena, graph, struct_delta);
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            graph = rdf_indexed_graph_add(arena, graph, t);
                            new_delta = types_delta_add(arena, new_delta, t);
                            count = (count + 1);
                        }
                    }
                    {
                        __auto_type _coll = scm_scm_hv(arena, graph, struct_delta);
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            graph = rdf_indexed_graph_add(arena, graph, t);
                            new_delta = types_delta_add(arena, new_delta, t);
                            count = (count + 1);
                        }
                    }
                    if (verbose) {
                        printf("%s", "[schema] phase 5 (structural iter ");
                        printf("%.*s", (int)(int_to_string(arena, phase_iter)).len, (int_to_string(arena, phase_iter)).data);
                        printf("%s", "): +");
                        printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                        printf("%s", " triples (");
                        engine_print_ms(arena, (slop_now_ms() - t0));
                        printf("%s\n", ")");
                    }
                    if ((count == 0)) {
                        phase_done = 1;
                    } else {
                        {
                            __auto_type t1 = slop_now_ms();
                            int64_t tc_count = 0;
                            {
                                __auto_type _coll = engine_compute_tc(arena, graph, subclass_pred);
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type t = _coll.data[_i];
                                    graph = rdf_indexed_graph_add(arena, graph, t);
                                    new_delta = types_delta_add(arena, new_delta, t);
                                    tc_count = (tc_count + 1);
                                }
                            }
                            {
                                __auto_type _coll = engine_compute_tc(arena, graph, subprop_pred);
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type t = _coll.data[_i];
                                    graph = rdf_indexed_graph_add(arena, graph, t);
                                    new_delta = types_delta_add(arena, new_delta, t);
                                    tc_count = (tc_count + 1);
                                }
                            }
                            if (verbose) {
                                printf("%s", "[schema] phase 6 (re-TC): +");
                                printf("%.*s", (int)(int_to_string(arena, tc_count)).len, (int_to_string(arena, tc_count)).data);
                                printf("%s", " triples (");
                                engine_print_ms(arena, (slop_now_ms() - t1));
                                printf("%s\n", ")");
                            }
                        }
                        {
                            __auto_type t2 = slop_now_ms();
                            int64_t prop_count = 0;
                            {
                                __auto_type _coll = scm_scm_dom1(arena, graph, new_delta);
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type t = _coll.data[_i];
                                    graph = rdf_indexed_graph_add(arena, graph, t);
                                    prop_count = (prop_count + 1);
                                }
                            }
                            {
                                __auto_type _coll = scm_scm_dom2(arena, graph, new_delta);
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type t = _coll.data[_i];
                                    graph = rdf_indexed_graph_add(arena, graph, t);
                                    prop_count = (prop_count + 1);
                                }
                            }
                            {
                                __auto_type _coll = scm_scm_rng1(arena, graph, new_delta);
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type t = _coll.data[_i];
                                    graph = rdf_indexed_graph_add(arena, graph, t);
                                    prop_count = (prop_count + 1);
                                }
                            }
                            {
                                __auto_type _coll = scm_scm_rng2(arena, graph, new_delta);
                                for (size_t _i = 0; _i < _coll.len; _i++) {
                                    __auto_type t = _coll.data[_i];
                                    graph = rdf_indexed_graph_add(arena, graph, t);
                                    prop_count = (prop_count + 1);
                                }
                            }
                            if (verbose) {
                                printf("%s", "[schema] phase 6 (re-prop): +");
                                printf("%.*s", (int)(int_to_string(arena, prop_count)).len, (int_to_string(arena, prop_count)).data);
                                printf("%s", " triples (");
                                engine_print_ms(arena, (slop_now_ms() - t2));
                                printf("%s\n", ")");
                            }
                        }
                        struct_delta = new_delta;
                    }
                }
                phase_iter = (phase_iter + 1);
            }
        }
        if (config.complete) {
            {
                __auto_type t0 = slop_now_ms();
                __auto_type full_d = engine_make_initial_delta(arena, graph);
                int64_t count = 0;
                {
                    __auto_type _coll = scm_scm_eqc2(arena, graph, full_d);
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type t = _coll.data[_i];
                        graph = rdf_indexed_graph_add(arena, graph, t);
                        count = (count + 1);
                    }
                }
                {
                    __auto_type _coll = scm_scm_eqp2(arena, graph, full_d);
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type t = _coll.data[_i];
                        graph = rdf_indexed_graph_add(arena, graph, t);
                        count = (count + 1);
                    }
                }
                if (verbose) {
                    printf("%s", "[schema] phase 7 (mutual-eq complete): +");
                    printf("%.*s", (int)(int_to_string(arena, count)).len, (int_to_string(arena, count)).data);
                    printf("%s", " triples (");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", ")");
                }
            }
        }
        if (verbose) {
            printf("%s", "[schema] done, graph=");
            printf("%.*s", (int)(int_to_string(arena, rdf_indexed_graph_size(graph))).len, (int_to_string(arena, rdf_indexed_graph_size(graph))).data);
            printf("%s\n", "");
        }
        return graph;
    }
}

slop_result_types_EngineState_types_InconsistencyReport engine_engine_run_iteration(slop_arena* arena, types_EngineState state) {
    SLOP_PRE(((state.iteration >= 0)), "(>= (. state iteration) 0)");
    slop_result_types_EngineState_types_InconsistencyReport _retval = {0};
    __auto_type _mv_276 = engine_apply_all_rules(arena, state.graph, state.delta, state.config);
    if (_mv_276.is_ok) {
        __auto_type new_delta = _mv_276.data.ok;
        {
            __auto_type new_graph = engine_merge_into_graph(arena, state.graph, new_delta);
            if (!(state.config.fast)) {
                {
                    __auto_type _coll = eq_eq_ref(arena, new_graph, new_delta);
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type t = _coll.data[_i];
                        new_graph = rdf_indexed_graph_add(arena, new_graph, t);
                    }
                }
            }
            return ((slop_result_types_EngineState_types_InconsistencyReport){ .is_ok = true, .data.ok = ((types_EngineState){.graph = new_graph, .delta = new_delta, .iteration = (state.iteration + 1), .config = state.config}) });
        }
    } else if (!_mv_276.is_ok) {
        __auto_type report = _mv_276.data.err;
        return ((slop_result_types_EngineState_types_InconsistencyReport){ .is_ok = false, .data.err = report });
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type new_state = _mv.data.ok; _mr = (new_state.iteration == (state.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok new-state) (== (. new-state iteration) (+ (. state iteration) 1))) ((error _) true))");
    return _retval;
}

slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval = {0};
    if (((config.worker_count <= 1) || (delta.iteration == 0))) {
        _retval = engine_apply_all_rules_sequential(arena, g, delta, config);
    } else {
        _retval = engine_apply_all_rules_parallel(arena, g, delta, config);
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == (delta.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) (+ (. delta iteration) 1))) ((error _) true))");
    return _retval;
}

slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_sequential(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval = {0};
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type combined = types_make_delta(arena, next_iter);
        __auto_type verbose = config.verbose;
        __auto_type fast = config.fast;
        {
            __auto_type t0 = slop_now_ms();
            __auto_type validate = config.validate;
            __auto_type _mv_277 = cax_apply_cax_rules(arena, g, delta, fast, validate);
            if (_mv_277.is_ok) {
                __auto_type cax_delta = _mv_277.data.ok;
                if (verbose) {
                    printf("%s", "  cax: ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, cax_delta);
            } else if (!_mv_277.is_ok) {
                __auto_type report = _mv_277.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type validate = config.validate;
            __auto_type _mv_278 = prp_apply_prp_rules(arena, g, delta, fast, validate);
            if (_mv_278.is_ok) {
                __auto_type prp_delta = _mv_278.data.ok;
                if (verbose) {
                    printf("%s", "  prp: ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, prp_delta);
            } else if (!_mv_278.is_ok) {
                __auto_type report = _mv_278.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type validate = config.validate;
            __auto_type _mv_279 = eq_apply_eq_rules(arena, g, delta, fast, validate);
            if (_mv_279.is_ok) {
                __auto_type eq_delta = _mv_279.data.ok;
                if (verbose) {
                    printf("%s", "  eq:  ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, eq_delta);
            } else if (!_mv_279.is_ok) {
                __auto_type report = _mv_279.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type validate = config.validate;
            __auto_type _mv_280 = cls_apply_cls_rules(arena, g, delta, fast, validate);
            if (_mv_280.is_ok) {
                __auto_type cls_delta = _mv_280.data.ok;
                if (verbose) {
                    printf("%s", "  cls: ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, cls_delta);
            } else if (!_mv_280.is_ok) {
                __auto_type report = _mv_280.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        _retval = ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = true, .data.ok = combined });
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == (delta.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) (+ (. delta iteration) 1))) ((error _) true))");
    return _retval;
}

slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_parallel(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    SLOP_PRE(((config.worker_count > 1)), "(> (. config worker-count) 1)");
    slop_result_types_Delta_types_InconsistencyReport _retval = {0};
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type fast = config.fast;
        __auto_type result_chan = (slop_chan_engine_WorkerMessage*)thread_chan_buffered(arena, config.channel_buffer);
        __auto_type arena_cax_infer = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_cax_check = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_prp_char = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_prp_chain = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_prp_check = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_eq_infer = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_eq_check = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(((fast) ? 64 : 1048576)); _new_arena; });
        __auto_type arena_cls_set = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_cls_ind = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        {
            __auto_type workers = engine_spawn_rule_workers(arena, g, delta, result_chan, arena_cax_infer, arena_cax_check, arena_prp_char, arena_prp_chain, arena_prp_check, arena_eq_infer, arena_eq_check, arena_cls_set, arena_cls_ind, config.verbose, fast, config.validate);
            {
                __auto_type result = engine_collect_worker_results(arena, result_chan, workers, next_iter);
                __auto_type _mv_281 = result;
                if (_mv_281.is_ok) {
                    __auto_type _ = _mv_281.data.ok;
                    ({ slop_arena_free(arena_cax_infer); free(arena_cax_infer); });
                    ({ slop_arena_free(arena_cax_check); free(arena_cax_check); });
                    ({ slop_arena_free(arena_prp_char); free(arena_prp_char); });
                    ({ slop_arena_free(arena_prp_chain); free(arena_prp_chain); });
                    ({ slop_arena_free(arena_prp_check); free(arena_prp_check); });
                    ({ slop_arena_free(arena_eq_infer); free(arena_eq_infer); });
                    ({ slop_arena_free(arena_eq_check); free(arena_eq_check); });
                    ({ slop_arena_free(arena_cls_set); free(arena_cls_set); });
                    ({ slop_arena_free(arena_cls_ind); free(arena_cls_ind); });
                } else if (!_mv_281.is_ok) {
                    __auto_type _ = _mv_281.data.err;
                }
                _retval = result;
            }
        }
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == (delta.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) (+ (. delta iteration) 1))) ((error _) true))");
    return _retval;
}

index_IndexedGraph engine_merge_into_graph(slop_arena* arena, index_IndexedGraph g, types_Delta d) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    index_IndexedGraph _retval = {0};
    {
        __auto_type result = g;
        {
            __auto_type _coll = d.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                result = rdf_indexed_graph_add(arena, result, t);
            }
        }
        _retval = result;
    }
    SLOP_POST(((rdf_indexed_graph_size(_retval) >= rdf_indexed_graph_size(g))), "(>= (indexed-graph-size $result) (indexed-graph-size g))");
    SLOP_POST(((rdf_indexed_graph_size(_retval) <= (rdf_indexed_graph_size(g) + ((int64_t)((d.triples).len))))), "(<= (indexed-graph-size $result) (+ (indexed-graph-size g) (list-len (. d triples))))");
    return _retval;
}

slop_list_thread_int_ptr engine_spawn_rule_workers(slop_arena* arena, index_IndexedGraph g, types_Delta delta, slop_chan_engine_WorkerMessage* result_chan, slop_arena* arena_cax_infer, slop_arena* arena_cax_check, slop_arena* arena_prp_char, slop_arena* arena_prp_chain, slop_arena* arena_prp_check, slop_arena* arena_eq_infer, slop_arena* arena_eq_check, slop_arena* arena_cls_set, slop_arena* arena_cls_ind, uint8_t verbose, uint8_t fast, uint8_t validate) {
    {
        __auto_type workers = ((slop_list_thread_int_ptr){ .data = (slop_thread_int**)slop_arena_alloc(arena, 16 * sizeof(slop_thread_int*)), .len = 0, .cap = 16 });
        __auto_type next_iter = (delta.iteration + 1);
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_282_env_t* engine__lambda_282_env = (engine__lambda_282_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_282_env_t)); *engine__lambda_282_env = (engine__lambda_282_env_t){ .arena_cax_infer = arena_cax_infer, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_282, (void*)engine__lambda_282_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        if (!(validate)) {
            ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_283_env_t* engine__lambda_283_env = (engine__lambda_283_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_283_env_t)); *engine__lambda_283_env = (engine__lambda_283_env_t){ .arena_cax_check = arena_cax_check, .g = g, .delta = delta, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_283, (void*)engine__lambda_283_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        }
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_284_env_t* engine__lambda_284_env = (engine__lambda_284_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_284_env_t)); *engine__lambda_284_env = (engine__lambda_284_env_t){ .arena_prp_char = arena_prp_char, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_284, (void*)engine__lambda_284_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_285_env_t* engine__lambda_285_env = (engine__lambda_285_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_285_env_t)); *engine__lambda_285_env = (engine__lambda_285_env_t){ .arena_prp_chain = arena_prp_chain, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_285, (void*)engine__lambda_285_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        if (!(validate)) {
            ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_286_env_t* engine__lambda_286_env = (engine__lambda_286_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_286_env_t)); *engine__lambda_286_env = (engine__lambda_286_env_t){ .arena_prp_check = arena_prp_check, .g = g, .delta = delta, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_286, (void*)engine__lambda_286_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        }
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_287_env_t* engine__lambda_287_env = (engine__lambda_287_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_287_env_t)); *engine__lambda_287_env = (engine__lambda_287_env_t){ .arena_eq_infer = arena_eq_infer, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_287, (void*)engine__lambda_287_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        if ((!(fast) && !(validate))) {
            ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_288_env_t* engine__lambda_288_env = (engine__lambda_288_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_288_env_t)); *engine__lambda_288_env = (engine__lambda_288_env_t){ .arena_eq_check = arena_eq_check, .g = g, .delta = delta, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_288, (void*)engine__lambda_288_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        }
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_289_env_t* engine__lambda_289_env = (engine__lambda_289_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_289_env_t)); *engine__lambda_289_env = (engine__lambda_289_env_t){ .arena_cls_set = arena_cls_set, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_289, (void*)engine__lambda_289_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_290_env_t* engine__lambda_290_env = (engine__lambda_290_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_290_env_t)); *engine__lambda_290_env = (engine__lambda_290_env_t){ .arena_cls_ind = arena_cls_ind, .next_iter = next_iter, .g = g, .delta = delta, .fast = fast, .validate = validate, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_290, (void*)engine__lambda_290_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        return workers;
    }
}

slop_result_types_Delta_types_InconsistencyReport engine_collect_worker_results(slop_arena* arena, slop_chan_engine_WorkerMessage* result_chan, slop_list_thread_int_ptr workers, int64_t next_iter) {
    SLOP_PRE(((((int64_t)((workers).len)) >= 1)), "(>= (list-len workers) 1)");
    SLOP_PRE(((next_iter >= 1)), "(>= next-iter 1)");
    slop_result_types_Delta_types_InconsistencyReport _retval = {0};
    {
        __auto_type combined = types_make_delta(arena, next_iter);
        slop_option_types_InconsistencyReport inconsistency = (slop_option_types_InconsistencyReport){.has_value = false};
        int64_t done_count = 0;
        __auto_type expected = ((int64_t)((workers).len));
        while ((done_count < expected)) {
            __auto_type _mv_291 = thread_recv_slop_chan_engine_WorkerMessage(result_chan);
            if (_mv_291.is_ok) {
                __auto_type msg = _mv_291.data.ok;
                __auto_type _mv_292 = msg;
                switch (_mv_292.tag) {
                    case engine_WorkerMessage_msg_delta:
                    {
                        __auto_type d = _mv_292.data.msg_delta;
                        combined = types_delta_merge(arena, combined, d);
                        break;
                    }
                    case engine_WorkerMessage_msg_inconsistent:
                    {
                        __auto_type r = _mv_292.data.msg_inconsistent;
                        inconsistency = (slop_option_types_InconsistencyReport){.has_value = 1, .value = r};
                        break;
                    }
                    case engine_WorkerMessage_msg_done:
                    {
                        __auto_type _ = _mv_292.data.msg_done;
                        done_count = (done_count + 1);
                        break;
                    }
                }
            } else if (!_mv_291.is_ok) {
                __auto_type _ = _mv_291.data.err;
                done_count = expected;
            }
        }
        {
            __auto_type _coll = workers;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type w = _coll.data[_i];
                thread_join(w);
            }
        }
        __auto_type _mv_293 = inconsistency;
        if (_mv_293.has_value) {
            __auto_type r = _mv_293.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = r });
        } else if (!_mv_293.has_value) {
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = true, .data.ok = combined });
        }
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == next_iter); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) next-iter)) ((error _) true))");
    return _retval;
}

