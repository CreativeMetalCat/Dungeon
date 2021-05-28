#pragma once
#include "Base/Types/Types.hpp"
namespace Engine
{
	struct Item
	{
	public:
		//Depending on this type item will be put in specific slot and specific values will be used
		enum class EquippableType : unsigned int
		{
			//Can not be equipped. This is default for simplicity
			None,
			//This item uses item slot
			Armor,
			//This item uses weapon slot
			Weapon
		};

		enum class ItemType :unsigned int
		{
			//this item can not be directcly used by player
			Generic,
			//player can consume this item via inventory system
			Consumable,
			//player can equip this item via inventory system
			Equippable
		};

		Item(String _name, String displayName, int maxAmout, int currentAmout) :
			name(_name), DisplayName(displayName), MaxAmout(maxAmout), CurrentAmout(currentAmout) {}

		//What kind of item this is 
		EquippableType Type = EquippableType::None;

		String name = "item0";

		String DisplayName = "Item";

		int MaxAmout = 99;

		int CurrentAmout = 0;

#pragma region Type
		ItemType itemType = ItemType::Generic;
#pragma endregion
	};
}

