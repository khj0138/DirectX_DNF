#pragma once
#include "hjEntity.h"

namespace hj
{
	class AttackScript;
	class AttackScriptManager : public Entity
	{
	public:
		AttackScriptManager();
		~AttackScriptManager();

		void SetType(hj::enums::eLayerType type) { mType = type; }
		void Update();
		void SetPosition(hj::math::Vector2 pos, float posVZ) { mPosition = pos; mPositionVZ = posVZ; }
		hj::math::Vector3 GetPosition() { return hj::math::Vector3{ mPosition.x, mPosition.y, mPositionVZ }; }

		template <typename T>
		void RegisterAttackScript(std::wstring name)
		{
			T* newAttack = new T();
			newAttack->Initialize();
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
			return iter->second;
		}
		void EnterScene();
		void ExitScene();
		std::map<std::wstring, AttackScript*> mAttackScripts;
	private:
		hj::enums::eLayerType mType;
		hj::math::Vector2 mPosition;
		float mPositionVZ;
	};
}

