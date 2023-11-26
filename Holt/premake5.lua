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
        "src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
    {
		"src",
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/Glad/include",
		"vendor/imgui",
		"vendor/glm",
		"vendor/stb_image"
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