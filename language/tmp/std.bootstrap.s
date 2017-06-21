	.text
	.def	 std.bootstrap.Ffmt;
	.scl	2;
	.type	32;
	.endef
	.globl	std.bootstrap.Ffmt
	.align	16, 0x90
std.bootstrap.Ffmt:
.Ltmp0:
.seh_proc std.bootstrap.Ffmt
	sub	rsp, 40
.Ltmp1:
	.seh_stackalloc 40
.Ltmp2:
	.seh_endprologue
	call	_fmt
	nop
	add	rsp, 40
	ret
.Leh_func_end0:
.Ltmp3:
	.seh_endproc

	.def	 std.bootstrap.Fprint;
	.scl	2;
	.type	32;
	.endef
	.globl	std.bootstrap.Fprint
	.align	16, 0x90
std.bootstrap.Fprint:
.Ltmp4:
.seh_proc std.bootstrap.Fprint
	sub	rsp, 40
.Ltmp5:
	.seh_stackalloc 40
.Ltmp6:
	.seh_endprologue
	call	_print
	nop
	add	rsp, 40
	ret
.Leh_func_end1:
.Ltmp7:
	.seh_endproc

	.def	 std.bootstrap.Fbreak;
	.scl	2;
	.type	32;
	.endef
	.globl	std.bootstrap.Fbreak
	.align	16, 0x90
std.bootstrap.Fbreak:
.Ltmp8:
.seh_proc std.bootstrap.Fbreak
	sub	rsp, 40
.Ltmp9:
	.seh_stackalloc 40
.Ltmp10:
	.seh_endprologue
	call	_break
	nop
	add	rsp, 40
	ret
.Leh_func_end2:
.Ltmp11:
	.seh_endproc

	.def	 std.bootstrap.Finput;
	.scl	2;
	.type	32;
	.endef
	.globl	std.bootstrap.Finput
	.align	16, 0x90
std.bootstrap.Finput:
.Ltmp12:
.seh_proc std.bootstrap.Finput
	sub	rsp, 40
.Ltmp13:
	.seh_stackalloc 40
.Ltmp14:
	.seh_endprologue
	call	_input
	nop
	add	rsp, 40
	ret
.Leh_func_end3:
.Ltmp15:
	.seh_endproc


