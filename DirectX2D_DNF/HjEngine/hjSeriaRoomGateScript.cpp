#include "hjSeriaRoomGateScript.h"
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

	SeriaRoomGateScript::SeriaRoomGateScript()
	{
	}
	SeriaRoomGateScript::~SeriaRoomGateScript()
	{
	}
	void SeriaRoomGateScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_eff", 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_glow_eff_1", 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_glow_eff_1", 0.05f, Vector2::Zero, true);
		
		mAnimator->PlayAnimation(L"BackGroundgate_new_glow_eff_1", false);
		mAnimator->CompleteEvent(L"BackGroundgate_new_glow_eff_1") = std::bind(&SeriaRoomGateScript::BackGroundgate_new_glow_effCompleteEvent, this);
		mAnimator->CompleteEvent(L"BackGroundgate_new_glow_eff_1Back") = std::bind(&SeriaRoomGateScript::BackGroundgate_new_glow_eff_backCompleteEvent, this);
		mAnimator->CompleteEvent(L"BackGroundgate_new_eff") = std::bind(&SeriaRoomGateScript::BackGroundgate_new_effCompleteEvent, this);
		
		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetType(eColliderType::Circle);
		mCollider->SetSize(Vector2{ 200.0f, 200.0f }, 1.0f);
		mCollider->SetRotation(math::degreeToRadian(60.0f));
		//GetOwner()->GetComponent<Transform>()->SetRotation2D(60.0f);
		mCollider->SetCenter(Vector2{ -80.0f, 0.0f });
		//mCollider->SetCenter(Vector2{ -200.0f, 0.0f });
	}
	void SeriaRoomGateScript::Update()
	{
	}

	void SeriaRoomGateScript::LateUpdate()
	{
		if (!(GetOwner()->GetComponent<Collider2D>()->GetCollision()))
			GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
	}
	
	
	
	
	void SeriaRoomGateScript::BackGroundgate_new_glow_effCompleteEvent()
	{
		mAnimator->PlayAnimation(L"BackGroundgate_new_eff", true);
	}
	void SeriaRoomGateScript::BackGroundgate_new_glow_eff_backCompleteEvent()
	{
		mAnimator->CloseAnimation();
	}
	void SeriaRoomGateScript::BackGroundgate_new_effCompleteEvent()
	{
		GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
		//mAnimator->PlayAnimation(L"BackGroundgate_new_glow_eff_1", false, true);
	}
}
