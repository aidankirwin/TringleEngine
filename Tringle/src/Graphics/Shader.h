#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glm.hpp"
#include "glad.h"

class Shader
{
public:
	Shader(std::string vertPath, std::string fragPath);

	/*
	* Makes this shader the active shader in the app
	* Returns this shader object
	*/
	Shader Use();

	// Uniform and attribute functions

	/*
	* ---- 1. Standard Uniforms ----
	* While user may set additional uniforms if they choose
	* to make their own vert and frag shaders, these are
	* the required (default) uniforms:
	* 	(a) mat4 model
	*	(b) mat4 view
	*	(c) mat4 projection
	*	(d) sampler2D texture
	* The uniforms (a)-(c) are required for calculating
	* the gl_Position of a textured mesh, where (d) is the
	* applied texture.
	*
	* ---- 2. Standard Attributes ----
	* Similarly, user may set additional attributes in their
	* own shaders, but the default uniforms are:
	*	(a) layout(location = 0) in vec3 vertex
	*	(b) layout(location = 1) in vec2 uv
	*/

	// Required default uniform setters
	void SetMat4(std::string name, glm::mat4 data);
	void SetVec2(std::string name, glm::vec2 data);
	void SetVec3(std::string name, glm::vec3 data);

	// Additional uniform setters
	void SetInt(std::string name, int data);
	void SetFloat(std::string name, float data);

	void DeleteShader();

	// Shader handle
	unsigned int ID;

private:
	void Error(std::string type);

	std::map<std::string, int> mUniformLocations;
	std::map<std::string, int> mAttribLocations;
};

/*
---- Default Vertex Shader ----
#version 330 core
layout (location = 0) in vec3 aPos;         // model coords of a vertex
layout (location = 1) in vec2 aTexCoord;    // uv coords of corresponding texture

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
*/