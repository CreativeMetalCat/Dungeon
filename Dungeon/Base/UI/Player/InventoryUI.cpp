#include "InventoryUI.hpp"

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
	/*
	Small explanation of how this system works
	keys 1-8 select items
	keys 9 and 0 change pages(if there are more then 8 items in inventory
	Why? Because you can not use mouse and inventory space is rather limited
	*/
	switch (input)
	{
	case '1':
	{
		changeSelection(0);
		break;
	}
	case '2':
		changeSelection(1);
		break;
	case '3':
		changeSelection(2);
		break;
	case '4':
		changeSelection(3);
		break;
	case '5':
		changeSelection(4);
		break;
	case '6':
		changeSelection(5);
		break;
	case '7':
		changeSelection(6);
		break;
	case '8':
		changeSelection(7);
		break;

	//needs better key, because enter is not relaiable
	case KEY_ENTER :case '0':
	{
		if (owningPlayer)
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
		}
		break;
	}
	default:
		break;
	}
}
