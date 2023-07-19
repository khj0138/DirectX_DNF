#pragma once
#include "hjEngine.h"
#include "hjGraphicDevice_Dx11.h"
#include "hjMesh.h"
#include "hjShader.h"
#include "hjConstantBuffer.h"
#include "hjCamera.h"

using namespace hj::math;
using namespace hj::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(EtcCB, CBSLOT_ETC)
	{
		float Time;
		Vector2 Res;
		float Empty;
	};

	extern hj::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern hj::Camera* mainCamera;
	extern std::vector<hj::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}

