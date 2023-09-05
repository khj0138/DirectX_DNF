#include "hjPlayerScript.h"

#include "hjResources.h"
#include "hjInput.h"
#include "hjTime.h"
#include "hjCamera.h"

#include "hjGameObject.h"

#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"

#include "hjAttackScriptManager.h"
#include "hjAttackScript.h"
#include "hjBasicAttackScript1.h"
#include "hjBasicAttackScript2.h"
#include "hjBasicAttackScript3.h"
namespace hj
{

	PlayerScript::PlayerScript()
		: mActivate(false)
		, AtkManager(nullptr)
		, mStatus(status(100, 100))
		, moveVector({})
		, moveTime(0.0f)
		, mPlayerState(ePlayerState::Idle)
		, mPrevPlayerState(ePlayerState::Idle)
		, bRun(false)
		, jumpDown(false)
		, bCommand(false)
		, mVelocity(Vector3::Zero)
	{
		moveVector.resize(2);
		bAttackVector.resize((UINT)eAttackType::End);
		commandVector.resize((UINT)eAttackType::End);
		//mAttackVector.resize((UINT)eAttackType::End);

		mAttackVector.push_back(L"SwordManAttack1");
		mAttackVector.push_back(L"SwordManAttack2");
		mAttackVector.push_back(L"SwordManAttack3");


	}
	PlayerScript::~PlayerScript()
	{
		delete AtkManager;
	}
	void PlayerScript::Initialize()
	{
		GetOwner()->SetName(L"SwordMan2");
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3{ 320.0f, 320.0f, 2.0f });
		tr->SetPosition(Vector3(500.0f, 0.0f, 450.000f));
		Collider2D* mCollider = GetOwner()->AddComponent<Collider2D>();
		mCollider->SetSize(Vector2{ 25.0f, 25.0f }, GetOwner()->GetComponent<Transform>()->GetScale().y);

