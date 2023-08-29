#pragma once
#include "hjPlayScene.h"


namespace hj
{
	class Town_GunHwaMun : public PlayScene
	{
	public:
		Town_GunHwaMun();
		virtual ~Town_GunHwaMun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
	};
}
