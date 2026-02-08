#ifndef SLOP_engine_H
#define SLOP_engine_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_vocab.h"
#include "slop_thread.h"
#include "slop_types.h"
#include "slop_cax.h"
#include "slop_scm.h"
#include "slop_prp.h"
#include "slop_eq.h"
#include "slop_cls.h"

typedef struct engine_WorkerMessage engine_WorkerMessage;

#ifndef SLOP_LIST_THREAD_INT_PTR_DEFINED
#define SLOP_LIST_THREAD_INT_PTR_DEFINED
SLOP_LIST_DEFINE(slop_thread_int*, slop_list_thread_int_ptr)
#endif

#ifndef SLOP_OPTION_THREAD_INT_PTR_DEFINED
#define SLOP_OPTION_THREAD_INT_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_thread_int*, slop_option_thread_int_ptr)
#endif

#ifndef SLOP_CHAN_ENGINE_WORKERMESSAGE_DEFINED
#define SLOP_CHAN_ENGINE_WORKERMESSAGE_DEFINED
typedef struct slop_chan_engine_WorkerMessage {
    uint8_t mutex[64];       /* pthread_mutex_t storage */
    uint8_t not_empty[64];   /* pthread_cond_t storage */
    uint8_t not_full[64];    /* pthread_cond_t storage */
    engine_WorkerMessage* buffer;         /* Ring buffer */
    size_t capacity;         /* Buffer capacity (0 = unbuffered) */
    size_t count;            /* Current item count */
    size_t head;             /* Read index */
    size_t tail;             /* Write index */
    bool closed;             /* Channel closed flag */
} slop_chan_engine_WorkerMessage;
#endif

#ifndef SLOP_THREAD_INT_DEFINED
#define SLOP_THREAD_INT_DEFINED
typedef struct slop_thread_int {
    pthread_t id;            /* pthread handle */
    int64_t result;          /* Thread return value */
    void* func;              /* Function pointer */
    void* env;               /* Closure environment */
    bool done;               /* Completion flag */
} slop_thread_int;
static void* slop_thread_int_entry(void* arg) {
    slop_thread_int* s = (slop_thread_int*)arg;
    if (s->env) {
        s->result = ((int64_t(*)(void*))(s->func))(s->env);
    } else {
        s->result = ((int64_t(*)(void))(s->func))();
    }
    s->done = true;
    return NULL;
}
#endif

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

typedef enum {
    engine_WorkerMessage_msg_delta,
    engine_WorkerMessage_msg_inconsistent,
    engine_WorkerMessage_msg_done
} engine_WorkerMessage_tag;

struct engine_WorkerMessage {
    engine_WorkerMessage_tag tag;
    union {
        types_Delta msg_delta;
        types_InconsistencyReport msg_inconsistent;
        int msg_done;
    } data;
};
typedef struct engine_WorkerMessage engine_WorkerMessage;

#ifndef SLOP_OPTION_ENGINE_WORKERMESSAGE_DEFINED
#define SLOP_OPTION_ENGINE_WORKERMESSAGE_DEFINED
SLOP_OPTION_DEFINE(engine_WorkerMessage, slop_option_engine_WorkerMessage)
#endif


