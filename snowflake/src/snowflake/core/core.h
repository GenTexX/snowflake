#pragma once

#include <assert.h>

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#ifdef SF_DEBUG

#define SF_ASSERT(x, ...) { if(!(x)) { assert(__VA_ARGS__); } }

#else

#define SF_ASSERT(x, ...)

#endif // SF_DEBUG





