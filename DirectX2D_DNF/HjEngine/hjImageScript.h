#pragma once
#include "..\\Engine_SRC\\hjScript.h"
#include "..\\Engine_SRC\\hjCamera.h"

namespace hj
{
	class ImageScript : public Script
	{
	public:
		ImageScript();
		~ImageScript();


		virtual void LateUpdate() override;
		virtual void Render() override;

		void setScale(Vector2 scale) { mScale = scale; }

	private:
		Vector2 mScale;
	};
}