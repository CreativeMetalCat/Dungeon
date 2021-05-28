#pragma once
#include "Base/Types/Types.hpp"
namespace Engine
{
	struct Item
	{
	public:
		//Depending on this type item will be put in specific slot and specific values will be used
		enum class EEquippableType : char
		{
			//Can not be equipped. This is default for simplicity
			None,
			//This item uses item slot
			Armor,
			//This item uses weapon slot
			Weapon
		};

		enum class EItemType : char
		{
			//this item can not be directcly used by player
			Generic,
			//player can consume this item via inventory system
			Consumable,
			//player can equip this item via inventory system
			Equippable
		};

		//What kind of effect this item applies
		enum class EEffectType : char
		{
			//Changes damage value of the pawn permanently
			Damage,
			//Changes value of the health
			Health,
			//Changes max health value of the pawn permanetly
			Health_Max,
			//Changes value of the damage by amout each turn - for 5 turns
			Damage_Lasting,
			//Changes value of the health by amount each turn - for 5 turns
			Health_Lasting,
			//Changes value of the luck by amount each turn - for 5 turns
			Luck
		};

		Item(String _name, String displayName, int maxAmout, int currentAmout) :
			name(_name), DisplayName(displayName), MaxAmout(maxAmout), CurrentAmout(currentAmout) {}

		//What kind of item this is 
		EEquippableType EquippableType = EEquippableType::None;

		String name = "item0";

		String DisplayName = "Item";

		int MaxAmout = 99;

		int CurrentAmout = 0;

		//These effects will be applied
		Map<EEffectType, int> Effects = Map<EEffectType, int>();

#pragma region Type
		EItemType ItemType = EItemType::Generic;
#pragma endregion
	};

	struct LastingEffect
	{
	public:
		Item::EEffectType Type = Item::EEffectType::Luck;

		int Amount = 0;

		int Turns = 0;
	};
}

