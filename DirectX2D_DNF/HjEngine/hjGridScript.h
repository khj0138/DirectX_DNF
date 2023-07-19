#pragma once
#include "..\\Engine_SRC\\hjScript.h"
#include "..\\Engine_SRC\\hjCamera.h"

namespace hj
{
	class GridScript : public Script
	{
	public:
		GridScript();
		~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { mCamera = camera; }

	private:
		Camera* mCamera;
	};
}