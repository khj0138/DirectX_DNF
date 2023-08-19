#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class BasicAttackScript1 : public AttackScript
	{
	public:
		BasicAttackScript1();
		~BasicAttackScript1();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

	public:

	private:

	};


}
