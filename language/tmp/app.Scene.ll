; ModuleID = 'app.Scene'

%"interface:app.Scene.IScene" = type opaque

define fastcc void @app.Scene.FStartApplicationScene(%"interface:app.Scene.IScene"*, i8*) {
  call void @_StartApplicationScene(%"interface:app.Scene.IScene"* %0, i8* %1)
  ret void
}

declare void @_StartApplicationScene(%"interface:app.Scene.IScene"*, i8*)
