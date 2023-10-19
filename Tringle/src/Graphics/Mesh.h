#pragma once

#include <vector>
#include "glm.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    glm::vec3 Normals;
};

struct Mesh
{
    int VAO;
    int VBO;
    std::vector<Vertex> Vertices;
};