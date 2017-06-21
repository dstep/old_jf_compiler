#pragma once

#if defined(_MSC_VER)
#	define JF_COMPILER_MSVC
#elif defined(__GNUC__)
#	define JF_COMPILER_GCC
#else
#	define JF_COMPILER_UNKNOWN
#endif

#if defined(_DEBUG)
#	define JF_DEBUG
#else
#	define JF_RELEASE
#endif

#if _WIN32 || _WIN64
#	define JF_PLATFORM_WIN
#else
#	define JF_PLATFORM_UNKNOWN
#endif

#if (!defined(JF_POINTER_32BIT)) && (!defined(JF_POINTER_64BIT))

#	if _WIN32 || _WIN64
#		if _WIN64
#			define JF_POINTER_64BIT
#		else
#			define JF_POINTER_32BIT
#		endif
#	endif

#	if __GNUC__
#		if __x86_64__ || __ppc64__
#			define JF_POINTER_64BIT
#		else
#			define JF_POINTER_32BIT
#		endif
#	endif

#endif

#if (!defined(JF_POINTER_32BIT)) && (!defined(JF_POINTER_64BIT))
#	error Either JF_POINTER_32BIT or JF_POINTER_64BIT should be set
#endif

#undef JF_TRACK_ALLOCATIONS

namespace jf{
}