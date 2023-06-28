#pragma once
#include "hjResource.h"

namespace hj
{
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& key)
		{
			// ���ҽ��� ���� ������ Ž��
			// ������ ���� �� ������ ��ȯ
			// ������ ���� �� end ��ȯ
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);

			// �������� �������� type ���� �� ��ȯ
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			//������ ���ٸ� nullptr ��ȯ
			return nullptr;
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// Ű������ Ž��
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// �ش� ���ҽ��� ���ٸ�
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

		static void Release()
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}

