#include "hjHysmarScript.h"

#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjResources.h"

#include "hjGameObject.h"

#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"


#include "hjAttackScriptManager.h"

#include "hjApplication.h"

extern hj::Application application;
namespace hj
{

	HysmarScript::HysmarScript()
		: mActivate(false)
		, phase(false)
		, mVelocity(Vector3::Zero)
		, attackName(L"")
	{
		SetStatus(MonsterScript::status(100, 100, false));
	}
	HysmarScript::~HysmarScript()
	{

	}
	void HysmarScript::Initialize()
	{
		MonsterScript::Initialize();


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3{ 780.0f, 509.0f, 2.0f });
		//tr->SetScale(Vector3{ 2341.0f, 1528.0f, 2.0f });
		GetOwner()->SetName(L"Hysmar");
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));


		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2{ 0.0f,-100.0f });
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Enter\\Phase1_Enter1", 0.13f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Enter\\Phase1_Enter2", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Enter\\Phase1_Enter3", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Enter\\Phase1_Enter4", 0.05f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Idle\\Idle1", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Idle\\Idle2", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_Jump\\Attack_Jump1", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_Jump\\Attack_Jump2", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Die", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Groggy", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Roar", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_JumpDown", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_Jump", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_LeftCrack", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_LeftCrash", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_Post", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_RightCrash", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_Roar", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_Rush", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_SwingTail", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_1p\\Phase1_Attack_WhipTail", 0.1f, Vector2(0.0f, 00.0f));


		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Die", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Groggy", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Phase2_Enter", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Roar", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\JumpUp", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\JumpDown", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_Jump", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_LeftCrack", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_LeftCrash", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_Post", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_RightCrash", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_Roar", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_Rush", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_SwingTail", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_WhipTail", 0.1f, Vector2(0.0f, 00.0f));
		//mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\boss\\hysmar\\hysmar_2p\\Attack_EarthQuake", 0.1f, Vector2(0.0f, 00.0f));

		mAnimator->CompleteEvent(L"Phase1_IdleIdle1") = std::bind(&HysmarScript::Idle1CompleteEvent, this);
		mAnimator->CompleteEvent(L"Phase1_IdleIdle2") = std::bind(&HysmarScript::Idle2CompleteEvent, this);


		//mAnimator->PlayAnimation(L"hysmar_1pIdle", true);
		SetMonsterState(eMonsterState::SceneEnter);
		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetSize(Vector2{ 50.0f, 50.0f }, 150.0f);

		AttackScriptManager* AtkManager = GetAtkManager();
	}
	void HysmarScript::Update()
	{
		if (GetCoolTime() == -1.0f)
		{
			SetCoolTime(3.0f + 0.1f * Time::TimeForRandom());
		}
		MonsterScript::Update();
		AttackScriptManager* AtkManager = GetAtkManager();

		SetCurTime(GetCurTime() + Time::DeltaTime());

		switch (GetMonsterState())
		{
		case MonsterScript::eMonsterState::SceneEnter:
			SceneEnter();
			break;
		case MonsterScript::eMonsterState::Idle:
			Idle();
			break;
		case MonsterScript::eMonsterState::Walk:
			Walk();
			break;
		case MonsterScript::eMonsterState::Attack:
			Attack();
			break;
		case MonsterScript::eMonsterState::Hit:
			Hit();
			break;
		case MonsterScript::eMonsterState::Die:
			Die();
			break;
		default:
			break;
		}

		Anim();

		SetPrevMonsterState(GetMonsterState());

		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float posVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		AtkManager->SetPosition(Vector2{ pos.x,pos.y }, posVZ);
		AtkManager->Update();
	}

	void HysmarScript::LateUpdate()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->LateUpdate();
	}

	void HysmarScript::Render()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->Render();
	}

	bool HysmarScript::IsWalk()
	{
		float fixedRes = (float)application.GetFixedWidth() / 800.f;

		GameObject* target = GetTarget();
		if (target != nullptr)
		{
			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
			float playerVZ = target->GetComponent<Transform>()->GetVirtualZ();
			Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);
			Vector3 monPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			float monPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
			Vector2 monPos2D = Vector2(monPos.x, monPosVZ);

			if (math::Vector2::Distance(playerPos2D, monPos2D) > 200.0f * fixedRes)
				return true;
		}
		return false;
	}
	bool HysmarScript::IsAttack()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		if (GetCurTime() < GetCoolTime())
		{
			return false;
		}
		else
		{
			for (auto iter = AtkManager->mAttackScripts.begin(); iter != AtkManager->mAttackScripts.end(); iter++)
			{
				if (iter->first == L"Detect")
					continue;
				if (AtkManager->LoadAttackScript(iter->first) != nullptr)
				{
					attackName = iter->first;
					//curTime = 0.0f;
					return true;
				}
			}
			return false;
		}
	}
	void HysmarScript::Idle()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		rb->SetVelocity(Vector3(0.0f, velocity.y, 0.0f));

		GameObject* target = GetTarget();
		if (target != nullptr)
		{
			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
			if (playerPos.x < pos.x)
				GetOwner()->SetFlip(true);
			else
				GetOwner()->SetFlip(false);
		}


		/*if (IsAttack())
		{
			SetMonsterState(MonsterScript::eMonsterState::Attack);
		}
		if (IsWalk())
		{
			SetMonsterState(MonsterScript::eMonsterState::Walk);
		}*/
	}
	void HysmarScript::Walk()
	{
		float fixedRes = (float)application.GetFixedWidth() / 800.0f;
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();

		GameObject* target = GetTarget();
		Vector2 moveVector = Vector2::Zero;
		if (target != nullptr)
		{
			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
			float playerVZ = target->GetComponent<Transform>()->GetVirtualZ();
			Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);
			Vector3 monPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			float monPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
			Vector2 monPos2D = Vector2(monPos.x, monPosVZ);

			if (playerPos2D.x <= monPos2D.x)
			{
				GetOwner()->SetFlip(true);
				if (abs(playerPos2D.x - monPos2D.x) > 70.0f * fixedRes)
					moveVector.x = -1.f;
			}
			else if (playerPos2D.x > monPos2D.x)
			{
				GetOwner()->SetFlip(false);
				if (abs(playerPos2D.x - monPos2D.x) > 70.0f * fixedRes)
					moveVector.x = 1.f;
			}

			if (playerPos2D.y > monPos2D.y)
			{
				if (abs(playerPos2D.y - monPos2D.y) > 25.0f * fixedRes)
					moveVector.y = 1.f;
			}
			else
			{
				if (abs(playerPos2D.y - monPos2D.y) > 25.0f * fixedRes)
					moveVector.y = -1.f;
			}
		}

		moveVector.Normalize();
		moveVector *= 100.0f;
		if (IsAttack())
		{
			SetMonsterState(MonsterScript::eMonsterState::Attack);
			moveVector = Vector2::Zero;
		}
		if (!IsWalk())
		{
			SetMonsterState(MonsterScript::eMonsterState::Idle);

			moveVector = Vector2::Zero;
		}
		else
		{
			moveVector.Normalize();
			moveVector *= 100.0f;
		}
		velocity.x = moveVector.x;
		velocity.z = moveVector.y;
		rb->SetVelocity(velocity);
	}

	void HysmarScript::Attack()
	{
		Animation* animation = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
		if (attackName == L"hysmarAttackBasic")
		{
			if (GetCurTime() > 1.0f && animation->GetPause())
			{
				animation->SetPause(false);
				SetCurTime(0.0f);

			}
			else if (GetCurTime() > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 1)
			{
				animation->SetPause(true);
				SetCurTime(0.0f);
			}
		}
		else if (attackName == L"hysmarAttackJump")
		{
			if (GetCurTime() > 1.0f && animation->GetPause())
			{
				float sec45 = 1.4f;
				Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
				Transform* tr = GetOwner()->GetComponent<Transform>();
				Collider2D* col = GetOwner()->GetComponent<Collider2D>();
				Vector3 colPos = col->GetPosition();
				Vector3 colSize = col->GetSize();
				float vz = tr->GetVirtualZ();
				colPos.y -= colSize.y / 2.0f * sec45;

				rb->SetGround(false);
				rb->SetVelocity(Vector3((GetAtkManager()->GetTargetPos().x - colPos.x), 1000.0f, GetAtkManager()->GetTargetPosVZ() - colPos.y));
				animation->SetPause(false);
				SetCurTime(0.0f);


			}
			else if (GetCurTime() > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 0)
			{
				GetAtkManager()->SetTargetColPos(GetTarget());
				animation->SetPause(true);
				SetCurTime(0.0f);

			}
		}
		else if (attackName == L"hysmarAttackSpear")
		{
			if (GetCurTime() > 1.0f && animation->GetPause())
			{
				animation->SetPause(false);
				SetCurTime(0.0f);
			}
			else if (GetCurTime() > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 1)
			{
				animation->SetPause(true);
				SetCurTime(0.0f);

			}
		}
		else if (attackName == L"hysmarAttackRush")
		{
			if (GetCurTime() > 1.0f && animation->GetPause())
			{
				float sec45 = 1.4f;
				Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
				Transform* tr = GetOwner()->GetComponent<Transform>();
				Collider2D* col = GetOwner()->GetComponent<Collider2D>();
				Vector3 colPos = col->GetPosition();
				Vector3 colSize = col->GetSize();
				float vz = tr->GetVirtualZ();
				colPos.y -= colSize.y / 2.0f * sec45;

				Vector2 rushMove = Vector2(GetAtkManager()->GetTargetPos().x - colPos.x, GetAtkManager()->GetTargetPosVZ() - colPos.y);
				rushMove.Normalize();
				rushMove *= 400.0f;

				rb->SetVelocity(Vector3(rushMove.x, 0.0f, rushMove.y));
				animation->SetPause(false);
				SetCurTime(0.0f);
			}
			else if (GetCurTime() > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 1)
			{
				GetAtkManager()->SetTargetColPos(GetTarget());

				animation->SetPause(true);
				SetCurTime(0.0f);

			}
		}
		else if (attackName == L"hysmarAttackRoar")
		{
			if (GetCurTime() > 1.0f && animation->GetPause())
			{
				animation->SetPause(false);
				SetCurTime(0.0f);
			}
			else if (GetCurTime() > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 2)
			{
				animation->SetPause(true);
				SetCurTime(0.0f);

			}
		}
		if (!GetAtkManager()->CheckActivate(attackName))
		{
			SetMonsterState(MonsterScript::eMonsterState::Idle);
			SetCurTime(0.0f);
			return;
		}
	}
	void HysmarScript::Hit()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		if (rb->GetGround())
		{
			if (abs(velocity.y) > 200.0f)
			{
				rb->SetGround(false);
				velocity.y *= -0.5f;
				velocity.x *= 0.5f;
				rb->SetVelocity(velocity);
			}
			else
			{
				SetHitTime(GetHitTime() + Time::DeltaTime());
			}
		}
		else
		{
			SetHitTime(0.0f);
		}

		if (GetHitTime() >= 0.3f)
		{
			rb->SetVelocity(Vector3::Zero);
			if (GetStatus().HP > 0.0f)
			{
				SetHitTime(0.0f);
				SetMonsterState(eMonsterState::Idle);
			}
			else
			{
				SetCurTime(0.0f);
				SetMonsterState(eMonsterState::Die);
				GetOwner()->GetComponent<Collider2D>()->GetMesh()->SetActivate(false);
				GetAtkManager()->SetPause();
			}

		}
	}
	void HysmarScript::Die()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		rb->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
		SetCurTime(GetCurTime() + Time::DeltaTime());
		if (GetCurTime() >= 1.0f)
		{
			GetOwner()->SetState(GameObject::eState::Paused);
		}
	}
	void HysmarScript::SceneEnter()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		MonsterScript::eMonsterState monsterState = GetMonsterState();
		MonsterScript::eMonsterState prevMonsterState = GetPrevMonsterState();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Animation* activeAnim = mAnimator->GetActiveAnimation();
		if (!phase)
		{
			if (prevMonsterState != monsterState)
			{
				GetOwner()->SetFlip(true);
				mAnimator->PlayAnimation(L"Phase1_EnterPhase1_Enter1", false);
				SetCurTime(0.0f);
			}
			else if (activeAnim->GetKey() == L"Phase1_EnterPhase1_Enter1")
			{
				if (GetCurTime() <= 3.0f)
				{
					activeAnim->SetPause(true);
				}
				else
				{
					rb->SetVelocity(Vector3(2000.0f, 0.0f, 0.0f));
					activeAnim->SetPause(false);
				}
				if(activeAnim->IsComplete())
				{
					if (tr->GetPosition().x < 900.0f)
					{
						SetCurTime(0.0f);
					}
					else if (tr->GetPosition().x >= 950.0f && GetCurTime() <= 1.0f)
					{
						rb->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
					}
					else if (tr->GetVirtualZ() >= 200.0f && GetCurTime() > 1.0f)
					{
						rb->SetVelocity(Vector3(0.0f, 0.0f, -1000.0f));
						mAnimator->PlayAnimation(L"Phase1_EnterPhase1_Enter2", false);

					}
				}
			}
			else if (activeAnim->GetKey() == L"Phase1_EnterPhase1_Enter2")
			{
				Vector3 scale = tr->GetScale();
				Vector2 scale2D = Vector2(scale.x, scale.y);
				scale2D *= (1.0f + 9.0f * Time::DeltaTime());
				if (scale2D.x > 2341.0f)
				{
					scale2D = Vector2(2341.0f, 1528.0f);
				}
				tr->SetScale(scale2D.x, scale2D.y, scale.z);

				Vector2 animOffset = mAnimator->GetAnimatorOffset();
				animOffset *= (1.0f + 9.0f * Time::DeltaTime());
				if (animOffset.y < -300.0f)
				{
					animOffset.y = -300.0f;
				}

				mAnimator->SetAnimatorOffset(animOffset);



				if (activeAnim->IsComplete())
				{
					if(tr->GetVirtualZ() < 200.0f)
					{
						tr->SetVirtualZ(200.0f);
						rb->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
						mAnimator->PlayAnimation(L"Phase1_EnterPhase1_Enter3", false);
						SetCurTime(0.0f);
					}
				}
			}
			else if (activeAnim->GetKey() == L"Phase1_EnterPhase1_Enter3")
			{
				if (activeAnim->IsComplete() && GetCurTime() > 0.4f)
				{
					mAnimator->PlayAnimation(L"Phase1_EnterPhase1_Enter4", false);
				}

				
			}
			else if (activeAnim->GetKey() == L"Phase1_EnterPhase1_Enter4")
			{
				if (!activeAnim->GetPause() && activeAnim->GetIndex() == 1 && GetCurTime() >= 0.5f)
				{
					activeAnim->SetPause(true);
				}
				else if (activeAnim->GetPause() && GetCurTime() > 1.0f)
				{
					activeAnim->SetPause(false);
					SetCurTime(0.0f);
				}
				else if (activeAnim->IsComplete())
				{
					SetMonsterState(eMonsterState::Idle);
					mAnimator->PlayAnimation(L"Phase1_EnterPhase1_Enter4", false);
				}
			}
		}
	}
	void HysmarScript::Anim()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		//mAnimator->SetFlip(GetOwner()->GetFlip());
		MonsterScript::eMonsterState monsterState = GetMonsterState();
		MonsterScript::eMonsterState prevMonsterState = GetPrevMonsterState();
		switch (monsterState)
		{
		case MonsterScript::eMonsterState::Idle:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"Phase1_IdleIdle1", false);
			break;
		case MonsterScript::eMonsterState::Attack:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(attackName, false);
			break;
		case MonsterScript::eMonsterState::Hit:
			AnimHit();
			break;
		case MonsterScript::eMonsterState::Die:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"hysmarDie", true);
			break;
		default:
			break;
		}
	}
	void HysmarScript::AnimHit()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		MonsterScript::eMonsterState monsterState = GetMonsterState();
		MonsterScript::eMonsterState prevMonsterState = GetPrevMonsterState();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		Animation* activeAnim = mAnimator->GetActiveAnimation();
		if (prevMonsterState != monsterState)
		{
			if (rb->GetGround())
				mAnimator->PlayAnimation(L"hysmarHit", false);
			else
			{
				mAnimator->PlayAnimation(L"hysmarHitUp", false);
			}
		}
		else if (activeAnim->GetKey() == L"hysmarHitUp")
		{
			if (velocity.y < 0.0f)
			{
				mAnimator->PlayAnimation(L"hysmarHitDown", false);
				activeAnim->SetPause(true);
			}
		}
		else if (activeAnim->GetKey() == L"hysmarHitDown")
		{
			if (velocity.y < 0.0f)
			{
				activeAnim->SetIndex(0);
			}
			else if (velocity.y > 0.0f)
			{
				activeAnim->SetIndex(1);
			}
			else
			{
				activeAnim->SetIndex(2);
				activeAnim->SetPause(false);
			}
		}
	}
	void HysmarScript::Idle1CompleteEvent()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->PlayAnimation(L"Phase1_IdleIdle2", false);
	}
	void HysmarScript::Idle2CompleteEvent()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->PlayAnimation(L"Phase1_IdleIdle1", false);
	}
	void HysmarScript::AttackCompleteEvent()
	{
	}
}
