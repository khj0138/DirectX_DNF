#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Town_SeriaRoom : public PlayScene
	{
	public:
		Town_SeriaRoom();
		virtual ~Town_SeriaRoom();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
	};
}
