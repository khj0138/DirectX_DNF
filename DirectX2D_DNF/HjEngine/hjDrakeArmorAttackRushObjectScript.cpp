#include "hjDrakeArmorAttackRushObjectScript.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
#include "hjGameObject.h"
namespace hj
{

	DrakeArmorAttackRushObjectScript::DrakeArmorAttackRushObjectScript()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DrakeArmorAttackRushObjectScript::~DrakeArmorAttackRushObjectScript()
	{
	}
	void DrakeArmorAttackRushObjectScript::Initialize()
	{
		AttackObjectScript::Initialize();
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(200.0f, 600.0f));

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(100.0f, 100.0f, 180.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		//col->SetType(eColliderType::Rect);
		col->SetType(eColliderType::Circle);
		col->SetSize(Vector2(100.0f, 100.0f), 0.0f);
		col->SetCenter(Vector2(0.0f, 0.0f));
		col->SetCollisionHeight(0.0f);
	}
	void DrakeArmorAttackRushObjectScript::Update()
	{
		AttackObjectScript::Update();
	}



	void DrakeArmorAttackRushObjectScript::OnCollisionEnter(Collider2D* other)
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

	void DrakeArmorAttackRushObjectScript::OnCollisionStay(Collider2D* other)
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

	void DrakeArmorAttackRushObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
