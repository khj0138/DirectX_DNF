#include "hjImageScript.h"
#include "hjConstantBuffer.h"
#include "hjCamera.h"
#include "hjTransform.h"
#include "hjApplication.h"
#include "hjGameObject.h"
#include "hjRenderer.h"
#include "hjTime.h"
#include "hjObject.h"

extern hj::Application application;

namespace hj
{
	ImageScript::ImageScript()
		: mScale(Vector2::One)
	{
	}
	ImageScript::~ImageScript()
	{
	}
	
	void ImageScript::LateUpdate()
	{
		float resolution[2] = { (float)application.GetWidth() / 800.f, (float)application.GetHeight() / 450.f };
		renderer::EtcCB etcCB = {};
		//etcCB.Time = 0.0f;
		etcCB.Res = { resolution[0], resolution[1] };
		etcCB.Expand = mScale;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Etc];
		cb->SetData(&etcCB);
		cb->Bind(eShaderStage::VS);
	}
	void ImageScript::Render()
	{
		float resolution[2] = { (float)application.GetWidth() / 800.f, (float)application.GetHeight() / 450.f };
		renderer::EtcCB etcCB = {};
		//etcCB.Time = 0.0f;
		etcCB.Res = { resolution[0], resolution[1] };
		etcCB.Expand = Vector2::One;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Etc];
		cb->SetData(&etcCB);
		cb->Bind(eShaderStage::VS);
	}
}