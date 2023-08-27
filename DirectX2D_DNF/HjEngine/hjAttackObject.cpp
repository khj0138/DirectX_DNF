#include "hjAttackObject.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"
#include "hjAttackScript.h"
//#include "hjBehaviorTree.h"

namespace hj
{
	AttackObject::AttackObject()
		: bActivate(false)
		, mCoolTime(0.0f)
		, bAnimate(false)
		//, attackHeight(Vector2::Zero)
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
		if (!bActivate)
			return;
		GameObject::Update();
	}
	void AttackObject::LateUpdate()
	{
		if (!bActivate)
			return;
		GameObject::LateUpdate();
	}
	void AttackObject::Render()
	{
		if (!bActivate)
			return;
		GameObject::Render();
	}
	



}
