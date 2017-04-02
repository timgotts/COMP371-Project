@echo off

mkdir build
pushd build

set CompilerFlags=-FC -Zi /W1

set Files=..\main.cpp ..\Cube.cpp ..\Renderable.cpp ..\Terrain.cpp ..\Skybox.cpp  

set Libs=user32.lib gdi32.lib opengl32.lib ..\LIBS\glfw3.lib msvcrt.lib msvcmrt.lib LIBCMT.lib Shell32.lib ..\LIBS\glew32s.lib ..\LIBS\SOIL.lib vcruntimed.lib ucrtd.lib


cl %Files% %CompilerFlags% %libs% /EHsc /I..\INCLUDE  


popd
