
#include "pdcurses/include/curses.h"

#include "Base/Player/Player.hpp"
#include "World.h"

#include <iostream>
#include <string>
#include "Base/Pawns/Enemy/EnemyBase.hpp"
#include "Base/Item/ItemPickup.hpp"
int main()
{
	//init pdcurses
	initscr();
	start_color();
	raw();
	noecho();

	//create world
	using namespace Engine;
	using namespace Dungeon;

	

	CWorld* world = new CWorld();

	UI::CUIBase* ui = world->CreateUI<UI::CUIBase>();
	ui->Size = Vector(15, 10);
	ui->DisplayName = "Inventory";

	CPlayer* player = world->SpawnObject<CPlayer>(ui);
	player->Location = Engine::Vector(20, 9);

	for (int i = 0; i < 10; i++)
	{

		CPawn* obj = world->SpawnObject<CPawn>('#');
		obj->Collision = CollisionType::Block;
		obj->Location.Y = i;
		obj->Location.X = 0;

		if (i != 5)
		{
			CPawn* obj2 = world->SpawnObject<CPawn>('#');
			obj2->Collision = CollisionType::Block;
			obj2->Location.Y = i;
			obj2->Location.X = 10;
		}

	}
	CEnemyBase* enemy = world->SpawnObject<CEnemyBase>();
	enemy->Location = Vector(5, 5);
	enemy->Collision = CollisionType::Block;
	
	CItemPickup* item = world->SpawnObject<CItemPickup>(Item("itemio","Trash",10,5 ));
	item->Location = Vector(5, 6);

	UI::CUIBase* ui2 = world->CreateUI<UI::CUIBase>(nullptr, "DebugUIFrame", "-Debug Info-", Vector(0, 20), Vector(15, 10), true);
	UI::CUIBase* locText = world->CreateUI<UI::CUIBase>(ui2, "locText", "X: 0, Y: 0", Vector(1, 1), Vector(0, 0), false);

	//update cycle

	char input = getch();
	while (true)
	{
		clear();
		for (int i = 0; i < world->Objects.size(); i++) 
		{
			world->Objects[i]->ProcessInput(input);
			
		}
		for (auto it = world->Objects.begin();it != world->Objects.end();++it)
		{
			(*it)->Update();
			if ((*it) != player)
			{
				mvaddch( (*it)->Location.Y + 15 - player->Location.Y,  (*it)->Location.X - player->Location.X + 60, (*it)->GetDisplayCharacter());
			}
			else
			{
				mvaddch(15, 60, (*it)->GetDisplayCharacter());
			}
		}
		locText->DisplayName = ("X: " + std::to_string(player->Location.X) + "Y: " + std::to_string(player->Location.Y)).c_str();

		for (auto it = world->UIElements.begin(); it != world->UIElements.end(); ++it)
		{
			if ((*it)->HasBorder)
			{
				if ((*it)->Size.X > 0 && (*it)->Size.Y > 0)
				{
					//Create upper border
					mvaddch((*it)->GetOnScreenLocation().Y, (*it)->GetOnScreenLocation().X, ACS_ULCORNER);

					for (int i = 1; i < (*it)->Size.X - 1; i++)
					{
						mvaddch((*it)->GetOnScreenLocation().Y, (*it)->GetOnScreenLocation().X + i, '-');
					}
					mvaddch((*it)->GetOnScreenLocation().Y, (*it)->GetOnScreenLocation().X + (*it)->Size.X - 1, ACS_URCORNER);
					mvprintw((*it)->GetOnScreenLocation().Y, (*it)->GetOnScreenLocation().X + 1, (*it)->DisplayName.c_str());

					//create left and right border
					for (int i = 1; i < (*it)->Size.Y; i++)
					{
						mvaddch((*it)->GetOnScreenLocation().Y + i, (*it)->GetOnScreenLocation().X, '|');
						mvaddch((*it)->GetOnScreenLocation().Y + i, (*it)->GetOnScreenLocation().X + (*it)->Size.X - 1, '|');
					}

					//Create lower border
					mvaddch((*it)->GetOnScreenLocation().Y + (*it)->Size.Y - 1, (*it)->GetOnScreenLocation().X, ACS_LLCORNER);

					for (int i = 1; i < (*it)->Size.X - 1; i++)
					{
						mvaddch((*it)->GetOnScreenLocation().Y + (*it)->Size.Y - 1, (*it)->GetOnScreenLocation().X + i, '-');
					}
					mvaddch((*it)->GetOnScreenLocation().Y + (*it)->Size.Y - 1, (*it)->GetOnScreenLocation().X + (*it)->Size.X - 1, ACS_LRCORNER);
				}
			}
			else
			{
				mvprintw((*it)->GetOnScreenLocation().Y, (*it)->GetOnScreenLocation().X, (*it)->DisplayName.c_str());
			}
		}
		input = getch();
		if (input == 'y')
		{
			endwin();
			return 0;
		}
	}


}