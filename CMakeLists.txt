cmake_minimum_required(VERSION 3.16)

project(xkcc VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(xkcc ${SOURCES})

target_include_directories(xkcc
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(xkcc
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)