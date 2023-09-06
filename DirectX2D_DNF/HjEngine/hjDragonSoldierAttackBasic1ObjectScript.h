#pragma once
#include <hjAttackObjectScript.h>

namespace hj
{
	//class Animator;
	class DragonSoldierAttackBasic1ObjectScript : public AttackObjectScript
	{
	public:
		DragonSoldierAttackBasic1ObjectScript();
		~DragonSoldierAttackBasic1ObjectScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:

	private:

	};


}
