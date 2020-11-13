# C/C++ Startup Template for IMGUI + GLFW

First, clone the repository including all the submodules:

`git clone https://github.com/yanuartadityan/imgui-glfw-glad-startup.git --recursive`

Then, build the *glad, opencv* and the rest of submodules, copy necessary includes of it and prepare the entire cmake toolchain:

`./INSTALL` if you are using Unix-based environment,`./INSTALL_MINGW` if you are using Windows 10.  

At the moment (2020/11/12), this project has been tested to run on all major environment (MacOS Catalina, Windows 10 on MinGW-x64 and Debian-based Linux).

Now, by default the Unix build chain used is set for **Unix Makefiles**, but feel free to change it to whatever environment you like, e.g. Xcode, Visual Studio, or even Ninja. Change the setting, obviously, in INSTALL script.

# Dependencies

* GLAD - OpenGL loader and wrapper
* GLFW - API for creating windows, contexts and handling input events
* Imgui - Graphical user interface, super awesome project
* OpenCV - The OpenCV that we know, yes :)
* GLM - GL mathematics library

This project is inspired from [https://github.com/urddru/imgui-glfw](https://github.com/urddru/imgui-glfw)



