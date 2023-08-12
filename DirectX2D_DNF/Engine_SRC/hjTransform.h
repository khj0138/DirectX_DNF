#pragma once
#include "hjComponent.h"

namespace hj
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetRotation(Vector3 rotation) { mRotation = rotation; }
		void SetScale(Vector3 scale) { mScale = scale; }
		void SetRotation2D(float rotation) { mRotation = Vector3{ 0.0f, 0.0f, math::degreeToRadian(rotation) }; }
		void SetCamMoveRate(Vector2 moveRate) { mCamMoveRate = moveRate; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void YtoVirtualZ()
		{
			mVirtualZ += mPosition.y / cos(45.0f);
			mPosition.y = 0.0f;
		}
		void VirtualZtoY()
		{
			mPosition.y += mVirtualZ * cos(45.0f);
			mVirtualZ = 0.0f;
		}

		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }
		void SetVirtualZ(float z) { mVirtualZ = z; }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }
		float GetVirtualZ() { return mVirtualZ; }

		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* transform) { mParent = transform; }
		Transform* GetParent() { return mParent; }

	private:
		Vector3 mPosition;
		float mVirtualZ;
		Vector3 mRotation;
		Vector3 mScale;

		Vector3 mUp;
		Vector3 mFoward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;
		Vector2 mCamMoveRate;
	};
}
