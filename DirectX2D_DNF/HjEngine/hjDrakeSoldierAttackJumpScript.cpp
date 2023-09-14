#include "hjDrakeSoldierAttackJumpScript.h"
#include "hjTime.h"

#include "hjAttackScriptManager.h"

#include "hjDrakeSoldierAttackJumpObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"

namespace hj
{

	DrakeSoldierAttackJumpScript::DrakeSoldierAttackJumpScript()
	{
	}
	DrakeSoldierAttackJumpScript::~DrakeSoldierAttackJumpScript()
	{
	}
	void DrakeSoldierAttackJumpScript::Initialize()
	{
		SetCoolTime(5.0f);
		RegisterAttackObject<DrakeSoldierAttackJumpObjectScript>(L"DrakeSoldierAttackJump");
		AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"DrakeSoldierAttackJump");
		//DragonSoldierAttackJump1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
		RegisterEffectObject<AttackEffectScript>(L"AttackEffect");
		EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
		AttackEffectScript* AttackEffectObject = dynamic_cast<AttackEffectScript*>(AttackEffect);
		if (AttackEffectObject != nullptr)
		{
			AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Circle);
		}
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(50.0f, 50.0f, 1.0f));
		AttackEffect->SetCastingTime(1.0f);
	}
	void DrakeSoldierAttackJumpScript::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			
			if (activeAnim->IsComplete() && activeAnim->GetKey() == L"drake_soldierAttackJump")
			{
				AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"DrakeSoldierAttackJump");
				DrakeSoldierAttackJump->SetFinTime(DrakeSoldierAttackJump->GetFinTime() + Time::DeltaTime());
				if (DrakeSoldierAttackJump->GetFinTime() >= 0.4f)
				{
					DrakeSoldierAttackJump->GetOwner()->SetState(GameObject::eState::Paused);
					DrakeSoldierAttackJump->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					DrakeSoldierAttackJump->SetAttack(false);

					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);

					SetActivate(false);
					DrakeSoldierAttackJump->SetFinTime(0.0f);
					return;

				}
			}
			else if (activeAnim->GetKey() != L"drake_soldierAttackJump")
			{
				AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"drake_soldierAttackJump");

				DrakeSoldierAttackJump->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeSoldierAttackJump->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeSoldierAttackJump->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);

				DrakeSoldierAttackJump->SetFinTime(0.0f);
				return;
			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() >= 1)
			{
				Transform* tr = GetOwner()->GetComponent<Transform>();

				AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"DrakeSoldierAttackJump");
				DrakeSoldierAttackJump->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
				DrakeSoldierAttackJump->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ());
				if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
				{
					DrakeSoldierAttackJump->GetOwner()->SetFlip(GetOwner()->GetFlip());
					DrakeSoldierAttackJump->GetOwner()->SetState(GameObject::eState::Active);
					DrakeSoldierAttackJump->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					

					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);
				}
				if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 5)
				{
					DrakeSoldierAttackJump->SetAttack(true);
				}
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 0)
			{
				

				Vector3 targetPos = GetManager()->GetTargetPos();
				float targetPosVZ = GetManager()->GetTargetPosVZ();

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(targetPos);
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(targetPosVZ);
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);
			}
		}
		AttackScript::Update();
	}

	void DrakeSoldierAttackJumpScript::Reset()
	{
		AttackScriptManager* manager = GetManager();

		MonsterScript* monster = GetOwner()->FindScript<MonsterScript>();
		GameObject* target = monster->GetTarget();
		if (monster != nullptr)
		{
			GameObject* player = monster->GetTarget();
			if (player == nullptr)
			{
				SetActivate(false);
				return;
			}
			AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"DrakeSoldierAttackJump");
			DrakeSoldierAttackJump->clearTargets();
			manager->SetTargetColPos(target);

			


		}
	}


}
