; ModuleID = 'e001'

%"interface:app.Scene.IScene" = type { void (i8*, %"interface:graphics.Context.Context3D"*, i8*)*, %"interface:app.Scene.ITouchListener"* (i8**, i8*)*, void (i8*)*, void (i8*)* }
%"interface:graphics.Context.Context3D" = type { void (i8*, double, double, double, double)*, void (i8*, double)*, void (i8*, i32)*, void (i8*, i1, i1, i1)*, %"interface:graphics.Context.VertexBuffer"* (i8**, i8*, i1, i32, i32)*, %"interface:graphics.Context.IndexBuffer"* (i8**, i8*, i1, i32)*, %"interface:graphics.Context.VertexShader"* (i8**, i8*)*, %"interface:graphics.Context.FragmentShader"* (i8**, i8*)*, %"interface:graphics.Context.Program"* (i8**, i8*, %"interface:graphics.Context.VertexShader"*, i8*, %"interface:graphics.Context.FragmentShader"*, i8*)*, %"interface:graphics.Context.Texture"* (i8**, i8*, i8*, i32, i32)*, void (i8*, i32, %"interface:graphics.Context.VertexBuffer"*, i8*, i8*, i32)*, void (i8*, i32)*, void (i8*, i32, %"interface:graphics.Context.Texture"*, i8*)*, void (i8*, i32)*, void (i8*, i32, double, double, double, double)*, void (i8*, %"interface:graphics.Context.Program"*, i8*)*, void (i8*, %"interface:graphics.Context.IndexBuffer"*, i8*, i32, i32)* }
%"interface:graphics.Context.VertexBuffer" = type { void (i8*, i32, i32, i32, i8*)* }
%"interface:graphics.Context.IndexBuffer" = type { void (i8*, i32, i32, i32, i8*)* }
%"interface:graphics.Context.VertexShader" = type opaque
%"interface:graphics.Context.FragmentShader" = type opaque
%"interface:graphics.Context.Program" = type opaque
%"interface:graphics.Context.Texture" = type opaque
%"interface:app.Scene.ITouchListener" = type { void (i8*, i32)*, void (i8*, i32, double, double)*, void (i8*, i32, double, double)*, void (i8*, i32, double, double, double, double)*, void (i8*, i32)*, void (i8*, i32, double, double, double, double)* }
%"classvtable:e001.Resources" = type { i8*, i8* }
%"classvtable:e001.MyScene" = type { i8*, i8*, void (%"class:e001.MyScene"*, i32)*, void (%"class:e001.MyScene"*, i32, double, double)*, void (%"class:e001.MyScene"*, i32, double, double)*, void (%"class:e001.MyScene"*, i32, double, double, double, double)*, void (%"class:e001.MyScene"*, i32)*, void (%"class:e001.MyScene"*, i32, double, double, double, double)*, void (%"class:e001.MyScene"*, %"interface:graphics.Context.Context3D"*, i8*)*, %"interface:app.Scene.ITouchListener"* (i8**, %"class:e001.MyScene"*)*, void (%"class:e001.MyScene"*)*, void (%"class:e001.MyScene"*)* }
%"class:e001.MyScene" = type { %"classvtable:e001.MyScene"*, %"interface:graphics.Context.Context3D"*, i8*, %"class:e001.Resources"*, double, i32 }
%"class:e001.Resources" = type { %"classvtable:e001.Resources"*, %"interface:graphics.Context.VertexBuffer"*, i8*, %"interface:graphics.Context.IndexBuffer"*, i8* }

