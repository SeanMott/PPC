workspace "PowerPCToC"
architecture "x64"
startproject "PPC"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}"

--the frontend PPC program that users pass flags into
project "PPC"
location "PPC"
kind "ConsoleApp"
language "C++"

files 
{
    "PPC/includes/**.h",
    "PPC/src/**.c",
    "PPC/includes/**.hpp",
    "PPC/src/**.cpp",
}

includedirs
{
    "DTK_PPC_Lexer/includes",

    "DTK_PowerPCDecoder/includes",

    "C:/Compilers/PPC/Venders/fmt/include/**.h"
}
    
links
{
    "DTK_PPC_Lexer"
}
    
flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}

buildoptions { "/utf-8" } --used for fmt
    
--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
    
defines
{
    "Window_Build",
    "Desktop_Build"
}
    
--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"
    
filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"
    
filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"
    
defines
{
    "NDEBUG"
}

--the lexer for generating metadata based on DTK assembly
project "DTK_PPC_Lexer"
location "DTK_PPC_Lexer"
kind "StaticLib"
language "C++"

files 
{
    "DTK_PPC_Lexer/includes/**.h",
    "DTK_PPC_Lexer/src/**.c",
    "DTK_PPC_Lexer/includes/**.hpp",
    "DTK_PPC_Lexer/src/**.cpp",

    "C:/Compilers/PPC/Venders/fmt/src/**.c",
    "C:/Compilers/PPC/Venders/fmt/src/**.cpp"
}

includedirs
{
    "DTK_PPC_Lexer/includes",

    "DTK_PowerPCDecoder/includes",

    "C:/Compilers/PPC/Venders/fmt/include/**.h"
}
    
links
{
       "DTK_PowerPCDecoder"
}
    
flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}
 
buildoptions { "/utf-8" } --used for fmt

--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
    
defines
{
    "Window_Build",
    "Desktop_Build"
}
    
--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"
    
filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"
    
filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"
    
defines
{
    "NDEBUG"
}

--the Power PC decoder for DTK
project "DTK_PowerPCDecoder"
location "DTK_PowerPCDecoder"
kind "StaticLib"
language "C++"

files 
{
    "DTK_PowerPCDecoder/includes/**.h",
    "DTK_PowerPCDecoder/src/**.c",
    "DTK_PowerPCDecoder/includes/**.hpp",
    "DTK_PowerPCDecoder/src/**.cpp",

    "C:/Compilers/PPC/Venders/fmt/src/**.c",
    "C:/Compilers/PPC/Venders/fmt/src/**.cpp"
}

includedirs
{
    "DTK_PowerPCDecoder/includes",

    "C:/Compilers/PPC/Venders/fmt/include/**.h"
}
    
links
{
       
}
    
flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}
 
buildoptions { "/utf-8" } --used for fmt

--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
    
defines
{
    "Window_Build",
    "Desktop_Build"
}
    
--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"
    
filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"
    
filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"
    
defines
{
    "NDEBUG"
}

--the Static Recomp Layer that implements Seafoam and the Opcode Macros

--the tool for generating PC Port Projects on any platform