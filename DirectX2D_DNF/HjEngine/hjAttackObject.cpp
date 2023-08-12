#include "hjAttackObject.h"
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
	AttackObject::AttackObject()
		: bActivate(false)
		, mCoolTime(0.0f)
		, bAnimate(false)
		, attackHeight(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, animOffset(Vector2::Zero)
		, mAnimator(nullptr)
	{
	}
	AttackObject::~AttackObject()
	{
	}
	void AttackObject::Initialize()
	{
	}
	void AttackObject::Update()
	{
		
	}

	void AttackObject::OnCollisionEnter(Collider2D* other)
	{
		
	}

	void AttackObject::OnCollisionStay(Collider2D* other)
	{
		
	}

	void AttackObject::OnCollisionExit(Collider2D* other)
	{
	}

	void AttackObject::SetActivate(bool activate)
	{
		
	}



}
