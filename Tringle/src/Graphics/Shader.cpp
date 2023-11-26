#include "Shader.h"

Shader::Shader(std::string vertPath, std::string fragPath)
{
    /*
    * ---- 1. Read Shader Files ----
    * Inputs:
    *   (a) vertPath: string path of vertex shader
    *   (b) fragPath: string path of fragment shader
    * Outputs:
    *   (a) vShaderCode: const char of vertex shader code
    *   (b) fShaderCode: const char of fragment shader code
    */

    std::string vertCode, fragCode;
    std::ifstream vShaderFile, fShaderFile;

    // Convert file paths from string to const char
    const char* vertPathChar = vertPath.c_str();
    const char* fragPathChar = fragPath.c_str();

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open the files
        vShaderFile.open(vertPathChar);
        fShaderFile.open(fragPathChar);

        // Read file
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Close the files
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream to string
        vertCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    }
    catch(std::ifstream::failure& error)
    {
        // TODO: Errors, logs, etc. should be wrapped and handled in a separate class
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << error.what() << '\n';
    }

    // Convert content string to const char
    const char* vShaderCode = vertCode.c_str();
    const char* fShaderCode = fragCode.c_str();

    /*
    * ---- 2. Compile Shader Code ----
    */
    unsigned int vertex, fragment;

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    Error("VERTEX");

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    Error("FRAGMENT");

    /*
    * ---- 3. Link Shaders ----
    */

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    Error("PROGRAM");

    /*
    * ---- 4. Fill Uniform and Attribute Maps ----
    */
}

Shader Shader::Use()
{

}

void Shader::SetInt(std::string name, int data)
{

}

void Shader::SetFloat(std::string name, float data)
{

}

void Shader::SetMat4(std::string name, glm::mat4 data)
{

}

void Shader::SetVec3(std::string name, glm::vec3 data)
{

}

void Shader::DeleteShader()
{

}

void Shader::Error(std::string type)
{

}