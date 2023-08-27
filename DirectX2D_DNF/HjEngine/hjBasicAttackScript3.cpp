#include "hjBasicAttackScript3.h"
#include "hjTime.h"

#include "hjBasicAttackObject3Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
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
		LoadAttackObject(L"BasicAttack3")->GetComponent<Transform>()->SetPosition(Vector3(150.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript3::Update()
	{
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObject* BasicAttack3 = LoadAttackObject(L"BasicAttack3");
				BasicAttack3->SetActivate(false);
				BasicAttack3->GetComponent<Collider2D>()->SetCollision(false);
				SetActivate(false);
				BasicAttack3->SetAttack(false);

			}
		}
		AttackScript::Update();
	}
	void BasicAttackScript3::Reset()
	{
		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AttackObject* BasicAttack3 = LoadAttackObject(L"BasicAttack3");
		BasicAttack3->SetPos(ownerPos);
		BasicAttack3->SetFlip(GetOwner()->GetFlip());
		BasicAttack3->SetPosVZ(ownerPosVZ);
		BasicAttack3->SetActivate(true);
		BasicAttack3->GetComponent<Collider2D>()->SetCollision(true);
		BasicAttack3->SetAttack(true);
		BasicAttack3->clearTargets();

	}

}
