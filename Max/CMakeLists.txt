cmake_minimum_required(VERSION 3.2.2) # Specify a minimum required CMake version
project(Max)                  # Define the project name



include(FetchContent)



set(SDL3_VERSION "release-3.2.22") # Or any other desired version/tag

# Declare the content to be fetched
FetchContent_Declare(
    SDL3
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/${SDL3_VERSION}.tar.gz # For Unix/Linux
    # Or for Windows: URL https://github.com/libsdl-org/SDL/archive/refs/tags/${SDL3_VERSION}.zip
)

# Make the fetched content available
FetchContent_MakeAvailable(SDL3)


include(FetchContent)
FetchContent_Declare (
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "")
set(GLFW_INSTALL OFF CACHE BOOL  "")

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(eigen GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git GIT_TAG 3.4.0)
#FetchContent_Populate(eigen)
FetchContent_MakeAvailable(eigen)
#set(CMAKE_PREFIX_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../eigen/build")
#find_package(Eigen3 3.4.90 EXACT REQUIRED)

add_executable(Max main.cpp Graphics.hpp Node.hpp Element.hpp Constraint.hpp Force.hpp Material.hpp Section.hpp Solver.hpp Tests.hpp Cylinder.hpp)

target_link_libraries(Max PUBLIC Eigen3::Eigen SDL3::SDL3 glfw opengl32)


target_include_directories(Max PUBLIC ${PROJECT_SOURCE_DIR}/../../eigen/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/_deps/sdl3-src/include ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/_deps/glfw-src/include)


if (WIN32)
    # Set the executable output directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    # Specify the file to copy (e.g., a DLL or config file)
    set(FILE_TO_COPY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/_deps/sdl3-build/Debug/SDL3.dll)

    # Define the destination directory (same as the executable directory)
    set(DESTINATION_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Max/Debug/SDL3.dll)

    # Add a custom command to copy the file after the build
    add_custom_command(
        TARGET Max POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${FILE_TO_COPY} ${DESTINATION_DIR}
        COMMENT "Copying example.dll to the executable directory"
    )
endif (WIN32)

if (UNIX)
    
endif (UNIX)