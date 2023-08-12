#pragma once
#include "hjAttackObject.h"


namespace hj
{
	class BasicAttackObject : public AttackObject
	{
	public:
		BasicAttackObject();
		~BasicAttackObject();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);


	private:
		Vector2 attackHeight;
	};
}
