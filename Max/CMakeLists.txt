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


add_executable(Max main.cpp Graphics.hpp)

target_link_libraries(Max PRIVATE Eigen3::Eigen SDL3::SDL3)