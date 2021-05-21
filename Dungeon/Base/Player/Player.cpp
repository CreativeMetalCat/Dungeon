﻿#include "Player.hpp"
#include "Base/Pawns/Pawn.hpp"
#include "World.h"
#include "Base/UI/UIBase.hpp"

#include <string>
#include "Base/Render/RenderMacros.h"

Dungeon::CPlayer::CPlayer(Engine::UI::CUIBase* _inventoryFrame) 
	:Engine::CPawn('@'),inventoryFrame(_inventoryFrame)
{
	Faction = Engine::EFaction::Player;
	Health = 10;
}

bool Dungeon::CPlayer::AddItem(Engine::Item item, int& amountLeft, int& resultId)
{
	bool res = CPawn::AddItem(item, amountLeft, resultId);
	//if we have less items that we had in the start
	if (amountLeft != item.CurrentAmout)
	{
		if (World)
		{
			World->CreateUI<Engine::UI::CUIBase>(
				inventoryFrame,
				"item",
				std::string(item.DisplayName + " x " + std::to_string(item.CurrentAmout)),
				Engine::Vector(1, 2 + resultId == -1 ? 0 : resultId),
				Engine::Vector(0, 0), false);
		}
	}

	return res;
}

void Dungeon::CPlayer::ProcessInput(int input)
{
	switch (input)
	{
	case ACS_LARROW:case 260:
	{
		Move(Engine::Vector(-1, 0));
		World->GameplayUpdate = true;
		break;
	}
	case ACS_RARROW:case 261:
	{
		Move(Engine::Vector(1, 0));
		World->GameplayUpdate = true;
		break;
	}
	case ACS_DARROW:case 258:
	{
		Move(Engine::Vector(0, 1));
		World->GameplayUpdate = true;
		break;
	}
	case ACS_UARROW:case 259:
	{
		Move(Engine::Vector(0, -1));
		World->GameplayUpdate = true;
		break;
	}
	case 'g':
	{
		flash();
	}
	default:
		break;
	}
}

void Dungeon::CPlayer::Update()
{
}
