#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Dungeon_skasa : public PlayScene
	{
	public:
		Dungeon_skasa();
		virtual ~Dungeon_skasa();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		GameObject* test;
	};
}
