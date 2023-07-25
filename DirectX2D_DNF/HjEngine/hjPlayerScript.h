#pragma once
//#include "hjScript.h"
#include <hjScript.h>

namespace hj
{
	class Animator;
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
		PlayerScript();
		~PlayerScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

	public:
		void Idle();
		void Walk();
		void Run();
		void Jump();
		void Attack();
		void Anim();
	private:
		ePlayerState mPlayerState;
		ePlayerState mPrevPlayerState;
		std::vector<UINT> commandVector;
		float commandTime;
		Animator* mAnimator;
		bool isFlip;
	};
}
