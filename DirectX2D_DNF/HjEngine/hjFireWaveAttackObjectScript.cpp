#include "hjFireWaveAttackObjectScript.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjAnimator.h"
#include "hjRigidbody.h"
namespace hj
{

	FireWaveAttackObjectScript::FireWaveAttackObjectScript()
		: AttackObjectScript(AttackObjectType::Player)
	{

	}
	FireWaveAttackObjectScript::~FireWaveAttackObjectScript()
	{
	}
	void FireWaveAttackObjectScript::Initialize()
	{
		GetOwner()->SetState(GameObject::eState::Paused);

		Animator* mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2(0.0f, -100.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\FireWave\\Wave", 0.07f, Vector2(0.0f, 00.0f));
		AttackObjectScript::Initialize();

		SetAnimate(true);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f, 500.0f));

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(479.0f, 565.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetSize(Vector2(180.0f, 180.0f), 240.0f);
		col->SetCenter(Vector2(94.0f, 0.0f));
		col->SetCollisionHeight(0.0f);
	}






	void FireWaveAttackObjectScript::Update()
	{
		AttackObjectScript::Update();
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		if (mAnimator->GetActiveAnimation()->IsComplete())
			GetOwner()->SetState(GameObject::eState::Paused);
	}



	void FireWaveAttackObjectScript::OnCollisionEnter(Collider2D* other)
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

	void FireWaveAttackObjectScript::OnCollisionStay(Collider2D* other)
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

	void FireWaveAttackObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
