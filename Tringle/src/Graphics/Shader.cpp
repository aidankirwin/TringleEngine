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

    // Uniforms
    GLint count;

    const GLsizei bufSize = 16; // maximum name length
    GLsizei length; // name length
    GLint size; // size of variable
    GLenum type; // type of variable (float, vec3, mat3, etc.)
    GLchar name[bufSize]; // variable name

    // Sets count to number of active uniforms
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);

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
        glGetActiveUniform(ID, (GLuint)i, bufSize, &length, &size, &type, name);
        
        std::string strName((char*)&name[0], length - 1);
        mUniformLocations.insert(std::make_pair(strName, i));

        std::cout << "Uniform name:" << strName << '\n' << "Uniform location:" << i << '\n';
    }
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


void Shader::SetVec2(std::string name, glm::vec2 data)
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