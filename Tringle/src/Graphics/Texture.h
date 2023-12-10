#pragma once

#include <string>
#include <iostream>
#include "glad.h"
#include "glm.hpp"

#include "Resources.h"

class Texture
{
public:
	Texture();

	void Create(std::string texturePath);
	void Use();

	// Texture unit ID, 0 by default
	unsigned int ID;
	void SetID(unsigned int id);

private:
	// Texture handle
	unsigned int mHandle;
};