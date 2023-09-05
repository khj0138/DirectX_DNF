#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class Player;
	class DetectScript : public AttackScript
	{
	public:
		DetectScript();
		~DetectScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;

		GameObject* GetTarget();

	public:

	private:
		GameObject* mTarget;

	};


}
