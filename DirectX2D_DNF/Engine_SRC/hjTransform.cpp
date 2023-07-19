#include "hjTransform.h"
#include "hjRenderer.h"
#include "hjConstantBuffer.h"
#include "hjCamera.h"
#include "hjApplication.h"

#include "hjGameObject.h"
//#include "hjComponent.h"
#include "hjRenderer.h"

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

		float fixedRes = (float)application.GetWidth() / 800.f;
		fixedRes = 1.0f;
		Vector3 fixedScale = mScale * fixedRes;
		Matrix scale = Matrix::CreateScale(fixedScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Vector3 fixedPosition = mPosition;
		if (renderer::mainCamera != nullptr)
		{
			Vector3 cameraPosition = renderer::mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			fixedPosition.x += (1.0f - mCamMoveRate.x) * cameraPosition.x;
			fixedPosition.y += (1.0f - mCamMoveRate.y) * cameraPosition.y;

		}

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
