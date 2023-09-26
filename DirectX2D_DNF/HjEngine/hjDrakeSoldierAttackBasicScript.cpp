#include "hjDrakeSoldierAttackBasicScript.h"
#include "hjTime.h"

#include "hjDrakeSoldierAttackBasicObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DrakeSoldierAttackBasicScript::DrakeSoldierAttackBasicScript()
	{
	}
	DrakeSoldierAttackBasicScript::~DrakeSoldierAttackBasicScript()
	{
	}
	void DrakeSoldierAttackBasicScript::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<DrakeSoldierAttackBasicObjectScript>(L"DrakeSoldierAttackBasic");
		AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
		//DrakeSoldierAttackBasic->SetDefaultPercent(Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f));
		//DrakeSoldierAttackBasic->SetCenterPercent(0.5f);
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
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(200.0f, 100.0f, 1.0f));
		AttackEffect->SetCastingTime(1.0f);
	}
	void DrakeSoldierAttackBasicScript::Update()
	{

		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_soldierAttackBasic")
			{
				AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
				DrakeSoldierAttackBasic->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeSoldierAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeSoldierAttackBasic->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);
				return;
			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
			{
				AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
				DrakeSoldierAttackBasic->SetAttack(true);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
			{
				AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
				GameObject* DrakeSoldierAttackBasicObject = DrakeSoldierAttackBasic->GetOwner();
				Transform* tr = DrakeSoldierAttackBasicObject->GetComponent<Transform>();
				graphics::DebugMesh* dMesh = DrakeSoldierAttackBasicObject->GetComponent<Collider2D>()->GetMesh();

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->SetPos(DrakeSoldierAttackBasicObject);
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

	void DrakeSoldierAttackBasicScript::Reset()
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
			AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
			

			DrakeSoldierAttackBasic->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DrakeSoldierAttackBasic->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DrakeSoldierAttackBasic->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DrakeSoldierAttackBasic->GetOwner()->SetState(GameObject::eState::Active);
			DrakeSoldierAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DrakeSoldierAttackBasic->clearTargets();


		}
	}

	void DrakeSoldierAttackBasicScript::SetActivate(bool activate)
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
					if (abs(playerPos2D.x - monsterPos2D.x) > 300.0f
					|| abs(playerPos2D.y - monsterPos2D.y) > 50.0f)
						AttackScript::SetActivate(false);
					return;
				}
			}
		}
	}

}
