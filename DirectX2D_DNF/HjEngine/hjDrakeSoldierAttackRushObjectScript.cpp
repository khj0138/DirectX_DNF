#include "hjDrakeSoldierAttackRushObjectScript.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjRigidBody.h"
#include "hjPlayerScript.h"
#include "hjGameObject.h"
namespace hj
{

	DrakeSoldierAttackRushObjectScript::DrakeSoldierAttackRushObjectScript()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DrakeSoldierAttackRushObjectScript::~DrakeSoldierAttackRushObjectScript()
	{
	}
	void DrakeSoldierAttackRushObjectScript::Initialize()
	{
		AttackObjectScript::Initialize();
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f, 0.0f));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(150.0f, 50.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(150.0f, 50.0f), 60.0f);
		col->SetCenter(Vector2(50.0f, 0.0f));
		col->SetCollisionHeight(40.0f);

	}
	void DrakeSoldierAttackRushObjectScript::Update()
	{
		AttackObjectScript::Update();
		
	}



	void DrakeSoldierAttackRushObjectScript::OnCollisionEnter(Collider2D* other)
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

	void DrakeSoldierAttackRushObjectScript::OnCollisionStay(Collider2D* other)
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

	void DrakeSoldierAttackRushObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
