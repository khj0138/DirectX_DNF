#include "hjAttackObjectScript.h"

#include "hjAttackScriptManager.h"
#include "hjTime.h"
#include "hjInput.h"
#include "hjCamera.h"
#include "hjResources.h"

#include "hjGameObject.h"
//#include "hjMonsterScript.h"


#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjRigidbody.h"
#include "hjCollider2D.h"
#include "hjMeshRenderer.h"

#include "hjPlayerScript.h"
#include "hjMonsterScript.h"
//#include "hjAttackScript.h"

namespace hj
{

	AttackObjectScript::AttackObjectScript(AttackObjectType attackObjectType)
		: mType((AttackObjectType)attackObjectType)
		, bActivate(false)
		, mCoolTime(0.0f)
		, mVelocity(Vector2::Zero)
		, animOffset(Vector2::Zero)
		, mAnimator(nullptr)
		, mFinTime(0.0f)
		, mStartPercent(Vector2::One)
		, mEndPercent(Vector2::One)
		, mCenterPercent(0.0f)
	{
	}
	AttackObjectScript::~AttackObjectScript()
	{
	}
	void AttackObjectScript::Initialize()
	{
		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->GetMesh()->setRectPercent(mStartPercent, mEndPercent);
		GetOwner()->AddComponent<Rigidbody>();
		if (GetOwner()->GetComponent<Animator>() == nullptr)
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		}
		else
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		}

		
	}
	void AttackObjectScript::Update()
	{
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 vel = rb->GetVelocity();
		pos.x += vel.x;
		tr->SetPosition(pos);
		tr->SetVirtualZ(tr->GetVirtualZ() + rb->GetVelocity().y);*/
		if (GetCoolTime() != 0.0f)
		{
			for (auto& iter : targets)
			{
				float a = Time::DeltaTime();
				iter.second += Time::DeltaTime();
			}
		}
		Script::Update();
	}

	void AttackObjectScript::OnCollisionEnter(Collider2D* other)
	{
		
	}

	void AttackObjectScript::OnCollisionStay(Collider2D* other)
	{
		
	}

	void AttackObjectScript::OnCollisionExit(Collider2D* other)
	{
	}

	
	void AttackObjectScript::Attack(Script* target)
	{
		Collider2D* attackCol = GetOwner()->GetComponent<Collider2D>();
		Collider2D* targetCol = target->GetOwner()->GetComponent<Collider2D>();
		if (attackCol->GetType() == eColliderType::Rect)
		{
			Vector2 startPercent = attackCol->GetMesh()->startPercent;
			Vector2 endPercent = attackCol->GetMesh()->endPercent;
			if (startPercent != Vector2::One || endPercent != Vector2::One)
			{
				Vector2 attackPos = Vector2(attackCol->GetPosition().x, attackCol->GetPosition().y);
				Vector3 attackScale = attackCol->GetSize();
				float attackRotation = attackCol->GetObjectRotation().z + attackCol->GetRotation();

				Vector2 targetPos = Vector2(targetCol->GetPosition().x, targetCol->GetPosition().y);
			
				std::vector<Vector2> attackLine;
				attackLine.push_back((Vector2(1.0f, (endPercent.y - startPercent.y) * 0.5f)));
				attackLine.push_back((Vector2(1.0f, (endPercent.x - startPercent.x) * 0.5f)));

				std::vector<Vector2> attackLinePoint;
				attackLinePoint.push_back(Vector2{ -0.5f, (startPercent.y) * 0.5f });
				attackLinePoint.push_back(Vector2{ -0.5f, (startPercent.x) * 0.5f });

				for (int i = 0; i < 2; i++)
				{
					math::Vector2::rotation(attackLine[i], attackRotation);
					math::Vector2::rotation(attackLinePoint[i], attackRotation);
					attackLinePoint[i] = attackPos + attackLinePoint[i] * Vector2(attackScale.x, attackScale.y);
				}

				Vector2 targetToAttackLine1 = targetPos - attackLinePoint[0];
				Vector2 targetToAttackLine2 = targetPos - attackLinePoint[1];

				float targetCross1 = targetToAttackLine1.x * attackLine[0].y - targetToAttackLine1.y * attackLine[0].x;
				float targetCross2 = targetToAttackLine2.x *
					attackLine[1].y - targetToAttackLine2.y * attackLine[1].x;
				if (targetCross1 < 0.0f || targetCross2 > 0.0f)
					return;
			}
		}

		else if (attackCol->GetType() == eColliderType::Circle)
		{
			float startPercent = attackCol->GetMesh()->startPercent.y;
			//float endPercent = attackCol->GetMesh()->endPercent.x;
			if (startPercent != 1.0f)// || endPercent != 1.0f)
			{
				Vector2 attackPos = Vector2(attackCol->GetPosition().x, attackCol->GetPosition().y);
				Vector3 attackScale = attackCol->GetSize();
				float attackRotation = attackCol->GetObjectRotation().z + attackCol->GetRotation();
				
				float attackRadius = attackCol->GetSize().x * 0.5f;
				float targetRadius = targetCol->GetSize().x * 0.5f;

				Vector3 temp = attackCol->GetPosition() - targetCol->GetPosition();
				Vector2 temp2D = Vector2{ temp.x,temp.y };
				float length = temp2D.Length() * 2.0f;

				if (length < (attackRadius * startPercent))// || length > (attackRadius * endPercent))
					return;
			}
		}
		UINT damage = mStatus.Damage;
		Vector2 direction = mStatus.Direction;
		float time = Time::DeltaTime();
		while (time < 1.0f)
		{
			time *= 10.0f;
		}
		time = time - ((UINT)time % 10);
		float randomDamage = time * (float)(mStatus.DamageRange);
		damage += (UINT)randomDamage;
		

		
		if (mType == AttackObjectType::Player)
		{
			Vector3 playerPos = GetManager()->GetManagerOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 monsterPos = target->GetOwner()->GetComponent<Transform>()->GetPosition();
			MonsterScript* monster = dynamic_cast<MonsterScript*>(target);
			if (monster != nullptr)
			{
				bool flip = true;
				if (playerPos.x < monsterPos.x)
					flip = false;
				monster->Hit(damage, flip, direction);
				return;
			}
		}
		else if (mType == AttackObjectType::Monster)
		{
			Vector3 monsterPos = GetManager()->GetManagerOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 playerPos = target->GetOwner()->GetComponent<Transform>()->GetPosition();
			PlayerScript* player = dynamic_cast<PlayerScript*>(target);
			if (player != nullptr)
			{
				bool flip = true;
				if (monsterPos.x < playerPos.x)
					flip = false;
				player->Hit(damage, flip, direction);
				return;
			}
		}
	}
	void AttackObjectScript::SetPause()
	{
		GetOwner()->SetState(GameObject::eState::Paused);
		GetOwner()->GetComponent<Collider2D>()->GetMesh()->SetActivate(false);
	}
	void AttackObjectScript::SetPosCol(GameObject* object)
	{
		float sec45 = 1.4f;
		Transform* tr = object->GetComponent<Transform>();
		Collider2D* objCol = object->GetComponent<Collider2D>();
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		Vector2 center = col->GetCenter();
		Vector3 objColPos = objCol->GetPosition();
		Vector3 objColSize = objCol->GetSize();
		Vector2 objColCenter = objCol->GetCenter();
		if (object->GetFlip())
		{
			objColCenter.x = objColCenter.x * -1.0f;
		}
		GetOwner()->SetFlip(object->GetFlip());
		//objColPos.y -= objColSize.y / 2.0f * sec45;
		GetOwner()->GetComponent<Transform>()->SetVirtualZ(objColPos.y);
		objColPos.x -= objColCenter.x + center.x;
		objColPos.y = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetPosition(objColPos);
		GetOwner()->GetComponent<Transform>()->SetRotation(tr->GetRotation());
	}
	void AttackObjectScript::SetDefaultPercent(Vector2 start, Vector2 end)
	{
		start.x *= -1.0f;
		end.x *= -1.0f;
		mStartPercent = start;
		mEndPercent = end;
		DebugMesh* colMesh = GetOwner()->GetComponent<Collider2D>()->GetMesh();
		colMesh->setRectPercent(mStartPercent, mEndPercent);
	}
	void AttackObjectScript::SetCenterPercent(float center)
	{
		center *= -1.0f;
		mCenterPercent = center;
		Vector2 start = Vector2(mStartPercent.x + center, mStartPercent.y + center);
		Vector2 end = Vector2(mEndPercent.x + center, mEndPercent.y + center);
		DebugMesh* colMesh = GetOwner()->GetComponent<Collider2D>()->GetMesh();
		colMesh->setRectPercent(start, end);
	}
}
