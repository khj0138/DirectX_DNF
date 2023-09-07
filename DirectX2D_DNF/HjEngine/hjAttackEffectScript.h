#pragma once
#include <hjEffectObjectScript.h>

namespace hj
{
	//class Animator;
	class GameObject;
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

		void SetMesh(AtkEffectType type);
		void SetAtkEffectType(AtkEffectType type) { mType = type; }
		AtkEffectType GetAtkEffectType() { return mType; }
	public:

	private:
		AtkEffectType mType;
		float mStartPercent;
		float mEndPercent;
	};


}
