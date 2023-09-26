#include "hjDrakeArmorAttackBasicObjectScript.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
#include "hjGameObject.h"
namespace hj
{

	DrakeArmorAttackBasicObjectScript::DrakeArmorAttackBasicObjectScript()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DrakeArmorAttackBasicObjectScript::~DrakeArmorAttackBasicObjectScript()
	{
	}
	void DrakeArmorAttackBasicObjectScript::Initialize()
	{
		AttackObjectScript::Initialize();
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f, 00.0f));

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(200.0f, 100.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		//col->SetType(eColliderType::Rect);
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(100.0f, 100.0f), 80.0f);
		col->SetCenter(Vector2(50.0f, 0.0f));
		col->SetCollisionHeight(100.0f);
	}
	void DrakeArmorAttackBasicObjectScript::Update()
	{
		AttackObjectScript::Update();
	}



	void DrakeArmorAttackBasicObjectScript::OnCollisionEnter(Collider2D* other)
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

	void DrakeArmorAttackBasicObjectScript::OnCollisionStay(Collider2D* other)
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

	void DrakeArmorAttackBasicObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
