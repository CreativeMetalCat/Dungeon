#pragma once
#include "Types/Types.hpp"

namespace Engine 
{
	class CWorld;

	enum class Faction : char
	{
		World = 0,
		Player = 1,
		EnemyOfAll = 2
	};

	//base object for everything that player will interact in world
	class CBaseObject
	{
	protected:
		bool pendingKill = false;

		char DisplayCharacter;
	public:

		bool Valid()const { return !pendingKill; }

		//id is not used for anything as of now, but could be useful for debug
		unsigned int id = 0;

		CBaseObject(int displayChar = '#'):DisplayCharacter(displayChar){}

		//This is the name used when telling stuff to player(lfor example #DisplayName# killed player with knife)
		String DisplayName = "Object";

		//World in which this object exists
		CWorld* World = nullptr;

		Vector Location;

		Faction Faction = Faction::World;

		char GetDisplayCharacter()const { return DisplayCharacter; }

		CollisionType Collision = CollisionType::None;

		bool Visible = true;

		virtual void Update() = 0;

		virtual void ProcessInput(int) {}

		virtual void OnOverlap(CBaseObject* other) {}

		virtual void Destroy();
	};
}
