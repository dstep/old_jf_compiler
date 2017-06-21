#pragma once
#include "BuildSettings.h"

#include <cassert>
#include <cstdlib>

#if defined(JF_COMPILER_MSVC)

#	if defined(JF_DEBUG)
#		define unreachable do{ assert(false); __assume(0); }while(true)
#	else
#		define unreachable __assume(0)
#	endif

#	define force_inline __forceinline

#elif defined(JF_COMPILER_GCC)

#	if defined(JF_DEBUG)
#		define unreachable do{ assert(false); __builtin_unreachable(); }while(true)
#	else
#		define unreachable __builtin_unreachable()
#	endif

#else

#	define unreachable do{ assert(false); }while(true)

#	define force_inline inline

#endif

#if defined(JF_POINTER_32BIT)
#	define JF_POINTER_BITS 32
#elif defined(JF_POINTER_64BIT)
#	define JF_POINTER_BITS 64
#else
#	undef JF_POINTER_BITS
#endif

#define iterate_enumerable(name, enumerable) for ( auto name = enumerable.enumerate(); name.hasNext(); name.advance() )