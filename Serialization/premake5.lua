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
        "%{prj.name}/include",
    }
    
    --configuration "windows"
   -- postbuildcommands{"{COPY} $(TargetPath) $(SolutionDir)\\scripts"}

   filter { "system:windows", "configurations:Debug" }
        buildoptions "/MTd"
    
   filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
