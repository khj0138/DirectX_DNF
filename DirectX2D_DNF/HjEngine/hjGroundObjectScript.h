#pragma once
#include <hjScript.h>

namespace hj
{
	//class Animator;
	class GroundObjectScript : public Script
	{
	public:
		GroundObjectScript();
		~GroundObjectScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		bool collisionCheck(Collider2D* other, Vector2& target);
		void groundCollision(Collider2D* other);
	public:

	private:
		std::vector<Vector2> groundPoints;
		int collisionIndex;
	};


}
