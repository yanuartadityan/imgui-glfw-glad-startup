//
// Created by Yanuar Tri Aditya Nugraha on 2020-11-07.
//

#ifndef IMGUI_GLFW_GLAD_IMGUI_DEMO_H
#define IMGUI_GLFW_GLAD_IMGUI_DEMO_H

#include "imgui.h"

//static void glfw_error_callback(int error, const char* description);
//void StyleColorSofty(ImGuiStyle*);
//int play_demo();
//int play_demo_glfw_glad();

class Demo{
private:
    int screen_x, screen_y;
    bool show_demo_window=true, show_theme_window=true, show_another_window=false;

public:
    Demo();
    Demo(int, int);
    Demo(int, int, bool, bool, bool);
    int init_glfw(int major, int minor);
    int play_demo();
    int play_demo_glfw_glad();
    static void glfw_error_callback(int error, const char* description);
    static void style_color_softy(ImGuiStyle* dst);
};

#endif //IMGUI_GLFW_GLAD_IMGUI_DEMO_H
