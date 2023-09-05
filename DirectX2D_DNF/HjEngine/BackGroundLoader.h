#pragma once
#include "..\\Engine_SRC\\hjSceneManager.h"
//#include "..\\Engine_SRC\\hjScene.h"
//#include "..\\Engine_SRC\\hjTime.h"

#include "hjPlayScene.h"
#include "hjDungeon_Skasa.h"
#include "..\\Engine_SRC\\hjMeshRenderer.h"
#include "..\\Engine_SRC\\hjResources.h"
#include "..\\Engine_SRC\\hjApplication.h"
#include "hjImageScript.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\HjEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\HjEngine.lib")
#endif

extern hj::Application application;

//#include "..\hjEngine\\hjPlayScene.h"
//#include "hjSceneManager.h"
namespace hj
{
	
	void CreateBasicObject(const std::wstring name,  Vector3 position, bool flip = false, Vector2 moveRate = Vector2::One)
	{
		//Scene* activeScene = SceneManager::GetActiveScene();
		//float fixedRes = (float)application.GetFixedWidth() / 800.f;
		//fixedRes = 1.0f;

		GameObject* basicImage = new GameObject();
		//basicImage->SetName(name);
		MeshRenderer* mr = basicImage->AddComponent<MeshRenderer>();
		//Collider2D * cd = basicImage->AddComponent<Collider2D>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(name));
		mr->SetUVFlip(flip);

		Vector3 imageScale = Resources::Find<Material>(name)->GetTextureSize();
		basicImage->GetComponent<Transform>()->SetScale(imageScale);
		position.x = (position.x + imageScale.x / 2.0f);// *moveRate.x;
		//position.y = (position.y + imageScale.y / 2.0f) * fixedRes;// *moveRate.y;
		basicImage->GetComponent<Transform>()->SetPosition(position);
		basicImage->GetComponent<Transform>()->SetCamMoveRate(moveRate);
		//return basicImage;
		basicImage->SetName(name);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::BackGround, basicImage);
	}
	void CreateRepeatObject(const std::wstring name, Vector3 position, bool flip = false, Vector2 repeatScale = Vector2::One, Vector2 moveRate = Vector2::One)
	{
		//Scene* activeScene = SceneManager::GetActiveScene();
		//float fixedRes = (float)application.GetFixedWidth() / 800.f;
		//fixedRes = 1.0f;


		GameObject* basicImage = new GameObject();
		basicImage->SetName(name);
		MeshRenderer* mr = basicImage->AddComponent<MeshRenderer>();
		//Collider2D * cd = basicImage->AddComponent<Collider2D>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(name));
		mr->SetUVScale(repeatScale);
		mr->SetUVFlip(flip);

		Vector3 imageScale = Resources::Find<Material>(name)->GetTextureSize();

		imageScale.x *= repeatScale.x;
		imageScale.y *= repeatScale.y;
		position.x = (position.x + imageScale.x / 2.0f);// *moveRate.x;
		//position.y = (position.y + imageScale.y / 2.0f) * fixedRes;// *moveRate.y;
		//position.y += imageScale.y / 2.0f *fixedRes;

		basicImage->GetComponent<Transform>()->SetScale(imageScale);
		basicImage->GetComponent<Transform>()->SetPosition(position);
		basicImage->GetComponent<Transform>()->SetCamMoveRate(moveRate);

		
		/*ImageScript* script = basicImage->AddComponent<ImageScript>();
		script->setScale(repeatScale);*/
		//return basicImage;
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::BackGround, basicImage);
	}
	void CreateMoveRepeatObject(const std::wstring name, Vector3 position, bool flip = false, bool repeat = true, Vector2 repeatScale = Vector2::One, Vector2 uvMove = Vector2::Zero, Vector2 moveRate = Vector2::One)
	{
		//Scene* activeScene = SceneManager::GetActiveScene();
		//float fixedRes = (float)application.GetFixedWidth() / 800.f;
		//fixedRes = 1.0f;


		GameObject* basicImage = new GameObject();
		basicImage->SetName(name);
		MeshRenderer* mr = basicImage->AddComponent<MeshRenderer>();
		//Collider2D * cd = basicImage->AddComponent<Collider2D>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(name));
		mr->SetUVScale(repeatScale);
		mr->SetUVMove(uvMove);
		mr->SetUVFlip(flip);
		mr->SetUVRepeat(repeat);
		Vector3 imageScale = Resources::Find<Material>(name)->GetTextureSize();

		imageScale.x *= repeatScale.x;
		imageScale.y *= repeatScale.y;
		position.x = (position.x + imageScale.x / 2.0f);// *moveRate.x;
		//position.y = (position.y + imageScale.y / 2.0f) * fixedRes;// *moveRate.y;
		//position.y += imageScale.y / 2.0f *fixedRes;

		basicImage->GetComponent<Transform>()->SetScale(imageScale);
		basicImage->GetComponent<Transform>()->SetPosition(position);
		basicImage->GetComponent<Transform>()->SetCamMoveRate(moveRate);


		/*ImageScript* script = basicImage->AddComponent<ImageScript>();
		script->setScale(repeatScale);*/
		//return basicImage;
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::BackGround, basicImage);
	}
	void CreateBackGrounds()
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		if (activeScene->GetName() == L"LoadingScene")
		{
			float fixedRes = 1.0f / ((float)application.GetFixedWidth() / 800.f);

			CreateBasicObject(L"LoadingSceneBackground", Vector3(-40.0f, -150.0f, 0.0f) * fixedRes, false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"LoadingSceneCircle", Vector3(693.0f, 0.0f, 0.0f) * fixedRes, false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"LoadingSceneEffect", Vector3(788.0f, 63.0f, 0.0f) * fixedRes, false, Vector2(1.0f, 1.0f));

			Vector3 fixedScale = Vector3::Zero;
			Transform* objectTr;
			objectTr = activeScene->GetLayer(eLayerType::BackGround).FindObject(L"LoadingSceneBackground")->GetComponent<Transform>();
			objectTr->SetPosition(objectTr->GetPosition()+ Vector3(objectTr->GetScale().x * (fixedRes - 1.0f) / 2.0f, 0.0f, 0.0f));
			//objectTr->SetPosition(objectTr->GetPosition()+ Vector3(objectTr->GetScale().x * (fixedRes - 1.0f) / 4.0f, 0.0f , 0.0f));
			fixedScale = Vector3(objectTr->GetScale().x * fixedRes, objectTr->GetScale().y * fixedRes, objectTr->GetScale().z);
			objectTr->SetScale(fixedScale);
			
			
			objectTr = activeScene->GetLayer(eLayerType::BackGround).FindObject(L"LoadingSceneCircle")->GetComponent<Transform>();
			objectTr->SetPosition(objectTr->GetPosition() + Vector3(objectTr->GetScale().x * (fixedRes - 1.0f) / 2.0f, 0.0f, 0.0f));
			//objectTr->SetPosition(objectTr->GetPosition()  + Vector3(objectTr->GetScale().x * (fixedRes - 1.0f) / 4.0f, 0.0f, 0.0f));

			fixedScale = Vector3(objectTr->GetScale().x * fixedRes, objectTr->GetScale().y * fixedRes, objectTr->GetScale().z);
			objectTr->SetScale(fixedScale);
			
			
			
			objectTr = activeScene->GetLayer(eLayerType::BackGround).FindObject(L"LoadingSceneEffect")->GetComponent<Transform>();
			objectTr->SetPosition(objectTr->GetPosition() + Vector3(objectTr->GetScale().x * (fixedRes - 1.0f) / 2.0f, 0.0f, 0.0f));
			//objectTr->SetPosition(objectTr->GetPosition() + Vector3(objectTr->GetScale().x * (fixedRes - 1.0f) / 4.0f, 0.0f, 0.0f));
			fixedScale = Vector3(objectTr->GetScale().x * fixedRes, objectTr->GetScale().y * fixedRes, objectTr->GetScale().z);
			objectTr->SetScale(fixedScale);




		}
		if (activeScene->GetName() == L"Town_SeriaRoom")
		{
			//back_far
			//back_middle 1197 734 600 -145 1595 685 1340 7101119127
			CreateBasicObject(L"SeriaRoom_background_0", Vector3(0.0f, 0.0f, 500.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"SeriaRoom_seria_add_0", Vector3(0.0f, 0.0f, 500.0f), false, Vector2(1.0f, 1.0f));

			//ground

			//object
			CreateBasicObject(L"SeriaRoom_left_door_0", Vector3(82.0f, 154.0f, 498.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"SeriaRoom_right_door_0", Vector3(82.0f, 154.0f, 498.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"SeriaRoom_background_eff_0", Vector3(82.0f, 134.0f, 498.0f), false, Vector2(1.0f, 1.0f));

			// border object
			CreateBasicObject(L"SeriaRoom_border_tree_0", Vector3(0.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"SeriaRoom_border_tree_1", Vector3(873.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));

			// light
			CreateBasicObject(L"SeriaRoom_backgruond_light_reflect_0", Vector3(172.0f, 241.0f, 300.0f), false, Vector2(1.0f, 1.0f));

		}
		else if (activeScene->GetName() == L"Town_MainCamp")
		{
			//back_far
			CreateRepeatObject(L"MainCamp_back_far_0", Vector3(-430.0f, 457.0f, 500.0f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			//back_middle
			CreateBasicObject(L"MainCamp_back_middle_0", Vector3(6.0f, 445.0f, 499.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_back_middle_1", Vector3(865.0f, 445.0f, 499.0f), false, Vector2(1.0f, 1.0f));

			//ground
			CreateBasicObject(L"MainCamp_tile", Vector3(0.0f, -50.0f, 498.0f), false, Vector2(1.0f, 1.0f));

			//object
			CreateBasicObject(L"MainCamp_object_main_17", Vector3(1080.0f, 373.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_16", Vector3(85.0f, 345.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_5", Vector3(230.0f, 340.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_0", Vector3(000.0f, 220.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_3", Vector3(-80.0f, -30.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_12", Vector3(130.0f, 125.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_9", Vector3(1240.0f, 325.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_4", Vector3(1200.0f, 365.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_13", Vector3(1080.0f, 340.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_15", Vector3(800.0f, 325.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_14", Vector3(405.0f, 290.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_2", Vector3(705.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_7", Vector3(920.0f, 280.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_11", Vector3(1160.0f, 310.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_11", Vector3(1240.0f, 345.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_door_0", Vector3(1168.0f, 15.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_title_0", Vector3(1500.0f, 545.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_door_1", Vector3(1442.0f, 72.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_8", Vector3(1280.0f, -165.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_door_2", Vector3(1530.0f, -60.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_dodge_light_0", Vector3(1177.0f, 396.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_6", Vector3(1070.0f, -60.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			// border object
			CreateBasicObject(L"MainCamp_border_0", Vector3(0.0f, -55.0f, 400.0f), false, Vector2(1.0f, 1.0f));
		}
		else if (activeScene->GetName() == L"Town_GunHwaMun")
		{
			//back_far
			CreateRepeatObject(L"GunHwaMun_back_far_0", Vector3(0.0f, 450.0f, 500.0f), false, Vector2(2.0f, 1.0f), Vector2(1.0f, 1.0f));
			//back_middle
			CreateBasicObject(L"GunHwaMun_back_middle_0", Vector3(70.0f, 435.0f, 499.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_back_middle_1", Vector3(820.0f, 435.0f, 499.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_back_middle_2", Vector3(995.0f, 440.0f, 499.0f), false, Vector2(1.0f, 1.0f));

			//ground
			CreateBasicObject(L"GunHwaMun_tile", Vector3(0.0f, 00.0f, 498.0f), false, Vector2(1.0f, 1.0f));

			//object
			CreateBasicObject(L"GunHwaMun_door_0", Vector3(000.0f, 50.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_door_1", Vector3(000.0f, 110.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_object_title_0", Vector3(220.0f, 605.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_object_0", Vector3(575.0f, 325.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_object_1", Vector3(725.0f, 295.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			// border object
			CreateBasicObject(L"GunHwaMun_border_2", Vector3(200.0f, 00.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_border_0", Vector3(-30.0f, -10.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_border_3", Vector3(635.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_border_1", Vector3(1000.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
		}

		else if (activeScene->GetName() == L"Dungeon_Entrance_1")
		{
			//phase1
			//back_far
			// 
			// 
			//back_middle
			CreateBasicObject(L"Dungeon_Entrance_back_middle_0", Vector3(-90.0f, 455.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_back_middle_1", Vector3(726.0f, 456.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			//ground
			//CreateBasicObject(L"Dungeon_Entrance_object_building_0", Vector3(0.0f, 0.0f, 500.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_common_tile_1", Vector3(0.0f, 0.0f, 500.0f), false, Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Dungeon_Entrance_common_tile_1", Vector3(0.0f, 0.0f, 498.000f), false, Vector2(6.0f, 1.0f), Vector2(1.0f, 1.0f));

			//CreateBasicObject(L"Hysmar_back_middle_0", Vector3(-676.0f,395.0f, 499.000f), false, Vector2(1.0f, 1.0f));

			//ground object
			//CreateBasicObject(L"Dungeon_Entrance_object_wall_4", Vector3(160.0f, 275.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_4", Vector3(-27.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_3", Vector3(230.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_1", Vector3(487.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_1", Vector3(744.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_2", Vector3(1001.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Dungeon_Entrance_object_bottom_03", Vector3(700.0f, 170.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_01", Vector3(185.0f, 25.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_02", Vector3(1055.0f, 75.0f, 496.0f), false, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Dungeon_Entrance_object_bottom_05", Vector3(905.0f, 115.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_06", Vector3(890.0f, 215.0f, 496.0f), false, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Dungeon_Entrance_object_bottom_09", Vector3(310.0f, 230.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_09", Vector3(875.0f, 220.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_09", Vector3(610.0f, 80.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_08", Vector3(625.0f, 200.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_10", Vector3(1020.0f, 280.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_13", Vector3(600.0f, 255.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_14", Vector3(855.0f, 120.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_15", Vector3(210.0f, 150.0f, 496.0f), false, Vector2(1.0f, 1.0f));

			//object945 145 1095 165
			CreateBasicObject(L"Dungeon_Entrance_object_building_0", Vector3(-30.0f, 70.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_tree_0", Vector3(595.0f, 310.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_basic_7", Vector3(545.0f, 305.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_basic_2", Vector3(320.0f, 255.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_basic_3", Vector3(1095.0f, 255.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			// border object
			CreateBasicObject(L"Dungeon_Entrance_object_border_1", Vector3(0.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_border_2", Vector3(257.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_border_4", Vector3(514.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_border_2", Vector3(771.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_border_1", Vector3(1028.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));

		}
		else if (activeScene->GetName() == L"Dungeon_Entrance_2")
		{
			//phase1
			//back_far
			// 
			// 
			//back_middle
			//CreateBasicObject(L"Dungeon_Entrance_back_middle_0", Vector3(-90.0f, 455.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_back_middle_1", Vector3(-35.0f, 450.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_back_middle_2", Vector3(651.0f, 450.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			//ground
			//CreateBasicObject(L"Dungeon_Entrance_object_building_0", Vector3(0.0f, 0.0f, 500.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_common_tile_1", Vector3(0.0f, 0.0f, 500.0f), false, Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Dungeon_Entrance_common_tile_1", Vector3(0.0f, 0.0f, 498.000f), false, Vector2(6.0f, 1.0f), Vector2(1.0f, 1.0f));

			//CreateBasicObject(L"Hysmar_back_middle_0", Vector3(-676.0f,395.0f, 499.000f), false, Vector2(1.0f, 1.0f));

			//ground object
			CreateBasicObject(L"Dungeon_Entrance_object_wall_2", Vector3(-168.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_3", Vector3(89.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_0", Vector3(346.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_wall_1", Vector3(945.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			
			
			//CreateBasicObject(L"Dungeon_Entrance_object_wall_4", Vector3(-27.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));

			//object945 145 1095 165
			//CreateBasicObject(L"Dungeon_Entrance_object_building_0", Vector3(-30.0f, 70.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_tree_0", Vector3(595.0f, 310.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_basic_7", Vector3(545.0f, 305.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_basic_2", Vector3(320.0f, 255.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_04", Vector3(725.0f, 33.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_05", Vector3(850.0f, 270.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_06", Vector3(720.0f, 215.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_06", Vector3(85.0f, 70.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_07", Vector3(1030.0f, 127.0f, 497.0f), false, Vector2(1.0f, 1.0f));


			CreateBasicObject(L"Dungeon_Entrance_object_bottom_08", Vector3(355.0f, 255.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_09", Vector3(750.0f, 250.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_09", Vector3(880.0f, 100.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_09", Vector3(435.0f, 30.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_14", Vector3(175.0f, 220.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_16", Vector3(340.0f, 190.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_bottom_15", Vector3(640.0f, 110.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			
			CreateBasicObject(L"Dungeon_Entrance_object_basic_0", Vector3(-75.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_basic_1", Vector3(-70.0f, 25.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_basic_4", Vector3(400.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_basic_3", Vector3(85.0f, 300.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_tree_2", Vector3(675.0f, 310.0f, 495.0f), false, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Dungeon_Entrance_object_basic_7", Vector3(980.0f, 315.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_basic_8", Vector3(940.0f, 300.0f, 497.0f), false, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Dungeon_Entrance_object_bottom_13", Vector3(1000.0f, 265.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_basic_3", Vector3(1095.0f, 255.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			// border object
			CreateBasicObject(L"Dungeon_Entrance_object_border_2", Vector3(-90.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_border_3", Vector3(167.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_border_4", Vector3(766.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Dungeon_Entrance_object_border_1", Vector3(1023.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_border_1", Vector3(0.0f, 0.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_border_4", Vector3(514.0f, 0.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_border_2", Vector3(771.0f, 0.0f, 495.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Dungeon_Entrance_object_border_1", Vector3(1028.0f, 0.0f, 495.0f), false, Vector2(1.0f, 1.0f));

		}
		else if (activeScene->GetName() == L"Dungeon_Skasa_Entrance")
		{
			// back_far
			//	CreateRepeatObject(L"Skasa_common_tile1", Vector3(0.0f, 0.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Skasa_common_back_far_0", Vector3(-430.0f, 427.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Skasa_common_back_far_0", Vector3(-430.0f, 427.0f, 500.000f), false, Vector2(2.0f, 1.0f), Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Skasa_common_back_far_deco_0", Vector3(83.0f, 463.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Skasa_common_back_middle_icetile_0", Vector3(0.0f, 42.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_back_far_deco_2", Vector3(-360.0f, 417.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			// 
			//back_middle
			//CreateBasicObject(L"Spirazzi_back_middle_0", Vector3(-279.0f, 520.0f, 498.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_back_middle_0", Vector3(679.0f, 528.0f, 498.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_back_middle_pavillion_6", Vector3(230.0f, 360.0f, 499.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_back_middle_pavillion_5", Vector3(728.0f, 360.0f, 499.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_back_middle_pavillion_2", Vector3(0.0f, 327.0f, 499.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_back_middle_deco_1", Vector3(960.0f, 346.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_back_middle_deco_3", Vector3(0.0f, 375.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			// 
			//CreateBasicObject(L"Hysmar_back_middle_0", Vector3(-676.0f,395.0f, 499.000f), false, Vector2(1.0f, 1.0f));

			//ground
			CreateRepeatObject(L"Skasa_common_tile1", Vector3(0.0f, 0.0f, 498.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_back_middle_bush_0", Vector3(503.0f, 334.0f, 498.000f), false, Vector2(1.0f, 1.0f));
			//CreateRepeatObject(L"Spirazzi_tile1", Vector3(0.0f, 0.0f, 498.000f), false, Vector2(5.0f, 1.0f), Vector2(1.0f, 1.0f));

			//ground object
			CreateBasicObject(L"Skasa_common_pillar_fence_4", Vector3(610.0f, 250.0f, 497.000f), false,  Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_pillar_fence_6", Vector3(700.0f, 300.0f, 497.000f), false,  Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_tile_deco_4", Vector3(-242.0f, 194.0f, 497.000f), false,  Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_tile_deco_1", Vector3(284.0f, 180.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_tile_deco_1", Vector3(884.0f, 40.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_tile_deco_3", Vector3(881.0f, 164.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_tile_deco_2", Vector3(1114.0f, 228.0f, 497.000f), false, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Skasa_common_snow_0_0", Vector3(-104.0f, 275.0f, 497.000f), false,  Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_snow_0_2", Vector3(-26.0f, -26.0f, 497.000f), false,  Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_snow_0_2", Vector3(570.0f, 158.0f, 497.000f), false,  Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_snow_0_3", Vector3(1000.0f, 0.0f, 497.000f), false,  Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Skasa_common_icicle_1", Vector3(75.0f, 28.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_icicle_1", Vector3(406.0f, 289.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_icicle_0", Vector3(787.0f, 277.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_bottom_obj_0", Vector3(463.0f, 443.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_bottom_obj_0", Vector3(728.0f, 450.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_bottom_obj_6", Vector3(428.0f, 379.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_bottom_obj_7", Vector3(-355.0f, 95.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_bottom_obj_5", Vector3(-21.0f, 334.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_bottom_obj_5", Vector3(668.0f, 0.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_object_7", Vector3(764.0f, 401.0f, 497.000f), false, Vector2(1.0f, 1.0f));

			//border object
			CreateBasicObject(L"Skasa_common_icicle_3", Vector3(0.0f, 540.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_icicle_3", Vector3(275.0f, 540.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Skasa_common_icicle_3", Vector3(550.0f, 540.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_border_1", Vector3(767.0f, 0.0f, 496.000f), false, Vector2(1.0f, 1.0f));
			//object
			CreateBasicObject(L"Skasa_common_pillar_fence_9", Vector3(-165.0f, 50.0f, 400.0f), false,  Vector2(1.0f, 1.0f));
			//CreateMoveRepeatObject(L"Spirazzi_fog_normal_0", Vector3(0.0f, 0.0f, 495.000f), false, false, Vector2(3.0f, 1.0f), Vector2(-20.0f, 0.0f), Vector2::One);
		}
		else if (activeScene->GetName() == L"Dungeon_Skasa")
		{
			//CreateBasicObject(L"Skasa_object_ice_0", Vector3(650.0f, 440.0f, 500.000f), false, Vector2::One);
			//CreateBasicObject(L"Skasa_object_ice_1", Vector3(1050.0f, 440.0f, 500.000f), false, Vector2::One);
			//CreateBasicObject(L"Skasa_object_bigice_1", Vector3(1800.0f, 480.0f, 500.000f), false, Vector2::One);
			//CreateBasicObject(L"Skasa_object_ice_0", Vector3(1460.0f, -40.0f, 500.000f), false, Vector2::One);
			//CreateBasicObject(L"Skasa_object_ice_1", Vector3(1500.0f, 0.0f, 500.000f), false, Vector2::One);
			//CreateMoveRepeatObject(L"Skasa_object_mist_1", Vector3(0.0f, 330.0f, 500.000f), false, Vector2(4.0f, 1.0f), Vector2(-20.0f, 0.0f), Vector2::One);
			//CreateMoveRepeatObject(L"Skasa_object_mist_1", Vector3(-412.0f, 330.0f, 500.000f), false, Vector2(4.0f, 1.0f), Vector2(-20.0f, 0.0f), Vector2::One);
			// back_far
			CreateRepeatObject(L"Skasa_back_far_0", Vector3(0.0f, 600.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			
			// back_middle
			CreateRepeatObject(L"Skasa_back_middle_0", Vector3(-410.0f, 600.0f, 499.0f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));

			// fog
			// 
			// ground
			CreateRepeatObject(L"Skasa_tile1", Vector3(0.0f, 0.0f, 498.0f), false, Vector2(5.0f, 1.0f), Vector2(1.0f, 1.0f));

			// ground object
			CreateBasicObject(L"Skasa_object_bottom_0", Vector3(-240.0f, 310.0f, 497.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_bottom_0", Vector3(-140.0f, -120.0f, 497.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_bottom_0", Vector3(1440.0f, -90.0f, 497.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_bottom_1", Vector3(-225.0f, 430.0f, 497.000f), false, Vector2::One);
			// 
			// object
			CreateBasicObject(L"Skasa_object_bigice_0", Vector3(320.0f, 310.0f, 496.0f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_bigice_1", Vector3(1390.0f, 280.0f, 496.0f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_0", Vector3(180.0f,425.0f, 496.0f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_1", Vector3(600.0f,410.0f, 496.0f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_0", Vector3(590.0f, -140.0f, 496.0f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_1", Vector3(655.0f, -110.0f, 496.0f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_2", Vector3(480.0f,450.0f, 496.0f), false, Vector2::One);
			// border object
		}
		
		else if (activeScene->GetName() == L"Dungeon_Spirazzi_Entrance")
		{
			//back_far
			CreateRepeatObject(L"Spirazzi_back_far_1", Vector3(-287.0f, 500.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			// 
			//back_middle
			CreateBasicObject(L"Spirazzi_back_middle_0", Vector3(-279.0f, 520.0f, 498.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_back_middle_0", Vector3(679.0f, 528.0f, 498.000f), true, Vector2(1.0f,  1.0f));
			// 
			//CreateBasicObject(L"Hysmar_back_middle_0", Vector3(-676.0f,395.0f, 499.000f), false, Vector2(1.0f, 1.0f));

			//ground
			CreateRepeatObject(L"Spirazzi_tile1", Vector3(0.0f, 0.0f, 498.000f), false, Vector2(5.0f, 1.0f), Vector2(1.0f, 1.0f));

			//ground object
			CreateBasicObject(L"Spirazzi_object_0", Vector3(-169.0f, 402.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_0", Vector3(463.0f, 443.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_0", Vector3(728.0f, 450.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_6", Vector3(428.0f, 379.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_7", Vector3(-355.0f, 95.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_5", Vector3(-21.0f, 334.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_5", Vector3(668.0f, 0.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_7", Vector3(764.0f, 401.0f, 497.000f), false, Vector2(1.0f, 1.0f));

			//border object
			CreateBasicObject(L"Spirazzi_border_0", Vector3(0.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_border_1", Vector3(767.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			//object
			CreateMoveRepeatObject(L"Spirazzi_fog_normal_0", Vector3(0.0f, 0.0f, 400.0f), false, false, Vector2(3.0f, 1.0f), Vector2(-20.0f, 0.0f), Vector2::One);
		}
		else if (activeScene->GetName() == L"Dungeon_Spirazzi")
		{
			//back_far
			CreateRepeatObject(L"Spirazzi_back_far_1", Vector3(-160.0f, 450.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(0.8f, 1.0f));
			CreateRepeatObject(L"Spirazzi_back_far_2", Vector3(-160.0f, 665.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(0.8f, 1.0f));
			//back_middle
			CreateBasicObject(L"Spirazzi_nest_2", Vector3(715.0f, 430.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_back_middle_6", Vector3(0.0f, 500.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_back_middle_7", Vector3(1415.0f, 460.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			//fog
			//CreateMoveRepeatObject(L"Spirazzi_fog_2", Vector3(-940.0f, 530.0f, 499.000f), false, true, Vector2(3.0f, 1.0f), Vector2(-60.0f, 0.0f), Vector2::One);
			//CreateMoveRepeatObject(L"Spirazzi_fog_1", Vector3(-60.0f, 480.0f, 499.000f), false, true, Vector2(3.0f, 1.0f), Vector2(-60.0f, 0.0f), Vector2::One);
			//CreateMoveRepeatObject(L"Spirazzi_fog_0", Vector3(-940.0f, 530.0f, 499.000f), true, true, Vector2(3.0f, 1.0f), Vector2(-60.0f, 0.0f), Vector2::One);

			//CreateRepeatObject(L"Spirazzi_fog_2", Vector3(-940.0f, 530.0f, 499.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			//CreateRepeatObject(L"Spirazzi_fog_1", Vector3(-60.0f, 480.0f, 499.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			//CreateRepeatObject(L"Spirazzi_fog_0", Vector3(-120.0f, 480.0f, 499.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			//ground
			CreateRepeatObject(L"Spirazzi_tile1", Vector3(0.0f, -50.0f, 498.000f), false, Vector2(5.0f, 1.0f), Vector2(1.0f, 1.0f));
			//ground object
			CreateBasicObject(L"Spirazzi_bottom_obj_0", Vector3(340.0f,350.0f , 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_0", Vector3(760.0f,380.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_1", Vector3(315.0f,165.0f , 497.000f), true, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Spirazzi_bottom_obj_2", Vector3(1025.0f,155.0f ,497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_3", Vector3(-20.0f,150.0f , 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_3", Vector3(350.0f,120.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_3", Vector3(430.0f,-50.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_3", Vector3(746.0f ,250.0f, 497.000f), true, Vector2(1.0f, 1.0f));
																							 
			CreateBasicObject(L"Spirazzi_bottom_obj_3", Vector3(710.0f,105.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_4", Vector3(710.0f,110.0f , 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_bottom_obj_4", Vector3(-100.0f,120.0f ,497.000f), true, Vector2(1.0f, 1.0f));
			// object
			CreateBasicObject(L"Spirazzi_object_0", Vector3(-520.0f, 360.0f, 496.0f),false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_3", Vector3(560.0f, 460.0f, 496.0f),true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_3", Vector3(680.0f, 460.0f, 496.0f),false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_3", Vector3(1245.0f, 385.0f, 496.0f),true, Vector2(1.0f, 1.0f));
			
			
			CreateBasicObject(L"Spirazzi_object_3", Vector3(70.0f, 420.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_3", Vector3(180.0f, 405.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_3", Vector3(330.0f, 430.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_2", Vector3(-50.0f, 380.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_4", Vector3(155.0f, 445.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_object_4", Vector3(1585.0f, 195.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_2", Vector3(1540.0f, 420.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_4", Vector3(1610.0f, 410.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_4", Vector3(1430.0f, 220.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_3", Vector3(1655.0f, 345.0f, 496.0f),true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_4", Vector3(1305.0f, 85.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_4", Vector3(1600.0f, 35.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_4", Vector3(150.0f, 110.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_2", Vector3(460.0f, 10.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_2", Vector3(660.0f, -10.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_5", Vector3(-10.0f, 110.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_object_5", Vector3(460.0f, 215.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			
			// border object
			CreateBasicObject(L"Spirazzi_border_2", Vector3(320.0f,0.0f , 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_border_2", Vector3(1500.0f,0.0f , 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_border_0", Vector3(00.0f,-20.0f , 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_border_1", Vector3(770.0f,-20.0f , 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_border_0", Vector3(1180.0f,-20.0f , 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Spirazzi_border_3", Vector3(1435,0.0f , 400.0f), false, Vector2(1.0f, 1.0f));
		}
		else if (activeScene->GetName() == L"Dungeon_Hysmar_Entrance")
		{
			//back_far
			// 
			CreateRepeatObject(L"Hysmar_common_back_far_0", Vector3(0.0f,560.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			//back_middle
			CreateRepeatObject(L"Hysmar_common_back_middle_0", Vector3(-37.0f,534.0f, 499.000f), false, Vector2(2.0f, 1.0f), Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_back_middle_0", Vector3(-279.0f, 520.0f, 498.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Spirazzi_back_middle_0", Vector3(679.0f, 528.0f, 498.000f), true, Vector2(1.0f, 1.0f));
			// 

			//ground
			CreateRepeatObject(L"Hysmar_common_tile", Vector3(0.0f, 0.0f, 498.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));

			//ground object
			CreateBasicObject(L"Hysmar_common_object_crack_0", Vector3(-140.0f, 116.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_crack_2", Vector3(1026.0f, 119.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_wall_1", Vector3(-187.0f, 423.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_wall_5", Vector3(439.0f, 387.0f, 497.000f), false, Vector2(1.0f, 1.0f));

			//object
			CreateBasicObject(L"Hysmar_common_object_03", Vector3(593.0f, 367.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_05", Vector3(79.0f, 72.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_05", Vector3(196.0f, 376.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_05", Vector3(1066.0f, 102.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_09", Vector3(866.0f, 364.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_15", Vector3(1051.0f, 52.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_04", Vector3(-21.0f, 72.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_18", Vector3(357.0f, 44.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_18", Vector3(733.0f, 119.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_12", Vector3(948.0f, 168.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_12", Vector3(723.0f, 263.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_12", Vector3(240.0f, 44.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_13", Vector3(277.0f, 0.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_08", Vector3(482.0f, 155.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_08", Vector3(535.0f, 359.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_06", Vector3(-17.0f, 257.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_00", Vector3(-19.0f, 388.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_13", Vector3(976.0f, 157.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_14", Vector3(242.0f, 331.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_15", Vector3(175.0f, 163.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_15", Vector3(422.0f, 280.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_16", Vector3(88.0f, 331.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_17", Vector3(362.0f, 382.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_17", Vector3(695.0f, 366.0f, 497.000f), false, Vector2(1.0f, 1.0f));
			//border object
			CreateBasicObject(L"Hysmar_common_object_border_0", Vector3(-88.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_common_object_border_1", Vector3(635.0f, 0.0f, 400.0f), false, Vector2(1.0f, 1.0f));


		}
		else if (activeScene->GetName() == L"Dungeon_Hysmar")
		{
			//phase1
			//back_far
			CreateRepeatObject(L"Hysmar_phase1_back_far_0", Vector3(-458.0f, 433.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			//back_middle
			CreateRepeatObject(L"Hysmar_back_middle_0", Vector3(-676.0f, 395.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Hysmar_back_middle_0", Vector3(-676.0f,395.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			
			//ground
			CreateBasicObject(L"Hysmar_tile1", Vector3(0.0f, 0.0f, 498.000f), false, Vector2(1.0f, 1.0f));

			//object
			CreateBasicObject(L"Hysmar_phase2_object_2", Vector3(-105.0f, 185.0f, 496.0f), false, Vector2(1.0f, 1.0f));


			////phase2
			////back_far
			//CreateRepeatObject(L"Hysmar_phase2_back_far", Vector3(0.0f, 340.0f, 500.000f), false, Vector2(1.0f, 1.0f), Vector2(1.0f, 1.0f));
			////ground
			//CreateBasicObject(L"Hysmar_tile2", Vector3(0.0f, 0.0f, 497.000f), false, Vector2(1.0f, 1.0f));

			//// border object
			//CreateBasicObject(L"Hysmar_phase2_border_0", Vector3(0.0f, 0.0f, 496.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Hysmar_phase2_border_1", Vector3(1400.0f, 0.0f, 496.000f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Hysmar_phase2_object_0", Vector3(975.0f, -130.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Hysmar_phase2_object_1", Vector3(140.0f, -40.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Hysmar_phase2_object_3", Vector3(1415.0f, 50.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Hysmar_phase2_object_4", Vector3(610.0f, -40.0f, 496.0f), false, Vector2(1.0f, 1.0f));


		}
		
		
		
	}
}