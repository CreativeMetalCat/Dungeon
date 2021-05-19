#pragma once
#include "Base/Types/Types.hpp"

//This class is used to display ui elements on screen
namespace Engine
{
	namespace UI 
	{
		class CUIBase
		{
		protected:
			//Location relative to the screen
			Vector onScreenLocation;
		public:
			Vector GetOnScreenLocation()const { return onScreenLocation; }

			void SetOnScreenLocation(Vector loc);

			Vector Size;

			bool HasBorder = true;
		};
	}
}


