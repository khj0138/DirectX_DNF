#pragma once
#include <hjAttackObjectScript.h>

namespace hj
{
	//class Animator;
	class DrakeArmorAttackBreathObjectScript : public AttackObjectScript
	{
	public:
		DrakeArmorAttackBreathObjectScript();
		~DrakeArmorAttackBreathObjectScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:

	private:

	};


}
