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
		: WaveIndex(-1)
		, WaveMax(4)
	{
	}
	FireWaveAttackScript::~FireWaveAttackScript()
	{
	}
	void FireWaveAttackScript::Initialize()
	{
		RegisterAttackObject<FireWaveAttackObjectScript>(L"FireWaveAttack1");
		RegisterAttackObject<FireWaveAttackObjectScript>(L"FireWaveAttack2");
		RegisterAttackObject<FireWaveAttackObjectScript>(L"FireWaveAttack3");

		SetCoolTime(1.0f);

	}
	void FireWaveAttackScript::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();


			if (WaveIndex == -1)
			{
				if (activeAnim->GetKey() == L"Attack_WaveFireWave")
				{
					if (activeAnim->GetIndex() == 2)
					{
						Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
						float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
						SavePos(Vector3(ownerPos.x, ownerPos.y, ownerPosVZ));
						SetFlip(GetOwner()->GetFlip());
						WaveIndex = 1;
					}

				}
			}
			else if (WaveIndex < 4)
			{
				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				std::wstring waveName = L"FireWaveAttack";
				std::wstring FireIndex = std::to_wstring(WaveIndex);

				waveName.append(FireIndex);
				AttackObjectScript* FireWaveAttack = LoadAttackObject(waveName);
				if (FireWaveAttack->GetOwner()->GetState() == GameObject::eState::Paused)
				{
					FireWaveAttack->GetOwner()->SetState(GameObject::eState::Active);
					FireWaveAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					FireWaveAttack->GetOwner()->SetFlip(GetFlip());

					FireWaveAttack->SetAttack(true);
					Vector3 FirePos = Vector3(LoadPos().x, LoadPos().y, ownerPos.z);
					FirePos.x += 140.0f * (float)(WaveIndex - 1) * (1.0f - 2.0f * (float)GetFlip());
					FireWaveAttack->GetOwner()->GetComponent<Transform>()->SetPosition(FirePos);
					FireWaveAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(LoadPos().z);
					FireWaveAttack->GetOwner()->GetComponent<Animator>()->PlayAnimation(L"FireWaveWave", false);
					FireWaveAttack->clearTargets();
				}
				else
				{
					Animator* mAnimator = FireWaveAttack->GetOwner()->GetComponent<Animator>();
					if (mAnimator->GetActiveAnimation()->GetIndex() == 3)
					{
						WaveIndex++;
					}
				}
			}
			else
			{
				for (int i = 1; i < 4; i++)
				{
					std::wstring waveName = L"FireWaveAttack";
					std::wstring FireIdx = std::to_wstring(i);
					waveName.append(FireIdx);
					if (LoadAttackObject(waveName)->GetOwner()->GetState() != GameObject::eState::Paused)
						break;
					if (i == 3)
					{
						WaveIndex = -1;
						SetPause();
					}
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
							if (commands[i].type == PlayerScript::eCommandType::F)
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
