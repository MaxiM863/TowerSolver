cmake_minimum_required(VERSION 3.10) # Specify a minimum required CMake version
project(Max)                  # Define the project name

include(FetchContent)

FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG master # Or a specific commit hash
)

FetchContent_MakeAvailable(Eigen3)

set(SDL3_VERSION "release-3.2.22") # Or any other desired version/tag

    # Declare the content to be fetched
    FetchContent_Declare(
        SDL3
        URL https://github.com/libsdl-org/SDL/archive/refs/tags/${SDL3_VERSION}.tar.gz # For Unix/Linux
        # Or for Windows: URL https://github.com/libsdl-org/SDL/archive/refs/tags/${SDL3_VERSION}.zip
    )

    # Make the fetched content available
    FetchContent_MakeAvailable(SDL3)


add_executable(Max main.cpp Graphics.hpp Node.hpp Element.hpp Constraint.hpp Force.hpp Material.hpp Section.hpp Solver.hpp Tests.hpp)

target_link_libraries(Max PRIVATE Eigen3::Eigen SDL3::SDL3)

target_include_directories(Max PRIVATE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/_deps/sdl3-src/include)

set_target_properties(Max PROPERTIES
    VS_DEBUGGER_COMMAND_ARGUMENTS "maxim.txt"
)

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