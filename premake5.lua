workspace "PPCToolchain"
architecture "x64"
startproject "PPC"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

FMT_INCLUDE = "Venders/FMT/include"

--stores the general definition of PPC Data Structures
--this way it can used in many tools
PPCLib_Include = "PPCLib/includes"
PPCLib_Link = "PPCLib"
project "PPCLib"
location "PPCLib"
kind "StaticLib"
language "C++"
targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")
objdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")


files 
{
---base code
"PPCLib/includes/**.h",
"PPCLib/src/**.c",
"PPCLib/includes/**.hpp",
"PPCLib/src/**.cpp",

}

includedirs 
{
---base code
"PPCLib/includes",
FMT_INCLUDE
}

links
{

}

flags
{
"MultiProcessorCompile",
"NoRuntimeChecks",
}


buildoptions
{
"/utf-8",
}


--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Window_Build"
}

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Linux_Build"
}


    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"MacOS_Build"
}

--configs
filter "configurations:Debug"
    defines "PPC_DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "PPC_RELEASE"
    optimize "On"

filter "configurations:Dist"
    defines "PPC_DIST"
    optimize "On"


defines
{
"NDEBUG",
}


flags
{
"LinkTimeOptimization",
}

--splits a ROM, generates asm, and scans
project "PPCAnalyse"
location "PPCAnalyse"
kind "ConsoleApp"
language "C++"
targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")
objdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")


files 
{
---base code
"PPCAnalyse/includes/**.h",
"PPCAnalyse/src/**.c",
"PPCAnalyse/includes/**.hpp",
"PPCAnalyse/src/**.cpp",

}

includedirs 
{
---base code
"PPCAnalyse/includes",
PPCLib_Include,
FMT_INCLUDE
}

links
{
    PPCLib_Link
}

flags
{
"MultiProcessorCompile",
"NoRuntimeChecks",
}


buildoptions
{
"/utf-8",
}


--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Window_Build"
}

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Linux_Build"
}


    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"MacOS_Build"
}

--configs
filter "configurations:Debug"
    defines "PPC_DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "PPC_RELEASE"
    optimize "On"

filter "configurations:Dist"
    defines "PPC_DIST"
    optimize "On"


defines
{
"NDEBUG",
}


flags
{
"LinkTimeOptimization",
}

--takes ASM and symbols and outputs C++
project "PPCRecomp"
location "PPCRecomp"
kind "ConsoleApp"
language "C++"
targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")
objdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")


files 
{
---base code
"PPCRecomp/includes/**.h",
"PPCRecomp/src/**.c",
"PPCRecomp/includes/**.hpp",
"PPCRecomp/src/**.cpp",

}

includedirs 
{
---base code
"PPCRecomp/includes",
PPCLib_Include,
FMT_INCLUDE
}

links
{
    PPCLib_Link
}

flags
{
"MultiProcessorCompile",
"NoRuntimeChecks",
}


buildoptions
{
"/utf-8",
}


--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Window_Build"
}

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Linux_Build"
}


    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"MacOS_Build"
}

--configs
filter "configurations:Debug"
    defines "PPC_DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "PPC_RELEASE"
    optimize "On"

filter "configurations:Dist"
    defines "PPC_DIST"
    optimize "On"


defines
{
"NDEBUG",
}

flags
{
"LinkTimeOptimization",
}