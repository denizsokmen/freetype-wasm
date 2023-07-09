/*
 * https://github.com/kripken/talks/blob/991fb1e4b6d7e4b0ea6b3e462d5643f11d422771/jmp.c
 */
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "setjmp.h"

enum wasm_jmp_buf_state {
    // Initial state
    JMP_BUF_STATE_INITIALIZED = 0,
    // Ready for longjmp
    JMP_BUF_STATE_CAPTURED    = 1,
    // Unwinding to the root or rewinding to the setjmp call
    // to restore the execution context
    JMP_BUF_STATE_RETURNING   = 2,
};

static wasm_jmp_buf *wasm_active_jmpbuf;

__attribute__((noinline))
int
wasm_setjmp_internal(wasm_jmp_buf *env)
{
    printf("setjmp called\n");
    switch (env->state) {
    case JMP_BUF_STATE_INITIALIZED: {
        env->state = JMP_BUF_STATE_CAPTURED;
        env->payload = 0;
        wasm_active_jmpbuf = env;
        return 0;
    }
    case JMP_BUF_STATE_RETURNING: {
        env->state = JMP_BUF_STATE_CAPTURED;
        wasm_active_jmpbuf = NULL;
        return env->payload;
    }
    default:
        assert(0 && "unexpected state");
    }
    return 0;
}

void
wasm_longjmp(wasm_jmp_buf* env, int value)
{
    printf("longjmp called\n");
    assert(env->state == JMP_BUF_STATE_CAPTURED);
    assert(value != 0);
    env->state = JMP_BUF_STATE_RETURNING;
    env->payload = value;
    wasm_active_jmpbuf = env;
}
