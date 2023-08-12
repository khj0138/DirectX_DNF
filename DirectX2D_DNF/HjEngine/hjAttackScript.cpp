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
	}

}
