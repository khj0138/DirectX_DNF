#include "hjTime.h"
#include "hjApplication.h"
#include "hjRenderer.h"
#include "hjInput.h"

#include "hjGameObject.h"

extern hj::Application application;



namespace hj
{
	double Time::mDeltaTime = 0.0l;
	double Time::mTimeForRandom = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initiailize()
	{
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		// 현재 프로그램 진동수
		QueryPerformanceCounter(&mCurFrequency);

		// 이전 프레임의 프로그램 진동수 계산
		double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		// 프레임의 deltaTime 계산
		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

		Time::BindConstantBuffer();

		mTimeForRandom = mDeltaTime;
	}

	void Time::Render()
	{
		mSecond += mDeltaTime;
	
		// 1초마다 FPS 출력
		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			Vector3 a = hj::Input::mMouse->GetComponent<Transform>()->GetPosition();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d, mouse(%f, %f)", (UINT)FPS, a.x, a.y);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}
	}
	
	void Time::BindConstantBuffer()
	{
		float resolution[2] = { (float)application.GetFixedWidth() / 800.f, (float)application.GetFixedHeight() / 450.f };
		renderer::TimeCB timeCB = {};
		timeCB.Time = mDeltaTime;
		timeCB.Empty = Vector3::One;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Time];
		cb->SetData(&timeCB);
		cb->Bind(eShaderStage::VS);
	}
}
