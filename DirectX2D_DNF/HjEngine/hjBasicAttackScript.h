#pragma once
#include <hjScript.h>

namespace hj
{
	//class Animator;
	class AttackObject;
	class EffectObject;
	class BasicAttackScript : public Script
	{
	public:
		BasicAttackScript();
		~BasicAttackScript();

		virtual void Initialize() override;
		virtual void Update() override;
	public:

	private:

	};


}
