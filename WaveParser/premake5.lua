project "WaveParser"
    kind "StaticLib"
    language "C++"
    
    targetdir ("lib/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    
    files
    {
        "**.h",
        "**.cpp"
    }
    
    includedirs
    {
        "%{prj.name}/include",
    }
    
    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MTd"
    
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
