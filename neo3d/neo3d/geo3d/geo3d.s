	.file	"geo3d.c"
	.text
.globl initGeo3d
	.type	initGeo3d, @function
initGeo3d:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	newVertex
	movl	%eax, v_buffer
	call	newVertex
	movl	%eax, v_buffer2
	call	newMatrix
	movl	%eax, m_buffer
	leave
	ret
	.size	initGeo3d, .-initGeo3d
.globl newMatrix
	.type	newMatrix, @function
newMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$128, (%esp)
	call	malloc
	leave
	ret
	.size	newMatrix, .-newMatrix
.globl newVertex
	.type	newVertex, @function
newVertex:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$32, (%esp)
	call	malloc
	leave
	ret
	.size	newVertex, .-newVertex
.globl setMatrix
	.type	setMatrix, @function
setMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	addl	$-128, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	fldl	20(%ebp)
	fstpl	-16(%ebp)
	fldl	28(%ebp)
	fstpl	-24(%ebp)
	fldl	36(%ebp)
	fstpl	-32(%ebp)
	fldl	44(%ebp)
	fstpl	-40(%ebp)
	fldl	52(%ebp)
	fstpl	-48(%ebp)
	fldl	60(%ebp)
	fstpl	-56(%ebp)
	fldl	68(%ebp)
	fstpl	-64(%ebp)
	fldl	76(%ebp)
	fstpl	-72(%ebp)
	fldl	84(%ebp)
	fstpl	-80(%ebp)
	fldl	92(%ebp)
	fstpl	-88(%ebp)
	fldl	100(%ebp)
	fstpl	-96(%ebp)
	fldl	108(%ebp)
	fstpl	-104(%ebp)
	fldl	116(%ebp)
	fstpl	-112(%ebp)
	fldl	124(%ebp)
	fstpl	-120(%ebp)
	fldl	132(%ebp)
	fstpl	-128(%ebp)
	movl	8(%ebp), %eax
	fldl	-8(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$8, %eax
	fldl	-40(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$16, %eax
	fldl	-72(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$24, %eax
	fldl	-104(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$32, %eax
	fldl	-16(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$40, %eax
	fldl	-48(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$48, %eax
	fldl	-80(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$56, %eax
	fldl	-112(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$64, %eax
	fldl	-24(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$72, %eax
	fldl	-56(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$80, %eax
	fldl	-88(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$88, %eax
	fldl	-120(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$96, %eax
	fldl	-32(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$104, %eax
	fldl	-64(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$112, %eax
	fldl	-96(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$120, %eax
	fldl	-128(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	leave
	ret
	.size	setMatrix, .-setMatrix
.globl setVertex
	.type	setVertex, @function
setVertex:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	fldl	20(%ebp)
	fstpl	-16(%ebp)
	fldl	28(%ebp)
	fstpl	-24(%ebp)
	fldl	36(%ebp)
	fstpl	-32(%ebp)
	movl	8(%ebp), %eax
	fldl	-8(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$8, %eax
	fldl	-16(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$16, %eax
	fldl	-24(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$24, %eax
	fldl	-32(%ebp)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	leave
	ret
	.size	setVertex, .-setVertex
.globl vertexXvertex
	.type	vertexXvertex, @function
vertexXvertex:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %eax
	addl	$8, %eax
	movl	16(%ebp), %edx
	addl	$16, %edx
	fldl	(%eax)
	fmull	(%edx)
	movl	12(%ebp), %eax
	addl	$16, %eax
	movl	16(%ebp), %edx
	addl	$8, %edx
	fldl	(%eax)
	fmull	(%edx)
	fsubrp	%st, %st(1)
	fstpl	(%ecx)
	movl	8(%ebp), %ecx
	addl	$8, %ecx
	movl	12(%ebp), %eax
	addl	$16, %eax
	movl	16(%ebp), %edx
	fldl	(%eax)
	fmull	(%edx)
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	addl	$16, %edx
	fldl	(%eax)
	fmull	(%edx)
	fsubrp	%st, %st(1)
	fstpl	(%ecx)
	movl	8(%ebp), %ecx
	addl	$16, %ecx
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	addl	$8, %edx
	fldl	(%eax)
	fmull	(%edx)
	movl	12(%ebp), %eax
	addl	$8, %eax
	movl	16(%ebp), %edx
	fldl	(%eax)
	fmull	(%edx)
	fsubrp	%st, %st(1)
	fstpl	(%ecx)
	movl	8(%ebp), %eax
	addl	$24, %eax
	fldz
	fstpl	(%eax)
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.size	vertexXvertex, .-vertexXvertex
.globl matrixXvertex
	.type	matrixXvertex, @function
matrixXvertex:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	fldz
	fstpl	28(%esp)
	fldz
	fstpl	20(%esp)
	fldz
	fstpl	12(%esp)
	fldz
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setVertex
	movl	$0, -16(%ebp)
.L11:
	cmpl	$3, -16(%ebp)
	jle	.L14
	jmp	.L12
.L14:
	movl	$0, -20(%ebp)
.L15:
	cmpl	$3, -20(%ebp)
	jle	.L18
	jmp	.L13
.L18:
	movl	-16(%ebp), %eax
	sall	$3, %eax
	movl	%eax, -24(%ebp)
	movl	8(%ebp), %esi
	movl	-16(%ebp), %eax
	leal	0(,%eax,8), %edi
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-20(%ebp), %eax
	sall	$2, %eax
	addl	-16(%ebp), %eax
	leal	0(,%eax,8), %ebx
	movl	12(%ebp), %ecx
	movl	-20(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	fldl	(%ecx,%ebx)
	fmull	(%eax,%edx)
	movl	-28(%ebp), %eax
	fldl	(%eax,%edi)
	faddp	%st, %st(1)
	movl	-24(%ebp), %eax
	fstpl	(%esi,%eax)
	leal	-20(%ebp), %eax
	incl	(%eax)
	jmp	.L15
.L13:
	leal	-16(%ebp), %eax
	incl	(%eax)
	jmp	.L11
.L12:
	movl	8(%ebp), %eax
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	matrixXvertex, .-matrixXvertex
.globl matrixXmatrix
	.type	matrixXmatrix, @function
matrixXmatrix:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$156, %esp
	fldz
	fstpl	124(%esp)
	fldz
	fstpl	116(%esp)
	fldz
	fstpl	108(%esp)
	fldz
	fstpl	100(%esp)
	fldz
	fstpl	92(%esp)
	fldz
	fstpl	84(%esp)
	fldz
	fstpl	76(%esp)
	fldz
	fstpl	68(%esp)
	fldz
	fstpl	60(%esp)
	fldz
	fstpl	52(%esp)
	fldz
	fstpl	44(%esp)
	fldz
	fstpl	36(%esp)
	fldz
	fstpl	28(%esp)
	fldz
	fstpl	20(%esp)
	fldz
	fstpl	12(%esp)
	fldz
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setMatrix
	movl	%eax, 8(%ebp)
	movl	$0, -16(%ebp)
.L20:
	cmpl	$3, -16(%ebp)
	jle	.L23
	jmp	.L21
.L23:
	movl	$0, -20(%ebp)
.L24:
	cmpl	$3, -20(%ebp)
	jle	.L27
	jmp	.L22
.L27:
	movl	$0, -24(%ebp)
.L28:
	cmpl	$3, -24(%ebp)
	jle	.L31
	jmp	.L26
.L31:
	movl	-20(%ebp), %eax
	sall	$2, %eax
	addl	-16(%ebp), %eax
	sall	$3, %eax
	movl	%eax, -28(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-20(%ebp), %eax
	sall	$2, %eax
	addl	-16(%ebp), %eax
	leal	0(,%eax,8), %esi
	movl	8(%ebp), %edi
	movl	-24(%ebp), %eax
	sall	$2, %eax
	addl	-16(%ebp), %eax
	leal	0(,%eax,8), %ecx
	movl	12(%ebp), %ebx
	movl	-20(%ebp), %eax
	sall	$2, %eax
	addl	-24(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	fldl	(%ebx,%ecx)
	fmull	(%eax,%edx)
	fldl	(%edi,%esi)
	faddp	%st, %st(1)
	movl	-28(%ebp), %edx
	movl	-32(%ebp), %eax
	fstpl	(%eax,%edx)
	leal	-24(%ebp), %eax
	incl	(%eax)
	jmp	.L28
.L26:
	leal	-20(%ebp), %eax
	incl	(%eax)
	jmp	.L24
.L22:
	leal	-16(%ebp), %eax
	incl	(%eax)
	jmp	.L20
.L21:
	movl	8(%ebp), %eax
	addl	$156, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	matrixXmatrix, .-matrixXmatrix
.globl addVertex
	.type	addVertex, @function
addVertex:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	fldl	(%eax)
	faddl	(%edx)
	fstpl	(%ecx)
	movl	8(%ebp), %ecx
	addl	$8, %ecx
	movl	12(%ebp), %eax
	addl	$8, %eax
	movl	16(%ebp), %edx
	addl	$8, %edx
	fldl	(%eax)
	faddl	(%edx)
	fstpl	(%ecx)
	movl	8(%ebp), %ecx
	addl	$16, %ecx
	movl	12(%ebp), %eax
	addl	$16, %eax
	movl	16(%ebp), %edx
	addl	$16, %edx
	fldl	(%eax)
	faddl	(%edx)
	fstpl	(%ecx)
	movl	8(%ebp), %eax
	addl	$24, %eax
	fld1
	fstpl	(%eax)
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.size	addVertex, .-addVertex
.globl subVertex
	.type	subVertex, @function
subVertex:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	fldl	(%eax)
	fsubl	(%edx)
	fstpl	(%ecx)
	movl	8(%ebp), %ecx
	addl	$8, %ecx
	movl	12(%ebp), %eax
	addl	$8, %eax
	movl	16(%ebp), %edx
	addl	$8, %edx
	fldl	(%eax)
	fsubl	(%edx)
	fstpl	(%ecx)
	movl	8(%ebp), %ecx
	addl	$16, %ecx
	movl	12(%ebp), %eax
	addl	$16, %eax
	movl	16(%ebp), %edx
	addl	$16, %edx
	fldl	(%eax)
	fsubl	(%edx)
	fstpl	(%ecx)
	movl	8(%ebp), %eax
	addl	$24, %eax
	fld1
	fstpl	(%eax)
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.size	subVertex, .-subVertex
	.section	.rodata
	.align 8
.LC14:
	.long	0
	.long	1073741824
	.text
.globl normalVertex
	.type	normalVertex, @function
normalVertex:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	fld1
	fstpl	28(%esp)
	fldz
	fstpl	20(%esp)
	fldz
	fstpl	12(%esp)
	fldz
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setVertex
	movl	%eax, 8(%ebp)
	fldl	.LC14
	fstpl	8(%esp)
	movl	12(%ebp), %eax
	fldl	(%eax)
	fstpl	(%esp)
	call	pow
	fstpl	-16(%ebp)
	fldl	.LC14
	fstpl	8(%esp)
	movl	12(%ebp), %eax
	addl	$8, %eax
	fldl	(%eax)
	fstpl	(%esp)
	call	pow
	fldl	-16(%ebp)
	faddp	%st, %st(1)
	fstpl	-24(%ebp)
	fldl	.LC14
	fstpl	8(%esp)
	movl	12(%ebp), %eax
	addl	$16, %eax
	fldl	(%eax)
	fstpl	(%esp)
	call	pow
	faddl	-24(%ebp)
	fstpl	(%esp)
	call	sqrt
	fstpl	-8(%ebp)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	fldl	(%eax)
	fdivl	-8(%ebp)
	fstpl	(%edx)
	movl	8(%ebp), %edx
	addl	$8, %edx
	movl	12(%ebp), %eax
	addl	$8, %eax
	fldl	(%eax)
	fdivl	-8(%ebp)
	fstpl	(%edx)
	movl	8(%ebp), %edx
	addl	$16, %edx
	movl	12(%ebp), %eax
	addl	$16, %eax
	fldl	(%eax)
	fdivl	-8(%ebp)
	fstpl	(%edx)
	movl	8(%ebp), %eax
	leave
	ret
	.size	normalVertex, .-normalVertex
	.section	.rodata
	.align 8
.LC16:
	.long	0
	.long	1073741824
	.text
.globl lengthVertex
	.type	lengthVertex, @function
lengthVertex:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	fldl	.LC16
	fstpl	8(%esp)
	movl	8(%ebp), %eax
	fldl	(%eax)
	fstpl	(%esp)
	call	pow
	fstpl	-8(%ebp)
	fldl	.LC16
	fstpl	8(%esp)
	movl	8(%ebp), %eax
	addl	$8, %eax
	fldl	(%eax)
	fstpl	(%esp)
	call	pow
	fldl	-8(%ebp)
	faddp	%st, %st(1)
	fstpl	-16(%ebp)
	fldl	.LC16
	fstpl	8(%esp)
	movl	8(%ebp), %eax
	addl	$16, %eax
	fldl	(%eax)
	fstpl	(%esp)
	call	pow
	faddl	-16(%ebp)
	fstpl	(%esp)
	call	sqrt
	leave
	ret
	.size	lengthVertex, .-lengthVertex
.globl dotProduct
	.type	dotProduct, @function
dotProduct:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	fldl	(%eax)
	fmull	(%edx)
	movl	8(%ebp), %eax
	addl	$8, %eax
	movl	12(%ebp), %edx
	addl	$8, %edx
	fldl	(%eax)
	fmull	(%edx)
	faddp	%st, %st(1)
	movl	8(%ebp), %eax
	addl	$16, %eax
	movl	12(%ebp), %edx
	addl	$16, %edx
	fldl	(%eax)
	fmull	(%edx)
	faddp	%st, %st(1)
	popl	%ebp
	ret
	.size	dotProduct, .-dotProduct
.globl radVertex
	.type	radVertex, @function
radVertex:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	dotProduct
	fstpl	-8(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	lengthVertex
	fldl	-8(%ebp)
	fdivp	%st, %st(1)
	fstpl	-16(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	lengthVertex
	fdivrl	-16(%ebp)
	fstpl	(%esp)
	call	acos
	leave
	ret
	.size	radVertex, .-radVertex
.globl degVertex
	.type	degVertex, @function
degVertex:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	radVertex
	fstpl	(%esp)
	call	rad2deg
	leave
	ret
	.size	degVertex, .-degVertex
.globl createTransMatrix
	.type	createTransMatrix, @function
createTransMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$168, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	fldl	20(%ebp)
	fstpl	-16(%ebp)
	fldl	28(%ebp)
	fstpl	-24(%ebp)
	fld1
	fstpl	124(%esp)
	fldz
	fstpl	116(%esp)
	fldz
	fstpl	108(%esp)
	fldz
	fstpl	100(%esp)
	fldl	-24(%ebp)
	fstpl	92(%esp)
	fld1
	fstpl	84(%esp)
	fldz
	fstpl	76(%esp)
	fldz
	fstpl	68(%esp)
	fldl	-16(%ebp)
	fstpl	60(%esp)
	fldz
	fstpl	52(%esp)
	fld1
	fstpl	44(%esp)
	fldz
	fstpl	36(%esp)
	fldl	-8(%ebp)
	fstpl	28(%esp)
	fldz
	fstpl	20(%esp)
	fldz
	fstpl	12(%esp)
	fld1
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setMatrix
	movl	%eax, 8(%ebp)
	movl	8(%ebp), %eax
	leave
	ret
	.size	createTransMatrix, .-createTransMatrix
.globl createScaleMatrix
	.type	createScaleMatrix, @function
createScaleMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$168, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	fldl	20(%ebp)
	fstpl	-16(%ebp)
	fldl	28(%ebp)
	fstpl	-24(%ebp)
	fld1
	fstpl	124(%esp)
	fldz
	fstpl	116(%esp)
	fldz
	fstpl	108(%esp)
	fldz
	fstpl	100(%esp)
	fldz
	fstpl	92(%esp)
	fldl	-24(%ebp)
	fstpl	84(%esp)
	fldz
	fstpl	76(%esp)
	fldz
	fstpl	68(%esp)
	fldz
	fstpl	60(%esp)
	fldz
	fstpl	52(%esp)
	fldl	-16(%ebp)
	fstpl	44(%esp)
	fldz
	fstpl	36(%esp)
	fldz
	fstpl	28(%esp)
	fldz
	fstpl	20(%esp)
	fldz
	fstpl	12(%esp)
	fldl	-8(%ebp)
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setMatrix
	movl	%eax, 8(%ebp)
	movl	8(%ebp), %eax
	leave
	ret
	.size	createScaleMatrix, .-createScaleMatrix
.globl createXRotMatrix
	.type	createXRotMatrix, @function
createXRotMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$184, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fstpl	-16(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	sin
	fstpl	-24(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	sin
	fstpl	-40(%ebp)
	movl	-40(%ebp), %eax
	movl	-36(%ebp), %edx
	xorl	$-2147483648, %edx
	movl	%eax, -32(%ebp)
	movl	%edx, -28(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fld1
	fstpl	124(%esp)
	fldz
	fstpl	116(%esp)
	fldz
	fstpl	108(%esp)
	fldz
	fstpl	100(%esp)
	fldz
	fstpl	92(%esp)
	fldl	-16(%ebp)
	fstpl	84(%esp)
	fldl	-24(%ebp)
	fstpl	76(%esp)
	fldz
	fstpl	68(%esp)
	fldz
	fstpl	60(%esp)
	fldl	-32(%ebp)
	fstpl	52(%esp)
	fstpl	44(%esp)
	fldz
	fstpl	36(%esp)
	fldz
	fstpl	28(%esp)
	fldz
	fstpl	20(%esp)
	fldz
	fstpl	12(%esp)
	fld1
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setMatrix
	movl	%eax, 8(%ebp)
	movl	8(%ebp), %eax
	leave
	ret
	.size	createXRotMatrix, .-createXRotMatrix
.globl createYRotMatrix
	.type	createYRotMatrix, @function
createYRotMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$184, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fstpl	-16(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	sin
	fstpl	-40(%ebp)
	movl	-40(%ebp), %eax
	movl	-36(%ebp), %edx
	xorl	$-2147483648, %edx
	movl	%eax, -24(%ebp)
	movl	%edx, -20(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	sin
	fstpl	-32(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fld1
	fstpl	124(%esp)
	fldz
	fstpl	116(%esp)
	fldz
	fstpl	108(%esp)
	fldz
	fstpl	100(%esp)
	fldz
	fstpl	92(%esp)
	fldl	-16(%ebp)
	fstpl	84(%esp)
	fldz
	fstpl	76(%esp)
	fldl	-24(%ebp)
	fstpl	68(%esp)
	fldz
	fstpl	60(%esp)
	fldz
	fstpl	52(%esp)
	fld1
	fstpl	44(%esp)
	fldz
	fstpl	36(%esp)
	fldz
	fstpl	28(%esp)
	fldl	-32(%ebp)
	fstpl	20(%esp)
	fldz
	fstpl	12(%esp)
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setMatrix
	movl	%eax, 8(%ebp)
	movl	8(%ebp), %eax
	leave
	ret
	.size	createYRotMatrix, .-createYRotMatrix
.globl createZRotMatrix
	.type	createZRotMatrix, @function
createZRotMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$184, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fstpl	-16(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	sin
	fstpl	-24(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	sin
	fstpl	-40(%ebp)
	movl	-40(%ebp), %eax
	movl	-36(%ebp), %edx
	xorl	$-2147483648, %edx
	movl	%eax, -32(%ebp)
	movl	%edx, -28(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fld1
	fstpl	124(%esp)
	fldz
	fstpl	116(%esp)
	fldz
	fstpl	108(%esp)
	fldz
	fstpl	100(%esp)
	fldz
	fstpl	92(%esp)
	fld1
	fstpl	84(%esp)
	fldz
	fstpl	76(%esp)
	fldz
	fstpl	68(%esp)
	fldz
	fstpl	60(%esp)
	fldz
	fstpl	52(%esp)
	fldl	-16(%ebp)
	fstpl	44(%esp)
	fldl	-24(%ebp)
	fstpl	36(%esp)
	fldz
	fstpl	28(%esp)
	fldz
	fstpl	20(%esp)
	fldl	-32(%ebp)
	fstpl	12(%esp)
	fstpl	4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	setMatrix
	movl	%eax, 8(%ebp)
	movl	8(%ebp), %eax
	leave
	ret
	.size	createZRotMatrix, .-createZRotMatrix
.globl createRotMatrix
	.type	createRotMatrix, @function
createRotMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	fldl	12(%ebp)
	fstpl	-8(%ebp)
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	v_buffer, %eax
	movl	%eax, (%esp)
	call	normalVertex
	movl	%eax, -12(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fstpl	-24(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	sin
	fstpl	-32(%ebp)
	fldl	-8(%ebp)
	fstpl	(%esp)
	call	cos
	fld1
	fsubp	%st, %st(1)
	fstpl	-40(%ebp)
	movl	-12(%ebp), %eax
	fldl	(%eax)
	fstpl	-48(%ebp)
	movl	-12(%ebp), %eax
	addl	$8, %eax
	fldl	(%eax)
	fstpl	-56(%ebp)
	movl	-12(%ebp), %eax
	addl	$16, %eax
	fldl	(%eax)
	fstpl	-64(%ebp)
	movl	8(%ebp), %eax
	fldl	-48(%ebp)
	fmull	-48(%ebp)
	fld1
	fsubp	%st, %st(1)
	fmull	-24(%ebp)
	fldl	-48(%ebp)
	fmull	-48(%ebp)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$40, %eax
	fldl	-56(%ebp)
	fmull	-56(%ebp)
	fld1
	fsubp	%st, %st(1)
	fmull	-24(%ebp)
	fldl	-56(%ebp)
	fmull	-56(%ebp)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$80, %eax
	fldl	-64(%ebp)
	fmull	-64(%ebp)
	fld1
	fsubp	%st, %st(1)
	fmull	-24(%ebp)
	fldl	-64(%ebp)
	fmull	-64(%ebp)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$32, %eax
	fldl	-64(%ebp)
	fchs
	fmull	-32(%ebp)
	fldl	-48(%ebp)
	fmull	-56(%ebp)
	fld1
	fsubl	-24(%ebp)
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$8, %eax
	fldl	-64(%ebp)
	fmull	-32(%ebp)
	fldl	-48(%ebp)
	fmull	-56(%ebp)
	fld1
	fsubl	-24(%ebp)
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$64, %eax
	fldl	-56(%ebp)
	fmull	-32(%ebp)
	fldl	-48(%ebp)
	fmull	-64(%ebp)
	fld1
	fsubl	-24(%ebp)
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$16, %eax
	fldl	-56(%ebp)
	fchs
	fmull	-32(%ebp)
	fldl	-48(%ebp)
	fmull	-64(%ebp)
	fld1
	fsubl	-24(%ebp)
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$72, %eax
	fldl	-48(%ebp)
	fchs
	fmull	-32(%ebp)
	fldl	-56(%ebp)
	fmull	-64(%ebp)
	fld1
	fsubl	-24(%ebp)
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$48, %eax
	fldl	-48(%ebp)
	fmull	-32(%ebp)
	fldl	-56(%ebp)
	fmull	-64(%ebp)
	fld1
	fsubl	-24(%ebp)
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$24, %eax
	fldz
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$56, %eax
	fldz
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$88, %eax
	fldz
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$120, %eax
	fld1
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$96, %eax
	fldz
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$104, %eax
	fldz
	fstpl	(%eax)
	movl	8(%ebp), %eax
	addl	$112, %eax
	fldz
	fstpl	(%eax)
	movl	8(%ebp), %eax
	leave
	ret
	.size	createRotMatrix, .-createRotMatrix
	.section	.rodata
	.align 8
.LC39:
	.long	1413754136
	.long	1074340347
	.align 8
.LC40:
	.long	0
	.long	1081507840
	.text
.globl deg2rad
	.type	deg2rad, @function
deg2rad:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	fldl	8(%ebp)
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	fadd	%st(0), %st
	fldl	.LC39
	fmulp	%st, %st(1)
	fldl	.LC40
	fdivrp	%st, %st(1)
	leave
	ret
	.size	deg2rad, .-deg2rad
	.section	.rodata
	.align 8
.LC42:
	.long	0
	.long	1081507840
	.align 8
.LC43:
	.long	0
	.long	1073741824
	.align 8
.LC44:
	.long	1413754136
	.long	1074340347
	.text
.globl rad2deg
	.type	rad2deg, @function
rad2deg:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	fldl	8(%ebp)
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	fldl	.LC42
	fmulp	%st, %st(1)
	fldl	.LC43
	fdivrp	%st, %st(1)
	fldl	.LC44
	fdivrp	%st, %st(1)
	leave
	ret
	.size	rad2deg, .-rad2deg
.globl normalTriangle
	.type	normalTriangle, @function
normalTriangle:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	v_buffer, %eax
	movl	%eax, (%esp)
	call	subVertex
	movl	20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	v_buffer2, %eax
	movl	%eax, (%esp)
	call	subVertex
	movl	v_buffer2, %eax
	movl	%eax, 8(%esp)
	movl	v_buffer, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	vertexXvertex
	movl	8(%ebp), %eax
	leave
	ret
	.size	normalTriangle, .-normalTriangle
	.section	.rodata
.LC46:
	.string	"|%f|\n|%f|\n|%f|\n|%f|\n"
	.text
.globl printVertex
	.type	printVertex, @function
printVertex:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %eax
	addl	$24, %eax
	fldl	(%eax)
	fstpl	28(%esp)
	movl	8(%ebp), %eax
	addl	$16, %eax
	fldl	(%eax)
	fstpl	20(%esp)
	movl	8(%ebp), %eax
	addl	$8, %eax
	fldl	(%eax)
	fstpl	12(%esp)
	movl	8(%ebp), %eax
	fldl	(%eax)
	fstpl	4(%esp)
	movl	$.LC46, (%esp)
	call	printf
	leave
	ret
	.size	printVertex, .-printVertex
	.section	.rodata
	.align 32
.LC48:
	.string	"|%f %f %f %f|\n|%f %f %f %f|\n|%f %f %f %f|\n|%f %f %f %f|\n"
	.text
.globl printMatrix
	.type	printMatrix, @function
printMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$136, %esp
	movl	8(%ebp), %eax
	addl	$120, %eax
	fldl	(%eax)
	fstpl	124(%esp)
	movl	8(%ebp), %eax
	addl	$88, %eax
	fldl	(%eax)
	fstpl	116(%esp)
	movl	8(%ebp), %eax
	addl	$56, %eax
	fldl	(%eax)
	fstpl	108(%esp)
	movl	8(%ebp), %eax
	addl	$24, %eax
	fldl	(%eax)
	fstpl	100(%esp)
	movl	8(%ebp), %eax
	addl	$112, %eax
	fldl	(%eax)
	fstpl	92(%esp)
	movl	8(%ebp), %eax
	addl	$80, %eax
	fldl	(%eax)
	fstpl	84(%esp)
	movl	8(%ebp), %eax
	addl	$48, %eax
	fldl	(%eax)
	fstpl	76(%esp)
	movl	8(%ebp), %eax
	addl	$16, %eax
	fldl	(%eax)
	fstpl	68(%esp)
	movl	8(%ebp), %eax
	addl	$104, %eax
	fldl	(%eax)
	fstpl	60(%esp)
	movl	8(%ebp), %eax
	addl	$72, %eax
	fldl	(%eax)
	fstpl	52(%esp)
	movl	8(%ebp), %eax
	addl	$40, %eax
	fldl	(%eax)
	fstpl	44(%esp)
	movl	8(%ebp), %eax
	addl	$8, %eax
	fldl	(%eax)
	fstpl	36(%esp)
	movl	8(%ebp), %eax
	addl	$96, %eax
	fldl	(%eax)
	fstpl	28(%esp)
	movl	8(%ebp), %eax
	addl	$64, %eax
	fldl	(%eax)
	fstpl	20(%esp)
	movl	8(%ebp), %eax
	addl	$32, %eax
	fldl	(%eax)
	fstpl	12(%esp)
	movl	8(%ebp), %eax
	fldl	(%eax)
	fstpl	4(%esp)
	movl	$.LC48, (%esp)
	call	printf
	leave
	ret
	.size	printMatrix, .-printMatrix
	.comm	v_buffer,4,4
	.comm	v_buffer2,4,4
	.comm	m_buffer,4,4
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.5  (Gentoo Linux 3.3.5-r1, ssp-3.3.2-3, pie-8.7.7.1)"
