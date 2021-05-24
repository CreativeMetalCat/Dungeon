#include "World.h"

#include "JSON/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

Engine::CWorld::CWorld()
{
	if (!LoadEntityFile()) { quick_exit(5); }
}

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

bool Engine::CWorld::LoadEntityFile()
{
	std::ifstream assetStream("Assets/Entities.dat", std::ios::in);
	if (assetStream.is_open())
	{
		std::stringstream sstr;
		sstr << assetStream.rdbuf();
		entityFileText = sstr.str();
		assetStream.close();
	}
	else
	{
		return false;
	}

	if (entityFileText == "")
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Engine::CWorld::ProcessInput()
{
	//proccess input runs before any update
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects[i]->ProcessInput(CurrenInput);
	}
}

void Engine::CWorld::KillActorsMarkedForDelete()
{
	for (int i = 0; i < Objects.size(); i++)
	{
		if (!Objects[i]->Valid())
		{
			delete (Objects[i]);
			Objects.erase(Objects.begin() + i);
		}
	}
}

void Engine::CWorld::Update()
{

}
