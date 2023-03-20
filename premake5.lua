workspace "MarkdownViewer"
    configurations { "Debug", "Release" }
    filter "configurations:Debug"
        defines { "DEBUG", "INCLUDE_STYLE", "STYLE_WHITE" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG", "INCLUDE_STYLE", "STYLE_WHITE" }
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
            "log-boii",
            "md4c",
            "SDL2/include",
            "SDL2_ttf/include",
            "tinyfiledialogs",
            "Nuklear",
        }
        files {
            "src/*.c",
            -- "MarkdownViewer.c",
            "using_nuklear.c",
            "memsafe-boii/memsafe_boii.c",
            "log-boii/log_boii.c",
            "md4c/md4c.c",
            "tinyfiledialogs/tinyfiledialogs.c",
        }
        filter { "system:windows" }
          links { "mingw32", "SDL2main", "SDL2", "SDL2_ttf", "comdlg32", "ole32" }
          libdirs { "SDL2/lib", "SDL2_ttf/lib" }
        filter { "system:linux" }
            links { "SDL2main", "SDL2", "SDL2_ttf", "m", "dl" }
            libdirs { "SDL2/lib", "SDL2_ttf/lib" }
        filter { "system:macos" }
            links { "SDL2main", "SDL2", "SDL2_ttf", "m", "dl" }
            libdirs { "SDL2/lib", "SDL2_ttf/lib" }
