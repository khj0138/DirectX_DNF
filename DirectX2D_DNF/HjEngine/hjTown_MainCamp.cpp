#include "hjTown_MainCamp.h"
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

#include "hjSeriaRoomGateScript.h"
#include "hjPortalScript.h"
#include "hjSceneManager.h"
#include "hjPlayer.h"
namespace hj
{
	Town_MainCamp::Town_MainCamp()
	{

	}
	Town_MainCamp::~Town_MainCamp()
	{

	}
	void Town_MainCamp::Initialize()
	{
		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"SwordMan");
		//	player->GetComponent<Transform>()->SetScale(Vector3{ 500.0f, 500.0f, 2.0f });
		//	player->GetComponent<Transform>()->SetPosition(Vector3(700.0f, 0.0f, 1.000f));
		//	player->GetComponent<Transform>()->SetCamMoveRate(0.5f);
		//	//player->GetComponent<Transform>()->SetRotation2D(60.0f);
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	Collider2D* cd = player->AddComponent<Collider2D>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//	
		//}

		//GameObject* player = new GameObject();
		////test = (GameObject*)player;
		//{
		//	player->GetComponent<Transform>()->SetScale(Vector3{ 500.0f, 500.0f, 2.0f });
		//	player->SetName(L"SwordMan2");
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		//	// mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(500.0f, 0.0f, 1.000f));

		//	//std::shared_ptr<Texture> atlas
		//	//	= Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");
		//	Animator* at = player->AddComponent<Animator>();
		//	/*at->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Idle", 0.1f);
		//	at->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Walk", 0.1f);
		//	at->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Run", 0.1f);
		//	at->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Jump", 0.2f);
		//	at->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack", 0.1f);*/


		//	//at->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\", 0.1f);
		//	//at->Plahjnimation(L"SwordManIdle", true);
		//	Collider2D* cd = player->AddComponent<Collider2D>();
		//	player->AddComponent<PlayerScript>();
		//	player->AddComponent<Rigidbody>();

		//	
		//}

		GameObject* gate = new GameObject();
		{
			gate->GetComponent<Transform>()->SetScale(Vector3{ 278.0f, 254.0f, 2.0f });
			gate->SetName(L"SeriaRoomGate");
			AddGameObject(eLayerType::BackGround, gate);
			MeshRenderer* mr = gate->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			gate->GetComponent<Transform>()->SetPosition(Vector3(638.0f, -23.0f, 450.000f));
			gate->GetComponent<Transform>()->YtoVirtualZ();

			Animator* at = gate->AddComponent<Animator>();

			Collider2D* cd = gate->AddComponent<Collider2D>();
			gate->AddComponent<SeriaRoomGateScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetPortal(L"MainCampPortal1", Vector2(-100.0f, 200.0f));
			portal->SetDestination(L"SeriaRoomPortal");
			//gate->AddComponent<GroundObjectScript>();

			//AudioSource* as = gate->AddComponent<AudioSource>();
			////as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\bakal_basecamp.OGG"));
			//as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\0.mp3"));
			//as->Play();
		}
		// MainCamera
		Player* player = SceneManager::GetPlayer();
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3((800.0f + 0.0f) * 1.0f, (450.0f + 0.0f) * 1.0f, -10.0f));
			//camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->setMaxXY(Vector2(3580.0f, 1340.0f));
			camera->AddComponent<CameraScript>();
			camera->GetComponent<Camera>()->RegisterTarget(player);
			camera->GetComponent<Camera>()->SetTarget(L"SwordMan2");
			renderer::cameras.push_back(cameraComp);
			

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

	void Town_MainCamp::Update()
	{

		Scene::Update();
	}

	void Town_MainCamp::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Town_MainCamp::Render()
	{
		Scene::Render();
	}
	void Town_MainCamp::OnEnter()
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
	void Town_MainCamp::OnExit()
	{
		Player* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{
			EraseGameObject(eLayerType::Player, (GameObject*)player);
			player->ExitScene();
		}
	}
}