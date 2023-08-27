
#include "hjTime.h"

#include "hjDetectObjectScript.h"
#include "hjDetectScript.h"
#include "hjGameObject.h"
#include "hjPlayer.h"
#include "hjTransform.h"
#include "hjCollider2D.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	DetectScript::DetectScript()
	{
	}
	DetectScript::~DetectScript()
	{
	}
	void DetectScript::Initialize()
	{
		SetActivate(true);
		RegisterAttackObject<DetectObjectScript>(L"DetectObject");
		LoadAttackObject(L"DetectObject")->GetComponent<Collider2D>()->SetSize(Vector2(1000.0f, 1000.0f), 1000.0f);
		LoadAttackObject(L"DetectObject")->SetActivate(true);
	}
	void DetectScript::Update()
	{
		AttackScript::Update();
		LoadAttackObject(L"DetectObject")->SetPos(Vector3{ GetPos().x, GetPos().y,1.0f });
		LoadAttackObject(L"DetectObject")->SetPosVZ(GetPosVZ());
	}

	void DetectScript::Reset()
	{
	}

	Player* DetectScript::GetTarget()
	{
		return mTarget;
	}

}
