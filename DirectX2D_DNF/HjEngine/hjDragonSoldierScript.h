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
			AttackBasic1,
			AttackBasic2,
			End,
		};
		DragonSoldierScript();
		~DragonSoldierScript();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		//behavior
		bool IsWalk();
		bool IsAttack();

		void Idle();
		void Walk();
		void Attack();
		void Hit();
		void Die();
		void Anim();
		void AnimHit();
		
		void AttackCompleteEvent();
		
	private:
		bool bMove;
		Vector3 mVelocity;
		//Animator* mAnimator;
		//Collider2D* mCollider;
		//bool isFlip;
		
		//AttackScriptManager* AtkManager;
		std::wstring attackName;

		bool mActivate;
		bool bAttack;
	};


}
