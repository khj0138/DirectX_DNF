#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_Spirazzi : public PlayScene
	{
	public:
		Dungeon_Spirazzi();
		virtual ~Dungeon_Spirazzi();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
