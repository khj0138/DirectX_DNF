#pragma once
#include "..\\Engine_SRC\\hjSceneManager.h"
#include "BackGroundLoader.h"
#include "hjPlayScene.h"

#include "hjTown_GunHwaMun.h"
#include "hjTown_MainCamp.h"
#include "hjTown_SeriaRoom.h"

#include "hjDungeon_Entrance_1.h"
#include "hjDungeon_Entrance_2.h"
#include "hjDungeon_Skasa.h"
#include "hjDungeon_Skasa_Entrance.h"
#include "hjDungeon_Spirazzi.h"
#include "hjDungeon_Spirazzi_Entrance.h"
#include "hjDungeon_Hysmar.h"
#include "hjDungeon_Hysmar_Entrance.h"

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
		SceneManager::CreateScene<Town_SeriaRoom>(L"Town_SeriaRoom");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Town_GunHwaMun>(L"Town_GunHwaMun");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Town_MainCamp>(L"Town_MainCamp");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Skasa>(L"Dungeon_Skasa");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Spirazzi>(L"Dungeon_Spirazzi");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Hysmar>(L"Dungeon_Hysmar");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Hysmar_Entrance>(L"Dungeon_Hysmar_Entrance");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Skasa_Entrance>(L"Dungeon_Skasa_Entrance");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Spirazzi_Entrance>(L"Dungeon_Spirazzi_Entrance");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Entrance_1>(L"Dungeon_Entrance_1");
		//CreateBackGrounds();
		//SceneManager::CreateScene<Dungeon_Entrance_2>(L"Dungeon_Entrance_2");
		//CreateBackGrounds();

		SceneManager::LoadScene(L"Town_SeriaRoom");
		//SceneManager::GetActiveScene()->Update();
	}
}