#include "hjDrakeSoldierAttackSpearScript.h"
#include "hjTime.h"

#include "hjAttackScriptManager.h"

#include "hjDrakeSoldierAttackSpearObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjRigidBody.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"
namespace hj
{

	DrakeSoldierAttackSpearScript::DrakeSoldierAttackSpearScript()
	{
	}
	DrakeSoldierAttackSpearScript::~DrakeSoldierAttackSpearScript()
	{
	}
	void DrakeSoldierAttackSpearScript::Initialize()
	{
		SetCoolTime(20.0f);
		RegisterAttackObject<DrakeSoldierAttackSpearObjectScript>(L"DrakeSoldierAttackSpear");
		AttackObjectScript* DrakeSoldierAttackSpear = LoadAttackObject(L"DrakeSoldierAttackSpear");
		//DragonSoldierAttackSpear1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
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
	void DrakeSoldierAttackSpearScript::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_soldierAttackSpear")
			{
				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);
				return;

			}

			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 3)
			{
				Transform* tr = GetOwner()->GetComponent<Transform>();
				Collider2D* col = GetOwner()->GetComponent<Collider2D>();
				AttackObjectScript* DrakeSoldierAttackSpear = LoadAttackObject(L"DrakeSoldierAttackSpear");
				

				DrakeSoldierAttackSpear->GetOwner()->SetFlip(GetOwner()->GetFlip());
				DrakeSoldierAttackSpear->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);
				DrakeSoldierAttackSpear->SetAttack(true);

				float sec45 = 1.4f;
				Vector3 TargetPos = GetManager()->GetTargetPos();
				float TargetPosVZ = GetManager()->GetTargetPosVZ();
				Vector3 colPos = col->GetPosition();
				Vector3 colSize = col->GetSize();

				colPos.y -= colSize.y / 2.0f * sec45;

				float vz = colPos.y;
				Vector3 offset = Vector3(00.0f, 100.0f, 0.0f);
				DrakeSoldierAttackSpear->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ() );
				if (GetOwner()->GetFlip())
				{
					offset.x *= -1.f;
				}
				DrakeSoldierAttackSpear->GetOwner()->GetComponent<Rigidbody>()->SetVelocity(Vector3((TargetPos.x - colPos.x - offset.x), 1000.0f, TargetPosVZ - vz));
				//offset.y = 0.0f;
				DrakeSoldierAttackSpear->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition() + offset);
				DrakeSoldierAttackSpear->GetOwner()->SetState(GameObject::eState::Active);
				DrakeSoldierAttackSpear->GetOwner()->GetComponent<Rigidbody>()->SetGround(false);

			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
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

	void DrakeSoldierAttackSpearScript::Reset()
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
			manager->SetTargetColPos(target);
			AttackObjectScript* DrakeSoldierAttackSpear = LoadAttackObject(L"DrakeSoldierAttackSpear");
			DrakeSoldierAttackSpear->clearTargets();


		}
	}

}
