#include "RenderManager.h"

RenderManager::RenderManager()
{
    // Do nothing.
}

RenderManager::~RenderManager()
{
    // Do nothing.
}

void RenderManager::StartUp()
{
    
}

void RenderManager::Update()
{
    
}

void RenderManager::ShutDown()
{
    
}

void RenderManager::Draw(Mesh mesh, Shader shader, Texture texture)
{
    /*
    * Note for later:
    * Must call shader.SetInt("textureUniformName", texture.ID) before using texture
    * Need to test / research whether it is okay to call this before glActiveTexture()
    */
}