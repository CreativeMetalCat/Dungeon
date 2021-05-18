#pragma once
#include "Types/Types.hpp"

namespace Engine 
{
	class CWorld;

	//base object for everything that player will interact in world
	class CBaseObject
	{
	protected:
		char DisplayCharacter;
	public:
		//id is not used for anything as of now, but could be useful for debug
		unsigned int id = 0;

		CBaseObject(char displayChar = '#'):DisplayCharacter(displayChar){}

		//This is the name used when telling stuff to player(lfor example #DisplayName# killed player with knife)
		String DisplayName = "Object";

		//World in which this object exists
		CWorld* World = nullptr;

		Vector Location;

		char GetDisplayCharacter()const { return DisplayCharacter; }

		CollisionType Collision = CollisionType::None;

		bool Visible = true;

		virtual void Update() = 0;

		virtual void ProcessInput(char) {}

		virtual void OnOverlap(CBaseObject* other) {}
	};
}
