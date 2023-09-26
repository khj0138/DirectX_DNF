#include "hjAttackScriptManager.h"

#include "hjCollider2D.h"
#include "hjTransform.h"
#include "hjSceneManager.h"
#include "hjGameObject.h"
namespace hj
{
	AttackScriptManager::AttackScriptManager()
		: mTargetPos(Vector3::Zero)
		, mTargetPosVZ(0.0f)
	{
	}
	AttackScriptManager::~AttackScriptManager()
	{
		for (auto attackScript = mAttackScripts.begin(); attackScript != mAttackScripts.end(); attackScript++)
		{
			delete attackScript->second;
		}
	}
	void AttackScriptManager::Update()
	{
		for (auto AttackScriptiter = mAttackScripts.begin(); AttackScriptiter != mAttackScripts.end(); AttackScriptiter++)
		{
			AttackScriptiter->second->SetPos(mPosition, mPositionVZ);
			AttackScriptiter->second->Update();
		}
	}

	void AttackScriptManager::LateUpdate()
	{
		for (auto AttackScriptiter = mAttackScripts.begin(); AttackScriptiter != mAttackScripts.end(); AttackScriptiter++)
		{
			AttackScriptiter->second->SetPos(mPosition, mPositionVZ);
			AttackScriptiter->second->LateUpdate();
		}
	}

	void AttackScriptManager::Render()
	{
		for (auto AttackScriptiter = mAttackScripts.begin(); AttackScriptiter != mAttackScripts.end(); AttackScriptiter++)
		{
			AttackScriptiter->second->SetPos(mPosition, mPositionVZ);
			AttackScriptiter->second->Render();
		}
	}
	
	void AttackScriptManager::EnterScene()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (auto attackScript = mAttackScripts.begin(); attackScript != mAttackScripts.end(); attackScript++)
		{
			for (auto attackObject = attackScript->second->GetAttackObjectsBegin();
				attackObject != attackScript->second->GetAttackObjectsEnd();
				attackObject++)
			scene->AddGameObject(mType, (GameObject*)(attackObject->second->GetOwner()));
		}
		/*for (auto attackScript = mAttackScripts.begin(); attackScript != mAttackScripts.end(); attackScript++)
		{
			for (auto effectObject = attackScript->second->GetEffectObjectsBegin();
				effectObject != attackScript->second->GetEffectObjectsEnd();
				effectObject++)
				scene->AddGameObject(eLayerType::Effect, (GameObject*)(effectObject->second->GetOwner()));
		}*/
	}
	void AttackScriptManager::ExitScene()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (auto attackScript = mAttackScripts.begin(); attackScript != mAttackScripts.end(); attackScript++)
		{
			for (auto attackObject = attackScript->second->GetAttackObjectsBegin();
				attackObject != attackScript->second->GetAttackObjectsEnd();
				attackObject++)
				scene->EraseGameObject(mType, (GameObject*)attackObject->second->GetOwner());
		}
		/*for (auto attackScript = mAttackScripts.begin(); attackScript != mAttackScripts.end(); attackScript++)
		{
			for (auto effectObject = attackScript->second->GetEffectObjectsBegin();
				effectObject != attackScript->second->GetEffectObjectsEnd();
				effectObject++)
				scene->EraseGameObject(eLayerType::Effect, (GameObject*)effectObject->second->GetOwner());
		}*/
	}
	void AttackScriptManager::SetTargetColPos(GameObject* target)
	{
		float sec45 = 1.4f;
		Transform* tr = target->GetComponent<Transform>();
		Collider2D* objCol = target->GetComponent<Collider2D>();
		Vector3 objColPos = objCol->GetPosition();
		Vector3 objColSize = objCol->GetSize();
		Vector2 objColCenter = objCol->GetCenter();
		if (target->GetFlip())
		{
			objColCenter.x = objColCenter.x * -1.0f;
		}
		objColPos.y -= objColSize.y / 2.0f * sec45;
		mTargetPosVZ = objColPos.y;
		objColPos.x -= objColCenter.x;
		objColPos.y = 0.0f;
		mTargetPos = objColPos;
		
	}
	void AttackScriptManager::SetTargetPos(GameObject* target)
	{
		Transform* tr = target->GetComponent<Transform>();
		mTargetPos = tr->GetPosition();
		mTargetPosVZ = tr->GetVirtualZ();
	}
	void AttackScriptManager::SetPause()
	{
		for (auto AttackScriptiter = mAttackScripts.begin(); AttackScriptiter != mAttackScripts.end(); AttackScriptiter++)
		{
			AttackScriptiter->second->SetPause();
		}
	}
}