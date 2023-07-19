#include "hjMeshRenderer.h"
#include "hjGameObject.h"
#include "hjTransform.h"
#include "hjRenderer.h"


namespace hj
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
		, mScale(Vector2::One)
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
		mMesh->Render();

		mMaterial->Clear();
	}
	void MeshRenderer::BindUVBuffer()
	{
		//float resolution[2] = { (float)application.GetWidth() / 800.f, (float)application.GetHeight() / 450.f };
		float resolution[2] = { 1.0f, 1.0f };
		renderer::EtcCB etcCB = {};
		//etcCB.Time = 0.0f;
		etcCB.Res = { resolution[0], resolution[1] };
		etcCB.Expand = mScale;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Etc];
		cb->SetData(&etcCB);
		cb->Bind(eShaderStage::VS);
	}
}
