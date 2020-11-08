//
// Created by Yanuar Tri Aditya Nugraha on 2020-11-07.
//

#ifndef IMGUI_GLFW_GLAD_IMGUI_DEMO_H
#define IMGUI_GLFW_GLAD_IMGUI_DEMO_H

#include <GLFW/glfw3.h>
#include "imgui.h"

class Demo{
private:
    int screen_x, screen_y;
    bool show_demo_window=true, show_theme_window=true, show_another_window=false;

public:
    /* constructors */
    Demo();
    Demo(int, int);
    Demo(int, int, bool, bool, bool);

    /* public funcs */
    int init_glfw(int major, int minor);
    int play_demo();
    int play_demo_glfw_glad();

    /* static */
    static void glfw_error_callback(int error, const char* description);
    static void style_color_softy(ImGuiStyle* dst);
    static void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

#endif //IMGUI_GLFW_GLAD_IMGUI_DEMO_H
