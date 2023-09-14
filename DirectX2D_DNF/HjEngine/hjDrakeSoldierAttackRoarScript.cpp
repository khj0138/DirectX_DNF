#include "hjDrakeSoldierAttackRoarScript.h"
#include "hjTime.h"


#include "hjDrakeSoldierAttackRoarObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DrakeSoldierAttackRoarScript::DrakeSoldierAttackRoarScript()
	{
	}
	DrakeSoldierAttackRoarScript::~DrakeSoldierAttackRoarScript()
	{
	}
	void DrakeSoldierAttackRoarScript::Initialize()
	{
		SetCoolTime(10.0f);
		RegisterAttackObject<DrakeSoldierAttackRoarObjectScript>(L"DrakeSoldierAttackRoar");
		AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
		//DragonSoldierAttackRoar1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
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
	void DrakeSoldierAttackRoarScript::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() && activeAnim->GetKey() == L"drake_soldierAttackRoar")
			{

				AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
				DrakeSoldierAttackRoar->SetFinTime(DrakeSoldierAttackRoar->GetFinTime() + Time::DeltaTime());
				if (DrakeSoldierAttackRoar->GetFinTime() >= 0.4f)
				{
					DrakeSoldierAttackRoar->GetOwner()->SetState(GameObject::eState::Paused);
					DrakeSoldierAttackRoar->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					DrakeSoldierAttackRoar->SetAttack(false);

					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);

					SetActivate(false);

					DrakeSoldierAttackRoar->SetFinTime(0.0f);
					return;

				}

			}
			else if (activeAnim->GetKey() != L"drake_soldierAttackRoar")
			{
				AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");

				DrakeSoldierAttackRoar->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeSoldierAttackRoar->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeSoldierAttackRoar->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);

				DrakeSoldierAttackRoar->SetFinTime(0.0f);
				return;

			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 4)
			{
				AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
				DrakeSoldierAttackRoar->SetAttack(true);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
			{
				AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
				GameObject* DrakeSoldierAttackRoarObject = DrakeSoldierAttackRoar->GetOwner();
				Transform* tr = DrakeSoldierAttackRoarObject->GetComponent<Transform>();
				graphics::DebugMesh* dMesh = DrakeSoldierAttackRoarObject->GetComponent<Collider2D>()->GetMesh();

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->SetPos(DrakeSoldierAttackRoarObject);
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);
				//float sec45 = 1.4f;
				////AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(dMesh->position.x, 0.0f, dMesh->position.z));
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
				////AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(dMesh->position.y);
				//AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ() - tr->GetScale().y / 2.0f * sec45);
				//AttackEffect->GetOwner()->SetFlip(DragonSoldierAttackRoar1Object->GetFlip());
			}
		}
		AttackScript::Update();
	}

	void DrakeSoldierAttackRoarScript::Reset()
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
			AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
			DrakeSoldierAttackRoar->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
			DrakeSoldierAttackRoar->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
			DrakeSoldierAttackRoar->GetOwner()->SetFlip(GetOwner()->GetFlip());
			DrakeSoldierAttackRoar->GetOwner()->SetState(GameObject::eState::Active);
			DrakeSoldierAttackRoar->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
			DrakeSoldierAttackRoar->clearTargets();


		}
	}

}
