#pragma once
#include "..\\Engine_SRC\\hjGameObject.h"

namespace gui
{
	class DebugObject : public hj::GameObject
	{
	public:
		DebugObject();
		~DebugObject();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
	};
}

