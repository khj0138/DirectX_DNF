#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class BasicAttackScript : public AttackScript
	{
	public:
		BasicAttackScript();
		~BasicAttackScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;
		virtual void SetActivate(bool activate) override;

	public:

	private:

	};


}
