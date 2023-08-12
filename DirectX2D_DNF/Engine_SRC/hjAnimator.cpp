#include "hjAnimator.h"
#include "hjResources.h"

namespace hj
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, isFlip(false)
	{
	}
	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}


		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;
		if (mActiveAnimation->IsComplete())
		{
			Events* events
				= FindEvents(mActiveAnimation->GetKey());
			if (events)
				events->completeEvent() ;
			if (mbLoop == true)
				mActiveAnimation->Reset();
		}

		if (mActiveAnimation == nullptr)
			return;
		mActiveAnimation->LateUpdate();
	}
	void Animator::LateUpdate()
	{
		
	}
	void Animator::Render()
	{

	}

	void Animator::Create(const std::wstring& name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration
		, bool back)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->SetKey(name);
		animation->SetBack(back);

		animation->Create(name
			, atlas
			, leftTop
			, size
			, columnLength
			, offset
			, duration);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (events != nullptr)
			return;

		events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}
	Animation* Animator::CreateAnimations(const std::wstring& path, float duration, Vector2 offset, bool back)
	{
		size_t maxWidth = 0;
		size_t maxHeight = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<std::shared_ptr<Texture>> textures = {};
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path().wstring();

			const std::wstring ext = p.path().extension();

			std::shared_ptr<Texture> tex = Resources::Load<Texture>(fileName, fullName);

			if (maxWidth < tex->GetWidth())
			{
				maxWidth = tex->GetWidth();
			}
			if (maxHeight < tex->GetHeight())
			{
				maxHeight = tex->GetHeight();
			}

			textures.push_back(tex);

			fileCount++;
		}

		std::wstring key = fs.parent_path().filename();
		key += fs.filename();

		mImageAtlas = std::make_shared<graphics::Texture>();
		mImageAtlas->CreateTex(path, fileCount, maxWidth, maxHeight);
		if (back)
		{
			std::wstring addingWord = L"Back";
			key.append(addingWord);
		}
		Create(key, mImageAtlas, Vector2(0.0), Vector2(maxWidth, maxHeight), fileCount, offset, duration, back);

		return nullptr;
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop, bool back)
	{




		Animation* prevAnimation = mActiveAnimation;

		Events* events;
		if (prevAnimation != nullptr)
		{

			events = FindEvents(prevAnimation->GetKey());
			if (events)
				events->endEvent();
		}

		std::wstring fixedName = name;
		if (back)
		{
			std::wstring addingWord = L"Back";
			fixedName.append(addingWord);
		}
		Animation* animation = FindAnimation(fixedName);
		if (animation)
		{
			mActiveAnimation = animation;
		}

		events = FindEvents(mActiveAnimation->GetKey());
		if (events)
			events->startEvent();

		mbLoop = loop;
		mActiveAnimation->Reset();
		mActiveAnimation->SetFlip(isFlip);
		mActiveAnimation->SetBack(back);
		
	}
	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Binds();
	}
	std::function<void()>& Animator::StartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::CompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::EndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->endEvent.mEvent;
	}
}
