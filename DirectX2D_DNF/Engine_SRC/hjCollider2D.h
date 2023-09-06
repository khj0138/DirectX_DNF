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
		Vector2 GetCenter() { return mCenter; }
		UINT GetColliderID() { return mColliderID; }
		Vector3 GetSize() { return mSize; }// *fixedRes; }
		Vector3 GetPosition() { return mPosition; }
		Vector3 GetPrevPosition() { return mPrevPosition; }

		void SetRotation(float rotation) { mRotation = rotation; }
		void SetPosition(Vector3 position) { mPosition = position; }
		float GetRotation() { return mRotation; }

		Transform* GetTransform() { return mTransform; }
		void SetCollision(bool collision) { bCollision = collision; }
		bool GetCollision() { return bCollision; }

		void SetCollisionHeight(float collisionHeight) { mCollisionHeight = collisionHeight; }
		float GetCollisionHeight() { return mCollisionHeight; }

		void SetCollisionRange(Vector2 collisionRange) { mCollisionRange = collisionRange; }
		Vector2 GetCollisionRange() { return mCollisionRange; }

		void CollisionMesh(bool collision) { mMesh->CollisionMesh(collision); }
		graphics::DebugMesh* GetMesh(){ return mMesh; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector2 mCollisionRange;
		float mCollisionHeight;
		Vector3 mPosition;
		Vector3 mPrevPosition;
		float mRotation;

		Vector3 mSize;
		Vector2 mCenter;
		graphics::DebugMesh* mMesh;

		bool bCollision;
		float fixedRes;
	};
}

