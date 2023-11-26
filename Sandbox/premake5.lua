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
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"../Holt/src",
		"../Holt/vendor/spdlog/include",
		"../Holt/vendor",
		"../Holt/vendor/glm"
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