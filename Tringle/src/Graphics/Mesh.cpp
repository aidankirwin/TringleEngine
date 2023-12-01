#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
    mVertices(vertices), mIndices(indices)
{

}

void Mesh::Initialize()
{
    // TODO: something is wrong with how VAO setup happens here,
   // Get an access violation when trying to bind to VAO in draw call
   // Update: see ExitOnGLError()

    std::cout << glGetString(GL_VERSION) << '\n';
    std::cout << "VAO:" << mVAO << '\n';
    std::cout << "VAO address:" << &(mVAO) << '\n';

    glGenVertexArrays(1, &(mVAO));

    // ExitOnGLError();

    std::cout << "VAO:" << mVAO << '\n';
    std::cout << "VAO address:" << &mVAO << '\n';

    // Returns error 1282
    // GL_INVALID_OPERATION
    // Something is wrong with VAO generation
    // Update: wtf if we run this before glGenVertexArrays() I get same error
    // // Fixed: something is wrong with shader uniform setters
    // ExitOnGLError();

    glBindVertexArray(mVAO);

    for (int i = 0; i < (mVertices).size(); i++)
    {
        std::cout << glm::to_string((mVertices)[i].Position) << '\n';
        std::cout << glm::to_string((mVertices)[i].TexCoord) << '\n';
    }

    std::cout << "VAO:" << mVAO << '\n';
    std::cout << "VAO address:" << &(mVAO) << '\n';

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, (mVertices).size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    std::cout << "Vertices size:" << (mVertices).size() * sizeof(Vertex) << '\n';

    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);
    ExitOnGLError();

    std::cout << "Indices size:" << mIndices.size() * sizeof(unsigned int) << '\n';
    std::cout << "Indices memory address:" << &(mIndices[0]) << '\n';

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

    std::cout << "TexCoord offset:" << (void*)offsetof(Vertex, TexCoord) << '\n';
    std::cout << "3 float offset:" << (void*)(3 * sizeof(float)) << '\n';

    ExitOnGLError();

    glBindVertexArray(0);
}

void Mesh::Draw(Shader shader)
{
    /*
    * Note for later:
    * Must call shader.SetInt("textureUniformName", texture.ID) before using texture
    * Need to test / research whether it is okay to call this before glActiveTexture()
    */

    glm::mat4 model(1.0f);
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 scale = glm::vec3(5, 5, 5);

    model = glm::scale(model, scale);
    model = glm::translate(model, pos);

    // shader.SetMat4("model", model);

    std::cout << mVAO << '\n';
    std::cout << &(mVAO) << '\n';

    //texture.Use();

    glBindVertexArray(mVAO);
    ExitOnGLError();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Access violation

   /* glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>((mesh->Indices).size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(0);*/
}

void Mesh::ExitOnGLError()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << err;
        exit(-1);
    }
}