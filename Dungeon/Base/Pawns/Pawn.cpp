#include "Pawn.hpp"
#include "..\..\World.h"


Engine::CPawn::CPawn(char displayChar):Engine::CBaseObject(displayChar)
{
	Faction = EFaction::World;
}

bool Engine::CPawn::AddItem(Item item, int& amountLeft,int &resultId)
{
	amountLeft = item.CurrentAmout;
	resultId = -1;
	//check if can add the item
	for (int i = 0; i < Items.size(); i++)
	{
		if (Items[i].name == item.name)
		{
			if (Items[i].MaxAmout - Items[i].CurrentAmout > 0)
			{
				if (amountLeft >= Items[i].MaxAmout - Items[i].CurrentAmout)
				{
					amountLeft = amountLeft - Items[i].MaxAmout - Items[i].CurrentAmout;
					Items[i].CurrentAmout = Items[i].MaxAmout;
				}
				else
				{
					amountLeft = 0;
					Items[i].CurrentAmout += amountLeft;
					return true;
				}
			}
		}
	}
	if (Items.size() < MaxItems)
	{
		resultId = Items.size() - 1;
		Items.push_back(item);
		amountLeft = 0;
	}
	return amountLeft == 0;
}

bool Engine::CPawn::RemoveItem(String name, int amount)
{
	return false;
}

int Engine::CPawn::ReceiveDamage(int damage, CPawn* damager)
{
	Health -= (damage - Defence) < 0 ? 0 : (damage - Defence);
	if (Health <= 0) { Die(damager); }
	return (damage - Defence);
}

void Engine::CPawn::MoveTo(Engine::Vector newLocation)
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

bool Engine::CPawn::Move(Engine::Vector direction)
{
	if (World)
	{
		Vector dir = direction.Normalise();
		//do a very basic for loop to find if there are objects in that spot

		Array<CBaseObject*>::iterator it = std::find_if(World->Objects.begin(), World->Objects.end(), [this, dir](Engine::CBaseObject* obj) {
			return obj->Location == Location + dir; 
			});
		if (it != World->Objects.end())
		{
			if ((*it)->Collision == CollisionType::Overlap)
			{
				(*it)->OnOverlap(this);
			}
			else if ((*it)->Collision == CollisionType::Block)
			{
				//we could not move so we stayed in place
				return false;
			}
			else
			{
				Location = Location + dir;
				return true;
			}
		}
		else
		{
			//move pawn and stay happy
			Location = Location + dir;
			return true;
		}
	}
	return false;
}

void Engine::CPawn::Update()
{
}

void Engine::CPawn::SetSelected(bool _selected)
{
	selected = _selected;
	data.Type = selected ? RenderData::ColorPalleteType::Selected : defaultColorPallet;
}
