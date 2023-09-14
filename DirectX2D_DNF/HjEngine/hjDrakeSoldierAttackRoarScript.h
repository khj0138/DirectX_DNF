#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class DrakeSoldierAttackRoarScript : public AttackScript
	{
	public:
		DrakeSoldierAttackRoarScript();
		~DrakeSoldierAttackRoarScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

	public:

	private:

	};


}
