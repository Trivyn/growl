#ifndef SLOP_thread_H
#define SLOP_thread_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "../runtime/slop_runtime.h"

typedef struct std_thread_ThreadInt std_thread_ThreadInt;
typedef struct std_thread_ThreadWithChan std_thread_ThreadWithChan;
typedef struct std_thread_Closure std_thread_Closure;

typedef enum {
    std_thread_ChanError_closed,
    std_thread_ChanError_would_block,
    std_thread_ChanError_send_on_closed
} std_thread_ChanError;

#ifndef SLOP_CHAN_INT_DEFINED
#define SLOP_CHAN_INT_DEFINED
typedef struct slop_chan_int {
    slop_mutex_t mutex;      /* Guards every field below */
    slop_cond_t not_empty;   /* Signalled when an item arrives */
    slop_cond_t not_full;    /* Signalled when space frees up */
    int64_t* buffer;         /* Ring buffer */
    size_t capacity;         /* Buffer capacity (0 = unbuffered) */
    size_t count;            /* Current item count */
    size_t head;             /* Read index */
    size_t tail;             /* Write index */
    bool closed;             /* Channel closed flag */
} slop_chan_int;
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

struct std_thread_ThreadInt {
    slop_thread_t id;
    int64_t result;
    void* func;
    void* env;
    uint8_t done;
};
typedef struct std_thread_ThreadInt std_thread_ThreadInt;

#ifndef SLOP_OPTION_STD_THREAD_THREADINT_DEFINED
#define SLOP_OPTION_STD_THREAD_THREADINT_DEFINED
SLOP_OPTION_DEFINE(std_thread_ThreadInt, slop_option_std_thread_ThreadInt)
#endif

struct std_thread_ThreadWithChan {
    void* func;
    slop_chan_int* chan;
    void* env;
    slop_thread_t id;
    int64_t result;
    uint8_t done;
};
typedef struct std_thread_ThreadWithChan std_thread_ThreadWithChan;

#ifndef SLOP_OPTION_STD_THREAD_THREADWITHCHAN_DEFINED
#define SLOP_OPTION_STD_THREAD_THREADWITHCHAN_DEFINED
SLOP_OPTION_DEFINE(std_thread_ThreadWithChan, slop_option_std_thread_ThreadWithChan)
#endif

struct std_thread_Closure {
    void* fn;
    void* env;
};
typedef struct std_thread_Closure std_thread_Closure;

#ifndef SLOP_OPTION_STD_THREAD_CLOSURE_DEFINED
#define SLOP_OPTION_STD_THREAD_CLOSURE_DEFINED
SLOP_OPTION_DEFINE(std_thread_Closure, slop_option_std_thread_Closure)
#endif

#ifndef SLOP_RESULT_VOID_STD_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_VOID_STD_THREAD_CHANERROR_DEFINED
typedef struct { bool is_ok; union { uint8_t ok; std_thread_ChanError err; } data; } slop_result_void_std_thread_ChanError;
#endif

#ifndef SLOP_RESULT_INT_STD_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_INT_STD_THREAD_CHANERROR_DEFINED
typedef struct { bool is_ok; union { int64_t ok; std_thread_ChanError err; } data; } slop_result_int_std_thread_ChanError;
#endif

slop_chan_int* std_thread_chan(slop_arena* arena);
slop_chan_int* std_thread_chan_buffered(slop_arena* arena, int64_t capacity);
void std_thread_chan_close(slop_chan_int* ch);
slop_result_void_std_thread_ChanError std_thread_send(slop_chan_int* ch, int64_t value);
slop_result_int_std_thread_ChanError std_thread_recv(slop_chan_int* ch);
slop_result_int_std_thread_ChanError std_thread_try_recv(slop_chan_int* ch);
slop_thread_int* std_thread_spawn(slop_arena* arena, slop_closure_t func);
slop_thread_int* std_thread_spawn_closure(slop_arena* arena, std_thread_Closure closure);
std_thread_ThreadWithChan* std_thread_spawn_with_chan(slop_arena* arena, slop_closure_t func, slop_chan_int* ch);
void* std_thread_thread_with_chan_entry(void* arg);
int64_t std_thread_join(slop_thread_int* thread);

#ifndef SLOP_OPTION_STD_THREAD_THREADINT_DEFINED
#define SLOP_OPTION_STD_THREAD_THREADINT_DEFINED
SLOP_OPTION_DEFINE(std_thread_ThreadInt, slop_option_std_thread_ThreadInt)
#endif

#ifndef SLOP_OPTION_STD_THREAD_THREADWITHCHAN_DEFINED
#define SLOP_OPTION_STD_THREAD_THREADWITHCHAN_DEFINED
SLOP_OPTION_DEFINE(std_thread_ThreadWithChan, slop_option_std_thread_ThreadWithChan)
#endif

#ifndef SLOP_OPTION_STD_THREAD_CLOSURE_DEFINED
#define SLOP_OPTION_STD_THREAD_CLOSURE_DEFINED
SLOP_OPTION_DEFINE(std_thread_Closure, slop_option_std_thread_Closure)
#endif


#endif
