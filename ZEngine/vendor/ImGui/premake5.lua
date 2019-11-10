project "ImGui"
	kind "StaticLib"
	language "C++"
    cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"imgui.cpp",
        "imgui.h",
        "imgui_demo.cpp",
        "imgui_draw.cpp",
        "imgui_widgets.cpp",
        "imgui_internal.h",
        "imconfig.h",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h"
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
