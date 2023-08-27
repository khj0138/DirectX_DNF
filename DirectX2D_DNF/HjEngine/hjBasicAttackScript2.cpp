#include "hjBasicAttackScript2.h"
#include "hjTime.h"

#include "hjBasicAttackObject2Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
namespace hj
{

	BasicAttackScript2::BasicAttackScript2()
	{
	}
	BasicAttackScript2::~BasicAttackScript2()
	{
	}
	void BasicAttackScript2::Initialize()
	{

		RegisterAttackObject<BasicAttackObject2Script>(L"BasicAttack2");
		LoadAttackObject(L"BasicAttack2")->GetComponent<Transform>()->SetPosition(Vector3(100.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript2::Update()
	{
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObject* BasicAttack2 = LoadAttackObject(L"BasicAttack2");
				BasicAttack2->SetActivate(false);
				BasicAttack2->GetComponent<Collider2D>()->SetCollision(false);
				SetActivate(false);
				BasicAttack2->SetAttack(false);

			}
		}
		AttackScript::Update();
	}
	void BasicAttackScript2::Reset()
	{
		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AttackObject* BasicAttack2 = LoadAttackObject(L"BasicAttack2");
		BasicAttack2->SetPos(ownerPos);
		BasicAttack2->SetFlip(GetOwner()->GetFlip());
		BasicAttack2->SetPosVZ(ownerPosVZ);
		BasicAttack2->SetActivate(true);
		BasicAttack2->GetComponent<Collider2D>()->SetCollision(true);
		BasicAttack2->SetAttack(true);
		BasicAttack2->clearTargets();
	}
}
