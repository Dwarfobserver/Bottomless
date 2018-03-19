
# Get tests source files
file(GLOB_RECURSE TESTS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Make the executable
add_executable(tests
    ${TESTS_SOURCES}
    ${CLIENT_SOURCES}
    ${SERVER_SOURCES}
)

# Set include directories
target_include_directories(tests PUBLIC
    "${CMAKE_SOURCE_DIR}/dependencies/catch2/include"
    ${COMMON_HEADERS}
    ${CLIENT_HEADERS}
    ${SERVER_HEADERS}
)

# Link to the common part
target_link_libraries(tests common)

# Specific macros
target_compile_definitions(tests PRIVATE
    BTL_TESTS_TARGET
)
