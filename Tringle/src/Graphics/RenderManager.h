#pragma once

#include <map>
#include <string>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Singleton.h"

#include "gtc/matrix_transform.hpp"

class RenderManager : public Singleton<RenderManager>
{
friend class Singleton<RenderManager>;
public:
    // Primary manager functions
    RenderManager();
    ~RenderManager();
    void StartUp();
    void Update();
    void ShutDown();

    // Mesh list functions
    void AddMesh(Mesh mesh, int id);
    void DeleteMesh(int id);
    Mesh* GetMesh(int id);
private:
    std::map<std::string, Mesh*>* mMesh;
    std::map<std::string, Texture*>* mTexture;
    std::map<std::string, Shader*>* mShader;
};