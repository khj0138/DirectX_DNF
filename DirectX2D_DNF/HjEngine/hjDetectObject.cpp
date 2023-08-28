//#include "hjDetectObject.h"
//#include "hjTransform.h"
//#include "hjGameObject.h"
//#include "hjTime.h"
//#include "hjCollider2D.h"
//#include "hjMeshRenderer.h"
//#include "hjResources.h"
//
//#include "hjPlayer.h"
//namespace hj
//{
//
//	DetectObject::DetectObject()
//		: mActivate(false)
//	{
//	}
//	DetectObject::~DetectObject()
//	{
//	}
//	void DetectObject::Initialize()
//	{
//		MeshRenderer* mr = AddComponent<MeshRenderer>();
//		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
//		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
//
//		AddComponent<Collider2D>();
//		AttackObject::Initialize();
//	}
//	void DetectObject::Update()
//	{
//		AttackObject::Update();
//	}
//
//	void DetectObject::LateUpdate()
//	{
//		AttackObject::LateUpdate();
//
//	}
//
//	void DetectObject::Render()
//	{
//		AttackObject::Render();
//
//	}
//
//	void DetectObject::OnCollisionEnter(Collider2D* other)
//	{
//		mPlayer = dynamic_cast<Player*>(other->GetOwner());
//	}
//
//	void DetectObject::OnCollisionStay(Collider2D* other)
//	{
//
//	}
//
//	void DetectObject::OnCollisionExit(Collider2D* other)
//	{
//	}
//
//}
