// DEMO 4 -- ROTATING CUBE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
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

    // Call glViewport when window is resized
    glfwSetWindowSizeCallback(window,[](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    // Cube vertex locations / texture coordinates
    /* Format:
        Position      Texture coords
        x,y,z,        u,v
    */
    float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		- 0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

    uint32_t va, vb;
    glGenBuffers(1, &va);
    glBindVertexArray(va);

    // Setup vertex buffer
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float))); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture coordinates
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindVertexArray(va);

    Shader shader("src/demo4/vertexshader.glsl", "src/demo4/fragmentshader.glsl");
    shader.Use();

    glEnable(GL_DEPTH_TEST);

    // MVP matrices
    glm::mat4 model;
    glm::vec3 cameraPos(0.0f, 0.0f, 2.3f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), -1.0f * cameraPos);
    view = glm::rotate(view, glm::radians(45.0f),glm::vec3(1.0f,0.0f,0.0f));
    glm::mat4 projection;
	projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

    // Get MVP uniform locations
    uint32_t ModelLoc = glGetUniformLocation(shader.GetID(), "Model");
    uint32_t ViewLoc = glGetUniformLocation(shader.GetID(), "View");
    uint32_t ProjectionLoc = glGetUniformLocation(shader.GetID(), "Projection");
    
    // Set VP uniforms
    glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Rotation of cube in scene
    float rot = 0.0f;

    // Load texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("content/checker.jpg", &width, &height, &nrChannels, 0);

    // Create OpenGL texture and load the data into it
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rotate cube and update model matrix
        rot += 0.1f;
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f,1.0f,0.0f));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}