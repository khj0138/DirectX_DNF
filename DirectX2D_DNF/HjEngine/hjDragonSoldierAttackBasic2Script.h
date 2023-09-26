#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class DragonSoldierAttackBasic2Script : public AttackScript
	{
	public:
		DragonSoldierAttackBasic2Script();
		~DragonSoldierAttackBasic2Script();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;
		virtual void SetActivate(bool activate) override;
	public:

	private:

	};


}
