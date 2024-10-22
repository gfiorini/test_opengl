mkdir dependencies
cd dependencies
git submodule add https://github.com/Perlmint/glew-cmake.git glew
cd glew
git submodule set-branch  -b  glew-cmake-release .
cd ..
git submodule add https://github.com/glfw/glfw.git 
git checkout 3.4