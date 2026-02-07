#include "../runtime/slop_runtime.h"
#include "slop_engine.h"

void engine_print_ms(slop_arena* arena, int64_t ms);
types_ReasonerResult engine_engine_run(slop_arena* arena, types_ReasonerConfig config, index_IndexedGraph initial);
types_Delta engine_make_initial_delta(slop_arena* arena, index_IndexedGraph g);
slop_result_types_EngineState_types_InconsistencyReport engine_engine_run_iteration(slop_arena* arena, types_EngineState state);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_sequential(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_parallel(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
index_IndexedGraph engine_merge_into_graph(slop_arena* arena, index_IndexedGraph g, types_Delta d);
slop_list_thread_int_ptr engine_spawn_rule_workers(slop_arena* arena, index_IndexedGraph g, types_Delta delta, slop_chan_engine_WorkerMessage* result_chan, slop_arena* arena_scm_class, slop_arena* arena_scm_prop, slop_arena* arena_scm_domrng, slop_arena* arena_cax_infer, slop_arena* arena_cax_check, slop_arena* arena_prp_char, slop_arena* arena_prp_chain, slop_arena* arena_prp_check, slop_arena* arena_eq_infer, slop_arena* arena_eq_check, slop_arena* arena_cls_set, slop_arena* arena_cls_ind, uint8_t verbose);
slop_result_types_Delta_types_InconsistencyReport engine_collect_worker_results(slop_arena* arena, slop_chan_engine_WorkerMessage* result_chan, slop_list_thread_int_ptr workers, int64_t next_iter);

typedef struct { types_Delta* d; slop_arena* arena; } engine__lambda_150_env_t;

static void engine__lambda_150(engine__lambda_150_env_t* _env, rdf_Triple t) { ({ (*_env->d) = types_delta_add(_env->arena, (*_env->d), t); (void)0; }); }

typedef struct { slop_arena* arena_scm_class; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_157_env_t;

static slop_result_void_thread_ChanError engine__lambda_157(engine__lambda_157_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_scm_class, _env->next_iter); ({ __auto_type _coll = scm_scm_cls(_env->arena_scm_class, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_class, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_sco(_env->arena_scm_class, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_class, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_eqc1(_env->arena_scm_class, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_class, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_eqc2(_env->arena_scm_class, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_class, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  scm-class: "); engine_print_ms(_env->arena_scm_class, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_scm_prop; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_158_env_t;

static slop_result_void_thread_ChanError engine__lambda_158(engine__lambda_158_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_scm_prop, _env->next_iter); ({ __auto_type _coll = scm_scm_op(_env->arena_scm_prop, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_prop, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_dp(_env->arena_scm_prop, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_prop, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_spo(_env->arena_scm_prop, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_prop, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_eqp1(_env->arena_scm_prop, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_prop, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_eqp2(_env->arena_scm_prop, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_prop, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  scm-prop: "); engine_print_ms(_env->arena_scm_prop, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_scm_domrng; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_159_env_t;

static slop_result_void_thread_ChanError engine__lambda_159(engine__lambda_159_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_scm_domrng, _env->next_iter); ({ __auto_type _coll = scm_scm_dom1(_env->arena_scm_domrng, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_domrng, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_dom2(_env->arena_scm_domrng, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_domrng, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_rng1(_env->arena_scm_domrng, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_domrng, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = scm_scm_rng2(_env->arena_scm_domrng, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_scm_domrng, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  scm-domrng: "); engine_print_ms(_env->arena_scm_domrng, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_cax_infer; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_160_env_t;

static slop_result_void_thread_ChanError engine__lambda_160(engine__lambda_160_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_cax_infer, _env->next_iter); ({ __auto_type _coll = cax_cax_sco(_env->arena_cax_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cax_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cax_cax_eqc1(_env->arena_cax_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cax_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cax_cax_eqc2(_env->arena_cax_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cax_infer, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  cax-infer: "); engine_print_ms(_env->arena_cax_infer, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_cax_check; index_IndexedGraph g; types_Delta delta; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_161_env_t;

static slop_result_void_thread_ChanError engine__lambda_161(engine__lambda_161_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); ({ __auto_type _mv = cax_cax_dw(_env->arena_cax_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ __auto_type _mv = cax_cax_adc(_env->arena_cax_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ (void)0; })); })); }); ((_env->verbose) ? ({ ({ printf("%s", "  cax-check: "); engine_print_ms(_env->arena_cax_check, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_prp_char; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_162_env_t;

static slop_result_void_thread_ChanError engine__lambda_162(engine__lambda_162_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_prp_char, _env->next_iter); ({ __auto_type _coll = prp_prp_dom(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_rng(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_fp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_ifp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_symp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_trp(_env->arena_prp_char, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_char, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  prp-char: "); engine_print_ms(_env->arena_prp_char, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_prp_chain; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_163_env_t;

static slop_result_void_thread_ChanError engine__lambda_163(engine__lambda_163_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_prp_chain, _env->next_iter); ({ __auto_type _coll = prp_prp_spo1(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_eqp1(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_eqp2(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_inv1(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = prp_prp_inv2(_env->arena_prp_chain, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_prp_chain, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  prp-chain: "); engine_print_ms(_env->arena_prp_chain, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_prp_check; index_IndexedGraph g; types_Delta delta; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_164_env_t;

static slop_result_void_thread_ChanError engine__lambda_164(engine__lambda_164_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); ({ __auto_type _mv = prp_prp_asyp(_env->arena_prp_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ __auto_type _mv = prp_prp_irp(_env->arena_prp_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ __auto_type _mv = prp_prp_pdw(_env->arena_prp_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ (void)0; })); })); })); }); ((_env->verbose) ? ({ ({ printf("%s", "  prp-check: "); engine_print_ms(_env->arena_prp_check, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_eq_infer; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_165_env_t;

static slop_result_void_thread_ChanError engine__lambda_165(engine__lambda_165_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_eq_infer, _env->next_iter); ({ __auto_type _coll = eq_eq_sym(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_trans(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_rep_s(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_rep_p(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = eq_eq_rep_o(_env->arena_eq_infer, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_eq_infer, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  eq-infer: "); engine_print_ms(_env->arena_eq_infer, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_eq_check; index_IndexedGraph g; types_Delta delta; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_166_env_t;

static slop_result_void_thread_ChanError engine__lambda_166(engine__lambda_166_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); ({ __auto_type _mv = eq_eq_diff1(_env->arena_eq_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ __auto_type _mv = eq_eq_diff2(_env->arena_eq_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ __auto_type _mv = eq_eq_diff3(_env->arena_eq_check, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ (void)0; })); })); })); }); ((_env->verbose) ? ({ ({ printf("%s", "  eq-check: "); engine_print_ms(_env->arena_eq_check, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_cls_set; int64_t next_iter; index_IndexedGraph g; types_Delta delta; uint8_t verbose; slop_chan_engine_WorkerMessage* result_chan; } engine__lambda_167_env_t;

static slop_result_void_thread_ChanError engine__lambda_167(engine__lambda_167_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_cls_set, _env->next_iter); ({ __auto_type _coll = cls_cls_int1(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_int2(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_uni(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_svf1(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_svf2(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_avf(_env->arena_cls_set, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_set, result, t); (void)0; }); } 0; }); ((_env->verbose) ? ({ ({ printf("%s", "  cls-set: "); engine_print_ms(_env->arena_cls_set, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

typedef struct { slop_arena* arena_cls_ind; int64_t next_iter; index_IndexedGraph g; types_Delta delta; slop_chan_engine_WorkerMessage* result_chan; uint8_t verbose; } engine__lambda_168_env_t;

static slop_result_void_thread_ChanError engine__lambda_168(engine__lambda_168_env_t* _env) { return ({ __auto_type t0 = slop_now_ms(); __auto_type result = types_make_delta(_env->arena_cls_ind, _env->next_iter); ({ __auto_type _coll = cls_cls_hv1(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_hv2(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_maxc1(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_maxc2(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ({ __auto_type _coll = cls_cls_oo(_env->arena_cls_ind, _env->g, _env->delta); for (size_t _i = 0; _i < _coll.len; _i++) { __auto_type t = _coll.data[_i]; ({ result = types_delta_add(_env->arena_cls_ind, result, t); (void)0; }); } 0; }); ({ __auto_type _mv = cls_cls_nothing2(_env->arena_cls_ind, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ __auto_type _mv = cls_cls_com(_env->arena_cls_ind, _env->g, _env->delta); _mv.has_value ? ({ __auto_type report = _mv.value; thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_inconsistent, .data.msg_inconsistent = report })); }) : (({ (void)0; })); })); }); ((_env->verbose) ? ({ ({ printf("%s", "  cls-ind: "); engine_print_ms(_env->arena_cls_ind, (slop_now_ms() - t0)); printf("%s\n", ""); }); 0; }) : ({ (void)0; })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_delta, .data.msg_delta = result })); thread_send_slop_chan_engine_WorkerMessage(_env->result_chan, ((engine_WorkerMessage){ .tag = engine_WorkerMessage_msg_done, .data.msg_done = 0 })); }); }

void engine_print_ms(slop_arena* arena, int64_t ms) {
    printf("%.*s", (int)(int_to_string(arena, ms)).len, (int_to_string(arena, ms)).data);
    printf("%s", "ms");
}

types_ReasonerResult engine_engine_run(slop_arena* arena, types_ReasonerConfig config, index_IndexedGraph initial) {
    SLOP_PRE(((config.worker_count >= 1)), "(>= (. config worker-count) 1)");
    SLOP_PRE(((config.max_iterations >= 1)), "(>= (. config max-iterations) 1)");
    SLOP_PRE(((rdf_indexed_graph_size(initial) >= 0)), "(>= (indexed-graph-size initial) 0)");
    types_ReasonerResult _retval;
    {
        __auto_type initial_size = rdf_indexed_graph_size(initial);
        __auto_type state = ((types_EngineState){.graph = initial, .delta = engine_make_initial_delta(arena, initial), .iteration = 0, .config = config});
        uint8_t done = 0;
        slop_option_types_InconsistencyReport inconsistency = (slop_option_types_InconsistencyReport){.has_value = false};
        while ((!(done) && (state.iteration < config.max_iterations))) {
            0;
            if (config.verbose) {
                printf("%s", "[iter ");
                printf("%.*s", (int)(int_to_string(arena, state.iteration)).len, (int_to_string(arena, state.iteration)).data);
                printf("%s", "] graph=");
                printf("%.*s", (int)(int_to_string(arena, rdf_indexed_graph_size(state.graph))).len, (int_to_string(arena, rdf_indexed_graph_size(state.graph))).data);
                printf("%s\n", "");
            }
            __auto_type _mv_148 = engine_engine_run_iteration(arena, state);
            if (_mv_148.is_ok) {
                __auto_type new_state = _mv_148.data.ok;
                if (types_delta_is_empty(new_state.delta)) {
                    done = 1;
                } else {
                    state = new_state;
                }
            } else if (!_mv_148.is_ok) {
                __auto_type report = _mv_148.data.err;
                done = 1;
                inconsistency = (slop_option_types_InconsistencyReport){.has_value = 1, .value = report};
            }
        }
        __auto_type _mv_149 = inconsistency;
        if (_mv_149.has_value) {
            __auto_type report = _mv_149.value;
            return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_inconsistent, .data.reason_inconsistent = report });
        } else if (!_mv_149.has_value) {
            return ((types_ReasonerResult){ .tag = types_ReasonerResult_reason_success, .data.reason_success = ((types_ReasonerSuccess){.graph = state.graph, .inferred_count = (rdf_indexed_graph_size(state.graph) - initial_size), .iterations = state.iteration}) });
        }
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr = {0}; switch (_mv.tag) { case types_ReasonerResult_reason_success: { __auto_type s = _mv.data.reason_success; _mr = (s.iterations <= config.max_iterations); break; } case types_ReasonerResult_reason_inconsistent: { __auto_type _ = _mv.data.reason_inconsistent; _mr = 1; break; }  } _mr; })), "(match $result ((reason-success s) (<= (. s iterations) (. config max-iterations))) ((reason-inconsistent _) true))");
    return _retval;
}

types_Delta engine_make_initial_delta(slop_arena* arena, index_IndexedGraph g) {
    types_Delta _retval;
    {
        __auto_type d = types_make_delta(arena, 0);
        rdf_indexed_graph_for_each(g, ((slop_option_rdf_Term){.has_value = false}), ((slop_option_rdf_Term){.has_value = false}), ((slop_option_rdf_Term){.has_value = false}), ({ engine__lambda_150_env_t* engine__lambda_150_env = (engine__lambda_150_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_150_env_t)); *engine__lambda_150_env = (engine__lambda_150_env_t){ .d = &(d), .arena = arena }; (slop_closure_t){ (void*)engine__lambda_150, (void*)engine__lambda_150_env }; }));
        _retval = d;
    }
    SLOP_POST(((_retval.iteration == 0)), "(== (. $result iteration) 0)");
    return _retval;
}

slop_result_types_EngineState_types_InconsistencyReport engine_engine_run_iteration(slop_arena* arena, types_EngineState state) {
    SLOP_PRE(((state.iteration >= 0)), "(>= (. state iteration) 0)");
    slop_result_types_EngineState_types_InconsistencyReport _retval;
    __auto_type _mv_151 = engine_apply_all_rules(arena, state.graph, state.delta, state.config);
    if (_mv_151.is_ok) {
        __auto_type new_delta = _mv_151.data.ok;
        return ((slop_result_types_EngineState_types_InconsistencyReport){ .is_ok = true, .data.ok = ((types_EngineState){.graph = engine_merge_into_graph(arena, state.graph, new_delta), .delta = new_delta, .iteration = (state.iteration + 1), .config = state.config}) });
    } else if (!_mv_151.is_ok) {
        __auto_type report = _mv_151.data.err;
        return ((slop_result_types_EngineState_types_InconsistencyReport){ .is_ok = false, .data.err = report });
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type new_state = _mv.data.ok; _mr = (new_state.iteration == (state.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok new-state) (== (. new-state iteration) (+ (. state iteration) 1))) ((error _) true))");
    return _retval;
}

slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    slop_result_types_Delta_types_InconsistencyReport _retval;
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
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type combined = types_make_delta(arena, next_iter);
        __auto_type verbose = config.verbose;
        {
            __auto_type t0 = slop_now_ms();
            __auto_type _mv_152 = scm_apply_scm_rules(arena, g, delta);
            if (_mv_152.is_ok) {
                __auto_type scm_delta = _mv_152.data.ok;
                if (verbose) {
                    printf("%s", "  scm: ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, scm_delta);
            } else if (!_mv_152.is_ok) {
                __auto_type report = _mv_152.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type _mv_153 = cax_apply_cax_rules(arena, g, delta);
            if (_mv_153.is_ok) {
                __auto_type cax_delta = _mv_153.data.ok;
                if (verbose) {
                    printf("%s", "  cax: ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, cax_delta);
            } else if (!_mv_153.is_ok) {
                __auto_type report = _mv_153.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type _mv_154 = prp_apply_prp_rules(arena, g, delta);
            if (_mv_154.is_ok) {
                __auto_type prp_delta = _mv_154.data.ok;
                if (verbose) {
                    printf("%s", "  prp: ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, prp_delta);
            } else if (!_mv_154.is_ok) {
                __auto_type report = _mv_154.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type _mv_155 = eq_apply_eq_rules(arena, g, delta);
            if (_mv_155.is_ok) {
                __auto_type eq_delta = _mv_155.data.ok;
                if (verbose) {
                    printf("%s", "  eq:  ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, eq_delta);
            } else if (!_mv_155.is_ok) {
                __auto_type report = _mv_155.data.err;
                return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = report });
            }
        }
        {
            __auto_type t0 = slop_now_ms();
            __auto_type _mv_156 = cls_apply_cls_rules(arena, g, delta);
            if (_mv_156.is_ok) {
                __auto_type cls_delta = _mv_156.data.ok;
                if (verbose) {
                    printf("%s", "  cls: ");
                    engine_print_ms(arena, (slop_now_ms() - t0));
                    printf("%s\n", "");
                }
                combined = types_delta_merge(arena, combined, cls_delta);
            } else if (!_mv_156.is_ok) {
                __auto_type report = _mv_156.data.err;
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
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type next_iter = (delta.iteration + 1);
        __auto_type result_chan = (slop_chan_engine_WorkerMessage*)thread_chan_buffered(arena, config.channel_buffer);
        __auto_type arena_scm_class = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_scm_prop = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_scm_domrng = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_cax_infer = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_cax_check = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_prp_char = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_prp_chain = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_prp_check = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_eq_infer = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_eq_check = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_cls_set = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        __auto_type arena_cls_ind = ({ slop_arena* _new_arena = malloc(sizeof(slop_arena)); if (!_new_arena) { fprintf(stderr, "SLOP: arena-new malloc failed\n"); abort(); } *_new_arena = slop_arena_new(1048576); _new_arena; });
        {
            __auto_type workers = engine_spawn_rule_workers(arena, g, delta, result_chan, arena_scm_class, arena_scm_prop, arena_scm_domrng, arena_cax_infer, arena_cax_check, arena_prp_char, arena_prp_chain, arena_prp_check, arena_eq_infer, arena_eq_check, arena_cls_set, arena_cls_ind, config.verbose);
            {
                __auto_type result = engine_collect_worker_results(arena, result_chan, workers, next_iter);
                ({ slop_arena_free(arena_scm_class); free(arena_scm_class); });
                ({ slop_arena_free(arena_scm_prop); free(arena_scm_prop); });
                ({ slop_arena_free(arena_scm_domrng); free(arena_scm_domrng); });
                ({ slop_arena_free(arena_cax_infer); free(arena_cax_infer); });
                ({ slop_arena_free(arena_cax_check); free(arena_cax_check); });
                ({ slop_arena_free(arena_prp_char); free(arena_prp_char); });
                ({ slop_arena_free(arena_prp_chain); free(arena_prp_chain); });
                ({ slop_arena_free(arena_prp_check); free(arena_prp_check); });
                ({ slop_arena_free(arena_eq_infer); free(arena_eq_infer); });
                ({ slop_arena_free(arena_eq_check); free(arena_eq_check); });
                ({ slop_arena_free(arena_cls_set); free(arena_cls_set); });
                ({ slop_arena_free(arena_cls_ind); free(arena_cls_ind); });
                _retval = result;
            }
        }
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == (delta.iteration + 1)); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) (+ (. delta iteration) 1))) ((error _) true))");
    return _retval;
}

index_IndexedGraph engine_merge_into_graph(slop_arena* arena, index_IndexedGraph g, types_Delta d) {
    SLOP_PRE(((rdf_indexed_graph_size(g) >= 0)), "(>= (indexed-graph-size g) 0)");
    index_IndexedGraph _retval;
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

slop_list_thread_int_ptr engine_spawn_rule_workers(slop_arena* arena, index_IndexedGraph g, types_Delta delta, slop_chan_engine_WorkerMessage* result_chan, slop_arena* arena_scm_class, slop_arena* arena_scm_prop, slop_arena* arena_scm_domrng, slop_arena* arena_cax_infer, slop_arena* arena_cax_check, slop_arena* arena_prp_char, slop_arena* arena_prp_chain, slop_arena* arena_prp_check, slop_arena* arena_eq_infer, slop_arena* arena_eq_check, slop_arena* arena_cls_set, slop_arena* arena_cls_ind, uint8_t verbose) {
    {
        __auto_type workers = ((slop_list_thread_int_ptr){ .data = (slop_thread_int**)slop_arena_alloc(arena, 16 * sizeof(slop_thread_int*)), .len = 0, .cap = 16 });
        __auto_type next_iter = (delta.iteration + 1);
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_157_env_t* engine__lambda_157_env = (engine__lambda_157_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_157_env_t)); *engine__lambda_157_env = (engine__lambda_157_env_t){ .arena_scm_class = arena_scm_class, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_157, (void*)engine__lambda_157_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_158_env_t* engine__lambda_158_env = (engine__lambda_158_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_158_env_t)); *engine__lambda_158_env = (engine__lambda_158_env_t){ .arena_scm_prop = arena_scm_prop, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_158, (void*)engine__lambda_158_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_159_env_t* engine__lambda_159_env = (engine__lambda_159_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_159_env_t)); *engine__lambda_159_env = (engine__lambda_159_env_t){ .arena_scm_domrng = arena_scm_domrng, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_159, (void*)engine__lambda_159_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_160_env_t* engine__lambda_160_env = (engine__lambda_160_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_160_env_t)); *engine__lambda_160_env = (engine__lambda_160_env_t){ .arena_cax_infer = arena_cax_infer, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_160, (void*)engine__lambda_160_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_161_env_t* engine__lambda_161_env = (engine__lambda_161_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_161_env_t)); *engine__lambda_161_env = (engine__lambda_161_env_t){ .arena_cax_check = arena_cax_check, .g = g, .delta = delta, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_161, (void*)engine__lambda_161_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_162_env_t* engine__lambda_162_env = (engine__lambda_162_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_162_env_t)); *engine__lambda_162_env = (engine__lambda_162_env_t){ .arena_prp_char = arena_prp_char, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_162, (void*)engine__lambda_162_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_163_env_t* engine__lambda_163_env = (engine__lambda_163_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_163_env_t)); *engine__lambda_163_env = (engine__lambda_163_env_t){ .arena_prp_chain = arena_prp_chain, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_163, (void*)engine__lambda_163_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_164_env_t* engine__lambda_164_env = (engine__lambda_164_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_164_env_t)); *engine__lambda_164_env = (engine__lambda_164_env_t){ .arena_prp_check = arena_prp_check, .g = g, .delta = delta, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_164, (void*)engine__lambda_164_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_165_env_t* engine__lambda_165_env = (engine__lambda_165_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_165_env_t)); *engine__lambda_165_env = (engine__lambda_165_env_t){ .arena_eq_infer = arena_eq_infer, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_165, (void*)engine__lambda_165_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_166_env_t* engine__lambda_166_env = (engine__lambda_166_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_166_env_t)); *engine__lambda_166_env = (engine__lambda_166_env_t){ .arena_eq_check = arena_eq_check, .g = g, .delta = delta, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_166, (void*)engine__lambda_166_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_167_env_t* engine__lambda_167_env = (engine__lambda_167_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_167_env_t)); *engine__lambda_167_env = (engine__lambda_167_env_t){ .arena_cls_set = arena_cls_set, .next_iter = next_iter, .g = g, .delta = delta, .verbose = verbose, .result_chan = result_chan }; (slop_closure_t){ (void*)engine__lambda_167, (void*)engine__lambda_167_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        ({ __auto_type _lst_p = &(workers); __auto_type _item = (({ slop_closure_t _spawn_cl = ({ engine__lambda_168_env_t* engine__lambda_168_env = (engine__lambda_168_env_t*)slop_arena_alloc(arena, sizeof(engine__lambda_168_env_t)); *engine__lambda_168_env = (engine__lambda_168_env_t){ .arena_cls_ind = arena_cls_ind, .next_iter = next_iter, .g = g, .delta = delta, .result_chan = result_chan, .verbose = verbose }; (slop_closure_t){ (void*)engine__lambda_168, (void*)engine__lambda_168_env }; }); slop_thread_int* _spawn_th = slop_arena_alloc(arena, sizeof(slop_thread_int)); _spawn_th->func = _spawn_cl.fn; _spawn_th->env = _spawn_cl.env; _spawn_th->done = false; pthread_create(&_spawn_th->id, NULL, (void*)slop_thread_int_entry, (void*)_spawn_th); _spawn_th; })); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        return workers;
    }
}

slop_result_types_Delta_types_InconsistencyReport engine_collect_worker_results(slop_arena* arena, slop_chan_engine_WorkerMessage* result_chan, slop_list_thread_int_ptr workers, int64_t next_iter) {
    SLOP_PRE(((((int64_t)((workers).len)) == 12)), "(== (list-len workers) 12)");
    SLOP_PRE(((next_iter >= 1)), "(>= next-iter 1)");
    slop_result_types_Delta_types_InconsistencyReport _retval;
    {
        __auto_type combined = types_make_delta(arena, next_iter);
        slop_option_types_InconsistencyReport inconsistency = (slop_option_types_InconsistencyReport){.has_value = false};
        int64_t done_count = 0;
        __auto_type expected = ((int64_t)((workers).len));
        while ((done_count < expected)) {
            __auto_type _mv_169 = thread_recv_slop_chan_engine_WorkerMessage(result_chan);
            if (_mv_169.is_ok) {
                __auto_type msg = _mv_169.data.ok;
                __auto_type _mv_170 = msg;
                switch (_mv_170.tag) {
                    case engine_WorkerMessage_msg_delta:
                    {
                        __auto_type d = _mv_170.data.msg_delta;
                        combined = types_delta_merge(arena, combined, d);
                        break;
                    }
                    case engine_WorkerMessage_msg_inconsistent:
                    {
                        __auto_type r = _mv_170.data.msg_inconsistent;
                        inconsistency = (slop_option_types_InconsistencyReport){.has_value = 1, .value = r};
                        break;
                    }
                    case engine_WorkerMessage_msg_done:
                    {
                        __auto_type _ = _mv_170.data.msg_done;
                        done_count = (done_count + 1);
                        break;
                    }
                }
            } else if (!_mv_169.is_ok) {
                __auto_type _ = _mv_169.data.err;
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
        __auto_type _mv_171 = inconsistency;
        if (_mv_171.has_value) {
            __auto_type r = _mv_171.value;
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = false, .data.err = r });
        } else if (!_mv_171.has_value) {
            return ((slop_result_types_Delta_types_InconsistencyReport){ .is_ok = true, .data.ok = combined });
        }
    }
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr; if (_mv.is_ok) { __auto_type d = _mv.data.ok; _mr = (d.iteration == next_iter); } else { __auto_type _ = _mv.data.err; _mr = 1; } _mr; })), "(match $result ((ok d) (== (. d iteration) next-iter)) ((error _) true))");
    return _retval;
}

