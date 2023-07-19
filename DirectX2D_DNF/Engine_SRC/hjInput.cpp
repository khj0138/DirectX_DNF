#include "hjInput.h"
#include "hjApplication.h"
#include "hjRenderer.h"
#include "hjmath.h"

#include "hjGameObject.h"
#include "hjTransform.h"
#include "hjSceneManager.h"
#include "hjMeshRenderer.h"
#include "hjResources.h";
#include "hjMesh.h";
#include "hjMaterial.h";

extern hj::Application application;

namespace hj
{
	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT ,VK_RIGHT, VK_SPACE,
		VK_LBUTTON, VK_RBUTTON,
	};

	std::vector<Input::Key> Input::mKeys;
	GameObject* Input::mMouse = new GameObject();

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
		{
			mMouse->SetName(L"Mouse");
			/*SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mMouse);
			MeshRenderer* mr = mMouse->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			mMouse->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));*/
		}
	}

	void Input::Update()
	{
		if (GetFocus())
		{

			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Pressed;
					else
						mKeys[i].state = eKeyState::Down;

					mKeys[i].bPressed = true;
				}
				else // 현재 프레임에 키가 눌려있지 않다.
				{
					// 이전 프레임에 내키가 눌려있엇다.
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Up;
					else
						mKeys[i].state = eKeyState::None;

					mKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);

			ScreenToClient(application.GetHwnd(), &mousePos);

			const Vector3 winMouse = Vector3{ (float)mousePos.x,(float)mousePos.y, 1.0f };

			Vector3 UIMouse = Vector3::Zero;
			Vector3 worldMouse = Vector3::Zero;
			const Matrix projectionMatrix = Camera::GetGPUProjectionMatrix();
			const Matrix viewMatrix = Camera::GetGPUViewMatrix();
			const Matrix UIMatrix = Matrix::Identity;
			if (renderer::mainCamera != nullptr)
			{
				Matrix WorldMatrix; 
				WorldMatrix.Translation(renderer::mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition());

				Viewport viewport;
				viewport.width = 1600.0f;
				viewport.height = 900.0f;
				viewport.x = 0;
				viewport.y = 0;
				viewport.minDepth = 0.0f;
				viewport.maxDepth = 1.0f;


				UIMouse = viewport.Unproject(winMouse, projectionMatrix, viewMatrix, WorldMatrix);
			
				worldMouse = viewport.Unproject(winMouse, projectionMatrix, viewMatrix, UIMatrix );
			if (GetKey(eKeyCode::A))
			{
				int a = 0;
			}
			mMouse->GetComponent<Transform>()->SetPosition(worldMouse);
			
			}
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (eKeyState::Down == mKeys[i].state
					|| eKeyState::Pressed == mKeys[i].state)
				{
					mKeys[i].state = eKeyState::Up;
				}
				else if (eKeyState::Up == mKeys[i].state)
				{
					mKeys[i].state = eKeyState::None;
				}

				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}
}
