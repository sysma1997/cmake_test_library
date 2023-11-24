# GENERAL
cmake_minimum_required(VERSION 3.25)

project(test VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(test_main "./main.cpp")

set(BUILD_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${BUILD_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BUILD_PATH})

# LIBRARIES
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE libraries "libs/*.dll")
file(COPY ${libraries} DESTINATION ${BUILD_PATH}/)

link_directories(libs/sysma
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR})

# SRC AND LIBS MANUAL
file(GLOB_RECURSE test_lib_src 
    "libs/*.h" "libs/*.hpp" "libs/*.cpp"
    "src/*.h" "src/*.cpp")

# COMPILED
add_executable(test ${test_main} ${test_lib_src})
target_link_libraries(test 
    libsysma.dll
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARIES}
    glfw)