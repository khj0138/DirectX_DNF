#include "hjSceneManager.h"

#include "hjPlayerScript.h"
//#include "hjApplication.h"
//
//extern hj::Application application;

namespace hj
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	std::map<std::wstring, std::wstring>  SceneManager::mPortalsScene;
	std::map<std::wstring, Vector2>  SceneManager::mPortals;
	PlayerScript* SceneManager::mPlayer = nullptr;

	void SceneManager::Initialize()
	{
		GameObject* player = new GameObject();
		mPlayer = player->AddComponent<PlayerScript>();

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
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (auto& iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}
	void SceneManager::RegisterPortal(std::wstring portalName, Vector2 portalPos)
	{
		mPortals.insert(std::make_pair(portalName, portalPos));
		for (auto iter = mScenes.begin(); iter != mScenes.end(); iter++)
		{
			if (iter->second == mActiveScene)
			{
				SetPortalScene(portalName, iter->first);
				return;
			}
		}
	}
	void SceneManager::SetPortalScene(std::wstring portalName, std::wstring sceneName)
	{
		mPortalsScene.insert(std::make_pair(portalName, sceneName));
	}
	void SceneManager::PortalTeleport(std::wstring portalName)
	{
		std::map<std::wstring, std::wstring>::iterator PortalScene = mPortalsScene.find(portalName);
		if (PortalScene != mPortalsScene.end())
		{
			LoadScene(PortalScene->second);
			std::map<std::wstring, Vector2>::iterator PortalPos = mPortals.find(portalName);
			if (PortalPos != mPortals.end())
			{
				Vector3 playerPos = mPlayer->GetOwner()->GetComponent<Transform>()->GetPosition();
				mPlayer->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(PortalPos->second.x, 0.0f,playerPos.z));
				mPlayer->GetOwner()->GetComponent<Transform>()->SetVirtualZ(PortalPos->second.y);
			}
		}
		

	}
	void SceneManager::PortalTeleport(std::wstring sceneName, Vector2 teleportPos)
	{
		std::map<std::wstring, Scene*>::iterator PortalScene = mScenes.find(sceneName);
		if (PortalScene != mScenes.end())
		{
			LoadScene(sceneName);
			Vector3 playerPos = mPlayer->GetOwner()->GetComponent<Transform>()->GetPosition();
			mPlayer->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(teleportPos.x, 0.0f, playerPos.z));
			mPlayer->GetOwner()->GetComponent<Transform>()->SetVirtualZ(teleportPos.y);
		}
	}
}
