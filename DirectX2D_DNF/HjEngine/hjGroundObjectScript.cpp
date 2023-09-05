#include "hjGroundObjectScript.h"

#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"

namespace hj
{

	GroundObjectScript::GroundObjectScript()
	{
		groundPoints.resize(4);
	}
	GroundObjectScript::~GroundObjectScript()
	{
	}
	void GroundObjectScript::Initialize()
	{
		Script::Initialize();
	}
	void GroundObjectScript::Update()
	{
		Script::Update();
	}



	void GroundObjectScript::OnCollisionEnter(Collider2D* other)
	{
		groundCollision(other);
		
	}

	void GroundObjectScript::OnCollisionStay(Collider2D* other)
	{
		groundCollision(other);

	}

	void GroundObjectScript::OnCollisionExit(Collider2D* other)
	{
		groundCollision(other);

	}

	bool GroundObjectScript::collisionCheck(Collider2D* other, Vector2& target)
	{
		collisionIndex = -1;
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		Vector3 colSize = col->GetSize();
		Vector2 colSize2D = Vector2(colSize.x, colSize.y);
		Vector3 colPosition = col->GetPosition();
		Vector2 colPosition2D = Vector2(colPosition.x, colPosition.y);
		float colRotation = col->GetRotation();

		groundPoints[0] = Vector2(colSize.x / -2.0f, colSize.y / 2.0f);
		groundPoints[1] = Vector2(colSize.x / 2.0f, colSize.y / 2.0f);
		groundPoints[2] = Vector2(colSize.x / 2.0f, colSize.y / -2.0f);
		groundPoints[3] = Vector2(colSize.x / -2.0f, colSize.y / -2.0f);
		for (int idx = 0; idx < 4; idx++)
		{
			math::Vector2::rotation(groundPoints[idx], colRotation);
			groundPoints[idx] += colPosition2D;
		}

		Vector2 otherColPrevPos = Vector2(other->GetPrevPosition().x, other->GetPrevPosition().y);
		Vector2 otherColPos = Vector2(other->GetPosition().x, other->GetPosition().y);

		for (int idx = 0; idx < 4; idx++)
		{
			Vector2 tempTarget = Vector2::Zero;
			Vector2 point1 = groundPoints[idx];
			Vector2 point2 = groundPoints[(idx + 1) % 4];
			if (math::Vector2::Intersection_Lines(otherColPrevPos, otherColPos, point1, point2, tempTarget))
			{
				
				if ((tempTarget != Vector2::Zero) &&
					math::Vector2::Distance(otherColPrevPos, tempTarget) < math::Vector2::Distance(otherColPrevPos, target))
				{
					target = tempTarget;
					collisionIndex = idx;
				}
			}
		}
		if (collisionIndex == -1)
		{
			return false;
		}
		return true;
	}

	void GroundObjectScript::groundCollision(Collider2D* other)
	{
		Vector2 target = Vector2(-9999.0f, -9999.0f);
		if (collisionCheck(other, target))
		{
			Vector2 otherColPrevPos = Vector2(other->GetPrevPosition().x, other->GetPrevPosition().y);
			Vector2 otherColPos = Vector2(other->GetPosition().x, other->GetPosition().y);

			//Vector2 colPrevPos = Vector2(GetOwner()->GetComponent<Collider2D>()->GetPrevPosition().x
			//	, GetOwner()->GetComponent<Collider2D>()->GetPrevPosition().y);
			//Vector2 colPos = Vector2(GetOwner()->GetComponent<Collider2D>()->GetPosition().x
			//	, GetOwner()->GetComponent<Collider2D>()->GetPosition().y);


			//Vector2 prevColVector = colPrevPos - otherColPrevPos; // c
			//Vector2 curColVector = colPos - otherColPos; // d
			//Vector2 otherColVector = otherColPos - otherColPrevPos; // a
			//Vector2 colVector = colPos - colPrevPos; // b
			int point1 = collisionIndex;
			int point2 = (collisionIndex+1) % 4;
			Vector2 colVector = groundPoints[point2] - groundPoints[point1]; // b

			//double otherToThis = otherColVector.Cross(colVector).x;
			//double prevToOther = prevColVector.Cross(colVector).x;

			//Vector2 crossPoint = otherColPrevPos + otherColVector * (prevToOther / otherToThis);
			Vector2 crossPoint = target;

			Vector2 otherColPrevToP = crossPoint - otherColPrevPos;
			Vector2 pToOtherCol = otherColPos - crossPoint;

			Vector2 colVectorN = Vector2::Zero;
			colVector.Normalize(colVectorN);

			/*Vector3 otherPos = other->GetOwner()->GetComponent<Transform>()->GetPrevPosition();
			Vector2 otherPos2D = Vector2(otherPos.x, other)*/
			
			Vector2 result = otherColPrevPos + otherColPrevToP
				+ colVectorN * colVectorN.Dot(pToOtherCol);
			Vector2 vect = colVector;
			vect.Normalize();
			math::Vector2::rotation(vect, math::degreeToRadian(90.0f));
			result += vect * 0.5f;
			Vector3 resultColPos = other->GetPosition();
			resultColPos.x = result.x;
			resultColPos.y = result.y;
			other->SetPosition(resultColPos);
			Vector3 otherPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();

			Vector3 resultPos = Vector3(result.x, result.y, otherPos.z);
			Vector2 otherCenter = other->GetCenter();
			resultPos.x -= otherCenter.x;
			resultPos.y -= otherCenter.y;
			float resultVZ = resultPos.y - otherPos.y;
			resultPos.y -= resultVZ;
			other->GetOwner()->GetComponent<Transform>()->SetPosition(resultPos);
			other->GetOwner()->GetComponent<Transform>()->SetVirtualZ(resultVZ);
		}
		
	}

}
