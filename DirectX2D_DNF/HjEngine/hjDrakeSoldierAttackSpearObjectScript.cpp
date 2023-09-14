#include "hjDrakeSoldierAttackSpearObjectScript.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjPlayerScript.h"
#include "hjGameObject.h"

#include "hjCollider2D.h"

#include "hjResources.h"
#include "hjMeshRenderer.h"
#include "hjRigidbody.h"
namespace hj
{

	DrakeSoldierAttackSpearObjectScript::DrakeSoldierAttackSpearObjectScript()
		: AttackObjectScript(AttackObjectType::Monster)
	{

	}
	DrakeSoldierAttackSpearObjectScript::~DrakeSoldierAttackSpearObjectScript()
	{
	}
	void DrakeSoldierAttackSpearObjectScript::Initialize()
	{
		AttackObjectScript::Initialize();

		MeshRenderer* mr = GetOwner()->GetComponent<MeshRenderer>();
		mr->SetMaterial(Resources::Find<Material>(L"DrakeSpear"));
		GetOwner()->SetState(GameObject::eState::Paused);

		SetAnimate(false);
		SetAttack(false);
		SetVelocity(Vector2::Zero);
		SetStatus(5, 2, Vector2(100.0f, 0.0f));


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(176.0f, 20.0f, 1.0f));
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		col->SetSize(Vector2(50.0f, 50.0f), 0.0f);
		col->SetCollisionHeight(1.0f);

	}
	void DrakeSoldierAttackSpearObjectScript::Update()
	{
		AttackObjectScript::Update();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		if (rb->GetGround())
		{
			GetOwner()->SetState(GameObject::eState::Paused);
			GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
			SetAttack(false);
			return;
		}
		Vector3 velocity = rb->GetVelocity();
		Vector2 spearDirection = Vector2(velocity.x, velocity.y + velocity.z);
		spearDirection.Normalize();
		float spearRadian = atan2( 1.0f * spearDirection.y, spearDirection.x);
		tr->SetRotation(Vector3(0.0f, 0.0f, spearRadian));
	}



	void DrakeSoldierAttackSpearObjectScript::OnCollisionEnter(Collider2D* other)
	{
		PlayerScript* target = other->GetOwner()->FindScript<PlayerScript>();
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

	void DrakeSoldierAttackSpearObjectScript::OnCollisionStay(Collider2D* other)
	{
		PlayerScript* target = other->GetOwner()->FindScript<PlayerScript>();
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

	void DrakeSoldierAttackSpearObjectScript::OnCollisionExit(Collider2D* other)
	{
	}


}
