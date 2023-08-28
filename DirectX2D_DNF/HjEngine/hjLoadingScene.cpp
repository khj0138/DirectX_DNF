#include "hjLoadingScene.h"
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

#include "hjTime.h"
#include "hjPlayer.h"
#include "hjSceneManager.h"


#include "hjApplication.h"

extern hj::Application application;
namespace hj
{
	LoadingScene::LoadingScene()
	{

	}
	LoadingScene::~LoadingScene()
	{

	}
	void LoadingScene::Initialize()
	{
		float fixedRes = (float)application.GetFixedWidth() / 800.f;
		// MainCamera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3((800.0f + 0.0f) * 1.0f, (450.0f + 0.0f), -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BackGround, true);
			cameraComp->setMinXY(Vector2::Zero);
			cameraComp->setMaxXY(Vector2(1600.0f, 900.0f));
			camera->AddComponent<CameraScript>();
			
			renderer::cameras.push_back(cameraComp);
		}

	}

	void LoadingScene::Update()
	{
		
		Scene::Update();
	}

	void LoadingScene::LateUpdate()
	{
		GameObject* effect = GetLayer(eLayerType::BackGround).FindObject(L"LoadingSceneEffect");
		float rotate = math::radianToDegree(effect->GetComponent<Transform>()->GetRotation().z);
		rotate += Time::DeltaTime() * -360.0f;
		 
		effect->GetComponent<Transform>()->SetRotation2D(rotate);

		Scene::LateUpdate();

		if (rotate < -1440.0f)
		{
			SceneManager::LoadScene(L"Town_SeriaRoom");

		}
	}

	void LoadingScene::Render()
	{
		Scene::Render();
		
	}

	void LoadingScene::OnEnter()
	{
	}

	void LoadingScene::OnExit()
	{
	}

}