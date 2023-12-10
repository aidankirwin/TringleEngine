#include "Shader.h"

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

    vertCode = Resource::ReadTextFile(vertPath);
    fragCode = Resource::ReadTextFile(fragPath);
    // TODO: add optional geometry shader setup

    // Test code, output shader code
    Log::DebugMsg("Path to vertex shader: " + vertPath);
    Log::DebugMsg("Vertex shader code: " + vertCode);

    Log::DebugMsg("Path to fragment shader: " + fragPath);
    Log::DebugMsg("Fragment shader code: " + fragCode);


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
    Error::ShaderError("VERTEX", mVertex);

    // Fragment Shader
    mFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragment, 1, &fShaderCode, NULL);
    glCompileShader(mFragment);
    Error::ShaderError("FRAGMENT", mFragment);

    /*
    * ---- 3. Link Shaders ----
    */

    mHandle = glCreateProgram();
    glAttachShader(mHandle, mVertex);
    glAttachShader(mHandle, mFragment);
    glLinkProgram(mHandle);
    Error::ShaderError("PROGRAM", mHandle);

    // Can delete these once their linked
    glDeleteShader(mVertex);
    glDeleteShader(mFragment);

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
        int loc = glGetUniformLocation(mHandle, name);

        std::string strName(name, length);
        mUniformLocations.insert(std::make_pair(strName, loc));

        Log::DebugMsg("Uniform name: " + strName + '\n' + "Uniform location: " + std::to_string(loc));
    }

    // Attributes
    glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTES, &count);

    for (int i = 0; i < count; i++)
    {
        glGetActiveAttrib(mHandle, (GLuint)i, bufSize, &length, &size, &type, name);
        int loc = glGetAttribLocation(mHandle, name);

        std::string strName(name, length);
        mAttribLocations.insert(std::make_pair(strName, loc));

         Log::DebugMsg("Attribute name: " + strName + '\n' + "Attribute location: " + std::to_string(loc));
    }

    Error::GLError();
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