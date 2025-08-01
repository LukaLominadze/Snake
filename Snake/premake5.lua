project "Snake"
	kind "ConsoleApp"
	staticruntime "off"

	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

	defines { "GLEW_STATIC", "YAML_CPP_STATIC_DEFINE" }
	
	files {
		"src/**.h",
		"src/**.cpp"
	}

	vpaths {
		["Source Files"] = "src/**.cpp",
		["Header Files"] = "src/**.h"
	}

	includedirs {  "src",
				  "%{wks.location}/NigoziEngine/NigoziEngine/src",
				  "%{wks.location}/NigoziEngine/NigoziEngine/src/Nigozi",
				  "%{wks.location}/NigoziEngine/dependencies/glew/include",
				  "%{wks.location}/NigoziEngine/dependencies/glfw/include",
				  "%{wks.location}/NigoziEngine/dependencies/stb",
				  "%{wks.location}/NigoziEngine/dependencies/imgui",
				  "%{wks.location}/NigoziEngine/dependencies/glm",
				  "%{wks.location}/vendor/yaml/include",
				  "%{wks.location}/vendor/nfd/src/include" }

	libdirs { "%{wks.location}/NigoziEngine/dependencies/libs/GLFW",
			  "%{wks.location}/NigoziEngine/dependencies/glew/lib/Release/x64",
			  "%{wks.location}/NigoziEngine/dependencies/libs/STB",
			  "%{wks.location}/NigoziEngine/dependencies/libs/ImGui",
			  "%{wks.location}/NigoziEngine/dependencies/glew/lib" }

	links {
		"nfd",
		"NigoziEngine",
		"GLEW",
		"GLFW",
		"STB",
		"ImGui",
		"yaml-cpp",
		 }

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

	postbuildcommands {
		"{COPYDIR} %{wks.location}/NigoziEngine/NigoziEngine/src/Nigozi/res %{prj.location}/src/Nigozi/res",
		"{MKDIR} %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/src/Nigozi",
		"{COPYDIR} %{prj.location}/src/Nigozi %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/Nigozi",
		"{COPYDIR} %{prj.location}/logo-small.png %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/",
		"{COPYDIR} %{prj.location}/logo.png %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/",
		"{MKDIR} %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/src/assets/sprites",
		"{COPYDIR} %{prj.location}/src/assets/sprites %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/assets/sprites",
		"{COPYDIR} %{prj.location}/src/assets/levels %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/assets/levels"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"
		
		defines { "NG_PLATFORM_WINDOWS" }
		
		links { "opengl32.lib" }
	
	filter "system:linux"
		cppdialect "C++20"
		systemversion "latest"
		
		defines { "GLFW_USE_X11", "_GLFW_X11", "NG_PLATFORM_LINUX" }
		
		links { "GL",
			"pthread",
        		"dl" }

	filter "configurations:Debug"
		
		defines { "_DEBUG", "_CONSOLE" }
		
		architecture "x64"
		symbols "on"

	filter "configurations:Release"
		
		defines { "NDEBUG", "_CONSOLE" }

		architecture "x64"
		optimize "on"

	filter "configurations:Distribution"
		
		kind "WindowedApp"

		defines { "DISTRIBUTION" }
	
		architecture "x64"
		optimize "on"
