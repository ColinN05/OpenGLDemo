ECHO OFF
cls

g++ src/demo2/**.cpp src/Shader.cpp -I src -I glew/include -I glfw/include -Lglew -Lglfw -lglew32s -lglfw3 -lopengl32 -lgdi32 -o demo2
if NOT %ERRORLEVEL% == 0 PAUSE