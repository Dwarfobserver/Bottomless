
# Get client files

file(GLOB_RECURSE CLIENT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    
file(GLOB_RECURSE TESTS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

set(CLIENT_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Make the library

add_library(client_lib STATIC
    ${CLIENT_SOURCES})

target_include_directories(client_lib PUBLIC
    ${CLIENT_HEADERS}
    ${COMMON_HEADERS})

# Make the client

add_executable(client
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_include_directories(client PUBLIC
    ${CLIENT_HEADERS}
    ${COMMON_HEADERS})

target_link_libraries(client common client_lib)

# Make the tests

add_executable(client_tests
    ${TESTS_SOURCES})

target_include_directories(client_tests PUBLIC
    ${TESTS_HEADERS}
    ${COMMON_HEADERS}
    ${CLIENT_HEADERS})

target_link_libraries(client_tests common client_lib)

add_test(client "${EXECUTABLES_DIRECTORY}/client_tests")

# Add client macros

set(CLIENT_MACROS
    BTL_RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    BTL_CLIENT_TARGET
)
target_compile_definitions(client PRIVATE ${CLIENT_MACROS})
target_compile_definitions(client_lib PRIVATE ${CLIENT_MACROS})
target_compile_definitions(client_tests PRIVATE ${CLIENT_MACROS})
