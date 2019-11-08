#pragma once

#ifdef ZE_DEBUG
	#define ZE_ENABLE_ENGINE_ASSERTS
#endif

#ifdef ZE_ENABLE_ENGINE_ASSERTS
	#define ZE_CORE_ASSERT(x, ...) { if(!(x)) { ZE_CORE_ERROR("Assertion Failed: %", __VA_ARGS__); __debugbreak(); } }
#else
	#define ZE_CORE_ASSERT(x, ...)
#endif

#ifdef ZE_ENABLE_ASSERTS
	#define ZE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ZE_ASSERT(x, ...)
#endif
