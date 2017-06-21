; ModuleID = 'e000'

%"interface:e000.IScene" = type { %"interface:e000.ITouchInput"* (i8**, i8*)*, void (i8*, %"interface:e000.Canvas"*, i8*)*, void (i8*)*, void (i8*)*, void (i8*, double, double)* }
%"interface:e000.Canvas" = type { void (i8*, double, double, double)*, void (i8*)*, void (i8*, double, double, double, double)* }
%"interface:e000.ITouchInput" = type { void (i8*, i32, double, double)*, void (i8*, i32, double, double)*, void (i8*, i32, double, double, double, double)*, void (i8*, i32)* }
%"classvtable:e000.Shape" = type { i8*, i8*, void (%"class:e000.Shape"*, %"interface:e000.Canvas"*, i8*)*, void (%"class:e000.Shape"*, double, double, double, double)*, void (%"class:e000.Shape"*, double, double, double, double, double)* }
%"class:e000.Shape" = type { %"classvtable:e000.Shape"*, double, double, double, double, double, double, double, double }
%"classvtable:e000.MyScene" = type { i8*, i8*, %"interface:e000.ITouchInput"* (i8**, %"class:e000.MyScene"*)*, void (%"class:e000.MyScene"*, %"interface:e000.Canvas"*, i8*)*, void (%"class:e000.MyScene"*)*, void (%"class:e000.MyScene"*)*, void (%"class:e000.MyScene"*, double, double)*, void (%"class:e000.MyScene"*, i32, double, double)*, void (%"class:e000.MyScene"*, i32, double, double)*, void (%"class:e000.MyScene"*, i32, double, double, double, double)*, void (%"class:e000.MyScene"*, i32)* }
%"class:e000.MyScene" = type { %"classvtable:e000.MyScene"*, %"interface:e000.Canvas"*, i8*, i8*, double, double }

@"classimplements:e000.MyScene" = constant { %"interface:e000.IScene", %"interface:e000.ITouchInput" } { %"interface:e000.IScene" { %"interface:e000.ITouchInput"* (i8**, i8*)* bitcast (%"interface:e000.ITouchInput"* (i8**, %"class:e000.MyScene"*)* @e000.CMyScene.MrequestTouchListener to %"interface:e000.ITouchInput"* (i8**, i8*)*), void (i8*, %"interface:e000.Canvas"*, i8*)* bitcast (void (%"class:e000.MyScene"*, %"interface:e000.Canvas"*, i8*)* @e000.CMyScene.MacquireCanvas to void (i8*, %"interface:e000.Canvas"*, i8*)*), void (i8*)* bitcast (void (%"class:e000.MyScene"*)* @e000.CMyScene.Mupdate to void (i8*)*), void (i8*)* bitcast (void (%"class:e000.MyScene"*)* @e000.CMyScene.Mrender to void (i8*)*), void (i8*, double, double)* bitcast (void (%"class:e000.MyScene"*, double, double)* @e000.CMyScene.Mresize to void (i8*, double, double)*) }, %"interface:e000.ITouchInput" { void (i8*, i32, double, double)* bitcast (void (%"class:e000.MyScene"*, i32, double, double)* @e000.CMyScene.MonTouchBegin to void (i8*, i32, double, double)*), void (i8*, i32, double, double)* bitcast (void (%"class:e000.MyScene"*, i32, double, double)* @e000.CMyScene.MonTouchEnd to void (i8*, i32, double, double)*), void (i8*, i32, double, double, double, double)* bitcast (void (%"class:e000.MyScene"*, i32, double, double, double, double)* @e000.CMyScene.MonTouchMove to void (i8*, i32, double, double, double, double)*), void (i8*, i32)* bitcast (void (%"class:e000.MyScene"*, i32)* @e000.CMyScene.MonTouchCancel to void (i8*, i32)*) } }
@"e000.CShape.@vtable" = constant %"classvtable:e000.Shape" { i8* null, i8* null, void (%"class:e000.Shape"*, %"interface:e000.Canvas"*, i8*)* @e000.CShape.Mdraw, void (%"class:e000.Shape"*, double, double, double, double)* @e000.CShape.MapplyForce, void (%"class:e000.Shape"*, double, double, double, double, double)* @e000.CShape.Mupdate }
@"classimplements:e000.Shape" = constant {} zeroinitializer
@"e000.CMyScene.@vtable" = constant %"classvtable:e000.MyScene" { i8* null, i8* null, %"interface:e000.ITouchInput"* (i8**, %"class:e000.MyScene"*)* @e000.CMyScene.MrequestTouchListener, void (%"class:e000.MyScene"*, %"interface:e000.Canvas"*, i8*)* @e000.CMyScene.MacquireCanvas, void (%"class:e000.MyScene"*)* @e000.CMyScene.Mupdate, void (%"class:e000.MyScene"*)* @e000.CMyScene.Mrender, void (%"class:e000.MyScene"*, double, double)* @e000.CMyScene.Mresize, void (%"class:e000.MyScene"*, i32, double, double)* @e000.CMyScene.MonTouchBegin, void (%"class:e000.MyScene"*, i32, double, double)* @e000.CMyScene.MonTouchEnd, void (%"class:e000.MyScene"*, i32, double, double, double, double)* @e000.CMyScene.MonTouchMove, void (%"class:e000.MyScene"*, i32)* @e000.CMyScene.MonTouchCancel }
@0 = internal constant [16 x i8] c"Canvas acquired!"

