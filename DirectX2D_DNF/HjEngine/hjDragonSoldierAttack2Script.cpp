#include "hjDragonSoldierAttack2Script.h"
#include "hjTime.h"

#include "hjBasicAttackObject2Script.h"
#include "hjAttackObject.h"
#include "hjTransform.h"
namespace hj
{

	DragonSoldierAttack2Script::DragonSoldierAttack2Script()
	{
	}
	DragonSoldierAttack2Script::~DragonSoldierAttack2Script()
	{
	}
	void DragonSoldierAttack2Script::Initialize()
	{

		RegisterAttackObject<BasicAttackObject2Script>(L"BasicAttack2");
		LoadAttackObject(L"BasicAttack2")->GetComponent<Transform>()->SetPosition(Vector3(100.0f, 0.0f, 1.0f));

	}
	void DragonSoldierAttack2Script::Update()
	{
		AttackScript::Update();
	}
	void DragonSoldierAttack2Script::Reset()
	{
		Vector2 pos = GetPos();
		float posVZ = GetPosVZ();

		AttackObject* BasicAttack2 = LoadAttackObject(L"BasicAttack2");
		BasicAttack2->SetPos(Vector3{ pos.x, pos.y, 1.0f });
		BasicAttack2->SetPosVZ(posVZ);
	}
}
