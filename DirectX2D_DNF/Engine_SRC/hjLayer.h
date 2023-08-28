#pragma once
#include "hjGameObject.h"

namespace hj
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		void AddGameObject(GameObject* gameObj);
		void EraseGameObject(GameObject* gameObj);
		GameObject* FindObject(std::wstring name)
		{
			GameObject* object;
			for (int i = 0; i < mGameObjects.size(); i++)
			{
				if (mGameObjects[i]->GetName() == name)
				{
					object = mGameObjects[i];
					return object;
				}
			}
			return nullptr;
		}
		const std::vector<GameObject*> GetGameObjects()
		{
			return mGameObjects;
		}

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
