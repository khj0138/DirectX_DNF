#include "hjDragonSoldierAttackBasic1Script.h"
#include "hjTime.h"

#include "hjDragonSoldierAttackBasic1ObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DragonSoldierAttackBasic1Script::DragonSoldierAttackBasic1Script()
	{
	}
	DragonSoldierAttackBasic1Script::~DragonSoldierAttackBasic1Script()
	{
	}
	void DragonSoldierAttackBasic1Script::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<DragonSoldierAttackBasic1ObjectScript>(L"DragonSoldierAttackBasic1");
		AttackObjectScript* DragonSoldierAttackBasic1 = LoadAttackObject(L"DragonSoldierAttackBasic1");
		//DragonSoldierAttackBasic1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
		RegisterEffectObject<AttackEffectScript>(L"AttackEffect");
		EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
		AttackEffectScript* AttackEffectObject = dynamic_cast<AttackEffectScript*>(AttackEffect);
		if (AttackEffectObject != nullptr)
		{
			AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Circle);
		}
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(200.0f, 200.0f, 1.0f));
		AttackEffect->SetCastingTime(1.0f);
	}
	void DragonSoldierAttackBasic1Script::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"dragon_soldierAttackBasic1")
			{
				AttackObjectScript* DragonSoldierAttackBasic1 = LoadAttackObject(L"DragonSoldierAttackBasic1");
				DragonSoldierAttackBasic1->GetOwner()->SetState(GameObject::eState::Paused);
				DragonSoldierAttackBasic1->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DragonSoldierAttackBasic1->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);
				return;
			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
			{
				AttackObjectScript* DragonSoldierAttackBasic1 = LoadAttackObject(L"DragonSoldierAttackBasic1");
				DragonSoldierAttackBasic1->SetAttack(true);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
			{
				AttackObjectScript* DragonSoldierAttackBasic1 = LoadAttackObject(L"DragonSoldierAttackBasic1");
				GameObject* DragonSoldierAttackBasic1Object = DragonSoldierAttackBasic1->GetOwner();
				Transform* tr = DragonSoldierAttackBasic1Object->GetComponent<Transform>();
				graphics::DebugMesh* dMesh = DragonSoldierAttackBasic1Object->GetComponent<Collider2D>()->GetMesh();
				
				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->SetPos(DragonSoldierAttackBasic1Object);
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);
				//float sec45 = 1.4f;
				////AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(dMesh->position.x, 0.0f, dMesh->position.z));
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
				////AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(dMesh->position.y);
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ() - tr->GetScale().y / 2.0f * sec45);
				//AttackEffect->GetOwner()->SetFlip(DragonSoldierAttackBasic1Object->GetFlip());
			}
		}
		AttackScript::Update();
	}

	void DragonSoldierAttackBasic1Script::Reset()
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
			AttackObjectScript* DragonSoldierAttackBasic1 = LoadAttackObject(L"DragonSoldierAttackBasic1");
			DragonSoldierAttackBasic1->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DragonSoldierAttackBasic1->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DragonSoldierAttackBasic1->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DragonSoldierAttackBasic1->GetOwner()->SetState(GameObject::eState::Active);
			DragonSoldierAttackBasic1->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DragonSoldierAttackBasic1->clearTargets();


		}
	}

	void DragonSoldierAttackBasic1Script::SetActivate(bool activate)
	{
		AttackScript::SetActivate(activate);
		if (GetActivate() && activate == true)
		{
			MonsterScript* monster = GetOwner()->FindScript<MonsterScript>();
			if (monster != nullptr)
			{
				GameObject* player = monster->GetTarget();

				if (player != nullptr)
				{
					Vector3 playerPos = player->GetComponent<Transform>()->GetPosition();
					float playerVZ = player->GetComponent<Transform>()->GetVirtualZ();
					Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);

					Vector3 monsterPos = monster->GetOwner()->GetComponent<Transform>()->GetPosition();
					float monsterVZ = monster->GetOwner()->GetComponent<Transform>()->GetVirtualZ();
					if (GetOwner()->GetFlip())
						monsterPos.x -= 100.0f;
					else
						monsterPos.x += 100.0f;
					Vector2 monsterPos2D = Vector2(monsterPos.x, monsterVZ);
					float dist = Vector2::Distance(playerPos2D, monsterPos2D);
					if (dist > 100.0f)
						AttackScript::SetActivate(false);
					return;
				}
			}
		}
	}

}
