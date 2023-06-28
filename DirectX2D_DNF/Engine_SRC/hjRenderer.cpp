#include "hjRenderer.h"

namespace hj::renderer
{
	Vertex vertexes[3] = {};

	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3D11Buffer* triangleIdxBuffer = nullptr;
	ID3D11Buffer* triangleConstantBuffer = nullptr;

	// error blob
	ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary Code
	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;

	// Pixel Shader code -> Binary Code
	ID3DBlob* trianglePSBlob = nullptr;

	// Vertex Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		// Vertex Buffer
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		hj::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		// Data Vector for Index Buffer 
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		
		// Index Buffer
		D3D11_BUFFER_DESC triangleIdxDesc = {};
		triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size();
		triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;
		triangleIdxDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		triangleIdxData.pSysMem = indexes.data();
		hj::graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		// Constant Buffer
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		hj::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);
		hj::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		hj::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
		//
	}

	void LoadShader()
	{
		hj::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		SetupState();
		LoadBuffer();
		LoadShader();
	}
}