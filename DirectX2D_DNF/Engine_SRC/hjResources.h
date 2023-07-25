#pragma once
#include "hjResource.h"

namespace hj
{
	class Resources
	{
	public:
		template <typename T>
		static std::shared_ptr<T> Find(const std::wstring& key)
		{
			// 리소스맵 내부 데이터 탐색
			// 데이터 존재 시 데이터 반환
			// 데이터 부재 시 end 반환
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter = mResources.find(key);

			// 동적으로 데이터의 type 설정 후 반환
			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			//데이터 없다면 nullptr 반환
			return nullptr;
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
		{
			// 키값으로 탐색
			std::shared_ptr<T> resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// 해당 리소스가 없다면
			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}
	private:
		static std::map<std::wstring, std::shared_ptr<Resource>> mResources;
	};
}

