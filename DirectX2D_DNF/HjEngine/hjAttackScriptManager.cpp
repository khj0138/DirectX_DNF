#include "hjAttackScriptManager.h"


#include "hjSceneManager.h"
#include "hjGameObject.h"
namespace hj
{
	AttackScriptManager::AttackScriptManager()
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
		for (auto attackScript = mAttackScripts.begin(); attackScript != mAttackScripts.end(); attackScript++)
		{
			for (auto effectObject = attackScript->second->GetEffectObjectsBegin();
				effectObject != attackScript->second->GetEffectObjectsEnd();
				effectObject++)
				scene->AddGameObject(eLayerType::Effect, (GameObject*)(effectObject->second->GetOwner()));
		}
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
		for (auto attackScript = mAttackScripts.begin(); attackScript != mAttackScripts.end(); attackScript++)
		{
			for (auto effectObject = attackScript->second->GetEffectObjectsBegin();
				effectObject != attackScript->second->GetEffectObjectsEnd();
				effectObject++)
				scene->EraseGameObject(eLayerType::Effect, (GameObject*)effectObject->second->GetOwner());
		}
	}
}