#pragma once
#include "hjResource.h"
#include "hjShader.h"
#include "hjTexture.h"

namespace hj::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		void SetRenderingMode(eRenderingMode mode);
		math::Vector3 GetTextureSize() { return math::Vector3((float)(mTexture->GetWidth()), (float)(mTexture->GetHeight()), 1.0f); }
		eRenderingMode GetRenderingMode() { return mMode; }

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;

		eRenderingMode mMode;
	};
}
