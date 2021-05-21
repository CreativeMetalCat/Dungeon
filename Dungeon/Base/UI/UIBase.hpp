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
			//will this element be destroyed on the next update?
			bool pendingKill = false;

			//Location relative to the screen
			Vector onScreenLocation;
		public:
			CUIBase(String name = "UI", String displayName= "" ,Vector location = Vector(0,0),Vector size = Vector(0, 0),bool hasBorder  = true);

			String Name = "UI";

			Vector GetOnScreenLocation();

			void SetOnScreenLocation(Vector loc);

			Vector Size;

			//If true this UI element will act as a frame
			//if false it will be closer to label
			bool HasBorder = true;

			//Will be displayed if HasBorder is true written on the top of the upper border
			//If HasBorder is false this will be the only thing displayed
			String DisplayName;

			//Parent of this ui -> used for calculating location
			CUIBase* Parent = nullptr;

			//List of child uis this object has. Location of children is relative to the ui object itself
			Array<CUIBase*>ChildUI = Array<CUIBase*>();

			virtual void Draw();

			/*Make ui process whateever key was pressed last. 
			Note: ui should not have any effect on gameplay because it's placed in full update category at all times
			Note2: ProcessInput for ui is same as Update for object for the reasons stated in note 1*/
			virtual void ProccessInput(int input) {}

			virtual bool Valid()const { return !pendingKill; }
			virtual void Destroy() { pendingKill = true; }
		};
	}
}


