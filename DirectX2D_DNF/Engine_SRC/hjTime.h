#pragma once
#include "hjEngine.h"

namespace hj
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render();
		static void BindConstantBuffer();


		__forceinline static double DeltaTime() { return mDeltaTime; }
		__forceinline static double TimeForRandom() { 
			int intNum = (int)mTimeForRandom;
			mTimeForRandom -= (float)intNum;
			while (mTimeForRandom < 1.0f)
			{
				mTimeForRandom *= 10.0f;
			}

			return mTimeForRandom;
		}

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static double mTimeForRandom;
	};
}
