#include "hjDragonSoldierAttackObject1Script.h"
#include "hjAttackObject.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayer.h"
namespace hj
{

	DragonSoldierAttackObject1Script::DragonSoldierAttackObject1Script()
	{

	}
	DragonSoldierAttackObject1Script::~DragonSoldierAttackObject1Script()
	{
	}
	void DragonSoldierAttackObject1Script::Initialize()
	{
		AttackObjectScript::Initialize();
		mOwner->SetState(GameObject::eState::Paused);

		mOwner->SetAnimate(false);
		mOwner->SetAttack(false);
		mOwner->SetVelocity(Vector2::Zero);
		mOwner->SetStatus(5, 2);

		Transform* tr = mOwner->GetComponent<Transform>();
		tr->SetScale(Vector3(100.0f, 100.0f, 1.0f));
		Collider2D* col = mOwner->GetComponent<Collider2D>();
		col->SetSize(Vector2(100.0f, 100.0f), 70.0f);
		col->SetCenter(Vector2(50.0f, 0.0f));
		col->SetCollisionHeight(30.0f);

	}
	void DragonSoldierAttackObject1Script::Update()
	{
		AttackObjectScript::Update();
	}



	void DragonSoldierAttackObject1Script::OnCollisionEnter(Collider2D* other)
	{
		Player* target = dynamic_cast<Player*>(other->GetOwner());
		if (target != nullptr)
		{
			if (mOwner->GetAttack())
			{
				std::map<UINT32, float>::iterator iter = mOwner->findTarget(other->GetColliderID());
				UINT32 targetID = other->GetColliderID();
				//float coolTime = GetCoolTime();
				if (!(mOwner->existTarget(targetID)))
				{
					mOwner->registerTarget(targetID);
					// 공격 코드
					Attack(target);
				}
				//if (findTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void DragonSoldierAttackObject1Script::OnCollisionStay(Collider2D* other)
	{
		Player* target = dynamic_cast<Player*>(other->GetOwner());
		if (target != nullptr)
		{
			if (mOwner->GetAttack())
			{
				std::map<UINT32, float>::iterator iter = mOwner->findTarget(other->GetColliderID());
				UINT32 targetID = other->GetColliderID();
				//float coolTime = GetCoolTime();
				if (!(mOwner->existTarget(targetID)))
				{
					mOwner->registerTarget(targetID);
					// 공격 코드
					Attack(target);
				}
				//if (findTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void DragonSoldierAttackObject1Script::OnCollisionExit(Collider2D* other)
	{
	}

	void DragonSoldierAttackObject1Script::Attack(Player* target)
	{
		AttackObjectScript::Attack(target);
	}

}
