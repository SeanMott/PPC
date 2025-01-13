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

--symbol cruncher, munches on DTK Symbols and splits and generates a Symbol Map PPC can use
project "PPCSymbolCruncher"
location "PPCSymbolCruncher"
kind "ConsoleApp"
language "C++"
targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")
objdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")


files 
{
---base code
"PPCSymbolCruncher/includes/**.h",
"PPCSymbolCruncher/src/**.c",
"PPCSymbolCruncher/includes/**.hpp",
"PPCSymbolCruncher/src/**.cpp",

}

includedirs 
{
---base code
"PPCSymbolCruncher/includes",
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

--lexer for generating tokenized streams
project "PPCLexer"
location "PPCLexer"
kind "ConsoleApp"
language "C++"
targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")
objdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")


files 
{
---base code
"PPCLexer/includes/**.h",
"PPCLexer/src/**.c",
"PPCLexer/includes/**.hpp",
"PPCLexer/src/**.cpp",

}

includedirs 
{
---base code
"PPCLexer/includes",
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