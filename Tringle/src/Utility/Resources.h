#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Log.h"

class Resource
{
public:
    static std::string ReadTextFile(const std::string& filePath);

    struct ImageData
    {
        unsigned char* data;
        int width, height, channelCount;
    };

    static ImageData ReadImageFile(std::string filePath);
    static void FreeImage(unsigned char* data);
};