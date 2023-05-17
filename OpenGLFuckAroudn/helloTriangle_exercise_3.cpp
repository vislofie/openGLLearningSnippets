#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* fragmentShaderSourceBlue = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";

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

	GLFWwindow* window = glfwCreateWindow(800, 600, "third exercise", NULL, NULL);

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

	// create and compile shaders

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int yellowFragmentShader;
	yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(yellowFragmentShader, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(yellowFragmentShader);

	unsigned int blueFragmentShader;
	blueFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(blueFragmentShader, 1, &fragmentShaderSourceBlue, NULL);
	glCompileShader(blueFragmentShader);

	// create and link shader programs

	unsigned int yellowProgram, blueProgram;

	yellowProgram = glCreateProgram();

	glAttachShader(yellowProgram, vertexShader);
	glAttachShader(yellowProgram, yellowFragmentShader);
	glLinkProgram(yellowProgram);


	blueProgram = glCreateProgram();

	glAttachShader(blueProgram, vertexShader);
	glAttachShader(blueProgram, blueFragmentShader);
	glLinkProgram(blueProgram);

	// delete shaders after use in linking
	glDeleteShader(vertexShader);
	glDeleteShader(blueFragmentShader);
	glDeleteShader(yellowFragmentShader);



	// ---triangles---

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

	// creating VAOs and VBOs

	unsigned int firstVAO, secondVAO;
	unsigned int firstVBO, secondVBO;

	// first VAO + VBO
	glGenVertexArrays(1, &firstVAO);
	glGenBuffers(1, &firstVBO);

	glBindVertexArray(firstVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, firstVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), verticesFirstTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second VAO + VBO
	glGenVertexArrays(1, &secondVAO);
	glGenBuffers(1, &secondVBO);

	glBindVertexArray(secondVAO);

	glBindBuffer(GL_ARRAY_BUFFER, secondVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSecondTriangle), verticesSecondTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(yellowProgram);

		glBindVertexArray(firstVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(blueProgram);

		glBindVertexArray(secondVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &firstVAO);
	glDeleteVertexArrays(1, &secondVAO);

	glDeleteBuffers(1, &firstVBO);
	glDeleteBuffers(1, &secondVBO);
	glDeleteProgram(yellowProgram);
	glDeleteProgram(blueProgram);

	glfwTerminate();

	return 0;
}
