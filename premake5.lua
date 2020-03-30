workspace "snowflake"
	architecture "x64"
	startproject "sandbox"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"
	
includeDir = {}
libDir = {}

--SPDLOG
includeDir["SPDLOG"] = "vendor/spdlog/include"

--GLEW
includeDir["GLEW"] = "vendor/GLEW/include"
libDir["GLEW"] = "vendor/GLEW/lib"

--SDL
includeDir["SDL"] = "vendor/SDL/include"
libDir["SDL"] = "vendor/SDL/lib"

--GLM
includeDir["GLM"] = "vendor/glm/include"

--IMGUI
includeDir["IMGUI"] = "vendor/imgui"

--STB
includeDir["STB"] = "vendor/stb"

include "vendor/imgui"
include "vendor/stb"

project "snowflake"
	location "snowflake"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	pchheader "sfpch.h"
	pchsource "snowflake/src/sfpch.cpp"
	
	--ignoredefaultlibraries { "libcmt.lib" }
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
J	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{includeDir.SPDLOG}",
		"%{includeDir.GLEW}",
		"%{includeDir.SDL}",
		"%{includeDir.GLM}",
		"%{includeDir.IMGUI}",
		"%{includeDir.STB}"
	}
	
	links
	{	
		"imgui",
		"stb"
	}

	defines {
		"GLEW_STATIC"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines{
			"SF_PLATFORM_WINDOWS",
			"NOMINMAX",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
			defines "SF_DEBUG"
			runtime "Debug"
			symbols "on"

	filter "configurations:Release"
			defines "SF_RELEASE"
			runtime "Release"
			optimize "on"
			
project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	postbuildcommands {
		"copy ..\\vendor\\SDL\\lib\\SDL2.dll ..\\bin\\%{cfg.buildcfg}-%{cfg.architecture}\\sandbox"
	}
	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		includeDir["SPDLOG"],
		includeDir["SDL"],
		includeDir["GLEW"],
		includeDir["GLM"],
		includeDir["IMGUI"],
		includeDir["STB"],
		"snowflake/src"
	}

	libdirs
	{
		"%{libDir.GLEW}",
		"%{libDir.SDL}"
	}

	links{
		"snowflake",
		"SDL2.lib",
		"SDL2main.lib",
		"glu32.lib",
		"glew32s.lib",
		"opengl32.lib"
	}
	
	defines {
		"GLEW_STATIC"
	}

	linkoptions { "/ignore:4099" }

	flags { 
		"FatalCompileWarnings",
		"FatalLinkWarnings"
	}

	filter "system:windows"
		systemversion "latest"
		defines "SF_PLATFORM_WINDOWS"
		
	filter "configurations:Debug"
		defines "SF_DEBUG"
		runtime "Debug"
		symbols "on"
		linkoptions { '/NODEFAULTLIB:"LIBCMT"' }

	filter "configurations:Release"
		defines "SF_RELEASE"
		runtime "Release"
		optimize "on"




