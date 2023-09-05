#include "hjAttackObjectScript.h"

#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjResources.h"

#include "hjGameObject.h"
//#include "hjMonsterScript.h"


#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"

#include "hjPlayerScript.h"
#include "hjMonsterScript.h"
//#include "hjAttackScript.h"

namespace hj
{

	AttackObjectScript::AttackObjectScript(AttackObjectType attackObjectType)
		: mType((AttackObjectType)attackObjectType)
		, bActivate(false)
		, bAnimate(false)
		, mCoolTime(0.0f)
		, mVelocity(Vector2::Zero)
		, animOffset(Vector2::Zero)
		, mAnimator(nullptr)
	{
	}
	AttackObjectScript::~AttackObjectScript()
	{
	}
	void AttackObjectScript::Initialize()
	{
		GetOwner()->AddComponent<Collider2D>();
		GetOwner()->AddComponent<Rigidbody>();
		if (GetOwner()->GetComponent<Animator>() == nullptr)
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		}
		else
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		}

		
	}
	void AttackObjectScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();
		pos.x += vel.x;
		tr->SetPosition(pos);
		tr->SetVirtualZ(tr->GetVirtualZ() + rb->GetVelocity().y);
		Script::Update();
	}

	void AttackObjectScript::OnCollisionEnter(Collider2D* other)
	{
		
	}

	void AttackObjectScript::OnCollisionStay(Collider2D* other)
	{
		
	}

	void AttackObjectScript::OnCollisionExit(Collider2D* other)
	{
	}

	
	void AttackObjectScript::Attack(Script* target)
	{
		UINT damage = mStatus.Damage;
		float time = Time::DeltaTime();
		while (time < 1.0f)
		{
			time *= 10.0f;
		}
		time = time - ((UINT)time % 10);
		float randomDamage = time * (float)(mStatus.DamageRange);
		damage += (UINT)randomDamage;
		
		
		if (mType == AttackObjectType::Player)
		{
			MonsterScript* monster = dynamic_cast<MonsterScript*>(target);
			if (monster != nullptr)
			{
				monster->Hit(damage, GetOwner()->GetFlip());
				return;
			}
		}
		else if (mType == AttackObjectType::Monster)
		{
			PlayerScript* player = dynamic_cast<PlayerScript*>(target);
			if (player != nullptr)
			{
				player->Hit(damage, GetOwner()->GetFlip());
				return;
			}
		}
	}
}
