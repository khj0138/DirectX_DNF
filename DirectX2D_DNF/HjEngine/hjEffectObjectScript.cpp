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

#include "hjAttackScriptManager.h"
namespace hj
{
	EffectObjectScript::EffectObjectScript(effectType type)
		: mType(type)
		, bAnimate(false)
		, bActivate(false)
		, mCastingTime(0.0f)
		, mCurTime(0.0f)
		, attackManager(nullptr)
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

	void EffectObjectScript::EffectRender()
	{
	}

	void EffectObjectScript::SetPause()
	{
		GetOwner()->SetState(GameObject::eState::Paused);
	}

	void EffectObjectScript::SetPos(GameObject* object)
	{
		float sec45 = 1.4f;
		Transform* tr = object->GetComponent<Transform>();
		Collider2D* objCol = object->GetComponent<Collider2D>();
		Vector2 objCenter = objCol->GetCenter();
		if (object->GetFlip())
		{
			objCenter.x = objCenter.x * -1.0f;
		}
		GetOwner()->SetFlip(object->GetFlip());
		GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition() + Vector3(objCenter.x, 0.0f, 0.0f));
		GetOwner()->GetComponent<Transform>()->SetRotation(tr->GetRotation());
		GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ() - tr->GetScale().y / 2.0f * sec45 + objCenter.y);
		//GetOwner()->SetFlip(object->GetFlip());
	}
	void EffectObjectScript::SetPosCol(GameObject* object)
	{
		float sec45 = 1.4f;
		Transform* tr = object->GetComponent<Transform>();
		Collider2D* objCol = object->GetComponent<Collider2D>();
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		Vector3 objColPos = objCol->GetPosition();
		Vector3 objColSize = objCol->GetSize();
		Vector2 objColCenter = objCol->GetCenter();
		if (object->GetFlip())
		{
			objColCenter.x = objColCenter.x * -1.0f;
		}
		GetOwner()->SetFlip(object->GetFlip());
		//objColPos.y -= objColSize.y / 2.0f * sec45;
		GetOwner()->GetComponent<Transform>()->SetVirtualZ(objColPos.y);
		//objColPos.x -= objColCenter.x;
		objColPos.y = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetPosition(objColPos);
		GetOwner()->GetComponent<Transform>()->SetRotation(tr->GetRotation());
		//GetOwner()->SetFlip(object->GetFlip());
	}
	
}
