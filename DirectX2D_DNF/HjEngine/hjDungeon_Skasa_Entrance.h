#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Skasa_Entrance : public PlayScene
	{
	public:
		Dungeon_Skasa_Entrance();
		virtual ~Dungeon_Skasa_Entrance();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
