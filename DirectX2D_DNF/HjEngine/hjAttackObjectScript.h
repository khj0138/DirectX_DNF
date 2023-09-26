#pragma once
#include <hjScript.h>


namespace hj
{
	//class Animator;
	//class AttackObject;
	class Monster;
	class Player;
	class Animator;
	class AttackScriptManager;
	class AttackObjectScript : public Script
	{
	public:
		struct status
		{
			UINT Damage;
			UINT DamageRange;
			Vector2 Direction;
		};
		enum class AttackObjectType
		{
			Player,
			Monster,
			End,
		};
		AttackObjectScript();
		AttackObjectScript(AttackObjectType attackObjectType);
		~AttackObjectScript();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		virtual void Attack(Script* target);
		
		/*AttackObject* GetOwner() { return mOwner; }
		void SetOwner(AttackObject* owner) { mOwner = owner; }*/


		void SetStatus(UINT damage, UINT damageRange, Vector2 direction)
		{
			mStatus.Damage = damage; mStatus.DamageRange = damageRange; mStatus.Direction = direction;
		}
		void SetActivate(bool activate) { bActivate = activate; }
		void SetPause();

		void SetAttack(bool attack) { bAttack = attack; }
		void SetAnimate(bool animate) { bAnimate = animate; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void SetCoolTime(float coolTime) { mCoolTime = coolTime; }
		//void SetPos(Vector3 pos) { GetOwner()->GetComponent<Transform>()->SetPosition(pos); }
		//void SetPosVZ(float posVZ) { GetOwner()->GetComponent<Transform>()->SetVirtualZ(posVZ); }
		//void SetFlip(bool flip) { GetOwner()->SetFlip(flip); }
		//void SetState(GameObject::eState state) { GetOwner()->SetState(state); }

		status GetStatus() { return mStatus; }
		bool GetActivate() { return bActivate; }
		bool GetAttack() { return bAttack; }
		Vector2 GetVelocity() { return mVelocity; }
		bool GetAnimate() { return bAnimate; }
		float GetCoolTime() { return mCoolTime; }
		float GetFinTime() { return mFinTime; }
		void SetFinTime(float finTime) { mFinTime = finTime; }
		//Vector3 GetPos() { return GetOwner()->GetComponent<Transform>()->GetPosition(); }
		//float GetPosVZ() { return GetOwner()->GetComponent<Transform>()->GetVirtualZ(); }
		//bool GetFlip() { return GetOwner()->GetFlip(); }
		//GameObject::eState GetState() { GetOwner()->GetState(); }



		std::map<UINT32, float>::iterator FindTarget(UINT32 id)
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
		void clearTargets()
		{
			targets.clear();
		}
		void SetPosCol(GameObject* object);

		void SetManager(AttackScriptManager* manager) { attackManager = manager; }
		AttackScriptManager* GetManager() { return attackManager; }

		void SetDefaultPercent(Vector2 start, Vector2 end);
		Vector2 GetDefaultStartPercent() { return mStartPercent; }
		Vector2 GetDefaultEndPercent() { return mEndPercent; }

		void SetCenterPercent(float center);
		float GetCenterPercent() { return mCenterPercent; }
	private:
		AttackObjectType mType;
		Animator* mAnimator;
		bool bAnimate;

		bool bActivate;
		bool bAttack;
		float mCoolTime;
		//float attackHeight;
		Vector2 mVelocity;
		Vector2 animOffset;
		float mFinTime;
		std::map<UINT32, float> targets;

		status mStatus;
		AttackScriptManager* attackManager;

		Vector2 mStartPercent;
		Vector2 mEndPercent;

		float mCenterPercent;

	};


}
