#include "hjApplication.h"
#include "hjInput.h"
#include "hjTime.h"
#include "hjRenderer.h"
#include "hjScene.h"

namespace hj
{

	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();

		renderer::Initialize();

		mScene = new Scene();
		mScene->Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();

		mScene->Update();
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->Draw();
		mScene->Render();
		graphicDevice->Present();
	}

	// 윈도우 속성 설정
	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<hj::graphics::GraphicDevice_Dx11>();
			hj::graphics::GetDevice() = graphicDevice.get();
		}

		// 윈도우 size 설정 (0 ~ width, 0 ~ height)
		RECT windowRect = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}
