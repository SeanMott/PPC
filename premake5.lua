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

--old lexer
---lexes the existing DTK Assembly into PPC IR
project "PPC"
location "PPC"
kind "ConsoleApp"
language "C++"
targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")
objdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Game")


files 
{
---base code
"PPC/includes/**.h",
"PPC/src/**.c",
"PPC/includes/**.hpp",
"PPC/src/**.cpp",

}

includedirs 
{
---base code
"PPC/includes",
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