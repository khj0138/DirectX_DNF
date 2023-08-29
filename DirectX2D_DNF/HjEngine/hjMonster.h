#pragma once
#include "hjGameObject.h"

namespace hj
{
	class Player;
	class AttackScriptManager;
	class Animator;
	class Monster : public GameObject
	{
	public:
		Monster();
		~Monster();
		struct status
		{
			UINT maxHP;
			UINT HP;
		};
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		
		/*virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);*/

		void EnterScene();

		void ExitScene();

		void Attack(UINT damage)
		{
			mStatus.HP > damage ? mStatus.HP = mStatus.HP - damage : mStatus.HP = 0;
			if (mStatus.HP == 0)
				SetState(GameObject::eState::Dead);
		}


		AttackScriptManager* GetAtkManager() { return AtkManager; }
		void SetAtkManager(AttackScriptManager* manager) { AtkManager = manager; }

		Player* GetTarget() { return mTarget; }

		void SetStatus(status stat) { mStatus = stat; }
		void SetMaxHP(UINT maxHP) { mStatus.maxHP = maxHP; }
		UINT GetMaxHP() { return mStatus.maxHP; }
		void SetHP(UINT maxHP) { mStatus.maxHP = maxHP; }
		UINT GetHP() { return mStatus.HP; }
		void SetStatus(UINT maxHP, UINT hp) { mStatus.maxHP = maxHP; mStatus.HP = hp; }
		status GetStatus() { return mStatus; }
		float GetCoolTime() { return mCoolTime; }
		void SetCoolTime(float cooltime) { mCoolTime = cooltime; }
		//Animator* GetAnimator() { return mAnimator; }
	private:
		bool mActivate;
		bool bAttack;
		AttackScriptManager* AtkManager;
		Player* mTarget;
		status mStatus;
		float mCoolTime;
		//Animator* mAnimator;
	};
}