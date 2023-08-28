#pragma once
#include "hjGameObject.h"

namespace hj
{
	class AttackScriptManager;
	class Animator;
	class Player : public GameObject
	{
	public:
		Player();
		~Player();
		struct status
		{
			UINT maxHP;
			UINT HP;
		};
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetStatus(UINT maxHP, UINT HP) { mStatus.maxHP = maxHP; mStatus.HP = HP; }
		status GetStatus() { return mStatus; }
		void Attack(UINT damage)
		{
			mStatus.HP > damage ? mStatus.HP = mStatus.HP - damage : mStatus.HP = 0;
		}
		//virtual void OnCollisionEnter(Collider2D* other);
		//virtual void OnCollisionStay(Collider2D* other);
		//virtual void OnCollisionExit(Collider2D* other);

		void EnterScene();
		
		void ExitScene();
		
		AttackScriptManager* GetAtkManager() { return AtkManager; }
	private:
		bool mActivate;
		bool bAttack;
		AttackScriptManager* AtkManager;
		status mStatus;
	};
}