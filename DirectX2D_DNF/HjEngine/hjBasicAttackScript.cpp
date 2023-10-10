#include "hjBasicAttackScript.h"
#include "hjTime.h"

#include "hjBasicAttackObject1Script.h"
#include "hjBasicAttackObject2Script.h"
#include "hjBasicAttackObject3Script.h"

#include "hjBasicAddAttackObject1Script.h"
#include "hjBasicAddAttackObject2Script.h"
#include "hjBasicAddAttackObject3Script.h"
#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjRigidbody.h"
#include "hjPlayerScript.h"
namespace hj
{

	BasicAttackScript::BasicAttackScript()
	{
	}
	BasicAttackScript::~BasicAttackScript()
	{
	}
	void BasicAttackScript::Initialize()
	{
		RegisterAttackObject<BasicAttackObject1Script>(L"BasicAttack1");
		RegisterAttackObject<BasicAttackObject2Script>(L"BasicAttack2");
		RegisterAttackObject<BasicAttackObject3Script>(L"BasicAttack3");
		
		RegisterAttackObject<BasicAddAttackObject1Script>(L"BasicAddAttack1");
		RegisterAttackObject<BasicAddAttackObject2Script>(L"BasicAddAttack2");
		RegisterAttackObject<BasicAddAttackObject3Script>(L"BasicAddAttack3");

	}
	void BasicAttackScript::Update()
	{
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->GetKey() == L"Attack_BasicAttack1")
			{
				AttackObjectScript* BasicAttack1 = LoadAttackObject(L"BasicAttack1");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				BasicAttack1->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				BasicAttack1->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					BasicAttack1->GetOwner()->SetState(GameObject::eState::Paused);
					BasicAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					BasicAttack1->SetAttack(false);

					AttackObjectScript* BasicAddAttack1 = LoadAttackObject(L"BasicAddAttack1");
					BasicAddAttack1->GetOwner()->SetState(GameObject::eState::Paused);
					BasicAddAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					BasicAddAttack1->SetAttack(false);
				}
				else if (activeAnim->GetIndex() == 0)
				{
					BasicAttack1->GetOwner()->SetFlip(GetOwner()->GetFlip());
					BasicAttack1->GetOwner()->SetState(GameObject::eState::Active);
					BasicAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					BasicAttack1->SetAttack(true);
					BasicAttack1->clearTargets();
				}
				else if (activeAnim->GetIndex() == 3)
				{
					AttackObjectScript* BasicAddAttack1 = LoadAttackObject(L"BasicAddAttack1");

					Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
					float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
					BasicAddAttack1->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
					BasicAddAttack1->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
					BasicAddAttack1->GetOwner()->SetFlip(GetOwner()->GetFlip());
					BasicAddAttack1->GetOwner()->SetState(GameObject::eState::Active);
					BasicAddAttack1->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					//Vector3 vel = BasicAddAttack->GetOwner()->GetComponent<Rigidbody>()->GetVelocity();

					Vector3 vel = Vector3(200.0f, 0.0f, 0.0f);
					if (BasicAddAttack1->GetOwner()->GetFlip())
						vel.x = -1.0f * vel.x;
					BasicAddAttack1->GetOwner()->GetComponent<Rigidbody>()->SetVelocity(vel);
					Animator* mAnimator = BasicAddAttack1->GetOwner()->GetComponent<Animator>();
					mAnimator->PlayAnimation(L"AddwaveAddwave1", true);
					BasicAddAttack1->SetAttack(true);
					BasicAddAttack1->clearTargets();
				}
			}
			else if (activeAnim->GetKey() == L"Attack_BasicAttack2")
			{
				AttackObjectScript* BasicAttack2 = LoadAttackObject(L"BasicAttack2");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				BasicAttack2->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				BasicAttack2->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					BasicAttack2->GetOwner()->SetState(GameObject::eState::Paused);
					BasicAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					BasicAttack2->SetAttack(false);

					AttackObjectScript* BasicAddAttack2 = LoadAttackObject(L"BasicAddAttack2");
					BasicAddAttack2->GetOwner()->SetState(GameObject::eState::Paused);
					BasicAddAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					BasicAddAttack2->SetAttack(false);
				}
				else if (activeAnim->GetIndex() == 0)
				{
					BasicAttack2->GetOwner()->SetFlip(GetOwner()->GetFlip());
					BasicAttack2->GetOwner()->SetState(GameObject::eState::Active);
					BasicAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					BasicAttack2->SetAttack(true);
					BasicAttack2->clearTargets();
				}
				else if (activeAnim->GetIndex() == 2)
				{
					AttackObjectScript* BasicAddAttack2 = LoadAttackObject(L"BasicAddAttack2");

					Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
					float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
					BasicAddAttack2->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
					BasicAddAttack2->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
					BasicAddAttack2->GetOwner()->SetFlip(GetOwner()->GetFlip());
					BasicAddAttack2->GetOwner()->SetState(GameObject::eState::Active);
					BasicAddAttack2->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					//Vector3 vel = BasicAddAttack->GetOwner()->GetComponent<Rigidbody>()->GetVelocity();

					Vector3 vel = Vector3(200.0f, 0.0f, 0.0f);
					if (BasicAddAttack2->GetOwner()->GetFlip())
						vel.x = -1.0f * vel.x;
					BasicAddAttack2->GetOwner()->GetComponent<Rigidbody>()->SetVelocity(vel);
					Animator* mAnimator = BasicAddAttack2->GetOwner()->GetComponent<Animator>();
					mAnimator->PlayAnimation(L"AddwaveAddwave2", true);
					BasicAddAttack2->SetAttack(true);
					BasicAddAttack2->clearTargets();
				}
			}
			else if (activeAnim->GetKey() == L"Attack_BasicAttack3")
			{
				AttackObjectScript* BasicAttack3 = LoadAttackObject(L"BasicAttack3");

				Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
				BasicAttack3->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
				BasicAttack3->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);

				if (activeAnim->IsComplete())
				{
					BasicAttack3->GetOwner()->SetState(GameObject::eState::Paused);
					BasicAttack3->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					BasicAttack3->SetAttack(false);

					AttackObjectScript* BasicAddAttack3 = LoadAttackObject(L"BasicAddAttack3");
					BasicAddAttack3->GetOwner()->SetState(GameObject::eState::Paused);
					BasicAddAttack3->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					BasicAddAttack3->SetAttack(false);
					SetPause();

				}
				else if (activeAnim->GetIndex() == 0)
				{
					BasicAttack3->GetOwner()->SetFlip(GetOwner()->GetFlip());
					BasicAttack3->GetOwner()->SetState(GameObject::eState::Active);
					BasicAttack3->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					BasicAttack3->SetAttack(true);
					BasicAttack3->clearTargets();
				}
				else if (activeAnim->GetIndex() == 2)
				{
					AttackObjectScript* BasicAddAttack3 = LoadAttackObject(L"BasicAddAttack3");

					Vector3 ownerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
					float ownerPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
					BasicAddAttack3->GetOwner()->GetComponent<Transform>()->SetPosition(ownerPos);
					BasicAddAttack3->GetOwner()->GetComponent<Transform>()->SetVirtualZ(ownerPosVZ);
					BasicAddAttack3->GetOwner()->SetFlip(GetOwner()->GetFlip());
					BasicAddAttack3->GetOwner()->SetState(GameObject::eState::Active);
					BasicAddAttack3->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					//Vector3 vel = BasicAddAttack->GetOwner()->GetComponent<Rigidbody>()->GetVelocity();

					Vector3 vel = Vector3(200.0f, 0.0f, 0.0f);
					if (BasicAddAttack3->GetOwner()->GetFlip())
						vel.x = -1.0f * vel.x;
					BasicAddAttack3->GetOwner()->GetComponent<Rigidbody>()->SetVelocity(vel);
					Animator* mAnimator = BasicAddAttack3->GetOwner()->GetComponent<Animator>();
					mAnimator->PlayAnimation(L"AddwaveAddwave3", false);
					BasicAddAttack3->SetAttack(true);
					BasicAddAttack3->clearTargets();
				}
			}
			else
			{
				SetPause();
			}
		}
		AttackScript::Update();
	}

	void BasicAttackScript::Reset()
	{
		
	}

	void BasicAttackScript::SetActivate(bool activate)
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
							if (commands[i].type == PlayerScript::eCommandType::X)
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
