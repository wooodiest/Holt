include "Dependencies.lua"

workspace "Holt"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Holt/vendor/GLFW"
	include "Holt/vendor/Glad"
	include "Holt/vendor/imgui"
group ""

include "Holt"
include "Sandbox"



