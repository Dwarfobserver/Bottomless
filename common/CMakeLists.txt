
# Get common source files
file(GLOB_RECURSE COMMON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Get common header files
set(COMMON_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/dependencies/asio-1.10.8/include"
)
set(COMMON_HEADERS ${COMMON_HEADERS} PARENT_SCOPE)

# Make the library
add_library(common STATIC
    ${COMMON_SOURCES}
)

# Set include directories
target_include_directories(common PUBLIC
    ${COMMON_HEADERS}
)

# Specific macros
target_compile_definitions(common PRIVATE
    BTL_COMMON_TARGET
)
