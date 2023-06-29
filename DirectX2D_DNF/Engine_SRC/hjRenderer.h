#pragma once
#include "hjEngine.h"
#include "hjGraphicDevice_Dx11.h"
#include "hjMesh.h"
#include "hjShader.h"
#include "hjConstantBuffer.h"

using namespace hj::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern hj::Mesh* mesh;
	extern ID3D11Buffer* triangleConstantBuffer;
	extern hj::Shader* shader;

	void Initialize();
	void Release();
}

