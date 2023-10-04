#include "hjAttackScript.h"

#include "hjTime.h"
#include "hjEffectObject.h"
#include "hjAttackScriptManager.h"

#include "hjCollider2D.h"
//#include "hjGameObject.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	AttackScript::AttackScript()
		: mActivate(false)
		, mCoolTime(0.0f)
		, mCurTime(0.0f)
	{
	}
	AttackScript::~AttackScript()
	{
		Release();
	}
	void AttackScript::Initialize()
	{
		
	}
	void AttackScript::Update()
	{
		mCurTime >= mCoolTime ? mCurTime = mCoolTime : mCurTime += Time::DeltaTime();
		for (auto iter = mEffectObjects.begin(); iter != mEffectObjects.end(); iter++)
		{
			if (iter->second->GetOwner()->GetState() == GameObject::eState::Active)
				iter->second->GetOwner()->Update();
		}
	}

	void AttackScript::LateUpdate()
	{
		for (auto iter = mEffectObjects.begin(); iter != mEffectObjects.end(); iter++)
		{
			if (iter->second->GetOwner()->GetState() == GameObject::eState::Active)
				iter->second->GetOwner()->LateUpdate();
		}
	}

	void AttackScript::Render()
	{
		for (auto iter = mEffectObjects.begin(); iter != mEffectObjects.end(); iter++)
		{
			if (iter->second->GetOwner()->GetState() == GameObject::eState::Active)
			{
				iter->second->EffectRender();
				iter->second->GetOwner()->Render();
			}
		}
	}

	void AttackScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void AttackScript::OnCollisionStay(Collider2D* other)
	{
	}

	void AttackScript::OnCollisionExit(Collider2D* other)
	{
	}

	void AttackScript::SetPause()
	{
		for (auto iter = mAttackObjects.begin(); iter != mAttackObjects.end(); iter++)
		{
			if (iter->second->GetOwner()->GetState() == GameObject::eState::Active)
			{
				iter->second->SetActivate(false);
				iter->second->SetPause();
			}
		}
		for (auto iter = mEffectObjects.begin(); iter != mEffectObjects.end(); iter++)
		{
			if (iter->second->GetOwner()->GetState() == GameObject::eState::Active)
			{
				iter->second->SetActivate(false);
				iter->second->SetPause();
			}

		}
		SetActivate(false);
	}

}
