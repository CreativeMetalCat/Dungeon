#include "EnemyBase.hpp"
#include "World.h"


void Engine::CEnemyBase::Update()
{
	//find enemies in range and attack them
	Array<CBaseObject*>::iterator it =  std::find_if(World->Objects.begin(), World->Objects.end(), [this](CBaseObject* obj) {return obj->Location.Distance(Location) <= Range; });
	if (it != World->Objects.end())
	{
		Attack(*it);
	}
}
