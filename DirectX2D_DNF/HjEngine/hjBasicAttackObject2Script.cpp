#include "hjBasicAttackObject2Script.h"
#include "hjAttackObject.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
namespace hj
{

	BasicAttackObject2Script::BasicAttackObject2Script()
	{

	}
	BasicAttackObject2Script::~BasicAttackObject2Script()
	{
	}
	void BasicAttackObject2Script::Initialize()
	{
		AttackObjectScript::Initialize();

		mOwner->SetAnimate(false);
		mOwner->SetActivate(false);
		mOwner->SetAttack(false);
		mOwner->SetVelocity(Vector2::Zero);
		mOwner->SetStatus(10, 5);


		Transform* tr = mOwner->GetComponent<Transform>();
		tr->SetScale(Vector3(150.0f, 150.0f, 1.0f));
		Collider2D* col = mOwner->GetComponent<Collider2D>();
		col->SetSize(Vector2(150.0f, 150.0f), 70.0f);
		col->SetCenter(Vector2(75.0f, 0.0f));
		col->SetCollisionHeight(30.0f);

	}
	void BasicAttackObject2Script::Update()
	{

		AttackObjectScript::Update();
	}



	void BasicAttackObject2Script::OnCollisionEnter(Collider2D* other)
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
			}
			//if (findTarget(targetID)->second >= coolTime)
			//{
			//	// 공격 코드
			//	setTargetZero(targetID)
			//}

		}
	}

	void BasicAttackObject2Script::OnCollisionStay(Collider2D* other)
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
			}

		}
	}

	void BasicAttackObject2Script::OnCollisionExit(Collider2D* other)
	{
	}

	void BasicAttackObject2Script::Attack(Monster* target)
	{
		AttackObjectScript::Attack(target);
	}

}
