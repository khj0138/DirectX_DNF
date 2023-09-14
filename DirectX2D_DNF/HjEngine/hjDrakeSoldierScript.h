#pragma once
//#include "hjScript.h"
#include "hjMonsterScript.h"

namespace hj
{
	class Animator;
	class Collider2D;
	class AttackScriptManager;
	class DrakeSoldierScript : public MonsterScript
	{
	public:
		enum class eAttackType
		{
			AttackBasic,
			AttackJump,
			AttackRoar,
			AttackRush,
			AttackSpear,
			End,
		};
		DrakeSoldierScript();
		~DrakeSoldierScript();


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
		void AnimHit();

		void AttackCompleteEvent();
	private:
		bool bMove;
		Vector3 mVelocity;
		Vector3 mTargetPos;
		float mTargetVZ;
		std::wstring attackName;

		bool mActivate;
		bool bAttack;
	};


}
