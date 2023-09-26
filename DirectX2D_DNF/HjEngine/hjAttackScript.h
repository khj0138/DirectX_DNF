#pragma once
#include <hjScript.h>
#include "hjAttackObjectScript.h"
#include "hjEffectObjectScript.h"
#include "hjGameObject.h"

namespace hj
{
	//class Animator;
	//class AttackObject;
	//class EffectObject;
	class AttackScriptManager;
	//class GameObject;
	class AttackScript : public Script
	{
	public:
		AttackScript();
		~AttackScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Reset() = 0;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);
	public:

		void SetCoolTime(float coolTime) { mCoolTime = coolTime; }

		virtual void SetActivate(bool activate)
		{
			if (activate)
			{
				if (curTime >= mCoolTime)
				{
					mActivate = true;
				}
			}
			else
			{
				mActivate = false;
				curTime = 0.0f;
			}
		}
		bool GetActivate() { return mActivate; }
		void SetPause();
		//template <typename T>

		template <typename T>
		bool RegisterAttackObject(const std::wstring name)
		{
			GameObject* attackObject = new GameObject();

			T* attackObjectScript = new T();
			attackObject->AddScript((Script*)attackObjectScript);

			std::map<std::wstring, AttackObjectScript*>::iterator iter
				= mAttackObjects.find(name);

			if (iter != mAttackObjects.end())
				return false;

			attackObject->SetName(name);
			mAttackObjects.insert(std::make_pair(name, (AttackObjectScript*)attackObjectScript));

			attackObjectScript->SetManager(GetManager());
			return true;

		}
		AttackObjectScript* LoadAttackObject(std::wstring name)
		{
			std::map<std::wstring, AttackObjectScript*>::iterator iter = mAttackObjects.find(name);
			if (iter == mAttackObjects.end())
				return nullptr;
			return iter->second;
		}

		

		template <typename T>
		bool RegisterEffectObject(const std::wstring name)
		{
			GameObject* effectObject = new GameObject();

			T* effectObjectScript = new T();
			effectObject->AddScript((Script*)effectObjectScript);

			std::map<std::wstring, EffectObjectScript*>::iterator iter
				= mEffectObjects.find(name);

			if (iter != mEffectObjects.end())
				return false;

			effectObject->SetName(name);
			mEffectObjects.insert(std::make_pair(name, (EffectObjectScript*)effectObjectScript));

			effectObjectScript->SetManager(GetManager());

			return true;
		}

		EffectObjectScript* LoadEffectObject(std::wstring name)
		{
			std::map<std::wstring, EffectObjectScript*>::iterator iter = mEffectObjects.find(name);
			if (iter == mEffectObjects.end())
				return nullptr;
			return iter->second;
		}

		void SetPos(Vector2 pos, float posVZ) 
		{
			mPosition = pos;
			mPositionVZ = posVZ;
		}
		Vector2 GetPos() { return mPosition; }
		float GetPosVZ() { return mPositionVZ; }
		bool checkCoolTime() { return (curTime == mCoolTime); }

		std::map<std::wstring, AttackObjectScript*>::iterator GetAttackObjectsBegin() { return mAttackObjects.begin(); }
		std::map<std::wstring, AttackObjectScript*>::iterator GetAttackObjectsEnd() { return mAttackObjects.end(); }
		std::map<std::wstring, EffectObjectScript*>::iterator GetEffectObjectsBegin() { return mEffectObjects.begin(); }
		std::map<std::wstring, EffectObjectScript*>::iterator GetEffectObjectsEnd() { return mEffectObjects.end(); }
		std::map<std::wstring, AttackObjectScript*> mAttackObjects;
		std::map<std::wstring, EffectObjectScript*> mEffectObjects;
		void Release()
		{
			/*for (auto iter = mAttackObjects.begin(); iter != mAttackObjects.end(); iter++)
			{
				delete iter->second;
			}
			for (auto iter = mEffectObjects.begin(); iter != mEffectObjects.end(); iter++)
			{
				delete iter->second;
			}
			mAttackObjects.clear();
			mEffectObjects.clear();*/
		}
		void SetManager(AttackScriptManager* manager) { attackManager = manager; }
		AttackScriptManager* GetManager() { return attackManager; }

	private:
		bool mActivate;
		float mCoolTime;
		float curTime;
		bool flip;
		Vector2 mPosition;
		float mPositionVZ;
		AttackScriptManager* attackManager;
	};


}
