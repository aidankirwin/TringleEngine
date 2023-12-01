#pragma once

#include <vector>
#include <string>
#include "glm.hpp"
#include "Shader.h"
#include "gtc/matrix_transform.hpp"

// temp
#include "ext.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoord;
};

struct Transform
{

};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Initialize();
    void Draw(Shader shader);
private:
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    unsigned int mVAO, mVBO, mEBO;

    void ExitOnGLError();
};