#include "Texture.h"

Texture::Texture() : ID(0)
{
}

void Texture::Create(std::string texturePath)
{
	// Set active texture unit
	glActiveTexture(GL_TEXTURE0 + ID);
	// Generate gl texture
	glGenTextures(1, &mHandle);

	// Load texture
	auto texData = Resource::ReadImageFile(texturePath);

	// Set image format based on number of colour channels
	GLenum format;
	switch (texData.channelCount)
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
	glTexImage2D(GL_TEXTURE_2D, 0, format, texData.width, texData.height, 0, format, GL_UNSIGNED_BYTE, texData.data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Free data
	Resource::FreeImage(texData.data);
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