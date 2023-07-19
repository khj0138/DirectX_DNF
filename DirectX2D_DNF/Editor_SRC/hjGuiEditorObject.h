#pragma once
#include "..\\Engine_SRC\\hjGameObject.h"

namespace gui
{
	class EditorObject : public hj::GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

