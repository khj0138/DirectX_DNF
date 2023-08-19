#pragma once
#include "hjComponent.h"
#include "hjMesh.h"
#include "hjMaterial.h"

namespace hj
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }

		void SetUVScale(Vector2 scale) { mScale = scale; }
		void SetUVMove(Vector2 scale) { mMove = scale; }
		void SetUVFlip(bool flip) { mFlip = flip; }
		void SetUVRepeat(bool repeat) { mRepeat = repeat; }
		void BindUVBuffer();

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
		Vector2 mScale;
		Vector2 mMove;
		Vector2 mTime;
		bool mFlip;
		bool mRepeat;
	};
}
