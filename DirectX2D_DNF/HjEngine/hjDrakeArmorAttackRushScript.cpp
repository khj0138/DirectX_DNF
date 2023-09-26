#include "hjDrakeArmorAttackRushScript.h"
#include "hjTime.h"

#include "hjDrakeArmorAttackRushObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DrakeArmorAttackRushScript::DrakeArmorAttackRushScript()
	{
	}
	DrakeArmorAttackRushScript::~DrakeArmorAttackRushScript()
	{
	}
	void DrakeArmorAttackRushScript::Initialize()
	{
		SetCoolTime(15.0f);
		RegisterAttackObject<DrakeArmorAttackRushObjectScript>(L"DrakeArmorAttackRush");
		AttackObjectScript* DrakeArmorAttackRush = LoadAttackObject(L"DrakeArmorAttackRush");
		//DrakeArmorAttackRush->SetDefaultPercent(Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f));
		//DrakeArmorAttackRush->SetCenterPercent(0.5f);
		//DragonSoldierAttackBasic1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
		RegisterEffectObject<AttackEffectScript>(L"AttackEffect");
		EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
		AttackEffectScript* AttackEffectObject = dynamic_cast<AttackEffectScript*>(AttackEffect);
		if (AttackEffectObject != nullptr)
		{
			/*AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Rect);
			AttackEffectObject->SetStartPercent(0.5f);
			AttackEffectObject->SetEndPercent(0.7f);*/

			AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Rect);
			//AttackEffectObject->SetStartPercent(0.5f);
			//AttackEffectObject->SetEndPercent(1.0f);
		}
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(400.0f, 100.0f, 1.0f));
		AttackEffect->SetCastingTime(1.0f);
	}
	void DrakeArmorAttackRushScript::Update()
	{

		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_armorAttackRush")
			{
				AttackObjectScript* DrakeArmorAttackRush = LoadAttackObject(L"DrakeArmorAttackRush");
				DrakeArmorAttackRush->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeArmorAttackRush->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeArmorAttackRush->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);
				return;
			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() >= 4)
			{
				AttackObjectScript* DrakeArmorAttackRush = LoadAttackObject(L"DrakeArmorAttackRush");
				Transform* tr = GetOwner()->GetComponent<Transform>();
				DrakeArmorAttackRush->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
				DrakeArmorAttackRush->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ());
				if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 4)
				{
					DrakeArmorAttackRush->SetAttack(true);
					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);
				}
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 3)
			{
				AttackObjectScript* DrakeArmorAttackRush = LoadAttackObject(L"DrakeArmorAttackRush");
				GameObject* DrakeArmorAttackRushObject = DrakeArmorAttackRush->GetOwner();
				Transform* tr = DrakeArmorAttackRushObject->GetComponent<Transform>();
				graphics::DebugMesh* dMesh = DrakeArmorAttackRushObject->GetComponent<Collider2D>()->GetMesh();

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				Collider2D* col = GetOwner()->GetComponent<Collider2D>();
				Vector3 colPos = col->GetPosition();
				AttackEffect->SetPos(DrakeArmorAttackRushObject);
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);
				AttackEffect->GetOwner()->SetFlip(GetOwner()->GetFlip());

				colPos.x += 400.0f * 0.5f * (1.0f - 2.0f * GetOwner()->GetFlip());
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(colPos.x, 0.0f, 1.0f));
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

	void DrakeArmorAttackRushScript::Reset()
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
			AttackObjectScript* DrakeArmorAttackRush = LoadAttackObject(L"DrakeArmorAttackRush");


			DrakeArmorAttackRush->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DrakeArmorAttackRush->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DrakeArmorAttackRush->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DrakeArmorAttackRush->GetOwner()->SetState(GameObject::eState::Active);
			DrakeArmorAttackRush->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DrakeArmorAttackRush->clearTargets();


		}
	}

	void DrakeArmorAttackRushScript::SetActivate(bool activate)
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
					Vector2 monsterPos2D = Vector2(monsterPos.x, monsterVZ);

					if (abs(playerPos2D.x - monsterPos2D.x) > 400.0f
						|| abs(playerPos2D.y - monsterPos2D.y) > 100.0f)
						AttackScript::SetActivate(false);
					return;
				}
			}

		}


	}

}
