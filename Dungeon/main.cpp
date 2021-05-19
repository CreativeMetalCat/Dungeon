#define PDC_FORCE_UTF8

#include "pdcurses/include/curses.h"

#include "Base/Player/Player.hpp"
#include "World.h"

#include <iostream>
#include <string>
#include "Base/Pawns/Enemy/EnemyBase.hpp"
#include "Base/Item/ItemPickup.hpp"

#include "Base/Render/RenderMacros.h"
int main()
{
	//init pdcurses
	initscr();
	start_color();
	keypad(stdscr, true);
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
	UI::CUIBase* keyText = world->CreateUI<UI::CUIBase>(ui2, "lastKey", "none", Vector(1, 2), Vector(0, 0), false);

	//update cycle

	int input = getch();
	while (true)
	{
		

		clear();
		for (int i = 0; i < world->Objects.size(); i++) 
		{
			world->Objects[i]->ProcessInput(input);
			
		}
		for (auto it = world->Objects.begin();it != world->Objects.end();++it)
		{
			if ((*it)->Valid())
			{
				(*it)->Update();
				if ((*it) != player)
				{
					ADD_CHAR_AT((*it)->Location.Y + 15 - player->Location.Y, (*it)->Location.X - player->Location.X + 60, (*it)->GetDisplayCharacter());
				}
				else
				{
					ADD_CHAR_AT(15, 60, (*it)->GetDisplayCharacter());
				}
			}
		}

		for (int i = 0;i< world->Objects.size();i++)
		{
			if (!world->Objects[i]->Valid())
			{
				delete (world->Objects[i]);
				world->Objects.erase(world->Objects.begin() + i);
			}
			
		}

		locText->DisplayName = ("X: " + std::to_string(player->Location.X) + "Y: " + std::to_string(player->Location.Y)).c_str();

		for (auto it = world->UIElements.begin(); it != world->UIElements.end(); ++it)
		{
			(*it)->ProccessInput(input);
			(*it)->Draw();
		}
	
		input = wgetch(stdscr);
		if (input == 27)
		{
			endwin();
			return 0;
		}
		else
		{
			keyText->DisplayName = std::to_string(input);
		}
	}


}