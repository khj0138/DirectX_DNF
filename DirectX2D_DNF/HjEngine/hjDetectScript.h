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

		Player* GetTarget();
		void SetTarget(Player* target) { mTarget = target; }

	public:

	private:
		Player* mTarget;

	};


}
