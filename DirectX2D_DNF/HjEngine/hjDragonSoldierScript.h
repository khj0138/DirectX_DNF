#pragma once
//#include "hjScript.h"
#include <hjScript.h>

namespace hj
{
	class DragonSoldier;
	class Animator;
	class Collider2D;
	class AttackScriptManager;
	class DragonSoldierScript : public Script
	{
	public:
		enum class eDragonSoldierState
		{
			Idle,
			Walk,
			Attack,
			Hit,
			Die,
			End,
		};

		enum class eAttackType
		{
			Attack1,
			Attack2,
			End,
		};
		DragonSoldierScript();
		~DragonSoldierScript();


		virtual void Initialize() override;
		virtual void Update() override;


		//behavior
		bool IsWalk();
		bool IsAttack();

	public:
		void Idle();
		void Walk();
		void Attack();
		void Hit();
		void Die();
		void Anim();
		
		void JumpUpStartEvent();
		void JumpUpCompleteEvent();
		void Attack1StartEvent();
		void Attack2StartEvent();
		void Attack1CompleteEvent();
		void Attack2CompleteEvent();
	private:
		eDragonSoldierState mDragonSoldierState;
		eDragonSoldierState mPrevDragonSoldierState;


		DragonSoldier* mOwner;
		bool bMove;
		Vector3 mVelocity;
		Animator* mAnimator;
		Collider2D* mCollider;
		//bool isFlip;
		
		AttackScriptManager* AtkManager;
		std::wstring attackName;
		float curTime;
	};


}
