#pragma once

#include <assert.h>
#include <memory>

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#ifdef SF_DEBUG

#define SF_ASSERT(x, ...) { if(!(x)) { assert(__VA_ARGS__); } }

#else

#define SF_ASSERT(x, ...)

#endif // SF_DEBUG

namespace SF {

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}




