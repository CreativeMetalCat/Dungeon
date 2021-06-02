#include "InputSystem.hpp"

#include <JSON/json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

Engine::Input::CInputSystem::CInputSystem()
{
    LoadData();
}

bool Engine::Input::CInputSystem::operator[](String inputName)
{
    auto it = std::find_if(Inputs.begin(), Inputs.end(),
        [inputName,this](Pair<String, Array<int>> input)
        {
            if (inputName == input.first)
            {
                return input.second.end() != std::find(input.second.begin(), input.second.end(), CurrentFrameInput);
            }
            return false;
        });
    return it != Inputs.end();
}

String Engine::Input::CInputSystem::operator[](int input)
{
    auto it = std::find_if(Inputs.begin(), Inputs.end(),
        [input](Pair<String, Array<int>> inputPair)
        {
            return inputPair.second.end() != std::find(inputPair.second.begin(), inputPair.second.end(), input);
        });

    return it == Inputs.end() ? "none" : (*it).first;
}

void Engine::Input::CInputSystem::LoadData()
{
    std::ifstream assetStream("Assets/Input.dat", std::ios::in);
    String inputFileText;
    if (assetStream.is_open())
    {
        std::stringstream sstr;
        sstr << assetStream.rdbuf();
       inputFileText = sstr.str();
        assetStream.close();
    }
    else
    {
        return;
    }

    if (inputFileText == "")
    {
        return;
    }
    else
    {
        nlohmann::json inputs = nlohmann::json::parse(inputFileText);
        try
        {
            for (nlohmann::json::iterator it = inputs["inputs"].begin(); it != inputs["inputs"].end(); ++it)
            {
                Array<int> keys = Array<int>();
                for (nlohmann::json::iterator it_key = (*it)["keys"].begin(); it_key != (*it)["keys"].end(); ++it_key)
                {
                    keys.push_back((*it_key).get<int>());
                }
                Inputs.push_back(Pair<String, Array<int>>((*it)["name"].get<String>(), keys));
            }
        }
        catch (nlohmann::detail::parse_error e)
        {          
            return;
        }
        catch (nlohmann::detail::type_error e)
        {
            return;
        }
    }
}
