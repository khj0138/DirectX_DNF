#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class DrakeSoldierAttackBasicScript : public AttackScript
	{
	public:
		DrakeSoldierAttackBasicScript();
		~DrakeSoldierAttackBasicScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

		virtual void SetActivate(bool activate) override;
	public:

	private:

	};


}
