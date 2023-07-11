project "sound_generator"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"
    flags "MultiProcessorCompile"

    targetdir(bin)
	objdir(int)

    files
    {
        "source/**.h",
        "source/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/include"
    }

    links "wavlib"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
        optimize "off"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
        symbols "off"