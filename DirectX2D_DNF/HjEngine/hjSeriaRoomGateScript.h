#pragma once
#include <hjScript.h>

namespace hj
{
	class Animator;
	class SeriaRoomGateScript : public Script
	{
	public:
		SeriaRoomGateScript();
		~SeriaRoomGateScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
	public:


		void BackGroundgate_new_glow_effCompleteEvent();
		void BackGroundgate_new_effCompleteEvent();
		void BackGroundgate_new_glow_eff_backCompleteEvent();

	private:
		Animator* mAnimator;

	};


}
