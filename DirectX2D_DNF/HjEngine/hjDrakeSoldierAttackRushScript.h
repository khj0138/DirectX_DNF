#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class DrakeSoldierAttackRushScript : public AttackScript
	{
	public:
		DrakeSoldierAttackRushScript();
		~DrakeSoldierAttackRushScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

	public:

	private:

	};


}
