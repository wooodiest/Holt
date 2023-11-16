workspace "Holt"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Holt/vendor/GLFW"
	include "Holt/vendor/Glad"
	include "Holt/vendor/imgui"
group ""

project "Holt"
	location "Holt"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hlpch.h"
	pchsource "Holt/src/hlpch.cpp"

	files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
    {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/glm"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
        systemversion "latest"

		defines
        {
            "HL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
        }

		filter "configurations:Debug"
		defines "HL_DEBUG"
		runtime "Debug"
		symbols "on"

		filter "configurations:Release"
		defines "HL_RELEASE"
		runtime "Release"
		optimize "on"

		filter "configurations:Dist"
		defines "HL_DIST"
		runtime "Release"
		optimize "on"


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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Holt/src",
		"Holt/vendor/spdlog/include",
		"Holt/vendor",
		"Holt/vendor/glm"
	}

	links
	{
		"Holt"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HL_DIST"
		runtime "Release"
		optimize "on"