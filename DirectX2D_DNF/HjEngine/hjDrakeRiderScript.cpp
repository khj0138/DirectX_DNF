#include "hjDrakeRiderScript.h"

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

#include "hjDrakeRiderAttackBasicScript.h"
#include "hjDrakeRiderAttackBreathScript.h"


#include "hjAttackScriptManager.h"

#include "hjApplication.h"

extern hj::Application application;
namespace hj
{

	DrakeRiderScript::DrakeRiderScript()
		: mActivate(false)
		, mVelocity(Vector3::Zero)
		, attackName(L"")
	{
		SetStatus(MonsterScript::status(100, 100, false));
	}
	DrakeRiderScript::~DrakeRiderScript()
	{
	}
	void DrakeRiderScript::Initialize()
	{
		MonsterScript::Initialize();


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3{ 489.0f, 300.0f, 2.0f });
		GetOwner()->SetName(L"DrakeRider");
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));


		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2{ -20.0f,-50.0f });
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\Die", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\Hit", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\HitUp", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\HitDown", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\AttackBasic", 0.05f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_rider\\AttackBreath", 0.05f, Vector2(0.0f, 00.0f));
		mAnimator->CompleteEvent(L"drake_riderAttackBasic") = std::bind(&DrakeRiderScript::AttackCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_riderAttackBreath") = std::bind(&DrakeRiderScript::AttackCompleteEvent, this);

		mAnimator->PlayAnimation(L"drake_riderIdle", true);

		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetSize(Vector2{ 100.0f, 100.0f }, 180.0f);

		AttackScriptManager* AtkManager = GetAtkManager();
		AtkManager->RegisterAttackScript<DrakeRiderAttackBasicScript>(L"drake_riderAttackBasic");
		AtkManager->RegisterAttackScript<DrakeRiderAttackBreathScript>(L"drake_riderAttackBreath");
	}
	void DrakeRiderScript::Update()
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

	void DrakeRiderScript::LateUpdate()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->LateUpdate();
	}

	void DrakeRiderScript::Render()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->Render();
	}

	bool DrakeRiderScript::IsWalk()
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

			if (math::Vector2::Distance(playerPos2D, monPos2D) > 100.0f * fixedRes)
				return true;
		}
		return false;
	}
	bool DrakeRiderScript::IsAttack()
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
	void DrakeRiderScript::Idle()
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
		if (IsWalk())
		{
			SetMonsterState(MonsterScript::eMonsterState::Walk);
		}
	}
	void DrakeRiderScript::Walk()
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

	void DrakeRiderScript::Attack()
	{
		Animation* animation = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
		if (attackName == L"drake_riderAttackBasic")
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
		else if (attackName == L"drake_riderAttackBreath")
		{
			if (GetCurTime() > 0.5f && animation->GetPause() && animation->GetIndex() == 2)
			{
				animation->SetPause(false);
				SetCurTime(0.0f);


			}
			else if (GetCurTime() > 0.15f && !(animation->GetPause()) && animation->GetIndex() == 2)
			{
				animation->SetPause(true);
				SetCurTime(0.0f);
				GetOwner()->GetComponent<Rigidbody>()->SetVelocity(Vector3::Zero);

			}
		}
		
		
		if (!GetAtkManager()->CheckActivate(attackName))
		{
			animation->SetPause(false);
			SetMonsterState(MonsterScript::eMonsterState::Idle);
			SetCurTime(0.0f);
			return;
		}
	}
	void DrakeRiderScript::Hit()
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
	void DrakeRiderScript::Die()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		float mActiveAnimIndex = GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex();

		Vector3 velocity = rb->GetVelocity();
		if(mActiveAnimIndex < 4)
			rb->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
		else
			rb->SetVelocity(Vector3(400.0f * (1.0f - 2.0f * GetOwner()->GetFlip()), 0.0f, 0.0f));

		SetCurTime(GetCurTime() + Time::DeltaTime());
		if (GetCurTime() >= 1.2f)
		{
			GetOwner()->SetState(GameObject::eState::Paused);
		}
	}
	void DrakeRiderScript::Anim()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		//mAnimator->SetFlip(GetOwner()->GetFlip());
		MonsterScript::eMonsterState monsterState = GetMonsterState();
		MonsterScript::eMonsterState prevMonsterState = GetPrevMonsterState();
		switch (monsterState)
		{
		case MonsterScript::eMonsterState::Idle:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"drake_riderIdle", true);
			break;
		case MonsterScript::eMonsterState::Walk:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"drake_riderWalk", true);
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
				mAnimator->PlayAnimation(L"drake_riderDie", false);
			break;
		default:
			break;
		}
	}
	void DrakeRiderScript::AnimHit()
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
				mAnimator->PlayAnimation(L"drake_riderHit", false);
			else
			{
				mAnimator->PlayAnimation(L"drake_riderHitUp", false);
			}
		}
		else if (activeAnim->GetKey() == L"drake_riderHitUp")
		{
			if (velocity.y < 0.0f)
			{
				mAnimator->PlayAnimation(L"drake_riderHitDown", false);
				activeAnim->SetPause(true);
			}
		}
		else if (activeAnim->GetKey() == L"drake_riderHitDown")
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
	void DrakeRiderScript::AttackCompleteEvent()
	{
	}
}
