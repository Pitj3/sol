project("math")
    kind("StaticLib")
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
        "%{Projects.math.include}"
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
        staticruntime("OFF")

        linkoptions({
            "/IGNORE:4006",
            "/IGNORE:4099"
        })

        defines({
            "PLATFORM_WIN32",
            "SOL_PLATFORM_WINDOWS",
            "NOMINMAX"
        })

    filter("system:Linux")
        staticruntime("OFF")

        defines({
            "SOL_PLATFORM_LINUX"
        })