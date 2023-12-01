#pragma once

#include <string>
#include <iostream>
#include "glad.h"
#include "glm.hpp"

class Texture
{
public:
	Texture();

	void LoadFromFiles(std::string texturePath);
	void Use();

	// Texture unit ID, 0 by default
	unsigned int ID;
	void SetID(unsigned int id);

private:
	// Texture handle
	unsigned int mHandle;
};