#include "hjDrakeRiderAttackBasicScript.h"
#include "hjTime.h"

#include "hjDrakeRiderAttackBasicObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DrakeRiderAttackBasicScript::DrakeRiderAttackBasicScript()
	{
	}
	DrakeRiderAttackBasicScript::~DrakeRiderAttackBasicScript()
	{
	}
	void DrakeRiderAttackBasicScript::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<DrakeRiderAttackBasicObjectScript>(L"DrakeRiderAttackBasic");
		AttackObjectScript* DrakeRiderAttackBasic = LoadAttackObject(L"DrakeRiderAttackBasic");
		//DrakeRiderAttackBasic->SetDefaultPercent(Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f));
		//DrakeRiderAttackBasic->SetCenterPercent(0.5f);
		//DragonRiderAttackBasic1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
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
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(260.0f, 100.0f, 1.0f));
		AttackEffect->SetCastingTime(1.0f);
	}
	void DrakeRiderAttackBasicScript::Update()
	{

		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_riderAttackBasic")
			{
				AttackObjectScript* DrakeRiderAttackBasic = LoadAttackObject(L"DrakeRiderAttackBasic");
				DrakeRiderAttackBasic->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeRiderAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeRiderAttackBasic->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);
				return;
			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
			{
				AttackObjectScript* DrakeRiderAttackBasic = LoadAttackObject(L"DrakeRiderAttackBasic");
				DrakeRiderAttackBasic->SetAttack(true);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
			{
				AttackObjectScript* DrakeRiderAttackBasic = LoadAttackObject(L"DrakeRiderAttackBasic");
				GameObject* DrakeRiderAttackBasicObject = DrakeRiderAttackBasic->GetOwner();
				Transform* tr = DrakeRiderAttackBasicObject->GetComponent<Transform>();
				graphics::DebugMesh* dMesh = DrakeRiderAttackBasicObject->GetComponent<Collider2D>()->GetMesh();

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->SetPos(DrakeRiderAttackBasicObject);
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);
				AttackEffect->GetOwner()->SetFlip(GetOwner()->GetFlip());
				//float sec45 = 1.4f;
				////AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(dMesh->position.x, 0.0f, dMesh->position.z));
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
				////AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(dMesh->position.y);
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ() - tr->GetScale().y / 2.0f * sec45);
				//AttackEffect->GetOwner()->SetFlip(DragonRiderAttackBasic1Object->GetFlip());
			}
		}
		AttackScript::Update();
	}

	void DrakeRiderAttackBasicScript::Reset()
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
			AttackObjectScript* DrakeRiderAttackBasic = LoadAttackObject(L"DrakeRiderAttackBasic");

			//ownerPos.x += 300.0f * 0.5f * (1.0f - 2.0f * GetOwner()->GetFlip());

			DrakeRiderAttackBasic->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DrakeRiderAttackBasic->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DrakeRiderAttackBasic->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DrakeRiderAttackBasic->GetOwner()->SetState(GameObject::eState::Active);
			DrakeRiderAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DrakeRiderAttackBasic->clearTargets();


		}
	}

	void DrakeRiderAttackBasicScript::SetActivate(bool activate)
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
