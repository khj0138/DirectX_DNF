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
		basicImage->SetName(name);
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
			CreateRepeatObject(L"Skasa_back_far_1", Vector3(0.0f, 600.0f, 500.000f), false, Vector2(10.0f, 1.0f), Vector2(0.8f, 1.0f));
			CreateRepeatObject(L"Skasa_back_middle_0", Vector3(0.0f, 600.0f, 500.000f), false, Vector2(10.0f, 1.0f), Vector2(0.9f,1.0f));
			CreateRepeatObject(L"Skasa_tile1", Vector3(0.0f, 0.0f, 501.000f), false, Vector2(10.0f, 1.0f), Vector2(1.0f, 1.0f));
			

			CreateBasicObject(L"Skasa_object_bottom_1", Vector3(250.0f, 440.0f, 500.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_0", Vector3(650.0f, 440.0f, 500.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_bigice_0", Vector3(750.0f, 480.0f, 500.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_1", Vector3(1050.0f, 440.0f, 500.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_bigice_1", Vector3(1800.0f, 480.0f, 500.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_0", Vector3(1460.0f, -40.0f, 500.000f), false, Vector2::One);
			CreateBasicObject(L"Skasa_object_ice_1", Vector3(1500.0f, 0.0f, 500.000f), false, Vector2::One);
			CreateMoveRepeatObject(L"Skasa_object_mist_1", Vector3(0.0f, 330.0f, 500.000f), false, Vector2(4.0f, 1.0f), Vector2(-20.0f, 0.0f), Vector2::One);
			CreateMoveRepeatObject(L"Skasa_object_mist_1", Vector3(-412.0f, 330.0f, 500.000f), false, Vector2(4.0f, 1.0f), Vector2(-20.0f, 0.0f), Vector2::One);
		}

		else if (activeScene->GetName() == L"Dungeon_Spirazzi")
		{
			CreateRepeatObject(L"Sparazzi_back_far_1", Vector3(-160.0f, 450.0f, 500.000f), false, Vector2(5.0f, 1.0f), Vector2(0.8f, 1.0f));
			CreateRepeatObject(L"Sparazzi_back_far_2", Vector3(-160.0f, 665.0f, 500.000f), false, Vector2(5.0f, 1.0f), Vector2(0.8f, 1.0f));
			CreateBasicObject(L"Sparazzi_nest_2", Vector3(715.0f, 430.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_back_middle_6", Vector3(0.0f, 500.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_back_middle_7", Vector3(1415.0f, 470.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Sparazzi_fog_2", Vector3(-940.0f, 530.0f, 500.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Sparazzi_fog_1", Vector3(-60.0f, 480.0f, 500.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Sparazzi_fog_0", Vector3(-120.0f, 480.0f, 500.000f), false, Vector2(4.0f, 1.0f), Vector2(1.0f, 1.0f));
			CreateRepeatObject(L"Sparazzi_tile1", Vector3(0.0f, -50.0f, 500.000f), false, Vector2(5.0f, 1.0f), Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_0", Vector3(-520.0f, 360.0f, 500.000f),false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(560.0f, 460.0f, 500.000f),true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(680.0f, 460.0f, 500.000f),false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(1305.0f, 345.0f, 500.000f),true, Vector2(1.0f, 1.0f));
			
			
			CreateBasicObject(L"Sparazzi_object_3", Vector3(70.0f, 420.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(180.0f, 405.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_3", Vector3(330.0f, 430.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			
			CreateBasicObject(L"Sparazzi_object_2", Vector3(-50.0f, 380.0f, 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(155.0f, 445.0f, 500.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_object_4", Vector3(1585.0f, 195.0f, 500.000f), true, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Sparazzi_bottom_obj_0", Vector3(340.0f,350.0f , 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_0", Vector3(760.0f,380.0f , 500.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_1", Vector3(315.0f,165.0f , 500.000f), true, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Sparazzi_bottom_obj_2", Vector3(1025.0f,155.0f , 500.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(-20.0f,150.0f , 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(350.0f,120.0f , 500.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(430.0f,-50.0f , 500.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(710.0f,105.0f , 500.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_3", Vector3(746.0f ,250.0f, 500.000f), true, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Sparazzi_bottom_obj_4", Vector3(-100.0f,120.0f , 500.000f), true, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_bottom_obj_4", Vector3(710.0f,110.0f , 500.000f), false, Vector2(1.0f, 1.0f));

			CreateBasicObject(L"Sparazzi_border_2", Vector3(320.0f,0.0f , 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_2", Vector3(1500.0f,0.0f , 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_0", Vector3(00.0f,-20.0f , 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_1", Vector3(770.0f,-20.0f , 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_0", Vector3(1180.0f,-20.0f , 500.000f), false, Vector2(1.0f, 1.0f));
			CreateBasicObject(L"Sparazzi_border_3", Vector3(1435,0.0f , 500.000f), false, Vector2(1.0f, 1.0f));
		}
		else if (activeScene->GetName() == L"Dungeon_hisma")
		{
		}
		else if (activeScene->GetName() == L"Town")s
		{
		}
		
	}
}