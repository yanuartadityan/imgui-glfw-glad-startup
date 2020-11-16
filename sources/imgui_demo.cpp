//
// Created by Yanuar Tri Aditya Nugraha on 2020-11-07.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "imgui_demo.h"
#include "imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"


/* constructors */
Demo::Demo(){
    this->screen_x = 1280;
    this->screen_y = 1024;
}

Demo::Demo(int x, int y){
    this->screen_x = x;
    this->screen_y = y;
}

Demo::Demo(int x, int y, bool show_demo_w, bool show_theme_w, bool show_another_w) {
    this->screen_x = x;
    this->screen_y = y;
    this->show_demo_window = show_demo_w;
    this->show_theme_window = show_theme_w;
    this->show_another_window = show_another_w;
}

/* all static function definitions */
void Demo::glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void Demo::glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void Demo::style_color_softy(ImGuiStyle *dst=nullptr) {
    ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();

    int hspacing = 8;
    int vspacing = 6;
    style->DisplaySafeAreaPadding = ImVec2(0, 0);
    style->WindowPadding = ImVec2(hspacing/2, vspacing);
    style->FramePadding = ImVec2(hspacing, vspacing);
    style->ItemSpacing = ImVec2(hspacing, vspacing);
    style->ItemInnerSpacing = ImVec2(hspacing, vspacing);
    style->IndentSpacing = 20.0f;

    style->WindowRounding = 0.0f;
    style->FrameRounding = 0.0f;

    style->WindowBorderSize = 0.0f;
    style->FrameBorderSize = 1.0f;
    style->PopupBorderSize = 1.0f;

    style->ScrollbarSize = 20.0f;
    style->ScrollbarRounding = 0.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 0.0f;

    ImVec4 white = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 transparent = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    ImVec4 dark = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    ImVec4 darker = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);

    ImVec4 background = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 text = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    ImVec4 border = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    ImVec4 grab = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    ImVec4 header = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    ImVec4 active = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    ImVec4 hover = ImVec4(0.00f, 0.47f, 0.84f, 0.20f);

    style->Colors[ImGuiCol_Text] = text;
    style->Colors[ImGuiCol_WindowBg] = background;
    style->Colors[ImGuiCol_ChildBg] = background;
    style->Colors[ImGuiCol_PopupBg] = white;

    style->Colors[ImGuiCol_Border] = border;
    style->Colors[ImGuiCol_BorderShadow] = transparent;

    style->Colors[ImGuiCol_Button] = header;
    style->Colors[ImGuiCol_ButtonHovered] = hover;
    style->Colors[ImGuiCol_ButtonActive] = active;

    style->Colors[ImGuiCol_FrameBg] = white;
    style->Colors[ImGuiCol_FrameBgHovered] = hover;
    style->Colors[ImGuiCol_FrameBgActive] = active;

    style->Colors[ImGuiCol_MenuBarBg] = header;
    style->Colors[ImGuiCol_Header] = header;
    style->Colors[ImGuiCol_HeaderHovered] = hover;
    style->Colors[ImGuiCol_HeaderActive] = active;

    style->Colors[ImGuiCol_CheckMark] = text;
    style->Colors[ImGuiCol_SliderGrab] = grab;
    style->Colors[ImGuiCol_SliderGrabActive] = darker;

    //style->Colors[ImGuiCol_CloseButton] = transparent;
    //style->Colors[ImGuiCol_CloseButtonHovered] = transparent;
    //style->Colors[ImGuiCol_CloseButtonActive] = transparent;

    style->Colors[ImGuiCol_ScrollbarBg] = header;
    style->Colors[ImGuiCol_ScrollbarGrab] = grab;
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = dark;
    style->Colors[ImGuiCol_ScrollbarGrabActive] = darker;
}

void Demo::get_file_path(const std::string &fullPath, std::string &pathWithoutFile) {
    size_t found = fullPath.find_last_of("/\\");
    pathWithoutFile = fullPath.substr(0, found + 1);
}

