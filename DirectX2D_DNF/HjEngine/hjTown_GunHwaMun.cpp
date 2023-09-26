#include "hjTown_GunHwaMun.h"
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




namespace hj
{
	Town_GunHwaMun::Town_GunHwaMun()
	{

	}
	Town_GunHwaMun::~Town_GunHwaMun()
	{

	}
	void Town_GunHwaMun::Initialize()
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
			gate->GetComponent<Transform>()->SetPosition(Vector3(050.0f, 0.0f, 450.0f));

			gate->GetComponent<Transform>()->SetVirtualZ(300.0f);

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<CommonPortalScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetDestination(L"Town_MainCamp", Vector2(1300.0f, 250.0f));
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
			gate->GetComponent<Transform>()->SetPosition(Vector3(1280.0f, 0.0f, 450.0f));

			gate->GetComponent<Transform>()->SetVirtualZ(300.0f);

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<CommonPortalScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetDestination(L"Dungeon_Entrance_1", Vector2(450.0f, 250.0f));
			gate->SetState(GameObject::eState::Paused);
		}
		PlayerScript* player = SceneManager::GetPlayer();

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
			camera->GetComponent<Camera>()->RegisterTarget(player->GetOwner());
			camera->GetComponent<Camera>()->SetTarget(L"SwordMan2");
			renderer::cameras.push_back(cameraComp);
			cameraComp->setMaxXY(Vector2(1340.0f, 670.0f));

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

	void Town_GunHwaMun::Update()
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

	void Town_GunHwaMun::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Town_GunHwaMun::Render()
	{
		Scene::Render();
	}
	void Town_GunHwaMun::OnEnter()
	{
		PlayerScript* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{
			player->EnterScene();
			AddGameObject(eLayerType::Player, player->GetOwner());
		}
	}
	void Town_GunHwaMun::OnExit()
	{
		PlayerScript* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{
			EraseGameObject(eLayerType::Player, player->GetOwner());
			player->ExitScene();
		}
	}
}