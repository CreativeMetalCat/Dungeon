#include "InputSystem.hpp"

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
    return false;
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
