#include "hjDrakeRiderAttackBreathObjectScript.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
#include "hjGameObject.h"
namespace hj
{

	DrakeRiderAttackBreathObjectScript::DrakeRiderAttackBreathObjectScript()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DrakeRiderAttackBreathObjectScript::~DrakeRiderAttackBreathObjectScript()
	{
	}
	void DrakeRiderAttackBreathObjectScript::Initialize()
	{
		AttackObjectScript::Initialize();
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f, 00.0f));
		SetCoolTime(0.5f);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(300.0f, 100.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		//col->SetType(eColliderType::Circle);
		col->SetSize(Vector2(300.0f, 100.0f), 70.0f);
		col->SetCenter(Vector2(250.0f, 0.0f));
		col->SetCollisionHeight(30.0f);
	}
	void DrakeRiderAttackBreathObjectScript::Update()
	{
		AttackObjectScript::Update();
	}



	void DrakeRiderAttackBreathObjectScript::OnCollisionEnter(Collider2D* other)
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
					setTargetZero(targetID);

				}
				else
				{
					if (FindTarget(targetID)->second >= GetCoolTime())
					{
						Attack(target);
						setTargetZero(targetID);
					}
				}
				//if (FindTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void DrakeRiderAttackBreathObjectScript::OnCollisionStay(Collider2D* other)
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
					setTargetZero(targetID);

				}
				else
				{
					if (FindTarget(targetID)->second >= GetCoolTime())
					{
						Attack(target);
						setTargetZero(targetID);
					}
				}
				//if (FindTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void DrakeRiderAttackBreathObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
