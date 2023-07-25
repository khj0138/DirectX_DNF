#pragma once
#include "..\\Engine_SRC\\hjSceneManager.h"
#include "BackGroundLoader.h"
#include "hjPlayScene.h"
#include "hjDungeon_Skasa.h"
#include "hjDungeon_Spirazzi.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\HjEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\HjEngine.lib")
#endif



//#include "..\hjEngine\\hjPlayScene.h"
//#include "hjSceneManager.h"
namespace hj
{
	void InitializeScenes()
	{
		//PlayScene* playScene = new PlayScene();
		SceneManager::CreateScene<Dungeon_Skasa>(L"Dungeon_Skasa");
		CreateBackGrounds();
		SceneManager::CreateScene<Dungeon_Spirazzi>(L"Dungeon_Spirazzi");
		CreateBackGrounds();

		//SceneManager::LoadScene(L"PlayScene");
		//SceneManager::GetActiveScene()->Update();
	}
}