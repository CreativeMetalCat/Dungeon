#include "Pawn.hpp"
#include "World.h"


void Engine::CPawn::OnItemCountUpdated(int id)
{
	OnItemCountUpdatedEvent.BroadCast(this, id);
}

Engine::CPawn::CPawn(char displayChar):Engine::CBaseObject(displayChar)
{
	Faction = EFaction::World;
}

bool Engine::CPawn::AddItem(Item item, int& amountLeft,int &resultId,bool auto_eqiup)
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
					OnItemCountUpdated(i);
				}
				else
				{
					Items[i].CurrentAmout += amountLeft;
					amountLeft = 0;
					OnItemCountUpdated(i);
					return true;
				}
			}
		}
	}
	if (Items.size() < MaxItems)
	{
		resultId = Items.size();
		Items.push_back(item);
		amountLeft = 0;
		if (auto_eqiup)
		{
			EquipItem(resultId);
		}
	}
	return amountLeft == 0;
}

bool Engine::CPawn::RemoveItem(String name, int amount)
{
	return false;
}

Engine::Item Engine::CPawn::GetItem(String name, bool& has)
{
	Array<Item>::iterator it = std::find_if(Items.begin(), Items.end(), [this, name](Engine::Item item) {return item.name == name; });
	if (it != Items.end())
	{
		has = true;
		return *it;
	}
	else
	{
		has = false;
		return Engine::Item("item0", "item0", -1, -1);
	}
}

Engine::Item Engine::CPawn::GetItem(int id, bool& has)
{
	if (Items.valid_index(id))
	{
		has = true;
		return Items[id];
	}
	else
	{
		has = false;
		return Engine::Item("item0", "item0", -1, -1);
	}
}

void Engine::CPawn::ConsumeItem(int id)
{
	if (Items.valid_index(id))
	{
		for (auto it = Items[id].Effects.begin(); it != Items[id].Effects.end(); ++it)
		{
			switch ((*it).Key)
			{
			case Engine::Item::EEffectType::Damage:
			{
				//by default it's "-" so that it would be easier to tell that "-" in the file is meant to be the addition
				Strenght -= (*it).Value;
				break;
			}
			/*these are !explicitly! lasting effects*/
			case  Engine::Item::EEffectType::Damage_Lasting:case  Engine::Item::EEffectType::Health_Lasting:case  Engine::Item::EEffectType::Luck:
			{
				effects.push_back({ (*it).Key/*type*/,(*it).Value/*amount*/,5/*turn count -> because it's a simple project all item's lasting effect only last for 5 turns*/ });
				break;
			}
			case  Engine::Item::EEffectType::Health:
			{
				//Because health is health reduction of health is damage
				if ((*it).Value < 0)
				{
					ReceiveDamage((*it).Value, this);
				}
				else
				{
					Health += (*it).Value;
				}
				break;
			}
			case  Engine::Item::EEffectType::Health_Max:
			{
				//by default it's "+" so that it would be easier to tell that "-" in the file is meant to be the subtraction
				MaxHealth += (*it).Value;
				break;
			}
			default:
				break;
			}
		}
	}
}

void Engine::CPawn::EquipItem(int id)
{
	if (Items.valid_index(id))
	{

		switch (Items[id].EquippableType)
		{
		case Engine::Item::EEquippableType::Armor:
		{
			ArmorItem = id;
			World->AddDebugMessage("Equipped item in armor slot");

			break;
		}
		case Engine::Item::EEquippableType::Weapon:
		{
			SwordItemId = id;
			World->AddDebugMessage("Equipped item in sword slot");

			break;
		}
		default:
			break;
		}
	}
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

	if (!effects.empty())
	{
		/*Effects are applied in reverse order, so that if effect is over it could be immediatly removed*/
		for (int i = effects.size() - 1; i > -1; --i)
		{
			/*Both damage and luck function similarly -> they don't constantly add Values, but rather add them once and then remove once time is over*/
			switch (effects[i].Type)
			{
			case  Engine::Item::EEffectType::Damage_Lasting:
			{
				if (effects[i].Turns == 5)
				{
					Strenght += effects[i].Amount;
				}
				else if (effects[i].Turns == 1)
				{
					Strenght -= effects[i].Amount;
				}
				break;
			}
			case  Engine::Item::EEffectType::Health_Lasting:
			{
				Health += effects[i].Amount;
				if (Health > MaxHealth) Health = MaxHealth;
				break;
			}
			case  Engine::Item::EEffectType::Luck:
			{
				/*no luck here pal*/
				break;
			}
			default:
				break;
			}

			if (effects[i].Turns == 1)
			{
				//remove the effect
				effects.erase(effects.begin() + i);
			}
			else
			{
				effects[i].Turns--;
			}
		}
	}
}

void Engine::CPawn::SetSelected(bool _selected)
{
	selected = _selected;
	data.Type = selected ? RenderData::ColorPalleteType::Selected : defaultColorPallet;
}
