#pragma once
#include "hjComponent.h"
#include "hjTransform.h"
#include "hjGraphics.h"

namespace hj
{
	//class graphics::DebugMesh;
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		eColliderType GetType() { return mType ; }
		void SetSize(Vector2 size, float height = 0.0f) { 
			if(height == 0.0f)
				mSize = Vector3{ size.x, size.y, size.y };
			else
				mSize = Vector3{ size.x, size.y, height };
		}
		void SetCenter(Vector2 size) { mCenter = size; }
		UINT GetColliderID() { return mColliderID; }
		Vector3 GetSize() { return mSize * fixedRes; }
		Vector3 GetPosition() { return mPosition; }
		Transform* GetTransform() { return mTransform; }
		void SetCollision(bool collision) { bCollision = collision; }
		bool GetCollision() { return bCollision; }

		void SetCollisionHeight(Vector2 collisionHeight) { mCollisionHeight = collisionHeight; }
		Vector2 GetCollisionHeight() { return mCollisionHeight; }

		void CollisionMesh(bool collision) { mMesh->CollisionMesh(collision); }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector2 mCollisionHeight;
		Vector3 mPosition;
		Vector3 mSize;
		Vector2 mCenter;
		graphics::DebugMesh* mMesh;

		bool bCollision;
		float fixedRes;
	};
}

