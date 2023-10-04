#pragma once
#include <hjAttackScript.h>

namespace hj
{
	//class Animator;
	class IceWaveAttackScript : public AttackScript
	{
	public:
		IceWaveAttackScript();
		~IceWaveAttackScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Reset() override;
		virtual void SetActivate(bool activate) override;

	public:

	private:
		int WaveMax;
		int WaveIndex;
		int IceMax;
		int IceIndex;
	};


}
