#pragma once
#include "hjComponent.h"
#include "hjGraphics.h"

namespace hj
{
	class Transform;
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perpective,
			OrthoGraphic,
			None,
		};

		static Matrix& GetGPUViewMatrix() { return View; }
		static void SetGPUViewMatrix(Matrix view) { View = view; }
		static Matrix& GetGPUProjectionMatrix() { return Projection; }
		static void SetGPUProjectionMatrix(Matrix projection) { Projection = projection; }

		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);
		void RegisterCameraInRenderer();


		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { mLayerMask.set(); }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void AlphaSortGameObjects();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs);
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisableDepthStencilState();

		void RegisterTarget(GameObject* target);
		void SetTarget(const std::wstring& name);
		bool CheckTarget(Vector3& pos, float& virtualZ);

		float GetSize() { return mSize; }
		Matrix& GetViewMatrix() { return mView; }
		Matrix& GetProjectionMatrix() { return mProjection; }


		Vector2 getMinXY() { return minXY; }
		void setMinXY(Vector2 xy) { minXY = xy * fixedRes; }
		Vector2 getMaxXY() { return maxXY; }
		void setMaxXY(Vector2 xy) { maxXY = xy * fixedRes; }

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;
		bool bTarget;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;

		std::vector<GameObject*> mTargets;
		GameObject* mActiveTarget;

		Vector2 minXY;
		Vector2 maxXY;

		float fixedRes;
	};
}
