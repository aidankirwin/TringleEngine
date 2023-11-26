#pragma once

#include <vector>
#include <map>
#include <string>
#include "glm.hpp"

class Shader
{
public:
	Shader(std::string vertPath, std::string fragPath);
	Shader Use();
	int GetAttribLocation(std::string attribName);


	GLuint Handle;

private:
	void CompileShader(int shader);
	void LinkProgram(int program);

	std::map<std::string, int> mUniformLocations;
};