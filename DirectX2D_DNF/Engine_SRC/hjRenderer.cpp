#include "hjRenderer.h"
#include "hjResources.h"
#include "hjTexture.h"
#include "hjMaterial.h"
#include "hjStructedBuffer.h"
#include "hjPaintShader.h"
#include "hjParticleShader.h"

namespace renderer
{
	using namespace hj;
	using namespace hj::graphics;
	hj::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};


	// light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;

	// mainCamera in Scene
	hj::Camera* mainCamera = nullptr;
	std::vector<hj::Camera*> cameras = {};
	std::vector<DebugMesh*> debugMeshs = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input layout 정점 구조 정보
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = hj::Resources::Find<Shader>(L"TriangleShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"SpriteShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"MoveShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"GridShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"DebugCircleShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"DebugRectShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"SpriteAnimShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
		shader = hj::Resources::Find<Shader>(L"ParticleShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"AttackCircleShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
		shader = hj::Resources::Find<Shader>(L"AttackRectShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
		
#pragma endregion
#pragma region Sampler State
		//Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};

		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadMesh()
	{
		//RECT
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};


		// PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);


		vertexes.clear();
		indexes.clear();

		//RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);


		// Create Mesh
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());


		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Rect Attack Mesh
		std::shared_ptr<Mesh> rectAttack = std::make_shared<Mesh>();
		Resources::Insert(L"AttackRect", rectAttack);
		rectAttack->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectAttack->CreateIndexBuffer(indexes.data(), indexes.size());
		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadiusX = 0.5f;
		float fRadiusY = 0.5f;
		//float fRadiusY = 0.5f * cosf(math::degreeToRadian(45.0f));
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadiusX * cosf(fTheta * (float)i)
				, fRadiusY * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
		// Circle Attack Mesh
		vertexes.clear();
		indexes.clear();

		center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2(0.0f, 0.0f);
		vertexes.push_back(center);

		iSlice = 1440;
		fRadiusX = 0.5f;
		fRadiusY = 0.5f;
		fTheta = XM_2PI / (float)1440;

		for (int i = 1; i <= iSlice; ++i)
		{
			center.pos = Vector3(fRadiusX * cosf(fTheta * (float)i)
				, fRadiusY * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			center.uv = Vector2(1.0f, 0.0f);
			vertexes.push_back(center);
		}

		for (int i = 1; i <= vertexes.size() - 1; ++i)
		{
			indexes.push_back(0);
			indexes.push_back(i);
		}

		std::shared_ptr<Mesh> circleAttack = std::make_shared<Mesh>();
		Resources::Insert(L"AttackCircle", circleAttack);
		circleAttack->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleAttack->CreateIndexBuffer(indexes.data(), indexes.size());
	}
	
	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		// Animation Buffer
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		//ParticleCB
		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		//NoiseCB
		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		// light structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eViewType::SRV, nullptr, true);

		// Etc Buffer
		constantBuffer[(UINT)eCBType::Etc] = new ConstantBuffer(eCBType::Etc);
		constantBuffer[(UINT)eCBType::Etc]->Create(sizeof(EtcCB));

		// Time Buffer
		constantBuffer[(UINT)eCBType::Time] = new ConstantBuffer(eCBType::Time);
		constantBuffer[(UINT)eCBType::Time]->Create(sizeof(TimeCB));

		// Collision Buffer
		constantBuffer[(UINT)eCBType::Collision] = new ConstantBuffer(eCBType::Collision);
		constantBuffer[(UINT)eCBType::Collision]->Create(sizeof(CollisionCB));

		// AtkEffect Buffer
		constantBuffer[(UINT)eCBType::AtkEffect] = new ConstantBuffer(eCBType::AtkEffect);
		constantBuffer[(UINT)eCBType::AtkEffect]->Create(sizeof(CollisionCB));
	}

	void CreateShader(const std::wstring vsName, const std::wstring psName, const std::wstring sName
		, const std::wstring gsName = L""
		, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		, eRSType rsType = eRSType::SolidBack
		, eDSType dsType = eDSType::Less
		, eBSType bsType = eBSType::AlphaBlend
		, const std::string funcName = "main")
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, vsName, funcName);
		if (gsName != L"")
		{
			shader->Create(eShaderStage::GS, gsName, funcName);
		}
		shader->Create(eShaderStage::PS, psName, funcName);
		shader->SetTopology(topology);
		shader->SetRSState(rsType);
		shader->SetDSState(dsType);
		shader->SetBSState(bsType);

		hj::Resources::Insert(sName, shader);
	}
	
	void LoadShader()
	{
		CreateShader(L"TriangleVS.hlsl", L"TrianglePS.hlsl", L"TriangleShader");
		CreateShader(L"SpriteVS.hlsl", L"SpritePS.hlsl", L"SpriteShader");
		CreateShader(L"MoveVS.hlsl", L"MovePS.hlsl", L"MoveShader");
		CreateShader(L"GridVS.hlsl", L"GridPS.hlsl", L"GridShader");
		CreateShader(L"SpriteAnimationVS.hlsl", L"SpriteAnimationPS.hlsl", L"SpriteAnimShader");
		CreateShader(L"DebugVS.hlsl", L"DebugPS.hlsl", L"DebugRectShader",L""
			, D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, eRSType::WireframeNone, eDSType::NoWrite);
		CreateShader(L"DebugVS.hlsl", L"DebugPS.hlsl", L"DebugCircleShader", L""
		, D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, eRSType::WireframeNone, eDSType::NoWrite);

		CreateShader(L"AtkCircleVS.hlsl", L"AtkCirclePS.hlsl", L"AttackCircleShader", L"AtkCircleGS.hlsl"
		, D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, eRSType::SolidNone, eDSType::NoWrite);
		CreateShader(L"AtkRectVS.hlsl", L"AtkRectPS.hlsl", L"AttackRectShader", L""
			, D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, eRSType::SolidNone, eDSType::NoWrite);
		
		CreateShader(L"ParticleVS.hlsl", L"ParticlePS.hlsl", L"ParticleShader", L"ParticleGS.hlsl"
		, D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST, eRSType::SolidNone, eDSType::NoWrite, eBSType::AlphaBlend);
		
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		hj::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		hj::Resources::Insert(L"ParticleSystemShader", psSystemShader);
	}

	void CreateMaterial(const std::wstring sName, const std::wstring mName, eRenderingMode rMode, const std::wstring tName = L"", const std::wstring tPath = L"")
	{
		std::shared_ptr<Material> material = std::make_shared<Material>();
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(sName);
		if(tName != L"")
		{ 
			std::wstring textureName = L"texture";
			textureName.append(tName);
			std::shared_ptr<Texture> texture
			= Resources::Load<Texture>(textureName, tPath);
			material->SetTexture(texture);
		}

		material->SetShader(spriteShader);
		material->SetRenderingMode(rMode);
		Resources::Insert(mName, material);
	}

	void LoadTexture()
	{
		//paint texture
		/*std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		hj::Resources::Insert(L"PaintTexuture", uavTexture);


		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		Resources::Load<Texture>(L"CartoonSmoke", L"..\\Resources\\particle\\CartoonSmoke.png");
	
		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");*/
	}

	void LoadMaterial()
	{
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		hj::Resources::Insert(L"PaintTexuture", uavTexture);
		//std::shared_ptr<Texture> particle = std::make_shared<Texture>();

		Resources::Load<Texture>(L"textureCartoonSmoke", L"..\\Resources\\Particle\\CartoonSmoke.png");
		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\Noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\Noise\\noise_02.png");
		//Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");

		CreateMaterial(L"SpriteShader", L"PaintMaterial", eRenderingMode::Transparent, L"PaintTexuture");
		CreateMaterial(L"ParticleShader", L"ParticleMaterial", eRenderingMode::Transparent, L"CartoonSmoke", L"..\\Resources\\Particle\\CartoonSmoke.png");


		//CreateMaterial(L"SpriteShader", L"SpriteMaterial", eRenderingMode::Transparent, L"SpriteMaterial", L"");
		CreateMaterial(L"SpriteShader", L"SpriteMaterial", eRenderingMode::Transparent);
		CreateMaterial(L"SpriteAnimShader", L"SpriteAnimationMaterial", eRenderingMode::Transparent);


		CreateMaterial(L"GridShader", L"GridMaterial", eRenderingMode::Transparent);
		CreateMaterial(L"DebugRectShader", L"DebugRectMaterial", eRenderingMode::Transparent);
		CreateMaterial(L"DebugCircleShader", L"DebugCircleMaterial", eRenderingMode::Transparent);

		CreateMaterial(L"AttackCircleShader", L"AttackCircleMaterial", eRenderingMode::Transparent);
		CreateMaterial(L"AttackRectShader", L"AttackRectMaterial", eRenderingMode::Transparent);
		
		
		
		CreateMaterial(L"SpriteShader", L"SpriteMaterial02", eRenderingMode::Transparent, L"SpriteMaterial02", L"..\\Resources\\Texture\\SwordManAttack.png");
		
		CreateMaterial(L"SpriteShader", L"LoadingSceneBackground", eRenderingMode::Transparent, L"LoadingSceneBackground", L"..\\Resources\\Texture\\CutScene\\machineRevolution.jpg");
		CreateMaterial(L"SpriteShader", L"LoadingSceneCircle", eRenderingMode::Transparent, L"LoadingSceneCircle", L"..\\Resources\\Texture\\CutScene\\LoadingCircle.png");
		CreateMaterial(L"SpriteShader", L"LoadingSceneBar", eRenderingMode::Transparent, L"LoadingSceneBar", L"..\\Resources\\Texture\\CutScene\\LoadingBar.png");
		CreateMaterial(L"SpriteShader", L"LoadingSceneEffect", eRenderingMode::Transparent, L"LoadingSceneEffect", L"..\\Resources\\Texture\\CutScene\\LoadingEffect.png");



		CreateMaterial(L"SpriteShader", L"Skasa_back_far_0", eRenderingMode::Transparent, L"Skasa_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\back_far_0.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_back_far_1", eRenderingMode::Transparent, L"Skasa_back_far_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\back_far_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_back_middle_0", eRenderingMode::Transparent, L"Skasa_back_middle_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\back_middle_0.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_backgorund_far_0", eRenderingMode::Transparent, L"Skasa_backgorund_far_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\Backgorund_far_0.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_background_middle_0", eRenderingMode::Transparent, L"Skasa_background_middle_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\Background_middle_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bigice_0", eRenderingMode::Transparent, L"Skasa_object_bigice_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bigice_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bigice_1", eRenderingMode::Transparent, L"Skasa_object_bigice_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bigice_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bottom_0", eRenderingMode::Transparent, L"Skasa_object_bottom_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bottom_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bottom_1", eRenderingMode::Transparent, L"Skasa_object_bottom_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bottom_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bottom_2", eRenderingMode::Transparent, L"Skasa_object_bottom_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bottom_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bottom_3", eRenderingMode::Transparent, L"Skasa_object_bottom_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bottom_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bottom_4", eRenderingMode::Transparent, L"Skasa_object_bottom_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bottom_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_bottom_5", eRenderingMode::Transparent, L"Skasa_object_bottom_5", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_bottom_5.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_ice_0", eRenderingMode::Transparent, L"Skasa_object_ice_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_ice_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_ice_1", eRenderingMode::Transparent, L"Skasa_object_ice_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_ice_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_ice_2", eRenderingMode::Transparent, L"Skasa_object_ice_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_ice_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_object_ice_3", eRenderingMode::Transparent, L"Skasa_object_ice_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_ice_3.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_tile", eRenderingMode::Transparent, L"Skasa_tile", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\Skasa_tile.png");
		CreateMaterial(L"SpriteShader", L"Skasa_tile1", eRenderingMode::Transparent, L"Skasa_tile1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\Skasa_tile1.png");

		CreateMaterial(L"SpriteShader", L"Skasa_common_back_far_0",  eRenderingMode::Transparent, L"Skasa_common_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_far_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_far_deco_0", eRenderingMode::Transparent, L"Skasa_common_back_far_deco_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_far_deco_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_far_deco_1", eRenderingMode::Transparent, L"Skasa_common_back_far_deco_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_far_deco_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_far_deco_2", eRenderingMode::Transparent, L"Skasa_common_back_far_deco_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_far_deco_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_far_deco_3", eRenderingMode::Transparent, L"Skasa_common_back_far_deco_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_far_deco_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_far_deco_4", eRenderingMode::Transparent, L"Skasa_common_back_far_deco_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_far_deco_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_bush_0", eRenderingMode::Transparent, L"Skasa_common_back_middle_bush_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_bush_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_bush_1", eRenderingMode::Transparent, L"Skasa_common_back_middle_bush_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_bush_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_deco_0", eRenderingMode::Transparent, L"Skasa_common_back_middle_deco_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_deco_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_deco_1", eRenderingMode::Transparent, L"Skasa_common_back_middle_deco_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_deco_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_deco_2", eRenderingMode::Transparent, L"Skasa_common_back_middle_deco_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_deco_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_deco_3", eRenderingMode::Transparent, L"Skasa_common_back_middle_deco_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_deco_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_filter_0", eRenderingMode::Transparent, L"Skasa_common_back_middle_filter_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_filter_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_icetile_0", eRenderingMode::Transparent, L"Skasa_common_back_middle_icetile_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_icetile_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_0", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_1", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_2", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_3", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_4", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_5", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_5", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_5.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_6", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_6", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_6.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_back_middle_pavillion_7", eRenderingMode::Transparent, L"Skasa_common_back_middle_pavilion_7", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_back_middle_pavilion_7.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_border_0", eRenderingMode::Transparent, L"Skasa_common_border_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_border_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_border_1", eRenderingMode::Transparent, L"Skasa_common_border_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_border_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_border_2", eRenderingMode::Transparent, L"Skasa_common_border_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_border_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_border_3", eRenderingMode::Transparent, L"Skasa_common_border_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_border_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_icicle_0", eRenderingMode::Transparent, L"Skasa_common_icicle_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_icicle_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_icicle_1", eRenderingMode::Transparent, L"Skasa_common_icicle_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_icicle_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_icicle_2", eRenderingMode::Transparent, L"Skasa_common_icicle_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_icicle_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_icicle_3", eRenderingMode::Transparent, L"Skasa_common_icicle_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_icicle_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_icicle_4", eRenderingMode::Transparent, L"Skasa_common_icicle_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_icicle_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_icicle_5", eRenderingMode::Transparent, L"Skasa_common_icicle_5", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_icicle_5.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_0", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_1", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_2", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_3", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_4", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_5", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_5", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_5.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_6", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_6", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_6.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_7", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_7", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_7.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_8", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_8", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_8.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_pillar_fence_9", eRenderingMode::Transparent, L"Skasa_common_pillar_fence_9", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_pillar_fence_9.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_0_0",  eRenderingMode::Transparent, L"Skasa_common_snow_0_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_0_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_0_1",  eRenderingMode::Transparent, L"Skasa_common_snow_0_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_0_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_0_2",  eRenderingMode::Transparent, L"Skasa_common_snow_0_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_0_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_0_3",  eRenderingMode::Transparent, L"Skasa_common_snow_0_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_0_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_0_4",  eRenderingMode::Transparent, L"Skasa_common_snow_0_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_0_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_00",  eRenderingMode::Transparent, L"Skasa_common_snow_1_00", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_00.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_01",  eRenderingMode::Transparent, L"Skasa_common_snow_1_01", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_01.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_02",  eRenderingMode::Transparent, L"Skasa_common_snow_1_02", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_02.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_03",  eRenderingMode::Transparent, L"Skasa_common_snow_1_03", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_03.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_04",  eRenderingMode::Transparent, L"Skasa_common_snow_1_04", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_04.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_05",  eRenderingMode::Transparent, L"Skasa_common_snow_1_05", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_05.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_06",  eRenderingMode::Transparent, L"Skasa_common_snow_1_06", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_06.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_07",  eRenderingMode::Transparent, L"Skasa_common_snow_1_07", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_07.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_08",  eRenderingMode::Transparent, L"Skasa_common_snow_1_08", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_08.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_09",  eRenderingMode::Transparent, L"Skasa_common_snow_1_09", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_09.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_10",  eRenderingMode::Transparent, L"Skasa_common_snow_1_10", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_10.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_11",  eRenderingMode::Transparent, L"Skasa_common_snow_1_11", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_11.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_12",  eRenderingMode::Transparent, L"Skasa_common_snow_1_12", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_12.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_13",  eRenderingMode::Transparent, L"Skasa_common_snow_1_13", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_13.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_14",  eRenderingMode::Transparent, L"Skasa_common_snow_1_14", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_14.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_15",  eRenderingMode::Transparent, L"Skasa_common_snow_1_15", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_15.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_16",  eRenderingMode::Transparent, L"Skasa_common_snow_1_16", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_16.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_17",  eRenderingMode::Transparent, L"Skasa_common_snow_1_17", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_17.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_18",  eRenderingMode::Transparent, L"Skasa_common_snow_1_18", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_18.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_snow_1_19",  eRenderingMode::Transparent, L"Skasa_common_snow_1_19", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_snow_1_19.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_0",  eRenderingMode::Transparent, L"Skasa_common_tile_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_1",  eRenderingMode::Transparent, L"Skasa_common_tile_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_2",  eRenderingMode::Transparent, L"Skasa_common_tile_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_3",  eRenderingMode::Transparent, L"Skasa_common_tile_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_4",  eRenderingMode::Transparent, L"Skasa_common_tile_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_deco_0",  eRenderingMode::Transparent, L"Skasa_common_tile_deco_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_deco_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_deco_1",  eRenderingMode::Transparent, L"Skasa_common_tile_deco_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_deco_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_deco_2",  eRenderingMode::Transparent, L"Skasa_common_tile_deco_2", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_deco_2.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_deco_3",  eRenderingMode::Transparent, L"Skasa_common_tile_deco_3", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_deco_3.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_deco_4",  eRenderingMode::Transparent, L"Skasa_common_tile_deco_4", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_deco_4.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_deco_5",  eRenderingMode::Transparent, L"Skasa_common_tile_deco_5", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_deco_5.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_deco_6",  eRenderingMode::Transparent, L"Skasa_common_tile_deco_6", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_deco_6.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_ex_0",  eRenderingMode::Transparent, L"Skasa_common_tile_ex_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_ex_0.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile_ex_1",  eRenderingMode::Transparent, L"Skasa_common_tile_ex_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile_ex_1.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile", eRenderingMode::Transparent, L"Skasa_common_tile", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile.png");
		CreateMaterial(L"SpriteShader", L"Skasa_common_tile1", eRenderingMode::Transparent, L"Skasa_common_tile1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\common_tile1.png");

		//CreateMaterial(L"MoveShader", L"Skasa_object_mist_0", eRenderingMode::Transparent, L"Skasa_object_mist_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_mist_0.png");
		//CreateMaterial(L"MoveShader", L"Skasa_object_mist_1", eRenderingMode::Transparent, L"Skasa_object_mist_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_mist_1.png");
		

		CreateMaterial(L"SpriteShader", L"Spirazzi_back_far_0", eRenderingMode::Transparent, L"Spirazzi_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\Back_far_0.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_far_1", eRenderingMode::Transparent, L"Spirazzi_back_far_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_far_1.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_far_2", eRenderingMode::Transparent, L"Spirazzi_back_far_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_far_2.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_0", eRenderingMode::Transparent, L"Spirazzi_back_middle_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_0.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_1", eRenderingMode::Transparent, L"Spirazzi_back_middle_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_1.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_2", eRenderingMode::Transparent, L"Spirazzi_back_middle_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_2.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_3", eRenderingMode::Transparent, L"Spirazzi_back_middle_3", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_3.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_4", eRenderingMode::Transparent, L"Spirazzi_back_middle_4", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_4.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_5", eRenderingMode::Transparent, L"Spirazzi_back_middle_5", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_5.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_6", eRenderingMode::Transparent, L"Spirazzi_back_middle_6", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_6.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_back_middle_7", eRenderingMode::Transparent, L"Spirazzi_back_middle_7", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\back_middle_7.png");

		CreateMaterial(L"SpriteShader", L"Spirazzi_tile1", eRenderingMode::Transparent, L"Spirazzi_tile1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\Spirazzi_tile1.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_tile", eRenderingMode::Transparent, L"Skasa_tile", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\Skasa_tile.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_tile1", eRenderingMode::Transparent, L"Skasa_tile1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\Skasa_tile1.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_0", eRenderingMode::Transparent, L"Spirazzi_fog_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_0.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_1", eRenderingMode::Transparent, L"Spirazzi_fog_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_1.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_2", eRenderingMode::Transparent, L"Spirazzi_fog_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_2.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_3", eRenderingMode::Transparent, L"Spirazzi_fog_3", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_3.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_4", eRenderingMode::Transparent, L"Spirazzi_fog_4", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_4.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_normal_0", eRenderingMode::Transparent, L"Spirazzi_fog_normal_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_normal_0.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_normal_1", eRenderingMode::Transparent, L"Spirazzi_fog_normal_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_normal_1.png");
		CreateMaterial(L"MoveShader", L"Spirazzi_fog_normal_2", eRenderingMode::Transparent, L"Spirazzi_fog_normal_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\fog_normal_2.png");

		CreateMaterial(L"SpriteShader", L"Spirazzi_object_0", eRenderingMode::Transparent, L"Spirazzi_object_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_0.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_object_1", eRenderingMode::Transparent, L"Spirazzi_object_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_1.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_object_2", eRenderingMode::Transparent, L"Spirazzi_object_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_2.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_object_3", eRenderingMode::Transparent, L"Spirazzi_object_3", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_3.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_object_4", eRenderingMode::Transparent, L"Spirazzi_object_4", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_4.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_object_5", eRenderingMode::Transparent, L"Spirazzi_object_5", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_5.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_object_6", eRenderingMode::Transparent, L"Spirazzi_object_6", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_6.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_object_7", eRenderingMode::Transparent, L"Spirazzi_object_7", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\object_7.png");

		CreateMaterial(L"SpriteShader", L"Spirazzi_nest_0", eRenderingMode::Transparent, L"Spirazzi_nest_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\nest_0.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_nest_1", eRenderingMode::Transparent, L"Spirazzi_nest_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\nest_1.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_nest_2", eRenderingMode::Transparent, L"Spirazzi_nest_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\nest_2.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_nest_3", eRenderingMode::Transparent, L"Spirazzi_nest_3", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\nest_3.png");

		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_0", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_0.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_1", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_1.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_2", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_2.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_3", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_3", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_3.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_4", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_4", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_4.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_5", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_5", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_5.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_6", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_6", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_6.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_bottom_obj_7", eRenderingMode::Transparent, L"Spirazzi_bottom_obj_7", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\bottom_obj_7.png");
		
		CreateMaterial(L"SpriteShader", L"Spirazzi_border_0", eRenderingMode::Transparent, L"Spirazzi_border_0", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\border_0.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_border_1", eRenderingMode::Transparent, L"Spirazzi_border_1", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\border_1.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_border_2", eRenderingMode::Transparent, L"Spirazzi_border_2", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\border_2.png");
		CreateMaterial(L"SpriteShader", L"Spirazzi_border_3", eRenderingMode::Transparent, L"Spirazzi_border_3", L"..\\Resources\\Texture\\Dungeon\\Spirazzi\\BackGround\\border_3.png");
		
		CreateMaterial(L"SpriteShader", L"Hysmar_back_far_0", eRenderingMode::Transparent, L"Hysmar_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\back_far_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_back_middle_0", eRenderingMode::Transparent, L"Hysmar_back_middle_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\back_middle_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_broken_briks_0", eRenderingMode::Transparent, L"Hysmar_broken_briks_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\broken_briks_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_crack_0", eRenderingMode::Transparent, L"Hysmar_crack_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\crack_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_tile1", eRenderingMode::Transparent, L"Hysmar_tile1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\Hysmar_tile1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_tile2", eRenderingMode::Transparent, L"Hysmar_tile2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\Hysmar_tile2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_middle_object_0", eRenderingMode::Transparent, L"Hysmar_middle_object_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\middle_object_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_middle_object_1", eRenderingMode::Transparent, L"Hysmar_middle_object_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\middle_object_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_middle_sub_object_0", eRenderingMode::Transparent, L"Hysmar_middle_sub_object_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\middle_sub_object_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_middle_sub_object_1", eRenderingMode::Transparent, L"Hysmar_middle_sub_object_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\middle_sub_object_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase1_back_far_0", eRenderingMode::Transparent, L"Hysmar_phase1_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase1_back_far_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase1_pillar_0", eRenderingMode::Transparent, L"Hysmar_phase1_pillar_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase1_pillar_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase1_pillar_1", eRenderingMode::Transparent, L"Hysmar_phase1_pillar_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase1_pillar_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase1_pillar_2", eRenderingMode::Transparent, L"Hysmar_phase1_pillar_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase1_pillar_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase1_roof_0", eRenderingMode::Transparent, L"Hysmar_phase1_roof_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase1_roof_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase1_roof_1", eRenderingMode::Transparent, L"Hysmar_phase1_roof_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase1_roof_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase1_sand_storm_0", eRenderingMode::Transparent, L"Hysmar_phase1_sand_storm_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase1_sand_storm_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_back_far", eRenderingMode::Transparent, L"Hysmar_phase2_back_far", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_back_far.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_back_far_0", eRenderingMode::Transparent, L"Hysmar_phase2_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_back_far_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_back_far_1", eRenderingMode::Transparent, L"Hysmar_phase2_back_far_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_back_far_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_back_far_2", eRenderingMode::Transparent, L"Hysmar_phase2_back_far_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_back_far_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_back_far_3", eRenderingMode::Transparent, L"Hysmar_phase2_back_far_3", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_back_far_3.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_border_0", eRenderingMode::Transparent, L"Hysmar_phase2_border_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_border_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_border_1", eRenderingMode::Transparent, L"Hysmar_phase2_border_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_border_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_fog_dodge_0", eRenderingMode::Transparent, L"Hysmar_phase2_fog_dodge_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_fog_dodge_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_fog_normal_0", eRenderingMode::Transparent, L"Hysmar_phase2_fog_normal_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_fog_normal_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_light_dodge_0", eRenderingMode::Transparent, L"Hysmar_phase2_light_dodge_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_light_dodge_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_light_dodge_1", eRenderingMode::Transparent, L"Hysmar_phase2_light_dodge_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_light_dodge_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_object_0", eRenderingMode::Transparent, L"Hysmar_phase2_object_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_object_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_object_1", eRenderingMode::Transparent, L"Hysmar_phase2_object_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_object_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_object_2", eRenderingMode::Transparent, L"Hysmar_phase2_object_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_object_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_object_3", eRenderingMode::Transparent, L"Hysmar_phase2_object_3", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_object_3.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_phase2_object_4", eRenderingMode::Transparent, L"Hysmar_phase2_object_4", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\phase2_object_4.png");
		

		CreateMaterial(L"SpriteShader", L"Hysmar_common_back_far_0", eRenderingMode::Transparent, L"Hysmar_common_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_back_far_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_back_middle_0", eRenderingMode::Transparent, L"Hysmar_common_back_middle_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_back_middle_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_boss_ex_0", eRenderingMode::Transparent, L"Hysmar_common_boss_ex_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_boss_ex_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_boss_ex_1", eRenderingMode::Transparent, L"Hysmar_common_boss_ex_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_boss_ex_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_boss_ex_2", eRenderingMode::Transparent, L"Hysmar_common_boss_ex_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_boss_ex_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_boss_ex_3", eRenderingMode::Transparent, L"Hysmar_common_boss_ex_3", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_boss_ex_3.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_boss_ex_4", eRenderingMode::Transparent, L"Hysmar_common_boss_ex_4", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_boss_ex_4.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_boss_ex_5", eRenderingMode::Transparent, L"Hysmar_common_boss_ex_5", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_boss_ex_5.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_00", eRenderingMode::Transparent, L"Hysmar_common_object_00", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_00.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_01", eRenderingMode::Transparent, L"Hysmar_common_object_01", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_01.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_02", eRenderingMode::Transparent, L"Hysmar_common_object_02", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_02.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_03", eRenderingMode::Transparent, L"Hysmar_common_object_03", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_03.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_04", eRenderingMode::Transparent, L"Hysmar_common_object_04", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_04.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_05", eRenderingMode::Transparent, L"Hysmar_common_object_05", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_05.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_06", eRenderingMode::Transparent, L"Hysmar_common_object_06", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_06.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_07", eRenderingMode::Transparent, L"Hysmar_common_object_07", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_07.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_08", eRenderingMode::Transparent, L"Hysmar_common_object_08", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_08.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_09", eRenderingMode::Transparent, L"Hysmar_common_object_09", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_09.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_10", eRenderingMode::Transparent, L"Hysmar_common_object_10", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_10.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_11", eRenderingMode::Transparent, L"Hysmar_common_object_11", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_11.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_12", eRenderingMode::Transparent, L"Hysmar_common_object_12", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_12.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_13", eRenderingMode::Transparent, L"Hysmar_common_object_13", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_13.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_14", eRenderingMode::Transparent, L"Hysmar_common_object_14", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_14.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_15", eRenderingMode::Transparent, L"Hysmar_common_object_15", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_15.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_16", eRenderingMode::Transparent, L"Hysmar_common_object_16", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_16.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_17", eRenderingMode::Transparent, L"Hysmar_common_object_17", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_17.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_18", eRenderingMode::Transparent, L"Hysmar_common_object_18", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_18.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_border_0", eRenderingMode::Transparent, L"Hysmar_common_object_border_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_border_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_border_1", eRenderingMode::Transparent, L"Hysmar_common_object_border_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_border_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_border_2", eRenderingMode::Transparent, L"Hysmar_common_object_border_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_border_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_crack_0", eRenderingMode::Transparent, L"Hysmar_common_object_crack_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_crack_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_crack_1", eRenderingMode::Transparent, L"Hysmar_common_object_crack_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_crack_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_crack_2", eRenderingMode::Transparent, L"Hysmar_common_object_crack_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_crack_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_0", eRenderingMode::Transparent, L"Hysmar_common_object_wall_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_1", eRenderingMode::Transparent, L"Hysmar_common_object_wall_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_2", eRenderingMode::Transparent, L"Hysmar_common_object_wall_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_3", eRenderingMode::Transparent, L"Hysmar_common_object_wall_3", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_3.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_4", eRenderingMode::Transparent, L"Hysmar_common_object_wall_4", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_4.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_5", eRenderingMode::Transparent, L"Hysmar_common_object_wall_5", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_5.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_6", eRenderingMode::Transparent, L"Hysmar_common_object_wall_6", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_6.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_object_wall_7", eRenderingMode::Transparent, L"Hysmar_common_object_wall_7", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_object_wall_7.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile", eRenderingMode::Transparent, L"Hysmar_common_tile", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_0", eRenderingMode::Transparent, L"Hysmar_common_tile_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_1", eRenderingMode::Transparent, L"Hysmar_common_tile_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_ex_0", eRenderingMode::Transparent, L"Hysmar_common_tile_ex_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_ex_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_ex_1", eRenderingMode::Transparent, L"Hysmar_common_tile_ex_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_ex_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_0", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_1", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_2", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_3", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_3", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_3.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_4", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_4", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_4.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_5", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_5", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_5.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_ex_0", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_ex_0", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_ex_0.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_ex_1", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_ex_1", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_ex_1.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_ex_2", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_ex_2", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_ex_2.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_ex_3", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_ex_3", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_ex_3.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_ex_4", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_ex_4", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_ex_4.png");
		CreateMaterial(L"SpriteShader", L"Hysmar_common_tile_boss_ex_5", eRenderingMode::Transparent, L"Hysmar_common_tile_boss_ex_5", L"..\\Resources\\Texture\\Dungeon\\Hysmar\\BackGround\\common_tile_boss_ex_5.png");



		CreateMaterial(L"SpriteShader", L"MainCamp_back_far_0", eRenderingMode::Transparent, L"MainCamp_back_far_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\back_far_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_back_middle_0", eRenderingMode::Transparent, L"MainCamp_back_middle_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\back_middle_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_back_middle_1", eRenderingMode::Transparent, L"MainCamp_back_middle_1", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\back_middle_1.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_border_0", eRenderingMode::Transparent, L"MainCamp_border_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\border_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_door_0", eRenderingMode::Transparent, L"MainCamp_object_door_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_door_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_door_1", eRenderingMode::Transparent, L"MainCamp_object_door_1", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_door_1.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_door_2", eRenderingMode::Transparent, L"MainCamp_object_door_2", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_door_2.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_dodge_fire_0", eRenderingMode::Transparent, L"MainCamp_dodge_fire_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\dodge_fire_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_dodge_light_0", eRenderingMode::Transparent, L"MainCamp_dodge_light_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\dodge_light_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_geonhwamungate_sign_0", eRenderingMode::Transparent, L"MainCamp_geonhwamungate_sign_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\geonhwamungate_sign_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_0", eRenderingMode::Transparent, L"MainCamp_object_main_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_1", eRenderingMode::Transparent, L"MainCamp_object_main_1", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_1.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_2", eRenderingMode::Transparent, L"MainCamp_object_main_2", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_2.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_3", eRenderingMode::Transparent, L"MainCamp_object_main_3", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_3.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_4", eRenderingMode::Transparent, L"MainCamp_object_main_4", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_4.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_5", eRenderingMode::Transparent, L"MainCamp_object_main_5", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_5.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_6", eRenderingMode::Transparent, L"MainCamp_object_main_6", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_6.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_7", eRenderingMode::Transparent, L"MainCamp_object_main_7", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_7.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_8", eRenderingMode::Transparent, L"MainCamp_object_main_8", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_8.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_9", eRenderingMode::Transparent, L"MainCamp_object_main_9", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_9.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_10", eRenderingMode::Transparent, L"MainCamp_object_main_10", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_10.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_11", eRenderingMode::Transparent, L"MainCamp_object_main_11", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_11.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_12", eRenderingMode::Transparent, L"MainCamp_object_main_12", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_12.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_13", eRenderingMode::Transparent, L"MainCamp_object_main_13", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_13.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_14", eRenderingMode::Transparent, L"MainCamp_object_main_14", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_14.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_15", eRenderingMode::Transparent, L"MainCamp_object_main_15", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_15.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_16", eRenderingMode::Transparent, L"MainCamp_object_main_16", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_16.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_main_17", eRenderingMode::Transparent, L"MainCamp_object_main_17", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_main_17.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_title_0", eRenderingMode::Transparent, L"MainCamp_object_title_0", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_title_0.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_object_title_1", eRenderingMode::Transparent, L"MainCamp_object_title_1", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\object_title_1.png");
		CreateMaterial(L"SpriteShader", L"MainCamp_tile", eRenderingMode::Transparent, L"MainCamp_tile", L"..\\Resources\\Texture\\Town\\MainCamp\\BackGround\\tile.png");



		CreateMaterial(L"SpriteShader", L"GunHwaMun_back_far_0", eRenderingMode::Transparent, L"GunHwaMun_back_far_0", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\back_far_0.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_back_middle_0", eRenderingMode::Transparent, L"GunHwaMun_back_middle_0", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\back_middle_0.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_back_middle_1", eRenderingMode::Transparent, L"GunHwaMun_back_middle_1", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\back_middle_1.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_back_middle_2", eRenderingMode::Transparent, L"GunHwaMun_back_middle_2", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\back_middle_2.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_border_0", eRenderingMode::Transparent, L"GunHwaMun_border_0", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\border_0.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_border_1", eRenderingMode::Transparent, L"GunHwaMun_border_1", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\border_1.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_border_2", eRenderingMode::Transparent, L"GunHwaMun_border_2", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\border_2.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_border_3", eRenderingMode::Transparent, L"GunHwaMun_border_3", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\border_3.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_door_0", eRenderingMode::Transparent, L"GunHwaMun_door_0", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\door_0.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_door_1", eRenderingMode::Transparent, L"GunHwaMun_door_1", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\door_1.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_object_0", eRenderingMode::Transparent, L"GunHwaMun_object_0", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\object_0.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_object_1", eRenderingMode::Transparent, L"GunHwaMun_object_1", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\object_1.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_object_title_0", eRenderingMode::Transparent, L"GunHwaMun_object_title_0", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\object_title_0.png");
		CreateMaterial(L"SpriteShader", L"GunHwaMun_tile", eRenderingMode::Transparent, L"GunHwaMun_tile", L"..\\Resources\\Texture\\Town\\GunHwaMun\\BackGround\\tile.png");

		CreateMaterial(L"SpriteShader", L"SeriaRoom_background_0", eRenderingMode::Transparent, L"SeriaRoom_background_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\background_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_seria_add_0",  eRenderingMode::Transparent, L"SeriaRoom_seria_add_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\seria_add_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_background_eff_0", eRenderingMode::Transparent, L"SeriaRoom_background_eff_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\background_eff_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_border_tree_0", eRenderingMode::Transparent, L"SeriaRoom_border_tree_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\border_tree_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_border_tree_1",  eRenderingMode::Transparent, L"SeriaRoom_border_tree_1", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\border_tree_1.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_gate_0", eRenderingMode::Transparent, L"SeriaRoom_gate_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_gate_eff_0", eRenderingMode::Transparent, L"SeriaRoom_gate_eff_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_eff_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_gate_new_0", eRenderingMode::Transparent, L"SeriaRoom_gate_new_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\gate_new_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_left_door_0",  eRenderingMode::Transparent, L"SeriaRoom_left_door_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\left_door_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_right_door_0", eRenderingMode::Transparent, L"SeriaRoom_right_door_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\right_door_0.png");
		CreateMaterial(L"SpriteShader", L"SeriaRoom_backgruond_light_reflect_0", eRenderingMode::Transparent, L"SeriaRoom_backgruond_light_reflect_0", L"..\\Resources\\Texture\\Town\\SeriaRoom\\BackGround\\backgruond_light_reflect_0.png");
		
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_back_middle_0", eRenderingMode::Transparent, L"Dungeon_Entrance_back_middle_0", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\back_middle_0.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_back_middle_1", eRenderingMode::Transparent, L"Dungeon_Entrance_back_middle_1", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\back_middle_1.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_back_middle_2", eRenderingMode::Transparent, L"Dungeon_Entrance_back_middle_2", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\back_middle_2.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_common_tile_0", eRenderingMode::Transparent, L"Dungeon_Entrance_common_tile_0", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\common_tile_0.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_common_tile_1", eRenderingMode::Transparent, L"Dungeon_Entrance_common_tile_1", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\common_tile_1.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_0", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_0", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_0.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_1", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_1", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_1.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_2", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_2", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_2.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_3", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_3", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_3.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_4", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_4", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_4.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_6", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_6", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_6.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_7", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_7", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_7.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_basic_8", eRenderingMode::Transparent, L"Dungeon_Entrance_object_basic_8", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_basic_8.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_wall_0", eRenderingMode::Transparent, L"Dungeon_Entrance_object_wall_0", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_wall_0.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_wall_1", eRenderingMode::Transparent, L"Dungeon_Entrance_object_wall_1", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_wall_1.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_wall_2", eRenderingMode::Transparent, L"Dungeon_Entrance_object_wall_2", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_wall_2.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_wall_3", eRenderingMode::Transparent, L"Dungeon_Entrance_object_wall_3", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_wall_3.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_wall_4", eRenderingMode::Transparent, L"Dungeon_Entrance_object_wall_4", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_wall_4.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_wall_5", eRenderingMode::Transparent, L"Dungeon_Entrance_object_wall_5", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_wall_5.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_border_0", eRenderingMode::Transparent, L"Dungeon_Entrance_object_border_0", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_border_0.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_border_1", eRenderingMode::Transparent, L"Dungeon_Entrance_object_border_1", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_border_1.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_border_2", eRenderingMode::Transparent, L"Dungeon_Entrance_object_border_2", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_border_2.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_border_3", eRenderingMode::Transparent, L"Dungeon_Entrance_object_border_3", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_border_3.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_border_4", eRenderingMode::Transparent, L"Dungeon_Entrance_object_border_4", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_border_4.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_00", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_00", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_00.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_01", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_01", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_01.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_02", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_02", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_02.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_03", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_03", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_03.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_04", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_04", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_04.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_05", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_05", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_05.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_06", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_06", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_06.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_07", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_07", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_07.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_08", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_08", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_08.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_09", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_09", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_09.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_10", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_10", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_10.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_11", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_11", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_11.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_12", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_12", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_12.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_13", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_13", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_13.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_14", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_14", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_14.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_15", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_15", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_15.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_bottom_16", eRenderingMode::Transparent, L"Dungeon_Entrance_object_bottom_16", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_bottom_16.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_building_0", eRenderingMode::Transparent, L"Dungeon_Entrance_object_building_0", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_building_0.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_building_1", eRenderingMode::Transparent, L"Dungeon_Entrance_object_building_1", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_building_1.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_tree_0", eRenderingMode::Transparent, L"Dungeon_Entrance_object_tree_0", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_tree_0.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_tree_1", eRenderingMode::Transparent, L"Dungeon_Entrance_object_tree_1", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_tree_1.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_tree_2", eRenderingMode::Transparent, L"Dungeon_Entrance_object_tree_2", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_tree_2.png");
		CreateMaterial(L"SpriteShader", L"Dungeon_Entrance_object_tree_3", eRenderingMode::Transparent, L"Dungeon_Entrance_object_tree_3", L"..\\Resources\\Texture\\Dungeon\\Common\\BackGround\\object_tree_3.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\gunhwamun_object_computer_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_back_far_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_back_middle_fire_dodge_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_border_wall_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_border_wall_1.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_border_wall_2.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_1.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_2.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_3.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_4.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_5.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_6.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_object_7.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\north_tile.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_back_far_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_border_wall_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_border_wall_1.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_border_wall_2.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_0.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_1.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_2.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_3.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_4.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_5.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_6.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_object_7.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\south_tile.png");
		//CreateMaterial(L"SpriteShader", L"H", eRenderingMode::Transparent, L"H", L"..\\Resources\\Texture\\Town\\GeonHwaMun\\p.png");
		
		CreateMaterial(L"SpriteShader", L"DrakeSpear", eRenderingMode::Transparent, L"DrakeSpear", L"..\\Resources\\Texture\\Monster\\normal\\drake_soldier\\drake_spear.png");
	}
	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadMaterial();
		//Resources::test();
		/*Resources::Find<Material>(L"object_mist_1");
		std::shared_ptr<Material> a = Resources::Find<Material>(L"object_mist_1");*/

	}

	void PushDebugMeshAttribute(DebugMesh* mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);
	}

	void BindNoiseTexture()
	{
	/*	std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(L"Noise01");*/

		/*texture->BindShaderResource(eShaderStage::VS, 15);
		texture->BindShaderResource(eShaderStage::HS, 15);
		texture->BindShaderResource(eShaderStage::DS, 15);
		texture->BindShaderResource(eShaderStage::GS, 15);
		texture->BindShaderResource(eShaderStage::PS, 15);
		texture->BindShaderResource(eShaderStage::CS, 15);*/

		/*ConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->GetWidth();
		data.size.y = texture->GetHeight();*/
		

		/*cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);*/
	}

	void Render()
	{
		mainCamera = cameras[0];
		BindNoiseTexture();
		BindLights();


		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
}