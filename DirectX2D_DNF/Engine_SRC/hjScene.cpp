#include "hjScene.h"

namespace hj
{
	Scene::Scene()
	{
		mLayers.resize((int)hj::enums::eLayerType::End);
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
		
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destroy();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		gameObj->SetLayer((UINT)type);
		mLayers[(int)type].AddGameObject(gameObj);
	}
	void Scene::EraseGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].EraseGameObject(gameObj);
	}
}
