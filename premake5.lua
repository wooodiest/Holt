include "Dependencies.lua"

workspace "Holt"
	architecture "x64"
	startproject "Holt-Editor"

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
	include "Holt/vendor/yaml-cpp"
group ""

include "Holt"
include "Sandbox"
include "Holt-Editor"



