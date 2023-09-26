#pragma once
//#include "hjScript.h"
#include "hjMonsterScript.h"

namespace hj
{
	class Animator;
	class Collider2D;
	class AttackScriptManager;
	class DrakeRiderScript : public MonsterScript
	{
	public:
		enum class eAttackType
		{
			AttackBasic,
			AttackBreath,
			AttackRush,
			End,
		};
		DrakeRiderScript();
		~DrakeRiderScript();


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
		Vector3 mTargetPos;
		float mTargetVZ;
		std::wstring attackName;

		bool mActivate;
		bool bAttack;
	};


}
