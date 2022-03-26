ECHO OFF
cls

g++ src/demo4/**.cpp src/Shader.cpp src/stb_image.cpp -I glm/include -I src -I glew/include -I glfw/include -Lglew -Lglfw -lglew32s -lglfw3 -lopengl32 -lgdi32 -o demo4
if NOT %ERRORLEVEL% == 0 PAUSE