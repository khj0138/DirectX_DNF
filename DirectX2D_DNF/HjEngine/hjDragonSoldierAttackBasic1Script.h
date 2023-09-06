#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class DragonSoldierAttackBasic1Script : public AttackScript
	{
	public:
		DragonSoldierAttackBasic1Script();
		~DragonSoldierAttackBasic1Script();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

	public:

	private:

	};


}