define fastcc void @e000.FstratApplication(%"interface:e000.IScene"*, i8*) {
  call void @_startApplication(%"interface:e000.IScene"* %0, i8* %1)
  ret void
}

declare void @_startApplication(%"interface:e000.IScene"*, i8*)

define fastcc void @e000.Frun() {
entry:
  br label %0

; <label>:0                                       ; preds = %entry
  %1 = call double @__jf_double_sqrt(double 5.000000e+00)
  %2 = call fastcc i8* @std.bootstrap.Ffmt(double %1)
  call fastcc void @std.bootstrap.Fprint(i8* %2)
  %3 = call i8* @__jf_allocate_object(i32 ptrtoint (%"class:e000.MyScene"* getelementptr (%"class:e000.MyScene"* null, i32 1) to i32))
  %4 = bitcast i8* %3 to %"class:e000.MyScene"*
  call void @e000.CMyScene.KMyScene(i8* null, i8* null, %"class:e000.MyScene"* %4)
  %5 = bitcast %"class:e000.MyScene"* %4 to i8*
  call fastcc void @e000.FstratApplication(%"interface:e000.IScene"* getelementptr inbounds ({ %"interface:e000.IScene", %"interface:e000.ITouchInput" }* @"classimplements:e000.MyScene", i32 0, i32 0), i8* %5)
  ret void
}

declare double @__jf_double_sqrt(double)

declare fastcc i8* @std.bootstrap.Ffmt(double)

declare fastcc void @std.bootstrap.Fprint(i8*)

declare i8* @__jf_allocate_object(i32)

define fastcc void @e000.CMyScene.KMyScene(i8*, i8*, %"class:e000.MyScene"*) {
entry:
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = getelementptr inbounds %"class:e000.MyScene"* %2, i32 0, i32 1
  store %"interface:e000.Canvas"* null, %"interface:e000.Canvas"** %4
  %5 = getelementptr inbounds %"class:e000.MyScene"* %2, i32 0, i32 2
  store i8* undef, i8** %5
  %6 = call i8* @__jf_empty_array(i32 ptrtoint (i1** getelementptr (i1** null, i32 1) to i32), i8* null)
  %7 = getelementptr inbounds %"class:e000.MyScene"* %2, i32 0, i32 3
  store i8* %6, i8** %7
  %8 = getelementptr inbounds %"class:e000.MyScene"* %2, i32 0, i32 4
  store double 0.000000e+00, double* %8
  %9 = getelementptr inbounds %"class:e000.MyScene"* %2, i32 0, i32 5
  store double 0.000000e+00, double* %9
  %10 = bitcast %"class:e000.MyScene"* %2 to %"classvtable:e000.MyScene"**
  store %"classvtable:e000.MyScene"* @"e000.CMyScene.@vtable", %"classvtable:e000.MyScene"** %10
  %11 = bitcast %"class:e000.MyScene"* %2 to i8*
  call void @__jf_unwind_constructor_stack(i8* %1, i8* %11)
  ret void
}

