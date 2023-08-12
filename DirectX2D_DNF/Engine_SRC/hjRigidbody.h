#pragma once
#include "hjComponent.h"
namespace hj
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector3 force) { mForce += force; }
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
		void SetGravity(bool gravity) { mbGravity = gravity; }
		Vector3 GetVelocity() { return mVelocity; }
		bool GetGround() { return mbGround; }
		bool GetGravity() { return mbGravity; }

	private:
		float mMass;
		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mLimitedVelocity;

		Vector3 mGravity;
		float mFriction;
		bool mbGround;
		bool mbGravity;

		float fixedRes;
	};
}

