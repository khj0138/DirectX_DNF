#include "hjApplication.h"
#include "hjInput.h"
#include "hjTime.h"
#include "hjRenderer.h"
#include "hjSceneManager.h"
#include "hjCollisionManager.h"
#include "hjFmod.h"

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
		CollisionManager::Update();
		Render();
		Destroy();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();
		Fmod::Initialize();

		renderer::Initialize();
		SceneManager::Initialize();
		CollisionManager::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();

		
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();
		
		renderer::Render();

	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Present()
	{
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
		RECT windowRect = { 0, 0, (LONG)width + 0 , (LONG)height + 20 };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);

		fixedRes = (800.0f / (float)width);
		//float fixedRes = 2.0f;
	}

}
