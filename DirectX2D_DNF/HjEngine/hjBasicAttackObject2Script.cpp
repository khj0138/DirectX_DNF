#include "hjBasicAttackObject2Script.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

namespace hj
{

	BasicAttackObject2Script::BasicAttackObject2Script()
		: AttackObjectScript(AttackObjectType::Player)
	{

	}
	BasicAttackObject2Script::~BasicAttackObject2Script()
	{
	}
	void BasicAttackObject2Script::Initialize()
	{
		AttackObjectScript::Initialize();
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);

		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(1, 1, Vector2(100.0f, 000.0f));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(100.0f, 100.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetSize(Vector2(100.0f, 100.0f), 70.0f);
		col->SetCenter(Vector2(75.0f, 0.0f));
		col->SetCollisionHeight(30.0f);

	}
	void BasicAttackObject2Script::Update()
	{

		AttackObjectScript::Update();
	}



	void BasicAttackObject2Script::OnCollisionEnter(Collider2D* other)
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

	void BasicAttackObject2Script::OnCollisionStay(Collider2D* other)
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

	void BasicAttackObject2Script::OnCollisionExit(Collider2D* other)
	{
	}


}
