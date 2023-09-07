#include "hjDragonSoldierAttackBasic2Script.h"
#include "hjTime.h"

#include "hjDragonSoldierAttackBasic2ObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjGameObject.h"

#include "hjTransform.h"

#include "hjAnimator.h"
#include "hjMonsterScript.h"

#include "hjGraphics.h"
namespace hj
{

	DragonSoldierAttackBasic2Script::DragonSoldierAttackBasic2Script()
	{
	}
	DragonSoldierAttackBasic2Script::~DragonSoldierAttackBasic2Script()
	{
	}
	void DragonSoldierAttackBasic2Script::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<DragonSoldierAttackBasic2ObjectScript>(L"DragonSoldierAttackBasic2");
		RegisterEffectObject<AttackEffectScript>(L"AttackEffect");
		EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
		AttackEffectScript* AttackEffectObject = dynamic_cast<AttackEffectScript*>(AttackEffect);
		if (AttackEffectObject != nullptr)
		{
			AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Circle);
		}
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(100.0f, 100.0f, 1.0f));
		AttackEffect->SetCastingTime(1.0f);
	}
	void DragonSoldierAttackBasic2Script::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"dragon_soldierAttackBasic2")
			{
				AttackObjectScript* DragonSoldierAttackBasic2 = LoadAttackObject(L"DragonSoldierAttackBasic2");
				DragonSoldierAttackBasic2->GetOwner()->SetState(GameObject::eState::Paused);
				DragonSoldierAttackBasic2->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DragonSoldierAttackBasic2->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
			{
				AttackObjectScript* DragonSoldierAttackBasic2 = LoadAttackObject(L"DragonSoldierAttackBasic2");
				DragonSoldierAttackBasic2->SetAttack(true);
				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 0)
			{
				AttackObjectScript* DragonSoldierAttackBasic2 = LoadAttackObject(L"DragonSoldierAttackBasic2");
				GameObject* DragonSoldierAttackBasic2Object = DragonSoldierAttackBasic2->GetOwner();
				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->SetPos(DragonSoldierAttackBasic2Object);
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);
				////Transform* tr = DragonSoldierAttackBasic2Object->GetComponent<Transform>();

				//graphics::DebugMesh* dMesh = DragonSoldierAttackBasic2Object->GetComponent<Collider2D>()->GetMesh();
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(dMesh->position.x, 0.0f, dMesh->position.z));
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(dMesh->position.y);
				//AttackEffect->GetOwner()->SetFlip(DragonSoldierAttackBasic2Object->GetFlip());
			}
		}
		AttackScript::Update();	
	}
	void DragonSoldierAttackBasic2Script::Reset()
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
			AttackObjectScript* DragonSoldierAttackBasic2 = LoadAttackObject(L"DragonSoldierAttackBasic2");
			DragonSoldierAttackBasic2->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DragonSoldierAttackBasic2->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DragonSoldierAttackBasic2->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DragonSoldierAttackBasic2->GetOwner()->SetState(GameObject::eState::Active);
			DragonSoldierAttackBasic2->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DragonSoldierAttackBasic2->clearTargets();
		}
	}
}