/* Hash/eq functions and list types for struct map/set keys */
#ifndef RDF_TERM_HASH_EQ_DEFINED
#define RDF_TERM_HASH_EQ_DEFINED
#ifndef RDF_IRI_HASH_EQ_DEFINED
#define RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_IRI(const void* key) {
    const rdf_IRI* _k = (const rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_IRI(const void* a, const void* b) {
    const rdf_IRI* _a = (const rdf_IRI*)a;
    const rdf_IRI* _b = (const rdf_IRI*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
    ;
}
#endif
#ifndef RDF_BLANKNODE_HASH_EQ_DEFINED
#define RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_BlankNode(const void* key) {
    const rdf_BlankNode* _k = (const rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    { int64_t _tmp = (int64_t)_k->id; hash ^= slop_hash_int(&_tmp); hash *= 1099511628211ULL; }
    return hash;
}
static inline bool slop_eq_rdf_BlankNode(const void* a, const void* b) {
    const rdf_BlankNode* _a = (const rdf_BlankNode*)a;
    const rdf_BlankNode* _b = (const rdf_BlankNode*)b;
    return true
        && _a->id == _b->id
    ;
}
#endif
#ifndef RDF_LITERAL_HASH_EQ_DEFINED
#define RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_rdf_Literal(const void* key) {
    const rdf_Literal* _k = (const rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    { const uint8_t* _b = (const uint8_t*)&_k->datatype; for(size_t _i=0; _i<sizeof(_k->datatype); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    { const uint8_t* _b = (const uint8_t*)&_k->lang; for(size_t _i=0; _i<sizeof(_k->lang); _i++) { hash ^= _b[_i]; hash *= 1099511628211ULL; } }
    return hash;
}
static inline bool slop_eq_rdf_Literal(const void* a, const void* b) {
    const rdf_Literal* _a = (const rdf_Literal*)a;
    const rdf_Literal* _b = (const rdf_Literal*)b;
    return true
        && slop_eq_string(&_a->value, &_b->value)
        && memcmp(&_a->datatype, &_b->datatype, sizeof(_a->datatype)) == 0
        && memcmp(&_a->lang, &_b->lang, sizeof(_a->lang)) == 0
    ;
}
#endif
static inline uint64_t slop_hash_rdf_Term(const void* key) {
    const rdf_Term* _k = (const rdf_Term*)key;
    switch (_k->tag) {
        case rdf_Term_term_iri:
            return slop_hash_rdf_IRI(&_k->data.term_iri);
        case rdf_Term_term_blank:
            return slop_hash_rdf_BlankNode(&_k->data.term_blank);
        case rdf_Term_term_literal:
            return slop_hash_rdf_Literal(&_k->data.term_literal);
    }
    return 0;
}
static inline bool slop_eq_rdf_Term(const void* a, const void* b) {
    const rdf_Term* _a = (const rdf_Term*)a;
    const rdf_Term* _b = (const rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case rdf_Term_term_iri:
            return slop_eq_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case rdf_Term_term_blank:
            return slop_eq_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case rdf_Term_term_literal:
            return slop_eq_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
    }
    return false;
}
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif

#ifndef SLOP_RESULT_TYPES_ENGINESTATE_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_TYPES_ENGINESTATE_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { types_EngineState ok; types_InconsistencyReport err; } data; } slop_result_types_EngineState_types_InconsistencyReport;
#endif

#ifndef SLOP_RESULT_TYPES_DELTA_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_TYPES_DELTA_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { types_Delta ok; types_InconsistencyReport err; } data; } slop_result_types_Delta_types_InconsistencyReport;
#endif

#ifndef SLOP_RESULT_VOID_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_VOID_THREAD_CHANERROR_DEFINED
typedef struct slop_result_void_thread_ChanError {
    bool is_ok;
    union { uint8_t ok; thread_ChanError err; } data;
} slop_result_void_thread_ChanError;
#endif

#ifndef SLOP_RESULT_ENGINE_WORKERMESSAGE_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_ENGINE_WORKERMESSAGE_THREAD_CHANERROR_DEFINED
typedef struct slop_result_engine_WorkerMessage_thread_ChanError {
    bool is_ok;
    union { engine_WorkerMessage ok; thread_ChanError err; } data;
} slop_result_engine_WorkerMessage_thread_ChanError;
#endif

static slop_result_void_thread_ChanError thread_send_slop_chan_engine_WorkerMessage(slop_chan_engine_WorkerMessage* ch, engine_WorkerMessage value) {
    pthread_mutex_lock((pthread_mutex_t*)ch->mutex);
    if (ch->closed) {
        pthread_mutex_unlock((pthread_mutex_t*)ch->mutex);
        return (slop_result_void_thread_ChanError){.is_ok = 0, .data.err = thread_ChanError_send_on_closed};
    }
    if (ch->capacity == 0) {
        /* Unbuffered: synchronous handoff */
        while (ch->count > 0 && !ch->closed)
            pthread_cond_wait((pthread_cond_t*)ch->not_full, (pthread_mutex_t*)ch->mutex);
        if (ch->closed) {
            pthread_mutex_unlock((pthread_mutex_t*)ch->mutex);
            return (slop_result_void_thread_ChanError){.is_ok = 0, .data.err = thread_ChanError_send_on_closed};
        }
        /* Store value in single-element inline storage */
        if (!ch->buffer) ch->buffer = malloc(sizeof(engine_WorkerMessage));
        ch->buffer[0] = value;
        ch->count = 1;
        pthread_cond_signal((pthread_cond_t*)ch->not_empty);
        /* Wait for receiver to take it */
        while (ch->count > 0 && !ch->closed)
            pthread_cond_wait((pthread_cond_t*)ch->not_full, (pthread_mutex_t*)ch->mutex);
        pthread_mutex_unlock((pthread_mutex_t*)ch->mutex);
        return (slop_result_void_thread_ChanError){.is_ok = 1};
    } else {
        /* Buffered: enqueue to ring buffer */
        while (ch->count >= ch->capacity && !ch->closed)
            pthread_cond_wait((pthread_cond_t*)ch->not_full, (pthread_mutex_t*)ch->mutex);
        if (ch->closed) {
            pthread_mutex_unlock((pthread_mutex_t*)ch->mutex);
            return (slop_result_void_thread_ChanError){.is_ok = 0, .data.err = thread_ChanError_send_on_closed};
        }
        ch->buffer[ch->tail] = value;
        ch->tail = (ch->tail + 1) % ch->capacity;
        ch->count++;
        pthread_cond_signal((pthread_cond_t*)ch->not_empty);
        pthread_mutex_unlock((pthread_mutex_t*)ch->mutex);
        return (slop_result_void_thread_ChanError){.is_ok = 1};
    }
}

static slop_result_engine_WorkerMessage_thread_ChanError thread_recv_slop_chan_engine_WorkerMessage(slop_chan_engine_WorkerMessage* ch) {
    engine_WorkerMessage _value;
    pthread_mutex_lock((pthread_mutex_t*)ch->mutex);
    while (ch->count == 0 && !ch->closed)
        pthread_cond_wait((pthread_cond_t*)ch->not_empty, (pthread_mutex_t*)ch->mutex);
    if (ch->count == 0 && ch->closed) {
        pthread_mutex_unlock((pthread_mutex_t*)ch->mutex);
        return (slop_result_engine_WorkerMessage_thread_ChanError){.is_ok = 0, .data.err = thread_ChanError_closed};
    }
    if (ch->capacity == 0) {
        /* Unbuffered */
        _value = ch->buffer[0];
        ch->count = 0;
        pthread_cond_signal((pthread_cond_t*)ch->not_full);
    } else {
        /* Buffered */
        _value = ch->buffer[ch->head];
        ch->head = (ch->head + 1) % ch->capacity;
        ch->count--;
        pthread_cond_signal((pthread_cond_t*)ch->not_full);
    }
    pthread_mutex_unlock((pthread_mutex_t*)ch->mutex);
    return (slop_result_engine_WorkerMessage_thread_ChanError){.is_ok = 1, .data.ok = _value};
}

void engine_print_ms(slop_arena* arena, int64_t ms);
types_ReasonerResult engine_engine_run(slop_arena* arena, types_ReasonerConfig config, index_IndexedGraph initial);
types_Delta engine_make_initial_delta(slop_arena* arena, index_IndexedGraph g);
slop_list_rdf_Triple engine_compute_tc(slop_arena* arena, index_IndexedGraph g, rdf_Term pred);
index_IndexedGraph engine_schema_materialize(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_EngineState_types_InconsistencyReport engine_engine_run_iteration(slop_arena* arena, types_EngineState state);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_sequential(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
slop_result_types_Delta_types_InconsistencyReport engine_apply_all_rules_parallel(slop_arena* arena, index_IndexedGraph g, types_Delta delta, types_ReasonerConfig config);
index_IndexedGraph engine_merge_into_graph(slop_arena* arena, index_IndexedGraph g, types_Delta d);
slop_list_thread_int_ptr engine_spawn_rule_workers(slop_arena* arena, index_IndexedGraph g, types_Delta delta, slop_chan_engine_WorkerMessage* result_chan, slop_arena* arena_cax_infer, slop_arena* arena_cax_check, slop_arena* arena_prp_char, slop_arena* arena_prp_chain, slop_arena* arena_prp_check, slop_arena* arena_eq_infer, slop_arena* arena_eq_check, slop_arena* arena_cls_set, slop_arena* arena_cls_ind, uint8_t verbose, uint8_t fast);
slop_result_types_Delta_types_InconsistencyReport engine_collect_worker_results(slop_arena* arena, slop_chan_engine_WorkerMessage* result_chan, slop_list_thread_int_ptr workers, int64_t next_iter);

#ifndef SLOP_OPTION_ENGINE_WORKERMESSAGE_DEFINED
#define SLOP_OPTION_ENGINE_WORKERMESSAGE_DEFINED
SLOP_OPTION_DEFINE(engine_WorkerMessage, slop_option_engine_WorkerMessage)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_THREAD_INT_PTR_DEFINED
#define SLOP_OPTION_THREAD_INT_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_thread_int*, slop_option_thread_int_ptr)
#endif


#endif
