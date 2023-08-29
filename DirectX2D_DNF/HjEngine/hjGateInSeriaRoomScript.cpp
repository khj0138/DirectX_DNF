#include "hjGateInSeriaRoomScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
//#include "hjComponent.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	GateInSeriaRoomScript::GateInSeriaRoomScript()
	{
	}
	GateInSeriaRoomScript::~GateInSeriaRoomScript()
	{
	}
	void GateInSeriaRoomScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_eff", 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_glow_eff_1", 0.03f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_glow_eff_1", 0.01f, Vector2::Zero, true);
		
		mAnimator->CompleteEvent(L"BackGroundgate_new_glow_eff_1") = std::bind(&GateInSeriaRoomScript::BackGroundgate_new_glow_effCompleteEvent, this);
		mAnimator->CompleteEvent(L"BackGroundgate_new_glow_eff_1Back") = std::bind(&GateInSeriaRoomScript::BackGroundgate_new_glow_eff_backCompleteEvent, this);
		mAnimator->CompleteEvent(L"BackGroundgate_new_eff") = std::bind(&GateInSeriaRoomScript::BackGroundgate_new_effCompleteEvent, this);
		
		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetType(eColliderType::Circle);
		mCollider->SetSize(Vector2{ 400.0f, 400.0f }, 1.0f);
		//mCollider->SetRotation(math::degreeToRadian(60.0f));
		//GetOwner()->GetComponent<Transform>()->SetRotation2D(60.0f);
		/*if (GetOwner()->GetFlip())
			mCollider->SetCenter(Vector2{ 80.0f, 0.0f });
		else*/
		mCollider->SetCenter(Vector2{ -40.0f, 0.0f });
		//mCollider->SetCenter(Vector2{ -200.0f, 0.0f 
	}
	void GateInSeriaRoomScript::Update()
	{
	}

	void GateInSeriaRoomScript::LateUpdate()
	{
	}

	void GateInSeriaRoomScript::OnCollisionEnter(Collider2D* other)
	{
		mAnimator->PlayAnimation(L"BackGroundgate_new_glow_eff_1", false);
	}

	void GateInSeriaRoomScript::OnCollisionStay(Collider2D* other)
	{

	}

	void GateInSeriaRoomScript::OnCollisionExit(Collider2D* other)
	{
		mAnimator->PlayAnimation(L"BackGroundgate_new_glow_eff_1Back", false, true);
	}
	
	
	
	
	void GateInSeriaRoomScript::BackGroundgate_new_glow_effCompleteEvent()
	{
		mAnimator->PlayAnimation(L"BackGroundgate_new_eff", true);
	}
	void GateInSeriaRoomScript::BackGroundgate_new_glow_eff_backCompleteEvent()
	{
		mAnimator->CloseAnimation();
	}
	void GateInSeriaRoomScript::BackGroundgate_new_effCompleteEvent()
	{
		GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
		//mAnimator->PlayAnimation(L"BackGroundgate_new_glow_eff_1", false, true);
	}
}
