#include "BaseObject.hpp"
#include "Render/RenderMacros.h"
#include "World.h"

void Engine::CBaseObject::Draw(Vector locationOffset)
{
	if (!Visible)return;

	//id, data.Color, data.BackgroundColor);
	ADD_CHAR_AT_W(stdscr,locationOffset.Y, locationOffset.X, data.DisplayChar| COLOR_PAIR((int)data.Type));

}

void Engine::CBaseObject::Destroy()
{
	//add code that will remove this object from game
	pendingKill = true;
}

void Engine::CBaseObject::Init()
{
	EXEC_IF_VALID(World, World->SetCellData(Location, { Location,CollisionType::Block == Collision,id }););
}
