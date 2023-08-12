#pragma once
#include <hjScript.h>

namespace hj
{
	//class Animator;
	class AttackObject;
	class EffectObject;
	class AttackScript : public Script
	{
	public:
		AttackScript();
		~AttackScript();

		virtual void Initialize() override;
		virtual void Update() override;
	public:


		void SetCoolTime(float coolTime) { mCoolTime = coolTime; }

		bool SetActivate(bool activate)
		{
			if (activate)
			{
				if (curTime > mCoolTime)
				{
					curTime = 0.0f;
					mActivate = true;
				}
			}
			else
			{
				mActivate = false;
			}
			return mActivate;
		}
		//template <typename T>

		template <typename T>
		bool RegisterAttackObject(const std::wstring name)
		{
			// 키값으로 탐색
			//T* attackObject = mAttackObjectsFind<T>(key);
			T* attackObject = new T();

			std::map<std::wstring, AttackObject*>::iterator iter
				= mAttackObjects.find(name);

			if (iter != mAttackObjects.end())
				return false;

			attackObject->SetName(name);
			mAttackObjects.insert(std::make_pair(name, attackObject));
			attackObject->Initialize();
			return true;

		}
		AttackObject* LoadAttackObject(std::wstring name)
		{
			std::map<std::wstring, AttackObject*>::iterator iter = mAttackObjects.find(name);
			if (iter == mAttackObjects.end())
				return nullptr;
			return iter->second;
		}

		

		template <typename T>
		bool RegisterEffectObject(const std::wstring name)
		{
			// 키값으로 탐색
			//T* EffectObject = mEffectObjectsFind<T>(key);
			T* effectObject = new T();

			std::map<std::wstring, EffectObject*>::iterator iter
				= mEffectObjects.find(name);

			if (iter != mEffectObjects.end())
				return false;

			effectObject->SetName(name);
			mEffectObjects.insert(std::make_pair(name, EffectObject));
			effectObject->Initialize();
			return true;

		}

		EffectObject* LoadEffectObject(std::wstring name)
		{
			std::map<std::wstring, EffectObject*>::iterator iter = mEffectObjects.find(name);
			if (iter == mEffectObjects.end())
				return nullptr;
			return iter->second;
		}

	private:
		std::map<std::wstring, AttackObject*> mAttackObjects;
		std::map<std::wstring, EffectObject*> mEffectObjects;
		bool mActivate;
		float mCoolTime;
		float curTime;

	};


}
