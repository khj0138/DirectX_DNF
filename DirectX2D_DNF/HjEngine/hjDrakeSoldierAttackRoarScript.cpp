//#include "hjDrakeSoldierAttackRoarScript.h"
//#include "hjTime.h"
//
//#include "hjDrakeSoldierAttackRoarObjectScript.h"
//#include "hjTransform.h"
//#include "hjAnimator.h"
//#include "hjMonsterScript.h"
//namespace hj
//{
//
//	DrakeSoldierAttackRoarScript::DrakeSoldierAttackRoarScript()
//	{
//	}
//	DrakeSoldierAttackRoarScript::~DrakeSoldierAttackRoarScript()
//	{
//	}
//	void DrakeSoldierAttackRoarScript::Initialize()
//	{
//		SetCoolTime(5.0f);
//		RegisterAttackObject<DrakeSoldierAttackRoarObjectScript>(L"DrakeSoldierAttackRoar");
//		LoadAttackObject(L"DrakeSoldierAttackRoar")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));
//
//	}
//	void DrakeSoldierAttackRoarScript::Update()
//	{
//		//if (GetActivate())
//		if (GetActivate())
//		{
//			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
//			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_soldierAttackRoar")
//			{
//				AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
//				DrakeSoldierAttackRoar->GetOwner()->SetState(GameObject::eState::Paused);
//				DrakeSoldierAttackRoar->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
//				DrakeSoldierAttackRoar->SetAttack(false);
//				SetActivate(false);
//			}
//			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
//			{
//				AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
//				DrakeSoldierAttackRoar->SetAttack(true);
//
//			}
//		}
//		AttackScript::Update();
//	}
//
//	void DrakeSoldierAttackRoarScript::Reset()
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
//			AttackObjectScript* DrakeSoldierAttackRoar = LoadAttackObject(L"DrakeSoldierAttackRoar");
//			DrakeSoldierAttackRoar->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
//			DrakeSoldierAttackRoar->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
//			DrakeSoldierAttackRoar->GetOwner()->SetFlip(GetOwner()->GetFlip());
//			DrakeSoldierAttackRoar->GetOwner()->SetState(GameObject::eState::Active);
//			DrakeSoldierAttackRoar->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
//			DrakeSoldierAttackRoar->clearTargets();
//		}
//	}
//
//}
