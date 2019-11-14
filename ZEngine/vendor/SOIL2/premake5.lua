project "SOIL2"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"srcs/**.c",
		"incs/SOIL2/**.h"
	}

	includedirs
	{
		"incs/SOIL2"
	}

	systemversion "latest"
	staticruntime "on"

	filter "system:windows"
		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
		}

	runtime "Release"
	optimize "speed"
	symbols "off"
