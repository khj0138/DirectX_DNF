#include "hjCommonPortalScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
//#include "hjSceneManager.h"
//#include "hjMonsterScript.h"
//#include "hjComponent.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	CommonPortalScript::CommonPortalScript()
	{
	}
	CommonPortalScript::~CommonPortalScript()
	{
	}
	void CommonPortalScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\portal\\gate", 0.07f);

		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetType(eColliderType::Circle);
		mCollider->SetSize(Vector2{ 400.0f, 400.0f }, 1.0f);
	}
	void CommonPortalScript::Update()
	{
		if (mAnimator->GetActiveAnimation() == nullptr)
		{
			mAnimator->PlayAnimation(L"portalgate", true);
		}
	}

	void CommonPortalScript::LateUpdate()
	{
	}

	void CommonPortalScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void CommonPortalScript::OnCollisionStay(Collider2D* other)
	{

	}

	void CommonPortalScript::OnCollisionExit(Collider2D* other)
	{
		
	}




	void CommonPortalScript::MainCampCreateGateCompleteEvent()
	{
	}
	void CommonPortalScript::MainCampDestroyGateBackCompleteEvent()
	{
	}
	void CommonPortalScript::MainCampGateGlowCompleteEvent()
	{
	}
}
