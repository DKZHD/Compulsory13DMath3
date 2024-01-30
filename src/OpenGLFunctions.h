#pragma once
#include "glad/glad.h"
#include <vector>

namespace GLFunctions
{
	template <typename T>
	void BindBufferVector(GLenum type,GLuint buffer_object, std::vector<T> object_vector, GLenum draw_type)
	{
		glBindBuffer(type, buffer_object);
		glBufferData(type, object_vector.size() * sizeof(T), object_vector.data(), draw_type);
	}
	inline void BindBufferFloat(GLenum type, GLuint buffer_object, const GLfloat* float_array,GLenum draw_type)
	{
		glBindBuffer(type, buffer_object);
		glBufferData(type, sizeof(float_array), float_array, draw_type);
	}
	GLFWwindow* CreateWindowAndMakeCurrent(int width, int height, const char* WindowName)
	{
		GLFWwindow* ThisWindow = glfwCreateWindow(width, height, WindowName, nullptr, nullptr);
		if(!ThisWindow)
		{
			glfwTerminate();
			return nullptr;
		}
		glfwMakeContextCurrent(ThisWindow);
		return ThisWindow;
	}
	void LoadGlad()
	{
		int width, height;
		glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
		glViewport(0, 0, width, height);
	}
	
	void ActivateVertexAttribPtr(GLint index,GLint size, GLenum type, GLboolean normalized,GLsizei stride, GLint start)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, (void*)(start * sizeof(float)));
		glEnableVertexAttribArray(index);
	}

	GLFWwindow* InitWindow(int width, int height, const char* window_name)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = CreateWindowAndMakeCurrent(width, height, window_name);
		LoadGlad();
		return window;
	}

}
