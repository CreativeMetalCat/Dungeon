#define PDC_FORCE_UTF8

#include "pdcurses/include/curses.h"

#include "Base/Player/Player.hpp"
#include "World.h"

#include <iostream>
#include <string>
#include "Base/Pawns/Enemy/EnemyBase.hpp"
#include "Base/Item/ItemPickup.hpp"

#include "Base/Render/RenderMacros.h"
#include "Base/UI/Player/PlayerStatsUI.hpp"

int main()
{
	//init pdcurses
	initscr();
	start_color();
	keypad(stdscr, true);
	raw();
	noecho();

	if (has_colors())
	{
		init_pair((int)RenderData::ColorPalleteType::Default, COLOR_WHITE, COLOR_BLACK);
		init_pair((int)RenderData::ColorPalleteType::Enemy, COLOR_RED, COLOR_BLACK);
		init_pair((int)RenderData::ColorPalleteType::Item, COLOR_BLUE, COLOR_BLACK);
		init_pair((int)RenderData::ColorPalleteType::Selected, COLOR_BLACK, COLOR_WHITE);
	}

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
		if (i == 0 || i == 9)
		{
			for (int u = 1; u < 10; u++)
			{
				CPawn* objt = world->SpawnObject<CPawn>('#');
				objt->Collision = CollisionType::Block;
				objt->Location.Y = i;
				objt->Location.X = u;
			}
		}

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

	world->DebugOutput = world->CreateUI<UI::CUIBase>(nullptr, "DebugUIFrame", "-Debug Info-", Vector(0, 20), Vector(15, 10), true);

	Dungeon::CPlayerStatsUI* statsUI = world->CreateUI<Dungeon::CPlayerStatsUI>(nullptr, player, "stats", "-Stats-", Vector(20, 20), Vector(20, 10));

	//update cycle

	world->CurrenInput = wgetch(stdscr);
	while (true)
	{
		clear();
		//proccess input runs before any update
		for (int i = 0; i < world->Objects.size(); i++) 
		{
			world->Objects[i]->ProcessInput(world->CurrenInput);
		}
		for (auto it = world->Objects.begin(); it != world->Objects.end(); ++it)
		{
			if ((*it)->Valid())
			{
				switch ((*it)->UpdateType)
				{
				case EUpdateType::EventOnly:
				{
					if (world->GameplayUpdate)
					{
						(*it)->Update();
					}
					break;
				}
				case EUpdateType::Full:
				{
					(*it)->Update(); break;
				}
				default:
					break;
				}
				
				//no matter the update type draw function is always called
				if ((*it) != player)
				{
					(*it)->Draw(Vector((*it)->Location.X - player->Location.X + 60, (*it)->Location.Y + 15 - player->Location.Y));
				}
				else
				{
					(*it)->Draw(Vector(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2));
				}
			}
		}
		world->GameplayUpdate = false;

		for (int i = 0;i< world->Objects.size();i++)
		{
			if (!world->Objects[i]->Valid())
			{
				delete (world->Objects[i]);
				world->Objects.erase(world->Objects.begin() + i);
			}
			
		}

		world->AddDebugMessage("X: " + std::to_string(player->Location.X) + "Y: " + std::to_string(player->Location.Y));

		world->UpdateUI();
		
		refresh();
		world->CurrenInput = wgetch(stdscr);
		if (world->CurrenInput == 27/*esc key*/)
		{
			
			endwin();
			return 0;
		}
		else
		{
			world->AddDebugMessage(std::to_string(world->CurrenInput));
		}
	}


}