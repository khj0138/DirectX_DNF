//#include "hjBasicAttackObject2.h"
//#include "hjTransform.h"
//#include "hjGameObject.h"
//#include "hjTime.h"
//#include "hjInput.h"
//#include "hjCamera.h"
//#include "hjAnimator.h"
//#include "hjRigidbody.h"
//#include "hjCollider2D.h"
////#include "hjBehaviorTree.h"
//
//namespace hj
//{
//
//	BasicAttackObject2::BasicAttackObject2()
//	{
//		SetAnimate(false);
//		SetActivate(false);
//		SetAttack(false);
//		//SetAttackHeight(Vector2::Zero);
//		SetVelocity(Vector2::Zero);
//	}
//	BasicAttackObject2::~BasicAttackObject2()
//	{
//	}
//	void BasicAttackObject2::Initialize()
//	{
//		AttackObject::Initialize();
//		Transform* tr = GetComponent<Transform>();
//		tr->SetScale(Vector3(150.0f, 150.0f, 1.0f));
//		Collider2D* col = GetComponent<Collider2D>();
//		col->SetSize(Vector2(150.0f, 150.0f), 70.0f);
//		//SetAttackHeight(30.0f);
//		GetComponent<Collider2D>()->SetSize(Vector2(150.0f, 150.0f), 70.0f);
//		GetComponent<Collider2D>()->SetCollisionHeight(30.0f);
//	}
//	void BasicAttackObject2::Update()
//	{
//		AttackObject::Update();
//	}
//	void BasicAttackObject2::LateUpdate()
//	{
//		AttackObject::LateUpdate();
//	}void BasicAttackObject2::Render()
//	{
//		AttackObject::Render();
//	}
//	void BasicAttackObject2::OnCollisionEnter(Collider2D* other)
//	{
//		if (GetAttack())
//		{
//			std::map<UINT32, float>::iterator iter = findTarget(other->GetColliderID());
//			UINT32 targetID = other->GetColliderID();
//			//float coolTime = GetCoolTime();
//			if (!existTarget(targetID))
//			{
//				registerTarget(targetID);
//				// 공격 코드
//			}
//			//if (findTarget(targetID)->second >= coolTime)
//			//{
//			//	// 공격 코드
//			//	setTargetZero(targetID)
//			//}
//
//		}
//	}
//
//	void BasicAttackObject2::OnCollisionStay(Collider2D* other)
//	{
//		if (GetAttack())
//		{
//			std::map<UINT32, float>::iterator iter = findTarget(other->GetColliderID());
//			UINT32 targetID = other->GetColliderID();
//			//float coolTime = GetCoolTime();
//			if (!existTarget(targetID))
//			{
//				registerTarget(targetID);
//				// 공격 코드
//			}
//			//if (findTarget(targetID)->second >= coolTime)
//			//{
//			//	// 공격 코드
//			//	setTargetZero(targetID)
//			//}
//
//		}
//	}
//
//	void BasicAttackObject2::OnCollisionExit(Collider2D* other)
//	{
//	}
//}
