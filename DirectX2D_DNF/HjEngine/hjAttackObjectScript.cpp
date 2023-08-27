#include "hjAttackObjectScript.h"

#include "hjTime.h"

//#include "hjGameObject.h"
#include "hjAttackObject.h"
//#include "hjBehaviorTree.h"
#include "hjResources.h"
#include "hjMeshRenderer.h"
#include "hjCollider2D.h"
#include "hjAnimator.h"
#include "hjMonster.h"
#include "hjPlayer.h"
namespace hj
{

	AttackObjectScript::AttackObjectScript()
		: mOwner(nullptr)
	{
	}
	AttackObjectScript::~AttackObjectScript()
	{
	}
	void AttackObjectScript::Initialize()
	{
		mOwner = dynamic_cast<AttackObject*>(Component::GetOwner());
		mOwner->AddComponent<Collider2D>();
		if (mOwner->GetComponent<Animator>() == nullptr)
		{
			MeshRenderer* mr = mOwner->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		}
		else
		{
			MeshRenderer* mr = mOwner->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		}
		mOwner->GameObject::Initialize();
	}
	void AttackObjectScript::Update()
	{
		Vector3 pos = mOwner->GetPos();
		pos.x += mOwner->GetVelocity().x;
		mOwner->SetPos(pos);
		mOwner->SetPosVZ(mOwner->GetPosVZ() + mOwner->GetVelocity().y);
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

	void AttackObjectScript::Attack(Player* target)
	{
		AttackObject::status damageStat = mOwner->GetStatus();
		UINT damage = damageStat.Damage;
		float time = Time::DeltaTime();
		while (time < 1.0f)
		{
			time *= 10.0f;
		}
		time = time - ((UINT)time % 10);
		float randomDamage = time * (float)(damageStat.DamageRange);
		damage += (UINT)randomDamage;

		target->Attack(damage);
	}
	void AttackObjectScript::Attack(Monster* target)
	{
		AttackObject::status damageStat = mOwner->GetStatus();
		UINT damage = damageStat.Damage;
		float time = Time::DeltaTime();
		while (time < 1.0f)
		{
			time *= 10.0f;
		}
		time = time - ((UINT)time % 10);
		float randomDamage = time * (float)(damageStat.DamageRange);
		damage += (UINT)randomDamage;

		target->Attack(damage);
	}
}
