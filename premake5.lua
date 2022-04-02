project "wavlib"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir(bindir)
    objdir(intdir)

    files
    {
        "%{prj.location}/include/*.h",
        "%{prj.location}/source/*.cpp",
    }

    includedirs
    {
        "%{prj.location}/include"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"