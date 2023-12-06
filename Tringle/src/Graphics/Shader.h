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
	Shader();

	// Creates a shader program given a vertex and fragment shader file
	void Create(const std::string& vertPath, const std::string& fragPath);

	/*
	* Makes this shader the active shader in the app
	* Returns this shader object
	*/
	void Use();

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

	// Uniform setters
	// Must call Shader::Use() before calling these
	void SetMat4(std::string name, glm::mat4& data);
	void SetVec2(std::string name, glm::vec2& data);
	void SetVec3(std::string name, glm::vec3& data);

	void SetInt(std::string name, int data);
	void SetFloat(std::string name, float data);

	void DeleteShader();

	// Shader handle
	unsigned int mHandle;
private:

	// Error handling
	void Error(std::string type);
	std::string LoadFile(const std::string& filePath);

	// Vertex and fragment shader IDs
	unsigned int mVertex, mFragment;

	// Uniform and attribute maps
	// Can access this data through GL calls but cleaner to store here
	std::map<std::string, int> mUniformLocations;
	std::map<std::string, int> mAttribLocations;
};