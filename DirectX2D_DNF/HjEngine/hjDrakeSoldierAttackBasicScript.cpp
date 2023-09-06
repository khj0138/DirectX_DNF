//#include "hjDrakeSoldierAttackBasicScript.h"
//#include "hjTime.h"
//
//#include "hjDrakeSoldierAttackBasicObjectScript.h"
//#include "hjTransform.h"
//#include "hjAnimator.h"
//#include "hjMonsterScript.h"
//namespace hj
//{
//
//	DrakeSoldierAttackBasicScript::DrakeSoldierAttackBasicScript()
//	{
//	}
//	DrakeSoldierAttackBasicScript::~DrakeSoldierAttackBasicScript()
//	{
//	}
//	void DrakeSoldierAttackBasicScript::Initialize()
//	{
//		SetCoolTime(5.0f);
//		RegisterAttackObject<DrakeSoldierAttackBasicObjectScript>(L"DrakeSoldierAttackBasic");
//		LoadAttackObject(L"DrakeSoldierAttackBasic")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));
//
//	}
//	void DrakeSoldierAttackBasicScript::Update()
//	{
//		//if (GetActivate())
//		if (GetActivate())
//		{
//			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
//			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_soldierAttackBasic")
//			{
//				AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
//				DrakeSoldierAttackBasic->GetOwner()->SetState(GameObject::eState::Paused);
//				DrakeSoldierAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
//				DrakeSoldierAttackBasic->SetAttack(false);
//				SetActivate(false);
//			}
//			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
//			{
//				AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
//				DrakeSoldierAttackBasic->SetAttack(true);
//
//			}
//		}
//		AttackScript::Update();
//	}
//
//	void DrakeSoldierAttackBasicScript::Reset()
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
//			AttackObjectScript* DrakeSoldierAttackBasic = LoadAttackObject(L"DrakeSoldierAttackBasic");
//			DrakeSoldierAttackBasic->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
//			DrakeSoldierAttackBasic->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
//			DrakeSoldierAttackBasic->GetOwner()->SetFlip(GetOwner()->GetFlip());
//			DrakeSoldierAttackBasic->GetOwner()->SetState(GameObject::eState::Active);
//			DrakeSoldierAttackBasic->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
//			DrakeSoldierAttackBasic->clearTargets();
//		}
//	}
//
//}
