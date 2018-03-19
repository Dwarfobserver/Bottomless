
/// Provides informations on the build environment in the build namespace.

#pragma once

namespace build {

    /// The project version.

    constexpr int version_major = BTL_VERSION_MAJOR;
    constexpr int version_minor = BTL_VERSION_MINOR;

    /// The build mode indicates if it is in debug or release mode.

    namespace mode {
        enum {
            release,
            debug
        };
    }
    #if   defined(_DEBUG)
    constexpr int current_mode = mode::debug;
    #elif defined(NDEBUG)
    constexpr int current_mode = mode::release;
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
    #elif defined(BTL_CLIENT_TARGET)
    constexpr int current_target = target::client;
    #elif defined(BTL_SERVER_TARGET)
    constexpr int current_target = target::server;
    #elif defined(BTL_TESTS_TARGET)
    constexpr int current_target = target::tests;
    #else
    #error Current build target could not be detected.
    #endif

    /// The resource path is the root of files neeed by the program.

    #if defined(BTL_RESOURCES_PATH)
    char const* resources_path = BTL_RESOURCES_PATH;
    constexpr bool has_resources = true;
    #else
    char const* resources_path = nullptr;
    constexpr bool has_resources = false;
    #endif

}
