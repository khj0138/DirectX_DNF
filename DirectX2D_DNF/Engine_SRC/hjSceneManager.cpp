#include "hjSceneManager.h"
#include "hjPlayScene.h"

namespace hj
{
	Scene* SceneManager::mActiveScene = nullptr;
	void SceneManager::Initialize()
	{
		mActiveScene = new PlayScene();
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
}
