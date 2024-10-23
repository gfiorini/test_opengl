Build instructions:

the project use cmake as build system

On Linux you must have installed openGL development libs:

    sudo apt install libgl1-mesa-dev

and to build glfw (see https://www.glfw.org/docs/latest/compile.html) you must have installed the following libs:

    sudo apt install libwayland-dev libxkbcommon-dev xorg-dev


On Windows build with your preferred IDE/toolchain and you're done (tested with Visual Studio and CLion)

----------------------------------------------------------------------------------------------------------------

submodule glew and glfw first initalization was made with:

mkdir dependencies
cd dependencies
git submodule add https://github.com/Perlmint/glew-cmake.git glew
cd glew
git submodule set-branch -b glew-cmake-release .
cd ..
git submodule add https://github.com/glfw/glfw.git 
git checkout 3.4