		Animator* mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2{ 20.0f, -80.0f });
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Run", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\JumpUp", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\JumpDown", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack1", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack2", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack3", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CompleteEvent(L"SwordManJumpUp") = std::bind(&PlayerScript::JumpUpCompleteEvent, this);
		mAnimator->StartEvent(L"SwordManAttack1") = std::bind(&PlayerScript::Attack1StartEvent, this);
		mAnimator->StartEvent(L"SwordManAttack2") = std::bind(&PlayerScript::Attack2StartEvent, this);
		mAnimator->StartEvent(L"SwordManAttack3") = std::bind(&PlayerScript::Attack3StartEvent, this);
		mAnimator->CompleteEvent(L"SwordManAttack1") = std::bind(&PlayerScript::Attack1CompleteEvent, this);
		mAnimator->CompleteEvent(L"SwordManAttack2") = std::bind(&PlayerScript::Attack2CompleteEvent, this);
		mAnimator->CompleteEvent(L"SwordManAttack3") = std::bind(&PlayerScript::Attack3CompleteEvent, this);
		mAnimator->PlayAnimation(L"SwordManIdle", true);

		GetOwner()->AddComponent<Rigidbody>();

		AtkManager = new AttackScriptManager();
		AtkManager->SetManagerOwner(GetOwner());
		AtkManager->SetType(eLayerType::PlayerAttack);

		AtkManager->RegisterAttackScript<BasicAttackScript1>(L"Attack1");
		AtkManager->RegisterAttackScript<BasicAttackScript2>(L"Attack2");
		AtkManager->RegisterAttackScript<BasicAttackScript3>(L"Attack3");
		
	}
	void PlayerScript::Update()
	{
		switch (mPlayerState)
		{
		case ePlayerState::Idle:
			Idle();
			break;

		case ePlayerState::Walk:
			Walk();
			break;

		case ePlayerState::Run:
			Run();
			break;

		case ePlayerState::Attack:
			Attack();
			break;

		case ePlayerState::Jump:
			Jump();
			break;
		default:
			break;
		}

		Anim();
		if (Input::GetKeyDown(eKeyCode::P))
		{
			if (GetOwner()->GetComponent<Collider2D>()->GetCollision())
			{
				GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
			}
			else
			{
				GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			}
		}
		mPrevPlayerState = mPlayerState;

		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float posVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AtkManager->SetPosition(Vector2{pos.x,pos.y}, posVZ);
		AtkManager->Update();
	}
	bool PlayerScript::IsWalk()
	{
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			GetOwner()->SetFlip(false);
			moveVector[0] = (UINT)(eKeyCode::RIGHT);
			return true;
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			GetOwner()->SetFlip(true);
			moveVector[0] = (UINT)(eKeyCode::LEFT);
			return true;
		}

		else if (Input::GetKey(eKeyCode::UP)
			|| Input::GetKey(eKeyCode::DOWN))
		{
			return true;
		}

		return false;
	}
	bool PlayerScript::IsRun()
	{
		moveTime += Time::DeltaTime();
		if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
		{
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				moveVector[0] = (UINT)eKeyCode::RIGHT;
				return true;
			}
		}
		else if ((eKeyCode)moveVector[0] == eKeyCode::LEFT)
		{
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				moveVector[0] = (UINT)eKeyCode::LEFT;
				return true;
			}
		}
		return false;
	}
	bool PlayerScript::IsJump()
	{
		if (Input::GetKeyDown(eKeyCode::C))
		{
			Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
			rb->SetGround(false);
			rb->SetVelocity(rb->GetVelocity() + Vector3::Up * 750.0f);
			return true;
		}
		return false;
	}
	void PlayerScript::Idle()
	{
		//moveVector.clear();
		//moveVector.resize(2);
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		moveTime = 0.0f;
		if (IsJump())
		{
			mPlayerState = ePlayerState::Jump;
		}
		else if (IsWalk())
		{
			bRun = true;
			mPlayerState = ePlayerState::Walk;
		}
		else if (Input::GetKey(eKeyCode::X))
		{
			bAttackVector[(UINT)eAttackType::Attack1] = true;
			bMove = false;
			commandVector[0] = (UINT)eKeyCode::X;
			mPlayerState = ePlayerState::Attack;
			mVelocity.x = 150.0f;
		}
		if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
		{
			GetOwner()->SetFlip(false);
		}
		else
		{
			GetOwner()->SetFlip(true);
		}
		Vector3 velocity = rb->GetVelocity();
		velocity.x = 0.0f;
		rb->SetVelocity(velocity);
	}
	void PlayerScript::Walk()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();

		if (bRun)
		{
			if (IsRun())
			{
				moveTime = 0.0f;
				mPlayerState = ePlayerState::Run;
				bRun = false;
				return;
			}
			else if (moveTime > 0.15f)
			{
				moveTime = 0.0f;
				bRun = false;
			}
		}
		else
		{

			if (Input::GetKeyNone(eKeyCode::RIGHT)
				&& Input::GetKeyNone(eKeyCode::LEFT)
				&& Input::GetKeyNone(eKeyCode::UP)
				&& Input::GetKeyNone(eKeyCode::DOWN))
			{
				moveTime += Time::DeltaTime();
				if (moveTime > 0.05f)
				{
					moveTime = 0.0f;
					velocity.x = 0.0f;
					mPlayerState = ePlayerState::Idle;
				}
			}
			else
			{
				moveTime = 0.0f;


				if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					bRun = true;
					GetOwner()->SetFlip(true);
					moveVector[0] = (UINT)eKeyCode::LEFT;
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					bRun = true;
					GetOwner()->SetFlip(false);
					moveVector[0] = (UINT)eKeyCode::RIGHT;
				}

				if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
				{
					if (Input::GetKeyUp(eKeyCode::RIGHT))
					{
						velocity.x = 0.0f;
						if (Input::GetKey(eKeyCode::LEFT))
						{

							GetOwner()->SetFlip(true);
							moveVector[0] = (UINT)eKeyCode::LEFT;
						}
					}
				}
				else if ((eKeyCode)moveVector[0] == eKeyCode::LEFT)
				{
					if (Input::GetKeyUp(eKeyCode::LEFT))
					{
						velocity.x = 0.0f;
						if (Input::GetKey(eKeyCode::RIGHT))
						{
							GetOwner()->SetFlip(false);
							moveVector[0] = (UINT)eKeyCode::RIGHT;
						}
					}
				}
				else
				{
					if (Input::GetKeyDown(eKeyCode::LEFT))
					{
						bRun = true;
						GetOwner()->SetFlip(true);
						moveVector[0] = (UINT)eKeyCode::LEFT;
					}
					else if (Input::GetKeyDown(eKeyCode::RIGHT))
					{
						bRun = true;
						GetOwner()->SetFlip(false);
						moveVector[0] = (UINT)eKeyCode::RIGHT;
					}
				}
			}
		}

		if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				velocity.x = 255.0f;
				//pos.x += 255.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
		else if ((eKeyCode)moveVector[0] == eKeyCode::LEFT)
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				velocity.x = -255.0f;
				//	pos.x -= 255.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = -255.0f;
			//tr->SetVirtualZ(virtualZ - 255.0f * Time::DeltaTime());
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = 255.0f;

			//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		}
		else if (Input::GetKeyNone(eKeyCode::UP) && Input::GetKeyNone(eKeyCode::DOWN))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = 0.0f;
			//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		}
		rb->SetVelocity(velocity);

		if (IsJump())
		{
			mPlayerState = ePlayerState::Jump;
		}
		if (Input::GetKey(eKeyCode::X))
		{
			bAttackVector[(UINT)eAttackType::Attack1] = true;
			bMove = false;
			commandVector[0] = (UINT)eKeyCode::X;
			mPlayerState = ePlayerState::Attack;
			mVelocity.x = 400.0f;
		}
	}
	void PlayerScript::Run()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		if (Input::GetKeyNone(eKeyCode::RIGHT)
			&& Input::GetKeyNone(eKeyCode::LEFT)
			&& Input::GetKeyNone(eKeyCode::UP)
			&& Input::GetKeyNone(eKeyCode::DOWN))
		{
			moveTime += Time::DeltaTime();
			if (moveTime > 0.05f)
			{
				moveTime = 0.0f;
				//moveVector[0] = 0;
				velocity.x = 0.0f;
				mPlayerState = ePlayerState::Idle;
			}
		}

		else
		{
			moveTime = 0.0f;


			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				GetOwner()->SetFlip(true);
				moveVector[0] = (UINT)eKeyCode::LEFT;
			}
			else if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				GetOwner()->SetFlip(false);
				moveVector[0] = (UINT)eKeyCode::RIGHT;
			}

			if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
			{
				if (Input::GetKeyUp(eKeyCode::RIGHT))
				{
					velocity.x = 0.0f;
					if (Input::GetKey(eKeyCode::LEFT))
					{
						GetOwner()->SetFlip(true);
						moveVector[0] = (UINT)eKeyCode::LEFT;
					}
				}
			}
			else if ((eKeyCode)moveVector[0] == eKeyCode::LEFT)
			{
				if (Input::GetKeyUp(eKeyCode::LEFT))
				{
					velocity.x = 0.0f;
					if (Input::GetKey(eKeyCode::RIGHT))
					{
						GetOwner()->SetFlip(false);
						moveVector[0] = (UINT)eKeyCode::RIGHT;
					}
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					GetOwner()->SetFlip(true);
					moveVector[0] = (UINT)eKeyCode::LEFT;
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					GetOwner()->SetFlip(false);
					moveVector[0] = (UINT)eKeyCode::RIGHT;
				}
			}

		}

		if ((eKeyCode)moveVector[0] == eKeyCode::RIGHT)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				GetOwner()->SetFlip(false);
				velocity.x = 510.0f;
				//pos.x += 510.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
		else if ((eKeyCode)moveVector[0] == eKeyCode::LEFT)
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				GetOwner()->SetFlip(true);
				velocity.x = -510.0f;
				//pos.x -= 510.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = -255.0f;
			//tr->SetVirtualZ(virtualZ - 255.0f * Time::DeltaTime());
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = 255.0f;

			//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		}
		else if (Input::GetKeyNone(eKeyCode::UP) && Input::GetKeyNone(eKeyCode::DOWN))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = 0.0f;
			//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		}
		rb->SetVelocity(velocity);
		if (IsJump())
		{
			mPlayerState = ePlayerState::Jump;
		}
	}
	void PlayerScript::Jump()
	{
		//moveTime += Time::DeltaTime();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (velocity.y < 0.0f && jumpDown == true)
		{
			jumpDown = false;
			animator->PlayAnimation(L"SwordManJumpDown", false);
		}
		if (rb->GetGround())
		{
			if (abs(velocity.x) < 500)
				mPlayerState = ePlayerState::Idle;
			else
				mPlayerState = ePlayerState::Run;
			return;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			GetOwner()->SetFlip(true);
			velocity.x = -1.0f * abs(velocity.x);

			//pos.x -= 255.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			GetOwner()->SetFlip(false);
			velocity.x = abs(velocity.x);

			//pos.x += 255.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if(Input::GetKey(eKeyCode::DOWN))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = -255.0f;
			//tr->SetVirtualZ(virtualZ - 255.0f * Time::DeltaTime());
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = 255.0f;

			//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		}
		else if (Input::GetKeyNone(eKeyCode::UP) && Input::GetKeyNone(eKeyCode::DOWN))
		{
			//float virtualZ = tr->GetVirtualZ();
			velocity.z = 0.0f;
			//tr->SetVirtualZ(virtualZ + 255.0f * Time::DeltaTime());
		}
		rb->SetVelocity(velocity);
	}
	void PlayerScript::Attack()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKeyDown(eKeyCode::X))
		{
			for (UINT i = 0; i < (UINT)eAttackType::End; i++)
			{
				if (commandVector[i] != (UINT)eKeyCode::X)
				{
				commandVector[i] = (UINT)eKeyCode::X;
					break;
				}
				else
				{
					continue;
				}
			}
		}

		if (commandTime > 0.2f)
		{
			commandTime = 0.0f;
			bCommand = false;
			mPlayerState = ePlayerState::Idle;
			moveTime = 0.0f;
			bMove = false;
			for (UINT i = 0; i < (UINT)eAttackType::End; i++)
			{
				commandVector[i] = 0;
				bAttackVector[i] = false;
			}
		}



		if (bCommand)
			commandTime += Time::DeltaTime();
		else
			commandTime = 0.0f;

		for (UINT i = 0; i < (UINT)eAttackType::End; i++)
		{
			if (bAttackVector[i] && (commandVector[i] == (UINT)eKeyCode::X))
			{
				if (Input::GetKey(eKeyCode::LEFT))
				{
					GetOwner()->SetFlip(true);
					//mVelocity.x = -600.0f;
				}
				else if (Input::GetKey(eKeyCode::RIGHT))
				{
					GetOwner()->SetFlip(false);
					//mVelocity.x = 600.0f;
				}
				/*else if (isFlip)
				{
					mVelocity.x = -150.0f;
				}
				else if (!isFlip)
				{
					mVelocity.x = 150.0f;
				}*/


				bAttackVector[i] = false;
				bCommand = false;
				commandTime = 0.0f;
				animator->PlayAnimation(mAttackVector[i], false);
				moveTime = 0.0f;
				bMove = true;
				break;
			}
			else
			{
				continue;
			}
		}


		if (bMove)
		{
			moveTime += Time::DeltaTime();
		}
		else
			moveTime = 0.0f;

		//velocity.x = mVelocity.x;
		if (bMove && moveTime <= 0.2f)
		{
			velocity.x = mVelocity.x;
			if (GetOwner()->GetFlip())
				velocity.x = -1.0f * abs(velocity.x);
		}
		else
		{
			bMove = false;
			velocity.x = 0.0f;
		}

		rb->SetVelocity(velocity);
	}
	void PlayerScript::Anim()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->SetFlip(GetOwner()->GetFlip());
		switch (mPlayerState)
		{
		case ePlayerState::Idle:
			if (mPrevPlayerState != mPlayerState)
				animator->PlayAnimation(L"SwordManIdle", true);
			break;
		case ePlayerState::Walk:
			if (mPrevPlayerState != mPlayerState)
				animator->PlayAnimation(L"SwordManWalk", true);
			break;
		case ePlayerState::Run:
			if (mPrevPlayerState != mPlayerState)
				animator->PlayAnimation(L"SwordManRun", true);
			break;
		case ePlayerState::Attack:
			break;
		case ePlayerState::Jump:
			if (mPrevPlayerState != mPlayerState)
				animator->PlayAnimation(L"SwordManJumpUp", false);
			break;
		default:
			break;
		}
	}
	void PlayerScript::JumpUpStartEvent()
	{
		jumpDown = false;
	}
	void PlayerScript::JumpUpCompleteEvent()
	{
		jumpDown = true;
	}
	void PlayerScript::Attack1StartEvent()
	{
		moveTime = 0.0f;
		bMove = true;
		AtkManager->LoadAttackScript(L"Attack1");

	}
	void PlayerScript::Attack2StartEvent()
	{
		moveTime = 0.0f;
		bMove = true;
		AtkManager->LoadAttackScript(L"Attack2");
	}
	void PlayerScript::Attack3StartEvent()
	{
		moveTime = 0.0f;
		bMove = true;
		AtkManager->LoadAttackScript(L"Attack3");
	}
	void PlayerScript::Attack1CompleteEvent()
	{
		bAttackVector[(UINT)eAttackType::Attack2] = true;
		bCommand = true;
		bMove = false;
	}
	void PlayerScript::Attack2CompleteEvent()
	{
		bAttackVector[(UINT)eAttackType::Attack3] = true;
		bCommand = true;
		bMove = false;
	}
	void PlayerScript::Attack3CompleteEvent()
	{
		bCommand = true;
	}

	void PlayerScript::EnterScene()
	{
		AtkManager->EnterScene();
	}

	void PlayerScript::ExitScene()
	{
		AtkManager->ExitScene();
	}
}
