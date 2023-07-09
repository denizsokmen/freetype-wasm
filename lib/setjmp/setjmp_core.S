	# extern int wasm_setjmp_internal(wasm_jmp_buf *env);
	.functype	wasm_setjmp_internal (i32) -> (i32)
	# extern int __stack_pointer;
	.globaltype 	__stack_pointer, i32

	# A wrapper of wasm_setjmp_internal to save and restore stack pointer
	# This cannot be implemented in C because there is no way to manipulate stack pointer
	# without C-epilogue.

	# extern int wasm_setjmp(wasm_jmp_buf *env);
	.section	.text.wasm_setjmp,"",@
	.globl		wasm_setjmp
	.type		wasm_setjmp,@function
wasm_setjmp:
	.functype	wasm_setjmp (i32) -> (i32)
	.local		i32, i32
	# save sp (this local is stored in asyncify stack and restored when rewinding)
	global.get	__stack_pointer
	local.set	1

	local.get	0
	call		wasm_setjmp_internal

	# restore sp
	local.get	1
	global.set	__stack_pointer
	end_function
