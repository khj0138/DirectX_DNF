#include "hjBasicAttackObject.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	BasicAttackObject::BasicAttackObject()
	{
		SetAnimate(false);
		SetActivate(false);
		SetAttack(false);
		SetAttackHeight(Vector2::Zero);
		SetVelocity(Vector2::Zero);
	}
	BasicAttackObject::~BasicAttackObject()
	{
	}
	void BasicAttackObject::Initialize()
	{
	}
	void BasicAttackObject::Update()
	{
		if (!GetActivate())
			return;
		else
		{
			
		}
	}

	void BasicAttackObject::OnCollisionEnter(Collider2D* other)
	{
		if (GetAttack())
		{
			std::map<UINT32, float>::iterator iter = findTarget(other->GetColliderID());
			UINT32 targetID = other->GetColliderID();
			float coolTime = GetCoolTime();
			if (!existTarget(targetID))
			{
				registerTarget(targetID);
				// 공격 코드
			}
			//if (findTarget(targetID)->second >= coolTime)
			//{
			//	// 공격 코드
			//	setTargetZero(targetID)
			//}
			
		}
	}

	void BasicAttackObject::OnCollisionStay(Collider2D* other)
	{
		if (GetAttack())
		{
			std::map<UINT32, float>::iterator iter = findTarget(other->GetColliderID());
			UINT32 targetID = other->GetColliderID();
			float coolTime = GetCoolTime();
			if (!existTarget(targetID))
			{
				registerTarget(targetID);
				// 공격 코드
			}
			//if (findTarget(targetID)->second >= coolTime)
			//{
			//	// 공격 코드
			//	setTargetZero(targetID)
			//}
			
		}
	}

	void BasicAttackObject::OnCollisionExit(Collider2D* other)
	{
	}
}
