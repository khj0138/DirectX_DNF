#include "hjCollider2D.h"
#include "hjGameObject.h"
#include "hjRenderer.h"
#include "hjAnimator.h"
#include "hjApplication.h"

extern hj::Application application;

namespace hj
{
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, mType(eColliderType::Circle)
		, bCollision(true)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}
	Collider2D::~Collider2D()
	{
		delete mMesh;
	}
	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		Vector3 trScale = mTransform->GetScale();
		mSize = Vector3{ trScale.x, trScale.y, trScale.y };
		/*if (mType == eColliderType::Rect)
		{
			mSize = mTransform->GetScale();
		}
		else if (mType == eColliderType::Circle)
		{
			mSize = mTransform->GetScale();
			mSize.y = mSize.x;
		}*/

		mMesh = new DebugMesh();
		mMesh->bCollision = false;
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
		mPrevPosition = mPosition;
		Transform* tr = GetOwner()->GetComponent<Transform>();

		fixedRes = (float)application.GetFixedWidth() / 800.f;

		Vector3 size = mSize;// *fixedRes;
		Vector3 scale = Vector3(size.x, size.y, 1.0f);
		
		//scale.x *= size.x;
		//scale.y *= size.y;

		Vector3 pos = Vector3::Zero;
		Vector3 trPos = tr->GetPosition();

		Vector2 center = mCenter;
		//center *= fixedRes;
		if (GetOwner()->GetFlip())
		{
			center.x = center.x * -1.0f;
		}
		pos.y = tr->GetVirtualZ();

		
		pos.x += center.x;
		pos.y += center.y;

		pos.x += trPos.x; // transform 별도 적용
		pos.z = 1.0f;

		mPosition = pos;
		//float sec45 = 1.0f / cosf(math::degreeToRadian(45.0f));
		float sec45 = 1.4f;
		if (mMesh != nullptr)
		{
			mMesh->position = pos;

			//mMesh->position.y *= cosf(math::degreeToRadian(45.0f));
			//scale.y *= cosf(math::degreeToRadian(45.0f));
			mMesh->scale = scale;

			mMesh->rotation = tr->GetRotation();
			mMesh->rotation.z += mRotation;
			mMesh->type = mType;
			mMesh->setCurPercent(0.7f);

			/*Vector2 vect2VZ = Vector2(0, pos.y);
			math::Vector2::rotation(vect2VZ, math::degreeToRadian(mMesh->rotation.z));
			pos.y = vect2VZ.y;*/
			
			//mMesh->position.y = vect2VZ.y;// *cosf(math::degreeToRadian(45.0f));
			//mMesh->position.y -= scale.y / 2.0f;// *sec45;
			mMesh->position.y -= scale.y / 2.0f *sec45;
			//mMesh->bCollision = false;
		}

		renderer::PushDebugMeshAttribute(mMesh);
		mTransform = tr;
		SetCollisionRange(Vector2(mCollisionHeight + trPos.y, mCollisionHeight + trPos.y + size.z));
	}
	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		const std::vector<Script*> scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}
}