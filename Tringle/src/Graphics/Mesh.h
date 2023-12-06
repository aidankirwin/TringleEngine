#pragma once

#include <vector>
#include <string>
#include "glm.hpp"
#include "Shader.h"
#include "Texture.h"
#include "gtc/matrix_transform.hpp"

// temp
#include "ext.hpp"

struct Vertex
{
    glm::vec3 Position;     // 12 bytes
    glm::vec2 TexCoord;     // 8 bytes
};

struct Transform
{
    glm::vec3 Position;
    glm::vec3 Scale;
    
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Initialize();
    void Draw(Shader& shader, Texture& texture, Transform transform);
    unsigned int VAO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
private:
    unsigned int mVBO, mEBO;

    void ExitOnGLError();
};