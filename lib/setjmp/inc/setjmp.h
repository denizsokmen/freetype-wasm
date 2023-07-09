#ifndef WASM_SUPPORT_SETJMP_H
#define WASM_SUPPORT_SETJMP_H

#include <stdbool.h>

typedef struct {
    // A payload value given by longjmp and returned by setjmp for the second time
    int payload;
    // Internal state field
    int state;
} wasm_jmp_buf;

// noinline to avoid breaking Asyncify assumption
__attribute__((noinline)) int wasm_setjmp(wasm_jmp_buf *env);
__attribute__((noinline)) void wasm_longjmp(wasm_jmp_buf *env, int payload);

//
// POSIX-compatible declarations
//
typedef wasm_jmp_buf jmp_buf;

#define setjmp(env) ((env).state = 0, wasm_setjmp(&(env)))
#define longjmp(env, payload) (wasm_longjmp(&env, payload), __builtin_unreachable())


#endif
