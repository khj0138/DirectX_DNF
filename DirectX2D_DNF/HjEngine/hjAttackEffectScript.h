#pragma once
#include <hjEffectObjectScript.h>

namespace hj
{
	//class Animator;
	class GameObject;
	class AttackScriptManager;
	class AttackEffectScript : public EffectObjectScript
	{
	public:
		enum class AtkEffectType
		{
			Circle,
			Rect,
			End,
		};
		AttackEffectScript();
		AttackEffectScript(AtkEffectType type);
		~AttackEffectScript();

		virtual void Initialize() override;
		virtual void Update() override;

		//virtual void LateUpdate() override;
		virtual void EffectRender() override;


		void SetMesh(AtkEffectType type);
		void SetAtkEffectType(AtkEffectType type) { mType = type; }
		AtkEffectType GetAtkEffectType() { return mType; }

		void SetStartPercent(float percent) { mStartPercent = percent; }
		float GetStartPercent() { return mStartPercent; }
		void SetEndPercent(float percent) { mEndPercent = percent; }
		float GetEndPercent() { return mEndPercent; }
		
	public:

	private:
		AtkEffectType mType;
		float mStartPercent;
		float mEndPercent;
	};


}