@"classimplements:e001.MyScene" = constant { %"interface:app.Scene.IScene", %"interface:app.Scene.ITouchListener" } { %"interface:app.Scene.IScene" { void (i8*, %"interface:graphics.Context.Context3D"*, i8*)* bitcast (void (%"class:e001.MyScene"*, %"interface:graphics.Context.Context3D"*, i8*)* @e001.CMyScene.MacquireContext to void (i8*, %"interface:graphics.Context.Context3D"*, i8*)*), %"interface:app.Scene.ITouchListener"* (i8**, i8*)* bitcast (%"interface:app.Scene.ITouchListener"* (i8**, %"class:e001.MyScene"*)* @e001.CMyScene.MrequestTouchListener to %"interface:app.Scene.ITouchListener"* (i8**, i8*)*), void (i8*)* bitcast (void (%"class:e001.MyScene"*)* @e001.CMyScene.Mupdate to void (i8*)*), void (i8*)* bitcast (void (%"class:e001.MyScene"*)* @e001.CMyScene.Mrender to void (i8*)*) }, %"interface:app.Scene.ITouchListener" { void (i8*, i32)* bitcast (void (%"class:e001.MyScene"*, i32)* @e001.CMyScene.MonTouchBoundToMouse to void (i8*, i32)*), void (i8*, i32, double, double)* bitcast (void (%"class:e001.MyScene"*, i32, double, double)* @e001.CMyScene.MonTouchBegin to void (i8*, i32, double, double)*), void (i8*, i32, double, double)* bitcast (void (%"class:e001.MyScene"*, i32, double, double)* @e001.CMyScene.MonTouchEnd to void (i8*, i32, double, double)*), void (i8*, i32, double, double, double, double)* bitcast (void (%"class:e001.MyScene"*, i32, double, double, double, double)* @e001.CMyScene.MonTouchMove to void (i8*, i32, double, double, double, double)*), void (i8*, i32)* bitcast (void (%"class:e001.MyScene"*, i32)* @e001.CMyScene.MonTouchCancel to void (i8*, i32)*), void (i8*, i32, double, double, double, double)* bitcast (void (%"class:e001.MyScene"*, i32, double, double, double, double)* @e001.CMyScene.MonTouchPassiveMove to void (i8*, i32, double, double, double, double)*) } }
@"e001.CResources.@vtable" = constant %"classvtable:e001.Resources" zeroinitializer
@"classimplements:e001.Resources" = constant {} zeroinitializer
@"e001.CMyScene.@vtable" = constant %"classvtable:e001.MyScene" { i8* null, i8* null, void (%"class:e001.MyScene"*, i32)* @e001.CMyScene.MonTouchBoundToMouse, void (%"class:e001.MyScene"*, i32, double, double)* @e001.CMyScene.MonTouchBegin, void (%"class:e001.MyScene"*, i32, double, double)* @e001.CMyScene.MonTouchEnd, void (%"class:e001.MyScene"*, i32, double, double, double, double)* @e001.CMyScene.MonTouchMove, void (%"class:e001.MyScene"*, i32)* @e001.CMyScene.MonTouchCancel, void (%"class:e001.MyScene"*, i32, double, double, double, double)* @e001.CMyScene.MonTouchPassiveMove, void (%"class:e001.MyScene"*, %"interface:graphics.Context.Context3D"*, i8*)* @e001.CMyScene.MacquireContext, %"interface:app.Scene.ITouchListener"* (i8**, %"class:e001.MyScene"*)* @e001.CMyScene.MrequestTouchListener, void (%"class:e001.MyScene"*)* @e001.CMyScene.Mupdate, void (%"class:e001.MyScene"*)* @e001.CMyScene.Mrender }

define fastcc void @e001.Frun() {
entry:
  br label %0

; <label>:0                                       ; preds = %entry
  %1 = call i8* @__jf_allocate_object(i32 ptrtoint (%"class:e001.MyScene"* getelementptr (%"class:e001.MyScene"* null, i32 1) to i32))
  %2 = bitcast i8* %1 to %"class:e001.MyScene"*
  call void @e001.CMyScene.KMyScene(i8* null, i8* null, %"class:e001.MyScene"* %2)
  %3 = bitcast %"class:e001.MyScene"* %2 to i8*
  call fastcc void @app.Scene.FStartApplicationScene(%"interface:app.Scene.IScene"* getelementptr inbounds ({ %"interface:app.Scene.IScene", %"interface:app.Scene.ITouchListener" }* @"classimplements:e001.MyScene", i32 0, i32 0), i8* %3)
  ret void
}

declare i8* @__jf_allocate_object(i32)

define fastcc void @e001.CMyScene.KMyScene(i8*, i8*, %"class:e001.MyScene"*) {
entry:
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = getelementptr inbounds %"class:e001.MyScene"* %2, i32 0, i32 1
  store %"interface:graphics.Context.Context3D"* null, %"interface:graphics.Context.Context3D"** %4
  %5 = getelementptr inbounds %"class:e001.MyScene"* %2, i32 0, i32 2
  store i8* undef, i8** %5
  %6 = getelementptr inbounds %"class:e001.MyScene"* %2, i32 0, i32 3
  store %"class:e001.Resources"* null, %"class:e001.Resources"** %6
  %7 = getelementptr inbounds %"class:e001.MyScene"* %2, i32 0, i32 4
  store double 0.000000e+00, double* %7
  %8 = getelementptr inbounds %"class:e001.MyScene"* %2, i32 0, i32 5
  store i32 1, i32* %8
  %9 = bitcast %"class:e001.MyScene"* %2 to %"classvtable:e001.MyScene"**
  store %"classvtable:e001.MyScene"* @"e001.CMyScene.@vtable", %"classvtable:e001.MyScene"** %9
  %10 = bitcast %"class:e001.MyScene"* %2 to i8*
  call void @__jf_unwind_constructor_stack(i8* %1, i8* %10)
  ret void
}

