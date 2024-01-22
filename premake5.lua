workspace "OpenGL-Renderer"
	architecture "x86_64"
	startproject "Sandbox"
	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "OpenGL-Renderer/vendor/spdlog/include"
IncludeDir["GLFW"] = "OpenGL-Renderer/vendor/GLFW/include"
IncludeDir["Glad"] = "OpenGL-Renderer/vendor/Glad/include"
IncludeDir["ImGui"] = "OpenGL-Renderer/vendor/imgui"
IncludeDir["glm"] = "OpenGL-Renderer/vendor/glm"
IncludeDir["stb_image"] = "OpenGL-Renderer/vendor/stb_image"

group "Dependencies"
	include "OpenGL-Renderer/vendor/GLFW"
	include "OpenGL-Renderer/vendor/Glad"
	include "OpenGL-Renderer/vendor/imgui"
group ""

project "OpenGL-Renderer"
	kind "StaticLib"
	language "C++"
	location "OpenGL-Renderer"
	staticruntime "on"
	cppdialect "Default"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "glpch.h"
	pchsource "%{prj.name}/src/glpch.cpp"
	
	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.ini",
		"%{prj.name}/vendor/stb_image/stb_image.cpp",
		"%{prj.name}/vendor/stb_image/stb_image.h"
	}

	includedirs { 
		"%{IncludeDir.spdlog}",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"Glad",
		"ImGui",
		"GLFW",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
			"PN_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS",
			"ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PN_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	location "Sandbox"
	cppdialect "Default"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"OpenGL-Renderer/src"
	}

	links {
		"OpenGL-Renderer",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PN_DIST"
		runtime "Release"
		optimize "on"