#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "headers/ShaderBuilder.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create window!" << std::endl;

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// creating shader
	const char* shaderPath = "C:/Users/infia/source/repos/OpenGLFuckAroudn/OpenGLFuckAroudn/src/gettingStarted/shaders";
	char vertexShaderPath[256];
	strcpy_s(vertexShaderPath, shaderPath);
	strcat_s(vertexShaderPath, "/helloTriangle.vert");

	char fragmentShaderPath[256];
	strcpy_s(fragmentShaderPath, shaderPath);
	strcat_s(fragmentShaderPath, "/helloTriangle.frag");

	Shader simpleShader = Shader(vertexShaderPath, fragmentShaderPath);

	// triangles

	float verticesFirstTriangle[]
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	float verticesSecondTriangle[]
	{
		0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	
	unsigned int firstVAO, secondVAO;
	unsigned int firstVBO, secondVBO;

	// first VAO and VBO
	glGenVertexArrays(1, &firstVAO);
	glGenBuffers(1, &firstVBO);

	glBindVertexArray(firstVAO);

	glBindBuffer(GL_ARRAY_BUFFER, firstVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), verticesFirstTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second VAO and VBO
	glGenVertexArrays(1, &secondVAO);
	glGenBuffers(1, &secondVBO);

	glBindVertexArray(secondVBO);

	glBindBuffer(GL_ARRAY_BUFFER, secondVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSecondTriangle), verticesSecondTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		simpleShader.use();

		glBindVertexArray(firstVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(secondVBO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &firstVAO);
	glDeleteVertexArrays(1, &secondVAO);
	
	glDeleteBuffers(1, &firstVBO);
	glDeleteBuffers(1, &secondVBO);

	return 0;
}