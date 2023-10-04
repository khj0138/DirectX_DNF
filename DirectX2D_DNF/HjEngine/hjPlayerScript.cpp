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
#include "hjBasicAttackScript.h"
#include "hjRushAttackScript.h"
#include "hjUpperSlashAttackScript.h"
#include "hjIceWaveAttackScript.h"
#include "hjFireWaveAttackScript.h"
#include "hjThrustAttackScript.h"
namespace hj
{

	PlayerScript::PlayerScript()
		: mActivate(false)
		, AtkManager(nullptr)
		, mStatus(status(10, 10, false))
		, mPlayerState(ePlayerState::Idle)
		, mPrevPlayerState(ePlayerState::Idle)
		, bRun(false)
		, jumpDown(false)
		, bCommand(false)
		, mVelocity(Vector3::Zero)
		, mHitTime(0.0f)
		, mCurTime(0.0f)
	{
		//bAttackVector.resize((UINT)eAttackType::End);
		//commandVector.resize((UINT)eAttackType::End);
		//mAttackVector.resize((UINT)eAttackType::End);

		/*mAttackVector.push_back(L"SwordManAttack1");
		mAttackVector.push_back(L"SwordManAttack2");
		mAttackVector.push_back(L"SwordManAttack3");*/


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
		mCollider->SetSize(Vector2{ 50.0f, 50.0f }, 120.0f);

		Animator* mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2{ 20.0f, -80.0f });
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Run", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\JumpUp", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\JumpDown", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Basic\\Attack1", 0.02f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Basic\\Attack2", 0.02f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Basic\\Attack3", 0.02f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Rush\\Rush1", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Rush\\Rush2", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Rush\\Rush3", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_UpperSlash\\Attack", 0.02f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Wave\\IceWave", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Wave\\FireWave", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Thrust\\Thrust1", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack_Thrust\\Thrust2", 0.03f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Hit", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\HitUp", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\HitDown", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Die", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CompleteEvent(L"SwordManJumpUp") = std::bind(&PlayerScript::JumpUpCompleteEvent, this);
		//mAnimator->StartEvent(L"Attack_BasicAttack1") = std::bind(&PlayerScript::Attack1StartEvent, this);
		//mAnimator->StartEvent(L"Attack_BasicAttack2") = std::bind(&PlayerScript::Attack1StartEvent, this);
		//mAnimator->StartEvent(L"Attack_BasicAttack3") = std::bind(&PlayerScript::Attack1StartEvent, this);
		//mAnimator->CompleteEvent(L"SwordManAttack1") = std::bind(&PlayerScript::Attack1CompleteEvent, this);
		//mAnimator->CompleteEvent(L"SwordManAttack2") = std::bind(&PlayerScript::Attack2CompleteEvent, this);
		//mAnimator->CompleteEvent(L"SwordManAttack3") = std::bind(&PlayerScript::Attack3CompleteEvent, this);
		mAnimator->PlayAnimation(L"SwordManIdle", true);

		GetOwner()->AddComponent<Rigidbody>();

		AtkManager = new AttackScriptManager();
		AtkManager->SetManagerOwner(GetOwner());
		AtkManager->SetType(eLayerType::PlayerAttack);

