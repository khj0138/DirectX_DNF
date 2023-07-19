#include "hjTime.h"
#include "hjApplication.h"
#include "hjRenderer.h"

extern hj::Application application;



namespace hj
{
	double Time::mDeltaTime = 0.0l;
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
	}

	void Time::Render()
	{
		mSecond += mDeltaTime;
	
		// 1초마다 FPS 출력
		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}
	}
	void Time::BindConstantBuffer()
	{
		float resolution[2] = { (float)application.GetWidth() / 1280.f, (float)application.GetHeight() / 720.f };
		renderer::EtcCB etcCB = {};
		etcCB.Time = mSecond;
		etcCB.Res = { resolution[0], resolution[1] };
		etcCB.Empty = 0.0f;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Etc];
		cb->SetData(&etcCB);
		cb->Bind(eShaderStage::VS);
	}
}
