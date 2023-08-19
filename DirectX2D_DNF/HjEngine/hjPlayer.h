#pragma once
#include "hjGameObject.h"

namespace hj
{
	class AttackScriptManager;
	class Animator;
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		//virtual void OnCollisionEnter(Collider2D* other);
		//virtual void OnCollisionStay(Collider2D* other);
		//virtual void OnCollisionExit(Collider2D* other);

		void EnterScene();
		
		void ExitScene();
		
		AttackScriptManager* GetAtkManager() { return AtkManager; }
	private:
		bool mActivate;
		bool bAttack;
		AttackScriptManager* AtkManager;
	};
}