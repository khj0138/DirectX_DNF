#include "hjMonsterScript.h"
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

//#include "hjBehaviorTree.h"

namespace hj
{
	MonsterScript::MonsterScript()
		: mActivate(false)
		, mMonsterState(eMonsterState::Idle)
	{
	}
	MonsterScript::~MonsterScript()
	{
		delete AtkManager;
	}
	void MonsterScript::Initialize()
	{
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		GetOwner()->AddComponent<Animator>();
		GetOwner()->AddComponent<Collider2D>();
		GetOwner()->AddComponent<Rigidbody>();

		AtkManager = new AttackScriptManager();
		AtkManager->SetManagerOwner(GetOwner());
		AtkManager->SetType(eLayerType::MonsterAttack);
		AtkManager->RegisterAttackScript<DetectScript>(L"Detect");
	}
	void MonsterScript::Update()
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
	}


	void MonsterScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void MonsterScript::OnCollisionStay(Collider2D* other)
	{
	}

	void MonsterScript::OnCollisionExit(Collider2D* other)
	{
	}
	void MonsterScript::EnterScene()
	{
		AtkManager->EnterScene();
	}
	void MonsterScript::ExitScene()
	{
		AtkManager->ExitScene();
	}
}
