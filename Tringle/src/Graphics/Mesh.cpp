#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
    vertices(vertices), indices(indices)
{

}

void Mesh::Initialize()
{
    std::cout << glGetString(GL_VERSION) << '\n';

    glGenVertexArrays(1, &VAO);
    std::cout << "Gen VAO" << '\n';
    ExitOnGLError();

    glBindVertexArray(VAO);
    std::cout << "Bind VAO" << '\n';
    ExitOnGLError();

    for (int i = 0; i < (vertices).size(); i++)
    {
        std::cout << glm::to_string((vertices)[i].Position) << '\n';
        std::cout << glm::to_string((vertices)[i].TexCoord) << '\n';
    }

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    std::cout << "Bind VBO" << '\n';
    ExitOnGLError();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);      // Pass a pointer to the START of vertex array + the total size (in bytes) of the vertex array
    std::cout << "Pass VBO data" << '\n';
    ExitOnGLError();

    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    std::cout << "Bind EBO" << '\n';
    ExitOnGLError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    std::cout << "Pass EBO data" << '\n';
    ExitOnGLError();

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);                                                                       // Enable location=0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);                          // 3 floats, entire thing is sizeof(vertex), but this is first 3 floats starting at 0 bytes offset
    std::cout << "Enable vertex attribute 0 and set size and offset" << '\n';
    ExitOnGLError();
    // vertex texture coords
    glEnableVertexAttribArray(1);                                                                       // Enable location=1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord)); // 2 floats, entire thing is sizeof(vertex), but this is 2 floats after 12 bytes offset
    std::cout << "Enable vertex attribute 1 and set size and offset" << '\n';
    ExitOnGLError();

    glBindVertexArray(0);
}

// For later, when passing shaders, pass &shader
// Can't work with a copy of our shader object
void Mesh::Draw(Shader& shader, Texture& texture, Transform transform)
{
    /*
    * Note for later:
    * Must call shader.SetInt("textureUniformName", texture.ID) before using texture
    * Need to test / research whether it is okay to call this before glActiveTexture()
    */
    // shader.Use();

    glm::mat4 model(1.0f);
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, -20.0f);
    glm::vec3 scale = glm::vec3(5, 5, 1);

    model = glm::scale(model, scale);
    model = glm::translate(model, pos);

    shader.SetMat4("model", model);

    // std::cout << mVAO << '\n';
    // std::cout << &(mVAO) << '\n';

    //texture.Use();

    glBindVertexArray(VAO);
    //ExitOnGLError();

    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

    // glActiveTexture(0);
    glBindVertexArray(0);
}

void Mesh::ExitOnGLError()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << err;
        exit(-1);
    }
}