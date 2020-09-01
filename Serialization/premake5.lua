project "Serialization"
    kind "StaticLib"
    language "C++"
    
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objectdir("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "{prj.name}/src/.**h",
        "{prj.name}/src/**cpp"
    }
    
    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"
        
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"