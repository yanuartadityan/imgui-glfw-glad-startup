//
// Created by Yanuar Nugraha on 04/11/20.
//

#include <iostream>
#include "imgui_demo.h"

using namespace std;

int main(int argc, char *argv[])
{
    Demo app(2560, 1440, true, true, false);
    app.play_demo();

    return EXIT_SUCCESS;
}
