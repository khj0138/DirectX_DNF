#pragma once
#include <hjScript.h>

namespace hj
{
	//class Animator;
	//class AttackObject;
	class Monster;
	class Player;
	class Animator;
	class EffectObjectScript : public Script
	{
	public:
		enum class effectType
		{
			Animation,
			Sprite,
			Mesh,
			End,
		};
		EffectObjectScript();
		EffectObjectScript(effectType type);
		~EffectObjectScript();
		virtual void Initialize() override;
		virtual void Update() override;


		/*AttackObject* GetOwner() { return mOwner; }
		void SetOwner(AttackObject* owner) { mOwner = owner; }*/


		void SetActivate(bool activate) { bActivate = activate; }
		void SetAnimate(bool animate) { bAnimate = animate; }
		void SetCastingTime(float castingTime) { mCastingTime = castingTime; }
		void SetCurTime(float curTime) { mCurTime = curTime; }
		void SetType(effectType type) { mType = type; }


		bool GetActivate() { return bActivate; }
		bool GetAnimate() { return bAnimate; }
		float GetCastingTime() { return mCastingTime; }
		float GetCurTime() { return mCurTime; }
		effectType GetType() { return mType; }
		void SetPos(GameObject* object);




	private:
		effectType mType;
		bool bAnimate;
		bool bActivate;
		float mCastingTime;
		float mCurTime;
	};


}
