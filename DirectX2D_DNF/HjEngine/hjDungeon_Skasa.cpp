#include "hjDungeon_Skasa.h"
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
#include "hjAnimator.h"
#include "hjInput.h"
#include "hjRigidbody.h"


#include "hjCommonPortalScript.h"
#include "hjPortalScript.h"
#include "hjSceneManager.h"
#include "hjPlayer.h"

namespace hj
{
	Dungeon_Skasa::Dungeon_Skasa()
	{

	}
	Dungeon_Skasa::~Dungeon_Skasa()
	{

	}
	void Dungeon_Skasa::Initialize()
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
			gate->GetComponent<Transform>()->SetPosition(Vector3(100.0f, 0.0f, 400.000f));

			gate->GetComponent<Transform>()->SetVirtualZ(250.0f);

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<CommonPortalScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetPortal(L"SkasaPortal", Vector2(200.0f, 0.0f)); 
			portal->SetDestination(L"SkasaEntrancePortal2");
			gate->SetState(GameObject::eState::Paused);
		}
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
			camera->AddComponent<CameraScript>();
			camera->GetComponent<Camera>()->RegisterTarget(player);
			camera->GetComponent<Camera>()->SetTarget(L"SwordMan2");
			renderer::cameras.push_back(cameraComp);

			cameraComp->setMaxXY(Vector2(3580.0f, 1340.0f));

		}
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		// UI Camera 
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::BackGround, false);

		}
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

	void Dungeon_Skasa::Update()
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

	void Dungeon_Skasa::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Dungeon_Skasa::Render()
	{
		Scene::Render();
	}
	void Dungeon_Skasa::OnEnter()
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
	void Dungeon_Skasa::OnExit()
	{
		Player* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{
			EraseGameObject(eLayerType::Player, (GameObject*)player);
			player->ExitScene();
		}
	}
}