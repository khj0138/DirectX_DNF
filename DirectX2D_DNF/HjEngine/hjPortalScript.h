#pragma once
#include <hjScript.h>

namespace hj
{
	class Animator;
	class PortalScript : public Script
	{
	public:
		PortalScript();
		~PortalScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		std::wstring GetDestination() { return destName; }
		void SetDestination(std::wstring destination) { destName = destination; }
		void SetPortal(std::wstring name, Vector2 offset);
		
		void SetDestination(std::wstring sceneName, Vector2 pos) { destScene = sceneName; destPos = pos; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:

	private:
		std::wstring mName;
		std::wstring destName;
		std::wstring destScene;
		Vector2 destPos;
	};


}
