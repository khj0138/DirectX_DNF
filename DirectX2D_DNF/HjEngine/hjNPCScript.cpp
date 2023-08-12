#include "hjNPCScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	NPCScript::NPCScript()
	{
	}
	NPCScript::~NPCScript()
	{
	}
	void NPCScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_eff", 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_glow_eff_1", 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_glow_eff_1", 0.05f, Vector2::Zero, true);


		mAnimator->PlayAnimation(L"BackGroundgate_new_glow_eff_1", false);
		mAnimator->CompleteEvent(L"BackGroundgate_new_glow_eff_1") = std::bind(&NPCScript::BackGroundgate_new_glow_effCompleteEvent, this);
		mAnimator->CompleteEvent(L"BackGroundgate_new_glow_eff_1Back") = std::bind(&NPCScript::BackGroundgate_new_glow_eff_backCompleteEvent, this);
		mAnimator->CompleteEvent(L"BackGroundgate_new_eff") = std::bind(&NPCScript::BackGroundgate_new_effCompleteEvent, this);

		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetSize(Vector2{ 400.0f, 400.0f });
		mCollider->SetCenter(Vector2{ -80.0f, 0.0f });
	}
	void NPCScript::Update()
	{

	}




	void NPCScript::BackGroundgate_new_glow_effCompleteEvent()
	{
		mAnimator->PlayAnimation(L"BackGroundgate_new_eff", true);
	}
	void NPCScript::BackGroundgate_new_glow_eff_backCompleteEvent()
	{
		mAnimator->CloseAnimation();
	}
	void NPCScript::BackGroundgate_new_effCompleteEvent()
	{
		//mAnimator->PlayAnimation(L"BackGroundgate_new_glow_eff_1", false, true);
	}
}
