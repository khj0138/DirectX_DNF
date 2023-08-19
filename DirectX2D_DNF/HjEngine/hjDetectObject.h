#pragma once
#include "hjAttackObject.h"

namespace hj
{
	class Player;
	class DetectObject : public AttackObject
	{
	public:
		DetectObject();
		~DetectObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

		Player* GetTarget() { return mPlayer; }

	private:
		bool mActivate;
		Player* mPlayer;
	};
}