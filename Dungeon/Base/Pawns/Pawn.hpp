#pragma once
#include "..\BaseObject.hpp"

namespace Engine
{
	//Similar to base object but has basic collision checks
	class CPawn : public CBaseObject
	{
	public:
		CPawn(char displayChar = 'P');

		/*This function checks if there are any objects in that space and either doesn't move or moves and triggers their overlap event*/
		void Move(Vector newLocation);

		// Inherited via CBaseObject
		virtual void Update() override;
	};
}

