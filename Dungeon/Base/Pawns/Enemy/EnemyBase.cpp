#include "EnemyBase.hpp"
#include "World.h"


Engine::CEnemyBase::CEnemyBase()
	:CPawn('E')
{
	data.Type = RenderData::ColorPalleteType::Enemy;
	UpdateType = EUpdateType::EventOnly;
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
