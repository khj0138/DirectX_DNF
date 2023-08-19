#include "hjBasicAttackScript1.h"
#include "hjTime.h"

#include "hjBasicAttackObject1Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"
namespace hj
{

	BasicAttackScript1::BasicAttackScript1()
	{
	}
	BasicAttackScript1::~BasicAttackScript1()
	{
	}
	void BasicAttackScript1::Initialize()
	{
		RegisterAttackObject<BasicAttackObject1Script>(L"BasicAttack1");
		LoadAttackObject(L"BasicAttack1")->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript1::Update()
	{

		AttackScript::Update();
	}

	void BasicAttackScript1::Reset()
	{
		Vector2 pos = GetPos();
		float posVZ = GetPosVZ();

		AttackObject* BasicAttack1 = LoadAttackObject(L"BasicAttack1");
		BasicAttack1->SetPos(Vector3{ pos.x, pos.y, 1.0f });
		BasicAttack1->SetPosVZ(posVZ);
	}

}
