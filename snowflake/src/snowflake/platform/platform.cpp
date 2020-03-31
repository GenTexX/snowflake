#include "sfpch.h"
#include "platform.h"
#ifdef SF_PLATFORM_WINDOWS
#include "windows/platformWindows.h"
#endif
namespace SF {

	std::unique_ptr<Platform> Platform::s_Instance = Platform::create();

	Platform::~Platform() {

	}

	std::unique_ptr<Platform> Platform::create() {
		
#ifdef SF_PLATFORM_WINDOWS
		return std::make_unique<PlatformWindows>();
#endif
	}

}
