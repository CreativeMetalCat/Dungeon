#pragma once
#include "Base/BaseObject.hpp"
#include "Base/Item/Item.hpp"
#include "Base/UI/UIBase.hpp"
namespace Engine
{
	//Similar to base object but has basic collision checks
	class CPawn : public CBaseObject
	{
		
	events:
		
		//Called when there is a new entry to the item list
		CEvent<void(CBaseObject::*)(String/*name of the item for display */,int/*id of item*/), CBaseObject*>OnItemAddedEvent;

		//Called when there is a new entry to the item list
		CEvent<void(CBaseObject::*)(String/*name of the item for display*/, int/*id of item*/), CBaseObject*>OnItemRemovedEvent;

		//Called when Count of item in the inventory is updated
		CEvent<void(CBaseObject::*)(int/*id of item*/), CBaseObject*>OnItemCountUpdatedEvent;
	protected:

		typedef void (CBaseObject::* pFunc)();

		virtual void OnItemCountUpdated(int id);

		//even though pawn has limited invenotry it is much easier to change size of inventory due to game events if array already has no limits
		Array<Item>Items = Array<Item>();

		Array<Engine::UI::CUIBase*> inventoryItemsUI = Array<Engine::UI::CUIBase*>();

		//Currently applied effects
		Array<LastingEffect>effects = Array<LastingEffect>();

		bool selected = false;

		RenderData::ColorPalleteType defaultColorPallet;
	public:
		CPawn(char displayChar = 'P');

#pragma region items_slots
		//This item will be used to dictate damage of the pawn udring attack
		//-1 means there is no item in the slot
		int SwordItemId = -1;

		//This item will be used damage dealt to this pawn and if there are any effects to apply
		 //-1 means there is no item in the slot
		int ArmorItem = -1;
#pragma endregion

		int GetCurrentItemCount()const { return Items.size(); }

		int MaxItems = 5;

		//Adds item to the inventory. If item slot of the same type as given item -> this item will be put in that slot
		virtual bool AddItem(Item item, int& amountLeft, int& resultId, bool auto_eqiup = true);

		virtual bool RemoveItem(String name, int amount, int& amount_left);

		Item GetItem(String name, bool& has);

		Item GetItem(int id, bool& has);

		//Tries to consume item -> or does nothing if item can not be consumed
		void ConsumeItem(int id);

		//Tries to update item slot it. Does nothing if id is invalid
		void EquipItem(int id);

		int Health = 1;

		int MaxHealth = 10;

		int Strenght = 1;

		int Defence = 0;

		virtual void Die(CBaseObject* killer) {}

		virtual int ReceiveDamage(int Damage, CPawn* damager);

		/*This function checks if there are any objects in that space and either doesn't move or moves and triggers their overlap event*/
		void MoveTo(Vector newLocation);

		bool Move(Vector direction);

		// Inherited via CBaseObject
		virtual void Update() override;

		virtual void SetSelected(bool _selected);
	};
}