std::string Demo::load_shader(const std::string& fpath, std::string inc_identifier) {
    inc_identifier += ' ';
    static bool is_recurse = false;

    std::string full_shaders_code;
    std::ifstream file(fpath);

    if (!file.is_open()){
        std::cerr << "error:load:shader:could_not_open_the_shader_at: " << fpath << std::endl;
        return full_shaders_code;
    }

    // iterate all lines
    std::string lineBuf;
    while (std::getline(file, lineBuf)){
        // look for #include identifier
        if (lineBuf.find(inc_identifier) != lineBuf.npos){
            // found it, remove the identifier, then recursively find the code
            lineBuf.erase(0, inc_identifier.size());

            // traverse
            std::string path_of_this_file;
            Demo::get_file_path(fpath, path_of_this_file);
            lineBuf.insert(0, path_of_this_file);

            // going in
            is_recurse = true;
            full_shaders_code += Demo::load_shader(lineBuf);

            continue;
        }

        full_shaders_code += lineBuf + '\n';
    }

    if (!is_recurse)
        full_shaders_code += '\0';

    file.close();

    return full_shaders_code;
}

/* non-static */
int Demo::init_glfw(int major, int minor) {
    // setup glfw
    glfwSetErrorCallback(this->glfw_error_callback);
    if (!glfwInit())
        return EXIT_FAILURE;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create main window
    this->main_window = glfwCreateWindow(this->screen_x, this->screen_y, "Demo: OpenGL Only", nullptr, nullptr);

    return EXIT_SUCCESS;
}

int Demo::init_glad(){
    gladLoadGL();

    return EXIT_SUCCESS;
}

