#pragma once
#include "Base/UI/UIBase.hpp"
#include "Base/Player/Player.hpp"

namespace Dungeon
{
	//Ui element that displayes set of player stats such as health, mana,strenght,defence, etc.
	class CPlayerStatsUI : public Engine::UI::CUIBase
	{
	protected:
		Engine::UI::CUIBase* healthText = nullptr;

		Engine::UI::CUIBase* manaText = nullptr;

		Engine::UI::CUIBase* defenceText = nullptr;

		Engine::UI::CUIBase* strenghtText = nullptr;
	public:
		CPlayerStatsUI(CPlayer*player, String name = "UI", String displayName = "", Vector location = Vector(0, 0), Vector size = Vector(0, 0));

		CPlayer* Player = nullptr;

		//Update Stats
		virtual void ProccessInput(int)override;

		virtual bool Valid()const override;
	};
}


