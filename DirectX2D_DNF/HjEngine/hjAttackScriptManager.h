#pragma once

namespace hj
{
	class AttackScript;
	class AttackScriptManager
	{
	public:
		AttackScriptManager();
		~AttackScriptManager();
		template <typename T>
		void RegisterAttackScript(std::wstring name)
		{
			T* newAttack = new T();
			newAttack->Initialize();
			if(newAttack != nullptr)
			mAttackScripts.insert(std::make_pair(name, newAttack));
		}
		AttackScript* LoadAttackScript(std::wstring name)
		{
			std::map<std::wstring, AttackScript*>::iterator iter = mAttackScripts.find(name);
			if (iter == mAttackScripts.end())
				return nullptr;
			return iter->second;
		}
	private:
		std::map<std::wstring, AttackScript*> mAttackScripts;
	};
}

