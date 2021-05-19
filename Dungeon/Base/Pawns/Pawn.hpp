#pragma once
#include "Base/BaseObject.hpp"
#include "Base/Item/Item.hpp"
#include "Base/UI/UIBase.hpp"
namespace Engine
{
	//Similar to base object but has basic collision checks
	class CPawn : public CBaseObject
	{
	protected:

		//even though pawn has limited invenotry it is much easier to change size of inventory due to game events if array already has no limits
		Array<Item>Items = Array<Item>();

		Array<Engine::UI::CUIBase*> inventoryItemsUI = Array<Engine::UI::CUIBase*>();
	public:
		CPawn(char displayChar = 'P');

		int MaxItems = 5;

		virtual bool AddItem(Item item,int &amountLeft, int& resultId);

		virtual bool RemoveItem(String name, int amount);

		int Health = 1;

		virtual void Die(CBaseObject* killer) {}

		/*This function checks if there are any objects in that space and either doesn't move or moves and triggers their overlap event*/
		void MoveTo(Vector newLocation);

		void Move(Vector direction);

		// Inherited via CBaseObject
		virtual void Update() override;
	};
}

