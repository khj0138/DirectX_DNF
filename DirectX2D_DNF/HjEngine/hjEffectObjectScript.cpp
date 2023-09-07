#include "hjEffectObjectScript.h"

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
	EffectObjectScript::EffectObjectScript(effectType type)
		: mType(type)
		, bAnimate(false)
		, bActivate(false)
		, mCastingTime(0.0f)
		, mCurTime(0.0f)
	{
	}
	EffectObjectScript::~EffectObjectScript()
	{
	}
	void EffectObjectScript::Initialize()
	{
		if (mType == effectType::Sprite)
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		}
		else if (mType == effectType::Animation)
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		}
	}
	void EffectObjectScript::Update()
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

	void EffectObjectScript::SetPos(GameObject* object)
	{
		float sec45 = 1.4f;
		Transform* tr = object->GetComponent<Transform>();
		Collider2D* col = object->GetComponent<Collider2D>();
		Vector2 center = col->GetCenter();
		if (object->GetFlip())
		{
			center.x = center.x * -1.0f;
		}
		GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition() + Vector3(center.x, 0.0f, 0.0f));
		GetOwner()->GetComponent<Transform>()->SetRotation(tr->GetRotation());
		GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ() - tr->GetScale().y / 2.0f * sec45 + center.y);
		GetOwner()->SetFlip(object->GetFlip());
	}
}
