#pragma once
#include <hjScript.h>

namespace hj
{
	class Animator;
	class CommonPortalScript : public Script
	{
	public:
		CommonPortalScript();
		~CommonPortalScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
	public:
		void MainCampCreateGateCompleteEvent();
		void MainCampDestroyGateBackCompleteEvent();
		void MainCampGateGlowCompleteEvent();

	private:
		Animator* mAnimator;

	};


}
