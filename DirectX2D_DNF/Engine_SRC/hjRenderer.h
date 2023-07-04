#pragma once
#include "hjEngine.h"
#include "hjGraphicDevice_Dx11.h"
#include "hjMesh.h"
#include "hjShader.h"
#include "hjConstantBuffer.h"

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

	extern Vertex vertexes[];
	extern hj::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Release();
}

