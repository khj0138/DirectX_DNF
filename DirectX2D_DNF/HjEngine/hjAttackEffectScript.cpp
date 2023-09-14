#include "hjAttackEffectScript.h"

#include "hjAttackScriptManager.h"
#include "hjTime.h"

#include "hjTransform.h"
#include "hjCollider2D.h"
#include "hjPlayerScript.h"
#include "hjGameObject.h"
#include "hjResources.h"

#include "hjConstantBuffer.h"
#include "hjRenderer.h"
#include "hjMeshRenderer.h"
namespace hj
{

	AttackEffectScript::AttackEffectScript()
		: EffectObjectScript(effectType::Mesh)
	{

	}
	AttackEffectScript::~AttackEffectScript()
	{
	}
	void AttackEffectScript::Initialize()
	{
		EffectObjectScript::Initialize();

		GetOwner()->SetState(GameObject::eState::Paused);
		SetAnimate(false);
		
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

	}
	void AttackEffectScript::Update()
	{
		float time = GetCurTime() + Time::DeltaTime();
		float castingTime = GetCastingTime();
		if (time > castingTime)
		{
			time = castingTime;
		}
		SetCurTime(time);

		renderer::AtkEffectCB AtkEffectObj = {};
		AtkEffectObj.type = (UINT)mType;
		AtkEffectObj.startPercent = 1.0f;
		AtkEffectObj.endPercent = 1.0f;
		/*if (mType == AtkEffectType::Rect)
		{
			AtkEffectObj.startPercent = mStartPercent;
			AtkEffectObj.endPercent = mEndPercent;
		}*/
		AtkEffectObj.curPercent = GetCurTime() / GetCastingTime();
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::AtkEffect];
		cb->SetData(&AtkEffectObj);
		cb->Bind(eShaderStage::PS);
	}

	void AttackEffectScript::SetMesh(AtkEffectType type)
	{
		mType = type;
		if (mType == AtkEffectType::Circle)
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"AttackCircle"));
			mr->SetMaterial(Resources::Find<Material>(L"AttackCircleMaterial"));
		}
		else if (mType == AtkEffectType::Rect)
		{
			MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"AttackRect"));
			mr->SetMaterial(Resources::Find<Material>(L"AttackRectMaterial"));
		}
	}
	
}
