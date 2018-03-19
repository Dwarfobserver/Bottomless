
# Get server source files, excluding the main
file(GLOB_RECURSE SERVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(SERVER_SOURCES ${SERVER_SOURCES} PARENT_SCOPE)

# Get server header files
set(SERVER_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set(SERVER_HEADERS ${SERVER_HEADERS} PARENT_SCOPE)

# Make the executable
add_executable(server
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    ${SERVER_SOURCES}
)

# Set include directories
target_include_directories(server PUBLIC
    ${SERVER_HEADERS}
    ${COMMON_HEADERS}
)

# Link to the common part
target_link_libraries(server common)

# Specific macros
target_compile_definitions(server PRIVATE
    BTL_RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    BTL_SERVER_TARGET
)
