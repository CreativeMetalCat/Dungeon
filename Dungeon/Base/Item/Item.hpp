#pragma once
#include "Base/Types/Types.hpp"
namespace Engine
{
	struct Item
	{
	public:
		Item(String _name, String displayName, int maxAmout, int currentAmout) :
			name(_name), DisplayName(displayName), MaxAmout(maxAmout), CurrentAmout(currentAmout) {}

		String name = "item0";

		String DisplayName = "Item";

		int MaxAmout = 99;

		int CurrentAmout = 0;
	};
}

