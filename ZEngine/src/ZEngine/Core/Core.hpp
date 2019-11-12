#pragma once

#ifndef ZE_PLATFORM_WINDOWS
	#error Windows only support at the moment
#endif

#ifdef ZE_DEBUG
	#define ZE_ENABLE_CORE_ASSERTS
#endif

#ifdef ZE_ENABLE_CORE_ASSERTS
	#define ZE_CORE_ASSERT(x, ...) { if(!(x)) { ZE_CORE_ERROR("Assertion Failed: %", __VA_ARGS__); __debugbreak(); } }
#else
	#define ZE_CORE_ASSERT(x, ...)
#endif

#ifdef ZE_ENABLE_ASSERTS
	#define ZE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ZE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
