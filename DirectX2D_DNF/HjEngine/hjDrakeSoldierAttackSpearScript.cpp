//#include "hjDrakeSoldierAttackSpearScript.h"
//#include "hjTime.h"
//
//#include "hjDrakeSoldierAttackSpearObjectScript.h"
//#include "hjTransform.h"
//#include "hjAnimator.h"
//#include "hjMonsterScript.h"
//namespace hj
//{
//
//	DrakeSoldierAttackSpearScript::DrakeSoldierAttackSpearScript()
//	{
//	}
//	DrakeSoldierAttackSpearScript::~DrakeSoldierAttackSpearScript()
//	{
//	}
//	void DrakeSoldierAttackSpearScript::Initialize()
//	{
//		SetCoolTime(5.0f);
//		RegisterAttackObject<DrakeSoldierAttackSpearObjectScript>(L"DrakeSoldierAttackSpear");
//		LoadAttackObject(L"DrakeSoldierAttackSpear")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));
//
//	}
//	void DrakeSoldierAttackSpearScript::Update()
//	{
//		//if (GetActivate())
//		if (GetActivate())
//		{
//			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
//			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_soldierAttackSpear")
//			{
//				AttackObjectScript* DrakeSoldierAttackSpear = LoadAttackObject(L"DrakeSoldierAttackSpear");
//				DrakeSoldierAttackSpear->GetOwner()->SetState(GameObject::eState::Paused);
//				DrakeSoldierAttackSpear->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
//				DrakeSoldierAttackSpear->SetAttack(false);
//				SetActivate(false);
//			}
//			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
//			{
//				AttackObjectScript* DrakeSoldierAttackSpear = LoadAttackObject(L"DrakeSoldierAttackSpear");
//				DrakeSoldierAttackSpear->SetAttack(true);
//
//			}
//		}
//		AttackScript::Update();
//	}
//
//	void DrakeSoldierAttackSpearScript::Reset()
//	{
//		Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
//		float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
//		MonsterScript* monster = GetOwner()->FindScript<MonsterScript>();
//		if (monster != nullptr)
//		{
//			GameObject* player = monster->GetTarget();
//			if (player == nullptr)
//			{
//				SetActivate(false);
//				return;
//			}
//			AttackObjectScript* DrakeSoldierAttackSpear = LoadAttackObject(L"DrakeSoldierAttackSpear");
//			DrakeSoldierAttackSpear->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
//			DrakeSoldierAttackSpear->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
//			DrakeSoldierAttackSpear->GetOwner()->SetFlip(GetOwner()->GetFlip());
//			DrakeSoldierAttackSpear->GetOwner()->SetState(GameObject::eState::Active);
//			DrakeSoldierAttackSpear->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
//			DrakeSoldierAttackSpear->clearTargets();
//		}
//	}
//
//}
