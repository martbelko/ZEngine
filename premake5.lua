workspace "ZEngine"
	platforms { "Win32", "x64" }

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg} - %{cfg.platform}"
	
	project "ZEngine"
		kind "StaticLib"
		language "C++"
		location "ZEngine"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "zpch.hpp"
		pchsource "ZEngine/src/zpch.cpp"

		files
		{
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/src",
		}

		filter "configurations:Debug"
			defines "ZE_DEBUG"
			runtime "Debug"
			symbols "on"
			optimize "off"

		filter "configurations:Release"
			defines "ZE_RELEASE"
			runtime "Release"
			optimize "on"
			symbols "off"

		filter "configurations:Dist"
			defines "ZE_DIST"
			runtime "Release"
			optimize "Speed"

		filter "platforms:*32"
			defines "ZE_32"

		filter "platforms:*64"
			defines "ZE_64"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"ZEngine/src",
			"Sandbox/src",
		}

		links
		{
			"ZEngine"
		}

		filter "system:windows"
			systemversion "latest"
		
		filter "configurations:Debug"
			defines "ZE_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "ZE_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "ZE_DIST"
			runtime "Release"
			optimize "speed"

		filter "platforms:*32"
			defines "ZE_32"

		filter "platforms:*64"
			defines "ZE_64"