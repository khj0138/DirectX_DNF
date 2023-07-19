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
	
	void CreateBasicObject(const std::wstring name, Vector3 position, Vector2 moveRate = Vector2::One)
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
		Vector3 imageScale = Resources::Find<Material>(name)->GetTextureSize();
		basicImage->GetComponent<Transform>()->SetScale(imageScale);
		position.x = (position.x + imageScale.x / 2.0f) * fixedRes;// *moveRate.x;
		position.y = (position.y + imageScale.y / 2.0f) * fixedRes;// *moveRate.y;
		basicImage->GetComponent<Transform>()->SetPosition(position);
		basicImage->GetComponent<Transform>()->SetCamMoveRate(moveRate);
		//return basicImage;
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, basicImage);
	}
	void CreateRepeatObject(const std::wstring name, Vector3 position, Vector2 repeatScale = Vector2::One, Vector2 moveRate = Vector2::One)
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
		if (activeScene->GetName() == L"Loading")
		{
		}
		else if (activeScene->GetName() == L"Dungeon_skasa")
		{
			CreateRepeatObject(L"back_far_0", Vector3(0.0f, 600.0f, 999.000f), Vector2(10.0f, 1.0f), Vector2(0.8f, 1.0f));
			CreateRepeatObject(L"back_middle_0", Vector3(0.0f, 600.0f, 999.000f), Vector2(10.0f, 1.0f), Vector2(0.9f,1.0f));
			CreateRepeatObject(L"skasa_tile", Vector3(0.0f, 0.0f, 999.0f), Vector2(10.0f, 1.0f), Vector2(1.0f, 1.0f));


			CreateBasicObject(L"object_bottom_1", Vector3(250.0f, 440.0f, 999.000f), Vector2::One);

			CreateBasicObject(L"object_ice_0", Vector3(650.0f, 440.0f, 999.000f), Vector2::One);
			CreateBasicObject(L"object_bigice_0", Vector3(750.0f, 480.0f, 999.000f), Vector2::One);
			CreateBasicObject(L"object_ice_1", Vector3(1050.0f, 440.0f, 999.000f), Vector2::One);

			CreateBasicObject(L"object_bigice_1", Vector3(1800.0f, 480.0f, 999.000f), Vector2::One);
			CreateBasicObject(L"object_mist_0", Vector3(250.0f, 480.0f, 999.000f), Vector2::One);
			CreateBasicObject(L"object_mist_1", Vector3(250.0f, 480.0f, 999.000f), Vector2::One);
			//CreateRepeatObject
			//CreateBasicObject(L"object_ice_3", Vector3(400.0f, 0.0f, 999.000f), 1.0f);
			CreateBasicObject(L"object_ice_0", Vector3(1460.0f, -40.0f, 999.000f), Vector2::One);
			CreateBasicObject(L"object_ice_1", Vector3(1500.0f, 0.0f, 999.000f), Vector2::One);
		}

		else if (activeScene->GetName() == L"Dungeon_spirazzi")
		{
		}
		else if (activeScene->GetName() == L"Dungeon_hisma")
		{
		}
		else if (activeScene->GetName() == L"Town")
		{
		}
		
	}
	/*GameObject* CreateMoveImage(float moveRate, const std::wstring name)
	{
		GameObject* MoveImage
		re
	}*/
}