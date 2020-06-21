# C/C++ Startup Template for IMGUI + GLFW

First, clone the repository including all the submodules:

`git clone --recurse-submodules https://github.com/yanuartadityan/imgui-glfw-glad-startup.git`

Then, build the *glad*, copy necessary includes of it and prepare the entire cmake toolchain:

`./INSTALL`

Now, by default the build chain used is for **Unix Makefiles**, but feel free to change it to whatever environment you like, e.g. Xcode, Visual Studio, or even Ninja. Change the setting, obviously, in INSTALL.

# Dependencies

* GLAD
* GLFW
* Imgui
* CMake

This project is inspired from [https://github.com/urddru/imgui-glfw](https://github.com/urddru/imgui-glfw)



