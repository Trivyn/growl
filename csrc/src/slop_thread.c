#include "../runtime/slop_runtime.h"
#include "slop_thread.h"

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

slop_chan_int* thread_chan(slop_arena* arena) {
    slop_chan_int* _retval = {0};
    {
        __auto_type ch = ({ __auto_type _alloc = (slop_chan_int*)slop_arena_alloc(arena, sizeof(slop_chan_int)); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; });
        pthread_mutex_init(((void*)((&ch->mutex))), NULL);
        pthread_cond_init(((void*)((&ch->not_empty))), NULL);
        pthread_cond_init(((void*)((&ch->not_full))), NULL);
        ch->buffer = NULL;
        ch->capacity = 0;
        ch->count = 0;
        ch->head = 0;
        ch->tail = 0;
        ch->closed = 0;
        _retval = ch;
    }
    SLOP_POST(((_retval != NULL)), "(!= $result nil)");
    return _retval;
}

slop_chan_int* thread_chan_buffered(slop_arena* arena, int64_t capacity) {
    SLOP_PRE(((capacity >= 1)), "(>= capacity 1)");
    slop_chan_int* _retval = {0};
    {
        __auto_type ch = ({ __auto_type _alloc = (slop_chan_int*)slop_arena_alloc(arena, sizeof(slop_chan_int)); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; });
        pthread_mutex_init(((void*)((&ch->mutex))), NULL);
        pthread_cond_init(((void*)((&ch->not_empty))), NULL);
        pthread_cond_init(((void*)((&ch->not_full))), NULL);
        ch->buffer = ({ __auto_type _alloc = (int64_t*)slop_arena_alloc(arena, (capacity * sizeof(int64_t))); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; });
        ch->capacity = ((uint64_t)(capacity));
        ch->count = 0;
        ch->head = 0;
        ch->tail = 0;
        ch->closed = 0;
        _retval = ch;
    }
    SLOP_POST(((_retval != NULL)), "(!= $result nil)");
    return _retval;
}

void thread_chan_close(slop_chan_int* ch) {
    SLOP_PRE(((ch != NULL)), "(!= ch nil)");
    pthread_mutex_lock(((void*)((&ch->mutex))));
    ch->closed = 1;
    pthread_cond_broadcast(((void*)((&ch->not_empty))));
    pthread_cond_broadcast(((void*)((&ch->not_full))));
    pthread_mutex_unlock(((void*)((&ch->mutex))));
}

slop_result_void_thread_ChanError thread_send(slop_chan_int* ch, int64_t value) {
    SLOP_PRE(((ch != NULL)), "(!= ch nil)");
    pthread_mutex_lock(((void*)((&ch->mutex))));
    if (ch->closed) {
        pthread_mutex_unlock(((void*)((&ch->mutex))));
        return ((slop_result_void_thread_ChanError){ .is_ok = false, .data.err = thread_ChanError_send_on_closed });
    } else {
        if ((ch->capacity == 0)) {
            while (((ch->count > 0) && !(ch->closed))) {
                pthread_cond_wait(((void*)((&ch->not_full))), ((void*)((&ch->mutex))));
            }
            if (ch->closed) {
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_void_thread_ChanError){ .is_ok = false, .data.err = thread_ChanError_send_on_closed });
            } else {
                ch->buffer = ((int64_t*)(((uint64_t)(value))));
                ch->count = 1;
                pthread_cond_signal(((void*)((&ch->not_empty))));
                while (((ch->count > 0) && !(ch->closed))) {
                    pthread_cond_wait(((void*)((&ch->not_full))), ((void*)((&ch->mutex))));
                }
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_void_thread_ChanError){ .is_ok = true, .data.ok = 0 });
            }
        } else {
            while (((ch->count >= ch->capacity) && !(ch->closed))) {
                pthread_cond_wait(((void*)((&ch->not_full))), ((void*)((&ch->mutex))));
            }
            if (ch->closed) {
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_void_thread_ChanError){ .is_ok = false, .data.err = thread_ChanError_send_on_closed });
            } else {
                (*(ch->buffer + ch->tail)) = value;
                ch->tail = ((ch->tail + 1) % ch->capacity);
                ch->count = (ch->count + 1);
                pthread_cond_signal(((void*)((&ch->not_empty))));
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_void_thread_ChanError){ .is_ok = true, .data.ok = 0 });
            }
        }
    }
}

slop_result_int_thread_ChanError thread_recv(slop_chan_int* ch) {
    SLOP_PRE(((ch != NULL)), "(!= ch nil)");
    pthread_mutex_lock(((void*)((&ch->mutex))));
    while (((ch->count == 0) && !(ch->closed))) {
        pthread_cond_wait(((void*)((&ch->not_empty))), ((void*)((&ch->mutex))));
    }
    if (((ch->count == 0) && ch->closed)) {
        pthread_mutex_unlock(((void*)((&ch->mutex))));
        return ((slop_result_int_thread_ChanError){ .is_ok = false, .data.err = thread_ChanError_closed });
    } else {
        if ((ch->capacity == 0)) {
            {
                __auto_type value = ((int64_t)(((uint64_t)(ch->buffer))));
                ch->count = 0;
                pthread_cond_signal(((void*)((&ch->not_full))));
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_int_thread_ChanError){ .is_ok = true, .data.ok = value });
            }
        } else {
            {
                __auto_type value = (*(ch->buffer + ch->head));
                ch->head = ((ch->head + 1) % ch->capacity);
                ch->count = (ch->count - 1);
                pthread_cond_signal(((void*)((&ch->not_full))));
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_int_thread_ChanError){ .is_ok = true, .data.ok = value });
            }
        }
    }
}

