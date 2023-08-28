#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Spirazzi_Entrance : public PlayScene
	{
	public:
		Dungeon_Spirazzi_Entrance();
		virtual ~Dungeon_Spirazzi_Entrance();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
