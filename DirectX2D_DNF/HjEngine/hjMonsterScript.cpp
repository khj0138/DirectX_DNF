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
		, mCoolTime(-1.0f)
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

	void MonsterScript::LateUpdate()
	{
	}

	void MonsterScript::Render()
	{
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
	void MonsterScript::Hit(UINT damage, bool flip, Vector2 direction)
	{
		mStatus.HP > damage ? mStatus.HP = mStatus.HP - damage : mStatus.HP = 0;

		
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();
		if (flip)
		{
			direction.x *= -1.f;
		}
			
		if (GetMonsterState() != eMonsterState::Hit)
		{
			if (mStatus.HP == 0)
			{
				mCurTime = 0.0f;

				SetMonsterState(eMonsterState::Die);
				GetOwner()->GetComponent<Collider2D>()->GetMesh()->SetActivate(false);
				GetAtkManager()->SetPause();
			}
			else
			{
				if (!mStatus.SuperArmor && GetMonsterState() != eMonsterState::Attack)
				{
					GetOwner()->SetFlip(!flip);
					SetMonsterState(eMonsterState::Hit);
					rb->SetVelocity(Vector3(direction.x, direction.y, vel.z));
					if (rb->GetGround() && direction.y > 0.0f)
						rb->SetGround(false);
				}
			}
		}
		else
		{
			
			if (rb->GetGround())
			{
				if (mStatus.HP == 0)
				{
					mCurTime = 0.0f;

					SetMonsterState(eMonsterState::Die);
					GetOwner()->GetComponent<Collider2D>()->GetMesh()->SetActivate(false);
					GetAtkManager()->SetPause();
				}
				else
				{
					if (!mStatus.SuperArmor)
					{
						GetOwner()->SetFlip(!flip);
						if (direction.y > 0.0f)
							rb->SetGround(false);
						rb->SetVelocity(Vector3(direction.x, direction.y, vel.z));
					}
				}
			}
			else
			{
				if (!mStatus.SuperArmor)
				{
					GetOwner()->SetFlip(!flip);
					rb->SetVelocity(Vector3(direction.x, direction.y + vel.y, vel.z));
				}
			}
		}
	}
}
