#include "hjCameraScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"

#include "hjApplication.h"
extern hj::Application application;
namespace hj
{
	
	void CameraScript::Update()
	{
		float fixedRes = (float)(application.GetFixedWidth()) / 800.0f;
		Vector3 pos = Vector3::Zero;
		float virtualZ = 0.0f;
		Camera* cam = GetOwner()->GetComponent<Camera>();

		if (cam->CheckTarget(pos, virtualZ))
		{
			GetOwner()->GetComponent<Transform>()->SetPosition(
				Vector3{
					pos.x,
					pos.y + virtualZ * cos(math::degreeToRadian(45.0f)),
					GetOwner()->GetComponent<Transform>()->GetPosition().z /fixedRes
				}
				*fixedRes
			);
			GetOwner()->GetComponent<Transform>()->SetVirtualZ(virtualZ);
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

		pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector2 minXY = (cam->getMinXY() + Vector2(800.0f, 450.0f));// / fixedRes;
		Vector2 maxXY = (cam->getMaxXY() - Vector2(800.0f, 450.0f));// / fixedRes;

		if (pos.x < minXY.x)
			pos.x = minXY.x;
		else if (pos.x > maxXY.x)
			pos.x = maxXY.x;


		if (pos.y < minXY.y)
			pos.y = minXY.y;
		else if (pos.y > maxXY.y)
			pos.y = maxXY.y;

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
}