slop_result_int_thread_ChanError thread_try_recv(slop_chan_int* ch) {
    SLOP_PRE(((ch != NULL)), "(!= ch nil)");
    pthread_mutex_lock(((void*)((&ch->mutex))));
    if ((ch->count == 0)) {
        pthread_mutex_unlock(((void*)((&ch->mutex))));
        if (ch->closed) {
            return ((slop_result_int_thread_ChanError){ .is_ok = false, .data.err = thread_ChanError_closed });
        } else {
            return ((slop_result_int_thread_ChanError){ .is_ok = false, .data.err = thread_ChanError_would_block });
        }
    } else {
        if ((ch->capacity == 0)) {
            {
                __auto_type value = ((int64_t)(((uint64_t)(ch->buffer))));
                ch->count = 0;
                pthread_cond_signal(((void*)((&ch->not_full))));
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_int_thread_ChanError){ .is_ok = true, .data.ok = value });
            }
        } else {
            {
                __auto_type value = (*(ch->buffer + ch->head));
                ch->head = ((ch->head + 1) % ch->capacity);
                ch->count = (ch->count - 1);
                pthread_cond_signal(((void*)((&ch->not_full))));
                pthread_mutex_unlock(((void*)((&ch->mutex))));
                return ((slop_result_int_thread_ChanError){ .is_ok = true, .data.ok = value });
            }
        }
    }
}

slop_thread_int* thread_spawn(slop_arena* arena, slop_closure_t func) {
    slop_thread_int* _retval = {0};
    {
        __auto_type th = ((thread_ThreadInt*)(({ __auto_type _alloc = (thread_ThreadInt*)slop_arena_alloc(arena, sizeof(thread_ThreadInt)); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; })));
        (*th).func = ((void*)(func.fn));
        (*th).env = NULL;
        (*th).done = 0;
        pthread_create((&(*th).id), NULL, ((void*)((void*)slop_thread_int_entry)), ((void*)(th)));
        _retval = ((slop_thread_int*)(th));
    }
    SLOP_POST(((_retval != NULL)), "(!= $result nil)");
    return _retval;
}

slop_thread_int* thread_spawn_closure(slop_arena* arena, thread_Closure closure) {
    slop_thread_int* _retval = {0};
    {
        __auto_type th = ((thread_ThreadInt*)(({ __auto_type _alloc = (thread_ThreadInt*)slop_arena_alloc(arena, sizeof(thread_ThreadInt)); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; })));
        (*th).func = closure.fn;
        (*th).env = closure.env;
        (*th).done = 0;
        pthread_create((&(*th).id), NULL, ((void*)((void*)slop_thread_int_entry)), ((void*)(th)));
        _retval = ((slop_thread_int*)(th));
    }
    SLOP_POST(((_retval != NULL)), "(!= $result nil)");
    return _retval;
}

thread_ThreadWithChan* thread_spawn_with_chan(slop_arena* arena, slop_closure_t func, slop_chan_int* ch) {
    SLOP_PRE(((ch != NULL)), "(!= ch nil)");
    thread_ThreadWithChan* _retval = {0};
    {
        __auto_type th = ((thread_ThreadWithChan*)(({ __auto_type _alloc = (thread_ThreadWithChan*)slop_arena_alloc(arena, sizeof(thread_ThreadWithChan)); if (_alloc == NULL) { fprintf(stderr, "SLOP: arena alloc failed at %s:%d\n", __FILE__, __LINE__); abort(); } _alloc; })));
        (*th).func = ((void*)(func.fn));
        (*th).chan = ch;
        (*th).env = NULL;
        (*th).done = 0;
        pthread_create((&(*th).id), NULL, ((void*)(thread_thread_with_chan_entry)), ((void*)(th)));
        _retval = th;
    }
    SLOP_POST(((_retval != NULL)), "(!= $result nil)");
    return _retval;
}

void* thread_thread_with_chan_entry(void* arg) {
    {
        __auto_type th = ((thread_ThreadWithChan*)(arg));
        __auto_type ch = th->chan;
        if (th->env) {
            {
                __auto_type closure_func = ((int64_t(*)(void*, slop_chan_int*))(th->func));
                th->result = closure_func(th->env, ch);
            }
        } else {
            {
                __auto_type user_func = ((int64_t(*)(slop_chan_int*))(th->func));
                th->result = user_func(ch);
            }
        }
        th->done = 1;
        return NULL;
    }
}

int64_t thread_join(slop_thread_int* thread) {
    SLOP_PRE(((thread != NULL)), "(!= thread nil)");
    pthread_join(thread->id, NULL);
    return thread->result;
}

