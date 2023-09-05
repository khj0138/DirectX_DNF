#include "hjDragonSoldierAttackObject2Script.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
namespace hj
{

	DragonSoldierAttackObject2Script::DragonSoldierAttackObject2Script()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DragonSoldierAttackObject2Script::~DragonSoldierAttackObject2Script()
	{
	}
	void DragonSoldierAttackObject2Script::Initialize()
	{
		AttackObjectScript::Initialize();
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(100.0f, 100.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetSize(Vector2(100.0f, 100.0f), 70.0f);
		col->SetCenter(Vector2(50.0f, 0.0f));
		col->SetCollisionHeight(30.0f);

	}
	void DragonSoldierAttackObject2Script::Update()
	{
		AttackObjectScript::Update();
	}



	void DragonSoldierAttackObject2Script::OnCollisionEnter(Collider2D* other)
	{
		PlayerScript* target = other->GetOwner()->FindScript<PlayerScript>();
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

	void DragonSoldierAttackObject2Script::OnCollisionStay(Collider2D* other)
	{
		PlayerScript* target = other->GetOwner()->FindScript<PlayerScript>();
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

	void DragonSoldierAttackObject2Script::OnCollisionExit(Collider2D* other)
	{
	}

}
