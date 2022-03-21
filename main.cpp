#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{

    if (!glfwInit())  //Initialize GLFW
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create GLFW window\

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Set OpenGL context

    // Initialize GLEW
    auto glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << glewGetErrorString(glewInitResult) << '\n';
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render here
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(1.0f, 0.0f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}