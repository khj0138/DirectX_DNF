#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class DrakeSoldierAttackSpearScript : public AttackScript
	{
	public:
		DrakeSoldierAttackSpearScript();
		~DrakeSoldierAttackSpearScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

	public:

	private:

	};


}
