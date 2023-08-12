#pragma once
#include <hjScript.h>

namespace hj
{
	class Animator;
	class NPCScript : public Script
	{
	public:
		NPCScript();
		~NPCScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetPathName(std::wstring name) { pathName = name; }
	public:


		void BackGroundgate_new_glow_effCompleteEvent();
		void BackGroundgate_new_effCompleteEvent();
		void BackGroundgate_new_glow_eff_backCompleteEvent();

	private:
		Animator* mAnimator;
		std::wstring pathName;
	};


}
