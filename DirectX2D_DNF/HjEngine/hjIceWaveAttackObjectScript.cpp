#include "hjIceWaveAttackObjectScript.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjAnimator.h"
#include "hjRigidbody.h"
namespace hj
{

	IceWaveAttackObjectScript::IceWaveAttackObjectScript()
		: AttackObjectScript(AttackObjectType::Player)
	{

	}
	IceWaveAttackObjectScript::~IceWaveAttackObjectScript()
	{
	}
	void IceWaveAttackObjectScript::Initialize()
	{
		GetOwner()->SetState(GameObject::eState::Paused);

		Animator* mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->SetAnimatorOffset(Vector2(0.0f, -10.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\IceWave\\Wave1", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\IceWave\\Wave2", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\IceWave\\Wave3", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\IceWave\\Wave4", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\IceWave\\Wave5", 0.04f, Vector2(0.0f, 00.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Texture\\SwordMan\\Attack\\IceWave\\Wave6", 0.04f, Vector2(0.0f, 00.0f));
		AttackObjectScript::Initialize();

		SetAnimate(true);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f, 0.0f));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(90.0f, 213.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetSize(Vector2(30.0f, 30.0f), 80.0f);
		col->SetCenter(Vector2(30.0f, 0.0f));
		col->SetCollisionHeight(0.0f);
	}






	void IceWaveAttackObjectScript::Update()
	{
		AttackObjectScript::Update();
		Animator* mAnimator = GetOwner()->GetComponent<Animator>();
		if (mAnimator->GetActiveAnimation()->IsComplete())
			GetOwner()->SetState(GameObject::eState::Paused);
	}



	void IceWaveAttackObjectScript::OnCollisionEnter(Collider2D* other)
	{
		MonsterScript* target = other->GetOwner()->FindScript<MonsterScript>();

		if (target != nullptr)
		{
			if (GetAttack())
			{
				std::map<UINT32, float>::iterator iter = FindTarget(other->GetColliderID());
				UINT32 targetID = other->GetColliderID();
				//float coolTime = GetCoolTime();
				if (!(existTarget(targetID)))
				{
					registerTarget(targetID);
					// 공격 코드
					Attack(target);
				}
				//if (FindTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void IceWaveAttackObjectScript::OnCollisionStay(Collider2D* other)
	{
		MonsterScript* target = other->GetOwner()->FindScript<MonsterScript>();

		if (target != nullptr)
		{
			if (GetAttack())
			{
				std::map<UINT32, float>::iterator iter = FindTarget(other->GetColliderID());
				UINT32 targetID = other->GetColliderID();
				//float coolTime = GetCoolTime();
				if (!(existTarget(targetID)))
				{
					registerTarget(targetID);
					// 공격 코드
					Attack(target);
				}
				//if (FindTarget(targetID)->second >= coolTime)
				//{
				//	// 공격 코드
				//	setTargetZero(targetID)
				//}

			}
		}
	}

	void IceWaveAttackObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
