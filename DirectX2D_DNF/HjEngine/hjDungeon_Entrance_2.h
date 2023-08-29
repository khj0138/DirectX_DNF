#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Entrance_2 : public PlayScene
	{
	public:
		Dungeon_Entrance_2();
		virtual ~Dungeon_Entrance_2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
	};
}
