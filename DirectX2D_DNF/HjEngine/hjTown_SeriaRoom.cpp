#include "hjTown_SeriaRoom.h"
#include "hjSceneManager.h"
#include "hjTransform.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"
#include "hjMesh.h"
#include "hjCameraScript.h"
#include "hjCamera.h"
#include "hjGridScript.h"
#include "hjPlayerScript.h"
#include "hjGateInSeriaRoomScript.h"
#include "hjRenderer.h"
#include "hjCollider2D.h"
#include "hjCollisionManager.h"
#include "hjAnimator.h"
#include "hjInput.h"
#include "hjRigidbody.h"


#include "hjLight.h"
#include "hjComputeShader.h"
#include "hjPaintShader.h"
#include "hjParticleSystem.h"

#include "hjAudioListener.h"
#include "hjAudioClip.h"
#include "hjAudioSource.h"
#include "hjGroundObjectScript.h"
#include "hjPortalScript.h"

#include "hjDrakeSoldierScript.h"
#include "hjDrakeArmorScript.h"
#include "hjDrakeRiderScript.h"
namespace hj
{
	Town_SeriaRoom::Town_SeriaRoom()
	{

	}
	Town_SeriaRoom::~Town_SeriaRoom()
	{

	}
	void Town_SeriaRoom::Initialize()
	{
		SetMinMax(Vector2(280.0f, 0.0f), Vector2(840.0f, 200.0f));

		GameObject* gate = new GameObject();
		{
			gate->GetComponent<Transform>()->SetScale(Vector3{278.0f, 254.0f, 2.0f});
			gate->SetName(L"GateInSeriaRoom");
			AddGameObject(eLayerType::BackGround, gate);
			MeshRenderer* mr = gate->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			gate->GetComponent<Transform>()->SetPosition(Vector3(638.0f, 0.0f, 450.000f));
			gate->GetComponent<Transform>()->SetVirtualZ(-46.0f);
			gate->AddComponent<Animator>();
			gate->AddComponent<Collider2D>();
			gate->AddComponent<GateInSeriaRoomScript>();
			PortalScript* portal = gate->AddComponent<PortalScript>();
			portal->SetDestination(L"Town_MainCamp", Vector2(320.0f, 200.0f));

			gate = new GameObject();
			gate->GetComponent<Transform>()->SetScale(Vector3{ 278.0f, 254.0f, 2.0f });
			gate->SetName(L"GateInSeriaRoom");
			AddGameObject(eLayerType::BackGround, gate);

			//MeshRenderer* mr = gate->AddComponent<MeshRenderer>();
			mr = gate->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			gate->GetComponent<Transform>()->SetPosition(Vector3(478.0f, 0.0f, 450.000f));
			gate->GetComponent<Transform>()->SetVirtualZ(-46.0f);
			gate->AddComponent<Animator>();
			gate->AddComponent<Collider2D>();
			gate->SetFlip(true);
			gate->AddComponent<GateInSeriaRoomScript>();
			//gate->AddComponent<GroundObjectScript>();

			//AudioSource* as = gate->AddComponent<AudioSource>();
			////as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\bakal_basecamp.OGG"));
			//as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\0.mp3"));
			//as->Play();
		}
		
		GameObject* monster = new GameObject();
		AddGameObject(eLayerType::Monster, monster);
		monster->GetComponent<Transform>()->SetPosition(Vector3(400.0f, 0.0f, 450.0f));
		monster->Initialize();
		monster->AddComponent<DrakeRiderScript>();
		monster->FindScript<DrakeRiderScript>()->EnterScene();
		//monster->AddComponent<DrakeArmorScript>();
		//monster->FindScript<DrakeArmorScript>()->EnterScene();
		
		PlayerScript* player = SceneManager::GetPlayer();
		// MainCamera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::UI, camera);
			//camera->GetComponent<Transform>()->SetPosition(Vector3((800.0f + 0.0f) * 1.0f, (450.0f + 0.0f) * 1.0f, -10.0f));
			camera->GetComponent<Transform>()->SetPosition(Vector3((800.0f + 0.0f) * 1.0f, (+ 0.0f) * 1.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->TurnLayerMask(eLayerType::PlayerAttack, true);
			cameraComp->TurnLayerMask(eLayerType::Monster, true);
			cameraComp->setMaxXY(Vector2(1115.0f, 600.0f));

			camera->AddComponent<CameraScript>();
			camera->GetComponent<Camera>()->RegisterTarget(player->GetOwner());
			camera->GetComponent<Camera>()->SetTarget(L"SwordMan2");
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
			//camera->AddComponent<AudioListener>();

		}
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BackGround, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::SetLayer(eLayerType::PlayerAttack, eLayerType::Monster, true);
		//// UI Camera 
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Player, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::Player, false);
		//	cameraComp->TurnLayerMask(eLayerType::BackGround, false);
		//	cameraComp->TurnLayerMask(eLayerType::Monster, false);


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

	void Town_SeriaRoom::Update()
	{

		Scene::Update();
	}

	void Town_SeriaRoom::LateUpdate()
	{
		PlayScene::LateUpdate();
	}

	void Town_SeriaRoom::Render()
	{
		Scene::Render();
	}
	void Town_SeriaRoom::OnEnter()
	{
		PlayerScript* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{
			player->EnterScene();
			AddGameObject(eLayerType::Player, player->GetOwner());
		}
	}
	void Town_SeriaRoom::OnExit()
	{
		PlayerScript* player = SceneManager::GetPlayer();
		if (player != nullptr)
		{
			EraseGameObject(eLayerType::Player, player->GetOwner());
			player->ExitScene();
		}
	}
}