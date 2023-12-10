#pragma once

#include <string>
#include <iostream>

#include "glad.h"

class Error
{
public:
    static void ErrorMsg(std::string msg)
    {
        std::cout << "[ERROR] " << msg << '\n';
    }
    
    static void GLError()
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cout << "[ERROR] "<< err << '\n';
            exit(-1);
        }
    }
    
    static void ShaderError(std::string type, int ID)
    {
        int success;
        char infoLog[1024];

        if (type == "PROGRAM") 
        {
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(ID, 512, NULL, infoLog);
                std::cout << "[ERROR] SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
                exit(-1);
            }
        }
        else if(type == "FRAGMENT") 
        {
            glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(ID, 512, NULL, infoLog);
                std::cout << "[ERROR] SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << '\n';
                exit(-1);
            }
        }
        else if (type == "VERTEX")
        {
            glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(ID, 512, NULL, infoLog);
                std::cout << "[ERROR] SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << '\n';
                exit(-1);
            }
        }
        else
        {
            exit(-1);
        }
    }
};

class Log
{
public: 
    void WriteToLog(std::string msg)
    {
        // TODO
    }

    static void DebugMsg(std::string msg)
    {
        std::cout << "[DEBUG] " << msg << '\n';
    }

private:
    std::string LogMsg;
};
