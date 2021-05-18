#include "Player.hpp"
#include "Base/Pawns/Pawn.hpp"

Dungeon::CPlayer::CPlayer() :Engine::CPawn('@')
{
	Faction = Engine::Faction::Player;
}

void Dungeon::CPlayer::ProcessInput(char input)
{
	switch (input)
	{
	case 'a':
	{
		Move(Engine::Vector(-1, 0));
		break;
	}
	case 'd':
	{
		Move(Engine::Vector(1, 0));
		break;
	}
	case 's':
	{
		Move(Engine::Vector(0, 1));
		break;
	}
	case 'w':
	{
		Move(Engine::Vector(0, -1));
		break;
	}
	default:
		break;
	}
}

void Dungeon::CPlayer::Update()
{
}
