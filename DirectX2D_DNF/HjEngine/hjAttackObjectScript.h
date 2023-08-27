#pragma once
#include <hjScript.h>

namespace hj
{
	//class Animator;
	class AttackObject;
	class Monster;
	class Player;
	class AttackObjectScript : public Script
	{
	public:
		AttackObjectScript();
		~AttackObjectScript();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		virtual void Attack(Monster* target);
		virtual void Attack(Player* target);
		
		AttackObject* GetOwner() { return mOwner; }
		void SetOwner(AttackObject* owner) { mOwner = owner; }

	public:

		AttackObject* mOwner;
	private:
	};


}
