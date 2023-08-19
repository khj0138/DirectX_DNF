#include "hjAttackObject.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"
#include "hjResources.h"
#include "hjAttackScript.h"
//#include "hjBehaviorTree.h"

namespace hj
{
	AttackObject::AttackObject()
		: bActivate(false)
		, mCoolTime(0.0f)
		, bAnimate(false)
		//, attackHeight(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, animOffset(Vector2::Zero)
		, mAnimator(nullptr)
	{
	}
	AttackObject::~AttackObject()
	{
	}
	void AttackObject::Initialize()
	{
		
		/*AddComponent<Collider2D>();
		if (GetComponent<Animator>() == nullptr)
		{
			MeshRenderer* mr = AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		}
		else
		{
			MeshRenderer* mr = AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		}
		GameObject::Initialize();*/
	}
	void AttackObject::Update()
	{
		
		GameObject::Update();
	}
	void AttackObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void AttackObject::Render()
	{
		GameObject::Render();
	}
	/*void AttackObject::OnCollisionEnter(Collider2D* other)
	{
		
	}

	void AttackObject::OnCollisionStay(Collider2D* other)
	{
		
	}

	void AttackObject::OnCollisionExit(Collider2D* other)
	{
	}*/

	void AttackObject::SetActivate(bool activate)
	{
		
	}



}
