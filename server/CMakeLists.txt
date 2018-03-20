
# Get server files

file(GLOB_RECURSE SERVER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    
file(GLOB_RECURSE TESTS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

set(SERVER_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Make the library

add_library(server_lib STATIC
    ${SERVER_SOURCES})

target_include_directories(server_lib PUBLIC
    ${SERVER_HEADERS}
    ${COMMON_HEADERS})

# Make the server

add_executable(server
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_include_directories(server PUBLIC
    ${SERVER_HEADERS}
    ${COMMON_HEADERS})

target_link_libraries(server common server_lib)

# Make the tests

add_executable(server_tests
    ${TESTS_SOURCES})

target_include_directories(server_tests PUBLIC
    ${TESTS_HEADERS}
    ${COMMON_HEADERS}
    ${SERVER_HEADERS})

target_link_libraries(server_tests common server_lib)

add_test(server "${EXECUTABLES_DIRECTORY}/server_tests")

# Add server macros

set(SERVER_MACROS
    BTL_RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    BTL_SERVER_TARGET
)
target_compile_definitions(server PRIVATE ${SERVER_MACROS})
target_compile_definitions(server_lib PRIVATE ${SERVER_MACROS})
target_compile_definitions(server_tests PRIVATE ${SERVER_MACROS})
