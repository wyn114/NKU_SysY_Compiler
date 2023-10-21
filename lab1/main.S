	.text
	.file	"main2.ll"
	.globl	foo                             # -- Begin function foo
	.p2align	4, 0x90
	.type	foo,@function
foo:                                    # @foo
	.cfi_startproc
# %bb.0:
                                        # kill: def $esi killed $esi def $rsi
                                        # kill: def $edi killed $edi def $rdi
	movl	%edi, -4(%rsp)
	movl	%esi, -8(%rsp)
	leal	(%rdi,%rsi), %eax
	retq
.Lfunc_end0:
	.size	foo, .Lfunc_end0-foo
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movl	$4, (%rsp)
	movq	a@GOTPCREL(%rip), %rax
	movl	(%rax), %edi
	movl	$4, %esi
	callq	foo@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	a,@object                       # @a
	.data
	.globl	a
	.p2align	2
a:
	.long	5                               # 0x5
	.size	a, 4

	.section	".note.GNU-stack","",@progbits
