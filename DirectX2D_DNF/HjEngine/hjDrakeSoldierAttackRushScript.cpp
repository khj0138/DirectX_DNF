//#include "hjDrakeSoldierAttackRushScript.h"
//#include "hjTime.h"
//
//#include "hjDrakeSoldierAttackRushObjectScript.h"
//#include "hjTransform.h"
//#include "hjAnimator.h"
//#include "hjMonsterScript.h"
//namespace hj
//{
//
//	DrakeSoldierAttackRushScript::DrakeSoldierAttackRushScript()
//	{
//	}
//	DrakeSoldierAttackRushScript::~DrakeSoldierAttackRushScript()
//	{
//	}
//	void DrakeSoldierAttackRushScript::Initialize()
//	{
//		SetCoolTime(5.0f);
//		RegisterAttackObject<DrakeSoldierAttackRushObjectScript>(L"DrakeSoldierAttackRush");
//		LoadAttackObject(L"DrakeSoldierAttackRush")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));
//
//	}
//	void DrakeSoldierAttackRushScript::Update()
//	{
//		//if (GetActivate())
//		if (GetActivate())
//		{
//			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
//			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_soldierAttackRush")
//			{
//				AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");
//				DrakeSoldierAttackRush->GetOwner()->SetState(GameObject::eState::Paused);
//				DrakeSoldierAttackRush->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
//				DrakeSoldierAttackRush->SetAttack(false);
//				SetActivate(false);
//			}
//			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
//			{
//				AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");
//				DrakeSoldierAttackRush->SetAttack(true);
//
//			}
//		}
//		AttackScript::Update();
//	}
//
//	void DrakeSoldierAttackRushScript::Reset()
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
//			AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");
//			DrakeSoldierAttackRush->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
//			DrakeSoldierAttackRush->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
//			DrakeSoldierAttackRush->GetOwner()->SetFlip(GetOwner()->GetFlip());
//			DrakeSoldierAttackRush->GetOwner()->SetState(GameObject::eState::Active);
//			DrakeSoldierAttackRush->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
//			DrakeSoldierAttackRush->clearTargets();
//		}
//	}
//
//}
