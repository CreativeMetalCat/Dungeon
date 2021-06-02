#pragma once
#include "Base/Types/Types.hpp"

namespace Engine
{
	namespace Input
	{
		class CInputSystem
		{
		public:

			CInputSystem();

			//What input happened during this frame
			//Due to the fact that this is a console game only one input at a time can happen
			int CurrentFrameInput = -1;

			/*Array of inputs used in this game*/
			Array<Pair<String/*input event name*/, Array<int>/*inputs binded to it*/>> Inputs = Array<Pair<String, Array<int>>>();

			//Get if input action was pressed
			bool operator[](String inputName);

			//Gets first input action that is binded to this input
			//Note: it is done this way because this game is intended to only have one input
			//Note2: This funtion is not meant for actual input getting -> use bool operator[](String inputName) for that
			String operator[](int input);

			//Loads input data from Input.dat
			void LoadData();
		};
	}
}