define fastcc void @e000.CShape.Mdraw(%"class:e000.Shape"*, %"interface:e000.Canvas"*, i8*) {
entry:
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 3
  %5 = load double* %4
  %6 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 4
  %7 = load double* %6
  %8 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 5
  %9 = load double* %8
  %10 = getelementptr inbounds %"interface:e000.Canvas"* %1, i32 0, i32 0
  %11 = load void (i8*, double, double, double)** %10
  call fastcc void %11(i8* %2, double %5, double %7, double %9)
  %12 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 1
  %13 = load double* %12
  %14 = fsub double %13, 3.000000e+00
  %15 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 2
  %16 = load double* %15
  %17 = fsub double %16, 3.000000e+00
  %18 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 1
  %19 = load double* %18
  %20 = fadd double %19, 3.000000e+00
  %21 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 2
  %22 = load double* %21
  %23 = fadd double %22, 3.000000e+00
  %24 = getelementptr inbounds %"interface:e000.Canvas"* %1, i32 0, i32 2
  %25 = load void (i8*, double, double, double, double)** %24
  call fastcc void %25(i8* %2, double %14, double %17, double %20, double %23)
  ret void
}

define fastcc void @e000.CShape.MapplyForce(%"class:e000.Shape"*, double, double, double, double) {
entry:
  %5 = alloca double
  %6 = alloca double
  %7 = alloca double
  br label %8

; <label>:8                                       ; preds = %entry
  %9 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 1
  %10 = load double* %9
  %11 = fsub double %10, %1
  store double %11, double* %5
  %12 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 2
  %13 = load double* %12
  %14 = fsub double %13, %2
  store double %14, double* %6
  %15 = load double* %5
  %16 = load double* %5
  %17 = fmul double %15, %16
  %18 = load double* %6
  %19 = load double* %6
  %20 = fmul double %18, %19
  %21 = fadd double %17, %20
  %22 = call double @__jf_double_sqrt(double %21)
  store double %22, double* %7
  %23 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  %24 = load double* %23
  %25 = fmul double %3, 1.000000e+02
  %26 = load double* %7
  %27 = fadd double 1.000000e+02, %26
  %28 = fdiv double %25, %27
  %29 = fmul double %28, 7.000000e+00
  %30 = fadd double %24, %29
  %31 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  store double %30, double* %31
  %32 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  %33 = load double* %32
  %34 = fmul double %4, 1.000000e+02
  %35 = load double* %7
  %36 = fadd double 1.000000e+02, %35
  %37 = fdiv double %34, %36
  %38 = fmul double %37, 7.000000e+00
  %39 = fadd double %33, %38
  %40 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  store double %39, double* %40
  ret void
}

define fastcc void @e000.CShape.Mupdate(%"class:e000.Shape"*, double, double, double, double, double) {
entry:
  %6 = alloca double
  br label %7

; <label>:7                                       ; preds = %entry
  %8 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 1
  %9 = load double* %8
  %10 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  %11 = load double* %10
  %12 = fmul double %11, %1
  %13 = fadd double %9, %12
  %14 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 1
  store double %13, double* %14
  %15 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 2
  %16 = load double* %15
  %17 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  %18 = load double* %17
  %19 = fmul double %18, %1
  %20 = fadd double %16, %19
  %21 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 2
  store double %20, double* %21
  %22 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  %23 = load double* %22
  %24 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 8
  %25 = load double* %24
  %26 = fmul double %25, %1
  %27 = fadd double %23, %26
  %28 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  store double %27, double* %28
  store double 9.000000e-01, double* %6
  %29 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 1
  %30 = load double* %29
  %31 = fcmp olt double %30, %2
  br i1 %31, label %33, label %32

; <label>:32                                      ; preds = %33, %7
  br label %44

; <label>:33                                      ; preds = %7
  %34 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  %35 = load double* %34
  %36 = fcmp olt double %35, 0.000000e+00
  br i1 %36, label %37, label %32

; <label>:37                                      ; preds = %33
  %38 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  %39 = load double* %38
  %40 = fsub double -0.000000e+00, %39
  %41 = load double* %6
  %42 = fmul double %40, %41
  %43 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  store double %42, double* %43
  br label %44

; <label>:44                                      ; preds = %37, %32
  %45 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 2
  %46 = load double* %45
  %47 = fcmp olt double %46, %3
  br i1 %47, label %49, label %48

; <label>:48                                      ; preds = %49, %44
  br label %60

; <label>:49                                      ; preds = %44
  %50 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  %51 = load double* %50
  %52 = fcmp olt double %51, 0.000000e+00
  br i1 %52, label %53, label %48

; <label>:53                                      ; preds = %49
  %54 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  %55 = load double* %54
  %56 = fsub double -0.000000e+00, %55
  %57 = load double* %6
  %58 = fmul double %56, %57
  %59 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  store double %58, double* %59
  br label %60

; <label>:60                                      ; preds = %53, %48
  %61 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 1
  %62 = load double* %61
  %63 = fcmp ogt double %62, %4
  br i1 %63, label %65, label %64

; <label>:64                                      ; preds = %65, %60
  br label %76

; <label>:65                                      ; preds = %60
  %66 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  %67 = load double* %66
  %68 = fcmp ogt double %67, 0.000000e+00
  br i1 %68, label %69, label %64

; <label>:69                                      ; preds = %65
  %70 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  %71 = load double* %70
  %72 = fsub double -0.000000e+00, %71
  %73 = load double* %6
  %74 = fmul double %72, %73
  %75 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 6
  store double %74, double* %75
  br label %76

; <label>:76                                      ; preds = %69, %64
  %77 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 2
  %78 = load double* %77
  %79 = fcmp ogt double %78, %5
  br i1 %79, label %81, label %80

; <label>:80                                      ; preds = %81, %76
  br label %92

; <label>:81                                      ; preds = %76
  %82 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  %83 = load double* %82
  %84 = fcmp ogt double %83, 0.000000e+00
  br i1 %84, label %85, label %80

; <label>:85                                      ; preds = %81
  %86 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  %87 = load double* %86
  %88 = fsub double -0.000000e+00, %87
  %89 = load double* %6
  %90 = fmul double %88, %89
  %91 = getelementptr inbounds %"class:e000.Shape"* %0, i32 0, i32 7
  store double %90, double* %91
  br label %92

; <label>:92                                      ; preds = %85, %80
  ret void
}

