#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Hysmar_Entrance : public PlayScene
	{
	public:
		Dungeon_Hysmar_Entrance();
		virtual ~Dungeon_Hysmar_Entrance();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
