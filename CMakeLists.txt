# GENERAL
cmake_minimum_required(VERSION 3.25)

project(sysma VERSION 1.0.1 DESCRIPTION "SYSMA library")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

set(sysma_main "src/sysma.cpp")

# FRAMEWORKS
find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

file(GLOB_RECURSE sysma_src 
    "src/*.cpp")
file(GLOB_RECURSE sysma_headers_src_h
    "src/*.h")
file(GLOB sysma_headers_src 
    "src/*")
file(COPY ${sysma_headers_src} DESTINATION ${BUILD_PATH}/ 
    FILES_MATCHING PATTERN "*.h")

include(GNUInstallDirs)
add_library(sysma SHARED ${sysma_main} ${sysma_src})
target_link_libraries(sysma
    ${SQLite3_LIBRARIES})
set_target_properties(sysma PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER src/sysma.h
    PUBLIC_HEADER src/storage.h
    PUBLIC_HEADER src/storage/user.h)
    #PUBLIC_HEADER "${sysma_headers_src_h}")
configure_file(sysma.pc.in sysma.pc @ONLY)
target_include_directories(sysma PRIVATE .)
install(TARGETS sysma
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/sysma.pc 
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)