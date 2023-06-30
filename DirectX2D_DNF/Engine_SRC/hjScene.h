#pragma once
#include "hjEntity.h"
#include "hjGameObject.h"

namespace hj
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
