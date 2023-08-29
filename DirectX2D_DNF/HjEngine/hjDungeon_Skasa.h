#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Skasa : public PlayScene
	{
	public:
		Dungeon_Skasa();
		virtual ~Dungeon_Skasa();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
	};
}
