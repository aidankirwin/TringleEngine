#pragma once

#include <vector>

#include "Scene.h"
#include "Singleton.h"

// TODO: separate definitions and declarations
class SceneManager : public Singleton<SceneManager>
{
public:
	~SceneManager() {}

	void AddScene(Scene* s)
	{
		mScenes.push_back(s);
	}

	// Set to 0 by default
	void SetCurrentScene(int id)
	{
		mCurrScene = id;
	}

	// Set to 0 by default
	Scene* GetCurrentScene()
	{
		return mScenes.at(mCurrScene);
	}

	Scene* GetScene(int id)
	{
		return mScenes.at(id);
	}
private:
	std::vector<Scene*> mScenes;
	unsigned int mCurrScene;
};