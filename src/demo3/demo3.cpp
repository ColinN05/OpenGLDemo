// DEMO 1 -- ROTATING SQUARE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
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

    float vertices[] = 
    {
        // Position
        -0.5f, -0.5f,
         0.5f, -0.5f,
        -0.5f, 0.5f,
         0.5f, 0.5f
    };

    uint32_t indices[] = 
    {
        0, 1, 2,
        2, 1, 3
    };

    uint32_t va, vb, eb;
    glGenBuffers(1, &va);
    glBindVertexArray(va);

    // Setup vertex buffer
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float))); // Position attribute
    glEnableVertexAttribArray(0);

    // Setup index buffer
    glGenBuffers(1, &eb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    glBindVertexArray(va);

    Shader shader("src/demo3/vertexshader.glsl", "src/demo3/fragmentshader.glsl");
    shader.Use();

    float rot = 0.0f;
    unsigned int RotLoc = glGetUniformLocation(shader.GetID(), "Rot");

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUniform1f(RotLoc, rot); // Set square rotation uniform
        rot += 0.001f;
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}