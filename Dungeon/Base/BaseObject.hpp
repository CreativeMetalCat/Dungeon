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

		CBaseObject(char displayChar = '#'):DisplayCharacter(displayChar){}

		//World in which this object exists
		CWorld* World;

		Vector Location;

		char GetDisplayCharacter()const { return DisplayCharacter; }

		CollisionType Collision = CollisionType::None;

		bool Visible = true;

		virtual void Update() = 0;

		virtual void ProcessInput(char) {}

		virtual void OnOverlap(CBaseObject* other) {}
	};
}
