#include "Resources.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string Resource::ReadTextFile(const std::string& filePath)
{
    std::string result;
    std::ifstream in(filePath, std::ios::in | std::ios::binary);

    if(in)
    {
        in.seekg(0, std::ios::end);
        size_t size = in.tellg();
        if(size != -1)
        {
            result.resize(size);
            in.seekg(0, std::ios::beg);
            in.read(&result[0], size);
        }
        else
        {
            std::cout << "Could not read from file:" << filePath << '\n';
            exit(-1);
        }
    }
    else
    {
        std::cout << "Could not open file:" << filePath << '\n';
        exit(-1);
    }

    return result;
}

Resource::ImageData Resource::ReadImageFile(std::string filePath)
{
    // stbi loads images with y=0.0 at the top but OpenGL
    // expects it to be the bottom
    stbi_set_flip_vertically_on_load(true);


    // Load the texture
    int width, height, channelCount;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channelCount, 0);
    // Error handling
    if (!data)
    {
    Error::ErrorMsg("TEXTURE FAILED TO LOAD AT PATH: " + filePath);
    }

    return {data, width, height, channelCount};
}

void Resource::FreeImage(unsigned char* data)
{
    stbi_image_free(data);
}