#pragma once
#include "hjResource.h"
#include "hjTexture.h"

namespace hj
{
	using namespace math;
	using namespace graphics;

	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Update();
		void LateUpdate();
		void Render();

		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);

		void Binds();
		void Reset();
		void SetFlip(bool flip) { isFlip = flip; }

		bool IsComplete() { return mbComplete; }

	private:
		std::shared_ptr<graphics::Texture> mAtlas;
		Animator* mAnimator;
		std::vector<Sprite> mSprites;
		int mIndex;
		float mTime;
		bool mbComplete;
		bool isFlip;
	};
}
