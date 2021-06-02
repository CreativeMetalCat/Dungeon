#include "InventoryUI.hpp"
#include "World.h"
#include "Base/Item/ItemPickup.hpp"
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
		if (owningPlayer->INPUT_SYSTEM["prev_item"])
		{
			changeSelection(currentSelection > 0 ? currentSelection - 1 : owningPlayer->GetCurrentItemCount() - 1);
		}
		if (owningPlayer->INPUT_SYSTEM["next_item"])
		{
			changeSelection(currentSelection < owningPlayer->GetCurrentItemCount() - 1 ? currentSelection + 1 : 0);
		}
		if (owningPlayer->INPUT_SYSTEM["drop_item"])
		{
			/*
			Dropping item is done in n steps
			* 1) Check if we have this item
			* 2) Check if there is a place to spawn item pickup object in 1 unit radius
			* 3) Check if there is a item pick up with same item type that can fit more items
			* 4.1) If there is -> add to it
			* 4.2) If there is not -> spawn new one
			*/

			bool has;
			int left;
			Engine::Item item = owningPlayer->GetItem(currentSelection, has);
			if (has)
			{
				bool has_empty_space = true;
				//we check 8 cells near player, stop if find empty one
				//starts with -1 because we need go left -> right ; up->down
				for (int x = -1; x < 2; x++)
				{
					for (int y = -1; y < 2; y++)
					{
						Engine::Cell cell = owningPlayer->World->GetCellData(Vector(x + owningPlayer->Location.X, y + owningPlayer->Location.Y));
						if (!cell.Occupied && cell.OccupantId == -1)//fully empty cell
						{
							//spawn item here
							Engine::CItemPickup* pickup = owningPlayer->World->SpawnObject<Engine::CItemPickup>(item);
							pickup->Item.CurrentAmount = 1;
							pickup->Location = Vector(x + owningPlayer->Location.X, y + owningPlayer->Location.Y);
							pickup->Init();
							owningPlayer->RemoveItem(item.name, 1, left);
							
							owningPlayer->World->GameplayUpdate = true;
							return;
						}
						else if (cell.OccupantId != -1)//not blocking but something is there
						{
							if (Engine::CItemPickup* pickup = dynamic_cast<Engine::CItemPickup*>(owningPlayer->World->GetObjectByObjectId(cell.OccupantId)))
							{
								if (pickup->Item.CurrentAmount + 1 <= pickup->Item.MaxAmout && pickup->Item.name == item.name)
								{
									pickup->Item.CurrentAmount += 1;//successfully put away one item
									
									owningPlayer->RemoveItem(item.name, 1, left);
									owningPlayer->World->GameplayUpdate = true;
									break;
								}
								//we could not add item to existing item drop
							}
						}
					}
				}

			}
		}
		if (owningPlayer->INPUT_SYSTEM["use_item"])
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
	}
}
