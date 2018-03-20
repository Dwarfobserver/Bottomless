
/// Provides informations on the build environment in the build namespace.

#pragma once

#define AS_STRING(value) #value

namespace build { // TODO Add constexpr char const* version, target, mode strings.

    /// The project version.

    constexpr int version_major = BTL_VERSION_MAJOR;
    constexpr int version_minor = BTL_VERSION_MINOR;

    constexpr char const* version_string =
        AS_STRING(BTL_VERSION_MAJOR) "." AS_STRING(BTL_VERSION_MINOR);

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

    /// The build target can be the common library, the client, the server or the tests.

    namespace target {
        enum {
            common,
            client,
            server,
            tests
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
    #elif defined(BTL_TESTS_TARGET)
    constexpr int current_target = target::tests;
    constexpr char const* target_string = "tests";
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
