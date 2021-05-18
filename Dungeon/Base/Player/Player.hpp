#pragma once
#include "Base/BaseObject.hpp"
#include "Base/Pawns/Pawn.hpp"

namespace Dungeon
{
	class CPlayer : public Engine::CPawn
	{
	public:
		CPlayer();

		virtual void ProcessInput(char) override;

		// Inherited via CPawn
		virtual void Update() override;
	};
}

