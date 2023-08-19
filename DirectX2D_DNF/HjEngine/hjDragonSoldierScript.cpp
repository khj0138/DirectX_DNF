#include "hjDragonSoldierScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
//#include "hjBehaviorTree.h"

#include "hjDragonSoldier.h"
#include "hjAttackScriptManager.h"
namespace hj
{

	DragonSoldierScript::DragonSoldierScript()
		: mDragonSoldierState(eDragonSoldierState::Idle)
		, mPrevDragonSoldierState(eDragonSoldierState::Idle)
		, mVelocity(Vector3::Zero)
	{
		


	}
	DragonSoldierScript::~DragonSoldierScript()
	{
	}
	void DragonSoldierScript::Initialize()
	{
		
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2{ 0.0f, -50.0f });

		mAnimator->PlayAnimation(L"dragon_soldierIdle", true);
		
		mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetSize(Vector2{ 75.0f, 75.0f }, 150.0f);

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		if (monster != nullptr)
		{
			mOwner = dynamic_cast<DragonSoldier*>(monster);
			AtkManager = monster->GetAtkManager();
		}
	}
	void DragonSoldierScript::Update()
	{
		switch (mDragonSoldierState)
		{
		case eDragonSoldierState::Idle:
			Idle();
			break;
		case eDragonSoldierState::Walk:
			Walk();
			break;
		case eDragonSoldierState::Attack:
			Attack();
			break;
		default:
			break;
		}

		Anim();
		if (Input::GetKeyDown(eKeyCode::P))
		{
			if (GetOwner()->GetComponent<Collider2D>()->GetCollision())
			{
				GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
			}
			else
			{
				GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			}
		}
		mPrevDragonSoldierState = mDragonSoldierState;

		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float posVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AtkManager->SetPosition(Vector2{ pos.x,pos.y }, posVZ);
		AtkManager->Update();
	}
	
	bool DragonSoldierScript::IsWalk()
	{
		Player* target = mOwner->GetTarget();
		if (target != nullptr)
		{
			return true;
		}
	}
	
	void DragonSoldierScript::Idle()
	{
		if (IsWalk())
		{

		}
	}
	void DragonSoldierScript::Walk()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();

		
		//{

		//	if (Input::GetKeyNone(eKeyCode::RIGHT)
		//		&& Input::GetKeyNone(eKeyCode::LEFT)
		//		&& Input::GetKeyNone(eKeyCode::UP)
		//		&& Input::GetKeyNone(eKeyCode::DOWN))
		//	{
		//		moveTime += Time::DeltaTime();
		//		if (moveTime > 0.05f)
		//		{
		//			moveTime = 0.0f;
		//			velocity.x = 0.0f;
		//			mDragonSoldierState = eDragonSoldierState::Idle;
		//		}
		//	}
		//	else
		//	{
		//		moveTime = 0.0f;


		//		if (Input::GetKeyDown(eKeyCode::LEFT))
		//		{
		//			bRun = true;
		//			isFlip = true;
		//			moveVector[0] = (UINT)eKeyCode::LEFT;
		//		}
		//		else if (Input::GetKeyDown(eKeyCode::RIGHT))
		//		{
		//			bRun = true;
		//			isFlip = false;
		//			moveVector[0] = (UINT)eKeyCode::RIGHT;
		//		}

		//		if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
		//		{
		//			if (Input::GetKeyUp(eKeyCode::RIGHT))
		//			{
		//				velocity.x = 0.0f;
		//				if (Input::GetKey(eKeyCode::LEFT))
		//				{

		//					isFlip = true;
		//					moveVector[0] = (UINT)eKeyCode::LEFT;
		//				}
		//			}
		//		}
		//		else if ((eKeyCode)moveVector[0] == eKeyCode::LEFT)
		//		{
		//			if (Input::GetKeyUp(eKeyCode::LEFT))
		//			{
		//				velocity.x = 0.0f;
		//				if (Input::GetKey(eKeyCode::RIGHT))
		//				{
		//					isFlip = false;
		//					moveVector[0] = (UINT)eKeyCode::RIGHT;
		//				}
		//			}
		//		}
		//		else
		//		{
		//			if (Input::GetKeyDown(eKeyCode::LEFT))
		//			{
		//				bRun = true;
		//				isFlip = true;
		//				moveVector[0] = (UINT)eKeyCode::LEFT;
		//			}
		//			else if (Input::GetKeyDown(eKeyCode::RIGHT))
		//			{
		//				bRun = true;
		//				isFlip = false;
		//				moveVector[0] = (UINT)eKeyCode::RIGHT;
		//			}
		//		}
		//	}
		//}

		//if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
		//{
		//	if (Input::GetKey(eKeyCode::RIGHT))
		//	{
		//		velocity.x = 255.0f;
		//		//pos.x += 255.0f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//	}
		//}
		//else if ((eKeyCode)moveVector[0] == eKeyCode::LEFT)
		//{
		//	if (Input::GetKey(eKeyCode::LEFT))
		//	{
		//		velocity.x = -255.0f;
		//		//	pos.x -= 255.0f * Time::DeltaTime();
		//		tr->SetPosition(pos);
		//	}
		//}
		//if (Input::GetKey(eKeyCode::DOWN))
		//{
		//	//float virtualZ = tr->GetVirtualZ();
		//	velocity.z = -255.0f;
		//	//tr->SetVirtualZ(virtualZ - 255.0f * Time::DeltaTime());
		//}
		//else if (Input::GetKey(eKeyCode::UP))
		//{
		//	//float virtualZ = tr->GetVirtualZ();
		//	velocity.z = 255.0f;

		//	//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		//}
		//else if (Input::GetKeyNone(eKeyCode::UP) && Input::GetKeyNone(eKeyCode::DOWN))
		//{
		//	//float virtualZ = tr->GetVirtualZ();
		//	velocity.z = 0.0f;
		//	//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		//}
		//rb->SetVelocity(velocity);

		//if (Input::GetKey(eKeyCode::X))
		//{
		//	bAttackVector[(UINT)eAttackType::Attack1] = true;
		//	bMove = false;
		//	commandVector[0] = (UINT)eKeyCode::X;
		//	mDragonSoldierState = eDragonSoldierState::Attack;
		//	mVelocity.x = 400.0f;
		//}
	}
	
	void DragonSoldierScript::Attack()
	{

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();
		//Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		//Vector3 velocity = rb->GetVelocity();


		//if (Input::GetKeyDown(eKeyCode::X))
		//{
		//	for (UINT i = 0; i < (UINT)eAttackType::End; i++)
		//	{
		//		if (commandVector[i] != (UINT)eKeyCode::X)
		//		{
		//			commandVector[i] = (UINT)eKeyCode::X;
		//			break;
		//		}
		//		else
		//		{
		//			continue;
		//		}
		//	}
		//}

		//if (commandTime > 0.2f)
		//{
		//	commandTime = 0.0f;
		//	bCommand = false;
		//	mDragonSoldierState = eDragonSoldierState::Idle;
		//	moveTime = 0.0f;
		//	bMove = false;
		//	for (UINT i = 0; i < (UINT)eAttackType::End; i++)
		//	{
		//		commandVector[i] = 0;
		//		bAttackVector[i] = false;
		//	}
		//}



		//if (bCommand)
		//	commandTime += Time::DeltaTime();
		//else
		//	commandTime = 0.0f;

		//for (UINT i = 0; i < (UINT)eAttackType::End; i++)
		//{
		//	if (bAttackVector[i] && (commandVector[i] == (UINT)eKeyCode::X))
		//	{
		//		if (Input::GetKey(eKeyCode::LEFT))
		//		{
		//			isFlip = true;
		//			//mVelocity.x = -600.0f;
		//		}
		//		else if (Input::GetKey(eKeyCode::RIGHT))
		//		{
		//			isFlip = false;
		//			//mVelocity.x = 600.0f;
		//		}
		//		/*else if (isFlip)
		//		{
		//			mVelocity.x = -150.0f;
		//		}
		//		else if (!isFlip)
		//		{
		//			mVelocity.x = 150.0f;
		//		}*/


		//		bAttackVector[i] = false;
		//		bCommand = false;
		//		commandTime = 0.0f;
		//		mAnimator->PlayAnimation(mAttackVector[i], false);
		//		moveTime = 0.0f;
		//		bMove = true;
		//		break;
		//	}
		//	else
		//	{
		//		continue;
		//	}
		//}


		//if (bMove)
		//{
		//	moveTime += Time::DeltaTime();
		//}
		//else
		//	moveTime = 0.0f;

		////velocity.x = mVelocity.x;
		//if (bMove && moveTime <= 0.2f)
		//{
		//	velocity.x = mVelocity.x;
		//	if (isFlip)
		//		velocity.x = -1.0f * abs(velocity.x);
		//}
		//else
		//{
		//	bMove = false;
		//	velocity.x = 0.0f;
		//}

		//rb->SetVelocity(velocity);
	}
	void DragonSoldierScript::Anim()
	{
		mAnimator->SetFlip(isFlip);
		switch (mDragonSoldierState)
		{
		case eDragonSoldierState::Idle:
			if (mPrevDragonSoldierState != mDragonSoldierState)
				mAnimator->PlayAnimation(L"dragon_soldierIdle", true);
			break;
		case eDragonSoldierState::Walk:
			if (mPrevDragonSoldierState != mDragonSoldierState)
				mAnimator->PlayAnimation(L"dragon_soldierWalk", true);
			break;
		case eDragonSoldierState::Attack:
			//if (mPrevDragonSoldierState != mDragonSoldierState)
				//mAnimator->PlayAnimation(L"SwordManAttack1", false);
			break;
		default:
			break;
		}
	}
	void DragonSoldierScript::Attack1StartEvent()
	{
		


	}
	void DragonSoldierScript::Attack2StartEvent()
	{
		
	}
	void DragonSoldierScript::Attack1CompleteEvent()
	{
		
	}
	void DragonSoldierScript::Attack2CompleteEvent()
	{
	
	}
}
