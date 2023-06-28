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
			// 리소스맵 내부 데이터 탐색
			// 데이터 존재 시 데이터 반환
			// 데이터 부재 시 end 반환
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);

			// 동적으로 데이터의 type 설정 후 반환
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			//데이터 없다면 nullptr 반환
			return nullptr;
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// 키값으로 탐색
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// 해당 리소스가 없다면
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

