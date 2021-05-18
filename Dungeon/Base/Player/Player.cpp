#include "Player.hpp"
#include "Base/Pawns/Pawn.hpp"

Dungeon::CPlayer::CPlayer() :Engine::CPawn('@')
{
}

void Dungeon::CPlayer::ProcessInput(char input)
{
	switch (input)
	{
	case 'a':
	{
		Move(Engine::Vector(Location.X - 1, Location.Y));
		break;
	}
	case 'd':
	{
		Move(Engine::Vector(Location.X + 1, Location.Y));
		break;
	}
	case 's':
	{
		Move(Engine::Vector(Location.X , Location.Y + 1));
		break;
	}
	case 'w':
	{
		Move(Engine::Vector(Location.X, Location.Y - 1));
		break;
	}
	default:
		break;
	}
}

void Dungeon::CPlayer::Update()
{
}
