project("glad")
    kind("StaticLib")
    language("C")
    cdialect("C11")

    targetdir(binaries)
    objdir(intermediate)

    files({
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/gl.c"
    })

    includedirs({
        "include"
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
            "NOMINMAX",
            "_CRT_SECURE_NO_WARNINGS"
        })

    filter("system:Linux")
        staticruntime("Off")

        defines({
            "SOL_PLATFORM_LINUX"
        })