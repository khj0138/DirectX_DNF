#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Town_MainCamp : public PlayScene
	{
	public:
		Town_MainCamp();
		virtual ~Town_MainCamp();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
	};
}
