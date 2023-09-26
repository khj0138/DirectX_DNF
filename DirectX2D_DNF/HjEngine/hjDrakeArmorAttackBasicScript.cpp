#include "hjDrakeArmorAttackBasicScript.h"
#include "hjTime.h"

#include "hjDrakeArmorAttackBasicObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DrakeArmorAttackBasicScript::DrakeArmorAttackBasicScript()
	{
	}
	DrakeArmorAttackBasicScript::~DrakeArmorAttackBasicScript()
	{
	}
	void DrakeArmorAttackBasicScript::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<DrakeArmorAttackBasicObjectScript>(L"DrakeArmorAttackBasic");
		AttackObjectScript* DrakeArmorAttackBasic = LoadAttackObject(L"DrakeArmorAttackBasic");
		//DrakeArmorAttackBasic->SetDefaultPercent(Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f));
		//DrakeArmorAttackBasic->SetCenterPercent(0.5f);
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
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(100.0f, 100.0f, 1.0f));
		AttackEffect->SetCastingTime(0.5f);
	}
	void DrakeArmorAttackBasicScript::Update()
	{

		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();

			if (activeAnim->GetIndex() == 4 && activeAnim->GetKey() == L"drake_armorAttackBasic")
			{
				AttackObjectScript* DrakeArmorAttackBasic = LoadAttackObject(L"DrakeArmorAttackBasic");

				DrakeArmorAttackBasic->SetFinTime(DrakeArmorAttackBasic->GetFinTime() + Time::DeltaTime());
				if (DrakeArmorAttackBasic->GetFinTime() >= 0.8f)
				{
					DrakeArmorAttackBasic->GetOwner()->SetState(GameObject::eState::Paused);
					DrakeArmorAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					DrakeArmorAttackBasic->SetAttack(false);

					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);

					SetActivate(false);

					DrakeArmorAttackBasic->SetFinTime(0.0f);
					return;
				}
			}
			else if (activeAnim->GetKey() != L"drake_armorAttackBasic")
			{
				AttackObjectScript* DrakeArmorAttackBasic = LoadAttackObject(L"DrakeArmorAttackBasic");

				DrakeArmorAttackBasic->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeArmorAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeArmorAttackBasic->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);

				DrakeArmorAttackBasic->SetFinTime(0.0f);
				return;

			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() >= 2)
			{
				Transform* tr = GetOwner()->GetComponent<Transform>();

				AttackObjectScript* DrakeArmorAttackBasic = LoadAttackObject(L"DrakeArmorAttackBasic");
				Vector3 ownerPos = tr->GetPosition();
				//ownerPos.x += 100.0f * 0.5f * (1.0f - 2.0f * GetOwner()->GetFlip());
				DrakeArmorAttackBasic->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				DrakeArmorAttackBasic->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ());
				if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
				{
					DrakeArmorAttackBasic->SetAttack(true);
					DrakeArmorAttackBasic->clearTargets();

					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);
				}
				else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 4)
				{
					DrakeArmorAttackBasic->SetAttack(false);
				}
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 0)
			{
				AttackObjectScript* DrakeArmorAttackBasic = LoadAttackObject(L"DrakeArmorAttackBasic");
				GameObject* DrakeArmorAttackBasicObject = DrakeArmorAttackBasic->GetOwner();
				Transform* tr = DrakeArmorAttackBasicObject->GetComponent<Transform>();
				graphics::DebugMesh* dMesh = DrakeArmorAttackBasicObject->GetComponent<Collider2D>()->GetMesh();

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->SetPos(DrakeArmorAttackBasicObject);
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);
				AttackEffect->GetOwner()->SetFlip(GetOwner()->GetFlip());
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

	void DrakeArmorAttackBasicScript::Reset()
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
			AttackObjectScript* DrakeArmorAttackBasic = LoadAttackObject(L"DrakeArmorAttackBasic");


			DrakeArmorAttackBasic->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DrakeArmorAttackBasic->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DrakeArmorAttackBasic->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DrakeArmorAttackBasic->GetOwner()->SetState(GameObject::eState::Active);
			DrakeArmorAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);


		}
	}

	void DrakeArmorAttackBasicScript::SetActivate(bool activate)
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

					float dist = Vector2::Distance(playerPos2D, monsterPos2D);
					if (dist >= 250.0f)
						AttackScript::SetActivate(false);
					return;
				}
			}

		}


	}

}
