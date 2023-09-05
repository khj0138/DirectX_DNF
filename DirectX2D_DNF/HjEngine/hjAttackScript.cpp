#include "hjAttackScript.h"

#include "hjTime.h"
#include "hjEffectObject.h"
#include "hjAttackScriptManager.h"
#include "hjGameObject.h"
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
		Release();
	}
	void AttackScript::Initialize()
	{
		
	}
	void AttackScript::Update()
	{
		curTime >= mCoolTime ? curTime = mCoolTime : curTime += Time::DeltaTime();
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
