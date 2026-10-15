#ifndef SLOP_engine_H
#define SLOP_engine_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_vocab.h"
#include "slop_thread.h"
#include "slop_strlib.h"
#include "slop_list.h"
#include "slop_types.h"
#include "slop_cax.h"
#include "slop_scm.h"
#include "slop_prp.h"
#include "slop_eq.h"
#include "slop_cls.h"
#include "slop_dt.h"

typedef struct growl_engine_WorkerMessage growl_engine_WorkerMessage;
typedef struct growl_engine_ValidateInjection growl_engine_ValidateInjection;

#ifndef SLOP_LIST_THREAD_INT_PTR_DEFINED
#define SLOP_LIST_THREAD_INT_PTR_DEFINED
#define SLOP_LIST_THREAD_INT_PTR_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_thread_int*, slop_list_thread_int_ptr)
#endif

#ifndef SLOP_OPTION_THREAD_INT_PTR_DEFINED
#define SLOP_OPTION_THREAD_INT_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_thread_int*, slop_option_thread_int_ptr)
#endif

#ifndef SLOP_CHAN_GROWL_ENGINE_WORKERMESSAGE_DEFINED
#define SLOP_CHAN_GROWL_ENGINE_WORKERMESSAGE_DEFINED
typedef struct slop_chan_growl_engine_WorkerMessage {
    slop_mutex_t mutex;      /* Guards every field below */
    slop_cond_t not_empty;   /* Signalled when an item arrives */
    slop_cond_t not_full;    /* Signalled when space frees up */
    growl_engine_WorkerMessage* buffer;         /* Ring buffer */
    size_t capacity;         /* Buffer capacity (0 = unbuffered) */
    size_t count;            /* Current item count */
    size_t head;             /* Read index */
    size_t tail;             /* Write index */
    bool closed;             /* Channel closed flag */
} slop_chan_growl_engine_WorkerMessage;
#endif