declare fastcc void @app.Scene.FStartApplicationScene(%"interface:app.Scene.IScene"*, i8*)

define fastcc void @e001.CResources.KResources(i8*, i8*, %"class:e001.Resources"*, %"interface:graphics.Context.Context3D"*, i8*) {
entry:
  %5 = alloca %"interface:graphics.Context.VertexBuffer"*
  %6 = alloca i8*
  %7 = alloca i32
  %8 = alloca i8*
  %9 = alloca %"interface:graphics.Context.IndexBuffer"*
  %10 = alloca i8*
  %11 = alloca i32
  %12 = alloca i8*
  %13 = alloca i8*
  %14 = alloca i8*
  br label %15

; <label>:15                                      ; preds = %entry
  %16 = getelementptr inbounds %"interface:graphics.Context.Context3D"* %3, i32 0, i32 4
  %17 = load %"interface:graphics.Context.VertexBuffer"* (i8**, i8*, i1, i32, i32)** %16
  %18 = call fastcc %"interface:graphics.Context.VertexBuffer"* %17(i8** %13, i8* %4, i1 true, i32 8, i32 4)
  %19 = load i8** %13
  store %"interface:graphics.Context.VertexBuffer"* %18, %"interface:graphics.Context.VertexBuffer"** %5
  store i8* %19, i8** %6
  %20 = call i8* @__jf_allocate_bytes(i32 32)
  store i32 32, i32* %7
  store i8* %20, i8** %8
  %21 = load i32* %7
  %22 = load i8** %8
  call void @__jf_write_float(i32 %21, i8* %22, i32 0, float -5.000000e-01)
  %23 = load i32* %7
  %24 = load i8** %8
  call void @__jf_write_float(i32 %23, i8* %24, i32 4, float -5.000000e-01)
  %25 = load i32* %7
  %26 = load i8** %8
  call void @__jf_write_float(i32 %25, i8* %26, i32 8, float -5.000000e-01)
  %27 = load i32* %7
  %28 = load i8** %8
  call void @__jf_write_float(i32 %27, i8* %28, i32 12, float 5.000000e-01)
  %29 = load i32* %7
  %30 = load i8** %8
  call void @__jf_write_float(i32 %29, i8* %30, i32 16, float 5.000000e-01)
  %31 = load i32* %7
  %32 = load i8** %8
  call void @__jf_write_float(i32 %31, i8* %32, i32 20, float 5.000000e-01)
  %33 = load i32* %7
  %34 = load i8** %8
  call void @__jf_write_float(i32 %33, i8* %34, i32 24, float 5.000000e-01)
  %35 = load i32* %7
  %36 = load i8** %8
  call void @__jf_write_float(i32 %35, i8* %36, i32 28, float -5.000000e-01)
  %37 = load %"interface:graphics.Context.VertexBuffer"** %5
  %38 = load i8** %6
  %39 = load i32* %7
  %40 = load i8** %8
  %41 = getelementptr inbounds %"interface:graphics.Context.VertexBuffer"* %37, i32 0, i32 0
  %42 = load void (i8*, i32, i32, i32, i8*)** %41
  call fastcc void %42(i8* %38, i32 0, i32 4, i32 %39, i8* %40)
  %43 = getelementptr inbounds %"interface:graphics.Context.Context3D"* %3, i32 0, i32 5
  %44 = load %"interface:graphics.Context.IndexBuffer"* (i8**, i8*, i1, i32)** %43
  %45 = call fastcc %"interface:graphics.Context.IndexBuffer"* %44(i8** %14, i8* %4, i1 true, i32 6)
  %46 = load i8** %14
  store %"interface:graphics.Context.IndexBuffer"* %45, %"interface:graphics.Context.IndexBuffer"** %9
  store i8* %46, i8** %10
  %47 = call i8* @__jf_allocate_bytes(i32 12)
  store i32 12, i32* %11
  store i8* %47, i8** %12
  %48 = load i32* %11
  %49 = load i8** %12
  call void @__jf_write_u16(i32 %48, i8* %49, i32 0, i32 0)
  %50 = load i32* %11
  %51 = load i8** %12
  call void @__jf_write_u16(i32 %50, i8* %51, i32 1, i32 1)
  %52 = load i32* %11
  %53 = load i8** %12
  call void @__jf_write_u16(i32 %52, i8* %53, i32 2, i32 2)
  %54 = load i32* %11
  %55 = load i8** %12
  call void @__jf_write_u16(i32 %54, i8* %55, i32 3, i32 2)
  %56 = load i32* %11
  %57 = load i8** %12
  call void @__jf_write_u16(i32 %56, i8* %57, i32 4, i32 1)
  %58 = load i32* %11
  %59 = load i8** %12
  call void @__jf_write_u16(i32 %58, i8* %59, i32 5, i32 3)
  %60 = load %"interface:graphics.Context.IndexBuffer"** %9
  %61 = load i8** %10
  %62 = load i32* %11
  %63 = load i8** %12
  %64 = getelementptr inbounds %"interface:graphics.Context.IndexBuffer"* %60, i32 0, i32 0
  %65 = load void (i8*, i32, i32, i32, i8*)** %64
  call fastcc void %65(i8* %61, i32 0, i32 6, i32 %62, i8* %63)
  %66 = load %"interface:graphics.Context.VertexBuffer"** %5
  %67 = load i8** %6
  %68 = getelementptr inbounds %"class:e001.Resources"* %2, i32 0, i32 1
  store %"interface:graphics.Context.VertexBuffer"* %66, %"interface:graphics.Context.VertexBuffer"** %68
  %69 = getelementptr inbounds %"class:e001.Resources"* %2, i32 0, i32 2
  store i8* %67, i8** %69
  %70 = load %"interface:graphics.Context.IndexBuffer"** %9
  %71 = load i8** %10
  %72 = getelementptr inbounds %"class:e001.Resources"* %2, i32 0, i32 3
  store %"interface:graphics.Context.IndexBuffer"* %70, %"interface:graphics.Context.IndexBuffer"** %72
  %73 = getelementptr inbounds %"class:e001.Resources"* %2, i32 0, i32 4
  store i8* %71, i8** %73
  %74 = bitcast %"class:e001.Resources"* %2 to %"classvtable:e001.Resources"**
  store %"classvtable:e001.Resources"* @"e001.CResources.@vtable", %"classvtable:e001.Resources"** %74
  %75 = bitcast %"class:e001.Resources"* %2 to i8*
  call void @__jf_unwind_constructor_stack(i8* %1, i8* %75)
  ret void
}

