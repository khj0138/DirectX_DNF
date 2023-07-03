#pragma once
#include "hjEntity.h"
#include "hjComponent.h"

namespace hj
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();

			Component* component
				= dynamic_cast<Component*>(comp);

			if (component == nullptr)
				return nullptr;

			mComponents.push_back(component);
			comp->SetOwner(this);

			return comp;
		}

	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}
