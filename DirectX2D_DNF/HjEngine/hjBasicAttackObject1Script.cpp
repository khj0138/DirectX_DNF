#include "hjBasicAttackObject1Script.h"
#include "hjAttackObject.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
namespace hj
{

	BasicAttackObject1Script::BasicAttackObject1Script()
	{
		
	}
	BasicAttackObject1Script::~BasicAttackObject1Script()
	{
	}
	void BasicAttackObject1Script::Initialize()
	{
		AttackObjectScript::Initialize();

		mOwner->SetAnimate(false);
		mOwner->SetActivate(false);
		mOwner->SetAttack(false);
		mOwner->SetVelocity(Vector2::Zero);

		Transform* tr = mOwner->GetComponent<Transform>();
		tr->SetScale(Vector3(150.0f, 150.0f, 1.0f));
		Collider2D* col = mOwner->GetComponent<Collider2D>();
		col->SetSize(Vector2(150.0f, 150.0f), 70.0f);
		col->SetCollisionHeight(30.0f);

	}
	void BasicAttackObject1Script::Update()
	{
		AttackObjectScript::Update();
	}



	void BasicAttackObject1Script::OnCollisionEnter(Collider2D* other)
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

	void BasicAttackObject1Script::OnCollisionStay(Collider2D* other)
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

	void BasicAttackObject1Script::OnCollisionExit(Collider2D* other)
	{
	}

}
