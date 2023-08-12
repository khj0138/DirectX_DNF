#pragma once
#include "hjComponent.h"
#include "hjAnimation.h"

namespace hj
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f
			, bool back = false);
		Animation* CreateAnimations(const std::wstring& path, float duration, Vector2 offset = Vector2::Zero, bool back = false);
		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop, bool back = false);
		void CloseAnimation() { mActiveAnimation = nullptr; }
		bool isAnimatorClose() { return (mActiveAnimation == nullptr); }

		void Binds();
		void SetFlip(bool flip) 
		{
			isFlip = flip;
			mActiveAnimation->SetFlip(flip);
			if (isFlip)
			{
				animatorOffset.x = -1.0f * abs(animatorOffset.x);
			}
			else
			{
				animatorOffset.x = abs(animatorOffset.x);
			}
		}

		Vector2 GetAnimatorOffset() { return animatorOffset; }
		void SetAnimatorOffset(Vector2 offset) { animatorOffset = offset; }

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		std::shared_ptr<graphics::Texture> mImageAtlas;
		bool mbLoop;
		bool isFlip;
		Vector2 animatorOffset;
		//bool isBack;
	};
}
