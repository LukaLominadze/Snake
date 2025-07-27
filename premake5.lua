workspace "Snake"
	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	architecture "x64"

	startproject "Snake"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "NigoziEngine/dependencies/glfw"
	include "NigoziEngine/dependencies/glew"
	include "NigoziEngine/dependencies/stb"
	include "NigoziEngine/dependencies/imgui"
	include "NigoziEngine/NigoziEngine"

group "Main"
	include "Snake"
group ""
