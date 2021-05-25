#include "PlayerStatsUI.hpp"
#include <string>
#include "World.h"
#include "Base/Types/Types.hpp"

Dungeon::CPlayerStatsUI::CPlayerStatsUI(Dungeon::CPlayer* player, String name, String displayName, Vector location , Vector size)
	:Player(player),CUIBase(name,displayName,location,size,true)
{
	if (player)
	{
		healthText = player->World->CreateUI<Engine::UI::CUIBase>(this, "healthText", "Health: " + STRING(Player->Health), Vector(1, 1), Vector(0, 0), false);
		manaText = player->World->CreateUI<Engine::UI::CUIBase>(this, "manaText", "Mana: " + STRING(Player->Mana), Vector(1, 2), Vector(0, 0), false);
		defenceText = player->World->CreateUI<Engine::UI::CUIBase>(this, "defenceText", "Defence: " + STRING(Player->Defence), Vector(1, 3), Vector(0, 0), false);
		strenghtText = player->World->CreateUI<Engine::UI::CUIBase>(this, "strenghtText", "Stenght: " + STRING(Player->Strenght), Vector(1, 4), Vector(0, 0), false);
	}
}

void Dungeon::CPlayerStatsUI::ProcessInput(int)
{
	healthText->DisplayName = "Health: " + STRING(Player->Health);

	manaText->DisplayName = "Mana: " + STRING(Player->Mana);

	defenceText->DisplayName = "Defence: " + STRING(Player->Defence);

	strenghtText->DisplayName = "Stenght: " + STRING(Player->Strenght);
}

bool Dungeon::CPlayerStatsUI::Valid() const
{
	return Player && !pendingKill;
}
