#include "hjReleaseWaveAttackScript.h"
#include "hjTime.h"

#include "hjReleaseWaveAttackObjectScript.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjRigidbody.h"
#include "hjPlayerScript.h"
namespace hj
{

	ReleaseWaveAttackScript::ReleaseWaveAttackScript()
	{
	}
	ReleaseWaveAttackScript::~ReleaseWaveAttackScript()
	{
	}
	void ReleaseWaveAttackScript::Initialize()
	{
		RegisterAttackObject<ReleaseWaveAttackObjectScript>(L"ReleaseWaveAttack");

		SetCoolTime(3.0f);

	}
	void ReleaseWaveAttackScript::Update()
	{
		if (GetActivate())
		{

			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->GetKey() == L"Attack_ReleaseWaveAttack")
			{
				AttackObjectScript* ReleaseWaveAttack = LoadAttackObject(L"ReleaseWaveAttack");
				if (activeAnim->IsComplete())
				{
					ReleaseWaveAttack->GetOwner()->SetState(GameObject::eState::Paused);
					ReleaseWaveAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					ReleaseWaveAttack->SetAttack(false);
					SetPause();
				}
				else if (activeAnim->GetIndex() == 1 && ReleaseWaveAttack->GetOwner()->GetState() == GameObject::eState::Paused)
				{
					Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
					float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();

					ReleaseWaveAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
					ReleaseWaveAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
					ReleaseWaveAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					ReleaseWaveAttack->GetOwner()->SetState(GameObject::eState::Active);
					ReleaseWaveAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					ReleaseWaveAttack->SetAttack(true);
					ReleaseWaveAttack->GetOwner()->GetComponent<Animator>()->PlayAnimation(L"ReleaseWaveWave", false);

					ReleaseWaveAttack->clearTargets();
				}
				
			}
			else
			{
				SetPause();
			}
		}
		AttackScript::Update();
	}

	void ReleaseWaveAttackScript::Reset()
	{

	}

	void ReleaseWaveAttackScript::SetActivate(bool activate)
	{
		AttackScript::SetActivate(activate);
		if (GetActivate())
		{
			PlayerScript* player = GetOwner()->FindScript<PlayerScript>();
			if (player != nullptr)
			{
				PlayerScript::ePlayerState playerState = player->GetPlayerState();
				if (playerState == PlayerScript::ePlayerState::Idle
					|| playerState == PlayerScript::ePlayerState::Walk
					|| playerState == PlayerScript::ePlayerState::Run)
				{
					std::vector<PlayerScript::Command> commands = player->GetCommandVector();
					int size = commands.size();
					if (size >= 1)
					{
						for (int i = 0; i < size; i++)
						{
							if (commands[i].type == PlayerScript::eCommandType::S)
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
