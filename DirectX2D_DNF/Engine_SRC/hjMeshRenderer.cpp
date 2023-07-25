#include "hjMeshRenderer.h"
#include "hjGameObject.h"
#include "hjTransform.h"
#include "hjRenderer.h"
#include "hjTime.h"
#include "hjAnimator.h"

namespace hj
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
		, mScale(Vector2::One)
		, mMove(Vector2::Zero)
		, mTime(Vector2::Zero)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();
		BindUVBuffer();

		mMesh->BindBuffer();
		mMaterial->Binds();

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}
		mMesh->Render();

		mMaterial->Clear();
	}
	void MeshRenderer::BindUVBuffer()
	{
		mTime.x += Time::DeltaTime();
		if (mTime.x > abs(mMove.x))
			mTime.x = 0.0f;
		mTime.y += Time::DeltaTime();
		if (mTime.y > abs(mMove.y))
			mTime.y = 0.0f;
		Vector2 moveCB = Vector2::Zero;
		if (mMove.x != 0.0f)
			moveCB.x = mTime.x / mMove.x;
		if(mMove.y != 0.0f)
			moveCB.y = mTime.y / mMove.y;

		renderer::EtcCB etcCB = {};
		//etcCB.Time = 0.0f;
		etcCB.Move = moveCB;
		etcCB.Expand = mScale;
		etcCB.Flip = (UINT)mFlip;


		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Etc];
		cb->SetData(&etcCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
}
