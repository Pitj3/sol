workspace("sol")
    configurations({
        "Debug",
        "Release"
    })

    sln = solution()
    binaries = "%{sln.location}/bin/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"
    intermediate = "%{sln.location}/bin-int/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

    startproject("entrypoint")
    architecture("x64")

    group("External Dependencies")
    include("dependencies/glad")
    include("dependencies/glfw")
    group("")

    include("projects/engine")
    include("projects/math")
    include("projects/entrypoint")
    
    Dependencies = {}

    Projects = {}
    Projects["sol"] = {
        include = "%{sln.location}/projects/engine/include"
    }
    Projects["math"] = {
        include = "%{sln.location}/projects/math/include"
    }

    NativeIncludeDirs = {}
    NativeIncludeDirs["glfw"] = "%{sln.location}/dependencies/glfw/include"
    NativeIncludeDirs["glad"] = "%{sln.location}/dependencies/glad/include"
    NativeIncludeDirs["spdlog"] = "%{sln.location}/dependencies/spdlog/include"
