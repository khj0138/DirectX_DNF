#include "hjMonster.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"

#include "hjAttackScriptManager.h"
#include "hjDetectScript.h"
#include "hjPlayer.h"
//#include "hjBehaviorTree.h"

namespace hj
{
	Monster::Monster()
		: mActivate(false)
	{
	}
	Monster::~Monster()
	{
		delete AtkManager;
	}
	void Monster::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		AddComponent<Animator>();
		AddComponent<Collider2D>();
		AddComponent<Rigidbody>();

		AtkManager = new AttackScriptManager();
		AtkManager->SetManagerOwner(this);
		AtkManager->SetType(eLayerType::MonsterAttack);
		AtkManager->RegisterAttackScript<DetectScript>(L"Detect");
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}

	void Monster::LateUpdate()
	{
		AttackScript* atkScript = AtkManager->LoadAttackScript(L"Detect");
		if (atkScript != nullptr)
		{
			DetectScript* dtScript = dynamic_cast<DetectScript*>(atkScript);
			if (dtScript != nullptr)
			{
				if (mTarget == nullptr)
					mTarget = dtScript->GetTarget();
				if (mTarget != nullptr)
					int a = 0;
			}
		}
		GameObject::LateUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();

	}

	/*void Monster::OnCollisionEnter(Collider2D* other)
	{
	}

	void Monster::OnCollisionStay(Collider2D* other)
	{
	}

	void Monster::OnCollisionExit(Collider2D* other)
	{
	}*/
	void Monster::EnterScene()
	{
		AtkManager->EnterScene();
	}
	void Monster::ExitScene()
	{
		AtkManager->ExitScene();
	}
}
