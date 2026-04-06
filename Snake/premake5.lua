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
				  "%{wks.location}/NigoziEngine/vendor/glew/include",
				  "%{wks.location}/NigoziEngine/vendor/glfw/include",
				  "%{wks.location}/NigoziEngine/vendor/stb",
				  "%{wks.location}/NigoziEngine/vendor/imgui",
				  "%{wks.location}/NigoziEngine/vendor/glm",
				  "%{wks.location}/vendor/yaml/include",
				  "%{wks.location}/vendor/nfd/src/include",
				  "%{wks.location}/NigoziEngine/vendor/spdlog/include" }

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
		"{COPYDIR} %{wks.location}/NigoziEngine/NigoziEngine/src/Nigozi/res %{prj.location}/src/Nigozi/",
		"{MKDIR} %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/src",
		"{COPYDIR} %{prj.location}/src/Nigozi %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/",
		"{COPYDIR} %{prj.location}/logo-small.png %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/",
		"{COPYDIR} %{prj.location}/logo.png %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/",
		"{MKDIR} %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/src/assets",
		"{COPYDIR} %{prj.location}/src/assets/sprites %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/assets/",
		"{COPYDIR} %{prj.location}/src/assets/levels %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/assets/",
		"{COPYDIR} %{prj.location}/src/assets/editor %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/assets/",
		"{COPYDIR} %{prj.location}/src/assets/audio %{wks.location}/bin/" ..outputdir.. "/%{prj.name}/src/assets/"
	}

	filter "toolset:msc*"
  		buildoptions { "/utf-8" }

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
	
	filter {"system:linux", "options:linux_backend=gtk3"}

		buildoptions {"`pkg-config --cflags gtk+-3.0`"}
		linkoptions  { "`pkg-config --libs gtk+-3.0`" }
		links { "gtk-3", "gobject-2.0", "glib-2.0" }

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
