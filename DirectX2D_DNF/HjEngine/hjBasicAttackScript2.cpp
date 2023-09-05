#include "hjBasicAttackScript2.h"
#include "hjTime.h"

#include "hjBasicAttackObject2Script.h"
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
		LoadAttackObject(L"BasicAttack2")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript2::Update()
	{
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObjectScript* BasicAttack2 = LoadAttackObject(L"BasicAttack2");
				BasicAttack2->GetOwner()->SetState(GameObject::eState::Paused);
				BasicAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				BasicAttack2->SetAttack(false);
				SetActivate(false);
			}
		}
		AttackScript::Update();
	}
	void BasicAttackScript2::Reset()
	{
		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AttackObjectScript* BasicAttack2 = LoadAttackObject(L"BasicAttack2");
		BasicAttack2->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
		BasicAttack2->GetOwner()->SetFlip(GetOwner()->GetFlip());
		BasicAttack2->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
		BasicAttack2->GetOwner()->SetState(GameObject::eState::Active);
		BasicAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
		BasicAttack2->SetAttack(true);
		BasicAttack2->clearTargets();
	}
}
