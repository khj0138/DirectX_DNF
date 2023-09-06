//#include "hjDrakeSoldierScript.h"
//
//#include "hjTime.h"
//#include "hjInput.h"
//#include "hjCamera.h"
//#include "hjResources.h"
//
//#include "hjGameObject.h"
//
//#include "hjTransform.h"
//#include "hjAnimator.h"
//#include "hjRigidbody.h"
//#include "hjCollider2D.h"
//#include "hjMeshRenderer.h"
//
//
//
//#include "hjAttackScriptManager.h"
//
//#include "hjApplication.h"
//
//extern hj::Application application;
//namespace hj
//{
//
//	DrakeSoldierScript::DrakeSoldierScript()
//		: mActivate(false)
//		, mVelocity(Vector3::Zero)
//		, attackName(L"")
//	{
//		SetStatus(MonsterScript::status(100, 100, false));
//	}
//	DrakeSoldierScript::~DrakeSoldierScript()
//	{
//	}
//	void DrakeSoldierScript::Initialize()
//	{
//		MonsterScript::Initialize();
//		SetCoolTime(3.0f);
//		Transform* tr = GetOwner()->GetComponent<Transform>();
//		tr->SetScale(Vector3{ 401.0f, 325.0f, 2.0f });
//		GetOwner()->SetName(L"DrakeSoldier");
//		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
//		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
//		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
//
//
//		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
//		mAnimator->SetAnimatorOffset(Vector2{ 0.0f, -50.0f });
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Idle", 0.1f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Walk", 0.1f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Die", 0.5f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\Hit", 0.2f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackBasic", 0.1f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackJump", 0.1f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackRoar", 0.1f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackRush", 0.1f, Vector2(0.0f, 00.0f));
//		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\AttackSpear", 0.1f, Vector2(0.0f, 00.0f));
//		mAnimator->CompleteEvent(L"drake_soldierAttackBasic") = std::bind(&DrakeSoldierScript::AttackBasicCompleteEvent, this);
//		mAnimator->CompleteEvent(L"drake_soldierAttackJump") = std::bind(&DrakeSoldierScript::AttackJumpCompleteEvent, this);
//		mAnimator->CompleteEvent(L"drake_soldierAttackRoar") = std::bind(&DrakeSoldierScript::AttackRoarCompleteEvent, this);
//		mAnimator->CompleteEvent(L"drake_soldierAttackRush") = std::bind(&DrakeSoldierScript::AttackRushCompleteEvent, this);
//		mAnimator->CompleteEvent(L"drake_soldierAttackSpear") = std::bind(&DrakeSoldierScript::AttackSpearCompleteEvent, this);
//		mAnimator->CompleteEvent(L"drake_soldierHit") = std::bind(&DrakeSoldierScript::HitCompleteEvent, this);
//		mAnimator->CompleteEvent(L"drake_soldierDie") = std::bind(&DrakeSoldierScript::DieCompleteEvent, this);
//		mAnimator->PlayAnimation(L"drake_soldierIdle", true);
//
//		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
//		mCollider->SetSize(Vector2{ 50.0f, 50.0f }, 150.0f);
//
//		AttackScriptManager* AtkManager = GetAtkManager();
//		AtkManager->RegisterAttackScript<DrakeSoldierAttackBasicScript>(L"drake_soldierAttackBasic");
//		AtkManager->RegisterAttackScript<DrakeSoldierAttackJumpScript>(L"drake_soldierAttackJump");
//		AtkManager->RegisterAttackScript<DrakeSoldierAttackRoarScript>(L"drake_soldierAttackRoar");
//		AtkManager->RegisterAttackScript<DrakeSoldierAttackRushScript>(L"drake_soldierAttackRush");
//		AtkManager->RegisterAttackScript<DrakeSoldierAttackSpearScript>(L"drake_soldierAttackSpear");
//	}
//	void DrakeSoldierScript::Update()
//	{
//		MonsterScript::Update();
//
//		AttackScriptManager* AtkManager = GetAtkManager();
//
//		curTime += Time::DeltaTime();
//		switch (GetMonsterState())
//		{
//		case MonsterScript::eMonsterState::Idle:
//			Idle();
//			break;
//		case MonsterScript::eMonsterState::Walk:
//			Walk();
//			break;
//		case MonsterScript::eMonsterState::Attack:
//			Attack();
//			break;
//		case MonsterScript::eMonsterState::Hit:
//			Hit();
//			break;
//		case MonsterScript::eMonsterState::Die:
//			Die();
//			break;
//		default:
//			break;
//		}
//
//		Anim();
//
//		SetPrevMonsterState(GetMonsterState());
//
//		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
//		float posVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
//		AtkManager->SetPosition(Vector2{ pos.x,pos.y }, posVZ);
//		AtkManager->Update();
//	}
//
//	bool DrakeSoldierScript::IsWalk()
//	{
//		float fixedRes = (float)application.GetFixedWidth() / 800.f;
//
//		GameObject* target = GetTarget();
//		if (target != nullptr)
//		{
//			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
//			float playerVZ = target->GetComponent<Transform>()->GetVirtualZ();
//			Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);
//			Vector3 monPos = GetOwner()->GetComponent<Transform>()->GetPosition();
//			float monPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
//			Vector2 monPos2D = Vector2(monPos.x, monPosVZ);
//
//			if (math::Vector2::Distance(playerPos2D, monPos2D) > GetOwner()->GetComponent<Collider2D>()->GetSize().x / 2.0f * fixedRes
//				|| abs(playerPos2D.y - monPos2D.y) > GetOwner()->GetComponent<Collider2D>()->GetSize().y / 4.0f * fixedRes)
//				return true;
//		}
//		return false;
//	}
//	bool DrakeSoldierScript::IsAttack()
//	{
//		AttackScriptManager* AtkManager = GetAtkManager();
//
//		if (curTime < GetCoolTime())
//		{
//			return false;
//		}
//		else
//		{
//			for (auto iter = AtkManager->mAttackScripts.begin(); iter != AtkManager->mAttackScripts.end(); iter++)
//			{
//				if (iter->first == L"Detect")
//					continue;
//				if (AtkManager->LoadAttackScript(iter->first) != nullptr)
//				{
//					attackName = iter->first;
//					//curTime = 0.0f;
//					return true;
//				}
//			}
//			return false;
//		}
//	}
//	void DrakeSoldierScript::Idle()
//	{
//		Transform* tr = GetOwner()->GetComponent<Transform>();
//		Vector3 pos = tr->GetPosition();
//		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
//		Vector3 velocity = rb->GetVelocity();
//		rb->SetVelocity(Vector3(0.0f, velocity.y, 0.0f));
//
//		GameObject* target = GetTarget();
//		if (target != nullptr)
//		{
//			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
//			if (playerPos.x < pos.x)
//				GetOwner()->SetFlip(true);
//			else
//				GetOwner()->SetFlip(false);
//		}
//
//
//		if (IsWalk())
//		{
//			SetMonsterState(MonsterScript::eMonsterState::Walk);
//		}
//		if (IsAttack())
//		{
//			SetMonsterState(MonsterScript::eMonsterState::Attack);
//		}
//	}
//	void DrakeSoldierScript::Walk()
//	{
//		Transform* tr = GetOwner()->GetComponent<Transform>();
//		Vector3 pos = tr->GetPosition();
//		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
//		Vector3 velocity = rb->GetVelocity();
//
//		GameObject* target = GetTarget();
//		Vector2 moveVector = Vector2::Zero;
//		if (target != nullptr)
//		{
//			Vector3 playerPos = target->GetComponent<Transform>()->GetPosition();
//			float playerVZ = target->GetComponent<Transform>()->GetVirtualZ();
//			Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);
//			Vector3 monPos = GetOwner()->GetComponent<Transform>()->GetPosition();
//			float monPosVZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
//			Vector2 monPos2D = Vector2(monPos.x, monPosVZ);
//
//			if (playerPos2D.x <= monPos2D.x)
//			{
//				GetOwner()->SetFlip(true);
//				if (abs(playerPos2D.x - monPos2D.x) > GetOwner()->GetComponent<Collider2D>()->GetSize().x / 2.0f)
//					moveVector.x = -1.f;
//			}
//			else if (playerPos2D.x > monPos2D.x)
//			{
//				GetOwner()->SetFlip(false);
//				if (abs(playerPos2D.x - monPos2D.x) > GetOwner()->GetComponent<Collider2D>()->GetSize().x / 2.0f)
//					moveVector.x = 1.f;
//			}
//
//			if (playerPos2D.y > monPos2D.y)
//			{
//				if (abs(playerPos2D.y - monPos2D.y) > GetOwner()->GetComponent<Collider2D>()->GetSize().y / 4.0f)
//					moveVector.y = 1.f;
//			}
//			else
//			{
//				if (abs(playerPos2D.y - monPos2D.y) > GetOwner()->GetComponent<Collider2D>()->GetSize().y / 4.0f)
//					moveVector.y = -1.f;
//			}
//		}
//
//		moveVector.Normalize();
//		moveVector *= 100.0f;
//		if (!IsWalk())
//		{
//			SetMonsterState(MonsterScript::eMonsterState::Idle);
//
//			moveVector = Vector2::Zero;
//		}
//		else
//		{
//			moveVector.Normalize();
//			moveVector *= 100.0f;
//		}
//		velocity.x = moveVector.x;
//		velocity.z = moveVector.y;
//		rb->SetVelocity(velocity);
//	}
//
//	void DrakeSoldierScript::Attack()
//	{
//		Animation* animation = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
//		if (attackName == L"Drake_soldierAttackBasic")
//		{
//			if (curTime > 1.0f && animation->GetPause())
//			{
//				animation->SetPause(false);
//				curTime = 0.0f;
//
//			}
//			else if (curTime > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 1)
//			{
//				animation->SetPause(true);
//				curTime = 0.0f;
//			}
//		}
//		else if (attackName == L"Drake_soldierAttack2")
//		{
//			if (curTime > 1.0f && animation->GetPause())
//			{
//				animation->SetPause(false);
//				curTime = 0.0f;
//
//			}
//			else if (curTime > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 0)
//			{
//				animation->SetPause(true);
//				curTime = 0.0f;
//			}
//		}
//	}
//	void DrakeSoldierScript::Hit()
//	{
//		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
//		Vector3 velocity = rb->GetVelocity();
//		bool flip = GetOwner()->GetFlip();
//
//		Vector2 moveVector = Vector2::Zero;
//		if (flip)
//			moveVector.x = 1.0f;
//		else
//			moveVector.x = -1.0f;
//		moveVector.Normalize();
//		moveVector *= 200.0f;
//		velocity.x = moveVector.x;
//		velocity.z = moveVector.y;
//		rb->SetVelocity(velocity);
//	}
//	void DrakeSoldierScript::Die()
//	{
//		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
//		Vector3 velocity = rb->GetVelocity();
//		rb->SetVelocity(Vector3(0.0f, velocity.y, 0.0f));
//	}
//	void DrakeSoldierScript::Anim()
//	{
//		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
//		mAnimator->SetFlip(GetOwner()->GetFlip());
//		MonsterScript::eMonsterState monsterState = GetMonsterState();
//		MonsterScript::eMonsterState prevMonsterState = GetPrevMonsterState();
//		switch (monsterState)
//		{
//		case MonsterScript::eMonsterState::Idle:
//			if (prevMonsterState != monsterState)
//				mAnimator->PlayAnimation(L"Drake_soldierIdle", true);
//			break;
//		case MonsterScript::eMonsterState::Walk:
//			if (prevMonsterState != monsterState)
//				mAnimator->PlayAnimation(L"Drake_soldierWalk", true);
//			break;
//		case MonsterScript::eMonsterState::Attack:
//			if (prevMonsterState != monsterState)
//				mAnimator->PlayAnimation(attackName, true);
//			break;
//		case MonsterScript::eMonsterState::Hit:
//			if (prevMonsterState != monsterState)
//				mAnimator->PlayAnimation(L"Drake_soldierHit", true);
//			break;
//		case MonsterScript::eMonsterState::Die:
//			if (prevMonsterState != monsterState)
//				mAnimator->PlayAnimation(L"Drake_soldierDie", true);
//			break;
//		default:
//			break;
//		}
//	}
//	void DrakeSoldierScript::HitCompleteEvent()
//	{
//		SetMonsterState(MonsterScript::eMonsterState::Idle);
//
//		curTime = 0.0f;
//	}
//	void DrakeSoldierScript::Attack1StartEvent()
//	{
//
//
//
//	}
//	void DrakeSoldierScript::Attack2StartEvent()
//	{
//
//	}
//	void DrakeSoldierScript::Attack1CompleteEvent()
//	{
//		SetMonsterState(MonsterScript::eMonsterState::Idle);
//
//		curTime = 0.0f;
//	}
//	void DrakeSoldierScript::Attack2CompleteEvent()
//	{
//		SetMonsterState(MonsterScript::eMonsterState::Idle);
//
//		curTime = 0.0f;
//	}
//	void DrakeSoldierScript::DieCompleteEvent()
//	{
//		GetOwner()->SetState(GameObject::eState::Dead);
//	}
//}
