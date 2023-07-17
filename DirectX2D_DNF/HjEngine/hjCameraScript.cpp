#include "hjCameraScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"

namespace hj
{
	void CameraScript::Update()
	{
		Vector3 pos = Vector3::Zero;
		Camera* cam = GetOwner()->GetComponent<Camera>();

		if (cam->CheckTarget(pos))
		{
			GetOwner()->GetComponent<Transform>()->SetPosition(
				Vector3{
					pos.x,
					pos.y,
					GetOwner()->GetComponent<Transform>()->GetPosition().z
				}
			);
		}

		else
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			pos = tr->GetPosition();
			if (Input::GetKey(eKeyCode::W))
			{
				pos.z += 500.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::S))
			{
				pos.z -= 500.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::A))
			{
				pos.x -= 500.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::D))
			{
				pos.x += 500.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::Q))
			{
				pos.y -= 500.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::E))
			{
				pos.y += 500.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}

	}
}
