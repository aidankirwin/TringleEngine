#pragma once

#include <vector>
#include "glm.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
};

struct Transform
{

};

struct Mesh
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    unsigned int VAO, VBO, EBO;
};