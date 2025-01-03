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

---main frontend
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