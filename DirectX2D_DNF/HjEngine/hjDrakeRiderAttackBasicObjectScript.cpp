#include "hjDrakeRiderAttackBasicObjectScript.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
#include "hjGameObject.h"
namespace hj
{

	DrakeRiderAttackBasicObjectScript::DrakeRiderAttackBasicObjectScript()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DrakeRiderAttackBasicObjectScript::~DrakeRiderAttackBasicObjectScript()
	{
	}
	void DrakeRiderAttackBasicObjectScript::Initialize()
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
		col->SetType(eColliderType::Rect);
		//col->SetType(eColliderType::Circle);
		col->SetSize(Vector2(260.0f, 100.0f), 70.0f);
		col->SetCenter(Vector2(130.0f, 0.0f));
		col->SetCollisionHeight(30.0f);
	}
	void DrakeRiderAttackBasicObjectScript::Update()
	{
		AttackObjectScript::Update();
	}



	void DrakeRiderAttackBasicObjectScript::OnCollisionEnter(Collider2D* other)
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

	void DrakeRiderAttackBasicObjectScript::OnCollisionStay(Collider2D* other)
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

	void DrakeRiderAttackBasicObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
