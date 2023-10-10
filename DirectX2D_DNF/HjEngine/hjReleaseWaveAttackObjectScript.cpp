#include "hjReleaseWaveAttackObjectScript.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjAnimator.h"
#include "hjRigidbody.h"
namespace hj
{

	ReleaseWaveAttackObjectScript::ReleaseWaveAttackObjectScript()
		: AttackObjectScript(AttackObjectType::Player)
	{

	}
	ReleaseWaveAttackObjectScript::~ReleaseWaveAttackObjectScript()
	{
	}
	void ReleaseWaveAttackObjectScript::Initialize()
	{
		GetOwner()->SetState(GameObject::eState::Paused);

		Animator* mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2(-46.0f, -50.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\ReleaseWave\\Wave", 0.05f, Vector2(0.0f, 00.0f));
		AttackObjectScript::Initialize();

		SetAnimate(true);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f,500.0f));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(412.0f, 379.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetSize(Vector2(200.0f, 200.0f), 200.0f);
		col->SetCenter(Vector2(0.0f, 0.0f));
		col->SetCollisionHeight(0.0f);
	}






	void ReleaseWaveAttackObjectScript::Update()
	{
		AttackObjectScript::Update();
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		if (mAnimator->GetActiveAnimation()->IsComplete())
			GetOwner()->SetState(GameObject::eState::Paused);
	}



	void ReleaseWaveAttackObjectScript::OnCollisionEnter(Collider2D* other)
	{
		MonsterScript* target = other->GetOwner()->FindScript<MonsterScript>();

		if (target != nullptr)
		{
			if (GetAttack())
			{
				std::map<UINT32, float>::iterator iter = FindTarget(other->GetColliderID());
				UINT32 targetID = other->GetColliderID();
				//float coolTime = GetCoolTime();
				if (!(existTarget(targetID)))
				{
					registerTarget(targetID);
					// 공격 코드
					Attack(target);
				}
				//if (FindTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void ReleaseWaveAttackObjectScript::OnCollisionStay(Collider2D* other)
	{
		MonsterScript* target = other->GetOwner()->FindScript<MonsterScript>();

		if (target != nullptr)
		{
			if (GetAttack())
			{
				std::map<UINT32, float>::iterator iter = FindTarget(other->GetColliderID());
				UINT32 targetID = other->GetColliderID();
				//float coolTime = GetCoolTime();
				if (!(existTarget(targetID)))
				{
					registerTarget(targetID);
					// 공격 코드
					Attack(target);
				}
				//if (FindTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void ReleaseWaveAttackObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
