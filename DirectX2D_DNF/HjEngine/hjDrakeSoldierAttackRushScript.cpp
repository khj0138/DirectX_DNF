#include "hjDrakeSoldierAttackRushScript.h"
#include "hjTime.h"

#include "hjAttackScriptManager.h"

#include "hjDrakeSoldierAttackRushObjectScript.h"
#include "hjAttackEffectScript.h"
#include "hjTransform.h"
#include "hjAnimator.h"
#include "hjMonsterScript.h"
#include "hjGameObject.h"

#include "hjGraphics.h"
#include "hjCollider2D.h"
#include "hjRigidBody.h"

namespace hj
{

	DrakeSoldierAttackRushScript::DrakeSoldierAttackRushScript()
	{
	}
	DrakeSoldierAttackRushScript::~DrakeSoldierAttackRushScript()
	{
	}
	void DrakeSoldierAttackRushScript::Initialize()
	{
		SetCoolTime(15.0f);
		RegisterAttackObject<DrakeSoldierAttackRushObjectScript>(L"DrakeSoldierAttackRush");
		AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");
		//DragonSoldierAttackRush1->GetOwner()->GetComponent<Transform>()->SetRotation2D(45);
		RegisterEffectObject<AttackEffectScript>(L"AttackEffect");
		EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
		AttackEffectScript* AttackEffectObject = dynamic_cast<AttackEffectScript*>(AttackEffect);
		if (AttackEffectObject != nullptr)
		{
			AttackEffectObject->SetMesh(AttackEffectScript::AtkEffectType::Rect);
		}
		AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(50.0f, 50.0f, 1.0f));
		AttackEffect->SetCastingTime(1.0f);
	}
	void DrakeSoldierAttackRushScript::Update()
	{
		//if (GetActivate())
		if (GetActivate())
		{
			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->IsComplete() && activeAnim->GetKey() == L"drake_soldierAttackRush")
			{

				AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");
				DrakeSoldierAttackRush->SetFinTime(DrakeSoldierAttackRush->GetFinTime() + Time::DeltaTime());
				if (DrakeSoldierAttackRush->GetFinTime() >= 0.2f)
				{
					DrakeSoldierAttackRush->GetOwner()->SetState(GameObject::eState::Paused);
					DrakeSoldierAttackRush->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
					DrakeSoldierAttackRush->SetAttack(false);

					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);

					SetActivate(false);

					DrakeSoldierAttackRush->SetFinTime(0.0f);
					return;

				}
			}
			else if (activeAnim->GetKey() != L"drake_soldierAttackRush")
			{
				AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");

				DrakeSoldierAttackRush->GetOwner()->SetState(GameObject::eState::Paused);
				DrakeSoldierAttackRush->GetOwner()->GetComponent<Collider2D>()->SetCollision(false);
				DrakeSoldierAttackRush->SetAttack(false);

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
				AttackEffect->SetCurTime(0.0f);

				SetActivate(false);

				DrakeSoldierAttackRush->SetFinTime(0.0f);
				return;

			}
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() >= 2)
			{
				Transform* tr = GetOwner()->GetComponent<Transform>();

				AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");
				

				DrakeSoldierAttackRush->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
				DrakeSoldierAttackRush->GetOwner()->GetComponent<Transform>()->SetVirtualZ(tr->GetVirtualZ());
				if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 2)
				{
					DrakeSoldierAttackRush->GetOwner()->SetFlip(GetOwner()->GetFlip());
					DrakeSoldierAttackRush->GetOwner()->SetState(GameObject::eState::Active);
					DrakeSoldierAttackRush->GetOwner()->GetComponent<Collider2D>()->SetCollision(true);
					DrakeSoldierAttackRush->SetAttack(true);
					DrakeSoldierAttackRush->SetFinTime(0.0f);


					Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
					Collider2D* col = DrakeSoldierAttackRush->GetOwner()->GetComponent<Collider2D>();

					Vector3 velocity = rb->GetVelocity();
					Vector2 rushDirection = Vector2(velocity.x, velocity.z);
					rushDirection.Normalize();
					float rushRadian = atan2(1.0f * rushDirection.y, rushDirection.x);


					Vector2 center = Vector2(50.0f, 0.0f);
					math::Vector2::rotation(center, 1.0f * rushRadian);
					col->SetRotation(rushRadian);
					if (GetOwner()->GetFlip())
					{
						center.x *= -1.0f;
					}

					col->SetCenter(center);




					EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
					AttackEffect->GetOwner()->SetState(GameObject::eState::Paused);
					AttackEffect->SetCurTime(0.0f);
				}
			}
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetIndex() == 1)
			{
				float sec45 = 1.4f;

				Vector3 targetPos = GetManager()->GetTargetPos();
				float targetPosVZ = GetManager()->GetTargetPosVZ();

				/*EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(targetPos);
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(targetPosVZ);*/

				Vector2 targetPos2D = Vector2(targetPos.x, targetPosVZ);

				Collider2D* col = GetOwner()->GetComponent<Collider2D>();
				Vector3 colPos = col->GetPosition();
				Vector3 colSize = col->GetSize();
				colPos.y -= colSize.y / 2.0f * sec45;

				Vector2 colPos2D = Vector2(colPos.x, colPos.y);

				Vector2 direction = targetPos2D - colPos2D;

				EffectObjectScript* AttackEffect = LoadEffectObject(L"AttackEffect");

				Vector3 scale = AttackEffect->GetOwner()->GetComponent<Transform>()->GetScale();
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(direction.x, scale.y, 1.0f));
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(colPos2D.x + direction.x / 2.0f,0.0f, 1.0f));
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetVirtualZ(colPos2D.y + direction.y / 2.0f );
				AttackEffect->GetOwner()->SetState(GameObject::eState::Active);

				direction.Normalize();
				float rushRadian = atan2(1.0f * direction.y, direction.x);
				AttackEffect->GetOwner()->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, rushRadian));

			}
		}
		AttackScript::Update();
	}

	void DrakeSoldierAttackRushScript::Reset()
	{
		AttackScriptManager* manager = GetManager();

		MonsterScript* monster = GetOwner()->FindScript<MonsterScript>();
		GameObject* target = monster->GetTarget();
		if (monster != nullptr)
		{
			GameObject* player = monster->GetTarget();
			if (player == nullptr)
			{
				SetActivate(false);
				return;
			}
			manager->SetTargetColPos(target);

			AttackObjectScript* DrakeSoldierAttackRush = LoadAttackObject(L"DrakeSoldierAttackRush");
			DrakeSoldierAttackRush->clearTargets();


		}
	}

	void DrakeSoldierAttackRushScript::SetActivate(bool activate)
	{
		AttackScript::SetActivate(activate);
		if (GetActivate() && activate == true)
		{
			MonsterScript* monster = GetOwner()->FindScript<MonsterScript>();
			if (monster != nullptr)
			{
				GameObject* player = monster->GetTarget();

				if (player != nullptr)
				{
					Vector3 playerPos = player->GetComponent<Transform>()->GetPosition();
					float playerVZ = player->GetComponent<Transform>()->GetVirtualZ();
					Vector2 playerPos2D = Vector2(playerPos.x, playerVZ);

					Vector3 monsterPos = monster->GetOwner()->GetComponent<Transform>()->GetPosition();
					float monsterVZ = monster->GetOwner()->GetComponent<Transform>()->GetVirtualZ();
					Vector2 monsterPos2D = Vector2(monsterPos.x, monsterVZ);

					float dist = Vector2::Distance(playerPos2D, monsterPos2D);
					if (dist > 340.0f)
						AttackScript::SetActivate(false);
					return;
				}
			}
		}
	}


}
