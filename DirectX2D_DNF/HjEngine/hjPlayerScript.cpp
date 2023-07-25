#include "hjPlayerScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"

namespace hj
{
	PlayerScript::PlayerScript()
		: commandVector({})
		, commandTime(0.0f)
		, mPlayerState(ePlayerState::Idle)
		, mPrevPlayerState(ePlayerState::Idle)
	{
		commandVector.resize(4);
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		mPlayerState = ePlayerState::Idle;
		mAnimator = GetOwner()->GetComponent<Animator>();

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
		mPrevPlayerState = mPlayerState;
	}
	void PlayerScript::Complete()
	{
	}
	void PlayerScript::Idle()
	{
		commandVector.clear();
		commandVector.resize(4);
		commandTime = 0.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			isFlip = false;
			commandVector[0] = (UINT)(eKeyCode::RIGHT);
			mPlayerState = ePlayerState::Walk;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			isFlip = true;
			commandVector[0] = (UINT)(eKeyCode::LEFT);
			mPlayerState = ePlayerState::Walk;
		}
		/*else if (Input::GetKey(eKeyCode::C))
		{
			mPlayerState = ePlayerState::Jump;
		}*/
		else if (Input::GetKey(eKeyCode::X))
		{
			mPlayerState = ePlayerState::Attack;
		}
	}
	void PlayerScript::Walk()
	{
		if (Input::GetKeyNone(eKeyCode::RIGHT)
			&& Input::GetKeyNone(eKeyCode::LEFT))
		{
			commandTime += Time::DeltaTime();
			if (commandTime > 0.1f)
			{
				commandVector[0] = 0;
				mPlayerState = ePlayerState::Idle;
			}
		}
		else
		{
			commandTime = 0.0f;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			if ((eKeyCode)commandVector[0] == eKeyCode::RIGHT)
			{
				if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					commandVector[1] = (UINT)eKeyCode::RIGHT;
					mPlayerState = ePlayerState::Run;
				}
				else if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					isFlip = true;
					commandVector[0] = (UINT)eKeyCode::LEFT;
				}
				else
				{
					pos.x += 255.0f * Time::DeltaTime();
					tr->SetPosition(pos);
				}
			}
			else if ((eKeyCode)commandVector[0] == eKeyCode::LEFT)
			{
				if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					commandVector[1] = (UINT)eKeyCode::LEFT;
					mPlayerState = ePlayerState::Run;
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					isFlip = false;
					commandVector[0] = (UINT)eKeyCode::RIGHT;
				}
				else
				{
					pos.x -= 255.0f * Time::DeltaTime();
					tr->SetPosition(pos);
				}
			}
		}
	}
	void PlayerScript::Run()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyNone(eKeyCode::LEFT) && Input::GetKeyNone(eKeyCode::RIGHT))
		{
			commandTime += Time::DeltaTime();
			if (commandTime > 0.1f)
			{
				commandVector[0] = 0;
				commandVector[1] = 0;
				mPlayerState = ePlayerState::Idle;
			}
		}
		else if ((eKeyCode)commandVector[1] == eKeyCode::RIGHT)
		{
			commandTime = 0.0f;
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				isFlip = true;
				commandVector[1] = (UINT)eKeyCode::LEFT;
			}
			else if (Input::GetKey(eKeyCode::RIGHT))
			{
				pos.x += 510.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				commandVector[0] = 0;
				commandVector[1] = 0;
				mPlayerState = ePlayerState::Idle;
			}
		}
		else if ((eKeyCode)commandVector[1] == eKeyCode::LEFT)
		{
			commandTime = 0.0f;
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				isFlip = false;
				commandVector[1] = (UINT)eKeyCode::RIGHT;
			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				pos.x -= 510.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::RIGHT))
			{
				commandVector[0] = 0;
				commandVector[1] = 0;
				mPlayerState = ePlayerState::Idle;
			}
		}
		
	}
	void PlayerScript::Jump()
	{
		/*commandTime += Time::DeltaTime();
		if (commandTime >= 1.6f)
			mPlayerState = ePlayerState::Idle;
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			isFlip = true;
			pos.x -= 255.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 255.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}*/
	}
	void PlayerScript::Attack()
	{
		commandTime += Time::DeltaTime();
		if (commandTime >= 3.1f)
			mPlayerState = ePlayerState::Idle;
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			isFlip = true;
			pos.x -= 255.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			isFlip = false;
			pos.x += 255.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
	void PlayerScript::Anim()
	{
		mAnimator->SetFlip(isFlip);
		switch (mPlayerState)
		{
		case ePlayerState::Idle:
			if (mPrevPlayerState != mPlayerState)
				mAnimator->PlayAnimation(L"SwordManIdle", true);
			break;
		case ePlayerState::Walk:
			if (mPrevPlayerState != mPlayerState)
				mAnimator->PlayAnimation(L"SwordManWalk", true);
			break;
		case ePlayerState::Run:
			if (mPrevPlayerState != mPlayerState)
				mAnimator->PlayAnimation(L"SwordManRun", true);
			break;
		case ePlayerState::Attack:
			if (mPrevPlayerState != mPlayerState)
				mAnimator->PlayAnimation(L"SwordManAttack", true);
			break;
		case ePlayerState::Jump:
			if (mPrevPlayerState != mPlayerState)
				mAnimator->PlayAnimation(L"SwordManJump", true);
			break;
		default:
			break;
		}
	}
}
