#include "hjBasicAddAttackObject1Script.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjAnimator.h"
#include "hjRigidbody.h"
namespace hj
{

	BasicAddAttackObject1Script::BasicAddAttackObject1Script()
		: AttackObjectScript(AttackObjectType::Player)
	{

	}
	BasicAddAttackObject1Script::~BasicAddAttackObject1Script()
	{
	}
	void BasicAddAttackObject1Script::Initialize()
	{
		GetOwner()->SetState(GameObject::eState::Paused);

		Animator* mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\Addwave\\Addwave1", 0.03f, Vector2(0.0f, 00.0f));
		AttackObjectScript::Initialize();

		SetAnimate(true);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f, 0.0f));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(468.0f, 423.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetSize(Vector2(120.0f, 120.0f), 120.0f);
		col->SetCenter(Vector2(174.0f, 0.0f));
		col->SetCollisionHeight(0.0f);
	}






	void BasicAddAttackObject1Script::Update()
	{
		AttackObjectScript::Update();
	}



	void BasicAddAttackObject1Script::OnCollisionEnter(Collider2D* other)
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

	void BasicAddAttackObject1Script::OnCollisionStay(Collider2D* other)
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

	void BasicAddAttackObject1Script::OnCollisionExit(Collider2D* other)
	{
	}


}
