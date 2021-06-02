#include "Player.hpp"
#include "Base/Pawns/Pawn.hpp"
#include "World.h"
#include "Base/UI/UIBase.hpp"

#include <string>
#include "Base/Render/RenderMacros.h"


void Dungeon::CPlayer::UpdateItemUI(int id)
{
	inventoryFrame->ChildrenUI[id]->DisplayName = String(Items[id].DisplayName + " x " + STRING(Items[id].CurrentAmount));
}

void Dungeon::CPlayer::RemoveUIItem(String name, int id)
{
	if (inventoryFrame->ChildrenUI.valid_index(id))
	{ 
		inventoryFrame->ChildrenUI[id]->Destroy();
		inventoryFrame->ChildrenUI.erase(inventoryFrame->ChildrenUI.begin() + id); 
	}
}

void Dungeon::CPlayer::generateTargetList()
{
	//reset the value
	currentTargetSelectionId = 0;
	if (World)
	{
		for (auto it = World->Objects.begin(); it != World->Objects.end(); ++it)
		{
			(*it)->OnDestroyed.UnBind((static_cast<void(Engine::CBaseObject::*)(Engine::CBaseObject*)>(&CPlayer::onObjectFromTargetListDestoryed)), this);
		}
		targetList.clear();
		target = nullptr;


		for (auto it = World->Objects.begin(); it != World->Objects.end(); ++it)
		{
			if ((*it)->Location.Distance(Location) <= 2/*Range will be defined by player's weapon ,but will rarely go above 4*/
				&& (*it) != this
				&& (*it)->Faction == Engine::EFaction::EnemyOfAll)
			{
				targetList.push_back(*it);
				(*it)->OnDestroyed.Bind((static_cast<void(Engine::CBaseObject::*)(Engine::CBaseObject*)>(&CPlayer::onObjectFromTargetListDestoryed)), this);
			}
		}

		if (targetList.empty())
		{
			currentTargetSelectionId = -1;
		}
		selectNewTarget();
	}

}

void Dungeon::CPlayer::selectNewTarget()
{
	if (currentTargetSelectionId != -1)
	{
		try
		{
			if (target)
			{
				target->SetSelected(false);
			}
		}
		catch (const std::exception&)
		{
			target = nullptr;
		}
		
		if (targetList.valid_index(currentTargetSelectionId))
		{
			//World objects MUST never have faction of "EnemyOfAll"
			target = static_cast<Engine::CPawn*>(targetList[currentTargetSelectionId]);
			target->SetSelected(true);
		}
	}
	else
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

void Dungeon::CPlayer::onObjectFromTargetListDestoryed(CBaseObject* obj)
{
	if (obj == this->target)
	{
		target = nullptr;
	}
	targetList.erase(std::find(targetList.begin(), targetList.end(), obj));
	selectNewTarget();
}

Dungeon::CPlayer::CPlayer(Engine::UI::CUIBase* _inventoryFrame)
	:Engine::CPawn('@'),inventoryFrame(_inventoryFrame)
{
	Faction = Engine::EFaction::Player;
	UpdateType = Engine::EUpdateType::EventOnly;
	Health = 10;

	OnItemCountUpdatedEvent.Bind(static_cast<void(Engine::CBaseObject::*)(int)>(&CPlayer::UpdateItemUI),this);
	OnItemRemovedEvent.Bind(static_cast<void(Engine::CBaseObject::*)(String, int)>(&CPlayer::RemoveUIItem),this);
}

bool Dungeon::CPlayer::AddItem(Engine::Item item, int& amountLeft, int& resultId, bool auto_eqiup)
{
	bool res = CPawn::AddItem(item, amountLeft, resultId);
	//if we have less items that we had in the start
	if (amountLeft != item.CurrentAmount && (amountLeft > 0 || resultId != -1))
	{
		if (World)
		{
			World->CreateUI<Engine::UI::CUIBase>(
				inventoryFrame,
				item.name + "_ui",
				String(item.DisplayName + " x " + STRING(item.CurrentAmount)),
				Engine::Vector(1, 1 + (resultId == -1 ? 0 : resultId)),
				Engine::Vector(0, 0), false);
		}
	}

	return res;
}

void Dungeon::CPlayer::ProcessInput(int input)
{
	
	if(INPUT_SYSTEM["left"])
	{
		Move(Engine::Vector(-1, 0));
		World->GameplayUpdate = true;
		generateTargetList();
	}
	if(INPUT_SYSTEM["right"])
	{
		Move(Engine::Vector(1, 0));
		World->GameplayUpdate = true;
		generateTargetList();
	}
	if (INPUT_SYSTEM["down"])
	{
		Move(Engine::Vector(0, 1));
		World->GameplayUpdate = true;
		generateTargetList();
	}
	if (INPUT_SYSTEM["up"])
	{
		Move(Engine::Vector(0, -1));
		World->GameplayUpdate = true;
		generateTargetList();
	}
	if (INPUT_SYSTEM["attack"])
	{
		if (target)
		{
			target->ReceiveDamage(1, this);
			flash();
		}
		World->GameplayUpdate = true;
	}
	if (INPUT_SYSTEM["prev_target"])
	{
		//select prev enemy
		//this action does not cause game to update
		currentTargetSelectionId--;
		if (currentTargetSelectionId < 0)
		{
			currentTargetSelectionId = targetList.size() - 1;
		}
		selectNewTarget();
	}
	if (INPUT_SYSTEM["nexr_target"])
	{
		//select next enemy
		//this action does not cause game to update
		currentTargetSelectionId++;
		if (currentTargetSelectionId >= targetList.size())
		{
			currentTargetSelectionId = 0;
		}
		selectNewTarget();
	}
}

void Dungeon::CPlayer::Update()
{
	CPawn::Update();
}

void Dungeon::CPlayer::OnItemCountUpdated(int id)
{
	CPawn::OnItemCountUpdated(id);
}
