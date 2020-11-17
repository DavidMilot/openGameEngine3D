workspace "openGameEngine3D"
	architecture "x86_64"
	startproject "openGameEngine3DEditor"

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

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "openGameEngine3D/vendor/GLFW/include"
IncludeDir["Glad"] = "openGameEngine3D/vendor/Glad/include"
IncludeDir["ImGui"] = "openGameEngine3D/vendor/imgui"
IncludeDir["glm"] = "openGameEngine3D/vendor/glm"
IncludeDir["stb_image"] = "openGameEngine3D/vendor/stb_image"
IncludeDir["entt"] = "openGameEngine3D/vendor/entt/include"

include "openGameEngine3D/vendor/GLFW"
include "openGameEngine3D/vendor/Glad"
include "openGameEngine3D/vendor/imgui"
include "openGameEngine3D/vendor/glm"

project "openGameEngine3D"
	location "openGameEngine3D"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	pchheader "ogepch.h"
	pchsource "%{prj.name}/src/openGameEngine3D/ogepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs 
	{
		"%{prj.name}/openGameEngine3D/vendor/spdlog/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{prj.name}/src/openGameEngine3D",
		"%{prj.name}/openGameEngine3D/src/openGameEngine3D",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		}

		filter "configurations:Debug"
			defines "OGE_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "OGE_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "OGE_DIST"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"openGameEngine3D/openGameEngine3D/vendor/spdlog/include",
		"%{prj.name}/openGameEngine3D/vendor/spdlog/include",
		"openGameEngine3D/src",
		"openGameEngine3D/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"openGameEngine3D"
	}

	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

		filter "configurations:Debug"
			defines "OGE_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "OGE_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "OGE_DIST"
			runtime "Release"
			optimize "on"

project "openGameEngine3DEditor"
	location "openGameEngine3DEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"openGameEngine3D/vendor/spdlog/include",
		"openGameEngine3D/src",
		"openGameEngine3D/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"openGameEngine3D"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "OGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OGE_DIST"
		runtime "Release"
		optimize "on"
