#include "hjDrakeArmorAttackBreathScript.h"
#include "hjTime.h"

#include "hjDrakeArmorAttackBreathObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DrakeArmorAttackBreathScript::DrakeArmorAttackBreathScript()
	{
	}
	DrakeArmorAttackBreathScript::~DrakeArmorAttackBreathScript()
	{
	}
	void DrakeArmorAttackBreathScript::Initialize()
	{
		SetCoolTime(15.0f);
		RegisterAttackObject<DrakeArmorAttackBreathObjectScript>(L"DrakeArmorAttackBreath");
		AttackObjectScript* DrakeArmorAttackBreath = LoadAttackObject(L"DrakeArmorAttackBreath");
		DrakeArmorAttackBreath->SetDefaultPercent(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
		//DrakeArmorAttackBreath->SetCenterPercent(0.5f);
		//DragonSoldierAttackBasic1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
		RegisterEffectObject<AttackEffectScript>(L"AttackEffect");
		EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
		AttackEffectScript* AttackEffectObject = dynamic_cast<AttackEffectScript*>(AttackEffect);
		if (AttackEffectObject != nullptr)
		{
			AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Rect);
			AttackEffectObject->SetStartPercent(0.0f);
			AttackEffectObject->SetEndPercent(1.0f);

			//AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Rect);
			//AttackEffectObject->SetStartPercent(0.5f);
			//AttackEffectObject->SetEndPercent(1.0f);
		}
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(300.0f, 100.0f, 1.0f));
		AttackEffect->SetCastingTime(0.5f);
	}
	void DrakeArmorAttackBreathScript::Update()
	{

		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() && activeAnim->GetKey() == L"drake_armorAttackBreath")
			{

				AttackObjectScript* DrakeArmorAttackBreath = LoadAttackObject(L"DrakeArmorAttackBreath");
				DrakeArmorAttackBreath->SetFinTime(DrakeArmorAttackBreath->GetFinTime() + Time::DeltaTime());
				if (DrakeArmorAttackBreath->GetFinTime() >= 1.0f)
				{
					DrakeArmorAttackBreath->GetOwner()->SetState(GameObject::eState::Paused);
					DrakeArmorAttackBreath->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					DrakeArmorAttackBreath->SetAttack(false);

					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);

					SetActivate(false);

					DrakeArmorAttackBreath->SetFinTime(0.0f);
					return;

				}
			}
			else if (activeAnim->GetKey() != L"drake_armorAttackBreath")
			{
				AttackObjectScript* DrakeArmorAttackBreath = LoadAttackObject(L"DrakeArmorAttackBreath");

				DrakeArmorAttackBreath->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeArmorAttackBreath->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeArmorAttackBreath->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);

				DrakeArmorAttackBreath->SetFinTime(0.0f);
				return;

			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 3)
			{
				AttackObjectScript* DrakeArmorAttackBreath = LoadAttackObject(L"DrakeArmorAttackBreath");
				DrakeArmorAttackBreath->SetAttack(true);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
			{
				AttackObjectScript* DrakeArmorAttackBreath = LoadAttackObject(L"DrakeArmorAttackBreath");
				GameObject* DrakeArmorAttackBreathObject = DrakeArmorAttackBreath->GetOwner();
				Transform* tr = DrakeArmorAttackBreathObject->GetComponent<Transform>();
				graphics::DebugMesh* dMesh = DrakeArmorAttackBreathObject->GetComponent<Collider2D>()->GetMesh();

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->SetPos(DrakeArmorAttackBreathObject);
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

	void DrakeArmorAttackBreathScript::Reset()
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
			AttackObjectScript* DrakeArmorAttackBreath = LoadAttackObject(L"DrakeArmorAttackBreath");


			//ownerPos.x += 300.0f * 0.5f * (1.0f - 2.0f * GetOwner()->GetFlip());
			DrakeArmorAttackBreath->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DrakeArmorAttackBreath->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DrakeArmorAttackBreath->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DrakeArmorAttackBreath->GetOwner()->SetState(GameObject::eState::Active);
			DrakeArmorAttackBreath->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DrakeArmorAttackBreath->clearTargets();


		}
	}

	void DrakeArmorAttackBreathScript::SetActivate(bool activate)
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

					if (abs(playerPos2D.x - monsterPos2D.x) > 300.0f
						|| abs(playerPos2D.y - monsterPos2D.y) > 100.0f)
						AttackScript::SetActivate(false);
					return;
				}
			}

		}


	}

}
