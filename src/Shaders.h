#pragma once
#include "glad/glad.h"

namespace Shader
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 Color;\n"
		"out vec3 VertexColor;\n"
		"	void main()"
		"{"
		"gl_Position = vec4(aPos, 1.0);\n"
		"VertexColor = Color;\n"
		"};\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec3 FragColor;\n"
		"in vec3 VertexColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec3(VertexColor);\n"
		"}\0";

	inline GLuint CreateVertexShader()
	{
		GLuint NewShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(NewShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(NewShader);
		return NewShader;
	}
	inline GLuint CreateFragmentShader()
	{
		
		GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(FragShader);
		return FragShader;
	}
	inline GLuint CreateShadersAndSetupProgram()
	{
		GLuint Program = glCreateProgram();
		GLuint VertShader = CreateVertexShader();
		GLuint FragShader = CreateFragmentShader();
		glAttachShader(Program, VertShader);
		glAttachShader(Program, FragShader);
		glLinkProgram(Program);
		glDeleteShader(VertShader);
		glDeleteShader(FragShader);
		return Program;
	}
}
