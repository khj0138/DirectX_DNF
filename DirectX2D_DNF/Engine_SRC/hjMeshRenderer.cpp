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

		Animator* animator = GetOwner()->GetComponent<Animator>();
		mMesh->BindBuffer();
		mFlip = GetOwner()->GetFlip();
		if (animator)
		{
			animator->Binds();
			if (animator->isAnimatorClose())
				return;
		}
		mMaterial->Binds();

		
		mMesh->Render();

		mMaterial->Clear();
	}
	void MeshRenderer::BindUVBuffer()
	{
		Vector2 moveCB = Vector2::Zero;
		if (mMove.x != 0.0f)
			moveCB.x = mTime.x / mMove.x;
		if (mMove.y != 0.0f)
			moveCB.y = mTime.y / mMove.y;

		if (mTime.x > abs(mMove.x))
		{
			moveCB.x = 1.0f;
			mTime.x = 0.0f;
		}
		if (mTime.y > abs(mMove.y))
		{
			moveCB.y = 1.0f;
			mTime.y = 0.0f;
		}
		mTime.x += Time::DeltaTime();
		mTime.y += Time::DeltaTime();

		renderer::EtcCB etcCB = {};
		//etcCB.Time = 0.0f;
		etcCB.Move = moveCB;
		etcCB.Expand = mScale;
		etcCB.Flip = (UINT)mFlip;
		etcCB.Repeat = (UINT)mRepeat;
		etcCB.padding = Vector2::Zero;

		/*if (UV.x < (-1.0f * Move.x) || UV.x >(-1.0f * Move.x + 0.25f))
			Out.UV = float2((In.UV.x + Move.x) * (Expand.x), (In.UV.y + Move.y) * Expand.y);*/
		

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Etc];
		cb->SetData(&etcCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);

	}
}
