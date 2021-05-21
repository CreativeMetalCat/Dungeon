#include "Player.hpp"
#include "Base/Pawns/Pawn.hpp"
#include "World.h"
#include "Base/UI/UIBase.hpp"

#include <string>
#include "Base/Render/RenderMacros.h"

Dungeon::CPlayer::CPlayer(Engine::UI::CUIBase* _inventoryFrame) 
	:Engine::CPawn('@'),inventoryFrame(_inventoryFrame)
{
	Faction = Engine::EFaction::Player;
	UpdateType = Engine::EUpdateType::EventOnly;
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
	case KEY_LEFT:
	{
		Move(Engine::Vector(-1, 0));
		World->GameplayUpdate = true;
		break;
	}
	case KEY_RIGHT:
	{
		Move(Engine::Vector(1, 0));
		World->GameplayUpdate = true;
		break;
	}
	case KEY_DOWN:
	{
		Move(Engine::Vector(0, 1));
		World->GameplayUpdate = true;
		break;
	}
	case KEY_UP:
	{
		Move(Engine::Vector(0, -1));
		World->GameplayUpdate = true;
		break;
	}
	case ' ':
	{
		if (target)
		{
			target->ReceiveDamage(1, this);
			flash();
		}
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
	//find enemies in range and select the first one
	Array<CBaseObject*>::iterator it = std::find_if(World->Objects.begin(), World->Objects.end(),
		[this](CBaseObject* obj)
		{
			return
				obj->Location.Distance(Location) <= 2/*Range will be defined by player's weapon ,but will rarely go above 4*/
				&& obj != this
				&& obj->Faction == Engine::EFaction::EnemyOfAll;
		}
	);
	if (it != World->Objects.end() && (*it) != target)
	{
		if (target)
		{
			target->SetSelected(false);
		}
		//World objects MUST never have faction of "EnemyOfAll"
		target = static_cast<Engine::CPawn*>(*it);
		target->SetSelected(true);
	}
	else if (it == World->Objects.end())
	{
		if (target && target->Valid())
		{
			target->SetSelected(false);
			target = nullptr;
		}
		else
		{
			target = nullptr;
		}
	}
}
