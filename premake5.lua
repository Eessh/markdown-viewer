workspace "MarkdownViewer"
    configurations { "Debug", "Release" }
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    filter {}
    targetdir "bin/%{cfg.buildcfg}/"

    -- MarkdownViewer
    project "MarkdownViewer"
        kind "WindowedApp"
        language "C"
        includedirs {
            "include",
            "memsafe-boii",
            "md4c",
            "SDL2-2.26.4/include",
            "SDL2_ttf-2.20.2/include",
            "tinyfiledialogs",
            "Nuklear",
        }
        files {
            "src/*.c",
            -- "MarkdownViewer.c",
            "using_nuklear.c",
            "memsafe-boii/memsafe_boii.c",
            "md4c/md4c.c",
            "tinyfiledialogs/tinyfiledialogs.c",
        }
        filter { "system:windows" }
          links { "mingw32", "SDL2main", "SDL2", "SDL2_ttf", "comdlg32", "ole32" }
          libdirs { "SDL2-2.26.4/lib", "SDL2_ttf-2.20.2/lib", "C:\\msys64\\mingw64\\lib" }
        filter {}
        links { "SDL2main", "SDL2", "SDL2_ttf", "m", "dl" }
        libdirs { "SDL2-2.26.4/lib", "SDL2_ttf-2.20.2/lib" }
