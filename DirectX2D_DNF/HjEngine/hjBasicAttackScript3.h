#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class BasicAttackScript3 : public AttackScript
	{
	public:
		BasicAttackScript3();
		~BasicAttackScript3();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;
	public:

	private:

	};


}
