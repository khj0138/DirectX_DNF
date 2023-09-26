#include "hjCollisionManager.h"
#include "hjGameObject.h"
#include "hjScene.h"
#include "hjSceneManager.h"
#include "hjLayer.h"
#include "hjCollider2D.h"

namespace hj
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	bool CollisionManager::start = false;

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		if (!start)
		{
			start = true;
			return;
		}
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}
	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState()
				!= GameObject::eState::Active)
				continue;
			/*if (!(leftCol->GetCollision()))
				continue;*/
			
			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;
				if (rightObj->GetState()
					!= GameObject::eState::Active)
					continue;
				/*if (!(rightCol->GetCollision()))
					continue;*/
				ColliderCollision(leftCol, rightCol);
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// 충돌정보를 가져온다
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));

			iter = mCollisionMap.find(id.id);
		}

		if (!(left->GetCollision()) || !(right->GetCollision()))
		{
			if (iter->second)
			{
				iter->second = false;

				left->CollisionMesh(false);
				right->CollisionMesh(false);
			}
			else
				return;
		}
		else
		{
			if (Intersect(left, right))
			{
				// 충돌
				if (iter->second == false)
				{
					//최초 충돌
					left->OnCollisionEnter(right);
					right->OnCollisionEnter(left);
				}
				else
				{
					// 충돌 중
					left->OnCollisionStay(right);
					right->OnCollisionStay(left);
				}
				iter->second = true;

				left->CollisionMesh(true);
				right->CollisionMesh(true);
			}
			else
			{
				// 충돌 X
				if (iter->second == true)
				{
					// 충돌하고 있다가 나갈떄
					left->OnCollisionExit(right);
					right->OnCollisionExit(left);

					left->CollisionMesh(false);
					right->CollisionMesh(false);
				}
				iter->second = false;

			}
		}
	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		if (left->GetType() == right->GetType())
		{
			if (left->GetType() == eColliderType::Rect)
			{
				Vector3 leftScale = left->GetSize();
				float leftRotation = left->GetObjectRotation().z;
				Vector3 rightScale = right->GetSize();
				float rightRotation = right->GetObjectRotation().z;

				/*std::vector<Vector3> axis3D;
				axis3D.push_back(Vector3::Up * left->GetTransform()->GetScale());
				axis3D.push_back(Vector3::Right * left->GetTransform()->GetScale());
				axis3D.push_back(Vector3::Up * right->GetTransform()->GetScale());
				axis3D.push_back(Vector3::Right * right->GetTransform()->GetScale());
				axis3D.push_back(left->GetTransform()->GetPosition() - right->GetTransform()->GetPosition());*/
				
				std::vector<Vector2> axis2D;
				axis2D.push_back((Vector2{ 0.0f, 1.0f } * Vector2(leftScale.x, leftScale.y)));
				axis2D.push_back((Vector2{ 1.0f, 0.0f } * Vector2(leftScale.x, leftScale.y)));
				axis2D.push_back((Vector2{ 0.0f, 1.0f } * Vector2(rightScale.x, rightScale.y)));
				axis2D.push_back((Vector2{ 1.0f, 0.0f } * Vector2(rightScale.x, rightScale.y)));
				


				for (int i = 0; i < 2; i++)
				{
					math::Vector2::rotation(axis2D[i], leftRotation);
					math::Vector2::rotation(axis2D[i + 2], rightRotation);
				}

				Vector3 temp = left->GetPosition() - right->GetPosition();
				axis2D.push_back(Vector2{temp.x, temp.y});

				for (int i = 0; i < 4; i++)
				{
					Vector2 axis = axis2D[i];
					axis.Normalize();
					float length = abs(axis.Dot(axis2D[4]));

					float sum = 0.0f;
					for (int j = 0; j < 4; j++)
					{
						sum += abs(axis.Dot(axis2D[j]));
					}
					if (sum < (length * 2))
						return false;
				}
				return HeightCheck(left, right);
			}
			else if (left->GetType() == eColliderType::Circle)
			{
				float leftRadius = left->GetSize().x * 0.5f;
				float rightRadius = right->GetSize().x * 0.5f;

				Vector3 temp = left->GetPosition() - right->GetPosition();
				//Vector2 temp2D = Vector2{ temp.x,temp.y / cosf(math::degreeToRadian(45.0f))};
				Vector2 temp2D = Vector2{ temp.x,temp.y};
				float length = temp2D.Length();

				if (length > (leftRadius + rightRadius))
					return false;
				return HeightCheck(left, right);
			}
		}
		else
		{
			if (left->GetType() == eColliderType::Circle)
			{
				Collider2D* temp = left;
				left = right;
				right = temp;
			}
			
			Vector3 leftScale = left->GetSize();
			float leftRotation = left->GetObjectRotation().z + left->GetRotation();

			std::vector<Vector2> axis2D;
			axis2D.push_back((Vector2{ 0.0f, 1.0f } *Vector2(leftScale.x, leftScale.y)));
			axis2D.push_back((Vector2{ 1.0f, 0.0f } *Vector2(leftScale.x, leftScale.y)));

			for (int i = 0; i < 2; i++)
			{
				math::Vector2::rotation(axis2D[i], leftRotation);
			}

			Vector2 leftPos = Vector2(left->GetPosition().x, left->GetPosition().y);
			Vector2 rightPos = Vector2(right->GetPosition().x, right->GetPosition().y);

			Vector3 temp = left->GetPosition() - right->GetPosition();
			axis2D.push_back(Vector2{ temp.x, temp.y });

			for (int i = 0; i < 2; i++)
			{
				Vector2 axis = axis2D[i];
				axis.Normalize();
				float length = abs(axis.Dot(axis2D[2]));

				float sum = 0.0f;
				for (int j = 0; j < 2; j++)
				{
					sum += abs(axis.Dot(axis2D[j]));
				}
				sum += right->GetSize().x;
				if (sum < (length * 2))
					return false;
			}
			
			/*Vector2 startPercent = left->GetMesh()->startPercent;
			Vector2 endPercent = left->GetMesh()->endPercent;
			if (startPercent != Vector2::One || endPercent != Vector2::One)
			{
				std::vector<Vector2> leftLine;
				leftLine.push_back((Vector2(1.0f, (endPercent.y -startPercent.y) * 0.5f) ));
				leftLine.push_back((Vector2(1.0f, (endPercent.x - startPercent.x) * 0.5f) ));

				std::vector<Vector2> leftLinePoint;
				leftLinePoint.push_back(Vector2{ -0.5f, (startPercent.y) * 0.5f });
				leftLinePoint.push_back(Vector2{ -0.5f, (startPercent.x) * 0.5f });

				for (int i = 0; i < 2; i++)
				{
					math::Vector2::rotation(leftLine[i], leftRotation);
					math::Vector2::rotation(leftLinePoint[i], leftRotation);
					leftLinePoint[i] = leftPos + leftLinePoint[i] * Vector2(leftScale.x, leftScale.y);
				}

				Vector2 rightToLeftLine1 = rightPos - leftLinePoint[0];
				Vector2 rightToLeftLine2 = rightPos - leftLinePoint[1];

				float rightCross1 = rightToLeftLine1.x * leftLine[0].y - rightToLeftLine1.y * leftLine[0].x;
				float rightCross2 = rightToLeftLine2.x * 
					leftLine[1].y - rightToLeftLine2.y * leftLine[1].x;
				if(rightCross1 < 0.0f || rightCross2 > 0.0f)
					return false;
			}*/

			return HeightCheck(left, right);
		}
	}
	bool CollisionManager::HeightCheck(Collider2D* left, Collider2D* right)
	{
		if (left->GetCollisionRange().x <= right->GetCollisionRange().y &&
			right->GetCollisionRange().x <= left->GetCollisionRange().y)
			return true;
		else
			return false;
	}
	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}
	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
}
