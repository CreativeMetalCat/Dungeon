#include "Pawn.hpp"
#include "..\..\World.h"


Engine::CPawn::CPawn(char displayChar):Engine::CBaseObject(displayChar)
{
}

void Engine::CPawn::Move(Engine::Vector newLocation)
{
	if (World)
	{
		//do a very basic for loop to find if there are objects in that spot

		Array<CBaseObject*>::iterator it =  std::find_if(World->Objects.begin(), World->Objects.end(), [newLocation](Engine::CBaseObject* obj) {return obj->Location == newLocation; });
		if (it != World->Objects.end())
		{
			if ((*it)->Collision == CollisionType::Overlap)
			{
				(*it)->OnOverlap(this);
			}
			else if((*it)->Collision == CollisionType::Block)
			{
				//we could not move so we stayed in place
			}
			else
			{
				Location = newLocation;
			}
		}
		else
		{
			//move pawn and stay happy
			Location = newLocation;
		}
	}
}

void Engine::CPawn::Update()
{
}
