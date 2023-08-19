#pragma once
#include "hjGameObject.h"

namespace hj
{
	class Animator;
	class AttackScript;
	class AttackObject : public GameObject
	{
	public:
		AttackObject();
		~AttackObject();
		//virtual bool Reset() = 0;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		/*virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);*/

		void SetActivate(bool activate);
		void SetAttack(bool attack) { bAttack = attack; }
		//void SetAttackHeight(Vector2 height) { attackHeight = height; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void SetAnimOffset(Vector2 offset) { animOffset = offset; }
		void SetAnimate(bool animate) { bAnimate = animate; }
		void SetCoolTime(float coolTime) { mCoolTime = coolTime; }
		void SetPos(Vector3 pos) { GetComponent<Transform>()->SetPosition(pos); }
		void SetPosVZ(float posVZ) { GetComponent<Transform>()->SetVirtualZ(posVZ); }
		void SetOwnerScript(AttackScript* script) { mOwner = script; }

		bool GetActivate() { return bActivate; }
		bool GetAttack() { return bAttack; }
		//float GetAttackHeight() { return attackHeight; }
		Vector2 GetVelocity() { return mVelocity; }
		Vector2 GetAnimOffset() { return animOffset; }
		bool GetAnimate() { return bAnimate; }
		float GetCoolTime() { return mCoolTime; }
		Vector3 GetPos() { return GetComponent<Transform>()->GetPosition(); }
		float GetPosVZ() { return GetComponent<Transform>()->GetVirtualZ(); }
		AttackScript* GetOwnerScript() { return mOwner; }


		std::map<UINT32, float>::iterator findTarget(UINT32 id)
		{
			return targets.find(id);
		}
		bool existTarget(UINT32 id)
		{
			return !(targets.find(id) == targets.end());
		}
		void registerTarget(UINT32 id)
		{
			targets.insert(std::make_pair(id, mCoolTime));
		}
		void setTargetZero(UINT32 id)
		{
			targets.find(id)->second = 0.0f;
		}
		
	private:
		Animator* mAnimator;
		bool bAnimate;

		bool bActivate;
		bool bAttack;
		float mCoolTime;
		//float attackHeight;
		Vector2 mVelocity;
		Vector2 animOffset;
		std::map<UINT32, float> targets;

		AttackScript* mOwner;
	};
}
