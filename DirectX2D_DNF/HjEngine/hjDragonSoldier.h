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


		//AttackScriptManager* GetAtkManager() { return Monster::GetAtkManager(); }

	private:
		bool mActivate;
		bool bAttack;
	};
}