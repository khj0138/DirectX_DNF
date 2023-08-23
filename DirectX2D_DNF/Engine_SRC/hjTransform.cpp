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
		mPrevPosition = mPosition;
	}

	void Transform::LateUpdate()
	{
		mWorld = Matrix::Identity;

		float fixedRes = (float)application.GetFixedWidth() / 800.f;
		//fixedRes = 1.0f;
		Vector3 fixedScale = mScale * fixedRes;
		//fixedScale.y = fixedScale.y * cosf(math::degreeToRadian(45.0f));
		//position.x = (position.x + imageScale.x / 2.0f) * fixedRes;// *moveRate.x;

		Matrix scale = Matrix::CreateScale(fixedScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Vector3 fixedPosition = Vector3::Zero;
		//float sec45 = 1.0f /cosf(math::degreeToRadian(45.0f));
		float sec45 = 1.4f;
		if (renderer::mainCamera != nullptr)
		{
			fixedPosition.x = mPosition.x;
			fixedPosition.y = mPosition.y * sec45 + (mScale.y / 2.0f) * sec45;
			fixedPosition.z = mPosition.z;
			Vector3 cameraPosition = renderer::mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector2 vect2VZ = Vector2(0, mVirtualZ);
			math::Vector2::rotation(vect2VZ, math::degreeToRadian(mRotation.z));
			//fixedPosition.y += vect2VZ.y *cosf(math::degreeToRadian(45.0f));
			//fixedPosition.y += vect2VZ.y *cosf(math::degreeToRadian(45.0f));
			//fixedPosition.y *= sec45;// *cosf(math::degreeToRadian(45.0f));
			fixedPosition.y += mVirtualZ;// *cosf(math::degreeToRadian(45.0f));
			//fixedPosition.y += mVirtualZ;

			//fixedPosition.y *= cosf(math::degreeToRadian(45.0f));
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
			fixedPosition.y += animator->GetAnimatorOffset().y * sec45;
		}

		fixedPosition = fixedPosition * fixedRes;
		Matrix position;
		position.Translation(fixedPosition);

		//mWorld = rotation * position;
		mWorld = scale * rotation * position;
		//mWorld._42 = mWorld._42 *cosf(math::degreeToRadian(45.0f));
		//mWorld = scale * mWorld;

		//mWorld._42 = mWorld._42 * cosf(math::degreeToRadian(45.0f));
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
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
	}

}
