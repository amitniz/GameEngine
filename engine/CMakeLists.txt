
cmake_minimum_required(VERSION 3.0.0)
project(OdysseyEngine VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g)

# Set the make program
set(CMAKE_MAKE_PROGRAM "/usr/bin/make")  # Change this path as needed

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "/opt/vcpkg/installed/x64-linux" ${CMAKE_PREFIX_PATH})
set(CMAKE_TOOLCHAIN_FILE "D:/gits/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Add your source and header files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# Add include directories
include_directories(include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# Create the shared library
add_library(OdysseyEngine SHARED ${SOURCES} ${HEADERS})

# packages
find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp CONFIG REQUIRED)
 
set(STB_INCLUDE_DIR "/opt/vcpkg/installed/x64-linux/include")
target_include_directories(OdysseyEngine PRIVATE
    ${STB_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)
target_link_libraries(OdysseyEngine PRIVATE  
    nlohmann_json::nlohmann_json
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    glfw
    assimp::assimp
    OpenGL::GL
)
