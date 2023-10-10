#pragma once
//#include "hjScript.h"
#include <hjScript.h>

namespace hj
{
	//class BehaviorTree;
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
			Sit,
			Hit,
			Die,
			End,
		};

		enum class eAttackType
		{
			Attack1,
			Attack2,
			Attack3,
			End,
		};

		enum class eCommandType
		{
			Z,
			X,
			C,
			S,
			D,
			F,
			UP,
			LEFT,
			DOWN,
			RIGHT,
			End,
		};

		enum class eMoveType
		{
			axisX,
			axisY,
			End,
		};

		struct Command
		{
			eCommandType type;
			float time;
		};

		struct status
		{
			UINT maxHP;
			UINT HP;
			bool SuperArmor;
			bool Hit;
		};

		PlayerScript();
		~PlayerScript();

		void SetStatus(UINT maxHP, UINT HP, bool armor, bool hit) { mStatus.maxHP = maxHP; mStatus.HP = HP; mStatus.SuperArmor = armor; mStatus.Hit = hit;}
		bool CheckHit() { return mStatus.Hit; }
		status GetStatus() { return mStatus; }

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Hit(UINT damage, bool flip, Vector2 direction);

		//float getMoveTime() { return moveTime; }
		eCommandType CheckMoveDirection();
		void CommandCheck();
		std::vector<Command> GetCommandVector() { return mCommandVector; }
		std::vector<eCommandType> GetXMoveVector() { return mMoveVector[(UINT)eMoveType::axisX]; }
		std::vector<eCommandType> GetYMoveVector() { return mMoveVector[(UINT)eMoveType::axisY]; }
		ePlayerState GetPlayerState() { return mPlayerState; }
		std::vector<std::wstring> mAttackVector;

		//BehaviorTree* GetBT() { return mBehaviors; }

		//behavior
		bool IsWalk();
		bool IsRun();
		bool IsJump();
		bool IsSit();
		bool IsAttack();

		float GetCurTime() { return mCurTime; }
		void SetCurTime(float time) { mCurTime = time; }

		void EnterScene();
		void ExitScene();

	private:
		void Idle();
		void Walk();
		void Run();
		void Jump();
		void Attack();
		void QuickStanding();
		void Anim();
		void Die();
		void Hit();
		void AnimHit();

		void JumpUpStartEvent();
		void JumpUpCompleteEvent();
		void Attack1StartEvent();
		void Attack2StartEvent();
		void Attack3StartEvent();
		void Attack1CompleteEvent();
		void Attack2CompleteEvent();
		void Attack3CompleteEvent();

		void Attack_Basic();
		void Attack_Rush();
		void Attack_Thrust();
		void Attack_UpperSlash();
		void Attack_IceWave();
		void Attack_FireWave();
		void Attack_ReleaseWave();



	private:
		ePlayerState mPlayerState;
		ePlayerState mPrevPlayerState;

		//std::vector<UINT> moveVector;
		//float moveTime;
		//bool bMove;
		float mCurTime;
		Vector3 mVelocity;

		std::vector<Command> mCommandVector;
		std::vector<eCommandType> mMoveVector[2];
		float commandTime;
		bool bCommand;

		std::vector<bool> bAttackVector;
		//std::vector<std::wstring> mAttackVector;

		//Animator* mAnimator;
		//Collider2D* mCollider;
		//bool isFlip;
		//BehaviorTree* mBehaviors;

		bool bRun;
		bool jumpDown;

		//Player* mOwner;
		AttackScriptManager* AtkManager;

		bool mActivate;
		bool bAttack;
		status mStatus;
		float mHitTime;

		std::wstring attackName;

	};


}
