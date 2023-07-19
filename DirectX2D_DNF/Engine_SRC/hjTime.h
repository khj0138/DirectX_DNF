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

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
	};
}
