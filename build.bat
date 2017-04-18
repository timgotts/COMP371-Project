@echo off

mkdir build
pushd build

set CompilerFlags=-FC -Zi /W0

set Files=..\main.cpp ..\Cube.cpp ..\Seaweed.cpp  ..\Fish.cpp ..\Renderable.cpp ..\Terrain.cpp ..\TerrainGenerator.cpp  ..\Skybox.cpp ..\Config.cpp ..\Rock.cpp ..\Material.cpp ..\DirectionalLight.cpp ..\LightSource.cpp ..\PointLight.cpp ..\Spotlight.cpp ..\Light.cpp ..\GlowFish.cpp ..\Coral.cpp ..\Harpoon.cpp

set Libs=user32.lib gdi32.lib opengl32.lib ..\LIBS\glfw3.lib msvcrtd.lib msvcmrtd.lib LIBCMT.lib Shell32.lib ..\LIBS\glew32s.lib ..\LIBS\SOIL.lib 


cl %Files% %CompilerFlags% %libs% /EHsc /I..\INCLUDE /W0


popd
