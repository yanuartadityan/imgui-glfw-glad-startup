set(MODULES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../modules)

add_definitions(-DCPP_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../")

find_package(OpenCV REQUIRED)

list(APPEND MAIN_APP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MODULES_INCLUDE_DIR}/imgui
    ${MODULES_INCLUDE_DIR}/glm
    ${OpenCV_INCLUDE_DIRS}
    )

list(APPEND MAIN_APP_SOURCES
    imgui_impl_opengl3.h
    imgui_impl_opengl3.cpp
    imgui_demo.cpp
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_glfw.h
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cv_video.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cv_video.cpp
    )

set(NAME applib)
add_library(${NAME} ${MAIN_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} imgui glfw glm ${OpenCV_LIBS})

