#pragma once
#include "hjEntity.h"

namespace hj
{
	using namespace hj::enums;

	class Component : public Entity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		const eComponentType mType;
	};
}
