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
		}
		else
		{
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하고 있다가 나갈떄
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
		}
	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		if (left->GetType() == eColliderType::Rect)
		{
			if (right->GetType() == eColliderType::Rect)
			{
				Vector3 leftScale = left->GetTransform()->GetScale();
				float leftRotation = left->GetTransform()->GetRotation().z;
				Vector3 rightScale = right->GetTransform()->GetScale();
				float rightRotation = right->GetTransform()->GetRotation().z;

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

				Vector3 temp = left->GetTransform()->GetPosition() - right->GetTransform()->GetPosition();
				axis2D.push_back(Vector2{temp.x, temp.y});

				for (int i = 0; i < 4; i++)
				{
					Vector2 length = axis2D[4];
					Vector2 axis = axis2D[i];
					axis.Normalize();

					float sum = 0.0f;
					for (int j = 0; j < 4; j++)
					{
						sum += abs(axis.Dot(axis2D[j]));
					}
					if (sum < (length.Length() * 2))
						return false;
				}
				return true;
			}
			else if (right->GetType() == eColliderType::Circle)
			{

			}
		}
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
