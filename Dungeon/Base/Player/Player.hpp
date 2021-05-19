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
	public:
		CPlayer(Engine::UI::CUIBase* _inventoryFrame = nullptr);

		virtual bool AddItem(Item item,int &amountLeft, int& resultId)override;

		virtual void ProcessInput(char) override;

		// Inherited via CPawn
		virtual void Update() override;
	};
}

