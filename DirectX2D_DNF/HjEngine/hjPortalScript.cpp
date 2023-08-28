#include "hjPortalScript.h"
#include "hjTransform.h"
#include "hjGameObject.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjSceneManager.h"
//#include "hjComponent.h"
//#include "hjBehaviorTree.h"

namespace hj
{

	PortalScript::PortalScript()
		: destName(L"")
	{
	}
	PortalScript::~PortalScript()
	{
	}
	void PortalScript::Initialize()
	{
	}
	void PortalScript::Update()
	{
	}

	void PortalScript::LateUpdate()
	{
		if (!(GetOwner()->GetComponent<Collider2D>()->GetCollision()))
			GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
	}

	void PortalScript::SetPortal(std::wstring name, Vector2 offset)
	{
		mName = name;
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		float virtualZ = GetOwner()->GetComponent<Transform>()->GetVirtualZ();
		Vector2 portalPos = Vector2(pos.x + offset.x, virtualZ + offset.y);
		SceneManager::RegisterPortal(mName, portalPos);
	}

	void PortalScript::OnCollisionEnter(Collider2D* other)
	{
		
	}

	void PortalScript::OnCollisionStay(Collider2D* other)
	{
		Vector3 colPos = GetOwner()->GetComponent<Collider2D>()->GetPosition();
		Vector3 playerColPos = other->GetPosition();
		Vector2 colPos2D = Vector2(colPos.x, colPos.y);
		Vector2 playerColPos2D = Vector2(playerColPos.x, playerColPos.y);
		if (GetDestination() != L"")
		{
			if(Vector2::Distance(colPos2D, playerColPos2D) < 100.0f)
				SceneManager::PortalTeleport(GetDestination());
		}
	}

	void PortalScript::OnCollisionExit(Collider2D* other)
	{
	}



}
