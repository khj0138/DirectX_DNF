#include "hjRigidbody.h"
#include "hjTime.h"
#include "hjGameObject.h"
#include "hjTransform.h"
#include "hjApplication.h"

extern hj::Application application;
namespace hj
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector3::Zero)
		, mAccelation(Vector3::Zero)
		, mVelocity(Vector3::Zero)
	{
		mLimitedVelocity.x = 500.0f;
		mLimitedVelocity.y = 1000.0f;
		//mbGround = false;
		mbGround = true;
		mGravity = Vector3(0.0f, -2000.0f, 0.0f);
		mbGravity = true;
		mFriction = 100.0f;
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Initialize()
	{
		fixedRes = (float)application.GetFixedWidth() / 800.f;
	}

	void Rigidbody::Update()
	{
		
		if (mbGround)
		{
			// ������ ������
			Vector3 gravity = mGravity;
			gravity.Normalize();

			
			float dot = math::Vector3::Dot3D(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			if (mbGravity)
				mVelocity += mGravity * Time::DeltaTime();
		}

		// �߷°��ӵ� �ִ� �ӵ� ����
		Vector3 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Vector3::Dot3D(mVelocity, gravity);
		gravity = gravity * dot;
		//Vector2 sideVelocity = mVelocity - gravity;

		if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
			mVelocity.y = gravity.y;
		}

		/*if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}*/

		// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	//�ӵ��� �ݴ�������� �������� ����ȴ�.
		//	Vector2 friction = mVelocity * (-1.f);
		//	friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

		//	//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���

		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		mVelocity += friction;
		//	}
		//}

		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		/*Vector3 vel = mVelocity;
		vel.x *= Time::DeltaTime();
		vel.x *= Time::DeltaTime();*/
		Vector3 velocity = mVelocity;
		velocity.z = 0.0f;
		velocity;// *= fixedRes;
		pos = pos + velocity * Time::DeltaTime();
		tr->SetVirtualZ(tr->GetVirtualZ() + mVelocity.z * Time::DeltaTime());
		if (pos.y < -2.0f)
		{
			pos.y = 0.0f;
			SetGround(true);
		}

		//if (!mbGravity)
		//	pos = pos + mVelocity;
		//else
		//{
		//	//pos = pos + mVelocity * 0.015f;
		//	if (Time::DeltaTime() > 0.08f)
		//		pos = pos + mVelocity * 0.08f;
		//	/*else if (Time::DeltaTime() < 0.015f)
		//		pos = pos + mVelocity * 0.015f;*/
		//	else
		//		pos = pos + mVelocity * Time::DeltaTime();

		//}
		//pos = pos + mVelocity * (Time::DeltaTime() > 1.0f ? 1.0f : Time::DeltaTime());
		tr->SetPosition(pos);
		//mForce.Clear();
	}
}