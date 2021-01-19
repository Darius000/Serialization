project "Serialization"
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
    
    --configuration "windows"
   -- postbuildcommands{"{COPY} $(TargetPath) $(SolutionDir)\\scripts"}
    
   filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