declare i8* @__jf_allocate_bytes(i32)

declare void @__jf_write_float(i32, i8*, i32, float)

declare void @__jf_write_u16(i32, i8*, i32, i32)

declare void @__jf_unwind_constructor_stack(i8*, i8*)

define fastcc void @e001.CMyScene.MonTouchBoundToMouse(%"class:e001.MyScene"*, i32) {
entry:
  br label %2

; <label>:2                                       ; preds = %entry
  ret void
}

define fastcc void @e001.CMyScene.MonTouchBegin(%"class:e001.MyScene"*, i32, double, double) {
entry:
  br label %4

; <label>:4                                       ; preds = %entry
  ret void
}

define fastcc void @e001.CMyScene.MonTouchEnd(%"class:e001.MyScene"*, i32, double, double) {
entry:
  br label %4

; <label>:4                                       ; preds = %entry
  ret void
}

define fastcc void @e001.CMyScene.MonTouchMove(%"class:e001.MyScene"*, i32, double, double, double, double) {
entry:
  br label %6

; <label>:6                                       ; preds = %entry
  ret void
}

define fastcc void @e001.CMyScene.MonTouchCancel(%"class:e001.MyScene"*, i32) {
entry:
  br label %2

; <label>:2                                       ; preds = %entry
  ret void
}

define fastcc void @e001.CMyScene.MonTouchPassiveMove(%"class:e001.MyScene"*, i32, double, double, double, double) {
entry:
  br label %6

; <label>:6                                       ; preds = %entry
  ret void
}

define fastcc void @e001.CMyScene.MacquireContext(%"class:e001.MyScene"*, %"interface:graphics.Context.Context3D"*, i8*) {
entry:
  br label %3

; <label>:3                                       ; preds = %entry
  %4 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 1
  store %"interface:graphics.Context.Context3D"* %1, %"interface:graphics.Context.Context3D"** %4
  %5 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 2
  store i8* %2, i8** %5
  %6 = call i8* @__jf_allocate_object(i32 mul nuw (i32 ptrtoint (i1** getelementptr (i1** null, i32 1) to i32), i32 5))
  %7 = bitcast i8* %6 to %"class:e001.Resources"*
  call void @e001.CResources.KResources(i8* null, i8* null, %"class:e001.Resources"* %7, %"interface:graphics.Context.Context3D"* %1, i8* %2)
  %8 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 3
  store %"class:e001.Resources"* %7, %"class:e001.Resources"** %8
  ret void
}

