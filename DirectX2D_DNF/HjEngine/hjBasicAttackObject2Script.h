#pragma once
#include <hjAttackObjectScript.h>

namespace hj
{
	//class Animator;
	class BasicAttackObject2Script : public AttackObjectScript
	{
	public:
		BasicAttackObject2Script();
		~BasicAttackObject2Script();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		virtual void Attack(Monster* target);

	public:

	private:

	};


}
