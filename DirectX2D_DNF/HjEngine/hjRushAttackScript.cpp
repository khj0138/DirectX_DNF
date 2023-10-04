#include "hjRushAttackScript.h"
#include "hjTime.h"

#include "hjRushAttackObjectScript.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjPlayerScript.h"
namespace hj
{

	RushAttackScript::RushAttackScript()
	{
	}
	RushAttackScript::~RushAttackScript()
	{
	}
	void RushAttackScript::Initialize()
	{
		RegisterAttackObject<RushAttackObjectScript>(L"RushAttack");
		SetCoolTime(10.0f);
	}
	void RushAttackScript::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->GetKey() == L"Attack_RushRush1")
			{
				AttackObjectScript* RushAttack = LoadAttackObject(L"RushAttack");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				RushAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				RushAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					RushAttack->GetOwner()->SetState(GameObject::eState::Paused);
					RushAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					RushAttack->SetAttack(false);
				}
				else if (activeAnim->GetIndex() == 0)
				{
					RushAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					RushAttack->GetOwner()->SetState(GameObject::eState::Active);
					RushAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					RushAttack->SetAttack(true);
					RushAttack->clearTargets();
				}
			}
			else if (activeAnim->GetKey() == L"Attack_RushRush2")
			{
				AttackObjectScript* RushAttack = LoadAttackObject(L"RushAttack");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				RushAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				RushAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					RushAttack->GetOwner()->SetState(GameObject::eState::Paused);
					RushAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					RushAttack->SetAttack(false);
				}
				else if (activeAnim->GetIndex() == 0)
				{
					RushAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					RushAttack->GetOwner()->SetState(GameObject::eState::Active);
					RushAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					RushAttack->SetAttack(true);
					RushAttack->clearTargets();
				}
			}
			else if (activeAnim->GetKey() == L"Attack_RushRush3")
			{
				AttackObjectScript* RushAttack = LoadAttackObject(L"RushAttack");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				RushAttack->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				RushAttack->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					RushAttack->GetOwner()->SetState(GameObject::eState::Paused);
					RushAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					RushAttack->SetAttack(false);
					SetPause();

				}
				else if (activeAnim->GetIndex() == 0)
				{
					RushAttack->GetOwner()->SetFlip(GetOwner()->GetFlip());
					RushAttack->GetOwner()->SetState(GameObject::eState::Active);
					RushAttack->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					RushAttack->SetAttack(true);
					RushAttack->clearTargets();
				}
			}
			else
			{
				SetPause();
			}
		}
		AttackScript::Update();
	}

	void RushAttackScript::Reset()
	{

	}

	void RushAttackScript::SetActivate(bool activate)
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
							if (commands[i].type == PlayerScript::eCommandType::Z && player->GetXMoveVector().size() > 0)
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
