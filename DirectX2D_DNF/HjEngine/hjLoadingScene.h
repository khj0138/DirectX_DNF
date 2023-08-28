#pragma once
#include "..\\Engine_SRC\\hjScene.h"


namespace hj
{
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		virtual ~LoadingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
