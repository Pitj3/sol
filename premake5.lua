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
    group("")

    include("projects/math")
    
    Dependencies = {}

    Projects = {}
    Projects["math"] = {
        include = "%{sln.location}/projects/math/include"
    }

    NativeIncludeDirs = {}
