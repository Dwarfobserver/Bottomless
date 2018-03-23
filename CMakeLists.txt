
# Root CMakeLists.txt

# TODO To avoid building tests, add -DNO_TESTS=1

project(bottomless)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

# Check the build type (debug by default)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "Debug mode (specified by -DCMAKE_BUILD_TYPE=Debug or Release)")
else()
    if    (CMAKE_BUILD_TYPE MATCHES Debug)
        message(STATUS "Debug mode")
    elseif(CMAKE_BUILD_TYPE MATCHES Release)
        message(STATUS "Release mode")
    else()
        message(FATAL_ERROR "Only Debug and Release CMAKE_BUILD_TYPE are supported (default = Debug)")
    endif()
endif()

# Check if tests are built (yes by default)

if (NOT NO_TESTS)
    message(STATUS "Tests enabled (they can be disabled with -DNO_TESTS=1)")
else()
    message(STATUS "Tests disabled")
endif()

# Add compiler-specific flags

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(FATAL_ERROR "MSVC is not supported")
elseif(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR
       ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    add_compile_options(
#        "-Wall -std=c++17"
#        "$<$<CONFIG:RELASE>:-O3>"
    )
else()
    message(FATAL_ERROR "Compiler not supported (it must be GCC or Clang, on Windows or Linux")
endif()

# Add mode-specific definitions

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG)
else()
    add_definitions(-DNDEBUG)
endif()

# Add generic definitions

add_definitions(
    -DBTL_VERSION_MAJOR=0
    -DBTL_VERSION_MINOR=1
    -DASIO_STANDALONE
    -DRESOURCES_PATH="${CMAKE_SOURCE_DIR}/resources"
)

# Put the executables in the bin directory

set(EXECUTABLES_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${EXECUTABLES_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLES_DIRECTORY})

# Add the common code part, the client, the server with their tests

set(TESTS_HEADERS "${CMAKE_SOURCE_DIR}/dependencies/catch2/include")

if (NOT NO_TESTS)
    enable_testing()
endif()

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
