#include "hjCameraScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"

namespace hj
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 1.0f * Time::DeltaTime();
		tr->SetPosition(pos);
	}
}
