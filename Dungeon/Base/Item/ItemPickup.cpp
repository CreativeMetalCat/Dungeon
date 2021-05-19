#include "ItemPickup.hpp"
#include "Base/Player/Player.hpp"


Engine::CItemPickup::CItemPickup(Engine::Item item):CBaseObject('i'),Item(item)
{
	Collision = CollisionType::Overlap;
	data.Type = RenderData::ColorPalleteType::Item;
}

void Engine::CItemPickup::Update()
{
}

void Engine::CItemPickup::OnOverlap(CBaseObject* other)
{
	if (other)
	{
		if (Dungeon::CPlayer* player = dynamic_cast<Dungeon::CPlayer*>(other))
		{
			int left, b;
			player->AddItem(Item, left, b);
			if(left == 0)
			{
				Destroy();
			}
		}
	}
}
