#ifndef SLOP_thread_H
#define SLOP_thread_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct thread_ThreadInt thread_ThreadInt;
typedef struct thread_ThreadWithChan thread_ThreadWithChan;
typedef struct thread_Closure thread_Closure;

typedef enum {
    thread_ChanError_closed,
    thread_ChanError_would_block,
    thread_ChanError_send_on_closed
} thread_ChanError;

#ifndef SLOP_CHAN_INT_DEFINED
#define SLOP_CHAN_INT_DEFINED
typedef struct slop_chan_int {
    uint8_t mutex[64];       /* pthread_mutex_t storage */
    uint8_t not_empty[64];   /* pthread_cond_t storage */
    uint8_t not_full[64];    /* pthread_cond_t storage */
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

struct thread_ThreadInt {
    pthread_t id;
    int64_t result;
    void* func;
    void* env;
    uint8_t done;
};
typedef struct thread_ThreadInt thread_ThreadInt;

#ifndef SLOP_OPTION_THREAD_THREADINT_DEFINED
#define SLOP_OPTION_THREAD_THREADINT_DEFINED
SLOP_OPTION_DEFINE(thread_ThreadInt, slop_option_thread_ThreadInt)
#endif

struct thread_ThreadWithChan {
    void* func;
    slop_chan_int* chan;
    void* env;
    pthread_t id;
    int64_t result;
    uint8_t done;
};
typedef struct thread_ThreadWithChan thread_ThreadWithChan;

#ifndef SLOP_OPTION_THREAD_THREADWITHCHAN_DEFINED
#define SLOP_OPTION_THREAD_THREADWITHCHAN_DEFINED
SLOP_OPTION_DEFINE(thread_ThreadWithChan, slop_option_thread_ThreadWithChan)
#endif

struct thread_Closure {
    void* fn;
    void* env;
};
typedef struct thread_Closure thread_Closure;

#ifndef SLOP_OPTION_THREAD_CLOSURE_DEFINED
#define SLOP_OPTION_THREAD_CLOSURE_DEFINED
SLOP_OPTION_DEFINE(thread_Closure, slop_option_thread_Closure)
#endif

#ifndef SLOP_RESULT_VOID_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_VOID_THREAD_CHANERROR_DEFINED
typedef struct { bool is_ok; union { uint8_t ok; thread_ChanError err; } data; } slop_result_void_thread_ChanError;
#endif

#ifndef SLOP_RESULT_INT_THREAD_CHANERROR_DEFINED
#define SLOP_RESULT_INT_THREAD_CHANERROR_DEFINED
typedef struct { bool is_ok; union { int64_t ok; thread_ChanError err; } data; } slop_result_int_thread_ChanError;
#endif

slop_chan_int* thread_chan(slop_arena* arena);
slop_chan_int* thread_chan_buffered(slop_arena* arena, int64_t capacity);
void thread_chan_close(slop_chan_int* ch);
slop_result_void_thread_ChanError thread_send(slop_chan_int* ch, int64_t value);
slop_result_int_thread_ChanError thread_recv(slop_chan_int* ch);
slop_result_int_thread_ChanError thread_try_recv(slop_chan_int* ch);
slop_thread_int* thread_spawn(slop_arena* arena, slop_closure_t func);
slop_thread_int* thread_spawn_closure(slop_arena* arena, thread_Closure closure);
thread_ThreadWithChan* thread_spawn_with_chan(slop_arena* arena, slop_closure_t func, slop_chan_int* ch);
void* thread_thread_with_chan_entry(void* arg);
int64_t thread_join(slop_thread_int* thread);

#ifndef SLOP_OPTION_THREAD_THREADINT_DEFINED
#define SLOP_OPTION_THREAD_THREADINT_DEFINED
SLOP_OPTION_DEFINE(thread_ThreadInt, slop_option_thread_ThreadInt)
#endif

#ifndef SLOP_OPTION_THREAD_THREADWITHCHAN_DEFINED
#define SLOP_OPTION_THREAD_THREADWITHCHAN_DEFINED
SLOP_OPTION_DEFINE(thread_ThreadWithChan, slop_option_thread_ThreadWithChan)
#endif

#ifndef SLOP_OPTION_THREAD_CLOSURE_DEFINED
#define SLOP_OPTION_THREAD_CLOSURE_DEFINED
SLOP_OPTION_DEFINE(thread_Closure, slop_option_thread_Closure)
#endif


#endif
