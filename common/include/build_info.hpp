
/// Provides informations on the build environment in the build namespace.

#pragma once

namespace build { // TODO Add constexpr char const* version, target, mode strings.

    /// The project version.

    constexpr int version_major = BTL_VERSION_MAJOR;
    constexpr int version_minor = BTL_VERSION_MINOR;

#define AS_EXPANDED_STRING(value) AS_STRING(value)
#define AS_STRING(value) #value

    constexpr char const* version_string =
        AS_EXPANDED_STRING(BTL_VERSION_MAJOR) "." AS_EXPANDED_STRING(BTL_VERSION_MINOR);

#undef AS_EXPANDED_STRING
#undef AS_STRING

    /// The build mode indicates if it is in debug or release mode.

    namespace mode {
        enum {
            release,
            debug
        };
    }
    #if   defined(_DEBUG)
    constexpr int current_mode  =  mode::debug;
    constexpr char const* mode_string = "debug";
    #elif defined(NDEBUG)
    constexpr int current_mode  =  mode::release;
    constexpr char const* mode_string = "release";
    #else
    #error Current build mode could not be detected.
    #endif

    /// The build target can be the common library, the client or the server.

    namespace target {
        enum {
            common,
            client,
            server
        };
    }
    #if   defined(BTL_COMMON_TARGET)
    constexpr int current_target = target::common;
    constexpr char const* target_string = "common";
    #elif defined(BTL_CLIENT_TARGET)
    constexpr int current_target = target::client;
    constexpr char const* target_string = "client";
    #elif defined(BTL_SERVER_TARGET)
    constexpr int current_target = target::server;
    constexpr char const* target_string = "server";
    #else
    #error Current build target could not be detected.
    #endif

    /// The resource path is the root of files neeed by the program.

    #if defined(BTL_RESOURCES_PATH)
    constexpr char const* resources_path = BTL_RESOURCES_PATH;
    constexpr bool has_resources = true;
    #else
    constexpr char const* resources_path = nullptr;
    constexpr bool has_resources = false;
    #endif

}
