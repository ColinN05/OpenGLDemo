ECHO OFF
cls

g++ src/demo3/**.cpp src/Shader.cpp -I src -I glew/include -I glfw/include -Lglew -Lglfw -lglew32s -lglfw3 -lopengl32 -lgdi32 -o demo3
if NOT %ERRORLEVEL% == 0 PAUSE