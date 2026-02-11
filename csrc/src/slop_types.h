#ifndef SLOP_types_H
#define SLOP_types_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"

typedef struct types_Delta types_Delta;
typedef struct types_ReasonerConfig types_ReasonerConfig;
typedef struct types_EngineState types_EngineState;
typedef struct types_ReasonerSuccess types_ReasonerSuccess;
typedef struct types_InconsistencyReport types_InconsistencyReport;
typedef struct types_ReasonerResult types_ReasonerResult;

#ifndef SLOP_OPTION_MAP_PTR_DEFINED
#define SLOP_OPTION_MAP_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_map*, slop_option_map_ptr)
#endif

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

#ifndef SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_DEFINED
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

#ifndef SLOP_LIST_RDF_TRIPLE_DEFINED
#define SLOP_LIST_RDF_TRIPLE_DEFINED
SLOP_LIST_DEFINE(rdf_Triple, slop_list_rdf_Triple)
#endif

#ifndef SLOP_LIST_RDF_TERM_DEFINED
#define SLOP_LIST_RDF_TERM_DEFINED
SLOP_LIST_DEFINE(rdf_Term, slop_list_rdf_Term)
#endif

struct types_Delta {
    slop_list_rdf_Triple triples;
    slop_map* seen;
    slop_map* by_predicate;
    int64_t iteration;
};
typedef struct types_Delta types_Delta;

#ifndef SLOP_OPTION_TYPES_DELTA_DEFINED
#define SLOP_OPTION_TYPES_DELTA_DEFINED
SLOP_OPTION_DEFINE(types_Delta, slop_option_types_Delta)
#endif

struct types_ReasonerConfig {
    uint8_t worker_count;
    uint16_t channel_buffer;
    uint16_t max_iterations;
    uint8_t verbose;
    uint8_t fast;
    uint8_t complete;
};
typedef struct types_ReasonerConfig types_ReasonerConfig;

#ifndef SLOP_OPTION_TYPES_REASONERCONFIG_DEFINED
#define SLOP_OPTION_TYPES_REASONERCONFIG_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerConfig, slop_option_types_ReasonerConfig)
#endif

struct types_EngineState {
    index_IndexedGraph graph;
    types_Delta delta;
    int64_t iteration;
    types_ReasonerConfig config;
};
typedef struct types_EngineState types_EngineState;

#ifndef SLOP_OPTION_TYPES_ENGINESTATE_DEFINED
#define SLOP_OPTION_TYPES_ENGINESTATE_DEFINED
SLOP_OPTION_DEFINE(types_EngineState, slop_option_types_EngineState)
#endif

struct types_ReasonerSuccess {
    index_IndexedGraph graph;
    int64_t inferred_count;
    int64_t iterations;
};
typedef struct types_ReasonerSuccess types_ReasonerSuccess;

#ifndef SLOP_OPTION_TYPES_REASONERSUCCESS_DEFINED
#define SLOP_OPTION_TYPES_REASONERSUCCESS_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerSuccess, slop_option_types_ReasonerSuccess)
#endif

struct types_InconsistencyReport {
    slop_string reason;
    slop_list_rdf_Triple witnesses;
};
typedef struct types_InconsistencyReport types_InconsistencyReport;

#ifndef SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(types_InconsistencyReport, slop_option_types_InconsistencyReport)
#endif

typedef enum {
    types_ReasonerResult_reason_success,
    types_ReasonerResult_reason_inconsistent
} types_ReasonerResult_tag;

struct types_ReasonerResult {
    types_ReasonerResult_tag tag;
    union {
        types_ReasonerSuccess reason_success;
        types_InconsistencyReport reason_inconsistent;
    } data;
};
typedef struct types_ReasonerResult types_ReasonerResult;

#ifndef SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
#define SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerResult, slop_option_types_ReasonerResult)
#endif


/* Hash/eq functions and list types for struct map/set keys */
#ifndef RDF_TRIPLE_HASH_EQ_DEFINED
#define RDF_TRIPLE_HASH_EQ_DEFINED
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
#endif
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
#endif
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
#endif
static inline uint64_t slop_hash_rdf_Triple(const void* key) {
    const rdf_Triple* _k = (const rdf_Triple*)key;
    uint64_t hash = 14695981039346656037ULL;
    hash ^= slop_hash_rdf_Term(&_k->subject); hash *= 1099511628211ULL;
    hash ^= slop_hash_rdf_Term(&_k->predicate); hash *= 1099511628211ULL;
    hash ^= slop_hash_rdf_Term(&_k->object); hash *= 1099511628211ULL;
    return hash;
}
static inline bool slop_eq_rdf_Triple(const void* a, const void* b) {
    const rdf_Triple* _a = (const rdf_Triple*)a;
    const rdf_Triple* _b = (const rdf_Triple*)b;
    return true
        && slop_eq_rdf_Term(&_a->subject, &_b->subject)
        && slop_eq_rdf_Term(&_a->predicate, &_b->predicate)
        && slop_eq_rdf_Term(&_a->object, &_b->object)
    ;
}
#endif

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
#endif

types_Delta types_make_delta(slop_arena* arena, int64_t iteration);
types_Delta types_delta_add(slop_arena* arena, types_Delta d, rdf_Triple t);
types_Delta types_delta_merge(slop_arena* arena, types_Delta d1, types_Delta d2);
uint8_t types_delta_is_empty(types_Delta d);
uint8_t types_all_triples_have_predicate(slop_list_rdf_Triple triples, slop_string pred_iri);

#ifndef SLOP_OPTION_RDF_TRIPLE_DEFINED
#define SLOP_OPTION_RDF_TRIPLE_DEFINED
SLOP_OPTION_DEFINE(rdf_Triple, slop_option_rdf_Triple)
#endif

#ifndef SLOP_OPTION_RDF_TERM_DEFINED
#define SLOP_OPTION_RDF_TERM_DEFINED
SLOP_OPTION_DEFINE(rdf_Term, slop_option_rdf_Term)
#endif

#ifndef SLOP_OPTION_MAP_PTR_DEFINED
#define SLOP_OPTION_MAP_PTR_DEFINED
SLOP_OPTION_DEFINE(slop_map*, slop_option_map_ptr)
#endif

#ifndef SLOP_OPTION_TYPES_DELTA_DEFINED
#define SLOP_OPTION_TYPES_DELTA_DEFINED
SLOP_OPTION_DEFINE(types_Delta, slop_option_types_Delta)
#endif

#ifndef SLOP_OPTION_TYPES_REASONERCONFIG_DEFINED
#define SLOP_OPTION_TYPES_REASONERCONFIG_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerConfig, slop_option_types_ReasonerConfig)
#endif

#ifndef SLOP_OPTION_TYPES_ENGINESTATE_DEFINED
#define SLOP_OPTION_TYPES_ENGINESTATE_DEFINED
SLOP_OPTION_DEFINE(types_EngineState, slop_option_types_EngineState)
#endif

#ifndef SLOP_OPTION_TYPES_REASONERSUCCESS_DEFINED
#define SLOP_OPTION_TYPES_REASONERSUCCESS_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerSuccess, slop_option_types_ReasonerSuccess)
#endif

#ifndef SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
#define SLOP_OPTION_TYPES_INCONSISTENCYREPORT_DEFINED
SLOP_OPTION_DEFINE(types_InconsistencyReport, slop_option_types_InconsistencyReport)
#endif

#ifndef SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
#define SLOP_OPTION_TYPES_REASONERRESULT_DEFINED
SLOP_OPTION_DEFINE(types_ReasonerResult, slop_option_types_ReasonerResult)
#endif


#endif
