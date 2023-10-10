#include "hjDrakeArmorScript.h"

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

#include "hjDrakeArmorAttackBasicScript.h"
#include "hjDrakeArmorAttackBreathScript.h"
#include "hjDrakeArmorAttackRushScript.h"


#include "hjAttackScriptManager.h"

#include "hjApplication.h"

extern hj::Application application;
namespace hj
{

	DrakeArmorScript::DrakeArmorScript()
		: mActivate(false)
		, mVelocity(Vector3::Zero)
		, attackName(L"")
	{
		SetStatus(MonsterScript::status(100, 100, false, true));
	}
	DrakeArmorScript::~DrakeArmorScript()
	{
	}
	void DrakeArmorScript::Initialize()
	{
		MonsterScript::Initialize();


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3{ 489.0f, 300.0f, 2.0f });
		GetOwner()->SetName(L"DrakeArmor");
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));


		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2{ -20.0f,-50.0f });
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\Idle", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\Walk", 0.1f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\Die", 0.5f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\Hit", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\HitUp", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\HitDown", 0.2f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\AttackBasic", 0.05f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\AttackBreath", 0.05f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\Monster\\normal\\drake_armor\\AttackRush", 0.05f, Vector2(0.0f, 00.0f));
		mAnimator->CompleteEvent(L"drake_armorAttackBasic") = std::bind(&DrakeArmorScript::AttackCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_armorAttackBreath") = std::bind(&DrakeArmorScript::AttackCompleteEvent, this);
		mAnimator->CompleteEvent(L"drake_armorAttackRush") = std::bind(&DrakeArmorScript::AttackCompleteEvent, this);

		mAnimator->PlayAnimation(L"drake_armorIdle", true);

		Collider2D* mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetSize(Vector2{ 100.0f, 100.0f }, 180.0f);

		AttackScriptManager* AtkManager = GetAtkManager();
		AtkManager->RegisterAttackScript<DrakeArmorAttackBasicScript>(L"drake_armorAttackBasic");
		AtkManager->RegisterAttackScript<DrakeArmorAttackBreathScript>(L"drake_armorAttackBreath");
		AtkManager->RegisterAttackScript<DrakeArmorAttackRushScript>(L"drake_armorAttackRush");
	}
	void DrakeArmorScript::Update()
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

	void DrakeArmorScript::LateUpdate()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->LateUpdate();
	}

	void DrakeArmorScript::Render()
	{
		AttackScriptManager* AtkManager = GetAtkManager();

		AtkManager->Render();
	}

	bool DrakeArmorScript::IsWalk()
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
	bool DrakeArmorScript::IsAttack()
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
	void DrakeArmorScript::Idle()
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
	void DrakeArmorScript::Walk()
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

	void DrakeArmorScript::Attack()
	{
		Animation* animation = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
		if (attackName == L"drake_armorAttackBasic")
		{
			if (GetCurTime() > 0.5f && animation->GetPause() && animation->GetIndex() == 0)
			{
				animation->SetPause(false);
				SetCurTime(0.0f);

				Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
				Vector3 vel = Vector3(200.0f * (1.0f - 2.0f * GetOwner()->GetFlip()), 0.0f, 0.0f);
				rb->SetVelocity(vel);

			}
			else if (GetCurTime() > 0.2f && animation->GetPause() && animation->GetIndex() == 4)
			{
				animation->SetPause(false);
				SetCurTime(0.0f);
				animation->SetIndex(1);

				Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
				Vector3 vel = Vector3(200.0f * (1.0f - 2.0f * GetOwner()->GetFlip()), 0.0f, 0.0f);
				rb->SetVelocity(vel);

			}
			else if (GetCurTime() > 0.1f && !(animation->GetPause()) && animation->GetIndex() == 0)
			{
				animation->SetPause(true);
				SetCurTime(0.0f);
				GetOwner()->GetComponent<Rigidbody>()->SetVelocity(Vector3::Zero);

			}
			else if (GetCurTime() > 0.15f && !(animation->GetPause()) && animation->GetIndex() == 4)
			{
				animation->SetPause(true);
				SetCurTime(0.0f);
				GetOwner()->GetComponent<Rigidbody>()->SetVelocity(Vector3::Zero);


			}
		}
		else if (attackName == L"drake_armorAttackBreath")
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
		else if (attackName == L"drake_armorAttackRush")
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

				Vector2 rushMove = Vector2(GetAtkManager()->GetTargetPos().x - colPos.x, 0.0f);
				rushMove.Normalize();
				rushMove *= 800.0f;

				rb->SetVelocity(Vector3(rushMove.x, 0.0f, rushMove.y));
				animation->SetPause(false);
				SetCurTime(0.0f);
			}
			else if (GetCurTime() > 0.5f && !(animation->GetPause()) && animation->GetIndex() == 3)
			{
				GetAtkManager()->SetTargetColPos(GetTarget());

				animation->SetPause(true);
				SetCurTime(0.0f);

			}
		}
		/*else if (attackName == L"drake_armorAttackJump")
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
		else if (attackName == L"drake_armorAttackSpear")
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
		else if (attackName == L"drake_armorAttackRush")
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
		else if (attackName == L"drake_armorAttackRoar")
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
		}*/
		if (!GetAtkManager()->CheckActivate(attackName))
		{
			animation->SetPause(false);
			SetMonsterState(MonsterScript::eMonsterState::Idle);
			SetCurTime(0.0f);
			return;
		}
	}
	void DrakeArmorScript::Hit()
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
			}

		}
	}
	void DrakeArmorScript::Die()
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
	void DrakeArmorScript::Anim()
	{
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		//mAnimator->SetFlip(GetOwner()->GetFlip());
		MonsterScript::eMonsterState monsterState = GetMonsterState();
		MonsterScript::eMonsterState prevMonsterState = GetPrevMonsterState();
		switch (monsterState)
		{
		case MonsterScript::eMonsterState::Idle:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"drake_armorIdle", true);
			break;
		case MonsterScript::eMonsterState::Walk:
			if (prevMonsterState != monsterState)
				mAnimator->PlayAnimation(L"drake_armorWalk", true);
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
				mAnimator->PlayAnimation(L"drake_armorDie", true);
			break;
		default:
			break;
		}
	}
	void DrakeArmorScript::AnimHit()
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
				mAnimator->PlayAnimation(L"drake_armorHit", false);
			else
			{
				mAnimator->PlayAnimation(L"drake_armorHitUp", false);
			}
		}
		else if (activeAnim->GetKey() == L"drake_armorHitUp")
		{
			if (velocity.y < 0.0f)
			{
				mAnimator->PlayAnimation(L"drake_armorHitDown", false);
				activeAnim->SetPause(true);
			}
		}
		else if (activeAnim->GetKey() == L"drake_armorHitDown")
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
	void DrakeArmorScript::AttackCompleteEvent()
	{
	}
}
