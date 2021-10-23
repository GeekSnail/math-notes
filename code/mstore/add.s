	.file	"add.c"
	.intel_syntax noprefix
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 56
	.seh_stackalloc	56
	.seh_endprologue
	mov	rbx, rcx
	mov	QWORD PTR 88[rsp], rdx
	mov	QWORD PTR 96[rsp], r8
	mov	QWORD PTR 104[rsp], r9
	lea	rsi, 88[rsp]
	mov	QWORD PTR 40[rsp], rsi
	mov	ecx, 1
	call	[QWORD PTR __imp___acrt_iob_func[rip]]
	mov	rcx, rax
	mov	r8, rsi
	mov	rdx, rbx
	call	__mingw_vfprintf
	add	rsp, 56
	pop	rbx
	pop	rsi
	ret
	.seh_endproc
	.globl	add
	.def	add;	.scl	2;	.type	32;	.endef
	.seh_proc	add
add:
	.seh_endprologue
	lea	eax, [rcx+rdx]
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "Result: %u\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	sub	rsp, 40
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	mov	edx, 4
	mov	ecx, 3
	call	add
	mov	edx, eax
	lea	rcx, .LC0[rip]
	call	printf
	mov	eax, 0
	add	rsp, 40
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-posix-seh, built by Brecht Sanders) 11.1.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
