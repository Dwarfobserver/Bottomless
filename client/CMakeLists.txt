
# Get client files

file(GLOB_RECURSE CLIENT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    
file(GLOB_RECURSE TESTS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

set(CLIENT_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Get dependencies

find_package(Opengl REQUIRED)
set(DEP_HEADERS
    "${GLEW_PATH}/include"
    "${GLFW_PATH}/include")

set(DEP_LIBRARIES
    "${GLEW_PATH}/${LIB_DIR}/glew.${LIB_EXT}"
    "${GLFW_PATH}/${LIB_DIR}/glfw.${LIB_EXT}")

# Make the library

add_library(client_lib STATIC
    ${CLIENT_SOURCES})

target_include_directories(client_lib PUBLIC
    ${CLIENT_HEADERS}
    ${COMMON_HEADERS}
    ${DEP_HEADERS})

# Make the client

add_executable(client
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_include_directories(client PUBLIC
    ${CLIENT_HEADERS}
    ${COMMON_HEADERS}
    ${DEP_HEADERS})

target_link_libraries(client
    common
    client_lib
    ${OPENGL_LIBRARY}
    ${DEP_LIBRARIES})

# Make the tests

if (NOT NO_TESTS)
    add_executable(client_tests
        ${TESTS_SOURCES})

    target_include_directories(client_tests PUBLIC
        ${TESTS_HEADERS}
        ${COMMON_HEADERS}
        ${CLIENT_HEADERS}
        ${DEP_HEADERS})

    target_link_libraries(client_tests
        common
        client_lib
        ${OPENGL_LIBRARY}
        ${DEP_LIBRARIES})

    add_test(client "${EXECUTABLES_DIRECTORY}/client_tests")
endif()

# Add client macros

set(CLIENT_MACROS
    BTL_RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    BTL_CLIENT_TARGET
    GLEW_STATIC
)
target_compile_definitions(client PRIVATE ${CLIENT_MACROS})
target_compile_definitions(client_lib PRIVATE ${CLIENT_MACROS})
if (NOT NO_TESTS)
    target_compile_definitions(client_tests PRIVATE ${CLIENT_MACROS})
endif()

