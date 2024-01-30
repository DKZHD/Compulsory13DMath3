#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "MathFunctions.h"
#include "Shaders.h"
#include "OpenGLFunctions.h"


void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	GLFWwindow* CurrentWindow = GLFunctions::InitWindow(1024,720, "Hello Window");
	GLuint shader_program = Shader::CreateShadersAndSetupProgram();
	glfwSetFramebufferSizeCallback(CurrentWindow, framebuffer_size_callback);
	glfwSetKeyCallback(CurrentWindow, processInput);

	Calculation CurrentCalculations;
	//const std::vector<VertexPoint> PointsGenerated = CurrentCalculations.PointsInGraph(-10.f,10.f,100);
	const std::vector<VertexPoint> PointsGenerated = CurrentCalculations.SpiralPoints(360.f);
	//const std::vector<VertexPoint> PointsGenerated = CurrentCalculations.GenerateFromFile();
	//const std::vector<VertexPoint> PointsGenerated = CurrentCalculations.PointsOfTwoVariableFunction(-100.f,100.f);
	
	std::vector<unsigned int> indices;
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	GLFunctions::BindBufferVector(GL_ARRAY_BUFFER, VBO, PointsGenerated, GL_STATIC_DRAW);
	GLFunctions::BindBufferVector(GL_ELEMENT_ARRAY_BUFFER, EBO, indices, GL_STATIC_DRAW);
	GLFunctions::ActivateVertexAttribPtr(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPoint), NULL);
	GLFunctions::ActivateVertexAttribPtr(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPoint), 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glBindVertexArray(1);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(CurrentWindow);

	while (!glfwWindowShouldClose(CurrentWindow))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, PointsGenerated.size());

		glfwSwapBuffers(CurrentWindow);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);

	return 0;
}

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static bool IsPressed = false;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}
	if (glfwGetKey(window, key) == GLFW_PRESS && glfwGetKeyName(key,scancode))
	{
		std::cout << "You Pressed " << glfwGetKeyName(key,scancode) <<"\n";
	}
	if(glfwGetKey(window,key)==GLFW_RELEASE && glfwGetKeyName(key, scancode))
	{
		std::cout << "You Released " << glfwGetKeyName(key, scancode) << "\n";
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}