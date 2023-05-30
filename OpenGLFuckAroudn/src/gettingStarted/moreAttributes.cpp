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

int main()
{
	GLFWwindow* window = initOpenGlWithSizeAndTitle(800, 600, "More Attributes! Glowy LGBTQ+ triangle!");

	const char* shaderPath = "C:/Users/infia/source/repos/OpenGLFuckAroudn/OpenGLFuckAroudn/src/gettingStarted/shaders";

	char vertexShaderPath[256];
	strcpy_s(vertexShaderPath, shaderPath);
	strcat_s(vertexShaderPath, "/moreAttributes.vert");

	char fragmentShaderPath[256];
	strcpy_s(fragmentShaderPath, shaderPath);
	strcat_s(fragmentShaderPath, "/moreAttributes.frag");

	Shader shaderProgram = Shader(vertexShaderPath, fragmentShaderPath);

	shaderProgram.use();

	float verticesAndColor[]
	{
		// positions	   // colors
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
	   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
	};

	unsigned int VAO;
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAndColor), verticesAndColor, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}