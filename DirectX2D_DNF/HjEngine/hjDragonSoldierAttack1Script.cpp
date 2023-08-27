#include "hjDragonSoldierAttack1Script.h"
#include "hjTime.h"

#include "hjDragonSoldierAttackObject1Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonster.h"
#include "hjPlayer.h"
namespace hj
{

	DragonSoldierAttack1Script::DragonSoldierAttack1Script()
	{
	}
	DragonSoldierAttack1Script::~DragonSoldierAttack1Script()
	{
	}
	void DragonSoldierAttack1Script::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<DragonSoldierAttackObject1Script>(L"DragonSoldierAttack1");
		LoadAttackObject(L"DragonSoldierAttack1")->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));

	}
	void DragonSoldierAttack1Script::Update()
	{
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObject* DragonSoldierAttack1 = LoadAttackObject(L"DragonSoldierAttack1");
				DragonSoldierAttack1->SetActivate(false);
				DragonSoldierAttack1->GetComponent<Collider2D>()->SetCollision(false);
				DragonSoldierAttack1->SetAttack(false);
				SetActivate(false);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 3)
			{
				AttackObject* DragonSoldierAttack1 = LoadAttackObject(L"DragonSoldierAttack1");
				DragonSoldierAttack1->SetAttack(true);
			}
		}
		AttackScript::Update();
	}

	void DragonSoldierAttack1Script::Reset()
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

			AttackObject* DragonSoldierAttack1 = LoadAttackObject(L"DragonSoldierAttack1");
			DragonSoldierAttack1->SetPos(ownerPos);
			DragonSoldierAttack1->SetFlip(GetOwner()->GetFlip());
			DragonSoldierAttack1->SetPosVZ(ownerPosVZ);
			DragonSoldierAttack1->SetActivate(true);
			DragonSoldierAttack1->GetComponent<Collider2D>()->SetCollision(true);
			DragonSoldierAttack1->clearTargets();
		}
	}

}
