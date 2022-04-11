project "wavlib"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir(bindir)
	objdir(intdir)

	files
	{
		"%{prj.location}/include/wavlib/*.h",
		"%{prj.location}/source/*.cpp",
	}

	defines
	{
		"WAVLIB_DLL",
		"WAVLIB_EXPORTS"
	}

	includedirs
	{
		"%{prj.location}/include",
		"%{prj.location}/include/wavlib",
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"