define fastcc void @e000.CShape.KShape(i8*, i8*, %"class:e000.Shape"*, double, double) {
entry:
  br label %5

; <label>:5                                       ; preds = %entry
  %6 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 1
  store double %3, double* %6
  %7 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 2
  store double %4, double* %7
  %8 = call fastcc double @std.bootstrap.Frandom()
  %9 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 3
  store double %8, double* %9
  %10 = call fastcc double @std.bootstrap.Frandom()
  %11 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 4
  store double %10, double* %11
  %12 = call fastcc double @std.bootstrap.Frandom()
  %13 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 5
  store double %12, double* %13
  %14 = call fastcc double @std.bootstrap.Frandom()
  %15 = fsub double %14, 5.000000e-01
  %16 = fmul double %15, 6.000000e+02
  %17 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 6
  store double %16, double* %17
  %18 = call fastcc double @std.bootstrap.Frandom()
  %19 = fsub double %18, 5.000000e-01
  %20 = fmul double %19, 6.000000e+02
  %21 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 7
  store double %20, double* %21
  %22 = getelementptr inbounds %"class:e000.Shape"* %2, i32 0, i32 8
  store double 5.000000e+02, double* %22
  %23 = bitcast %"class:e000.Shape"* %2 to %"classvtable:e000.Shape"**
  store %"classvtable:e000.Shape"* @"e000.CShape.@vtable", %"classvtable:e000.Shape"** %23
  %24 = bitcast %"class:e000.Shape"* %2 to i8*
  call void @__jf_unwind_constructor_stack(i8* %1, i8* %24)
  ret void
}

declare fastcc double @std.bootstrap.Frandom()

declare void @__jf_unwind_constructor_stack(i8*, i8*)

define fastcc %"interface:e000.ITouchInput"* @e000.CMyScene.MrequestTouchListener(i8**, %"class:e000.MyScene"*) {
entry:
  br label %2

; <label>:2                                       ; preds = %entry
  %3 = bitcast %"class:e000.MyScene"* %1 to i8*
  store i8* %3, i8** %0
  ret %"interface:e000.ITouchInput"* bitcast (void (i8*, i32, double, double)** getelementptr inbounds ({ %"interface:e000.IScene", %"interface:e000.ITouchInput" }* @"classimplements:e000.MyScene", i32 0, i32 1, i32 0) to %"interface:e000.ITouchInput"*)
}

define fastcc void @e000.CMyScene.MacquireCanvas(%"class:e000.MyScene"*, %"interface:e000.Canvas"*, i8*) {
entry:
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = call i8* @__jf_make_string(i8* getelementptr inbounds ([16 x i8]* @0, i32 0, i32 0), i32 16)
  call fastcc void @std.bootstrap.Fprint(i8* %4)
  %5 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 1
  store %"interface:e000.Canvas"* %1, %"interface:e000.Canvas"** %5
  %6 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 2
  store i8* %2, i8** %6
  ret void
}

