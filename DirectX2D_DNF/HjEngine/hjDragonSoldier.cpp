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

		SetStatus(Monster::status(100, 100));
	}
	DragonSoldier::~DragonSoldier()
	{
	}
	void DragonSoldier::Initialize()
	{
		SetCoolTime(3.0f);
		Monster::Initialize();
		GetComponent<Transform>()->SetScale(Vector3{ 401.0f, 325.0f, 2.0f });
		SetName(L"DragonSoldier");
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));


		Animator* mAnimator = GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Die", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Hit", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Attack1", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\dragon_soldier\\Attack2", 0.1f, Vector2(0.0f, 00.0f));

		AddComponent<Rigidbody>();

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

}
