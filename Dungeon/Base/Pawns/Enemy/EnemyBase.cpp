#include "EnemyBase.hpp"
#include "World.h"
#include "Base/Item/ItemPickup.hpp"

Engine::CEnemyBase::CEnemyBase()
	:CPawn('E')
{
	data.Type = RenderData::ColorPalleteType::Enemy;
	defaultColorPallet = RenderData::ColorPalleteType::Enemy;
	UpdateType = EUpdateType::EventOnly;
	Faction = EFaction::EnemyOfAll;
}

void Engine::CEnemyBase::Update()
{
	//this is base ai for enemy -> attack if someone is near or move in random direction if noone is near

	//find enemies in range and attack them
	Array<CBaseObject*>::iterator it = std::find_if(World->Objects.begin(), World->Objects.end(), 
		[this](CBaseObject* obj)
		{
			return
				obj->Location.Distance(Location) <= Range
				&& obj != this
				&& obj->Faction == EFaction::Player;
		}
	);

	if (it != World->Objects.end())
	{
		Attack(*it);
	}
	else
	{
		auto vec = Engine::Vector((rand() % 4) - 2, (rand() % 4) - 2);
		Move(vec);
		this->World->AddDebugMessage(vec.ToString());
	}
}

void Engine::CEnemyBase::Attack(CBaseObject* victim)
{
	if (CPawn* pawn = dynamic_cast<CPawn*>(victim))
	{
		pawn->ReceiveDamage(1, this);
	}
}

void Engine::CEnemyBase::Die(CBaseObject* killer)
{
	Engine::CItemPickup * pickup = World->SpawnObject<Engine::CItemPickup>(Item("itemio", "Trash", 10, 5));
	pickup->Location = Location;
	World->AddDebugMessage(Name + " died by the hands of " + killer->Name);
	Destroy();
}
