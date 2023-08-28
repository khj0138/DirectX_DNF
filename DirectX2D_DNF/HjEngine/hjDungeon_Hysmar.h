#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Hysmar : public PlayScene
	{
	public:
		Dungeon_Hysmar();
		virtual ~Dungeon_Hysmar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
