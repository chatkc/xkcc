cmake_minimum_required(VERSION 3.18)

project(xkcc VERSION 1.0.0 LANGUAGES CXX)

find_package(Lua REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core WebSockets Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(xkcc ${SOURCES})

target_include_directories(xkcc
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${LUA_INCLUDE_DIR}
)

target_link_libraries(xkcc
    PRIVATE
        ${LUA_LIBRARIES}
        Qt6::Core
        Qt6::WebSockets
        Qt6::Widgets
)

add_custom_command(TARGET xkcc POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/plugins/ $<TARGET_FILE_DIR:xkcc>/plugins/)