#include "hjBasicAddAttackObject3Script.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjAnimator.h"
#include "hjRigidbody.h"
namespace hj
{

	BasicAddAttackObject3Script::BasicAddAttackObject3Script()
		: AttackObjectScript(AttackObjectType::Player)
	{

	}
	BasicAddAttackObject3Script::~BasicAddAttackObject3Script()
	{
	}
	void BasicAddAttackObject3Script::Initialize()
	{
		GetOwner()->SetState(GameObject::eState::Paused);
		Animator* mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2(0.0f, -28.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\Addwave\\Addwave3", 0.05f, Vector2(0.0f, 00.0f));
		AttackObjectScript::Initialize();
		SetAnimate(true);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(1, 1, Vector2(100.0f, 0.0f));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		tr->SetScale(Vector3(582.0f, 455.0f, 1.0f));
		col->SetSize(Vector2(200.0f, 200.0f), 200.0f);
		col->SetCenter(Vector2(191.0f, 0.0f));
		col->SetCollisionHeight(0.0f);
	}






	void BasicAddAttackObject3Script::Update()
	{
		AttackObjectScript::Update();
	}



	void BasicAddAttackObject3Script::OnCollisionEnter(Collider2D* other)
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

	void BasicAddAttackObject3Script::OnCollisionStay(Collider2D* other)
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

	void BasicAddAttackObject3Script::OnCollisionExit(Collider2D* other)
	{
	}


}
