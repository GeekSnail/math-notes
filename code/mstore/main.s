	.file	"main.c"
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	movq	%rcx, %rbx
	movq	%rdx, 88(%rsp)
	movq	%r8, 96(%rsp)
	movq	%r9, 104(%rsp)
	leaq	88(%rsp), %rsi
	movq	%rsi, 40(%rsp)
	movl	$1, %ecx
	call	*__imp___acrt_iob_func(%rip)
	movq	%rax, %rcx
	movq	%rsi, %r8
	movq	%rbx, %rdx
	call	__mingw_vfprintf
	addq	$56, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "2 * 3 --> %ld\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	call	__main
	leaq	44(%rsp), %r8
	movl	$3, %edx
	movl	$2, %ecx
	call	multstore
	movl	44(%rsp), %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	$0, %eax
	addq	$56, %rsp
	ret
	.seh_endproc
	.globl	mult2
	.def	mult2;	.scl	2;	.type	32;	.endef
	.seh_proc	mult2
mult2:
	.seh_endprologue
	movl	%ecx, %eax
	imull	%edx, %eax
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-posix-seh, built by Brecht Sanders) 11.1.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	multstore;	.scl	2;	.type	32;	.endef
