#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class FireWaveAttackScript : public AttackScript
	{
	public:
		FireWaveAttackScript();
		~FireWaveAttackScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;
		virtual void SetActivate(bool activate) override;

	public:

	private:

	};


}
