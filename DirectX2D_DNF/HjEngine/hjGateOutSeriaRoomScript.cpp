#include "hjGateOutSeriaRoomScript.h"
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

	GateOutSeriaRoomScript::GateOutSeriaRoomScript()
	{
	}
	GateOutSeriaRoomScript::~GateOutSeriaRoomScript()
	{
	}
	void GateOutSeriaRoomScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\MainCamp\\seriaRoomGate\\GateGlow", 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\MainCamp\\seriaRoomGate\\CreateGate", 0.03f);
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Town\\MainCamp\\seriaRoomGate\\DestroyGate", 0.02f, Vector2::Zero, true);

		mAnimator->CompleteEvent(L"seriaRoomGateCreateGate") = std::bind(&GateOutSeriaRoomScript::MainCampCreateGateCompleteEvent, this);
		mAnimator->CompleteEvent(L"seriaRoomGateDestroyGateBack") = std::bind(&GateOutSeriaRoomScript::MainCampDestroyGateBackCompleteEvent, this);
		mAnimator->CompleteEvent(L"seriaRoomGateGateGlow") = std::bind(&GateOutSeriaRoomScript::MainCampGateGlowCompleteEvent, this);

		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetType(eColliderType::Circle);
		mCollider->SetSize(Vector2{ 400.0f, 400.0f }, 1.0f);
		//mCollider->SetRotation(math::degreeToRadian(60.0f));
		//GetOwner()->GetComponent<Transform>()->SetRotation2D(60.0f);
		mCollider->SetCenter(Vector2{ 00.0f, 0.0f });
		//mCollider->SetCenter(Vector2{ -200.0f, 0.0f 
	}
	void GateOutSeriaRoomScript::Update()
	{
	}

	void GateOutSeriaRoomScript::LateUpdate()
	{
	}

	void GateOutSeriaRoomScript::OnCollisionEnter(Collider2D* other)
	{
		mAnimator->PlayAnimation(L"seriaRoomGateCreateGate", false);
	}

	void GateOutSeriaRoomScript::OnCollisionStay(Collider2D* other)
	{

	}

	void GateOutSeriaRoomScript::OnCollisionExit(Collider2D* other)
	{
		mAnimator->PlayAnimation(L"seriaRoomGateDestroyGateBack", false, true);
	}




	void GateOutSeriaRoomScript::MainCampCreateGateCompleteEvent()
	{
		mAnimator->PlayAnimation(L"seriaRoomGateGateGlow", true);
	}
	void GateOutSeriaRoomScript::MainCampDestroyGateBackCompleteEvent()
	{
		mAnimator->CloseAnimation();
	}
	void GateOutSeriaRoomScript::MainCampGateGlowCompleteEvent()
	{
	}
}
