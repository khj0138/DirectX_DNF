#include "hjDrakeSoldierScript.h"

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

#include "hjDrakeSoldierAttackBasicScript.h"
#include "hjDrakeSoldierAttackJumpScript.h"
#include "hjDrakeSoldierAttackSpearScript.h"
#include "hjDrakeSoldierAttackRushScript.h"
#include "hjDrakeSoldierAttackRoarScript.h"


#include "hjAttackScriptManager.h"

#include "hjApplication.h"

extern hj::Application application;
namespace hj
{

	DrakeSoldierScript::DrakeSoldierScript()
		: mActivate(false)
		, mVelocity(Vector3::Zero)
		, attackName(L"")
	{
		SetStatus(MonsterScript::status(100, 100, false, true));

	}
	DrakeSoldierScript::~DrakeSoldierScript()
	{
	}
	void DrakeSoldierScript::Initialize()
	{
		MonsterScript::Initialize();
		

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3{ 501.0f, 300.0f, 2.0f });
		GetOwner()->SetName(L"DrakeSoldier");
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));


		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2{ 0.0f,-50.0f });
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Die", 0.5f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Hit", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\HitUp", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\HitDown", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackBasic", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackJump", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackRoar", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackRush", 0.05f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackSpear", 0.05f, Vector2(0.0f, 00.0f));
		//mAnimator->CompleteEvent(L"drake_soldierAttackBasic") = std::bind(&DrakeSoldierScript::AttackBasicCompleteEvent, this);
		//mAnimator->CompleteEvent(L"drake_soldierAttackJump") = std::bind(&DrakeSoldierScript::AttackJumpCompleteEvent, this);
		//mAnimator->CompleteEvent(L"drake_soldierAttackRoar") = std::bind(&DrakeSoldierScript::AttackRoarCompleteEvent, this);
		//mAnimator->CompleteEvent(L"drake_soldierAttackRush") = std::bind(&DrakeSoldierScript::AttackRushCompleteEvent, this);
		//mAnimator->CompleteEvent(L"drake_soldierAttackSpear") = std::bind(&DrakeSoldierScript::AttackSpearCompleteEvent, this);mAnimator->CompleteEvent(L"drake_soldierAttackBasic") = std::bind(&DrakeSoldierScript::AttackBasicCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_soldierAttackBasic") = std::bind(&DrakeSoldierScript::AttackCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_soldierAttackJump") = std::bind(&DrakeSoldierScript::AttackCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_soldierAttackRoar") = std::bind(&DrakeSoldierScript::AttackCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_soldierAttackRush") = std::bind(&DrakeSoldierScript::AttackCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_soldierAttackSpear") = std::bind(&DrakeSoldierScript::AttackCompleteEvent, this);

		mAnimator->PlayAnimation(L"drake_soldierIdle", true);

		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetSize(Vector2{ 50.0f, 50.0f }, 150.0f);

		AttackScriptManager* AtkManager = GetAtkManager();
		AtkManager->RegisterAttackScript<DrakeSoldierAttackBasicScript>(L"drake_soldierAttackBasic");
		AtkManager->RegisterAttackScript<DrakeSoldierAttackJumpScript>(L"drake_soldierAttackJump");
		AtkManager->RegisterAttackScript<DrakeSoldierAttackRoarScript>(L"drake_soldierAttackRoar");
		AtkManager->RegisterAttackScript<DrakeSoldierAttackRushScript>(L"drake_soldierAttackRush");
		AtkManager->RegisterAttackScript<DrakeSoldierAttackSpearScript>(L"drake_soldierAttackSpear");
	}
	void DrakeSoldierScript::Update()
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

	void DrakeSoldierScript::LateUpdate()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->LateUpdate();
	}

	void DrakeSoldierScript::Render()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->Render();
	}

	bool DrakeSoldierScript::IsWalk()
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
	bool DrakeSoldierScript::IsAttack()
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
	void DrakeSoldierScript::Idle()
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


		if (IsAttack())
		{
			SetMonsterState(MonsterScript::eMonsterState::Attack);
		}
		else if (IsWalk())
		{
			SetMonsterState(MonsterScript::eMonsterState::Walk);
		}
	}
	void DrakeSoldierScript::Walk()
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
		else if (!IsWalk())
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

	void DrakeSoldierScript::Attack()
	{
		Animation* animation = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
		if (attackName == L"drake_soldierAttackBasic")
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
		else if (attackName == L"drake_soldierAttackJump")
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
		else if (attackName == L"drake_soldierAttackSpear")
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
		else if (attackName == L"drake_soldierAttackRush")
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

				Vector2 rushMove = Vector2(GetAtkManager()->GetTargetPos().x - colPos.x, GetAtkManager()->GetTargetPosVZ() - colPos.y );
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
		else if (attackName == L"drake_soldierAttackRoar")
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
	void DrakeSoldierScript::Hit()
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
	void DrakeSoldierScript::Die()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();
		rb->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
		SetCurTime(GetCurTime() + Time::DeltaTime());
		if (GetCurTime() >= 1.0f)
		{
			GetOwner()->SetState(GameObject::eState::Paused);
			GetAtkManager()->SetPause();
		}
	}
	void DrakeSoldierScript::Anim()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		//mAnimator->SetFlip(GetOwner()->GetFlip());
		MonsterScript::eMonsterState monsterState = GetMonsterState();
		MonsterScript::eMonsterState prevMonsterState = GetPrevMonsterState();
		switch (monsterState)
		{
		case MonsterScript::eMonsterState::Idle:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"drake_soldierIdle", true);
			break;
		case MonsterScript::eMonsterState::Walk:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"drake_soldierWalk", true);
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
				mAnimator->PlayAnimation(L"drake_soldierDie", true);
			break;
		default:
			break;
		}
	}
	void DrakeSoldierScript::AnimHit()
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
				mAnimator->PlayAnimation(L"drake_soldierHit", false);
			else
			{
				mAnimator->PlayAnimation(L"drake_soldierHitUp", false);
			}
		}
		else if (activeAnim->GetKey() == L"drake_soldierHitUp")
		{
			if (velocity.y < 0.0f)
			{
				mAnimator->PlayAnimation(L"drake_soldierHitDown", false);
				activeAnim->SetPause(true);
			}
		}
		else if (activeAnim->GetKey() == L"drake_soldierHitDown")
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
	void DrakeSoldierScript::AttackCompleteEvent()
	{
	}
}
