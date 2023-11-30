#pragma once

#include <string>
#include "glm.hpp"

class Texture
{
public:
	Texture();

	void LoadFromFiles(std::string texturePath);
	void Use();

	// Texture handle
	unsigned int ID;
private:

};