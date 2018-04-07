
# Get common files

file(GLOB_RECURSE COMMON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE TESTS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

set(COMMON_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/deps/asio-1.10.8/include")
set(COMMON_HEADERS ${COMMON_HEADERS} PARENT_SCOPE)

# Make the library

add_library(common STATIC
    ${COMMON_SOURCES})

target_include_directories(common PUBLIC
    ${COMMON_HEADERS})

# Make the tests

if (NOT NO_TESTS)
    add_executable(common_tests
        ${TESTS_SOURCES})

    target_include_directories(common_tests PUBLIC
        ${TESTS_HEADERS}
        ${COMMON_HEADERS})

    target_link_libraries(common_tests common)

    add_test(common "${EXECUTABLES_DIRECTORY}/common_tests")
endif()

# Specific macros

set(COMMON_MACROS
    BTL_COMMON_TARGET
)
target_compile_definitions(common PRIVATE ${COMMON_MACROS})
if (NOT NO_TESTS)
    target_compile_definitions(common_tests PRIVATE ${COMMON_MACROS})
endif()
