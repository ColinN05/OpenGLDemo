ECHO OFF
cls
g++ main.cpp -I glew/include -I glfw/include -Lglew -Lglfw -lglew32s -lglfw3 -lopengl32 -lgdi32 -o DemoApp
if %ERRORLEVEL% == 0 DemoApp.exe else PAUSE