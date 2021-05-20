#include "World.h"

void Engine::CWorld::UpdateUI()
{
	for (auto it = UIElements.begin(); it != UIElements.end(); ++it)
	{
		if (CurrenInput != -1)
		{
			(*it)->ProccessInput(CurrenInput);
		}
		(*it)->Draw();
	}
}
