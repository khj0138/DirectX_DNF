#include "hjGuiEditor.h"
#include "..\\Engine_SRC\\hjMesh.h"
#include "..\\Engine_SRC\\hjResources.h"
#include "..\\Engine_SRC\\hjTransform.h"
#include "..\\Engine_SRC\\hjMeshRenderer.h"
#include "..\\Engine_SRC\\hjMaterial.h"
#include "..\\Engine_SRC\\hjRenderer.h"

#include "hjGridScript.h"

namespace gui
{
	using namespace hj::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*>Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};


	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<hj::Mesh> mesh
			= hj::Resources::Find<hj::Mesh>(L"DebugRect");
		std::shared_ptr<hj::Material> material
			= hj::Resources::Find<hj::Material>(L"DebugRectMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		//mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<hj::Transform>();
		hj::MeshRenderer* mr
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<hj::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		mesh
			= hj::Resources::Find<hj::Mesh>(L"DebugCircle");
		material
			= hj::Resources::Find<hj::Material>(L"DebugCircleMaterial");
		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		//mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<hj::Transform>();
		mr
			= mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<hj::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		/*EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<hj::MeshRenderer>();
		mr->SetMesh(hj::Resources::Find<hj::Mesh>(L"RectMesh"));
		mr->SetMaterial(hj::Resources::Find<hj::Material>(L"GridMaterial"));
		hj::GridScript* gridSc = grid->AddComponent<hj::GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);*/
	}

	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const hj::graphics::DebugMesh* mesh
			: renderer::debugMeshs)
		{
			if(mesh->bActivate)
				DebugRender(mesh);
			else
			{
				int a = 0;
			}
		}
		renderer::debugMeshs.clear();
	}

	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const hj::graphics::DebugMesh* mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh->type];


		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		hj::Transform* tr = debugObj->GetComponent<hj::Transform>();

		Vector3 pos = Vector3(mesh->position.x, 0.0f,-0.01f);
		//pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetVirtualZ(mesh->position.y);// / cosf(hj::math::degreeToRadian(45.0f)));
		tr->SetScale(mesh->scale);
		tr->SetRotation(mesh->rotation);

		tr->LateUpdate();
		Matrix world = tr->GetMatrix();
		//world._12 = world._12 * cosf(math::degreeToRadian(45.0f));
		//world._22 = world._22 * cosf(math::degreeToRadian(45.0f));
		//world._32 = world._32 * cosf(math::degreeToRadian(45.0f));
		//world._42 = world._42 / cosf(math::degreeToRadian(45.0f));
		/*hj::MeshRenderer * mr
			= debugObj->GetComponent<hj::MeshRenderer>();*/
			// main camera
		hj::Camera* mainCamara = renderer::mainCamera;

		hj::Camera::SetGPUViewMatrix(mainCamara->GetViewMatrix());
		hj::Camera::SetGPUProjectionMatrix(mainCamara->GetProjectionMatrix());



		renderer::CollisionCB colObj = {};
		if (mesh->bCollision == true)
			int a = 0;
		colObj.bCollision = (UINT)(mesh->bCollision);
		colObj.Empty = Vector3::Zero;
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Collision];
		cb->SetData(&colObj);
		cb->Bind(eShaderStage::PS);

		debugObj->Render();
	}

}