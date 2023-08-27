#pragma once
#include <hjAttackObjectScript.h>

namespace hj
{
	//class Animator;
	class DragonSoldierAttackObject1Script : public AttackObjectScript
	{
	public:
		DragonSoldierAttackObject1Script();
		~DragonSoldierAttackObject1Script();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		virtual void Attack(Player* target);

	public:

	private:

	};


}
