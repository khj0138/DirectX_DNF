#include "hjTown_SeriaRoom.h"
#include "hjSceneManager.h"
//#include "hjPlayScene.h"
#include "hjTransform.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"
#include "hjMesh.h"
#include "hjCameraScript.h"
#include "hjCamera.h"
#include "hjGridScript.h"
#include "hjPlayerScript.h"
#include "hjSeriaRoomGateScript.h"
#include "hjRenderer.h"
//#include "hjObject.h"
#include "hjCollider2D.h"
#include "hjCollisionManager.h"
#include "hjAnimator.h"
#include "hjInput.h"
#include "hjRigidbody.h"
#include "hjPlayer.h"

#include "hjDragonSoldier.h"

#include "hjLight.h"
#include "hjComputeShader.h"
#include "hjPaintShader.h"
#include "hjParticleSystem.h"

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
		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();


		/*GameObject* smile = new GameObject();
		smile->SetName(L"smile");
		AddGameObject(eLayerType::Monster, smile);
		MeshRenderer* mr = smile->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"PaintMaterial"));
		smile->GetComponent<Transform>()->SetPosition(Vector3(500.0f, 500.0f, 2.0f));
		*/

		GameObject* particle = new GameObject();
		particle->SetName(L"Particle");
		AddGameObject(eLayerType::Monster, particle);
		ParticleSystem* particleSys = particle->AddComponent<ParticleSystem>();
		particle->GetComponent<Transform>()->SetPosition(Vector3(500.0f, 500.0f, 2.0f));
		particle->GetComponent<Transform>()->SetScale(Vector3(100.0f, 100.0f, 1.0f));
		//particle->GetComponent<Transform>()->SetPosition(Vector3(00.0f,0.0f, 1.0f));
		//particle->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 0.2f));
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

		//Player* player = new Player();
		////test = (GameObject*)player;
		//{
		//	player->Initialize();
		//	//player->GetComponent<Transform>()->SetScale(Vector3{ 320.0f, 320.0f, 2.0f });
		//	AddGameObject(eLayerType::Player, player);
		//	player->GetComponent<Transform>()->SetPosition(Vector3(500.0f, 0.0f, 1.000f));
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


		}
		DragonSoldier* dragon = new DragonSoldier();
		AddGameObject(eLayerType::Monster, dragon);
		dragon->GetComponent<Transform>()->SetPosition(Vector3(400.0f, 0.0f, 2.000f));
		dragon->Initialize();
		dragon->EnterScene();

		/*DragonSoldier* dragon2 = new DragonSoldier();
		AddGameObject(eLayerType::Monster, dragon2);
		dragon2->GetComponent<Transform>()->SetPosition(Vector3(400.0f, 0.0f, 2.000f));
		dragon2->Initialize();*/
		
		/*{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
			lightComp->SetRadius(3.0f);
		}*/
		
		// MainCamera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3((800.0f + 0.0f) * 1.0f, (450.0f + 0.0f) * 1.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->TurnLayerMask(eLayerType::PlayerAttack, true);
			cameraComp->TurnLayerMask(eLayerType::Monster, true);
			camera->AddComponent<CameraScript>();
			//camera->GetComponent<Camera>()->RegisterTarget(player);
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;


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
		Scene::LateUpdate();
	}

	void Town_SeriaRoom::Render()
	{
		Scene::Render();
	}
	void Town_SeriaRoom::OnEnter()
	{
		Player* player = SceneManager::GetPlayer();
		player->EnterScene();
		AddGameObject(eLayerType::Player, (GameObject*)player);
		player->GetComponent<Transform>()->SetPosition(Vector3(500.0f, 0.0f, 1.000f));
	}
	void Town_SeriaRoom::OnExit()
	{
		Player* player = SceneManager::GetPlayer();
		EraseGameObject(eLayerType::Player, (GameObject*)player);
		player->ExitScene();
	}
}