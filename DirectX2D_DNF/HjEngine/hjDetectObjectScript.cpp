#include "hjDetectObjectScript.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
#include "hjDetectScript.h"
namespace hj
{

	DetectObjectScript::DetectObjectScript()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DetectObjectScript::~DetectObjectScript()
	{
	}
	void DetectObjectScript::Initialize()
	{
		AttackObjectScript::Initialize();
	}
	void DetectObjectScript::Update()
	{
		AttackObjectScript::Update();
	}



	void DetectObjectScript::OnCollisionEnter(Collider2D* other)
	{
		
		PlayerScript* player = other->GetOwner()->FindScript<PlayerScript>();
		if (player != nullptr)
		{
			mTarget = player->GetOwner();
		}
	}

	void DetectObjectScript::OnCollisionStay(Collider2D* other)
	{
	}

	void DetectObjectScript::OnCollisionExit(Collider2D* other)
	{
	}

}
