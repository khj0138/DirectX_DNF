#pragma once
//#include "hjScript.h"
#include "hjMonsterScript.h"

namespace hj
{
	class Animator;
	class Collider2D;
	class AttackScriptManager;
	class HysmarScript : public MonsterScript
	{
	public:
		enum class eAttackType
		{
			AttackBasic1,
			AttackBasic2,
			End,
		};
		HysmarScript();
		~HysmarScript();


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
		void SceneEnter();
		void Anim();
		void AnimHit();
		void AnimAttack();

		void Idle1CompleteEvent();
		void Idle2CompleteEvent();
		void AttackCompleteEvent();

	private:
		bool bMove;
		Vector3 mVelocity;
		bool phase;
		//Animator* mAnimator;
		//Collider2D* mCollider;
		//bool isFlip;

		//AttackScriptManager* AtkManager;
		std::wstring attackName;

		bool mActivate;
		bool bAttack;
	};


}
