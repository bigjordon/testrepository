	.file	"example1.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	-20(%rbp), %eax
	cltq
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$9999, (%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$9999, %eax
	jne	.L2
	movl	$5, %eax
	jmp	.L3
.L2:
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
