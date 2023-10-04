#include "hjThrustAttackObjectScript.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"
namespace hj
{

	ThrustAttackObjectScript::ThrustAttackObjectScript()
		: AttackObjectScript(AttackObjectType::Player)
	{

	}
	ThrustAttackObjectScript::~ThrustAttackObjectScript()
	{
	}
	void ThrustAttackObjectScript::Initialize()
	{
		AttackObjectScript::Initialize();
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(1, 1, Vector2(300.0f, 000.0f));

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(150.0f, 50.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(150.0f, 50.0f), 70.0f);
		col->SetCenter(Vector2(75.0f, 0.0f));
		col->SetCollisionHeight(30.0f);

	}
	void ThrustAttackObjectScript::Update()
	{
		AttackObjectScript::Update();
	}



	void ThrustAttackObjectScript::OnCollisionEnter(Collider2D* other)
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

	void ThrustAttackObjectScript::OnCollisionStay(Collider2D* other)
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

	void ThrustAttackObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
