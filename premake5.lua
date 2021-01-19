workspace "Tutorials"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Arrays"] = "Arrays/include"
IncludeDir["Reflection"] = "Reflection/include"
IncludeDir["Serialization"] = "Serialization/include"
IncludeDir["HeaderTool"] = "HeaderTool/include"
IncludeDir["CreateWindow"] = "CreateWindow/include"
IncludeDir["JSON"] = "JsonReaderWriter/include"
IncludeDir["WaveParser"] = "WaveParser/include"

group "Dependencies"
    include "Arrays"
    include "Reflection"
    include "Serialization"
    include "HeaderTool"
    include "CreateWindow"
    include "JsonReaderWriter"
    include "WaveParser"
group  ""

project "Tutorials"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
        "%{prj.name}/Reflection/include/**h",
        "%{prj.name}/Arrays/include/**h"
    }

    includedirs
    {
        "%{IncludeDir.Reflection}",
        "%{IncludeDir.Serialization}",
        "%{IncludeDir.Arrays}",
        "%{IncludeDir.HeaderTool}",
        "%{IncludeDir.CreateWindow}",
        "%{IncludeDir.JSON}",
        "%{IncludeDir.WaveParser}"
    }
    
    links
    {
        "Serialization",
        "CreateWindow",
        "JsonReaderWriter",
        "WaveParser",
        "winmm"
    }
    
    filter"system:windows"
        systemversion "latest"

        filter "configurations:Debug"
            defines "DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "RELEASE"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "DIST"
            runtime "Release"
            optimize "on"

