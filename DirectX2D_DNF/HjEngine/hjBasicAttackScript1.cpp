#include "hjBasicAttackScript1.h"
#include "hjTime.h"

#include "hjBasicAttackObject1Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"

namespace hj
{

	BasicAttackScript1::BasicAttackScript1()
	{
	}
	BasicAttackScript1::~BasicAttackScript1()
	{
	}
	void BasicAttackScript1::Initialize()
	{
		RegisterAttackObject<BasicAttackObject1Script>(L"BasicAttack1");
		LoadAttackObject(L"BasicAttack1")->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript1::Update()
	{
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObject* BasicAttack1 = LoadAttackObject(L"BasicAttack1");
				BasicAttack1->SetActivate(false);
				BasicAttack1->GetComponent<Collider2D>()->SetCollision(false);
				BasicAttack1->SetAttack(false);
				SetActivate(false);
			}
		}
		AttackScript::Update();
	}

	void BasicAttackScript1::Reset()
	{
		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AttackObject* BasicAttack1 = LoadAttackObject(L"BasicAttack1");
		BasicAttack1->SetPos(ownerPos);
		BasicAttack1->SetFlip(GetOwner()->GetFlip());
		BasicAttack1->SetPosVZ(ownerPosVZ);
		BasicAttack1->SetActivate(true);
		BasicAttack1->GetComponent<Collider2D>()->SetCollision(true);
		BasicAttack1->SetAttack(true);
		BasicAttack1->clearTargets();

	}

}
