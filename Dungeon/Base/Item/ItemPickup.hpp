#pragma once
#include "Base/BaseObject.hpp"
#include "Item.hpp"

namespace Engine
{
	class CItemPickup : public CBaseObject
	{
	public:
		CItemPickup(Item item);

		//Item that will be picked up
		Item Item;
	
		// Inherited via CBaseObject
		virtual void Update() override;

		virtual void OnOverlap(CBaseObject* other)override;
	};
}


