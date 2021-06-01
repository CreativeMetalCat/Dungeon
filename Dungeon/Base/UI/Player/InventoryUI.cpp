#include "InventoryUI.hpp"
#include "World.h"

void Dungeon::CInventoryUI::changeSelection(int selectionId)
{
	//same as ChildrenUI.size() > selectionId && selectionId > -1
	if (ChildrenUI.valid_index(selectionId))
	{
		if (ChildrenUI.valid_index(currentSelection))
		{
			ChildrenUI[currentSelection]->ChangeState(false);
		}
		ChildrenUI[selectionId]->ChangeState(true);
		currentSelection = selectionId;
	}
}

void Dungeon::CInventoryUI::ProcessInput(int input)
{
	if (owningPlayer)
	{
		/*
		Small explanation of how this system works
		keys 1-2 change current selection
		key 3 - drops currently selected item
		key 4 - use current item
		*/
		switch (input)
		{
		case '1':
		{
			changeSelection(currentSelection > 0 ? currentSelection - 1 : owningPlayer->GetCurrentItemCount() - 1);
			break;
		}
		case '2':
			changeSelection(currentSelection < owningPlayer->GetCurrentItemCount() - 1 ? currentSelection + 1 : 0);
			break;
		case '3':
			/*
			Dropping item is done in n steps
			* 1) Check if we have this item
			* 2) Check if there is a place to spawn item pickup object in 1 unit radius
			* 3) Check if there is a item pick up with same item type that can fit more items
			* 4.1) If there is -> add to it
			* 4.2) If there is not -> spawn new one
			*/
			bool has;
			owningPlayer->GetItem(currentSelection, has);
			if (has)
			{
				bool has_empty_space = true;
				//this iteration idea will be slow no matter which way you look
				//but it's easiest to use and change and dropping operation would not be called a lot anyway
				for (auto it = owningPlayer->World->Objects.begin(); it != owningPlayer->World->Objects.end(); ++it)
				{
					if ((*it)->Location.Distance(owningPlayer->Location) <= 1)
					{
						has_empty_space = false;
						break;
					}
				}
			}
			break;
		case '4':
		{	
			//We need to equip/consume the item
			//first the equippement
			bool has = false;
			Engine::Item item = owningPlayer->GetItem(currentSelection, has);
			//check if id is valid
			if (has)
			{
				if (item.ItemType == Engine::Item::EItemType::Equippable)
				{
					owningPlayer->EquipItem(currentSelection);
				}
				if (item.ItemType == Engine::Item::EItemType::Consumable)
				{
					owningPlayer->ConsumeItem(currentSelection);
				}
			}
			break;
		}
		default:
			break;
		}
	}
}
