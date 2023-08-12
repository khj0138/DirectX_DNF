#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Entrance_1 : public PlayScene
	{
	public:
		Dungeon_Entrance_1();
		virtual ~Dungeon_Entrance_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		GameObject* test;
	};
}
