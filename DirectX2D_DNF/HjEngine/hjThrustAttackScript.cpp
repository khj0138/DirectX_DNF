#include "hjThrustAttackScript.h"
#include "hjTime.h"

#include "hjThrustAttackObjectScript.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjPlayerScript.h"
namespace hj
{

	ThrustAttackScript::ThrustAttackScript()
	{
	}
	ThrustAttackScript::~ThrustAttackScript()
	{
	}
	void ThrustAttackScript::Initialize()
	{
		RegisterAttackObject<ThrustAttackObjectScript>(L"ThrustAttack");
		SetCoolTime(3.0f);
	}
	void ThrustAttackScript::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->GetKey() == L"Attack_ThrustThrust1")
			{
				AttackObjectScript* ThrustAttack = LoadAttackObject(L"ThrustAttack");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				ThrustAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				ThrustAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					ThrustAttack->GetOwner()->SetState(GameObject::eState::Paused);
					ThrustAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					ThrustAttack->SetAttack(false);
				}
				else if (activeAnim->GetIndex() == 2)
				{
					ThrustAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					ThrustAttack->GetOwner()->SetState(GameObject::eState::Active);
					ThrustAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					ThrustAttack->SetAttack(true);
					ThrustAttack->clearTargets();
				}
			}
			else if (activeAnim->GetKey() == L"Attack_ThrustThrust2")
			{
				AttackObjectScript* ThrustAttack = LoadAttackObject(L"ThrustAttack");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				ThrustAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				ThrustAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					ThrustAttack->GetOwner()->SetState(GameObject::eState::Paused);
					ThrustAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					ThrustAttack->SetAttack(false);
				}
				else if (activeAnim->GetIndex() == 2)
				{
					ThrustAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					ThrustAttack->GetOwner()->SetState(GameObject::eState::Active);
					ThrustAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					ThrustAttack->SetAttack(true);
					ThrustAttack->clearTargets();
				}
			}
			else
			{
				SetPause();
			}
		}
		AttackScript::Update();
	}

	void ThrustAttackScript::Reset()
	{

	}

	void ThrustAttackScript::SetActivate(bool activate)
	{
		AttackScript::SetActivate(activate);
		if (GetActivate())
		{
			PlayerScript* player = GetOwner()->FindScript<PlayerScript>();
			if (player != nullptr)
			{
				if (player->GetPlayerState() == PlayerScript::ePlayerState::Run)
				{
					std::vector<PlayerScript::Command> commands = player->GetCommandVector();
					int size = commands.size();
					if (size >= 1)
					{
						for (int i = 0; i < size; i++)
						{
							if (commands[i].type == PlayerScript::eCommandType::X && player->GetXMoveVector().size() > 0)
							{
								return;
							}
						}

					}
				}
			}
			SetActivate(false);
		}
	}

}
