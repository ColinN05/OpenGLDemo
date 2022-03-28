ECHO OFF
cls

g++ src/demo5/**.cpp src/Shader.cpp src/stb_image.cpp -I glm/include -I src -I glew/include -I glfw/include -Lglew -Lglfw -lglew32s -lglfw3 -lopengl32 -lgdi32 -o demo5
if NOT %ERRORLEVEL% == 0 PAUSE