#include "hjUpperSlashAttackScript.h"
#include "hjTime.h"

#include "hjUpperSlashAttackObjectScript.h"
#include "hjBasicAddAttackObject3Script.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjRigidbody.h"
#include "hjPlayerScript.h"
namespace hj
{

	UpperSlashAttackScript::UpperSlashAttackScript()
	{
	}
	UpperSlashAttackScript::~UpperSlashAttackScript()
	{
	}
	void UpperSlashAttackScript::Initialize()
	{
		RegisterAttackObject<UpperSlashAttackObjectScript>(L"UpperSlashAttack");
		RegisterAttackObject<BasicAddAttackObject3Script>(L"UpperSlashAddAttack");
		SetCoolTime(3.0f);

	}
	void UpperSlashAttackScript::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			
			if (activeAnim->GetKey() == L"Attack_UpperSlashAttack")
			{
				AttackObjectScript* UpperSlashAttack = LoadAttackObject(L"UpperSlashAttack");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				UpperSlashAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				UpperSlashAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					UpperSlashAttack->GetOwner()->SetState(GameObject::eState::Paused);
					UpperSlashAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					UpperSlashAttack->SetAttack(false);
					
					AttackObjectScript* UpperSlashAddAttack = LoadAttackObject(L"UpperSlashAddAttack");
					UpperSlashAddAttack->GetOwner()->SetState(GameObject::eState::Paused);
					UpperSlashAddAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					UpperSlashAddAttack->SetAttack(false);

					SetPause();
				}
				else if (activeAnim->GetIndex() == 0)
				{
					UpperSlashAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					UpperSlashAttack->GetOwner()->SetState(GameObject::eState::Active);
					UpperSlashAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					UpperSlashAttack->SetAttack(true);
					UpperSlashAttack->clearTargets();
				}
				else if (activeAnim->GetIndex() == 2)
				{
					AttackObjectScript* UpperSlashAddAttack = LoadAttackObject(L"UpperSlashAddAttack");

					Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
					float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
					UpperSlashAddAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
					UpperSlashAddAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
					UpperSlashAddAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					UpperSlashAddAttack->GetOwner()->SetState(GameObject::eState::Active);
					UpperSlashAddAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					//Vector3 vel = UpperSlashAddAttack->GetOwner()->GetComponent<Rigidbody>()->GetVelocity();

					Vector3 vel = Vector3(200.0f, 0.0f, 0.0f);
					if (UpperSlashAddAttack->GetOwner()->GetFlip())
						vel.x = -1.0f * vel.x;
					UpperSlashAddAttack->GetOwner()->GetComponent<Rigidbody>()->SetVelocity(vel);
					Animator* mAnimator = UpperSlashAddAttack->GetOwner()->GetComponent<Animator>();
					mAnimator->PlayAnimation(L"AddwaveAddwave3", false);
					UpperSlashAddAttack->SetAttack(true);
					UpperSlashAddAttack->clearTargets();
				}
			}
		}
		AttackScript::Update();
	}

	void UpperSlashAttackScript::Reset()
	{

	}

	void UpperSlashAttackScript::SetActivate(bool activate)
	{
		AttackScript::SetActivate(activate);
		if (GetActivate())
		{
			PlayerScript* player = GetOwner()->FindScript<PlayerScript>();
			if (player != nullptr)
			{
				if (player->GetPlayerState() == PlayerScript::ePlayerState::Idle
					|| player->GetPlayerState() == PlayerScript::ePlayerState::Walk)
				{
					std::vector<PlayerScript::Command> commands = player->GetCommandVector();
					int size = commands.size();
					if (size >= 1)
					{
						for (int i = 0; i < size; i++)
						{
							if (commands[i].type == PlayerScript::eCommandType::Z)
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
