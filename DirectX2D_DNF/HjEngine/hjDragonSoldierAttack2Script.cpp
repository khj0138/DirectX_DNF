#include "hjDragonSoldierAttack2Script.h"
#include "hjTime.h"

#include "hjDragonSoldierAttackObject2Script.h"
#include "hjTransform.h"

#include "hjAnimator.h"
#include "hjMonsterScript.h"

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
		RegisterAttackObject<DragonSoldierAttackObject2Script>(L"DragonSoldierAttack2");
		LoadAttackObject(L"DragonSoldierAttack2")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(200.0f, 0.0f, 1.0f));
	}
	void DragonSoldierAttack2Script::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"dragon_soldierAttack2")
			{
				AttackObjectScript* DragonSoldierAttack2 = LoadAttackObject(L"DragonSoldierAttack2");
				DragonSoldierAttack2->GetOwner()->SetState(GameObject::eState::Paused);
				DragonSoldierAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DragonSoldierAttack2->SetAttack(false);
				SetActivate(false);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
			{
				AttackObjectScript* DragonSoldierAttack2 = LoadAttackObject(L"DragonSoldierAttack2");
				DragonSoldierAttack2->SetAttack(true);

			}
		}
		AttackScript::Update();	
	}
	void DragonSoldierAttack2Script::Reset()
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
			AttackObjectScript* DragonSoldierAttack2 = LoadAttackObject(L"DragonSoldierAttack2");
			DragonSoldierAttack2->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DragonSoldierAttack2->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DragonSoldierAttack2->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DragonSoldierAttack2->GetOwner()->SetState(GameObject::eState::Active);
			DragonSoldierAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DragonSoldierAttack2->clearTargets();
		}
	}
}
