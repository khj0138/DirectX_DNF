#include "hjBasicAttackScript1.h"
#include "hjTime.h"

#include "hjBasicAttackObject1Script.h"
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
		LoadAttackObject(L"BasicAttack1")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript1::Update()
	{
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObjectScript* BasicAttack1 = LoadAttackObject(L"BasicAttack1");
				BasicAttack1->GetOwner()->SetState(GameObject::eState::Paused);
				BasicAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
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
		AttackObjectScript* BasicAttack1 = LoadAttackObject(L"BasicAttack1");
		BasicAttack1->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
		BasicAttack1->GetOwner()->SetFlip(GetOwner()->GetFlip());
		BasicAttack1->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
		BasicAttack1->GetOwner()->SetState(GameObject::eState::Active);
		BasicAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
		BasicAttack1->SetAttack(true);
		BasicAttack1->clearTargets();

	}

}
