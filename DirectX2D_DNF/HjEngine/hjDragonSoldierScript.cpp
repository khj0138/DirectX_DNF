#include "hjDragonSoldierScript.h"
#include "hjTransform.h"
#include "hjPlayer.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
//#include "hjBehaviorTree.h"

#include "hjDragonSoldier.h"
#include "hjDragonSoldierAttack1Script.h";
#include "hjDragonSoldierAttack2Script.h";

#include "hjAttackScriptManager.h"
#include "hjApplication.h"

extern hj::Application application;
namespace hj
{

	DragonSoldierScript::DragonSoldierScript()
		: mDragonSoldierState(eDragonSoldierState::Idle)
		, mPrevDragonSoldierState(eDragonSoldierState::Idle)
		, mVelocity(Vector3::Zero)
		, attackName(L"")
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
		mAnimator->CompleteEvent(L"dragon_soldierAttack1") = std::bind(&DragonSoldierScript::Attack1CompleteEvent, this);
		mAnimator->CompleteEvent(L"dragon_soldierAttack2") = std::bind(&DragonSoldierScript::Attack2CompleteEvent, this);

		mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetSize(Vector2{50.0f, 50.0f }, 150.0f);

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		if (monster != nullptr)
		{
			mOwner = dynamic_cast<DragonSoldier*>(monster);
			AtkManager = monster->GetAtkManager();
			AtkManager->RegisterAttackScript<DragonSoldierAttack1Script>(L"dragon_soldierAttack1");
			AtkManager->RegisterAttackScript<DragonSoldierAttack2Script>(L"dragon_soldierAttack2");
		}
	}
	void DragonSoldierScript::Update()
	{
		curTime += Time::DeltaTime();
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
		
		mPrevDragonSoldierState = mDragonSoldierState;

		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float posVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AtkManager->SetPosition(Vector2{ pos.x,pos.y }, posVZ);
		AtkManager->Update();
	}
	
	bool DragonSoldierScript::IsWalk()
	{
		float fixedRes = (float)application.GetFixedWidth() / 800.f;

		Player* target = mOwner->GetTarget();
		if (target != nullptr)
		{
			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
			float playerVZ = target->GetComponent<Transform>()->GetVirtualZ();
			Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);
			Vector3 monPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			float monPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
			Vector2 monPos2D = Vector2(monPos.x, monPosVZ);

			if(math::Vector2::Distance(playerPos2D, monPos2D) > GetOwner()->GetComponent<Collider2D>()->GetSize().x / 2.0f * fixedRes
				|| abs(playerPos2D.y - monPos2D.y) > GetOwner()->GetComponent<Collider2D>()->GetSize().y / 4.0f * fixedRes)
				return true;
		}
		return false;
	}
	bool DragonSoldierScript::IsAttack()
	{
		if (curTime < mOwner->GetCoolTime())
		{
			return false;
		}
		else
		{
			for (auto iter = AtkManager->mAttackScripts.begin(); iter != AtkManager->mAttackScripts.end(); iter++)
			{
				if (iter->first == L"Detect")
					continue;
				if (AtkManager->LoadAttackScript(iter->first) != nullptr)
				{
					attackName = iter->first;
					curTime = 0.0f;
					return true;
				}
			}
			return false;
		}
	}
	void DragonSoldierScript::Idle()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		rb->SetVelocity(Vector3(0.0f, velocity.y,0.0f));

		Player* target = mOwner->GetTarget();
		if (target != nullptr)
		{
			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
			if (playerPos.x < pos.x)
				GetOwner()->SetFlip(true);
			else
				GetOwner()->SetFlip(false);
		}

		
		if (IsWalk())
		{
			mDragonSoldierState = eDragonSoldierState::Walk;
		}
		if (IsAttack())
		{
			mDragonSoldierState = eDragonSoldierState::Attack;
		}
	}
	void DragonSoldierScript::Walk()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();

		Player* target = mOwner->GetTarget();
		Vector2 moveVector = Vector2::Zero;
		if (target != nullptr)
		{
			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
			float playerVZ = target->GetComponent<Transform>()->GetVirtualZ();
			Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);
			Vector3 monPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			float monPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
			Vector2 monPos2D = Vector2(monPos.x, monPosVZ);

			if (playerPos2D.x <= monPos2D.x)
			{
				GetOwner()->SetFlip(true);
				if(abs(playerPos2D.x - monPos2D.x) > GetOwner()->GetComponent<Collider2D>()->GetSize().x / 2.0f)
					moveVector.x = -1.f;
			}
			else if (playerPos2D.x > monPos2D.x)
			{
				GetOwner()->SetFlip(false);
				if (abs(playerPos2D.x - monPos2D.x) > GetOwner()->GetComponent<Collider2D>()->GetSize().x / 2.0f)
					moveVector.x = 1.f;
			}
			
			if(playerPos2D.y > monPos2D.y)
			{
				if (abs(playerPos2D.y - monPos2D.y) > GetOwner()->GetComponent<Collider2D>()->GetSize().y / 4.0f)
				moveVector.y = 1.f;
			}
			else
			{
				if (abs(playerPos2D.y - monPos2D.y) > GetOwner()->GetComponent<Collider2D>()->GetSize().y / 4.0f)
					moveVector.y = -1.f;
			}
		}

		moveVector.Normalize();
		moveVector *= 100.0f;
		if (!IsWalk())
		{
			mDragonSoldierState = eDragonSoldierState::Idle;
			moveVector = Vector2::Zero;
		}
		else
		{
			moveVector.Normalize();
			moveVector *= 100.0f;
		}
		velocity.x = moveVector.x;
		velocity.z = moveVector.y;
		rb->SetVelocity(velocity);
	}
	
	void DragonSoldierScript::Attack()
	{
		Animation* animation = mAnimator->GetActiveAnimation();
		if (attackName == L"dragon_soldierAttack1")
		{
			if (animation->GetIndex() == 1 && !(animation->GetPause()))
			{
				animation->SetPause(true);
				curTime = 0.0f;
			}
			else if (curTime >= 0.1f)
			{
				animation->SetPause(false);
			}
		}
		else if (attackName == L"dragon_soldierAttack2")
		{
			if (animation->GetIndex() == 0 && !(animation->GetPause()))
			{
				animation->SetPause(true);
				curTime = 0.0f;
			}
			else if (curTime >= 0.1f)
			{
				animation->SetPause(false);
			}
		}
	}
	void DragonSoldierScript::Anim()
	{
		mAnimator->SetFlip(GetOwner()->GetFlip());
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
		{
			if (mPrevDragonSoldierState != mDragonSoldierState)
				mAnimator->PlayAnimation(attackName, true);
			break;
		}
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
		mDragonSoldierState = eDragonSoldierState::Idle;
		curTime = 0.0f;
	}
	void DragonSoldierScript::Attack2CompleteEvent()
	{
		mDragonSoldierState = eDragonSoldierState::Idle;
		curTime = 0.0f;
	}
}
