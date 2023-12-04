#include "Shader.h"

#include <unistd.h>

Shader::Shader()
{

}

void Shader::Create(const std::string& vertPath, const std::string& fragPath)
{
    /*
    * ---- 1. Read Shader Files ----
    * Inputs:
    *   (a) vertPath: path of vertex shader
    *   (b) fragPath: path of fragment shader
    * Outputs:
    *   (a) vShaderCode: const char of vertex shader code
    *   (b) fShaderCode: const char of fragment shader code
    */

    std::string vertCode, fragCode;
    
    // Test code, print working directory
    // Note that paths are relative to the working directory
    // Not the binary directory (where the executable is stored)
    char buffer[256];
    char* val = getcwd(buffer, sizeof(buffer));
    if(val)
    {
        std::cout << buffer << '\n';
    }

    vertCode = LoadFile(vertPath);
    fragCode = LoadFile(fragPath);
    // TODO: add optional geometry shader setup

    // Test code, output shader code
    std::cout << vertPath << '\n';
    std::cout << "vertex code: " << vertCode << '\n';

    std::cout << fragPath << '\n';
    std::cout << "frag code: " << fragCode << '\n';


    // Convert content string to const char
    const char* vShaderCode = vertCode.c_str();
    const char* fShaderCode = fragCode.c_str();

    /*
    * ---- 2. Compile Shader Code ----
    */

    // Vertex Shader
    mVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertex, 1, &vShaderCode, NULL);
    glCompileShader(mVertex);
    Error("VERTEX");

    // Fragment Shader
    mFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragment, 1, &fShaderCode, NULL);
    glCompileShader(mFragment);
    Error("FRAGMENT");

    /*
    * ---- 3. Link Shaders ----
    */

    mHandle = glCreateProgram();
    glAttachShader(mHandle, mVertex);
    glAttachShader(mHandle, mFragment);
    glLinkProgram(mHandle);
    Error("PROGRAM");

    int infoLength;
    char text[1000];
    glGetProgramInfoLog(mHandle, 1000, &infoLength, text);

    // Can delete these once their linked
    // Note that these vars are used in Shader::Error()
    // Might want to clean that up. No risk of memory leak just bad code
    glDeleteShader(mVertex);
    glDeleteShader(mFragment);

    if(infoLength > 0)
    {
        std::cout << "Shader" << '\n' << text << '\n';
    }

    /*
    * ---- 4. Fill Uniform and Attribute Maps ----
    */

    // Uniforms
    GLint count;

    const GLsizei bufSize = 16; // maximum name length
    GLsizei length; // name length
    GLint size; // size of variable
    GLenum type; // type of variable (float, vec3, mat3, etc.)
    GLchar name[bufSize]; // variable name

    // Sets count to number of active uniforms
    glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &count);

    std::cout << count << '\n';

    for (int i = 0; i < count; i++)
    {
        /*
        * void glGetActiveUniform(GLuint program,
 	    *   GLuint index,
 	    *   GLsizei bufSize,
 	    *   GLsizei *length,
 	    *   GLint *size,
 	    *   GLenum *type,
 	    *   GLchar *name);
        * 
        * program: specifies program object, equal to Shader::ID
        * index: index of the uniform variable to be quieried
        * bufSize: max number of characters OpenGL can write to the character buffer (name)
        * length: returns number of characters written by OpenGL to name
        * size: returns size of the uniform variable
        * type: returns data type of uniform variable
        * name: returns string containing name of variable
        */
        glGetActiveUniform(mHandle, (GLuint)i, bufSize, &length, &size, &type, name);
        
        std::string strName(name, length);
        mUniformLocations.insert(std::make_pair(strName, i));

        std::cout << "Uniform name:" << strName << '\n' << "Uniform location:" << i << '\n';
    }

    // Attributes
    glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTES, &count);

    std::cout << count << '\n';

    for (int i = 0; i < count; i++)
    {
        glGetActiveAttrib(mHandle, (GLuint)i, bufSize, &length, &size, &type, name);

        std::string strName(name, length);
        mAttribLocations.insert(std::make_pair(strName, i));

        std::cout << "Attribute name:" << strName << '\n' << "Attribute location:" << i << '\n';
    }
}

void Shader::Use()
{
    glUseProgram(mHandle);
}

void Shader::SetInt(std::string name, int data)
{
    glUniform1i(mUniformLocations[name], data);
}

void Shader::SetFloat(std::string name, float data)
{
    glUniform1f(mUniformLocations[name], data);
}

void Shader::SetMat4(std::string name, glm::mat4& data)
{
    /*
    * void glUniformMatrix4fv(GLint location,
 	*    GLsizei count,
 	*    GLboolean transpose,
 	*    const GLfloat *value);
    * 
    * location: uniform variable location
    * count: number of matrices that are to be modified, 1 unless matrix is array of matrices
    * transpose: specifies whether to transpose matrix as values are loaded in
    * value: pointer to an array of 'count' values
    */

    glUniformMatrix4fv(mUniformLocations[name], 1, GL_FALSE, &data[0][0]);
}


void Shader::SetVec2(std::string name, glm::vec2& data)
{
    glUniform2fv(mUniformLocations[name], 1, &data[0]);
}


void Shader::SetVec3(std::string name, glm::vec3& data)
{
    glUniform3fv(mUniformLocations[name], 1, &data[0]);
}

void Shader::DeleteShader()
{
    glDeleteProgram(mHandle);
}

void Shader::Error(std::string type)
{
    int success;
    char infoLog[1024];

    if (type == "PROGRAM") 
    {
        glGetProgramiv(mHandle, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(mHandle, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
            exit(-1);
        }
    }
    else if(type == "FRAGMENT") 
    {
        glGetShaderiv(mFragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(mFragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << '\n';
            exit(-1);
        }
    }
    else if (type == "VERTEX")
    {
        glGetShaderiv(mVertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(mVertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << '\n';
            exit(-1);
        }
    }
    else
    {
        exit(-1);
    }
}

std::string Shader::LoadFile(const std::string& filePath)
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