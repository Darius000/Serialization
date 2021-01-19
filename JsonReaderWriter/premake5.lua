project "JsonReaderWriter"
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
        "%{prj.name}/src"
    }
    
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