void Demo::process_input() {
    if(glfwGetKey(this->main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->main_window, true);
}

void Demo::set_context_window(GLFWwindow* handle){
    glfwMakeContextCurrent(handle);
}

void Demo::set_vsync(int vsync_state){
    glfwSwapInterval(vsync_state);
}

void Demo::set_viewport(int x_origin, int y_origin){
    // set the viewport
    std::cout << "Setting the viewport:..." << std::endl;
    std::cout << "Width of the screen: " << this->screen_x << std::endl;
    std::cout << "Height of the screen: " << this->screen_y << std::endl;
    glViewport(x_origin, y_origin, this->screen_x, this->screen_y);
}

void Demo::set_shaders(unsigned int& shaderProgram,
                       unsigned int& vertexShader,
                       const std::string& vertexShaderPath,
                       unsigned int& fragShader,
                       const std::string& fragShaderPath)
{
    // --- optional: create vertex shader
    const std::string vertexShaderSource = Demo::load_shader(vertexShaderPath);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_str = vertexShaderSource.c_str();
    std::cout << vertex_str << std::endl;
    glShaderSource(vertexShader, 1, &vertex_str, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLogVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLogVertex);
        std::cout << "error:shader:vertex:compilation_failed\n" << infoLogVertex << std::endl;
    }

    // create fragment shader
    const std::string fragShaderSource = Demo::load_shader(fragShaderPath);

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *frag_str = fragShaderSource.c_str();
    std::cout << frag_str << std::endl;
    glShaderSource(fragShader, 1, &frag_str, nullptr);
    glCompileShader(fragShader);

    char infoLogFrag[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, nullptr, infoLogFrag);
        std::cout << "error:shader:fragment:compilation_failed\n" << infoLogFrag << std::endl;
    }

    // create program and link both vertex and fragments shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    char infoLogProg[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLogProg);
        std::cout << "error:program:link_failed\n" << infoLogProg << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void Demo::set_buffers(float *input_vertices, size_t vertices_size){
//    float input_vertices[] = {
//            -0.5f, -0.5f, 0.0f, // left
//            0.5f, -0.5f, 0.0f, // right
//            0.0f,  0.5f, 0.0f  // top
//    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, input_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

int Demo::play_demo(){
    // setup glfw
    this->init_glfw(3, 3);

    glfwMakeContextCurrent(this->main_window);
    glfwSwapInterval(0); // Enable vsync

    // load GL binders (either GLAD, GL3W or OpenGL)
    gladLoadGL();

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(this->main_window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();
    // ImGui::StyleColorsLight();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);

    auto font_default = io.Fonts->AddFontDefault();
    auto font_cousine = io.Fonts->AddFontFromFileTTF( CPP_SRC_DIR "modules/imgui/misc/fonts/Cousine-Regular.ttf", 14.0f);
    auto font_karla   = io.Fonts->AddFontFromFileTTF( CPP_SRC_DIR "modules/imgui/misc/fonts/Karla-Regular.ttf", 14.0f);
    auto font_lato    = io.Fonts->AddFontFromFileTTF( CPP_SRC_DIR "fonts/Lato-Regular.ttf", 14.0f);


    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(this->main_window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static int font_current = 0;
        static int old_font_current = 0;
        switch (font_current)
        {
            case 0:
                ImGui::PushFont(font_default);
                break;
            case 1:
                ImGui::PushFont(font_cousine);
                break;
            case 2:
                ImGui::PushFont(font_karla);
                break;
            case 3:
                ImGui::PushFont(font_lato);
                break;
        }


        // 1. Show a simple window.
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Text("Windows");
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Themes Window", &show_theme_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::Text("Font Samples");
            ImGui::PushFont(font_cousine);
            ImGui::Text("Font Render Test - Cousine: Bit Test.123");
            ImGui::Text("Font Render Test - Cousine: XXXXXXXXXXXX");
            ImGui::PopFont();

            ImGui::PushFont(font_karla);
            ImGui::Text("Font Render Test - Karla: Bit Test.123");
            ImGui::Text("Font Render Test - Karla: XXXXXXXXXXXX");
            ImGui::PopFont();

            ImGui::PushFont(font_lato);
            ImGui::Text("Font Render Test - Lato: Bit Test.123");
            ImGui::Text("Font Render Test - Lato: XXXXXXXXXXXX");
            ImGui::PopFont();

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
        if (this->show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // 3. Show theme window
        if (this->show_theme_window)
        {
            ImGui::Begin("Themes", &show_theme_window);
            {
                // Using the _simplified_ one-liner Combo() api here
                // See "Combo" section for examples of how to use the more complete BeginCombo()/EndCombo() api.
                const char* themes[] = { "Light", "Dark", "Default", "Softy" };
                static int theme_current = 0;
                static int old_theme_current = 0;
                ImGui::Combo("theme-combo", &theme_current, themes, IM_ARRAYSIZE(themes));
                if (old_theme_current != theme_current)
                {
                    old_theme_current = theme_current;

                    switch (theme_current)
                    {
                        case 0:
                            ImGui::StyleColorsLight();
                            break;
                        case 1:
                            ImGui::StyleColorsDark();
                            break;
                        case 2:
                            ImGui::StyleColorsClassic();
                            break;
                        case 3:
                            Demo::style_color_softy();
                            break;
                    }
                }

                const char* fonts[] = { "Default", "Cousine", "Karla", "Lato" };
                ImGui::Combo("font-combo", &font_current, fonts, IM_ARRAYSIZE(fonts));
                if (old_font_current != font_current)
                {
                    old_font_current = font_current;
                }
            }

            ImGui::End();
        }

        // 4. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
        if (this->show_demo_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGui::PopFont();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(this->main_window);
        glfwGetFramebufferSize(this->main_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(this->main_window);
        glfwSwapBuffers(this->main_window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->main_window);
    glfwTerminate();

    return 0;
}

int Demo::play_demo_glfw_glad() {

//    float input_vertices[] = {
//            -0.5f, -0.5f, 0.0f, // left
//            0.5f, -0.5f, 0.0f, // right
//            0.0f,  0.5f, 0.0f  // top
//    };
    float input_vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.5f, 0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f  // top
    };

    if (this->init_glfw(3, 3)) {
        std::cout << "Failed on initializing GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    this->set_context_window(this->main_window);
    this->set_vsync(1);     // 0: vsync-off, 1: vsync-on

    if (this->init_glad()){
        std:: cout << "Failed on initializing GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    this->set_viewport(0, 0);

    // handle user's resizing of the window
    glfwSetFramebufferSizeCallback(this->main_window, this->glfw_framebuffer_size_callback);

    // shaders
    unsigned int shaderProgram, vertexShader, fragmentShader;
    this->set_shaders(shaderProgram,
                      vertexShader,
                      "../sources/shaders/shader.vs",
                      fragmentShader,
                      "../sources/shaders/fragment.vs");


    // buffer, vao, vbo
    this->set_buffers(input_vertices, sizeof(input_vertices));

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // engine
    while (!glfwWindowShouldClose(this->main_window)){
        // process key input
        this->process_input();

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // everything falls under glUserProgram will impacted by the shader programs
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // before finishing current frame
        glfwSwapBuffers(this->main_window);
        glfwPollEvents();
    }

    // termination and cleaning
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return EXIT_SUCCESS;
}