define fastcc %"interface:app.Scene.ITouchListener"* @e001.CMyScene.MrequestTouchListener(i8**, %"class:e001.MyScene"*) {
entry:
  br label %2

; <label>:2                                       ; preds = %entry
  %3 = bitcast %"class:e001.MyScene"* %1 to i8*
  store i8* %3, i8** %0
  ret %"interface:app.Scene.ITouchListener"* bitcast (void (i8*, i32)** getelementptr inbounds ({ %"interface:app.Scene.IScene", %"interface:app.Scene.ITouchListener" }* @"classimplements:e001.MyScene", i32 0, i32 1, i32 0) to %"interface:app.Scene.ITouchListener"*)
}

define fastcc void @e001.CMyScene.Mupdate(%"class:e001.MyScene"*) {
entry:
  br label %1

; <label>:1                                       ; preds = %entry
  %2 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 4
  %3 = load double* %2
  %4 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 5
  %5 = load i32* %4
  %6 = sitofp i32 %5 to double
  %7 = fmul double 1.000000e-02, %6
  %8 = fadd double %3, %7
  %9 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 4
  store double %8, double* %9
  %10 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 4
  %11 = load double* %10
  %12 = fcmp ogt double %11, 1.000000e+00
  br i1 %12, label %17, label %13

; <label>:13                                      ; preds = %17, %1
  %14 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 4
  %15 = load double* %14
  %16 = fcmp olt double %15, 0.000000e+00
  br i1 %16, label %27, label %26

; <label>:17                                      ; preds = %1
  %18 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 5
  %19 = load i32* %18
  %20 = icmp sgt i32 %19, 0
  br i1 %20, label %21, label %13

; <label>:21                                      ; preds = %17
  %22 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 5
  %23 = load i32* %22
  %24 = sub i32 0, %23
  %25 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 5
  store i32 %24, i32* %25
  br label %31

; <label>:26                                      ; preds = %27, %13
  br label %37

; <label>:27                                      ; preds = %13
  %28 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 5
  %29 = load i32* %28
  %30 = icmp slt i32 %29, 0
  br i1 %30, label %32, label %26

; <label>:31                                      ; preds = %37, %21
  ret void

; <label>:32                                      ; preds = %27
  %33 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 5
  %34 = load i32* %33
  %35 = sub i32 0, %34
  %36 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 5
  store i32 %35, i32* %36
  br label %37

; <label>:37                                      ; preds = %32, %26
  br label %31
}

define fastcc void @e001.CMyScene.Mrender(%"class:e001.MyScene"*) {
entry:
  br label %1

; <label>:1                                       ; preds = %entry
  %2 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 1
  %3 = load %"interface:graphics.Context.Context3D"** %2
  %4 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 2
  %5 = load i8** %4
  %6 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 3
  %7 = load %"class:e001.Resources"** %6
  %8 = icmp ne %"interface:graphics.Context.Context3D"* %3, null
  br i1 %8, label %10, label %9

; <label>:9                                       ; preds = %1
  br label %12

; <label>:10                                      ; preds = %1
  %11 = icmp ne %"class:e001.Resources"* %7, null
  br i1 %11, label %14, label %13

; <label>:12                                      ; preds = %14, %13, %9
  ret void

; <label>:13                                      ; preds = %10
  br label %12

; <label>:14                                      ; preds = %10
  %15 = getelementptr inbounds %"class:e001.MyScene"* %0, i32 0, i32 4
  %16 = load double* %15
  %17 = getelementptr inbounds %"interface:graphics.Context.Context3D"* %3, i32 0, i32 0
  %18 = load void (i8*, double, double, double, double)** %17
  call fastcc void %18(i8* %5, double 0.000000e+00, double 2.500000e-01, double %16, double 0.000000e+00)
  %19 = getelementptr inbounds %"interface:graphics.Context.Context3D"* %3, i32 0, i32 3
  %20 = load void (i8*, i1, i1, i1)** %19
  call fastcc void %20(i8* %5, i1 true, i1 true, i1 true)
  br label %12
}

define void @__jf_main() {
entry:
  call fastcc void @e001.Frun()
  ret void
}
