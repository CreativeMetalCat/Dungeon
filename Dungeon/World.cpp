#include "World.h"

void Engine::CWorld::AddDebugMessage(String msg)
{
	if (MaxDebugMessageCount == -1 || debugOutputMessages.size() < MaxDebugMessageCount)
	{
		debugOutputMessages.push_back(msg);
	}
}

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

	if (DebugOutput && !debugOutputMessages.empty())
	{
		DebugOutput->DisplayName = "\n";
		for (int i = 0; i < debugOutputMessages.size(); i++)
		{
			DebugOutput->DisplayName += debugOutputMessages[i] + "\n";
		}
		debugOutputMessages.clear();
	}
}
