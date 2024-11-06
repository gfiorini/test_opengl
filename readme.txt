Build instructions:

clone with:

    git clone https://github.com/gfiorini/test_opengl.git

then update submodules with:

    git submodule update --init --recursive

the project use cmake as build system

On Linux you must have installed openGL development libs:

    sudo apt install libgl1-mesa-dev

and to build glfw (see https://www.glfw.org/docs/latest/compile.html) you must have installed the following libs:

    sudo apt install libwayland-dev libxkbcommon-dev xorg-dev


On Windows build with your preferred IDE/toolchain and you're done (tested with Visual Studio and CLion)

----------------------------------------------------------------------------------------------------------------

submodule glew, glfw, glm, imgui first initalization was made with:

mkdir dependencies
cd dependencies
git submodule add https://github.com/Perlmint/glew-cmake.git glew
cd ..
git submodule add https://github.com/glfw/glfw.git 
git checkout 3.4
cd ..
git submodule add https://github.com/g-truc/glm.git glm
cd glm
git checkout 1.0.1
cd..
git submodule add https://github.com/ocornut/imgui.git imgui
cd imgui
git checkout v1.91.4


