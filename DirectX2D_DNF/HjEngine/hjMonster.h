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

		AttackScriptManager* GetAtkManager() { return AtkManager; }

		Player* GetTarget() { return mTarget; }

		void SetStatus(status stat) { mStatus = stat; }
		void SetStatus(UINT maxHP, UINT hp) { mStatus.maxHP = maxHP; mStatus.HP = hp; }
		void SetMaxHP(UINT maxHP) { mStatus.maxHP = maxHP; }
		UINT GetMaxHP() { return mStatus.maxHP; }
		void SetHP(UINT maxHP) { mStatus.maxHP = maxHP; }
		UINT GetHP() { return mStatus.HP; }
		status GetStatus() { return mStatus; }

		//Animator* GetAnimator() { return mAnimator; }
	private:
		bool mActivate;
		bool bAttack;
		AttackScriptManager* AtkManager;
		Player* mTarget;
		status mStatus;
		//Animator* mAnimator;
	};
}