#include "hjBasicAttackScript2.h"
#include "hjTime.h"

#include "hjBasicAttackObject2Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"
namespace hj
{

	BasicAttackScript2::BasicAttackScript2()
	{
	}
	BasicAttackScript2::~BasicAttackScript2()
	{
	}
	void BasicAttackScript2::Initialize()
	{

		RegisterAttackObject<BasicAttackObject2Script>(L"BasicAttack2");
		LoadAttackObject(L"BasicAttack2")->GetComponent<Transform>()->SetPosition(Vector3(100.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript2::Update()
	{
		AttackScript::Update();
	}
	void BasicAttackScript2::Reset()
	{
		Vector2 pos = GetPos();
		float posVZ = GetPosVZ();

		AttackObject* BasicAttack2 = LoadAttackObject(L"BasicAttack2");
		BasicAttack2->SetPos(Vector3{ pos.x, pos.y, 1.0f });
		BasicAttack2->SetPosVZ(posVZ);
	}
}
