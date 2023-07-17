#include "hjMaterial.h"


namespace hj::graphics
{
	Material::Material()
		: Resource(hj::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mMode(eRenderingMode::Opaque)
	{

	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::Binds()
	{
		if (mTexture)
			mTexture->BindShader(eShaderStage::PS, 0);

		if (mShader)
			mShader->Binds();
	}
	void Material::Clear()
	{
		mTexture->Clear();
	}
	void Material::SetRenderingMode(eRenderingMode mode)
	{
		mMode = mode;
		switch (mode)
		{
		case eRenderingMode::Opaque:
		{
			mShader->SetDSState(eDSType::Less);
			break;
		}
		case eRenderingMode::Transparent:
		{
			mShader->SetDSState(eDSType::None);
			break;
		}
		}
	}
}