		AtkManager->RegisterAttackScript<BasicAttackScript>(L"Attack_Basic");
		AtkManager->RegisterAttackScript<RushAttackScript>(L"Attack_Rush");
		AtkManager->RegisterAttackScript<UpperSlashAttackScript>(L"Attack_UpperSlash");
		AtkManager->RegisterAttackScript<IceWaveAttackScript>(L"Attack_IceWave");
		//AtkManager->RegisterAttackScript<FireWaveAttackScript>(L"Attack_FireWave");
		AtkManager->RegisterAttackScript<ThrustAttackScript>(L"Attack_Thrust");
		
	}
	void PlayerScript::Update()
	{
		SetCurTime(GetCurTime() + Time::DeltaTime());
		CommandCheck();
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
		case ePlayerState::Hit:
			Hit();
			break;
		case ePlayerState::Die:
			Die();
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
	void PlayerScript::LateUpdate()
	{
		AtkManager->LateUpdate();
	}
	void PlayerScript::Render()
	{
		AtkManager->Render();
	}
	void PlayerScript::Hit(UINT damage, bool flip, Vector2 direction)
	{
		mStatus.HP > damage ? mStatus.HP = mStatus.HP - damage : mStatus.HP = 0;


		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();
		if (flip)
		{
			direction.x *= -1.f;
		}

		if (mPlayerState != ePlayerState::Hit)
		{
			if (mStatus.HP == 0)
			{
				mPlayerState = ePlayerState::Die;
				SetCurTime(0.0f);
			}
			else
			{
				if (!mStatus.SuperArmor)
				{
					GetOwner()->SetFlip(!flip);
					mPlayerState = ePlayerState::Hit;
					rb->SetVelocity(Vector3(direction.x, direction.y, vel.z));
					if (rb->GetGround() && direction.y > 0.0f)
						rb->SetGround(false);
				}
			}
		}
		else
		{

			if (rb->GetGround())
			{
				if (mStatus.HP == 0)
				{
					mPlayerState = ePlayerState::Die;
					SetCurTime(0.0f);

				}
				else
				{
					if (!mStatus.SuperArmor)
					{
						GetOwner()->SetFlip(!flip);
						if (direction.y > 0.0f)
							rb->SetGround(false);
						rb->SetVelocity(Vector3(direction.x, direction.y, vel.z));
					}
				}
			}
			else
			{
				if (!mStatus.SuperArmor)
				{
					GetOwner()->SetFlip(!flip);
					rb->SetVelocity(Vector3(direction.x, direction.y + vel.y, vel.z));
				}
			}
		}
	}
	PlayerScript::eCommandType PlayerScript::CheckMoveDirection()
	{
		for (int i = mCommandVector.size(); i > 0; i--)
		{
			if(mCommandVector[i].type == eCommandType::LEFT || mCommandVector[i].type == eCommandType::RIGHT)
				return mCommandVector[i].type;
		}
		return eCommandType::End;
	}
	void PlayerScript::CommandCheck()
	{
		UINT deleteIndex = 0;
		for (int command = 0; command < mCommandVector.size(); command++)
		{
			if (mCommandVector[command].time >= 5.0f)
			{
				deleteIndex++;
			}
			mCommandVector[command].time += Time::DeltaTime();
		}
		for (int i = 0; i < deleteIndex; i++)
		{
			mCommandVector.pop_back();
		}
		Command input = { eCommandType::End, 0.0f };
		if (Input::GetKeyDown(eKeyCode::C))
		{
			input.type = eCommandType::C;
		}
		else if (Input::GetKeyDown(eKeyCode::X))
		{
			input.type = eCommandType::X;
		}
		else if (Input::GetKeyDown(eKeyCode::Z))
		{
			input.type = eCommandType::Z;
		}
		else if (Input::GetKeyDown(eKeyCode::D))
		{
			input.type = eCommandType::D;
		}
		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			input.type = eCommandType::DOWN;
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisY].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisY].begin(), mMoveVector[(UINT)eMoveType::axisY].end(), eCommandType::DOWN);
				if (temp != mMoveVector[(UINT)eMoveType::axisY].end())
				{
					mMoveVector[(UINT)eMoveType::axisY].erase(temp);
					break;
				}
			}
			mMoveVector[(UINT)eMoveType::axisY].push_back(input.type);
		}
		else if (Input::GetKeyDown(eKeyCode::UP))
		{
			input.type = eCommandType::UP;
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisY].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisY].begin(), mMoveVector[(UINT)eMoveType::axisY].end(), eCommandType::UP);
				if (temp != mMoveVector[(UINT)eMoveType::axisY].end())
				{
					mMoveVector[(UINT)eMoveType::axisY].erase(temp);
					break;
				}
			}
			mMoveVector[(UINT)eMoveType::axisY].push_back(input.type);
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			input.type = eCommandType::LEFT;
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisX].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisX].begin(), mMoveVector[(UINT)eMoveType::axisX].end(), eCommandType::LEFT);
				if (temp != mMoveVector[(UINT)eMoveType::axisX].end())
				{
					mMoveVector[(UINT)eMoveType::axisX].erase(temp);
					break;
				}
			}
			mMoveVector[(UINT)eMoveType::axisX].push_back(input.type);
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			input.type = eCommandType::RIGHT;
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisX].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisX].begin(), mMoveVector[(UINT)eMoveType::axisX].end(), eCommandType::RIGHT);
				if (temp != mMoveVector[(UINT)eMoveType::axisX].end())
				{
					mMoveVector[(UINT)eMoveType::axisX].erase(temp);
					break;
				}
			}
			mMoveVector[(UINT)eMoveType::axisX].push_back(input.type);
		}

		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisX].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisX].begin(), mMoveVector[(UINT)eMoveType::axisX].end(), eCommandType::LEFT);
				if (temp != mMoveVector[(UINT)eMoveType::axisX].end())
				{
					mMoveVector[(UINT)eMoveType::axisX].erase(temp);
					break;
				}
			}
		}
		if( Input::GetKeyUp(eKeyCode::RIGHT))
		{
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisX].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisX].begin(), mMoveVector[(UINT)eMoveType::axisX].end(), eCommandType::RIGHT);
				if (temp != mMoveVector[(UINT)eMoveType::axisX].end())
				{
					mMoveVector[(UINT)eMoveType::axisX].erase(temp);
					break;
				}
			}
		}
		if (Input::GetKeyUp(eKeyCode::UP))
		{
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisY].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisY].begin(), mMoveVector[(UINT)eMoveType::axisY].end(), eCommandType::UP);
				if (temp != mMoveVector[(UINT)eMoveType::axisY].end())
				{
					mMoveVector[(UINT)eMoveType::axisY].erase(temp);
					break;
				}
			}
		}
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			for (int i = 0; i < mMoveVector[(UINT)eMoveType::axisY].size(); i++)
			{
				std::vector<eCommandType>::iterator temp = find(mMoveVector[(UINT)eMoveType::axisY].begin(), mMoveVector[(UINT)eMoveType::axisY].end(), eCommandType::DOWN);
				if (temp != mMoveVector[(UINT)eMoveType::axisY].end())
				{
					mMoveVector[(UINT)eMoveType::axisY].erase(temp);
					break;
				}
			}
		}


		if (input.type != eCommandType::End)
			mCommandVector.push_back(input);
	}
	bool PlayerScript::IsWalk()
	{
		if (mMoveVector[(UINT)eMoveType::axisX].empty() && mMoveVector[(UINT)eMoveType::axisY].empty())
			return false;
		return true;
	}
	bool PlayerScript::IsRun()
	{
		
		int size = mCommandVector.size();
		if (size >= 2)
		{
			if (mCommandVector[size - 1].type == eCommandType::RIGHT && mCommandVector[size - 2].type == eCommandType::RIGHT)
			{
				GetOwner()->SetFlip(false);
				mCommandVector.clear();
				return true;
			}
			else if (mCommandVector[size - 1].type == eCommandType::LEFT && mCommandVector[size - 2].type == eCommandType::LEFT)
			{
				GetOwner()->SetFlip(true);
				mCommandVector.clear();
				return true;
			}
		}
		return false;
	}
	bool PlayerScript::IsJump()
	{
		int size = mCommandVector.size();
		if (size >= 1)
		{
			if (mCommandVector[size - 1].type == eCommandType::C)
			{
				Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(false);
				rb->SetVelocity(rb->GetVelocity() + Vector3::Up * 750.0f);
				mCommandVector.clear();
				return true;
			}
		}
		return false;
	}
	bool PlayerScript::IsAttack()
	{

		for (auto iter = AtkManager->mAttackScripts.begin(); iter != AtkManager->mAttackScripts.end(); iter++)
		{
			if (AtkManager->LoadAttackScript(iter->first) != nullptr)
			{
				Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
				Vector3 vel = rb->GetVelocity();
				vel.x = 0.0f;
				vel.z = 0.0f;
				rb->SetVelocity(vel);
			
				attackName = iter->first;

				return true;
			}
		}

		return false;
	}
	void PlayerScript::Idle()
	{

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		if (IsAttack())
		{
			mPlayerState = ePlayerState::Attack;
			Attack();
			return;
		}
		if (IsJump())
		{
			mPlayerState = ePlayerState::Jump;
			return;
		}
		if (IsWalk())
		{
			mPlayerState = ePlayerState::Walk;
			return;
		}


		
		
		Vector3 velocity = rb->GetVelocity();
		velocity.x = 0.0f;
		velocity.z = 0.0f;
		rb->SetVelocity(velocity);
	}
	void PlayerScript::Walk()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();

		if (IsRun())
		{
			mPlayerState = ePlayerState::Run;
			return;
		}
		int size = mMoveVector[(UINT)eMoveType::axisX].size();
		if(size >= 1)
		{
			if(mMoveVector[(UINT)eMoveType::axisX][size -1] == eCommandType::RIGHT)
			{
				velocity.x = 255.0f;
				if (GetOwner()->GetFlip())
					GetOwner()->SetFlip(false);
			}
			else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
			{
				velocity.x = -255.0f;
				if (!GetOwner()->GetFlip())
					GetOwner()->SetFlip(true);
			}
		}
		size = mMoveVector[(UINT)eMoveType::axisY].size();
		if (size >= 1)
		{
			if (mMoveVector[(UINT)eMoveType::axisY][size - 1] == eCommandType::UP)
			{
				velocity.z = 255.0f;
			}
			else if (mMoveVector[(UINT)eMoveType::axisY][size - 1] == eCommandType::DOWN)
			{
				velocity.z = -255.0f;
			}
		}
		if (mMoveVector[(UINT)eMoveType::axisX].empty())
		{
			velocity.x = 0.0f;
		}
		if (mMoveVector[(UINT)eMoveType::axisY].empty())
		{
			velocity.z = 0.0f;
		}
		rb->SetVelocity(velocity);

		if (velocity.x == 0.0f && velocity.z == 0.0f)
		{
			mPlayerState = ePlayerState::Idle;
			return;
		}

		if (IsAttack())
		{
			mPlayerState = ePlayerState::Attack;
			Attack();
			return;
		}
		if (IsJump())
		{
			mPlayerState = ePlayerState::Jump;
			return;
		}
	}
	void PlayerScript::Run()
	{
		if (IsAttack())
		{
			mPlayerState = ePlayerState::Attack;
			Attack();
			return;
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();

		int size = mMoveVector[(UINT)eMoveType::axisX].size();
		if (size >= 1)
		{
			if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
			{
				velocity.x = 510.0f;
				if (GetOwner()->GetFlip())
					GetOwner()->SetFlip(false);
			}
			else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
			{
				velocity.x = -510.0f;
				if (!GetOwner()->GetFlip())
					GetOwner()->SetFlip(true);
			}
		}
		size = mMoveVector[(UINT)eMoveType::axisY].size();
		if (size >= 1)
		{
			if (mMoveVector[(UINT)eMoveType::axisY][size - 1] == eCommandType::UP)
			{
				velocity.z = 255.0f;
			}
			else if (mMoveVector[(UINT)eMoveType::axisY][size - 1] == eCommandType::DOWN)
			{
				velocity.z = -255.0f;
			}
		}
		if (mMoveVector[(UINT)eMoveType::axisX].empty())
		{
			velocity.x = 0.0f;
		}
		if (mMoveVector[(UINT)eMoveType::axisY].empty())
		{
			velocity.z = 0.0f;
		}
		rb->SetVelocity(velocity);

		if (velocity.x == 0.0f && velocity.z == 0.0f)
		{
			mPlayerState = ePlayerState::Idle;
			return;
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
		Animation* animation = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
		if (attackName == L"Attack_Rush")
		{
			Attack_Rush();
		}
		else if (attackName == L"Attack_UpperSlash")
		{
			Attack_UpperSlash();
		}
		else if (attackName == L"Attack_Basic")
		{
			Attack_Basic();
		}
		else if (attackName == L"Attack_IceWave")
		{
			Attack_IceWave();
		}
		else if (attackName == L"Attack_FireWave")
		{
			Attack_FireWave();
		}
		else if (attackName == L"Attack_Thrust")
		{
			Attack_Thrust();
		}
		
	}
	void PlayerScript::Anim()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		//animator->SetFlip(GetOwner()->GetFlip());
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
		case ePlayerState::Hit:
			AnimHit();
			break;
		case ePlayerState::Die:
			if (mPrevPlayerState != mPlayerState)
				animator->PlayAnimation(L"SwordManDie", false);
			break;
			break;
		case ePlayerState::Jump:
			if (mPrevPlayerState != mPlayerState)
				animator->PlayAnimation(L"SwordManJumpUp", false);
			break;
		default:
			break;
		}
	}
	void PlayerScript::Die()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		rb->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
		mCurTime += Time::DeltaTime();
		if (mCurTime > 1.0f)
		{
			mStatus.HP = mStatus.maxHP;
			mPlayerState = ePlayerState::Idle;
			mCurTime = 0.0f;
		}
	}
	void PlayerScript::Hit()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		if (rb->GetGround())
		{
			if (abs(velocity.y) > 200.0f)
			{
				rb->SetGround(false);
				velocity.y *= -0.5f;
				velocity.x *= 0.5f;
				rb->SetVelocity(velocity);
			}
			else
			{
				mHitTime = (mHitTime + Time::DeltaTime());
			}
		}
		else
		{
			mHitTime = 0.0f;
		}

		if (mHitTime >= 0.3f)
		{
			rb->SetVelocity(Vector3::Zero);
			if (GetStatus().HP > 0.0f)
			{
				mHitTime = 0.0f;
				mPlayerState = ePlayerState::Idle;
			}
			else
			{
				//mCurTime = 0.0f;
				mPlayerState = ePlayerState::Die;
				SetCurTime(0.0f);

			}

		}
	}
	void PlayerScript::AnimHit()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		Animation* activeAnim = mAnimator->GetActiveAnimation();
		if (mPrevPlayerState != mPlayerState)
		{
			if (rb->GetGround())
				mAnimator->PlayAnimation(L"SwordManHit", false);
			else
			{
				mAnimator->PlayAnimation(L"SwordManHitUp", false);
			}
		}
		else if (activeAnim->GetKey() == L"SwordManHitUp")
		{
			if (velocity.y < 0.0f)
			{
				mAnimator->PlayAnimation(L"SwordManHitDown", false);
				activeAnim->SetPause(true);
			}
		}
		else if (activeAnim->GetKey() == L"SwordManHitDown")
		{
			if (velocity.y < 0.0f)
			{
				activeAnim->SetIndex(0);
			}
			else if (velocity.y > 0.0f)
			{
				activeAnim->SetIndex(1);
			}
			else
			{
				activeAnim->SetIndex(2);
				activeAnim->SetPause(false);
			}
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
		AtkManager->LoadAttackScript(L"Attack1");

	}
	void PlayerScript::Attack2StartEvent()
	{
		AtkManager->LoadAttackScript(L"Attack2");
	}
	void PlayerScript::Attack3StartEvent()
	{
		AtkManager->LoadAttackScript(L"Attack3");
	}
	void PlayerScript::Attack1CompleteEvent()
	{
		bAttackVector[(UINT)eAttackType::Attack2] = true;
	}
	void PlayerScript::Attack2CompleteEvent()
	{
		bAttackVector[(UINT)eAttackType::Attack3] = true;
	}
	void PlayerScript::Attack3CompleteEvent()
	{
		bCommand = true;
	}

	void PlayerScript::Attack_Basic()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animation* activeAnim = animator->GetActiveAnimation();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();

		if (activeAnim->GetKey() == L"Attack_BasicAttack1")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.1f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.09f)
				{
					int size = mCommandVector.size();
					if (size >= 1)
					{
						for (int i = 0; i < size; i++)
						{
							if (mCommandVector[i].type == PlayerScript::eCommandType::X)
							{
								animator->PlayAnimation(L"Attack_BasicAttack2", false);
								mCommandVector.clear();
								SetCurTime(0.0f);
								break;
							}
						}
					}
				}
				else if (activeAnim->IsComplete() && GetCurTime() > 0.09f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						vel.x = 510.0f;
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						vel.x = -510.0f;
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				else
				{
					if (GetOwner()->GetFlip())
					{
						vel.x = -255.0f;
					}
					else
					{
						vel.x = 255.0f;
					}
				}
			}
			else
			{
				if (GetCurTime() > 0.066f)
				{
					if (vel.x != 0.0f)
						mVelocity = vel;
					vel.x = 0.0f;
				}
			}
		}
		else if (activeAnim->GetKey() == L"Attack_BasicAttack2")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;

				if (GetCurTime() > 0.1f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.09f)
				{
					int size = mCommandVector.size();
					if (size >= 1)
					{
						for (int i = 0; i < size; i++)
						{
							if (mCommandVector[i].type == PlayerScript::eCommandType::X)
							{
								animator->PlayAnimation(L"Attack_BasicAttack3", false);
								mCommandVector.clear();
								SetCurTime(0.0f);
								break;
							}
						}
					}
				}
				else if (activeAnim->IsComplete() && GetCurTime() > 0.09f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				if (GetOwner()->GetFlip())
				{
					vel.x = -1.f * abs(mVelocity.x);
				}
				else
				{
					vel.x = abs(mVelocity.x);
				}
			}
			
			else
			{
				if (GetCurTime() > 0.066f)
				{
					
					vel.x = 0.0f;
				}
			}
		}
		else if (activeAnim->GetKey() == L"Attack_BasicAttack3")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.1f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.09f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				if (GetOwner()->GetFlip())
				{
					vel.x = -1.f * abs(mVelocity.x);
				}
				else
				{
					vel.x = abs(mVelocity.x);
				}
			}
			else
			{
				if (GetCurTime() > 0.066f)
				{
					vel.x = 0.0f;
				}
			}
		}
		else
		{
			animator->PlayAnimation(L"Attack_BasicAttack1", false);
			mCommandVector.clear();
		}

		rb->SetVelocity(vel);
	}

	void PlayerScript::Attack_Rush()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animation* activeAnim = animator->GetActiveAnimation();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();

		if (activeAnim->GetKey() == L"Attack_RushRush1")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.19f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.17f)
				{
					int comSize = mCommandVector.size();
					int moveSize = mMoveVector[(UINT)eMoveType::axisX].size();
					if (comSize >= 1 && moveSize >= 1)
					{
						for (int i = 0; i < comSize; i++)
						{
							if (mCommandVector[i].type == PlayerScript::eCommandType::Z)
							{
								animator->PlayAnimation(L"Attack_RushRush2", false);
								mCommandVector.clear();
								SetCurTime(0.0f);
								break;
							}
						}
					}
				}
				else if (activeAnim->IsComplete() && GetCurTime() > 0.17f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						vel.x = 1020.0f;
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						vel.x = -1020.0f;
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
			}
			else
			{
				if (GetCurTime() > 0.12f)
				{
					if (vel.x != 0.0f)
						mVelocity = vel;
					vel.x = 0.0f;
				}
			}
		}
		else if (activeAnim->GetKey() == L"Attack_RushRush2")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.19f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.17f)
				{
					int comSize = mCommandVector.size();
					int moveSize = mMoveVector[(UINT)eMoveType::axisX].size();
					if (comSize >= 1 && moveSize >= 1)
					{
						for (int i = 0; i < comSize; i++)
						{
							if (mCommandVector[i].type == PlayerScript::eCommandType::Z)
							{
								animator->PlayAnimation(L"Attack_RushRush3", false);
								mCommandVector.clear();
								SetCurTime(0.0f);
								break;
							}
						}
					}
				}
				else if (activeAnim->IsComplete() && GetCurTime() > 0.17f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				if (GetOwner()->GetFlip())
				{
					vel.x = -1.f * abs(mVelocity.x);
				}
				else
				{
					vel.x = abs(mVelocity.x);
				}
			}
			else
			{
				if (GetCurTime() > 0.12f)
				{
					vel.x = 0.0f;
				}
			}
		}
		else if (activeAnim->GetKey() == L"Attack_RushRush3")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.19f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.14f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				if (GetOwner()->GetFlip())
				{
					vel.x = -1.f * abs(mVelocity.x);
				}
				else
				{
					vel.x = abs(mVelocity.x);
				}
			}
			else
			{
				if (GetCurTime() > 0.12f)
				{
					vel.x = 0.0f;
				}
			}
		}
		else
		{
			animator->PlayAnimation(L"Attack_RushRush1", false);
			mCommandVector.clear();
		}

		rb->SetVelocity(vel);
	}
	void PlayerScript::Attack_UpperSlash()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animation* activeAnim = animator->GetActiveAnimation();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();

		if (activeAnim->GetKey() == L"Attack_UpperSlashAttack")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.1f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.05f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						vel.x = 510.0f;
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						vel.x = -510.0f;
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				else
				{
					if (GetOwner()->GetFlip())
					{
						vel.x = -255.0f;
					}
					else
					{
						vel.x = 255.0f;
					}
				}
			}
			else
			{
				if (GetCurTime() > 0.066f)
				{
					if (vel.x != 0.0f)
						mVelocity = vel;
					vel.x = 0.0f;
				}
			}
		}
		
		else
		{
			animator->PlayAnimation(L"Attack_UpperSlashAttack", false);
			mCommandVector.clear();
		}

		rb->SetVelocity(vel);
	}
	void PlayerScript::Attack_IceWave()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animation* activeAnim = animator->GetActiveAnimation();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();

		if (activeAnim->GetKey() == L"Attack_WaveIceWave")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.15f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.05f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						vel.x = 510.0f;
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						vel.x = -510.0f;
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				else
				{
					if (GetOwner()->GetFlip())
					{
						vel.x = -255.0f;
					}
					else
					{
						vel.x = 255.0f;
					}
				}
			}
			else
			{
				if (GetCurTime() > 0.1f)
				{
					if (vel.x != 0.0f)
						mVelocity = vel;
					vel.x = 0.0f;
				}
			}
		}

		else
		{
			animator->PlayAnimation(L"Attack_WaveIceWave", false);
			mCommandVector.clear();
		}
	}
	void PlayerScript::Attack_FireWave()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animation* activeAnim = animator->GetActiveAnimation();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();

		if (activeAnim->GetKey() == L"Attack_WaveFireWave")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.15f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.05f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				SetCurTime(0.0f);
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						vel.x = 510.0f;
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						vel.x = -510.0f;
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
				else
				{
					if (GetOwner()->GetFlip())
					{
						vel.x = -255.0f;
					}
					else
					{
						vel.x = 255.0f;
					}
				}
			}
			else
			{
				if (GetCurTime() > 0.1f)
				{
					if (vel.x != 0.0f)
						mVelocity = vel;
					vel.x = 0.0f;
				}
			}
		}

		else
		{
			animator->PlayAnimation(L"Attack_WaveFireWave", false);
			mCommandVector.clear();
		}
	}
	void PlayerScript::Attack_Thrust()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animation* activeAnim = animator->GetActiveAnimation();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();

		if (activeAnim->GetKey() == L"Attack_ThrustThrust1")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.1f)
				{
					SetCurTime(0.0f);
				}
				else if (GetCurTime() <= 0.09f)
				{
					int size = mCommandVector.size();
					if (size >= 1)
					{
						for (int i = 0; i < size; i++)
						{
							if (mCommandVector[i].type == PlayerScript::eCommandType::X)
							{
								animator->PlayAnimation(L"Attack_ThrustThrust2", false);
								mCommandVector.clear();
								SetCurTime(0.0f);
								break;
							}
						}
					}
				}
				
				else if (GetCurTime() > 0.09f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				vel.x = 0.0f;
				int size = mMoveVector[(UINT)eMoveType::axisX].size();
				if (size >= 1)
				{
					if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::RIGHT)
					{
						if (GetOwner()->GetFlip())
							GetOwner()->SetFlip(false);
					}
					else if (mMoveVector[(UINT)eMoveType::axisX][size - 1] == eCommandType::LEFT)
					{
						if (!GetOwner()->GetFlip())
							GetOwner()->SetFlip(true);
					}
				}
			}
			else if (activeAnim->GetIndex() == 2)
			{
				if (GetCurTime() > 0.1f)
				{
					SetCurTime(0.0f);
					if (GetOwner()->GetFlip())
					{
						vel.x = -765.0f;
					}
					else
					{
						vel.x = 765.0f;
					}
				}
			}
			else
			{
				if (GetCurTime() > 0.1f)
				{
					if (vel.x != 0.0f)
						mVelocity = vel;
					vel.x = 0.0f;
				}
			}
		}
		else if (activeAnim->GetKey() == L"Attack_ThrustThrust2")
		{
			if (activeAnim->IsComplete())
			{
				vel.x = 0.0f;
				if (GetCurTime() > 0.15f)
				{
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete() && GetCurTime() <= 0.05f)
				{
					mPlayerState = ePlayerState::Idle;
					vel.x = 0.0f;
					vel.y = 0.0f;
					vel.z = 0.0f;
					mCommandVector.clear();
				}
			}
			else if (activeAnim->GetIndex() == 0)
			{
				vel.x = 0.0f;

				SetCurTime(0.0f);
				if (GetOwner()->GetFlip())
				{
					vel.x = -1.f * abs(mVelocity.x);
				}
				else
				{
					vel.x = abs(mVelocity.x);
				}
			}
			else if (activeAnim->GetIndex() == 2)
			{
				if (GetCurTime() > 0.1f)
				{
					SetCurTime(0.0f);
					if (GetOwner()->GetFlip())
					{
						vel.x = -1.f * abs(mVelocity.x);
					}
					else
					{
						vel.x = abs(mVelocity.x);
					}
				}
			}
			else
			{
				if (GetCurTime() > 0.1f)
				{
					vel.x = 0.0f;
				}
			}
		}
		
		else
		{
			animator->PlayAnimation(L"Attack_ThrustThrust1", false);
			mCommandVector.clear();
		}

		rb->SetVelocity(vel);
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
