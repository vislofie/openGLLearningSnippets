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

GLFWwindow* initOpenGlWithSizeAndTitle(int width, int height, const char* title)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, title, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return window;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

void main()
{
	GLFWwindow* window = initOpenGlWithSizeAndTitle(800, 600, "Shaders exercise 2");

	const char* shaderPath = "C:/Users/infia/source/repos/OpenGLFuckAroudn/OpenGLFuckAroudn/src/gettingStarted/shaders";
	char vertexShaderPath[256];
	strcpy_s(vertexShaderPath, shaderPath);
	strcat_s(vertexShaderPath, "/shaders_exercise_2.vert");

	char fragmentShaderPath[256];
	strcpy_s(fragmentShaderPath, shaderPath);
	strcat_s(fragmentShaderPath, "/shaders_exercise_2.frag");

	Shader shaderProgram = Shader(vertexShaderPath, fragmentShaderPath);

	float vertices[] =
	{
		0.0f,  0.5f,  0.0f,	// top
	   -0.5f,  0.0f,  0.0f,	// left bottom
		0.5f,  0.0f,  0.0f  // right bottom
	};

	unsigned int VAO;
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);

		shaderProgram.setUniformFloat("horizontalOffset", 0.5f);
		shaderProgram.use();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}