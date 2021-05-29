#pragma once
#include "Base/BaseObject.hpp"
#include "Base/Pawns/Pawn.hpp"
#include "Base/Item/Item.hpp"

#include "Base/UI/UIBase.hpp"
namespace Dungeon
{
	class CPlayer : public Engine::CPawn
	{
	protected:
		Engine::UI::CUIBase* inventoryFrame = nullptr;

		//Who is going to be attacked next
		CPawn* target = nullptr;

		void UpdateItemUI(int id);
	public:
		CPlayer(Engine::UI::CUIBase* _inventoryFrame = nullptr);

		//Adds item to the inventory. If item slot of the same type as given item -> this item will be put in that slot
		virtual bool AddItem(Engine::Item item,int &amountLeft, int& resultId, bool auto_eqiup = true)override;

		virtual void ProcessInput(int) override;

		// Inherited via CPawn
		virtual void Update() override;

		virtual void OnItemCountUpdated(int id)override;

		int Mana = 1;
	};
}

