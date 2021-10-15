	.file	"f1.c"
	.intel_syntax noprefix
	.text
	.globl	f1
	.def	f1;	.scl	2;	.type	32;	.endef
	.seh_proc	f1
f1:
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	ebx, ecx
	cmp	ecx, 1
	jg	.L4
	mov	eax, 1
.L1:
	add	rsp, 32
	pop	rbx
	ret
.L4:
	lea	ecx, -1[rcx]
	call	f1
	imul	eax, ebx
	jmp	.L1
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-posix-seh, built by Brecht Sanders) 11.1.0"
