
#include "hjTime.h"

#include "hjDetectObjectScript.h"
#include "hjDetectScript.h"
#include "hjGameObject.h"

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
		LoadAttackObject(L"DetectObject")->GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2(1000.0f, 1000.0f), 1000.0f);
		LoadAttackObject(L"DetectObject")->SetActivate(true);
	}
	void DetectScript::Update()
	{
		AttackScript::Update();
		LoadAttackObject(L"DetectObject")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3{ GetPos().x, GetPos().y,1.0f });
		LoadAttackObject(L"DetectObject")->GetOwner()->GetComponent<Transform>()->SetVirtualZ(GetPosVZ());
	}

	void DetectScript::Reset()
	{
	}

	GameObject* DetectScript::GetTarget()
	{
		DetectObjectScript* DetectObject = dynamic_cast<DetectObjectScript*>(LoadAttackObject(L"DetectObject"));
		if (DetectObject != nullptr)
		{
			return DetectObject->GetTarget();
		}
	}

}
