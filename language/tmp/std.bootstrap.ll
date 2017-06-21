; ModuleID = 'std.bootstrap'

define fastcc void @std.bootstrap.Fprint([16 x i8]*) {
  call void @_print([16 x i8]* %0)
  ret void
}

declare void @_print([16 x i8]*)

define fastcc double @std.bootstrap.Frandom() {
  %1 = call double @_random()
  ret double %1
}

declare double @_random()
