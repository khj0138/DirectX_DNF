#include "hjDragonSoldierAttack2Script.h"
#include "hjTime.h"

#include "hjBasicAttackObject2Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"

#include "hjAnimator.h"
#include "hjMonster.h"
#include "hjPlayer.h"
namespace hj
{

	DragonSoldierAttack2Script::DragonSoldierAttack2Script()
	{
	}
	DragonSoldierAttack2Script::~DragonSoldierAttack2Script()
	{
	}
	void DragonSoldierAttack2Script::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<BasicAttackObject2Script>(L"DragonSoldierAttack2");
		LoadAttackObject(L"DragonSoldierAttack2")->GetComponent<Transform>()->SetPosition(Vector3(200.0f, 0.0f, 2.0f));

	}
	void DragonSoldierAttack2Script::Update()
	{
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObject* DragonSoldierAttack2 = LoadAttackObject(L"DragonSoldierAttack2");
				DragonSoldierAttack2->SetActivate(false);
				DragonSoldierAttack2->GetComponent<Collider2D>()->SetCollision(false);
				DragonSoldierAttack2->SetAttack(false);
				SetActivate(false);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 3)
			{
				AttackObject* DragonSoldierAttack2 = LoadAttackObject(L"DragonSoldierAttack2");
				DragonSoldierAttack2->SetAttack(true);
			}
		}
		AttackScript::Update();	
	}
	void DragonSoldierAttack2Script::Reset()
	{
		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		if (monster != nullptr)
		{
			Player* player = monster->GetTarget();
			if (player == nullptr)
			{
				SetActivate(false);
				return;
			}
			Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
			AttackObject* DragonSoldierAttack2 = LoadAttackObject(L"DragonSoldierAttack2");
			DragonSoldierAttack2->SetPos(ownerPos);
			DragonSoldierAttack2->SetFlip(GetOwner()->GetFlip());
			DragonSoldierAttack2->SetPosVZ(ownerPosVZ);
			DragonSoldierAttack2->SetActivate(true);
			DragonSoldierAttack2->GetComponent<Collider2D>()->SetCollision(true);
			DragonSoldierAttack2->clearTargets();
		}
	}
}
