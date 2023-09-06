#pragma once
#include "hjEngine.h"
#include "hjGraphicDevice_Dx11.h"
#include "hjMesh.h"
#include "hjShader.h"
#include "hjConstantBuffer.h"
#include "hjCamera.h"
#include "hjLight.h"


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

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
		UINT flip;
		UINT back;
		float padding;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elpasedTime;
		float deltaTime;
		int padding;
	};


	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};
	CBUFFER(EtcCB, CBSLOT_ETC)
	{
		//float Time;
		Vector2 Move;
		Vector2 Expand;
		UINT Flip;
		UINT Repeat;
		Vector2 padding;
	};

	CBUFFER(TimeCB, CBSLOT_TIME)
	{
		float Time;
		Vector3 Empty;
	};

	CBUFFER(CollisionCB, CBSLOT_COLLISION)
	{
		UINT bCollision;
		Vector3 Empty;
	};
	CBUFFER(AtkEffectCB, CBSLOT_ATKEFFECT)
	{
		UINT type;
		float startPercent;
		float endPercent;
		float curPercent;
	};
	
	
	extern hj::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<hj::Light*> lights;
	extern hj::Camera* mainCamera;
	extern std::vector<hj::Camera*> cameras;
	extern std::vector<DebugMesh*> debugMeshs;

	void Initialize();
	void BindLights();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh* mesh);
}

