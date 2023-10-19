#pragma once

#include "Mesh.h"
#include "Singleton.h"
#include "Core.h"

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
    MeshMap* mMesh;
};