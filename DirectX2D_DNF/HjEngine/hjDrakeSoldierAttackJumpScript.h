#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class DrakeSoldierAttackJumpScript : public AttackScript
	{
	public:
		DrakeSoldierAttackJumpScript();
		~DrakeSoldierAttackJumpScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;
	public:

	private:

	};


}
