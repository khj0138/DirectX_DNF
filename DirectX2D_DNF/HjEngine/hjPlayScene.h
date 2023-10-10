#pragma once
#include "..\\Engine_SRC\\hjScene.h"


namespace hj
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMinMax(Vector2 rangeMin, Vector2 rangeMax) {
			minMax.clear();
			minMax.push_back(rangeMin);
			minMax.push_back(rangeMax);
		}

	private:
		GameObject* test;
		std::vector<Vector2> minMax;
	};
}
