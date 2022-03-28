// DEMO 5 -- SHADOWMAPPING
/*
WIP -- 
    Directional lighting works, but shadowmap doesn't
*/
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
        Position      Normals       Texture coords
        x,y,z,        a,b,c         u,v
    */
    float cubeVertices[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

    uint32_t cube_va, cube_vb;
    glGenVertexArrays(1, &cube_va);
    glBindVertexArray(cube_va);

    // Setup vertex buffer
    glGenBuffers(1, &cube_vb);
    glBindBuffer(GL_ARRAY_BUFFER,cube_vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float))); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture coordinates
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    float plane_vertices[] = 
    {
        // Positions        // Normals             // Tex coords
        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,      0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,      1.0f, 0.0f,
        1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,      1.0f, 1.0f,

        1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,      1.0f, 1.0f,
        0.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,      0.0f, 0.0f
    };

    uint32_t plane_va, plane_vb;
    glGenVertexArrays(1, &plane_va);
    glBindVertexArray(plane_va);

    glGenBuffers(1, &plane_vb);
    glBindBuffer(GL_VERTEX_ARRAY, plane_vb);
    glBufferData(GL_VERTEX_ARRAY, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float))); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture coordinates
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    Shader shader("src/demo5/vertexshader.glsl", "src/demo5/fragmentshader.glsl");
    shader.Use();

    Shader depthmap_shader("src/demo5/depthmapvertexshader.glsl", "src/demo5/depthmapfragmentshader.glsl");

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

    // Rotation of cube in scene
    float rot = 0.0f;

    // Load cube texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("content/checker.png", &width, &height, &nrChannels, 0);

    // Create OpenGL texture and load the data into it
    uint32_t cube_texture;
    glGenTextures(1, &cube_texture);
    glBindTexture(GL_TEXTURE_2D, cube_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    // Load plane texture
    data = stbi_load("content/wood.png", &width, &height, &nrChannels, 0);

    // Create OpenGL texture and load the data into it
    uint32_t plane_texture;
    glGenTextures(1, &plane_texture);
    glBindTexture(GL_TEXTURE_2D, plane_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    // Directional light
    glm::vec3 light_direction(1.0f, -0.5f, -1.0f);
    uint32_t LightDirectionLoc = glGetUniformLocation(shader.GetID(), "LightDirection");
    glUniform3fv(LightDirectionLoc, 1, glm::value_ptr(light_direction));

    // Create depth framebuffer
    uint32_t depth_fb;
    glGenFramebuffers(1, &depth_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_fb);

    // Create depth map
    uint32_t depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 640, 640, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Attach depth map to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

    //
    uint32_t LightSpaceMatrixLoc = glGetUniformLocation(depthmap_shader.GetID(), "LightSpaceMatrix");
    uint32_t depthModelLoc = glGetUniformLocation(depthmap_shader.GetID(), "Model");

    uint32_t fb_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fb_status == GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer status complete\n";
    }
    else
    {
        std::cout << "Framebuffer status not complete\n";
    }
    std::cout << fb_status << '\n';

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // FIRST: Render scene to depth framebuffer from perspective of directional light //////////////////////////////////////////////////////////
        glBindFramebuffer(GL_FRAMEBUFFER, depth_fb);
        depthmap_shader.Use();

        view = glm::lookAt(-1000.0f * light_direction, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
        projection = glm::ortho(-12.0f, 12.0f, -12.0f, 12.0f);
        glm::mat4 lightSpaceMatrix = projection * view;
        glUniform2fv(LightSpaceMatrixLoc, 1, glm::value_ptr(lightSpaceMatrix));

        // Plane model matrix
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-2.0f,0.0f));
        model = glm::scale(model, glm::vec3(12.0f,1.0f,12.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));
        glUniformMatrix4fv(depthModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Draw plane
        glBindTexture(GL_TEXTURE_2D, plane_texture);
        glBindVertexArray(plane_va);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Rotate cube and update model matrix
        rot += 0.1f;
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f,1.0f,0.0f));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Draw the cube
        glBindTexture(GL_TEXTURE_2D, cube_texture);
        glBindVertexArray(cube_va);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //SECOND: Render scene to screen /////////////////////////////////////////////////////////////////////////////////////
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        shader.Use();

        uint32_t DepthMapLoc = glGetUniformLocation(shader.GetID(), "DepthMap");
        glUniform1i(DepthMapLoc, 1);
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glActiveTexture(GL_TEXTURE0);
        //glClear(GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::translate(glm::mat4(1.0f), -1.0f * cameraPos);
        view = glm::rotate(view, glm::radians(45.0f),glm::vec3(1.0f,0.0f,0.0f));
	    projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Plane model matrix
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-2.0f,0.0f));
        model = glm::scale(model, glm::vec3(12.0f,1.0f,12.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Draw plane
        glBindTexture(GL_TEXTURE_2D, plane_texture);
        glBindVertexArray(plane_va);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Rotate cube and update model matrix
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f,1.0f,0.0f));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Draw the cube
        glBindTexture(GL_TEXTURE_2D, cube_texture);
        glBindVertexArray(cube_va);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}