#include "hjQuickStandingScript.h"
#include "hjTime.h"

#include "hjTransform.h"

#include "hjGameObject.h"
#include "hjAnimator.h"
#include "hjAnimation.h"
#include "hjRigidbody.h"
#include "hjPlayerScript.h"
namespace hj
{

	QuickStandingScript::QuickStandingScript()
	{
	}
	QuickStandingScript::~QuickStandingScript()
	{
	}
	void QuickStandingScript::Initialize()
	{

		SetCoolTime(10.0f);

	}
	void QuickStandingScript::Update()
	{
		if (GetActivate())
		{

			Animation* activeAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();
			if (activeAnim->GetKey() != L"SwordManSit")
			{
				SetPause();
			}
		}
		AttackScript::Update();
	}

	void QuickStandingScript::Reset()
	{

	}

	void QuickStandingScript::SetActivate(bool activate)
	{
		AttackScript::SetActivate(activate);
		if (GetActivate())
		{
			PlayerScript* player = GetOwner()->FindScript<PlayerScript>();
			if (player != nullptr)
			{
				PlayerScript::ePlayerState playerState = player->GetPlayerState();
				if (playerState == PlayerScript::ePlayerState::Hit)
				{
					std::vector<PlayerScript::Command> commands = player->GetCommandVector();
					int size = commands.size();
					if (size >= 1)
					{
						for (int i = 0; i < size; i++)
						{
							if (commands[i].type == PlayerScript::eCommandType::C)
							{
								return;
							}
						}

					}
				}
			}
			SetActivate(false);
		}
	}

}
