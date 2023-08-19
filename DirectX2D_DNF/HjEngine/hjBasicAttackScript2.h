#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class BasicAttackScript2 : public AttackScript
	{
	public:
		BasicAttackScript2();
		~BasicAttackScript2();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

	public:

	private:

	};


}
