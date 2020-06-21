get_filename_component(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(MODULES_INCLUDE_DIR ${THIRD_PARTY_DIR}/modules)

list(APPEND MAIN_APP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${MODULES_INCLUDE_DIR}/imgui"
    )

list(APPEND MAIN_APP_SOURCES
    main.cpp
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_opengl3.h
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_opengl3.cpp
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_glfw.h
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_glfw.cpp
    ${MODULES_INCLUDE_DIR}/glad/build/include/glad.h
    ${MODULES_INCLUDE_DIR}/glad/build/src/glad.c
    ${MODULES_INCLUDE_DIR}/glad/KHR/khrplatform.h
    )

set(MAIN_APP_LIBRARIES
    imgui
    glfw
    glad
    )

set(NAME imgui-glfw-glad-project)
add_executable(${NAME} ${MAIN_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${MAIN_APP_LIBRARIES})

