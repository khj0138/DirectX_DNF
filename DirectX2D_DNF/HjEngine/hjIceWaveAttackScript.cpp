#include "hjIceWaveAttackScript.h"
#include "hjTime.h"

#include "hjIceWaveAttackObjectScript.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjRigidbody.h"
#include "hjPlayerScript.h"
namespace hj
{

	IceWaveAttackScript::IceWaveAttackScript()
		: WaveIndex(-1)
		, WaveMax(4)
		, IceIndex(1)
		, IceMax(6)
	{
	}
	IceWaveAttackScript::~IceWaveAttackScript()
	{
	}
	void IceWaveAttackScript::Initialize()
	{
		RegisterAttackObject<IceWaveAttackObjectScript>(L"IceWaveAttack1");
		RegisterAttackObject<IceWaveAttackObjectScript>(L"IceWaveAttack2");
		RegisterAttackObject<IceWaveAttackObjectScript>(L"IceWaveAttack3");
		RegisterAttackObject<IceWaveAttackObjectScript>(L"IceWaveAttack4");
		RegisterAttackObject<IceWaveAttackObjectScript>(L"IceWaveAttack5");
		RegisterAttackObject<IceWaveAttackObjectScript>(L"IceWaveAttack6");

		SetCoolTime(3.0f);

	}
	void IceWaveAttackScript::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();

			if (WaveIndex == -1)
			{
				if (activeAnim->GetKey() == L"Attack_WaveIceWave")
				{
					if (activeAnim->GetIndex() == 2)
					{
						Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
						float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
						SavePos(Vector3(ownerPos.x, ownerPos.y, ownerPosVZ));	
						SetFlip(GetOwner()->GetFlip());
						WaveIndex = 0;
					}
				
				}
			}
			else if (WaveIndex < 4)
			{
				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				std::wstring waveName = L"IceWaveAttack";
				std::wstring iceidx = std::to_wstring(IceIndex);

				waveName.append(iceidx);

				AttackObjectScript* IceWaveAttack = LoadAttackObject(waveName);
				if (IceWaveAttack->GetOwner()->GetState() == GameObject::eState::Paused)
				{
					IceWaveAttack->GetOwner()->SetState(GameObject::eState::Active);
					IceWaveAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					IceWaveAttack->SetAttack(true);
					Vector3 IcePos = Vector3(LoadPos().x, LoadPos().y, ownerPos.z);
					IcePos.x += 30.0f * (float)(IceIndex - 1 + WaveIndex * 6) * (1.0f - 2.0f * (float)GetFlip());
					IceWaveAttack->GetOwner()->GetComponent<Transform>()->SetPosition(IcePos);
					IceWaveAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(LoadPos().z);
					std::wstring iceName = L"IceWaveWave";
					iceName.append(iceidx);
					IceWaveAttack->GetOwner()->GetComponent<Animator>()->PlayAnimation(iceName, false);
					IceWaveAttack->clearTargets();
				}
				else
				{
					Animator* mAnimator = IceWaveAttack->GetOwner()->GetComponent<Animator>();
					if (mAnimator->GetActiveAnimation()->GetIndex() == 1)
					{
						IceIndex++;
					}
				}
				if (IceIndex > 6)
				{
					WaveIndex++;
					IceIndex = 1;
				}
			}
			else
			{
				for (int i = 1; i <= 6; i++)
				{
					std::wstring waveName = L"IceWaveAttack";
					std::wstring iceidx = std::to_wstring(i);
					waveName.append(iceidx);
					if (LoadAttackObject(waveName)->GetOwner()->GetState() != GameObject::eState::Paused)
						break;
					if (i == 6)
					{
						WaveIndex = -1;
						IceIndex = 1;
						SetPause();
					}
				}

			}
		}
		AttackScript::Update();
	}

	void IceWaveAttackScript::Reset()
	{

	}

	void IceWaveAttackScript::SetActivate(bool activate)
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
							if (commands[i].type == PlayerScript::eCommandType::D)
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
