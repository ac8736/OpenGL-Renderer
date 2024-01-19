#pragma once

#ifdef ENABLE_ASSERTS
	#define CLIENT_ASSERT(x, ...) { if (!(x)) { PN_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CORE_ASSERT(x, ...) { if (!(x)) { PN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CLIENT_ASSERT(x, ...)
	#define CORE_ASSERT(x, ...)
#endif