#include <GLFW/glfw3.h>
#pragma once
class simpleRenderer
{
	public:
		void mainFunc();
	private:
		void processInput(GLFWwindow* window);
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

