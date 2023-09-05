#pragma once
//#include "hjScript.h"
#include "hjMonsterScript.h"

namespace hj
{
	class Animator;
	class Collider2D;
	class AttackScriptManager;
	class DragonSoldierScript : public MonsterScript
	{
	public:
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

		void Idle();
		void Walk();
		void Attack();
		void Hit();
		void Die();
		void Anim();
		
		void Attack1StartEvent();
		void Attack2StartEvent();
		void Attack1CompleteEvent();
		void Attack2CompleteEvent();
		void HitCompleteEvent();
		void DieCompleteEvent();
	private:
		bool bMove;
		Vector3 mVelocity;
		//Animator* mAnimator;
		//Collider2D* mCollider;
		//bool isFlip;
		
		//AttackScriptManager* AtkManager;
		std::wstring attackName;
		float curTime;

		bool mActivate;
		bool bAttack;
	};


}
