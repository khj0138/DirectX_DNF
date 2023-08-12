#pragma once
#include "..\\Engine_SRC\\CommonInclude.h"
#include "..\\Engine_SRC\\hjEngine.h"
#include "..\\Engine_SRC\\hjGraphics.h"

#include "hjGuiWidget.h"
#include "hjGuiEditorObject.h"
#include "hjGuiDebugObject.h"

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const hj::graphics::DebugMesh* mesh);
	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugObjects;
	};
}


