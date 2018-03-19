
# Get client source files, excluding the main
file(GLOB_RECURSE CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(CLIENT_SOURCES ${CLIENT_SOURCES} PARENT_SCOPE)

# Get client header files
set(CLIENT_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set(CLIENT_HEADERS ${CLIENT_HEADERS} PARENT_SCOPE)

# Make the executable
add_executable(client
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    ${CLIENT_SOURCES}
)

# Set include directories
target_include_directories(client PUBLIC
    ${CLIENT_HEADERS}
    ${COMMON_HEADERS}
)

# Link to the common part
target_link_libraries(client common)

# Specific macros
target_compile_definitions(client PRIVATE
    BTL_RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    BTL_CLIENT_TARGET
)
