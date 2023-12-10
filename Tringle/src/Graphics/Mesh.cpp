#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
    vertices(vertices), indices(indices)
{

}

void Mesh::Initialize()
{
    glGenVertexArrays(1, &VAO);

    Log::DebugMsg("Gen VAO");
    Error::GLError();

    glBindVertexArray(VAO);
    Log::DebugMsg("Bind VAO");
    Error::GLError();

    for (int i = 0; i < (vertices).size(); i++)
    {
        Log::DebugMsg(glm::to_string((vertices)[i].Position));
        Log::DebugMsg(glm::to_string((vertices)[i].TexCoord));
    }

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    Log::DebugMsg("Bind VBO");
    Error::GLError();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);      // Pass a pointer to the START of vertex array + the total size (in bytes) of the vertex array
    Log::DebugMsg("Pass VBO data");
    Error::GLError();

    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    Log::DebugMsg("Bind EBO");
    Error::GLError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    Log::DebugMsg("Pass EBO data");
    Error::GLError();

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);                                                                       // Enable location=0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);                          // 3 floats, entire thing is sizeof(vertex), but this is first 3 floats starting at 0 bytes offset
    Log::DebugMsg("Enable vertex attribute 0 and set size and offset");
    Error::GLError();
    // vertex texture coords
    glEnableVertexAttribArray(1);                                                                       // Enable location=1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord)); // 2 floats, entire thing is sizeof(vertex), but this is 2 floats after 12 bytes offset
    Log::DebugMsg("Enable vertex attribute 1 and set size and offset");
    Error::GLError();

    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader, Texture& texture, Transform transform)
{   
    // Set active shader program
    shader.Use();

    // Set model matrix
    glm::mat4 model(1.0f);                      // Init to identity matrix

    glm::vec3 pos = transform.Position;         // Get position vector
    glm::vec3 scale = transform.Scale;          // Get scale vector
    glm::vec3 axis = transform.Rotation.Axis;   // Get axis of rotation
    float angle = transform.Rotation.Angle;     // Get angle of rotation

    model = glm::scale(model, scale);           // Apply scale to model
    model = glm::translate(model, pos);         // Apply translate to model
    model = glm::rotate(model, angle, axis);    // Apply rotation to model

    shader.SetMat4("model", model);             // Pass model to shader

    // Set active shader and send to shader
    shader.SetInt("tex1", texture.ID);
    texture.Use();

    // Bind VAO and draw
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

    glActiveTexture(0);
    glBindVertexArray(0);
}