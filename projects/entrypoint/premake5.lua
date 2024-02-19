project("entrypoint")
    kind("ConsoleApp")
    language("C++")
    cppdialect("C++20")

    targetdir(binaries)
    objdir(intermediate)

    files({
        "include/**.hpp",
        "src/**.cpp",
        "src/**.hpp", -- private headers
    })

    includedirs({
        "src", -- private headers
        "%{Projects.sol.include}"
    })

    links({
        "sol"
    })

    filter("Debug")
        defines({
            "DEBUG",
            "_DEBUG"
        })

        symbols("On")

    filter("Release")
        defines({
            "NDEBUG"
        })

    filter("system:Windows")
        staticruntime("Off")

        linkoptions({
            "/IGNORE:4006",
            "/IGNORE:4099"
        })

        defines({
            "PLATFORM_WIN32",
            "SOL_PLATFORM_WINDOWS",
            "GLFW_EXPOSE_NATIVE_WIN32",
            "NOMINMAX"
        })

    filter("system:Linux")
        staticruntime("Off")

        defines({
            "SOL_PLATFORM_LINUX"
        })