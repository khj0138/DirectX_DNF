#pragma once
#include "hjMonster.h"

namespace hj
{
	class AttackScriptManager;
	class Animator;
	class DragonSoldier : public Monster
	{
	public:
		DragonSoldier();
		~DragonSoldier();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);


		//AttackScriptManager* GetAtkManager() { return Monster::GetAtkManager(); }

	private:
		bool mActivate;
		bool bAttack;
		//AttackScriptManager* atkManager;
	};
}