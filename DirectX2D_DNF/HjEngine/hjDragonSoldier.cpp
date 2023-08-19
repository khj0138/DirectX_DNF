#include "hjDragonSoldier.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"

#include "hjDragonSoldierScript.h"
#include "hjAttackScriptManager.h"
#include "hjBasicAttackScript1.h"
#include "hjBasicAttackScript2.h"
#include "hjBasicAttackScript3.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	DragonSoldier::DragonSoldier()
		: mActivate(false)
	{
	}
	DragonSoldier::~DragonSoldier()
	{
	}
	void DragonSoldier::Initialize()
	{
		Monster::Initialize();
		GetComponent<Transform>()->SetScale(Vector3{ 401.0f, 325.0f, 2.0f });
		SetName(L"DragonSoldier");


		Animator* mAnimator = GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Die", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Hit", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Attack1", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Attack2", 0.1f, Vector2(0.0f, 00.0f));

		AddComponent<DragonSoldierScript>();
	}
	void DragonSoldier::Update()
	{
		Monster::Update();
	}

	void DragonSoldier::LateUpdate()
	{
		Monster::LateUpdate();

	}

	void DragonSoldier::Render()
	{
		Monster::Render();

	}

	void DragonSoldier::OnCollisionEnter(Collider2D* other)
	{


	}

	void DragonSoldier::OnCollisionStay(Collider2D* other)
	{

	}

	void DragonSoldier::OnCollisionExit(Collider2D* other)
	{
	}

}
