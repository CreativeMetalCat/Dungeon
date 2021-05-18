
#include "pdcurses/include/curses.h"

#include "Base/Player/Player.hpp"
#include "World.h"

#include <iostream>
#include <string>
#include "Base/Pawns/Enemy/EnemyBase.hpp"

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
	CPlayer* player = new CPlayer();
	player->Location = Engine::Vector(20, 9);
	player->World = world;
	world->Objects.push_back(player);

	for (int i = 0; i < 10;i++)
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

		move(500, 0);
		addstr("\n Debug info: \n");
		addstr(("X: " + std::to_string(player->Location.X) + "Y: " + std::to_string(player->Location.Y)).c_str());
		input = getch();
		if (input == 'y')
		{
			endwin();
			return 0;
		}
	}


}