	.text
	.def	 e000.Frun;
	.scl	2;
	.type	32;
	.endef
	.globl	e000.Frun
	.align	16, 0x90
e000.Frun:
.Ltmp0:
.seh_proc e000.Frun
	sub	rsp, 40
.Ltmp1:
	.seh_stackalloc 40
.Ltmp2:
	.seh_endprologue
	jmp	.LBB0_1
.LBB0_1:
	call	e000.FsayHello
	nop
	add	rsp, 40
	ret
.Leh_func_end0:
.Ltmp3:
	.seh_endproc

	.def	 e000.FsayHello;
	.scl	2;
	.type	32;
	.endef
	.globl	e000.FsayHello
	.align	16, 0x90
e000.FsayHello:
.Ltmp4:
.seh_proc e000.FsayHello
	sub	rsp, 72
.Ltmp5:
	.seh_stackalloc 72
.Ltmp6:
	.seh_endprologue
	lea	rcx, qword ptr [rip + __unnamed_1]
	mov	edx, 15
	call	__jf_make_string
	mov	rcx, rax
	call	std.bootstrap.Fprint
	mov	dword ptr [rsp + 60], 3
.LBB1_2:
	call	std.bootstrap.Finput
	lea	rcx, qword ptr [rip + __unnamed_2]
	mov	edx, 6
	mov	qword ptr [rsp + 64], rax
	mov	rax, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 48], rax
	call	__jf_make_string
	mov	rcx, qword ptr [rsp + 48]
	mov	rdx, rax
	call	__jf_string_equal
	test	al, 1
	jne	.LBB1_4
	lea	rcx, qword ptr [rip + __unnamed_3]
	mov	edx, 6
	mov	rax, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 40], rax
	call	__jf_make_string
	mov	rcx, qword ptr [rsp + 40]
	mov	rdx, rax
	call	__jf_string_equal
	test	al, 1
	jne	.LBB1_6
	jmp	.LBB1_5
.LBB1_4:
	lea	rcx, qword ptr [rip + __unnamed_4]
	mov	edx, 18
	call	__jf_make_string
	mov	rcx, rax
	call	std.bootstrap.Fprint
	nop
	add	rsp, 72
	ret
.LBB1_5:
	mov	eax, dword ptr [rsp + 60]
	sub	eax, 1
	mov	dword ptr [rsp + 60], eax
	cmp	dword ptr [rsp + 60], 0
	jle	.LBB1_9
	jmp	.LBB1_8
.LBB1_6:
	lea	rcx, qword ptr [rip + __unnamed_5]
	mov	edx, 11
	call	__jf_make_string
	mov	rcx, rax
	call	std.bootstrap.Fbreak
.LBB1_7:
	jmp	.LBB1_10
.LBB1_8:
	lea	rcx, qword ptr [rip + __unnamed_6]
	mov	edx, 29
	call	__jf_make_string
	mov	rcx, rax
	call	std.bootstrap.Fprint
	jmp	.LBB1_11
.LBB1_9:
	lea	rcx, qword ptr [rip + __unnamed_7]
	mov	edx, 44
	call	__jf_make_string
	mov	rcx, rax
	call	std.bootstrap.Fprint
	jmp	.LBB1_11
.LBB1_10:
	cmp	dword ptr [rsp + 60], 0
	je	.LBB1_12
	jmp	.LBB1_2
.LBB1_11:
	jmp	.LBB1_7
.LBB1_12:
	add	rsp, 72
	ret
.Leh_func_end1:
.Ltmp7:
	.seh_endproc

	.def	 __jf_main;
	.scl	2;
	.type	32;
	.endef
	.globl	__jf_main
	.align	16, 0x90
__jf_main:
.Ltmp8:
.seh_proc __jf_main
	sub	rsp, 40
.Ltmp9:
	.seh_stackalloc 40
.Ltmp10:
	.seh_endprologue
	call	e000.Frun
	nop
	add	rsp, 40
	ret
.Leh_func_end2:
.Ltmp11:
	.seh_endproc

	.section	.rdata,"rd"
__unnamed_1:
	.ascii	"Enter password:"

__unnamed_2:
	.ascii	"qwerty"

	.align	16
__unnamed_4:
	.ascii	"Password Accepted!"

__unnamed_3:
	.ascii	"secret"

__unnamed_5:
	.ascii	"Secret pass"

	.align	16
__unnamed_7:
	.ascii	"Incorrect password! Sorry, no more guessing."

	.align	16
__unnamed_6:
	.ascii	"Incorrect password! Try again"


