#pragma once
//#include "hjScript.h"
#include <hjScript.h>

namespace hj
{
	class BehaviorTree;
	class Animator;
	class Collider2D;
	class AttackScriptManager;
	class Player;
	class PlayerScript : public Script
	{
	public:
		enum class ePlayerState
		{
			Idle,
			Walk,
			Run,
			Attack,
			Jump,
			End,
		};

		enum class eAttackType
		{
			Attack1,
			Attack2,
			Attack3,
			End,
		};
		PlayerScript();
		~PlayerScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();
		float getMoveTime() { return moveTime; }
		BehaviorTree* GetBT() { return mBehaviors; }

		//behavior
		bool IsWalk();
		bool IsRun();
		bool IsJump();

	public:
		void Idle();
		void Walk();
		void Run();
		void Jump();
		void Attack();
		void Anim();

		void JumpUpStartEvent();
		void JumpUpCompleteEvent();
		void Attack1StartEvent();
		void Attack2StartEvent();
		void Attack3StartEvent();
		void Attack1CompleteEvent();
		void Attack2CompleteEvent();
		void Attack3CompleteEvent();

		void EnterScene();
		void ExitScene();
	private:
		ePlayerState mPlayerState;
		ePlayerState mPrevPlayerState;

		std::vector<UINT> moveVector;
		float moveTime;
		bool bMove;
		Vector3 mVelocity;

		std::vector<UINT> commandVector;
		float commandTime;
		bool bCommand;

		std::vector<bool> bAttackVector;
		std::vector<std::wstring> mAttackVector;

		Animator* mAnimator;
		Collider2D* mCollider;
		bool isFlip;
		BehaviorTree* mBehaviors;

		bool bRun;
		bool jumpDown;

		Player* mOwner;
		AttackScriptManager* AtkManager;
	};


}
