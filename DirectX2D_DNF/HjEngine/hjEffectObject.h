#pragma once
#include "hjGameObject.h"

namespace hj
{
	class Animator;
	class EffectObject : public GameObject
	{
	public:
		EffectObject();
		~EffectObject();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetActivate(bool activate) { mActivate = activate; }

	private:
		Animator* mAnimator;
		bool mActivate;
		bool bEffect;
	};


}
