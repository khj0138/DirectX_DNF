#pragma once
#include "hjScript.h"

namespace hj
{
	class Player;
	class AttackScriptManager;
	class Animator;
	class MonsterScript : public Script
	{
	public:
		MonsterScript();
		~MonsterScript();
		enum class eMonsterState
		{
			Idle,
			Walk,
			Attack,
			Hit,
			Die,
			End,
		};
		struct status
		{
			UINT maxHP;
			UINT HP;
			bool SuperArmor;
		};
		virtual void Initialize() override;
		virtual void Update() override;

		eMonsterState GetMonsterState() { return mMonsterState; }
		void SetMonsterState(eMonsterState monsterState) { mMonsterState = monsterState; }

		eMonsterState GetPrevMonsterState() { return mPrevMonsterState; }
		void SetPrevMonsterState(eMonsterState monsterState) { mPrevMonsterState = monsterState; }
		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

		void EnterScene();

		void ExitScene();

		void Hit(UINT damage, bool flip, Vector2 direction);
		


		AttackScriptManager* GetAtkManager() { return AtkManager; }
		void SetAtkManager(AttackScriptManager* manager) { AtkManager = manager; }

		GameObject* GetTarget() { return mTarget; }

		void SetStatus(status stat) { mStatus = stat; }
		void SetStatus(UINT maxHP, UINT hp, bool armor) { mStatus = status(maxHP, hp, armor); }
		status GetStatus() { return mStatus; }

		void SetMaxHP(UINT maxHP) { mStatus.maxHP = maxHP; }
		UINT GetMaxHP() { return mStatus.maxHP; }
		void SetHP(UINT hp) { mStatus.HP = hp; }
		UINT GetHP() { return mStatus.HP; }
		void SetSuperArmor(bool armor) { mStatus.SuperArmor = armor; }
		bool GetSuperArmor() { return mStatus.SuperArmor; }

		float GetCoolTime() { return mCoolTime; }
		void SetCoolTime(float cooltime) { mCoolTime = cooltime; }
		float GetCurTime() { return mCurTime; }
		void SetCurTime(float curtime) { mCurTime = curtime; }
		float GetHitTime() { return mHitTime; }
		void SetHitTime(float hittime) { mHitTime = hittime; }
		//Animator* GetAnimator() { return mAnimator; }
	private:
		bool mActivate;
		bool bAttack;
		AttackScriptManager* AtkManager;
		GameObject* mTarget;
		status mStatus;
		float mCoolTime;
		float mCurTime;
		float mHitTime;

		eMonsterState mMonsterState;
		eMonsterState mPrevMonsterState;
		//Animator* mAnimator;
	};
}