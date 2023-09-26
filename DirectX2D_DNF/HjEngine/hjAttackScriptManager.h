#pragma once
#include "hjEntity.h"
#include "hjAttackScript.h"
namespace hj
{
	class GameObject;
	class AttackScriptManager : public Entity
	{
	public:
		AttackScriptManager();
		~AttackScriptManager();

		void SetType(hj::enums::eLayerType type) { mType = type; }
		void Update();
		void LateUpdate();
		void Render();
		void SetPosition(hj::math::Vector2 pos, float posVZ) { mPosition = pos; mPositionVZ = posVZ; }
		hj::math::Vector3 GetPosition() { return hj::math::Vector3{ mPosition.x, mPosition.y, mPositionVZ }; }

		template <typename T>
		void RegisterAttackScript(std::wstring name)
		{
			T* newAttack = new T();
			newAttack->SetManager(this);
			newAttack->Initialize();
			newAttack->SetOwner(mManagerOwner);
			//std::pair<std::wstring, AttackScript*> a = std::make_pair(name, (AttackScript*)newAttack);
			AttackScript* attack = (AttackScript*)newAttack;
			if(attack != nullptr)
				mAttackScripts.insert(std::make_pair(name, attack));
		}
		AttackScript* LoadAttackScript(std::wstring name)
		{
			std::map<std::wstring, AttackScript*>::iterator iter = mAttackScripts.find(name);
			if (iter == mAttackScripts.end())
				return nullptr;
			iter->second->SetActivate(true);
			if (iter->second->GetActivate())
				iter->second->Reset();
			else
				return nullptr;
			return iter->second;
		}
		void EnterScene();
		void ExitScene();
		std::map<std::wstring, AttackScript*> mAttackScripts;

		GameObject* GetManagerOwner() { return mManagerOwner; }
		void SetManagerOwner(GameObject* owner) { mManagerOwner = owner; }

		void SetTargetColPos(GameObject* target);
		void SetTargetPos(GameObject* target);
		Vector3 GetTargetPos() { return mTargetPos; }
		float GetTargetPosVZ() { return mTargetPosVZ; }

		bool CheckActivate(std::wstring name)
		{
			std::map<std::wstring, AttackScript*>::iterator iter = mAttackScripts.find(name);
			if (iter != mAttackScripts.end())
				return iter->second->GetActivate();
			return false;
		}
		void SetPause();
	private:
		hj::enums::eLayerType mType;
		hj::math::Vector2 mPosition;
		float mPositionVZ;
		GameObject* mManagerOwner;
		Vector3 mTargetPos;
		float mTargetPosVZ;
	};
}

