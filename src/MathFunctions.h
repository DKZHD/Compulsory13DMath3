#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

struct VertexPoint
{
	float x;
	float y;
	float z;
	glm::vec3 Color = glm::vec3(1.f, 0.f, 0.f);
	VertexPoint(){}
	VertexPoint(float x, float y, float z, float r, float g, float b) : x(x), y(y), z(z), Color(r, g, b){}
};

struct Calculation
{
	double Derivative(double x)
	{
		return 5 * (std::pow(cos(x), 4)) * -sin(x);
	}
	std::vector<VertexPoint> PointsInGraph(float starting_point, float stopping_point, int steps)
	{
		float increment = (stopping_point - starting_point) / steps;
		std::ofstream FileOut;
		std::string Name("Task1-3.txt");
		FileOut.open(Name);
		FileOut << "Amount of Points: " << steps << "\n";
		FileOut << std::fixed << std::setprecision(4);
		std::vector<VertexPoint> VectorToReturn;
		for (float i = starting_point; i < stopping_point; i+=increment)
		{
			VertexPoint temp;
			temp.x =(i)/10;
			temp.y = std::pow(cos(i), 5.f) / 10;
			temp.z = 0;
			if(!VectorToReturn.empty())
			{
				if (Derivative(i)>=0.f)
				{
					temp.Color = glm::vec3(0.f, 1.f, 0.f);
				}
			}
			
			FileOut << "The derivative is = " << Derivative(i) << "\n";
			FileOut << temp.x << ", " << temp.y << ", " << temp.z << ", " << temp.Color.x << ", " << temp.Color.y << ", " << temp.Color.z << "\n";
			VectorToReturn.push_back(temp);
		}
		FileOut.close();
		return VectorToReturn;
	}
	std::vector<VertexPoint> SpiralPoints(float Radius)
	{
		std::ofstream FileOut;
		std::string Name("Spiral.txt");
		FileOut.open(Name);
		FileOut << "Amount of Points: " << Radius * 10 << "\n";
		FileOut << std::fixed << std::setprecision(4);
		std::vector<VertexPoint> VectorToReturn;
		for (float i = 0; i < Radius; i+=0.1f)
		{
			VertexPoint temp;
			temp.x = i * cos(i / 3.141592653589) * 0.005;
			temp.y = i * 0.01f-1.f;
			temp.z = i * sin(i / 3.141592653589) * 0.005;
			
			FileOut << temp.x << ", " << temp.y << ", " << temp.z << ", " << temp.Color.x << ", " << temp.Color.y << ", " << temp.Color.z << "\n";
			VectorToReturn.push_back(temp);
		}
		FileOut.close();
		return VectorToReturn;
	}
	std::vector<VertexPoint> PointsOfTwoVariableFunction(float starting_point,float stopping_point)
	{
		std::ofstream FileOut;
		std::string Name("Task3.txt");
		FileOut.open(Name);
		FileOut << std::fixed << std::setprecision(4);
		std::vector<VertexPoint> VectorToReturn;
		for (float i = starting_point; i < stopping_point; i += 0.01f)
		{
			VertexPoint temp;
			temp.x = (i*i*i)/100;
			temp.y = (i*5)/100;
			temp.z = (std::pow(temp.x, 2.f) * temp.y)/100;
			FileOut << temp.x << ", " << temp.y << ", " << temp.z << ", " << temp.Color.x << ", " << temp.Color.y << ", " << temp.Color.z << "\n";
			VectorToReturn.push_back(temp);
		}
		FileOut.close();
		return VectorToReturn;
	}
	std::vector<VertexPoint> GenerateFromFile()
	{
		std::vector<VertexPoint> VectorToReturn;
		std::ifstream InFile;
		std::string Name("Test.txt");
		InFile.open(Name);
		std::string CurrentLine;
		bool IsFirstLine = true;
		while (std::getline(InFile,CurrentLine))
		{
			if(IsFirstLine)
			{
				IsFirstLine = false;
				continue;
			}
			std::stringstream ss(CurrentLine);
			char Comma[3] = ", ";
			float x, y, z, r, g, b;
			ss >> x >> Comma >> y >> Comma >> z >> Comma >> r >> Comma >> g >> Comma >> b;
			VectorToReturn.emplace_back(x, y, z, r, g, b);
		}
		InFile.close();
		return VectorToReturn;
	}

};
