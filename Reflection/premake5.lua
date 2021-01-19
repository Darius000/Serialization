project "Reflection"
    kind "StaticLib"
    language "C++"

    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    
    files
    {
        "**.h"
    }
    
    includedirs
    {
        "%{prj.name}/src"
    }
    
   filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
