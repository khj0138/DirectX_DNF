#include "hjBasicAttackScript3.h"
#include "hjTime.h"

#include "hjBasicAttackObject3Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"
namespace hj
{

	BasicAttackScript3::BasicAttackScript3()
	{
	}
	BasicAttackScript3::~BasicAttackScript3()
	{
	}
	void BasicAttackScript3::Initialize()
	{
		RegisterAttackObject<BasicAttackObject3Script>(L"BasicAttack3");
		LoadAttackObject(L"BasicAttack3")->GetComponent<Transform>()->SetPosition(Vector3(150.0f, 0.0f, 1.0f));

	}
	void BasicAttackScript3::Update()
	{
		AttackScript::Update();
	}
	void BasicAttackScript3::Reset()
	{
		Vector2 pos = GetPos();
		float posVZ = GetPosVZ();

		AttackObject* BasicAttack3 = LoadAttackObject(L"BasicAttack3");
		BasicAttack3->SetPos(Vector3{ pos.x, pos.y, 1.0f });
		BasicAttack3->SetPosVZ(posVZ);
	}

}