#ifndef SLOP_THREAD_INT_DEFINED
#define SLOP_THREAD_INT_DEFINED
typedef struct slop_thread_int {
    slop_thread_t id;        /* Thread handle */
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

#ifndef SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TERM_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Term, slop_list_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_LIST_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_LIST_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_LIST_GROWL_TYPES_INCONSISTENCYREPORT_IMPL_DEFINED
SLOP_LIST_DEFINE(growl_types_InconsistencyReport, slop_list_growl_types_InconsistencyReport)
#endif

#ifndef SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_RDF_TRIPLE_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_rdf_Triple, slop_list_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(growl_types_InconsistencyReport, slop_option_growl_types_InconsistencyReport)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

typedef enum {
    growl_engine_WorkerMessage_msg_delta,
    growl_engine_WorkerMessage_msg_inconsistent,
    growl_engine_WorkerMessage_msg_done
} growl_engine_WorkerMessage_tag;

struct growl_engine_WorkerMessage {
    growl_engine_WorkerMessage_tag tag;
    union {
        growl_types_Delta msg_delta;
        growl_types_InconsistencyReport msg_inconsistent;
        int msg_done;
    } data;
};
typedef struct growl_engine_WorkerMessage growl_engine_WorkerMessage;

#ifndef SLOP_OPTION_GROWL_ENGINE_WORKERMESSAGE_DEFINED
#define SLOP_OPTION_GROWL_ENGINE_WORKERMESSAGE_DEFINED
SLOP_OPTION_DEFINE(growl_engine_WorkerMessage, slop_option_growl_engine_WorkerMessage)
#endif

struct growl_engine_ValidateInjection {
    slop_rdf_index_IndexedGraph graph;
    slop_list_slop_rdf_rdf_Term class_map;
    slop_list_slop_rdf_rdf_Term prop_map;
};
typedef struct growl_engine_ValidateInjection growl_engine_ValidateInjection;

#ifndef SLOP_OPTION_GROWL_ENGINE_VALIDATEINJECTION_DEFINED
#define SLOP_OPTION_GROWL_ENGINE_VALIDATEINJECTION_DEFINED
SLOP_OPTION_DEFINE(growl_engine_ValidateInjection, slop_option_growl_engine_ValidateInjection)
#endif


/* Hash/eq functions and list types for struct map/set keys */
#ifndef SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#ifndef SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_IRI(const void* key) {
    const slop_rdf_rdf_IRI* _k = (const slop_rdf_rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_IRI(const void* a, const void* b) {
    const slop_rdf_rdf_IRI* _a = (const slop_rdf_rdf_IRI*)a;
    const slop_rdf_rdf_IRI* _b = (const slop_rdf_rdf_IRI*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
    ;
}
#endif
#ifndef SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_BlankNode(const void* key) {
    const slop_rdf_rdf_BlankNode* _k = (const slop_rdf_rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_int(&(int64_t){ (int64_t)_k->id }); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_BlankNode(const void* a, const void* b) {
    const slop_rdf_rdf_BlankNode* _a = (const slop_rdf_rdf_BlankNode*)a;
    const slop_rdf_rdf_BlankNode* _b = (const slop_rdf_rdf_BlankNode*)b;
    return true
        && (_a->id == _b->id)
    ;
}
#endif
#ifndef SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_Literal(const void* key) {
    const slop_rdf_rdf_Literal* _k = (const slop_rdf_rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    hash ^= ((_k->datatype).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->datatype).value)) : 0); hash *= 1099511628211ULL;
    hash ^= ((_k->lang).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->lang).value)) : 0); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_Literal(const void* a, const void* b) {
    const slop_rdf_rdf_Literal* _a = (const slop_rdf_rdf_Literal*)a;
    const slop_rdf_rdf_Literal* _b = (const slop_rdf_rdf_Literal*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
        && ((_a->datatype).has_value == (_b->datatype).has_value && (!(_a->datatype).has_value || ((slop_eq_string(&(_a->datatype).value, &(_b->datatype).value)))))
        && ((_a->lang).has_value == (_b->lang).has_value && (!(_a->lang).has_value || ((slop_eq_string(&(_a->lang).value, &(_b->lang).value)))))
    ;
}
#endif
static inline uint64_t slop_hash_slop_rdf_rdf_Term(const void* key) {
    const slop_rdf_rdf_Term* _k = (const slop_rdf_rdf_Term*)key;
    switch (_k->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_hash_slop_rdf_rdf_IRI(&_k->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_hash_slop_rdf_rdf_BlankNode(&_k->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_hash_slop_rdf_rdf_Literal(&_k->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return slop_hash_ptr(&_k->data.term_triple);
    }
    return 0;
}
static inline bool slop_eq_slop_rdf_rdf_Term(const void* a, const void* b) {
    const slop_rdf_rdf_Term* _a = (const slop_rdf_rdf_Term*)a;
    const slop_rdf_rdf_Term* _b = (const slop_rdf_rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_eq_slop_rdf_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_eq_slop_rdf_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_eq_slop_rdf_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return _a->data.term_triple == _b->data.term_triple;
    }
    return false;
}
#endif

#ifndef SLOP_RDF_RDF_TRIPLE_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_TRIPLE_HASH_EQ_DEFINED
#ifndef SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#ifndef SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_IRI(const void* key) {
    const slop_rdf_rdf_IRI* _k = (const slop_rdf_rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_IRI(const void* a, const void* b) {
    const slop_rdf_rdf_IRI* _a = (const slop_rdf_rdf_IRI*)a;
    const slop_rdf_rdf_IRI* _b = (const slop_rdf_rdf_IRI*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
    ;
}
#endif
#ifndef SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_BlankNode(const void* key) {
    const slop_rdf_rdf_BlankNode* _k = (const slop_rdf_rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_int(&(int64_t){ (int64_t)_k->id }); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_BlankNode(const void* a, const void* b) {
    const slop_rdf_rdf_BlankNode* _a = (const slop_rdf_rdf_BlankNode*)a;
    const slop_rdf_rdf_BlankNode* _b = (const slop_rdf_rdf_BlankNode*)b;
    return true
        && (_a->id == _b->id)
    ;
}
#endif
#ifndef SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_Literal(const void* key) {
    const slop_rdf_rdf_Literal* _k = (const slop_rdf_rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    hash ^= ((_k->datatype).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->datatype).value)) : 0); hash *= 1099511628211ULL;
    hash ^= ((_k->lang).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->lang).value)) : 0); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_Literal(const void* a, const void* b) {
    const slop_rdf_rdf_Literal* _a = (const slop_rdf_rdf_Literal*)a;
    const slop_rdf_rdf_Literal* _b = (const slop_rdf_rdf_Literal*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
        && ((_a->datatype).has_value == (_b->datatype).has_value && (!(_a->datatype).has_value || ((slop_eq_string(&(_a->datatype).value, &(_b->datatype).value)))))
        && ((_a->lang).has_value == (_b->lang).has_value && (!(_a->lang).has_value || ((slop_eq_string(&(_a->lang).value, &(_b->lang).value)))))
    ;
}
#endif
static inline uint64_t slop_hash_slop_rdf_rdf_Term(const void* key) {
    const slop_rdf_rdf_Term* _k = (const slop_rdf_rdf_Term*)key;
    switch (_k->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_hash_slop_rdf_rdf_IRI(&_k->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_hash_slop_rdf_rdf_BlankNode(&_k->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_hash_slop_rdf_rdf_Literal(&_k->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return slop_hash_ptr(&_k->data.term_triple);
    }
    return 0;
}
static inline bool slop_eq_slop_rdf_rdf_Term(const void* a, const void* b) {
    const slop_rdf_rdf_Term* _a = (const slop_rdf_rdf_Term*)a;
    const slop_rdf_rdf_Term* _b = (const slop_rdf_rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_eq_slop_rdf_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_eq_slop_rdf_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_eq_slop_rdf_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return _a->data.term_triple == _b->data.term_triple;
    }
    return false;
}
#endif
#ifndef SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#ifndef SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_IRI(const void* key) {
    const slop_rdf_rdf_IRI* _k = (const slop_rdf_rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_IRI(const void* a, const void* b) {
    const slop_rdf_rdf_IRI* _a = (const slop_rdf_rdf_IRI*)a;
    const slop_rdf_rdf_IRI* _b = (const slop_rdf_rdf_IRI*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
    ;
}
#endif
#ifndef SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_BlankNode(const void* key) {
    const slop_rdf_rdf_BlankNode* _k = (const slop_rdf_rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_int(&(int64_t){ (int64_t)_k->id }); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_BlankNode(const void* a, const void* b) {
    const slop_rdf_rdf_BlankNode* _a = (const slop_rdf_rdf_BlankNode*)a;
    const slop_rdf_rdf_BlankNode* _b = (const slop_rdf_rdf_BlankNode*)b;
    return true
        && (_a->id == _b->id)
    ;
}
#endif
#ifndef SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_Literal(const void* key) {
    const slop_rdf_rdf_Literal* _k = (const slop_rdf_rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    hash ^= ((_k->datatype).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->datatype).value)) : 0); hash *= 1099511628211ULL;
    hash ^= ((_k->lang).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->lang).value)) : 0); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_Literal(const void* a, const void* b) {
    const slop_rdf_rdf_Literal* _a = (const slop_rdf_rdf_Literal*)a;
    const slop_rdf_rdf_Literal* _b = (const slop_rdf_rdf_Literal*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
        && ((_a->datatype).has_value == (_b->datatype).has_value && (!(_a->datatype).has_value || ((slop_eq_string(&(_a->datatype).value, &(_b->datatype).value)))))
        && ((_a->lang).has_value == (_b->lang).has_value && (!(_a->lang).has_value || ((slop_eq_string(&(_a->lang).value, &(_b->lang).value)))))
    ;
}
#endif
static inline uint64_t slop_hash_slop_rdf_rdf_Term(const void* key) {
    const slop_rdf_rdf_Term* _k = (const slop_rdf_rdf_Term*)key;
    switch (_k->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_hash_slop_rdf_rdf_IRI(&_k->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_hash_slop_rdf_rdf_BlankNode(&_k->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_hash_slop_rdf_rdf_Literal(&_k->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return slop_hash_ptr(&_k->data.term_triple);
    }
    return 0;
}
static inline bool slop_eq_slop_rdf_rdf_Term(const void* a, const void* b) {
    const slop_rdf_rdf_Term* _a = (const slop_rdf_rdf_Term*)a;
    const slop_rdf_rdf_Term* _b = (const slop_rdf_rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_eq_slop_rdf_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_eq_slop_rdf_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_eq_slop_rdf_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return _a->data.term_triple == _b->data.term_triple;
    }
    return false;
}
#endif
#ifndef SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_TERM_HASH_EQ_DEFINED
#ifndef SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_IRI_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_IRI(const void* key) {
    const slop_rdf_rdf_IRI* _k = (const slop_rdf_rdf_IRI*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_IRI(const void* a, const void* b) {
    const slop_rdf_rdf_IRI* _a = (const slop_rdf_rdf_IRI*)a;
    const slop_rdf_rdf_IRI* _b = (const slop_rdf_rdf_IRI*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
    ;
}
#endif
#ifndef SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_BLANKNODE_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_BlankNode(const void* key) {
    const slop_rdf_rdf_BlankNode* _k = (const slop_rdf_rdf_BlankNode*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_int(&(int64_t){ (int64_t)_k->id }); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_BlankNode(const void* a, const void* b) {
    const slop_rdf_rdf_BlankNode* _a = (const slop_rdf_rdf_BlankNode*)a;
    const slop_rdf_rdf_BlankNode* _b = (const slop_rdf_rdf_BlankNode*)b;
    return true
        && (_a->id == _b->id)
    ;
}
#endif
#ifndef SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
#define SLOP_RDF_RDF_LITERAL_HASH_EQ_DEFINED
static inline uint64_t slop_hash_slop_rdf_rdf_Literal(const void* key) {
    const slop_rdf_rdf_Literal* _k = (const slop_rdf_rdf_Literal*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_string(&_k->value); hash *= 1099511628211ULL;
    hash ^= ((_k->datatype).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->datatype).value)) : 0); hash *= 1099511628211ULL;
    hash ^= ((_k->lang).has_value ? slop_hash_combine(1, slop_hash_string(&(_k->lang).value)) : 0); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_Literal(const void* a, const void* b) {
    const slop_rdf_rdf_Literal* _a = (const slop_rdf_rdf_Literal*)a;
    const slop_rdf_rdf_Literal* _b = (const slop_rdf_rdf_Literal*)b;
    return true
        && (slop_eq_string(&_a->value, &_b->value))
        && ((_a->datatype).has_value == (_b->datatype).has_value && (!(_a->datatype).has_value || ((slop_eq_string(&(_a->datatype).value, &(_b->datatype).value)))))
        && ((_a->lang).has_value == (_b->lang).has_value && (!(_a->lang).has_value || ((slop_eq_string(&(_a->lang).value, &(_b->lang).value)))))
    ;
}
#endif
static inline uint64_t slop_hash_slop_rdf_rdf_Term(const void* key) {
    const slop_rdf_rdf_Term* _k = (const slop_rdf_rdf_Term*)key;
    switch (_k->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_hash_slop_rdf_rdf_IRI(&_k->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_hash_slop_rdf_rdf_BlankNode(&_k->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_hash_slop_rdf_rdf_Literal(&_k->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return slop_hash_ptr(&_k->data.term_triple);
    }
    return 0;
}
static inline bool slop_eq_slop_rdf_rdf_Term(const void* a, const void* b) {
    const slop_rdf_rdf_Term* _a = (const slop_rdf_rdf_Term*)a;
    const slop_rdf_rdf_Term* _b = (const slop_rdf_rdf_Term*)b;
    if (_a->tag != _b->tag) return false;
    switch (_a->tag) {
        case slop_rdf_rdf_Term_term_iri:
            return slop_eq_slop_rdf_rdf_IRI(&_a->data.term_iri, &_b->data.term_iri);
        case slop_rdf_rdf_Term_term_blank:
            return slop_eq_slop_rdf_rdf_BlankNode(&_a->data.term_blank, &_b->data.term_blank);
        case slop_rdf_rdf_Term_term_literal:
            return slop_eq_slop_rdf_rdf_Literal(&_a->data.term_literal, &_b->data.term_literal);
        case slop_rdf_rdf_Term_term_triple:
            return _a->data.term_triple == _b->data.term_triple;
    }
    return false;
}
#endif
static inline uint64_t slop_hash_slop_rdf_rdf_Triple(const void* key) {
    const slop_rdf_rdf_Triple* _k = (const slop_rdf_rdf_Triple*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_slop_rdf_rdf_Term(&_k->subject); hash *= 1099511628211ULL;
    hash ^= slop_hash_slop_rdf_rdf_Term(&_k->predicate); hash *= 1099511628211ULL;
    hash ^= slop_hash_slop_rdf_rdf_Term(&_k->object); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_slop_rdf_rdf_Triple(const void* a, const void* b) {
    const slop_rdf_rdf_Triple* _a = (const slop_rdf_rdf_Triple*)a;
    const slop_rdf_rdf_Triple* _b = (const slop_rdf_rdf_Triple*)b;
    return true
        && (slop_eq_slop_rdf_rdf_Term(&_a->subject, &_b->subject))
        && (slop_eq_slop_rdf_rdf_Term(&_a->predicate, &_b->predicate))
        && (slop_eq_slop_rdf_rdf_Term(&_a->object, &_b->object))
    ;
}
#endif

#ifndef SLOP_RESULT_GROWL_TYPES_ENGINESTATE_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_GROWL_TYPES_ENGINESTATE_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { growl_types_EngineState ok; growl_types_InconsistencyReport err; } data; } slop_result_growl_types_EngineState_growl_types_InconsistencyReport;
#endif

#ifndef SLOP_RESULT_GROWL_TYPES_DELTA_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_RESULT_GROWL_TYPES_DELTA_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
typedef struct { bool is_ok; union { growl_types_Delta ok; growl_types_InconsistencyReport err; } data; } slop_result_growl_types_Delta_growl_types_InconsistencyReport;
#endif

#ifndef SLOP_RESULT_VOID_STD_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_VOID_STD_THREAD_CHANERROR_DEFINED
typedef struct slop_result_void_std_thread_ChanError {
    bool is_ok;
    union { uint8_t ok; std_thread_ChanError err; } data;
} slop_result_void_std_thread_ChanError;
#endif

#ifndef SLOP_RESULT_GROWL_ENGINE_WORKERMESSAGE_STD_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_GROWL_ENGINE_WORKERMESSAGE_STD_THREAD_CHANERROR_DEFINED
typedef struct slop_result_growl_engine_WorkerMessage_std_thread_ChanError {
    bool is_ok;
    union { growl_engine_WorkerMessage ok; std_thread_ChanError err; } data;
} slop_result_growl_engine_WorkerMessage_std_thread_ChanError;
#endif

static slop_result_void_std_thread_ChanError thread_send_slop_chan_growl_engine_WorkerMessage(slop_chan_growl_engine_WorkerMessage* ch, growl_engine_WorkerMessage value) {
    slop_mutex_lock(&ch->mutex);
    if (ch->closed) {
        slop_mutex_unlock(&ch->mutex);
        return (slop_result_void_std_thread_ChanError){.is_ok = 0, .data.err = std_thread_ChanError_send_on_closed};
    }
    if (ch->capacity == 0) {
        /* Unbuffered: synchronous handoff */
        while (ch->count > 0 && !ch->closed)
            slop_cond_wait(&ch->not_full, &ch->mutex);
        if (ch->closed) {
            slop_mutex_unlock(&ch->mutex);
            return (slop_result_void_std_thread_ChanError){.is_ok = 0, .data.err = std_thread_ChanError_send_on_closed};
        }
        /* Store value in single-element inline storage */
        if (!ch->buffer) ch->buffer = malloc(sizeof(growl_engine_WorkerMessage));
        ch->buffer[0] = value;
        ch->count = 1;
        slop_cond_signal(&ch->not_empty);
        /* Wait for receiver to take it */
        while (ch->count > 0 && !ch->closed)
            slop_cond_wait(&ch->not_full, &ch->mutex);
        slop_mutex_unlock(&ch->mutex);
        return (slop_result_void_std_thread_ChanError){.is_ok = 1};
    } else {
        /* Buffered: enqueue to ring buffer */
        while (ch->count >= ch->capacity && !ch->closed)
            slop_cond_wait(&ch->not_full, &ch->mutex);
        if (ch->closed) {
            slop_mutex_unlock(&ch->mutex);
            return (slop_result_void_std_thread_ChanError){.is_ok = 0, .data.err = std_thread_ChanError_send_on_closed};
        }
        ch->buffer[ch->tail] = value;
        ch->tail = (ch->tail + 1) % ch->capacity;
        ch->count++;
        slop_cond_signal(&ch->not_empty);
        slop_mutex_unlock(&ch->mutex);
        return (slop_result_void_std_thread_ChanError){.is_ok = 1};
    }
}

static slop_result_growl_engine_WorkerMessage_std_thread_ChanError thread_recv_slop_chan_growl_engine_WorkerMessage(slop_chan_growl_engine_WorkerMessage* ch) {
    growl_engine_WorkerMessage _value;
    slop_mutex_lock(&ch->mutex);
    while (ch->count == 0 && !ch->closed)
        slop_cond_wait(&ch->not_empty, &ch->mutex);
    if (ch->count == 0 && ch->closed) {
        slop_mutex_unlock(&ch->mutex);
        return (slop_result_growl_engine_WorkerMessage_std_thread_ChanError){.is_ok = 0, .data.err = std_thread_ChanError_closed};
    }
    if (ch->capacity == 0) {
        /* Unbuffered */
        _value = ch->buffer[0];
        ch->count = 0;
        slop_cond_signal(&ch->not_full);
    } else {
        /* Buffered */
        _value = ch->buffer[ch->head];
        ch->head = (ch->head + 1) % ch->capacity;
        ch->count--;
        slop_cond_signal(&ch->not_full);
    }
    slop_mutex_unlock(&ch->mutex);
    return (slop_result_growl_engine_WorkerMessage_std_thread_ChanError){.is_ok = 1, .data.ok = _value};
}

void growl_engine_print_ms(slop_arena* arena, int64_t ms);
slop_list_slop_rdf_rdf_Term growl_engine_collect_declared_properties(slop_arena* arena, slop_rdf_index_IndexedGraph g);
uint8_t growl_engine_iri_matches_ns(slop_rdf_rdf_Term term, slop_string ns);
growl_engine_ValidateInjection growl_engine_inject_validate_instances(slop_arena* arena, slop_rdf_index_IndexedGraph g, uint8_t verbose, slop_string validate_ns);
slop_string growl_engine_resolve_blank_class(slop_arena* arena, int64_t blank_id, slop_list_slop_rdf_rdf_Term class_map);
slop_string growl_engine_resolve_blank_prop(slop_arena* arena, int64_t blank_id, slop_list_slop_rdf_rdf_Term prop_map);
slop_string growl_engine_build_enriched_reason(slop_arena* arena, slop_string class_name, slop_string prop_name, slop_string original_reason, slop_string detail);
growl_types_InconsistencyReport growl_engine_enrich_validate_report(slop_arena* arena, growl_types_InconsistencyReport report, slop_rdf_index_IndexedGraph pre_inject_graph, slop_string validate_ns, slop_list_slop_rdf_rdf_Term class_map, slop_list_slop_rdf_rdf_Term prop_map);
slop_list_growl_types_InconsistencyReport growl_engine_validate_check_all(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_index_IndexedGraph pre_inject_graph, slop_string validate_ns, slop_list_slop_rdf_rdf_Term class_map, slop_list_slop_rdf_rdf_Term prop_map);
growl_types_ReasonerResult growl_engine_engine_run(slop_arena* arena, growl_types_ReasonerConfig config, slop_rdf_index_IndexedGraph initial);
growl_types_Delta growl_engine_make_initial_delta(slop_arena* arena, slop_rdf_index_IndexedGraph g);
slop_list_slop_rdf_rdf_Triple growl_engine_compute_tc(slop_arena* arena, slop_rdf_index_IndexedGraph g, slop_rdf_rdf_Term pred);
slop_rdf_index_IndexedGraph growl_engine_schema_materialize_fast(slop_arena* arena, slop_rdf_index_IndexedGraph g);
slop_rdf_index_IndexedGraph growl_engine_schema_materialize(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, growl_types_ReasonerConfig config);
slop_result_growl_types_EngineState_growl_types_InconsistencyReport growl_engine_engine_run_iteration(slop_arena* arena, growl_types_EngineState state);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_engine_apply_all_rules(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, growl_types_ReasonerConfig config);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_engine_apply_all_rules_sequential(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, growl_types_ReasonerConfig config);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_engine_apply_all_rules_parallel(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, growl_types_ReasonerConfig config);
slop_rdf_index_IndexedGraph growl_engine_merge_into_graph(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta d);
slop_list_thread_int_ptr growl_engine_spawn_rule_workers(slop_arena* arena, slop_rdf_index_IndexedGraph g, growl_types_Delta delta, slop_chan_growl_engine_WorkerMessage* result_chan, slop_arena* arena_cax_infer, slop_arena* arena_cax_check, slop_arena* arena_prp_char, slop_arena* arena_prp_chain, slop_arena* arena_prp_check, slop_arena* arena_eq_infer, slop_arena* arena_eq_check, slop_arena* arena_cls_set, slop_arena* arena_cls_ind, uint8_t verbose, uint8_t fast, uint8_t validate, uint8_t enrich);
slop_result_growl_types_Delta_growl_types_InconsistencyReport growl_engine_collect_worker_results(slop_arena* arena, slop_chan_growl_engine_WorkerMessage* result_chan, slop_list_thread_int_ptr workers, int64_t next_iter);

#ifndef SLOP_OPTION_GROWL_ENGINE_WORKERMESSAGE_DEFINED
#define SLOP_OPTION_GROWL_ENGINE_WORKERMESSAGE_DEFINED
SLOP_OPTION_DEFINE(growl_engine_WorkerMessage, slop_option_growl_engine_WorkerMessage)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Term, slop_option_slop_rdf_rdf_Term)
#endif

#ifndef SLOP_OPTION_GROWL_ENGINE_VALIDATEINJECTION_DEFINED
#define SLOP_OPTION_GROWL_ENGINE_VALIDATEINJECTION_DEFINED
SLOP_OPTION_DEFINE(growl_engine_ValidateInjection, slop_option_growl_engine_ValidateInjection)
#endif

#ifndef SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_GROWL_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(growl_types_InconsistencyReport, slop_option_growl_types_InconsistencyReport)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_rdf_Triple, slop_option_slop_rdf_rdf_Triple)
#endif

#ifndef SLOP_OPTION_THREAD_INT_PTR_DEFINED
#define SLOP_OPTION_THREAD_INT_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_thread_int*, slop_option_thread_int_ptr)
#endif

#ifndef SLOP_OPTION_MAP_PTR_DEFINED
#define SLOP_OPTION_MAP_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_map*, slop_option_map_ptr)
#endif


#endif
