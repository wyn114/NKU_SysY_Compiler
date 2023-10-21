	.text
	.file	"main0.ll"
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2                               # -- Begin function func
.LCPI0_0:
	.long	0xc0000000                      # float -2
	.text
	.globl	func
	.p2align	4, 0x90
	.type	func,@function
func:                                   # @func
	.cfi_startproc
# %bb.0:
	movl	%edi, -4(%rsp)
	movq	a@GOTPCREL(%rip), %rax
	cvtsi2ss	%edi, %xmm0
	mulss	(%rax), %xmm0
	cvttss2si	%xmm0, %eax
	movq	c@GOTPCREL(%rip), %rcx
	movl	%eax, 4(%rcx)
	movl	(%rcx), %eax
	cltd
	idivl	%edi
	movl	%edx, 8(%rcx)
	cvttps2dq	%xmm0, %xmm0
	cvtdq2ps	%xmm0, %xmm1
	addss	.LCPI0_0(%rip), %xmm1
	xorps	%xmm0, %xmm0
	cvtsi2ss	%edx, %xmm0
	addss	%xmm1, %xmm0
	retq
.Lfunc_end0:
	.size	func, .Lfunc_end0-func
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2                               # -- Begin function main
.LCPI1_0:
	.long	0x40400000                      # float 3
.LCPI1_1:
	.long	0x41a80000                      # float 21
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$0, 20(%rsp)
	movl	$0, 12(%rsp)
	callq	getint@PLT
	movl	%eax, 16(%rsp)
	movq	a@GOTPCREL(%rip), %rax
	movss	.LCPI1_0(%rip), %xmm0           # xmm0 = mem[0],zero,zero,zero
	movq	b@GOTPCREL(%rip), %rcx
	xorps	%xmm1, %xmm1
	movss	.LCPI1_1(%rip), %xmm2           # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB1_1
	.p2align	4, 0x90
.LBB1_4:                                #   in Loop: Header=BB1_1 Depth=1
	incl	12(%rsp)
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$9, 12(%rsp)
	jg	.LBB1_5
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
	movss	(%rax), %xmm3                   # xmm3 = mem[0],zero,zero,zero
	addss	%xmm0, %xmm3
	movss	%xmm3, (%rax)
	movss	(%rcx), %xmm4                   # xmm4 = mem[0],zero,zero,zero
	divss	%xmm3, %xmm4
	ucomiss	%xmm1, %xmm4
	jne	.LBB1_4
	jp	.LBB1_4
# %bb.3:                                #   in Loop: Header=BB1_1 Depth=1
	movss	(%rax), %xmm3                   # xmm3 = mem[0],zero,zero,zero
	ucomiss	%xmm2, %xmm3
	jbe	.LBB1_4
.LBB1_5:
	movl	16(%rsp), %edi
	callq	func@PLT
	cvttss2si	%xmm0, %edi
	callq	putint@PLT
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	k,@object                       # @k
	.section	.rodata,"a",@progbits
	.globl	k
	.p2align	2
k:
	.long	0x40000000                      # float 2
	.size	k, 4

	.type	a,@object                       # @a
	.data
	.globl	a
	.p2align	2
a:
	.long	0x40000000                      # float 2
	.size	a, 4

	.type	b,@object                       # @b
	.globl	b
	.p2align	2
b:
	.long	0x41a00000                      # float 20
	.size	b, 4

	.type	c,@object                       # @c
	.globl	c
	.p2align	2
c:
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.size	c, 12

	.section	".note.GNU-stack","",@progbits
