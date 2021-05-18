#pragma once
#include "..\BaseObject.hpp"

namespace Engine
{
	//Similar to base object but has basic collision checks
	class CPawn : public CBaseObject
	{
	public:
		CPawn(char displayChar = 'P');

		int Health = 1;

		virtual void Die(CBaseObject* killer) {}

		/*This function checks if there are any objects in that space and either doesn't move or moves and triggers their overlap event*/
		void MoveTo(Vector newLocation);

		void Move(Vector direction);

		// Inherited via CBaseObject
		virtual void Update() override;
	};
}