define fastcc void @e000.CMyScene.Mupdate(%"class:e000.MyScene"*) {
entry:
  %1 = alloca i32
  %2 = alloca i32
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 3
  %5 = load i8** %4
  %6 = call i32 @__jf_array_size(i8* %5)
  store i32 %6, i32* %2
  store i32 0, i32* %1
  br label %7

; <label>:7                                       ; preds = %12, %3
  %8 = load i32* %1
  %9 = load i32* %2
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %12, label %11

; <label>:11                                      ; preds = %7
  ret void

; <label>:12                                      ; preds = %7
  %13 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 3
  %14 = load i8** %13
  %15 = load i32* %1
  %16 = call i8* @__jf_array_ref(i8* %14, i32 %15)
  %17 = bitcast i8* %16 to { %"class:e000.Shape"* }*
  %18 = getelementptr inbounds { %"class:e000.Shape"* }* %17, i32 0, i32 0
  %19 = load %"class:e000.Shape"** %18
  %20 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 4
  %21 = load double* %20
  %22 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 5
  %23 = load double* %22
  %24 = bitcast %"class:e000.Shape"* %19 to %"classvtable:e000.Shape"**
  %25 = load %"classvtable:e000.Shape"** %24
  %26 = getelementptr inbounds %"classvtable:e000.Shape"* %25, i32 0, i32 4
  %27 = load void (%"class:e000.Shape"*, double, double, double, double, double)** %26
  call fastcc void %27(%"class:e000.Shape"* %19, double 2.000000e-02, double 0.000000e+00, double 0.000000e+00, double %21, double %23)
  %28 = load i32* %1
  %29 = add i32 %28, 1
  store i32 %29, i32* %1
  br label %7
}

define fastcc void @e000.CMyScene.Mrender(%"class:e000.MyScene"*) {
entry:
  %1 = alloca i32
  %2 = alloca i32
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 1
  %5 = load %"interface:e000.Canvas"** %4
  %6 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 2
  %7 = load i8** %6
  %8 = icmp ne %"interface:e000.Canvas"* %5, null
  br i1 %8, label %10, label %9

; <label>:9                                       ; preds = %3
  br label %24

; <label>:10                                      ; preds = %3
  %11 = getelementptr inbounds %"interface:e000.Canvas"* %5, i32 0, i32 1
  %12 = load void (i8*)** %11
  call fastcc void %12(i8* %7)
  %13 = getelementptr inbounds %"interface:e000.Canvas"* %5, i32 0, i32 0
  %14 = load void (i8*, double, double, double)** %13
  call fastcc void %14(i8* %7, double 1.000000e+00, double 0.000000e+00, double 0.000000e+00)
  %15 = getelementptr inbounds %"interface:e000.Canvas"* %5, i32 0, i32 2
  %16 = load void (i8*, double, double, double, double)** %15
  call fastcc void %16(i8* %7, double 1.000000e+02, double 1.000000e+02, double 3.000000e+02, double 2.000000e+02)
  %17 = getelementptr inbounds %"interface:e000.Canvas"* %5, i32 0, i32 0
  %18 = load void (i8*, double, double, double)** %17
  call fastcc void %18(i8* %7, double 0.000000e+00, double 0.000000e+00, double 1.000000e+00)
  %19 = getelementptr inbounds %"interface:e000.Canvas"* %5, i32 0, i32 2
  %20 = load void (i8*, double, double, double, double)** %19
  call fastcc void %20(i8* %7, double 2.000000e+02, double 5.000000e+01, double 2.600000e+02, double 3.000000e+02)
  %21 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 3
  %22 = load i8** %21
  %23 = call i32 @__jf_array_size(i8* %22)
  store i32 %23, i32* %2
  store i32 0, i32* %1
  br label %25

; <label>:24                                      ; preds = %29, %9
  ret void

; <label>:25                                      ; preds = %30, %10
  %26 = load i32* %1
  %27 = load i32* %2
  %28 = icmp slt i32 %26, %27
  br i1 %28, label %30, label %29

; <label>:29                                      ; preds = %25
  br label %24

; <label>:30                                      ; preds = %25
  %31 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 3
  %32 = load i8** %31
  %33 = load i32* %1
  %34 = call i8* @__jf_array_ref(i8* %32, i32 %33)
  %35 = bitcast i8* %34 to { %"class:e000.Shape"* }*
  %36 = getelementptr inbounds { %"class:e000.Shape"* }* %35, i32 0, i32 0
  %37 = load %"class:e000.Shape"** %36
  %38 = bitcast %"class:e000.Shape"* %37 to %"classvtable:e000.Shape"**
  %39 = load %"classvtable:e000.Shape"** %38
  %40 = getelementptr inbounds %"classvtable:e000.Shape"* %39, i32 0, i32 2
  %41 = load void (%"class:e000.Shape"*, %"interface:e000.Canvas"*, i8*)** %40
  call fastcc void %41(%"class:e000.Shape"* %37, %"interface:e000.Canvas"* %5, i8* %7)
  %42 = load i32* %1
  %43 = add i32 %42, 1
  store i32 %43, i32* %1
  br label %25
}

