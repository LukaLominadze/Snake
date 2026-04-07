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
	include "NigoziEngine/vendor/nfd/build/Build-nfd-Only.lua"
	include "NigoziEngine/vendor/glfw"
	include "NigoziEngine/vendor/glew"
	include "NigoziEngine/vendor/stb"
	include "NigoziEngine/vendor/imgui"
	include "vendor/yaml"
	include "NigoziEngine/NigoziEngine"
group ""

group "Main"
	include "Snake"
group ""
