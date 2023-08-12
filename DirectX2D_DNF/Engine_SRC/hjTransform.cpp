#include "hjTransform.h"
#include "hjRenderer.h"
#include "hjConstantBuffer.h"
#include "hjCamera.h"
#include "hjApplication.h"

#include "hjGameObject.h"
//#include "hjComponent.h"
#include "hjRenderer.h"
#include "hjAnimator.h"
#include "hjMath.h"

extern hj::Application application;
//extern hj::Camera* mainCamera;

namespace hj
{
	using namespace hj::graphics;
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mCamMoveRate(1.0f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::LateUpdate()
	{
		mWorld = Matrix::Identity;

		float fixedRes = (float)application.GetFixedWidth() / 800.f;
		//fixedRes = 1.0f;
		Vector3 fixedScale = mScale * fixedRes;
		//position.x = (position.x + imageScale.x / 2.0f) * fixedRes;// *moveRate.x;

		Matrix scale = Matrix::CreateScale(fixedScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Vector3 fixedPosition = mPosition;
		if (renderer::mainCamera != nullptr)
		{
			fixedPosition.x = fixedPosition.x;
			fixedPosition.y = (fixedPosition.y + mScale.y / 2.0f);
			Vector3 cameraPosition = renderer::mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			fixedPosition.y += mVirtualZ * cos(45.0f);
			fixedPosition.x += (1.0f - mCamMoveRate.x) * cameraPosition.x;
			fixedPosition.y += (1.0f - mCamMoveRate.y) * cameraPosition.y;
			/*if (GetOwner()->GetComponent<Animator>() != nullptr)
			{
				fixedPosition.y += fixedScale.y / 2.0f;
			}*/
		}
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator != nullptr)
		{
			fixedPosition.x += animator->GetAnimatorOffset().x;
			fixedPosition.y += animator->GetAnimatorOffset().y;
		}

		fixedPosition = fixedPosition * fixedRes;
		Matrix position;
		position.Translation(fixedPosition);

		mWorld = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{

	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.mWorld = mWorld;
		trCB.mView = Camera::GetGPUViewMatrix();
		trCB.mProjection = Camera::GetGPUProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}

}
