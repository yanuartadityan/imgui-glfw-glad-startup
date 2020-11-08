//
// Created by Yanuar Nugraha on 04/11/20.
//
#include "imgui_demo.h"

int main(int argc, char *argv[])
{
    Demo app(1680, 1050, true, true, false);
    app.play_demo_glfw_glad();
    // app.play_demo();

    return EXIT_SUCCESS;
}
