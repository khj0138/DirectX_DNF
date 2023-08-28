#pragma once
#include "hjScene.h"

namespace hj
{
	class Player;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destroy();
		static void Release();


		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			scene->SetName(name);
			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();
			return true;
		}
		static Scene* LoadScene(std::wstring name);
		static Scene* GetActiveScene() { return mActiveScene; }
		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* GetPlayer() { return mPlayer; }

		static void RegisterPortal(std::wstring portalName, Vector2 portalPos); 
		static void SetPortalScene(std::wstring portalName, std::wstring sceneName); 
		static void PortalTeleport(std::wstring portalName);
	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
		static Player* mPlayer;
		static std::map<std::wstring, std::wstring> mPortalsScene;
		static std::map<std::wstring, Vector2> mPortals;
	};
}
