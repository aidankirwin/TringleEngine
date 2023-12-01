#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() : ID(0)
{
}

void Texture::LoadFromFiles(std::string texturePath)
{
	// stbi loads images with y=0.0 at the top but OpenGL
	// expects it to be the bottom
	stbi_set_flip_vertically_on_load(true);

	// Set active texture unit
	glActiveTexture(GL_TEXTURE0 + ID);
	// Generate gl texture
	glGenTextures(1, &mHandle);

	// Load the texture
	int width, height, channelCount;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channelCount, 0);
	// Error handling
	if (!data)
	{
		std::cout << "TEXTURE FAILED TO LOAD AT PATH: " << texturePath << '\n';
	}

	// Set image format based on number of colour channels
	GLenum format;
	switch (channelCount)
	{
		case(1):
			format = GL_RED;
		case(4):
			format = GL_RGBA;
		default:
			format = GL_RGB;
	}

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, mHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
}

void Texture::Use()
{
	// Set active texture unit and bind
	glActiveTexture(GL_TEXTURE0 + ID);
	glBindTexture(GL_TEXTURE_2D, mHandle);
}

void Texture::SetID(unsigned int id)
{
	ID = id;
}