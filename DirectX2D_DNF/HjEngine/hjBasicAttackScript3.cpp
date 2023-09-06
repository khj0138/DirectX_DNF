#include "hjBasicAttackScript3.h"
#include "hjTime.h"

#include "hjBasicAttackObject3Script.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
//#include "hjPlayerScript.h"

namespace hj
{

	BasicAttackScript3::BasicAttackScript3()
	{
	}
	BasicAttackScript3::~BasicAttackScript3()
	{
	}
	void BasicAttackScript3::Initialize()
	{
		RegisterAttackObject<BasicAttackObject3Script>(L"BasicAttack3");
		LoadAttackObject(L"BasicAttack3")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript3::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"SwordManAttack3")
			{
				AttackObjectScript* BasicAttack3 = LoadAttackObject(L"BasicAttack3");
				BasicAttack3->GetOwner()->SetState(GameObject::eState::Paused);
				BasicAttack3->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				BasicAttack3->SetAttack(false);
				SetActivate(false);
			}
		}
		AttackScript::Update();
	}
	void BasicAttackScript3::Reset()
	{
		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AttackObjectScript* BasicAttack3 = LoadAttackObject(L"BasicAttack3");
		BasicAttack3->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
		BasicAttack3->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
		BasicAttack3->GetOwner()->SetFlip(GetOwner()->GetFlip());
		BasicAttack3->GetOwner()->SetState(GameObject::eState::Active);
		BasicAttack3->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
		BasicAttack3->SetAttack(true);
		BasicAttack3->clearTargets();
	}

}