define fastcc void @e000.CMyScene.Mresize(%"class:e000.MyScene"*, double, double) {
entry:
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 4
  store double %1, double* %4
  %5 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 5
  store double %2, double* %5
  ret void
}

define fastcc void @e000.CMyScene.MonTouchBegin(%"class:e000.MyScene"*, i32, double, double) {
entry:
  br label %4

; <label>:4                                       ; preds = %entry
  ret void
}

define fastcc void @e000.CMyScene.MonTouchEnd(%"class:e000.MyScene"*, i32, double, double) {
entry:
  br label %4

; <label>:4                                       ; preds = %entry
  ret void
}

define fastcc void @e000.CMyScene.MonTouchMove(%"class:e000.MyScene"*, i32, double, double, double, double) {
entry:
  %6 = alloca i32
  %7 = alloca i32
  br label %8

; <label>:8                                       ; preds = %entry
  %9 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 3
  %10 = load i8** %9
  %11 = call i32 @__jf_array_size(i8* %10)
  store i32 %11, i32* %7
  store i32 0, i32* %6
  br label %12

; <label>:12                                      ; preds = %24, %8
  %13 = load i32* %6
  %14 = load i32* %7
  %15 = icmp slt i32 %13, %14
  br i1 %15, label %24, label %16

; <label>:16                                      ; preds = %12
  %17 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 3
  %18 = load i8** %17
  %19 = call i8* @__jf_allocate_object(i32 ptrtoint (%"class:e000.Shape"* getelementptr (%"class:e000.Shape"* null, i32 1) to i32))
  %20 = bitcast i8* %19 to %"class:e000.Shape"*
  call void @e000.CShape.KShape(i8* null, i8* null, %"class:e000.Shape"* %20, double %4, double %5)
  %21 = call i8* @__jf_array_push(i8* %18)
  %22 = bitcast i8* %21 to { %"class:e000.Shape"* }*
  %23 = getelementptr inbounds { %"class:e000.Shape"* }* %22, i32 0, i32 0
  store %"class:e000.Shape"* %20, %"class:e000.Shape"** %23
  ret void

; <label>:24                                      ; preds = %12
  %25 = getelementptr inbounds %"class:e000.MyScene"* %0, i32 0, i32 3
  %26 = load i8** %25
  %27 = load i32* %6
  %28 = call i8* @__jf_array_ref(i8* %26, i32 %27)
  %29 = bitcast i8* %28 to { %"class:e000.Shape"* }*
  %30 = getelementptr inbounds { %"class:e000.Shape"* }* %29, i32 0, i32 0
  %31 = load %"class:e000.Shape"** %30
  %32 = fsub double %4, %2
  %33 = fsub double %5, %3
  %34 = bitcast %"class:e000.Shape"* %31 to %"classvtable:e000.Shape"**
  %35 = load %"classvtable:e000.Shape"** %34
  %36 = getelementptr inbounds %"classvtable:e000.Shape"* %35, i32 0, i32 3
  %37 = load void (%"class:e000.Shape"*, double, double, double, double)** %36
  call fastcc void %37(%"class:e000.Shape"* %31, double %4, double %5, double %32, double %33)
  %38 = load i32* %6
  %39 = add i32 %38, 1
  store i32 %39, i32* %6
  br label %12
}

define fastcc void @e000.CMyScene.MonTouchCancel(%"class:e000.MyScene"*, i32) {
entry:
  br label %2

; <label>:2                                       ; preds = %entry
  ret void
}

declare i8* @__jf_make_string(i8*, i32)

declare i32 @__jf_array_size(i8*)

declare i8* @__jf_array_ref(i8*, i32)

declare i8* @__jf_array_push(i8*)

declare i8* @__jf_empty_array(i32, i8*)

define void @__jf_main() {
entry:
  call fastcc void @e000.Frun()
  ret void
}
