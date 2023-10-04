#include "hjFireWaveAttackScript.h"
#include "hjTime.h"

#include "hjFireWaveAttackObjectScript.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjRigidbody.h"
#include "hjPlayerScript.h"
namespace hj
{

	FireWaveAttackScript::FireWaveAttackScript()
	{
	}
	FireWaveAttackScript::~FireWaveAttackScript()
	{
	}
	void FireWaveAttackScript::Initialize()
	{
		RegisterAttackObject<FireWaveAttackObjectScript>(L"FireWaveAttack");

	}
	void FireWaveAttackScript::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();

			if (activeAnim->GetKey() == L"Attack_Wave")
			{
				AttackObjectScript* FireWaveAttack = LoadAttackObject(L"FireWaveAttack");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				FireWaveAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				FireWaveAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					FireWaveAttack->GetOwner()->SetState(GameObject::eState::Paused);
					FireWaveAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					FireWaveAttack->SetAttack(false);

					AttackObjectScript* FireWaveAddAttack = LoadAttackObject(L"FireWaveAddAttack");
					FireWaveAddAttack->GetOwner()->SetState(GameObject::eState::Paused);
					FireWaveAddAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					FireWaveAddAttack->SetAttack(false);

					SetPause();
				}
				else if (activeAnim->GetIndex() == 0)
				{
					FireWaveAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					FireWaveAttack->GetOwner()->SetState(GameObject::eState::Active);
					FireWaveAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					FireWaveAttack->SetAttack(true);
					FireWaveAttack->clearTargets();
				}
				else if (activeAnim->GetIndex() == 2)
				{
					AttackObjectScript* FireWaveAddAttack = LoadAttackObject(L"FireWaveAddAttack");

					Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
					float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
					FireWaveAddAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
					FireWaveAddAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
					FireWaveAddAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					FireWaveAddAttack->GetOwner()->SetState(GameObject::eState::Active);
					FireWaveAddAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					//Vector3 vel = FireWaveAddAttack->GetOwner()->GetComponent<Rigidbody>()->GetVelocity();

					Vector3 vel = Vector3(200.0f, 0.0f, 0.0f);
					if (FireWaveAddAttack->GetOwner()->GetFlip())
						vel.x = -1.0f * vel.x;
					FireWaveAddAttack->GetOwner()->GetComponent<Rigidbody>()->SetVelocity(vel);
					Animator* mAnimator = FireWaveAddAttack->GetOwner()->GetComponent<Animator>();
					mAnimator->PlayAnimation(L"AddwaveAddwave3", false);
					FireWaveAddAttack->SetAttack(true);
					FireWaveAddAttack->clearTargets();
				}
			}
		}
		AttackScript::Update();
	}

	void FireWaveAttackScript::Reset()
	{

	}

	void FireWaveAttackScript::SetActivate(bool activate)
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
