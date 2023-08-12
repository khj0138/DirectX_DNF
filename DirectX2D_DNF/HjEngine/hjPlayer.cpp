#include "hjPlayer.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	Player::Player()
		: mActivate(false)
		, coolTime(0.0f)
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GetComponent<Transform>()->SetScale(Vector3{ 320.0f, 320.0f, 2.0f });
		SetName(L"SwordMan2");
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
	

		Animator * mAnimator = AddComponent<Animator>();
		AddComponent<Collider2D>();
		
		mAnimator = GetComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Run", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\JumpUp", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\JumpDown", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack1", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack2", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack3", 0.03f, Vector2(0.0f, 00.0f));

		AddComponent<PlayerScript>();

		AddComponent<Rigidbody>();
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

	}

	void Player::Render()
	{
		GameObject::Render();

	}

	void Player::OnCollisionEnter(Collider2D* other)
	{

		
	}

	void Player::OnCollisionStay(Collider2D* other)
	{
		
	}

	void Player::OnCollisionExit(Collider2D* other)
	{
	}

	



}
