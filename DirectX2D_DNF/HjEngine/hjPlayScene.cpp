#include "hjPlayScene.h"
#include "hjTransform.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"
#include "hjMesh.h"
#include "hjCameraScript.h"
#include "hjCamera.h"
#include "hjGridScript.h"
#include "hjPlayerScript.h"

//#include "hjObject.h"

namespace hj
{
	PlayScene::PlayScene()
	{

	}
	PlayScene::~PlayScene()
	{
		 
	}
	void PlayScene::Initialize()
	{
		{
			// GameObject* player 
			// = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

			GameObject* player = new GameObject();
			player->GetComponent<Transform>()->SetScale(Vector3{ 500.0f, 500.0f, 2.0f });
			player->SetName(L"SwordMan");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.000f));


			/*GameObject* child = new GameObject();
			child->SetName(L"ZeldaChild");
			AddGameObject(eLayerType::Player, child);
			MeshRenderer* mr2 = player->AddComponent<MeshRenderer>();
			mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			child->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));
			
			child->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

			const float pi = 3.141592f;
			float degree = pi / 2.0f;
			
			player->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
			player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));*/
		}


		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"SwordMan3");
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 0.0f,0.0f));
		//}
			GameObject* player = new GameObject();
		{
			player->GetComponent<Transform>()->SetScale(Vector3{500.0f, 500.0f, 2.0f});
			player->SetName(L"SwordMan2");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.000f));
			player->AddComponent<PlayerScript>();
		}

		//// Main Camera
		//Camera* cameraComp = nullptr;
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Player, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::Player, false);
		//	camera->AddComponent<CameraScript>();
		//	camera->GetComponent<Camera>()->RegisterTarget(player);
		//	camera->GetComponent<Camera>()->SetTarget(L"SwordMan2");
		//	//camera->AddComponent<CameraScript>();
		//}
		// Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			camera->GetComponent<Camera>()->RegisterTarget(player);
			//camera->GetComponent<Camera>()->SetTarget(L"SwordMan2");
			
		}
		
		// UI Camera
		/*{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);

		}

		{
			GameObject* grid = new GameObject();
			grid->SetName(L"Grid");
			AddGameObject(eLayerType::Grid, grid);
			MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridSc = grid->AddComponent<GridScript>();
			gridSc->SetCamera(cameraComp);
		}*/
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}