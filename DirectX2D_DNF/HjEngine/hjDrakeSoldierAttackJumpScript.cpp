//#include "hjDrakeSoldierAttackJumpScript.h"
//#include "hjTime.h"
//
//#include "hjDrakeSoldierAttackJumpObjectScript.h"
//#include "hjTransform.h"
//#include "hjAnimator.h"
//#include "hjMonsterScript.h"
//namespace hj
//{
//
//	DrakeSoldierAttackJumpScript::DrakeSoldierAttackJumpScript()
//	{
//	}
//	DrakeSoldierAttackJumpScript::~DrakeSoldierAttackJumpScript()
//	{
//	}
//	void DrakeSoldierAttackJumpScript::Initialize()
//	{
//		SetCoolTime(5.0f);
//		RegisterAttackObject<DrakeSoldierAttackJumpObjectScript>(L"DrakeSoldierAttackJump");
//		LoadAttackObject(L"DrakeSoldierAttackJump")->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));
//
//	}
//	void DrakeSoldierAttackJumpScript::Update()
//	{
//		//if (GetActivate())
//		if (GetActivate())
//		{
//			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
//			if (activeAnim->IsComplete() || activeAnim->GetKey() != L"drake_soldierAttackJump")
//			{
//				AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"DrakeSoldierAttackJump");
//				DrakeSoldierAttackJump->GetOwner()->SetState(GameObject::eState::Paused);
//				DrakeSoldierAttackJump->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
//				DrakeSoldierAttackJump->SetAttack(false);
//				SetActivate(false);
//			}
//			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
//			{
//				AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"DrakeSoldierAttackJump");
//				DrakeSoldierAttackJump->SetAttack(true);
//
//			}
//		}
//		AttackScript::Update();
//	}
//
//	void DrakeSoldierAttackJumpScript::Reset()
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
//			AttackObjectScript* DrakeSoldierAttackJump = LoadAttackObject(L"DrakeSoldierAttackJump");
//			DrakeSoldierAttackJump->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
//			DrakeSoldierAttackJump->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
//			DrakeSoldierAttackJump->GetOwner()->SetFlip(GetOwner()->GetFlip());
//			DrakeSoldierAttackJump->GetOwner()->SetState(GameObject::eState::Active);
//			DrakeSoldierAttackJump->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
//			DrakeSoldierAttackJump->clearTargets();
//		}
//	}
//
//}
