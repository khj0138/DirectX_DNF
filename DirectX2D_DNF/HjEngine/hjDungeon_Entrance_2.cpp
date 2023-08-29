#include "hjDungeon_Entrance_2.h"
//#include "hjPlayScene.h"
#include "hjTransform.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"
#include "hjMesh.h"
#include "hjCameraScript.h"
#include "hjCamera.h"
#include "hjGridScript.h"
#include "hjPlayerScript.h"
#include "hjRenderer.h"
//#include "hjObject.h"
#include "hjCollider2D.h"
#include "hjCollisionManager.h"

#include "hjInput.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"


#include "hjCommonPortalScript.h"
#include "hjPortalScript.h"
#include "hjSceneManager.h"
#include "hjPlayer.h"
#include "hjDragonSoldier.h"
namespace hj
{
	Dungeon_Entrance_2::Dungeon_Entrance_2()
	{

	}
	Dungeon_Entrance_2::~Dungeon_Entrance_2()
	{

	}
	void Dungeon_Entrance_2::Initialize()
	{
		

		
		GameObject* gate = new GameObject();
		{
			//gate->GetComponent<Transform>()->SetScale(Vector3{ 300.0f, 300.0f, 2.0f });


			gate->GetComponent<Transform>()->SetScale(Vector3{ 108.0f, 180.0f, 2.0f });
			gate->SetName(L"CommonPortal");
			AddGameObject(eLayerType::BackGround, gate);
			MeshRenderer* mr = gate->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			gate->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 400.000f));
			gate->GetComponent<Transform>()->SetVirtualZ(250.0f);

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<CommonPortalScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetPortal(L"Entrance2Portal1", Vector2(200.0f, 0.0f));
			portal->SetDestination(L"Entrance1Portal");
			gate->SetState(GameObject::eState::Paused);
		}
		gate = new GameObject();
		{
			//gate->GetComponent<Transform>()->SetScale(Vector3{ 300.0f, 300.0f, 2.0f });


			gate->GetComponent<Transform>()->SetScale(Vector3{ 108.0f, 180.0f, 2.0f });
			gate->SetName(L"CommonPortal");
			AddGameObject(eLayerType::BackGround, gate);
			MeshRenderer* mr = gate->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			gate->GetComponent<Transform>()->SetPosition(Vector3(750.0f, 0.0f, 400.000f));
			gate->GetComponent<Transform>()->SetVirtualZ(360.0f);

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<CommonPortalScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetPortal(L"Entrance2Portal2", Vector2(000.0f, -200.0f));
			portal->SetDestination(L"SpirazziEntrancePortal1");
			gate->SetState(GameObject::eState::Paused);
		}
		gate = new GameObject();
		{
			//gate->GetComponent<Transform>()->SetScale(Vector3{ 300.0f, 300.0f, 2.0f });


			gate->GetComponent<Transform>()->SetScale(Vector3{ 108.0f, 180.0f, 2.0f });
			gate->SetName(L"CommonPortal");
			AddGameObject(eLayerType::BackGround, gate);
			MeshRenderer* mr = gate->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			gate->GetComponent<Transform>()->SetPosition(Vector3(1050.0f, 0.0f, 400.000f));
			gate->GetComponent<Transform>()->SetVirtualZ(250.0f);

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<CommonPortalScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetPortal(L"Entrance2Portal3", Vector2(-200.0f, 00.0f));
			portal->SetDestination(L"SkasaEntrancePortal1");
			gate->SetState(GameObject::eState::Paused);
		}
		gate = new GameObject();
		{
			//gate->GetComponent<Transform>()->SetScale(Vector3{ 300.0f, 300.0f, 2.0f });


			gate->GetComponent<Transform>()->SetScale(Vector3{ 108.0f, 180.0f, 2.0f });
			gate->SetName(L"CommonPortal");
			AddGameObject(eLayerType::BackGround, gate);
			MeshRenderer* mr = gate->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			gate->GetComponent<Transform>()->SetPosition(Vector3(500.0f, 0.0f, 400.000f));
			gate->GetComponent<Transform>()->SetVirtualZ(0.0f);

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<CommonPortalScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetPortal(L"Entrance2Portal4", Vector2(00.0f, 100.0f));
			portal->SetDestination(L"HysmarEntrancePortal1");
			gate->SetState(GameObject::eState::Paused);
		}

		DragonSoldier* dragon = new DragonSoldier();
		AddGameObject(eLayerType::Monster, dragon);
		dragon->GetComponent<Transform>()->SetPosition(Vector3(400.0f, 0.0f, 2.000f));
		dragon->Initialize();
		dragon->EnterScene();

		Player* player = SceneManager::GetPlayer();

		// MainCamera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3((800.0f + 0.0f) * 1.0f, (450.0f + 0.0f) * 1.0f, -10.0f));
			//camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->TurnLayerMask(eLayerType::Player, true);
			cameraComp->TurnLayerMask(eLayerType::BackGround, true);
			camera->AddComponent<CameraScript>();
			camera->GetComponent<Camera>()->RegisterTarget(player);
			camera->GetComponent<Camera>()->SetTarget(L"SwordMan2");
			renderer::cameras.push_back(cameraComp);

			cameraComp->setMaxXY(Vector2(2260.0f, 1160.0f));
		}
		//CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		//// UI Camera
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Player, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	//cameraComp->TurnLayerMask(eLayerType::Player, false);

		//}
		/*
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
		/*{
			GameObject* mouse = hj::Input::mMouse;
			AddGameObject(eLayerType::Player, mouse);
			MeshRenderer* mr = mouse->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			mouse->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			mouse->GetComponent<Transform>()->SetScale(Vector3(100.0f, 100.0f, 1.0f));
			Collider2D* cd = mouse->AddComponent<Collider2D>();
		}*/
	}

	void Dungeon_Entrance_2::Update()
	{
		std::vector<GameObject*> monsters = GetLayer(eLayerType::Monster).GetGameObjects();
		bool monsterZero = false;
		if (monsters.size() == 0)
		{
			monsterZero = true;
		}
		else
		{
			monsterZero = true;
			for (int i = 0; i < monsters.size(); i++)
			{
				if (monsters[i]->GetState() == GameObject::eState::Active)
				{
					monsterZero = false;
					break;
				}
			}
		}
		if (monsterZero)
		{
			std::vector<GameObject*> backgrounds = GetLayer(eLayerType::BackGround).GetGameObjects();
			for (int i = 0; i < backgrounds.size(); i++)
			{
				if (backgrounds[i]->GetName() == L"CommonPortal")
					backgrounds[i]->SetState(GameObject::eState::Active);
				if (backgrounds[i]->GetName() == L"GateOutSeriaRoom")
					backgrounds[i]->SetState(GameObject::eState::Active);
			}
		}
		Scene::Update();
	}

	void Dungeon_Entrance_2::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Dungeon_Entrance_2::Render()
	{
		Scene::Render();
	}
	void Dungeon_Entrance_2::OnEnter()
	{
		Player* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{

			player->EnterScene();
			AddGameObject(eLayerType::Player, (GameObject*)player);
			player->GetComponent<Transform>()->SetPosition(Vector3(500.0f, 0.0f, 1.000f));
			player->GetComponent<Transform>()->SetVirtualZ(200.0f);
		}
	}
	void Dungeon_Entrance_2::OnExit()
	{
		Player* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{
			EraseGameObject(eLayerType::Player, (GameObject*)player);
			player->ExitScene();
		}
	}
}