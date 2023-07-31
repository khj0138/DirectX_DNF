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
		float fixedRes = (float)application.GetWidth() / 800.f;
		fixedRes = 1.0f;

		GameObject* basicImage = new GameObject();
		//basicImage->SetName(name);
		MeshRenderer* mr = basicImage->AddComponent<MeshRenderer>();
		//Collider2D * cd = basicImage->AddComponent<Collider2D>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(name));
		mr->SetUVFlip(flip);

		Vector3 imageScale = Resources::Find<Material>(name)->GetTextureSize();
		basicImage->GetComponent<Transform>()->SetScale(imageScale);
		position.x = (position.x + imageScale.x / 2.0f) * fixedRes;// *moveRate.x;
		position.y = (position.y + imageScale.y / 2.0f) * fixedRes;// *moveRate.y;
		basicImage->GetComponent<Transform>()->SetPosition(position);
		basicImage->GetComponent<Transform>()->SetCamMoveRate(moveRate);
		//return basicImage;
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, basicImage);
	}
	void CreateRepeatObject(const std::wstring name, Vector3 position, bool flip = false, Vector2 repeatScale = Vector2::One, Vector2 moveRate = Vector2::One)
	{
		//Scene* activeScene = SceneManager::GetActiveScene();
		float fixedRes = (float)application.GetWidth() / 800.f;
		fixedRes = 1.0f;


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
		position.x = (position.x + imageScale.x / 2.0f) * fixedRes;// *moveRate.x;
		position.y = (position.y + imageScale.y / 2.0f) * fixedRes;// *moveRate.y;
		//position.y += imageScale.y / 2.0f *fixedRes;

		basicImage->GetComponent<Transform>()->SetScale(imageScale);
		basicImage->GetComponent<Transform>()->SetPosition(position);
		basicImage->GetComponent<Transform>()->SetCamMoveRate(moveRate);

		
		/*ImageScript* script = basicImage->AddComponent<ImageScript>();
		script->setScale(repeatScale);*/
		//return basicImage;
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, basicImage);
	}
	void CreateMoveRepeatObject(const std::wstring name, Vector3 position, bool flip = false, Vector2 repeatScale = Vector2::One, Vector2 uvMove = Vector2::Zero, Vector2 moveRate = Vector2::One)
	{
		//Scene* activeScene = SceneManager::GetActiveScene();
		float fixedRes = (float)application.GetWidth() / 800.f;
		fixedRes = 1.0f;


		GameObject* basicImage = new GameObject();
		basicImage->SetName(name);
		MeshRenderer* mr = basicImage->AddComponent<MeshRenderer>();
		//Collider2D * cd = basicImage->AddComponent<Collider2D>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(name));
		mr->SetUVScale(repeatScale);
		mr->SetUVMove(uvMove);
		mr->SetUVFlip(flip);
		Vector3 imageScale = Resources::Find<Material>(name)->GetTextureSize();

		imageScale.x *= repeatScale.x;
		imageScale.y *= repeatScale.y;
		position.x = (position.x + imageScale.x / 2.0f) * fixedRes;// *moveRate.x;
		position.y = (position.y + imageScale.y / 2.0f) * fixedRes;// *moveRate.y;
		//position.y += imageScale.y / 2.0f *fixedRes;

		basicImage->GetComponent<Transform>()->SetScale(imageScale);
		basicImage->GetComponent<Transform>()->SetPosition(position);
		basicImage->GetComponent<Transform>()->SetCamMoveRate(moveRate);


		/*ImageScript* script = basicImage->AddComponent<ImageScript>();
		script->setScale(repeatScale);*/
		//return basicImage;
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, basicImage);
	}
	void CreateBackGrounds()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene->GetName() == L"SeriaRoom")
		{
		}
		if (activeScene->GetName() == L"Town")
		{
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

		else if (activeScene->GetName() == L"Dungeon_Spirazzi")
		{
			//back_far
			CreateRepeatObject(L"Sparazzi_back_far_1", Vector3(-160.0f, 450.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(0.8f, 1.0f));
			CreateRepeatObject(L"Sparazzi_back_far_2", Vector3(-160.0f, 665.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(0.8f, 1.0f));
			//back_middle
			CreateBasicObject(L"Sparazzi_nest_2", Vector3(715.0f, 430.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_back_middle_6", Vector3(0.0f, 500.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_back_middle_7", Vector3(1415.0f, 460.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			//fog
			CreateMoveRepeatObject(L"Sparazzi_fog_2", Vector3(-940.0f, 530.0f, 499.000f), false, Vector2(3.0f, 1.0f), Vector2(-60.0f, 0.0f), Vector2::One);
			CreateMoveRepeatObject(L"Sparazzi_fog_1", Vector3(-60.0f, 480.0f, 499.000f), false, Vector2(3.0f, 1.0f), Vector2(-60.0f, 0.0f), Vector2::One);
			CreateMoveRepeatObject(L"Sparazzi_fog_0", Vector3(-120.0f, 480.0f, 499.000f), false, Vector2(3.0f, 1.0f), Vector2(-60.0f, 0.0f), Vector2::One);

			//CreateRepeatObject(L"Sparazzi_fog_2", Vector3(-940.0f, 530.0f, 499.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			//CreateRepeatObject(L"Sparazzi_fog_1", Vector3(-60.0f, 480.0f, 499.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			//CreateRepeatObject(L"Sparazzi_fog_0", Vector3(-120.0f, 480.0f, 499.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			//ground
			CreateRepeatObject(L"Sparazzi_tile1", Vector3(0.0f, -50.0f, 498.000f), false, Vector2(5.0f, 1.0f), Vector2(1.0f, 1.0f));
			//ground object
			CreateBasicObject(L"Sparazzi_bottom_obj_0", Vector3(340.0f,350.0f , 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_0", Vector3(760.0f,380.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_1", Vector3(315.0f,165.0f , 497.000f), true, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Sparazzi_bottom_obj_2", Vector3(1025.0f,155.0f ,497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(-20.0f,150.0f , 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(350.0f,120.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(430.0f,-50.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(746.0f ,250.0f, 497.000f), true, Vector2(1.0f, 1.0f));
																							 
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(710.0f,105.0f , 497.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_4", Vector3(710.0f,110.0f , 497.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_4", Vector3(-100.0f,120.0f ,497.000f), true, Vector2(1.0f, 1.0f));
			// object
			CreateBasicObject(L"Sparazzi_object_0", Vector3(-520.0f, 360.0f, 496.0f),false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(560.0f, 460.0f, 496.0f),true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(680.0f, 460.0f, 496.0f),false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(1245.0f, 385.0f, 496.0f),true, Vector2(1.0f, 1.0f));
			
			
			CreateBasicObject(L"Sparazzi_object_3", Vector3(70.0f, 420.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(180.0f, 405.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(330.0f, 430.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			//
			CreateBasicObject(L"Sparazzi_object_2", Vector3(-50.0f, 380.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(155.0f, 445.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			//CreateBasicObject(L"Sparazzi_object_4", Vector3(1585.0f, 195.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_2", Vector3(1540.0f, 420.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(1610.0f, 410.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(1430.0f, 220.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(1655.0f, 345.0f, 496.0f),true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(1305.0f, 85.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(1600.0f, 35.0f, 496.0f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(150.0f, 110.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_2", Vector3(460.0f, 10.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_2", Vector3(660.0f, -10.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_5", Vector3(-10.0f, 110.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_5", Vector3(460.0f, 215.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			
			// border object
			CreateBasicObject(L"Sparazzi_border_2", Vector3(320.0f,0.0f , 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_2", Vector3(1500.0f,0.0f , 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_0", Vector3(00.0f,-20.0f , 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_1", Vector3(770.0f,-20.0f , 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_0", Vector3(1180.0f,-20.0f , 495.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_3", Vector3(1435,0.0f , 495.0f), false, Vector2(1.0f, 1.0f));
		}
		else if (activeScene->GetName() == L"Dungeon_Hysmar")
		{
			//phase1
			////back_far
			//CreateRepeatObject(L"Hysmar_phase1_back_far_0", Vector3(-458.0f, 433.0f, 500.000f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			////back_middle
			//CreateBasicObject(L"Hysmar_back_middle_0", Vector3(244.0f,395.0f, 499.000f), false, Vector2(1.0f, 1.0f));
			
			//ground
			//CreateBasicObject(L"Hysmar_tile1", Vector3(0.0f, 0.0f, 500.000f), false, Vector2(1.0f, 1.0f));

			//object
			//CreateBasicObject(L"Hysmar_phase2_object_2", Vector3(-105.0f, 185.0f, 496.0f), false, Vector2(1.0f, 1.0f));


			//phase2
			//back_far
			CreateRepeatObject(L"Hysmar_phase2_back_far", Vector3(0.0f, 340.0f, 500.000f), false, Vector2(1.0f, 1.0f), Vector2(1.0f, 1.0f));
			//ground
			CreateBasicObject(L"Hysmar_tile2", Vector3(0.0f, 0.0f, 497.000f), false, Vector2(1.0f, 1.0f));

			// border object
			CreateBasicObject(L"Hysmar_phase2_border_0", Vector3(0.0f, 0.0f, 496.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_phase2_border_1", Vector3(1400.0f, 0.0f, 496.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_phase2_object_0", Vector3(975.0f, -130.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_phase2_object_1", Vector3(140.0f, -40.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_phase2_object_3", Vector3(1415.0f, 50.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Hysmar_phase2_object_4", Vector3(610.0f, -40.0f, 496.0f), false, Vector2(1.0f, 1.0f));


		}
		else if (activeScene->GetName() == L"Town_MainCamp")
		{
			//back_far
			CreateRepeatObject(L"MainCamp_back_far_0", Vector3(-430.0f, 457.0f, 500.0f), false, Vector2(3.0f, 1.0f), Vector2(1.0f, 1.0f));
			//back_middle 1197 734 600 -145 1595 685 1340 710
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
			CreateBasicObject(L"MainCamp_object_door_0", Vector3(1168.0f,15.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_title_0", Vector3(1500.0f, 545.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_door_1", Vector3(1442.0f, 72.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_8", Vector3(1280.0f, -165.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_door_2", Vector3(1530.0f, -60.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_dodge_light_0", Vector3(1177.0f, 396.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"MainCamp_object_main_6", Vector3(1070.0f, -60.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			// border object 80 160
			CreateBasicObject(L"MainCamp_border_0", Vector3(0.0f, -55.0f, 496.0f), false, Vector2(1.0f, 1.0f));
		}
		else if (activeScene->GetName() == L"Town_GunHwaMun")
		{
			//back_far
			CreateRepeatObject(L"GunHwaMun_back_far_0", Vector3(0.0f, 400.0f, 500.0f), false, Vector2(2.0f, 1.0f), Vector2(1.0f, 1.0f));
			//back_middle
			CreateBasicObject(L"GunHwaMun_back_middle_0", Vector3(70.0f, 385.0f, 499.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_back_middle_1", Vector3(820.0f, 385.0f, 499.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_back_middle_2", Vector3(995.0f, 390.0f, 499.0f), false, Vector2(1.0f, 1.0f));

			//ground
			CreateBasicObject(L"GunHwaMun_tile", Vector3(0.0f, -50.0f, 498.0f), false, Vector2(1.0f, 1.0f));

			//object795495
			CreateBasicObject(L"GunHwaMun_door_0", Vector3(000.0f, 000.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_door_1", Vector3(000.0f, 60.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_object_title_0", Vector3(220.0f, 555.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_object_0", Vector3(575.0f, 275.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_object_1", Vector3(725.0f, 245.0f, 497.0f), false, Vector2(1.0f, 1.0f));
			// border object
			CreateBasicObject(L"GunHwaMun_border_0", Vector3(-30.0f, -60.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_border_2", Vector3(200.0f, -50.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_border_3", Vector3(635.0f, -50.0f, 496.0f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"GunHwaMun_border_1", Vector3(1000.0f, -50.0f, 496.0f), false, Vector2(1.0f, 1.0f));
		}
		
	}
}