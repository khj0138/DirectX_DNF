#pragma once
#include <hjAttackObjectScript.h>

namespace hj
{
	//class Animator;
	class DragonSoldierAttackBasic2ObjectScript : public AttackObjectScript
	{
	public:
		DragonSoldierAttackBasic2ObjectScript();
		~DragonSoldierAttackBasic2ObjectScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:

	private:

	};


}
