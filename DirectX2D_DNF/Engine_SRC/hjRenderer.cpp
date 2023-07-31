#include "hjRenderer.h"
#include "hjResources.h"
#include "hjTexture.h"
#include "hjMaterial.h"


namespace renderer
{
	using namespace hj;
	using namespace hj::graphics;
	hj::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	hj::Camera* mainCamera = nullptr;
	std::vector<hj::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input layout ���� ���� ����
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

		shader = hj::Resources::Find<Shader>(L"DebugShader");
		hj::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = hj::Resources::Find<Shader>(L"SpriteAnimShader");
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

		//vertexes.resize(4);
		//vertexes[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		//vertexes[0].uv = Vector2(0.0f, 0.0f);

		//vertexes[1].pos = Vector3(1.0f, 1.0f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		//vertexes[1].uv = Vector2(1.0f, 0.0f);

		//vertexes[2].pos = Vector3(1.0f, -1.0f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		//vertexes[2].uv = Vector2(1.0f, 1.0f);

		//vertexes[3].pos = Vector3(-1.0f, -1.0f, 0.0f);
		//vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertexes[3].uv = Vector2(0.0f, 1.0f);
		// Create Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		// Data Vector for Index Buffer 

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

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
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
	}
	
	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));

		// Animation Buffer
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		// Etc Buffer
		constantBuffer[(UINT)eCBType::Etc] = new ConstantBuffer(eCBType::Etc);
		constantBuffer[(UINT)eCBType::Etc]->Create(sizeof(EtcCB));

		// Time Buffer
		constantBuffer[(UINT)eCBType::Time] = new ConstantBuffer(eCBType::Time);
		constantBuffer[(UINT)eCBType::Time]->Create(sizeof(TimeCB));
	}

	void CreateShader(const std::wstring vsName, const std::wstring psName, const std::wstring sName
		, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		, eRSType rsType = eRSType::SolidBack
		, eDSType dsType = eDSType::Less
		, eBSType bsType = eBSType::AlphaBlend
		, const std::string funcName = "main")
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, vsName, funcName);
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
		CreateShader(L"DebugVS.hlsl", L"DebugPS.hlsl", L"DebugShader"
		, D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, eRSType::WireframeNone, eDSType::NoWrite);
		
	}

	void CreateMaterial(const std::wstring sName, const std::wstring mName, eRenderingMode rMode, const std::wstring tName = L"", const std::wstring tPath = L"")
	{
		std::shared_ptr<Material> material = std::make_shared<Material>();
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(sName);
		if(tPath != L"")
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

	void LoadMaterial()
	{
		CreateMaterial(L"SpriteShader", L"SpriteMaterial", eRenderingMode::Transparent, L"SpriteMaterial", L"..\\Resources\\Texture\\SwordManAttack3.png");
		CreateMaterial(L"SpriteShader", L"SpriteMaterial02", eRenderingMode::Transparent, L"SpriteMaterial02", L"..\\Resources\\Texture\\SwordManAttack.png");
		
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

		//CreateMaterial(L"MoveShader", L"Skasa_object_mist_0", eRenderingMode::Transparent, L"Skasa_object_mist_0", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_mist_0.png");
		//CreateMaterial(L"MoveShader", L"Skasa_object_mist_1", eRenderingMode::Transparent, L"Skasa_object_mist_1", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\object_mist_1.png");
		

		CreateMaterial(L"SpriteShader", L"Sparazzi_back_far_0", eRenderingMode::Transparent, L"Sparazzi_back_far_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\Back_far_0.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_far_1", eRenderingMode::Transparent, L"Sparazzi_back_far_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_far_1.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_far_2", eRenderingMode::Transparent, L"Sparazzi_back_far_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_far_2.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_0", eRenderingMode::Transparent, L"Sparazzi_back_middle_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_0.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_1", eRenderingMode::Transparent, L"Sparazzi_back_middle_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_1.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_2", eRenderingMode::Transparent, L"Sparazzi_back_middle_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_2.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_3", eRenderingMode::Transparent, L"Sparazzi_back_middle_3", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_3.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_4", eRenderingMode::Transparent, L"Sparazzi_back_middle_4", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_4.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_5", eRenderingMode::Transparent, L"Sparazzi_back_middle_5", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_5.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_6", eRenderingMode::Transparent, L"Sparazzi_back_middle_6", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_6.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_back_middle_7", eRenderingMode::Transparent, L"Sparazzi_back_middle_7", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\back_middle_7.png");

		CreateMaterial(L"SpriteShader", L"Sparazzi_tile1", eRenderingMode::Transparent, L"Sparazzi_tile1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\Sparazzi_tile1.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_tile", eRenderingMode::Transparent, L"Skasa_tile", L"..\\Resources\\Texture\\Dungeon\\Skasa\\BackGround\\Skasa_tile.png");
		//CreateMaterial(L"SpriteShader", L"Skasa_tile1", eRenderingMode::Transparent, L"Skasa_tile1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\Skasa_tile1.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_0", eRenderingMode::Transparent, L"Sparazzi_fog_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_0.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_1", eRenderingMode::Transparent, L"Sparazzi_fog_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_1.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_2", eRenderingMode::Transparent, L"Sparazzi_fog_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_2.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_3", eRenderingMode::Transparent, L"Sparazzi_fog_3", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_3.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_4", eRenderingMode::Transparent, L"Sparazzi_fog_4", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_4.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_normal_0", eRenderingMode::Transparent, L"Sparazzi_fog_normal_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_normal_0.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_normal_1", eRenderingMode::Transparent, L"Sparazzi_fog_normal_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_normal_1.png");
		CreateMaterial(L"MoveShader", L"Sparazzi_fog_normal_2", eRenderingMode::Transparent, L"Sparazzi_fog_normal_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\fog_normal_2.png");

		CreateMaterial(L"SpriteShader", L"Sparazzi_object_0", eRenderingMode::Transparent, L"Sparazzi_object_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_0.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_object_1", eRenderingMode::Transparent, L"Sparazzi_object_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_1.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_object_2", eRenderingMode::Transparent, L"Sparazzi_object_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_2.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_object_3", eRenderingMode::Transparent, L"Sparazzi_object_3", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_3.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_object_4", eRenderingMode::Transparent, L"Sparazzi_object_4", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_4.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_object_5", eRenderingMode::Transparent, L"Sparazzi_object_5", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_5.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_object_6", eRenderingMode::Transparent, L"Sparazzi_object_6", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_6.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_object_7", eRenderingMode::Transparent, L"Sparazzi_object_7", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\object_7.png");

		CreateMaterial(L"SpriteShader", L"Sparazzi_nest_0", eRenderingMode::Transparent, L"Sparazzi_nest_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\nest_0.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_nest_1", eRenderingMode::Transparent, L"Sparazzi_nest_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\nest_1.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_nest_2", eRenderingMode::Transparent, L"Sparazzi_nest_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\nest_2.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_nest_3", eRenderingMode::Transparent, L"Sparazzi_nest_3", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\nest_3.png");

		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_0", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_0.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_1", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_1.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_2", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_2.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_3", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_3", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_3.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_4", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_4", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_4.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_5", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_5", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_5.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_6", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_6", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_6.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_bottom_obj_7", eRenderingMode::Transparent, L"Sparazzi_bottom_obj_7", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\bottom_obj_7.png");
		
		CreateMaterial(L"SpriteShader", L"Sparazzi_border_0", eRenderingMode::Transparent, L"Sparazzi_border_0", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\border_0.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_border_1", eRenderingMode::Transparent, L"Sparazzi_border_1", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\border_1.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_border_2", eRenderingMode::Transparent, L"Sparazzi_border_2", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\border_2.png");
		CreateMaterial(L"SpriteShader", L"Sparazzi_border_3", eRenderingMode::Transparent, L"Sparazzi_border_3", L"..\\Resources\\Texture\\Dungeon\\Sparazzi\\BackGround\\border_3.png");
		
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
		
		CreateMaterial(L"SpriteAnimShader", L"SpriteAnimationMaterial", eRenderingMode::Transparent);


		CreateMaterial(L"GridShader", L"GridMaterial", eRenderingMode::Transparent);
		CreateMaterial(L"DebugShader", L"DebugMaterial", eRenderingMode::Transparent);
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

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void Render()
	{
		mainCamera = cameras[0];

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
	}
}