cmake_minimum_required (VERSION 3.10)
project (imgui-glfw-glad)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE "Debug")

add_definitions(-DCPP_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")

set(APPEND MAIN_HEADER_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/sources)

add_subdirectory(modules)
add_subdirectory(sources)

set(EXEC_NAME imgui-glfw-glad-startup)
add_executable(${EXEC_NAME} main.cpp)
target_include_directories(${EXEC_NAME} PRIVATE ${MAIN_HEADER_DIRS})
target_link_libraries(${EXEC_NAME} applib)