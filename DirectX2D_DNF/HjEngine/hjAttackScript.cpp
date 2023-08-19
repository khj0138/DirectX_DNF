#include "hjAttackScript.h"

#include "hjTime.h"
#include "hjAttackObject.h"
#include "hjEffectObject.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	AttackScript::AttackScript()
		: mActivate(false)
		, mCoolTime(0.0f)
		, curTime(0.0f)
	{
	}
	AttackScript::~AttackScript()
	{
	}
	void AttackScript::Initialize()
	{
		
	}
	void AttackScript::Update()
	{
		curTime += Time::DeltaTime();
		/*for (auto iter = mAttackObjects.begin(); iter != mAttackObjects.end(); iter++)
		{
			iter->second->Update();
		}
		for (auto iter = mEffectObjects.begin(); iter != mEffectObjects.end(); iter++)
		{
			iter->second->Update();
		}*/
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

}
