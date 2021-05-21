#pragma once
#include "Base/Pawns/Pawn.hpp"
namespace Engine
{
	class CEnemyBase : public CPawn
	{
	public:
		int Range = 1;

		CEnemyBase();

		virtual void Update()override;

		virtual void Attack(CBaseObject* victim);
	};
}

