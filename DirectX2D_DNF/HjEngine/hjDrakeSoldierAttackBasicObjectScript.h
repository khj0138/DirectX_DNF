#pragma once
#include <hjAttackObjectScript.h>

namespace hj
{
	//class Animator;
	class DrakeSoldierAttackBasicObjectScript : public AttackObjectScript
	{
	public:
		DrakeSoldierAttackBasicObjectScript();
		~DrakeSoldierAttackBasicObjectScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:

	private:

	};


}
