#include "World.h"

#include "JSON/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

Engine::CWorld::CWorld()
{
	if (!LoadEntityFile()) { quick_exit(5); }
	LoadItemFile();
	Input = Input::CInputSystem();
}

Engine::Cell Engine::CWorld::GetCellData(Vector loc)
{
	auto it = std::find_if(occupanceData.begin(), occupanceData.end(), [loc](Cell cell) {return cell.Location == loc; });
	if (it == occupanceData.end())
	{
		occupanceData.push_back({ loc,false,-1 });
		return occupanceData[occupanceData.size() - 1];
	}
	return *it;
}

void Engine::CWorld::SetCellData(Vector loc, Cell cell)
{
	auto it = std::find_if(occupanceData.begin(), occupanceData.end(), [loc](Cell cell) {return cell.Location == loc; });
	if (it == occupanceData.end())
	{
		occupanceData.push_back(cell);
	}
	else
	{
		(*it) = cell;
	}
}

Engine::CBaseObject* Engine::CWorld::GetObjectByObjectId(unsigned int id)
{
	try
	{
		auto it = std::find_if(Objects.begin(), Objects.end(), [id](CBaseObject* obj)
			{
				return obj->id == id; 
			});
		if (it == Objects.end())
		{
			return nullptr;
		}
		else
		{
			return *it;
		}
	}
	catch (const std::exception&e)
	{
		return nullptr;
	}
	
}

Engine::Item Engine::CWorld::GetItemDefaultData(String itemName, bool& hasData) const
{
	if (!defaultItemData.empty())
	{
		Array<Item>::const_iterator it = std::find_if(defaultItemData.begin(), defaultItemData.end(), [this, itemName](Item item) {return itemName == item.name; });
		if (it != defaultItemData.end())
		{
			hasData = true;
			return *it;
		}
	}
	hasData = false;
	return Engine::Item("item0", "item0", -1, -1);
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
			(*it)->ProcessInput(CurrenInput);
		}
		(*it)->Draw();
	}

	for (int i = UIElements.size() - 1; i > -1; --i)
	{
		if (!UIElements[i]->Valid())
		{
			UIElements.erase(UIElements.begin() + i);
		}
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

bool Engine::CWorld::LoadItemFile()
{
	std::ifstream assetStream("Assets/Items.dat", std::ios::in);
	String itemFileText;
	if (assetStream.is_open())
	{
		std::stringstream sstr;
		sstr << assetStream.rdbuf();
		itemFileText = sstr.str();
		assetStream.close();
	}
	else
	{
		return false;
	}

	if (itemFileText == "")
	{
		return false;
	}
	//parse data into the array
	else
	{
		nlohmann::json items = nlohmann::json::parse(itemFileText);
		try
		{
			for (nlohmann::json::iterator it = items["items"].begin(); it != items["items"].end(); ++it)
			{
				//*it here is the item data
				Item res = Item((*it)["name"], (*it)["display_name"], (*it)["max_amount"], (*it)["default_amount"]);
				res.EquippableType = (Item::EEquippableType)(int)(*it)["equippable_type"];
				res.ItemType = (Item::EItemType)(int)(*it)["type"];

				for (auto eff_it = (*it)["effects"].begin(); eff_it != (*it)["effects"].end(); ++eff_it)
				{

					res.Effects.push_back
					(
						{
							(Item::EEffectType)(int)(*eff_it)["type"],
							(int)(*eff_it)["amount"]
						}
					);
				}
				defaultItemData.push_back(res);
			}
			return true;
		}
		catch (nlohmann::detail::parse_error e)
		{
			AddDebugMessage(e.what());
			return false;
		}
		catch (nlohmann::detail::type_error e)
		{
			AddDebugMessage(e.what());
			return false;
		}
		
	}
}

void Engine::CWorld::ProcessInput()
{
	Input.CurrentFrameInput = CurrenInput;
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
