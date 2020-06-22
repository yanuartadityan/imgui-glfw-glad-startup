get_filename_component(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(MODULES_INCLUDE_DIR ${THIRD_PARTY_DIR}/modules)

message(${THIRD_PARTY_DIR})
message(${MODULES_INCLUDE_DIR})

list(APPEND MAIN_APP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${MODULES_INCLUDE_DIR}/imgui"
    )

list(APPEND MAIN_APP_SOURCES
    main.cpp
    imgui_impl_opengl3.h
    imgui_impl_opengl3.cpp
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_glfw.h
    ${MODULES_INCLUDE_DIR}/imgui/examples/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/KHR/khrplatform.h
    )

set(NAME imgui-glfw-glad-project)
add_executable(${NAME} ${MAIN_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} 
    imgui
    glfw
    )

