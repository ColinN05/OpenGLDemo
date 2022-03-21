#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void Use();
	unsigned int m_ID;
};

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::ifstream vertexSourceFile;
	vertexSourceFile.open(vertexPath);
	std::string vertexSource;
	std::string line;

	if (!vertexSourceFile.is_open())
	{
		std::cout << "COULD NOT OPEN VERTEX SHADER SOURCE FILE!\n";
	}

	while (getline(vertexSourceFile, line))
	{
		vertexSource += line + '\n';
	}
	const char* vertexChar = vertexSource.c_str();
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexChar, NULL);
	glCompileShader(vertexShader);

	std::ifstream fragmentSourceFile(fragmentPath);
	std::string fragmentSource;
	while (getline(fragmentSourceFile, line))
	{
		fragmentSource += line + '\n';
	}
	const char* fragChar = fragmentSource.c_str();

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragChar, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	m_ID = shaderProgram;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER PROGRAM LINKING FAILED:\n" << infoLog << '\n';
	}
}

void Shader::Use()
{
	glUseProgram(m_ID);
}

int main(void)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create GLFW window
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

    float vertices[] = 
    {
        // Position     // Color
        0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
        1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
        0.0f, 1.0f,     0.0f, 0.0f, 1.0f
    };

    uint32_t indices[] = 
    {
        0, 1, 2
    };

    uint32_t va, vb, eb;
    glGenBuffers(1, &va);
    glBindVertexArray(va);

    // Setup vertex buffer
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))); // Color attribute
    glEnableVertexAttribArray(1);

    // Setup index buffer
    glGenBuffers(1, &eb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    glBindVertexArray(va);

    Shader shader("vertexshader.glsl", "fragmentshader.glsl");
    shader.Use();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}