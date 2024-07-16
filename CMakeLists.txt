cmake_minimum_required(VERSION 3.10)
project(Simulations)

set(CMAKE_C_STANDARD 99)

# Define directories
set(SRC_DIR src)
set(BUILD_DIR build)
set(BIN_DIR bin)

# Specify source files
file(GLOB SRC_FILES ${SRC_DIR}/*.c)

# Add executable
add_executable(sim ${SRC_FILES})

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(include ${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(sim /usr/local/Cellar/sdl2/2.30.5/lib/libSDL2.dylib)

# Set RPATH for runtime
set_target_properties(sim PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${BUILD_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${BUILD_DIR}"
    INSTALL_RPATH_USE_LINK_PATH TRUE
    BUILD_RPATH /usr/local/Cellar/sdl2/2.30.5/lib
    INSTALL_RPATH /usr/local/Cellar/sdl2/2.30.5/lib
)
