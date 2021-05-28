#pragma once
#include "Base/UI/UIBase.hpp"
#include "Base/Player/Player.hpp"

namespace Dungeon
{
	class CInventoryUI : public Engine::UI::CUIBase
	{
	protected:
		int currentSelection = -1;

		void changeSelection(int selectionId);

		CPlayer* owningPlayer = nullptr;
	public:
		virtual void ProcessInput(int)override;
	};
}

