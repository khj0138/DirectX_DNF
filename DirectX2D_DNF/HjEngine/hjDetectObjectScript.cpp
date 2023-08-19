#include "hjDetectObjectScript.h"
#include "hjAttackObject.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayer.h"
#include "hjDetectScript.h"
namespace hj
{

	DetectObjectScript::DetectObjectScript()
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
		
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			DetectScript* dtScript = dynamic_cast<DetectScript*>(mOwner->GetOwnerScript());
			dtScript->SetTarget(player);
		}
	}

	void DetectObjectScript::OnCollisionStay(Collider2D* other)
	{
	}

	void DetectObjectScript::OnCollisionExit(Collider2D* other)
	{
	}

}
