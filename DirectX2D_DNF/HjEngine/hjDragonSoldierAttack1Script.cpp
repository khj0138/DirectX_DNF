#include "hjDragonSoldierAttack1Script.h"
#include "hjTime.h"

#include "hjDragonSoldierAttackObject1Script.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
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
		LoadAttackObject(L"DragonSoldierAttack1")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));

	}
	void DragonSoldierAttack1Script::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->IsComplete())
			{
				AttackObjectScript* DragonSoldierAttack1 = LoadAttackObject(L"DragonSoldierAttack1");
				DragonSoldierAttack1->GetOwner()->SetState(GameObject::eState::Paused);
				DragonSoldierAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DragonSoldierAttack1->SetAttack(false);
				SetActivate(false);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
			{
				AttackObjectScript* DragonSoldierAttack1 = LoadAttackObject(L"DragonSoldierAttack1");
				DragonSoldierAttack1->SetAttack(true);

			}
		}
		AttackScript::Update();
	}

	void DragonSoldierAttack1Script::Reset()
	{
		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		MonsterScript* monster = GetOwner()->FindScript<MonsterScript>();
		if (monster != nullptr)
		{
			GameObject* player = monster->GetTarget();
			if (player == nullptr)
			{
				SetActivate(false);
				return;
			}
			AttackObjectScript* DragonSoldierAttack1 = LoadAttackObject(L"DragonSoldierAttack1");
			DragonSoldierAttack1->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DragonSoldierAttack1->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DragonSoldierAttack1->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DragonSoldierAttack1->GetOwner()->SetState(GameObject::eState::Active);
			DragonSoldierAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DragonSoldierAttack1->clearTargets();
		}
	}

}
